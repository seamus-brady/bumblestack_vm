/*
 * Copyright 2021 seamus@bumblestack.com, Corvideon Limited.
 * Portions of this code were originally created by the OpenNARS authors under the MIT License.

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "unit_tests.h"

void setup_logging() {// Enable all logging levels
    int enabledLevels = SLOG_FLAGS_ALL;
    // check debug logs
    if(!DEBUG_MODE){
        slog_disable(SLOG_DEBUG);
    }
    // init log system with no file output
    slog_init(NULL, enabledLevels, 0);
    // logging config
    SLogConfig slgCfg;
    slog_config_get(&slgCfg);
    // Enable date + time in output
    slgCfg.eDateControl = SLOG_DATE_FULL;
    slog_config_set(&slgCfg);
}

void setUp(void) {
    // set stuff up here
    setup_logging();
    mysrand(42);
    NAR_INIT();
}

void tearDown(void) {
    // clean stuff up here
}



void test_stamp() {
    Stamp stamp1 = {.evidentialBase = {1, 2}};
    Stamp stamp2 = {.evidentialBase = {2, 3, 4}};
    Stamp stamp3 = Stamp_make(&stamp1, &stamp2);
    TEST_ASSERT_TRUE_MESSAGE(stamp3.evidentialBase[0] != 0, "Stamp not made correctly.");
    TEST_ASSERT_TRUE_MESSAGE(Stamp_checkOverlap(&stamp1, &stamp2) == true, "Stamp should overlap.");
}

void test_fifo() {
    FIFO fifo = {0};
    //First, evaluate whether the fifo works, not leading to overflow
    for (int i = FIFO_SIZE * 2; i >= 1; i--) {
        // rolling over once by adding a k*FIFO_Size items
        Event event1 = {.term = Narsese_AtomicTerm("test"),
                .type = EVENT_TYPE_BELIEF,
                .truth = {.frequency = 1.0, .confidence = 0.9},
                .stamp = {.evidentialBase = {i}},
                .occurrenceTime = FIFO_SIZE * 2 - i * 10};
        FIFO_Add(&event1, &fifo);
    }
    for (int i = 0; i < FIFO_SIZE; i++) {
        TEST_ASSERT_TRUE_MESSAGE(FIFO_SIZE - i == fifo.array[0][i].stamp.evidentialBase[0],
                                 "Item at FIFO position has to be right");
    }
    //now see whether a new item is revised with the correct one:
    int i = 3; //revise with item 10, which has occurrence time 10
    int newbase = FIFO_SIZE * 2 + 1;
    Event event2 = {.term = Narsese_AtomicTerm("test"),
            .type = EVENT_TYPE_BELIEF,
            .truth = {.frequency = 1.0, .confidence = 0.9},
            .stamp = {.evidentialBase = {newbase}},
            .occurrenceTime = i * 10 + 3};
    FIFO fifo2 = {0};
    for (int i = 0; i < FIFO_SIZE * 2; i++) {
        Term zero = (Term) {0};
        FIFO_Add(&event2, &fifo2);
        if (i < FIFO_SIZE && i < MAX_SEQUENCE_LEN) {
            char buf[100];
            Event *ev = FIFO_GetKthNewestSequence(&fifo2, 0, i);
            sprintf(buf, "This event Term is not allowed to be zero, sequence length=%d\n", i + 1);
            TEST_ASSERT_TRUE_MESSAGE(!Term_Equal(&zero, &ev->term), buf);
        }
    }
    TEST_ASSERT_TRUE_MESSAGE(fifo2.itemsAmount == FIFO_SIZE, "FIFO size differs");
}


void test_priority_queue(void) {
    PriorityQueue queue;
    int n_items = 10;
    Item items[n_items];
    for (int i = 0; i < n_items; i++) {
        items[i].address = (void *) ((long) i + 1);
        items[i].priority = 0;
    }
    PriorityQueue_INIT(&queue, items, n_items);
    for (int i = 0, evictions = 0; i < n_items * 2; i++) {
        PriorityQueue_Push_Feedback feedback = PriorityQueue_Push(&queue, 1.0 / ((double) (n_items * 2 - i)));
        if (feedback.added) {
            TEST_ASSERT_TRUE_MESSAGE(feedback.addedItem.priority != 0, "Feedback priority should not be 0.");
            TEST_ASSERT_TRUE_MESSAGE((long) feedback.addedItem.address != 0, "Feedback address should not be 0.");
        }
        if (feedback.evicted) {
            TEST_ASSERT_TRUE_MESSAGE(evictions > 0 ||
                                     (feedback.evictedItem.priority - ((double) (1.0 / ((double) (n_items * 2))))) <
                                     0.00001, "the evicted item has to be the lowest priority one");
            TEST_ASSERT_TRUE_MESSAGE(queue.itemsAmount < n_items + 1, "eviction should only happen when full!");
            evictions++;
        }
    }
}


void test_table(void) {
    Concept sourceConcept = {0};
    Table table = {0};
    for (int i = TABLE_SIZE * 2; i >= 1; i--) {
        Implication imp = {.term = Narsese_AtomicTerm("test"),
                .truth = {.frequency = 1.0, .confidence = 1.0 / ((double) (i + 1))},
                .stamp = {.evidentialBase = {i}},
                .occurrenceTimeOffset = 10,
                .sourceConcept = &sourceConcept};
        Table_Add(&table, &imp);
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        TEST_ASSERT_TRUE_MESSAGE(i + 1 == table.array[i].stamp.evidentialBase[0],
                                 "Item at table position has to be right");
    }
    Implication imp = {.term = Narsese_AtomicTerm("test"),
            .truth = {.frequency = 1.0, .confidence = 0.9},
            .stamp = {.evidentialBase = {TABLE_SIZE * 2 + 1}},
            .occurrenceTimeOffset = 10,
            .sourceConcept = &sourceConcept};
    TEST_ASSERT_TRUE_MESSAGE(table.array[0].truth.confidence == 0.5, "The highest confidence one should be the first.");
    Table_AddAndRevise(&table, &imp);
    TEST_ASSERT_TRUE_MESSAGE(table.array[0].truth.confidence > 0.5,
                             "The revision result should be more confident than the table element that existed.");
}

void test_memory(void) {
    Event e = Event_InputEvent(Narsese_AtomicTerm("a"),
                               EVENT_TYPE_BELIEF,
                               (Truth) {.frequency = 1, .confidence = 0.9},
                               1337);
    Memory_AddInputEvent(&e, 0, 0);
    //identify
    TEST_ASSERT_TRUE_MESSAGE(belief_events.array[0][0].truth.confidence == (double) 0.9, "event has to be there");
    Memory_Conceptualize(&e.term, 1);
    Concept *c1 = Memory_FindConceptByTerm(&e.term);
    TEST_ASSERT_TRUE_MESSAGE(c1 != NULL, "Concept should have been created!");
    Event e2 = Event_InputEvent(Narsese_AtomicTerm("b"),
                                EVENT_TYPE_BELIEF,
                                (Truth) {.frequency = 1, .confidence = 0.9},
                                1337);
    Memory_AddInputEvent(&e2, 0, 0);
    Memory_Conceptualize(&e2.term, 1);
    Concept *c2 = Memory_FindConceptByTerm(&e2.term);
    TEST_ASSERT_TRUE_MESSAGE(c2 != NULL, "Concept should have been created!");
}


void test_inverted_atom_index(void) {
    Term term = Narsese_Term("<a --> (b & c)>");
    Concept c = {.term = term};
    InvertedAtomIndex_AddConcept(term, &c);
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("a")]->c == &c,
                             "There was no concept reference added for key a!");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("b")]->c == &c,
                             "There was no concept reference added for key b!");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("c")]->c == &c,
                             "There was no concept reference added for key c!");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex(":")] == NULL,
                             "There was a concept reference added for key inheritance!");
    InvertedAtomIndex_RemoveConcept(term, &c);
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("a")] == NULL,
                             "Concept reference was not removed for key a!");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("b")] == NULL,
                             "Concept reference was not removed for key b!");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("c")] == NULL,
                             "Concept reference was not removed for key c!");
    InvertedAtomIndex_AddConcept(term, &c);
    Term term2 = Narsese_Term("<b --> d>");
    Concept c2 = {.term = term2};
    InvertedAtomIndex_AddConcept(term2, &c2);
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("a")]->c == &c,
                             "There was no concept reference added for key a! (2)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("b")]->c == &c,
                             "There was no concept reference added for key b! (2)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("c")]->c == &c,
                             "There was no concept reference added for key c! (2)");
    TEST_ASSERT_TRUE_MESSAGE(((ConceptChainElement *) invertedAtomIndex[Narsese_AtomicTermIndex("b")]->next)->c == &c2,
                             "There was no concept2 reference added for key b! (2)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("d")]->c == &c2,
                             "There was no concept2 reference added for key d! (2)");
    InvertedAtomIndex_RemoveConcept(term, &c);
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("b")]->c == &c2,
                             "There was no concept2 reference remaining for key b! (3)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("d")]->c == &c2,
                             "There was no concept2 reference remaining for key d! (3)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("a")] == NULL,
                             "Concept reference was not removed for key a! (3)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("c")] == NULL,
                             "Concept reference was not removed for key c! (3)");
    InvertedAtomIndex_RemoveConcept(term2, &c2);
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("a")] == NULL,
                             "Concept reference was not removed for key a! (4)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("b")] == NULL,
                             "Concept reference was not removed for key b! (4)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("c")] == NULL,
                             "Concept reference was not removed for key c! (4)");
    TEST_ASSERT_TRUE_MESSAGE(invertedAtomIndex[Narsese_AtomicTermIndex("d")] == NULL,
                             "Concept reference was not removed for key d! (4)");
}

void test_narsese(void) {
    char *narsese = "<<$sth --> (&,[furry,meowing],animal)> =/> <$sth --> [good]>>";
    printf("Narsese: %s\n", narsese);
    char *preprocessed = Narsese_Expand(narsese);
    char *expanded = "(  ( $sth :  ( &  ( ' furry meowing )  animal )  )  $  ( $sth :  ( ' good )  )  )";
    TEST_ASSERT_TRUE_MESSAGE(strcmp(preprocessed, expanded),
                             "Expanded string is incorrect");
    char **tokens = Narsese_PrefixTransform(preprocessed);
    int k = 0;
    for (; tokens[k] != NULL; k++) {
        // NO-OP
    }
    TEST_ASSERT_TRUE_MESSAGE(k == 24, "Prefix transform string is incorrect size.");
    Term ret = Narsese_Term(narsese);
    // first letters of 'meowing' and 'animal' :)
    TEST_ASSERT_TRUE_MESSAGE(Narsese_atomNames[59][0] == 'm', "Atomic term is incorrect.");
    TEST_ASSERT_TRUE_MESSAGE(Narsese_atomNames[60][0] == 'a', "Atomic term is incorrect.");
}

void test_ruletable(void) {
    NAR_AddInput(Narsese_Term(
            "<cat --> animal>"), EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH,
                 true, 0, false);
    NAR_AddInput(Narsese_Term(
            "<animal --> being>"), EVENT_TYPE_BELIEF, NAR_DEFAULT_TRUTH,
                 true, 0, false);
    NAR_Cycles(1);
    TEST_ASSERT_TRUE_MESSAGE(currentTime != 0, "NAR cycle time should not be zero.");
}

void test_stack(void) {
    Stack stack = {0};
    VMItem *storageptrs[CONCEPTS_MAX];
    Stack_INIT(&stack, (void **) storageptrs, CONCEPTS_MAX);
    Concept c1 = {0};
    Concept c2 = {0};
    VMItem item1 = {.value = &c1};
    VMItem item2 = {.value = &c2};
    Stack_Push(&stack, &item1);
    TEST_ASSERT_TRUE_MESSAGE(stack.stackpointer == 1, "Stackpointer wasn't incremented");
    TEST_ASSERT_TRUE_MESSAGE(((VMItem **) stack.items)[0]->value == &c1, "Item should point to c1");
    TEST_ASSERT_TRUE_MESSAGE(!Stack_IsEmpty(&stack), "Stack should not be empty");
    VMItem *item1_popped = Stack_Pop(&stack);
    TEST_ASSERT_TRUE_MESSAGE(stack.stackpointer == 0, "Stackpointer wasn't decremented");
    TEST_ASSERT_TRUE_MESSAGE(item1_popped->value == &c1, "Popped item1 should point to c1 (1)");
    Stack_Push(&stack, &item1);
    Stack_Push(&stack, &item2);
    TEST_ASSERT_TRUE_MESSAGE(stack.stackpointer == 2, "Stackpointer wrong");
    VMItem *item2_popped = Stack_Pop(&stack);
    TEST_ASSERT_TRUE_MESSAGE(item2_popped->value == &c2, "Popped item2 should point to c2");
    VMItem *item1_popped_again = Stack_Pop(&stack);
    TEST_ASSERT_TRUE_MESSAGE(item1_popped_again->value == &c1, "Popped item1 should point to c1 (2)");
    TEST_ASSERT_TRUE_MESSAGE(Stack_IsEmpty(&stack), "Stack should be empty");
}

void test_hashtable() {
    HashTable HTtest;
    VMItem *HTest_storageptrs[CONCEPTS_MAX];
    VMItem HTest_storage[CONCEPTS_MAX];
    VMItem *HTest_HT[CONCEPTS_HASHTABLE_BUCKETS]; //the hash of the concept term is the index
    HashTable_INIT(&HTtest, HTest_storage, HTest_storageptrs, HTest_HT, CONCEPTS_HASHTABLE_BUCKETS, CONCEPTS_MAX,
                   (Equal) Term_Equal, (Hash) Term_Hash);
    TEST_ASSERT_TRUE_MESSAGE(HTtest.VMStack.stackpointer == CONCEPTS_MAX, "The stack should be full!");
    //Insert a first concept:
    Term term1 = Narsese_Term("<a --> b>");
    Concept c1 = {.id = 1, .term = term1};
    HashTable_Set(&HTtest, &term1, &c1);
    TEST_ASSERT_TRUE_MESSAGE(HTtest.VMStack.stackpointer == CONCEPTS_MAX - 1,
                             "One item should be taken off of the stack");
    TEST_ASSERT_TRUE_MESSAGE(HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS] != NULL,
                             "Item didn't go in right place");
    //Return it
    Concept *c1_returned = HashTable_Get(&HTtest, &term1);
    TEST_ASSERT_TRUE_MESSAGE(c1_returned != NULL, "Returned item is null (1)");
    TEST_ASSERT_TRUE_MESSAGE(Term_Equal(&c1.term, &c1_returned->term),
                             "Hashtable Get led to different term than we put into (1)");
    //insert another with the same hash:
    Term term2 = Narsese_Term("<c --> d>");
    term2.hash = c1.term.hash;
    Concept c2 = {.id = 2, .term = term2}; //use different term but same hash, hash collision!
    HashTable_Set(&HTtest, &term2, &c2);
    //get first one:
    Concept *c1_returned_again = HashTable_Get(&HTtest, &term1);
    TEST_ASSERT_TRUE_MESSAGE(c1_returned_again != NULL, "Returned item is null (2)");
    TEST_ASSERT_TRUE_MESSAGE(Term_Equal(&c1.term, &c1_returned_again->term),
                             "Hashtable Get led to different term than we put into (2)");
    Term term3 = Narsese_Term("<e --> f>");
    term3.hash = c1.term.hash;
    Concept c3 = {.id = 3, .term = term3}; //use different term but same hash, hash collision!
    HashTable_Set(&HTtest, &term3, &c3);
    //there should be a chain of 3 concepts now at the hash position:
    TEST_ASSERT_TRUE_MESSAGE(Term_Equal(HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS]->key, &c1.term),
                             "c1 not there! (1)");
    TEST_ASSERT_TRUE_MESSAGE(
            Term_Equal(((VMItem *) HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS]->next)->key, &c2.term),
            "c2 not there! (1)");
    TEST_ASSERT_TRUE_MESSAGE(
            Term_Equal(((VMItem *) ((VMItem *) HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS]->next)->next)->key,
                       &c3.term), "c3 not there! (1)");
    //Delete the middle one, c2
    HashTable_Delete(&HTtest, &term2);
    TEST_ASSERT_TRUE_MESSAGE(
            ((Concept *) ((VMItem *) HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS]->next)->value)->id == 3,
            "c3 not there according to id! (2)");
    TEST_ASSERT_TRUE_MESSAGE(Term_Equal(HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS]->key, &c1.term),
                             "c1 not there! (2)");
    TEST_ASSERT_TRUE_MESSAGE(
            Term_Equal(((VMItem *) HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS]->next)->key, &c3.term),
            "c3 not there! (2)");
    //Delete the last one, c3
    HashTable_Delete(&HTtest, &term3);
    TEST_ASSERT_TRUE_MESSAGE(Term_Equal(HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS]->key, &c1.term),
                             "c1 not there! (3)");
    //Delete the first one, which is the last one left, c1
    HashTable_Delete(&HTtest, &term1);
    TEST_ASSERT_TRUE_MESSAGE(HTtest.HT[c1.term.hash % CONCEPTS_HASHTABLE_BUCKETS] == NULL,
                             "Hash table at hash position must be null");
    TEST_ASSERT_TRUE_MESSAGE(HTtest.VMStack.stackpointer == CONCEPTS_MAX, "All elements should be free now");
    //test for chars:
    HashTable HTtest2;
    VMItem *HTtest2_storageptrs[ATOMS_MAX];
    VMItem HTtest2_storage[ATOMS_MAX];
    VMItem *HTtest2_HT[ATOMS_HASHTABLE_BUCKETS];
    HashTable_INIT(&HTtest2, HTtest2_storage, HTtest2_storageptrs, HTtest2_HT, ATOMS_HASHTABLE_BUCKETS, ATOMS_MAX,
                   (Equal) Narsese_StringEqual, (Hash) Narsese_StringHash);
    char *testname = "test";
    char blockname[ATOMIC_TERM_LEN_MAX] = {0};
    strncpy(blockname, testname, ATOMIC_TERM_LEN_MAX - 1);
    HashTable_Set(&HTtest2, blockname, (void *) 42);
    long res = (long) HashTable_Get(&HTtest2, blockname);
    TEST_ASSERT_TRUE_MESSAGE(res == 42, "Result is not right!");
}

// multiple step tests
bool NAR_Lightswitch_GotoSwitch_executed = false;
bool NAR_Lightswitch_ActivateSwitch_executed = false;

void NAR_Lightswitch_GotoSwitch() {
    NAR_Lightswitch_GotoSwitch_executed = true;
    puts("NAR invoked goto switch");
}

void NAR_Lightswitch_ActivateSwitch() {
    NAR_Lightswitch_ActivateSwitch_executed = true;
    puts("NAR invoked activate switch");
}

void test_multiple_steps() {
    MOTOR_BABBLING_CHANCE = 0;
    NAR_INIT();
    NAR_AddOperation(Narsese_AtomicTerm("^goto_switch"), NAR_Lightswitch_GotoSwitch);
    NAR_AddOperation(Narsese_AtomicTerm("^activate_switch"), NAR_Lightswitch_ActivateSwitch);
    for (int i = 0; i < 5; i++) {
        NAR_AddInputBelief(Narsese_AtomicTerm("start_at"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^goto_switch"));
        NAR_Cycles(1);
        NAR_AddInputBelief(Narsese_AtomicTerm("switch_at"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^activate_switch"));
        NAR_AddInputBelief(Narsese_AtomicTerm("switch_active"));
        NAR_Cycles(1);
        NAR_AddInputBelief(Narsese_AtomicTerm("light_active"));
        NAR_Cycles(10);
    }
    NAR_Cycles(10);
    NAR_AddInputBelief(Narsese_AtomicTerm("start_at"));
    NAR_AddInputGoal(Narsese_AtomicTerm("light_active"));
    NAR_Cycles(10);
    TEST_ASSERT_TRUE_MESSAGE(NAR_Lightswitch_GotoSwitch_executed && !NAR_Lightswitch_ActivateSwitch_executed,
                             "NAR needs to go to the switch first");
    NAR_Lightswitch_GotoSwitch_executed = false;
    NAR_AddInputBelief(Narsese_AtomicTerm("switch_at"));
    NAR_AddInputGoal(Narsese_AtomicTerm("light_active"));
    TEST_ASSERT_TRUE_MESSAGE(!NAR_Lightswitch_GotoSwitch_executed && NAR_Lightswitch_ActivateSwitch_executed,
                             "NAR needs to activate the switch");
}

void test_multiple_steps2() {
    NAR_Lightswitch_ActivateSwitch_executed = false;
    MOTOR_BABBLING_CHANCE = 0;
    NAR_INIT();
    NAR_AddOperation(Narsese_AtomicTerm("^goto_switch"), NAR_Lightswitch_GotoSwitch);
    NAR_AddOperation(Narsese_AtomicTerm("^activate_switch"), NAR_Lightswitch_ActivateSwitch);
    for (int i = 0; i < 5; i++) {
        NAR_AddInputBelief(Narsese_AtomicTerm("start_at"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^goto_switch"));
        NAR_Cycles(1);
        NAR_AddInputBelief(Narsese_AtomicTerm("switch_at"));
        NAR_Cycles(10);
    }
    NAR_Cycles(1000);
    for (int i = 0; i < 5; i++) {
        NAR_AddInputBelief(Narsese_AtomicTerm("switch_at"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^activate_switch"));
        NAR_AddInputBelief(Narsese_AtomicTerm("switch_active"));
        NAR_Cycles(1);
        NAR_AddInputBelief(Narsese_AtomicTerm("light_active"));
        NAR_Cycles(10);
    }
    NAR_Cycles(10);
    NAR_AddInputBelief(Narsese_AtomicTerm("start_at"));
    NAR_AddInputGoal(Narsese_AtomicTerm("light_active"));
    NAR_Cycles(10);
    TEST_ASSERT_TRUE_MESSAGE(NAR_Lightswitch_GotoSwitch_executed && !NAR_Lightswitch_ActivateSwitch_executed,
                             "NAR needs to go to the switch first (2)");
    NAR_Lightswitch_GotoSwitch_executed = false;
    NAR_AddInputBelief(Narsese_AtomicTerm("switch_at"));
    NAR_AddInputGoal(Narsese_AtomicTerm("light_active"));
    TEST_ASSERT_TRUE_MESSAGE(!NAR_Lightswitch_GotoSwitch_executed && NAR_Lightswitch_ActivateSwitch_executed,
                             "NAR needs to activate the switch (2)");
}

// test running a procedure
bool NAR_Procedure_Test_Op_executed = false;

void NAR_Procedure_Test_Op() {
    puts("op executed by NAR");
    NAR_Procedure_Test_Op_executed = true;
}

void test_operation_execution() {
    NAR_INIT();
    NAR_AddOperation(Narsese_AtomicTerm("^op"), NAR_Procedure_Test_Op);
    NAR_AddInputBelief(Narsese_AtomicTerm("a"));
    NAR_Cycles(1);
    NAR_AddInputBelief(Narsese_AtomicTerm("^op"));
    NAR_Cycles(1);
    NAR_AddInputBelief(Narsese_AtomicTerm("result"));
    NAR_Cycles(1);
    NAR_AddInputBelief(Narsese_AtomicTerm("a"));
    NAR_Cycles(1);
    NAR_AddInputGoal(Narsese_AtomicTerm("result"));
    NAR_Cycles(1);
    TEST_ASSERT_TRUE_MESSAGE(NAR_Procedure_Test_Op_executed, "NAR should have executed op!");
}

// sequence test
bool op_1_executed = false;
bool op_2_executed = false;
bool op_3_executed = false;

void op_1() {
    op_1_executed = true;
}

void op_2() {
    op_2_executed = true;
}

void op_3() {
    op_3_executed = true;
}

void test_sequences() {
    NAR_INIT();
    MOTOR_BABBLING_CHANCE = 0;
    NAR_AddOperation(Narsese_AtomicTerm("^1"), op_1);
    NAR_AddOperation(Narsese_AtomicTerm("^2"), op_2);
    NAR_AddOperation(Narsese_AtomicTerm("^3"), op_3);
    for (int i = 0; i < 5; i++) {
        NAR_AddInputBelief(Narsese_AtomicTerm("a")); //0 2 4 5
        NAR_AddInputBelief(Narsese_AtomicTerm("b"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^1"));
        NAR_AddInputBelief(Narsese_AtomicTerm("g"));
        NAR_Cycles(100);
    }
    for (int i = 0; i < 100; i++) {
        NAR_AddInputBelief(Narsese_AtomicTerm("a"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^1"));
        NAR_Cycles(100);
    }
    for (int i = 0; i < 100; i++) {
        NAR_AddInputBelief(Narsese_AtomicTerm("b"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^1"));
        NAR_Cycles(100);
    }
    for (int i = 0; i < 2; i++) {
        NAR_AddInputBelief(Narsese_AtomicTerm("b"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^2"));
        NAR_AddInputBelief(Narsese_AtomicTerm("g"));
        NAR_Cycles(100);
    }
    for (int i = 0; i < 2; i++) {
        NAR_AddInputBelief(Narsese_AtomicTerm("a"));
        NAR_AddInputBelief(Narsese_AtomicTerm("^3"));
        NAR_AddInputBelief(Narsese_AtomicTerm("g"));
        NAR_Cycles(100);
    }
    NAR_AddInputBelief(Narsese_AtomicTerm("a"));
    NAR_AddInputBelief(Narsese_AtomicTerm("b"));
    NAR_AddInputGoal(Narsese_AtomicTerm("g"));
    assert(op_1_executed && !op_2_executed && !op_3_executed, "Expected op1 execution");
    op_1_executed = op_2_executed = op_3_executed = false;
    NAR_Cycles(100);
    NAR_AddInputBelief(Narsese_AtomicTerm("b"));
    NAR_AddInputGoal(Narsese_AtomicTerm("g"));
    TEST_ASSERT_TRUE_MESSAGE(!op_1_executed && op_2_executed && !op_3_executed, "Expected op2 execution"); //b here
    op_1_executed = op_2_executed = op_3_executed = false;
    NAR_Cycles(100);
    NAR_AddInputBelief(Narsese_AtomicTerm("a"));
    NAR_AddInputGoal(Narsese_AtomicTerm("g"));
    TEST_ASSERT_TRUE_MESSAGE(!op_1_executed && !op_2_executed && op_3_executed, "Expected op3 execution"); //a here
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stamp);
    RUN_TEST(test_fifo);
    RUN_TEST(test_priority_queue);
    RUN_TEST(test_table);
    RUN_TEST(test_memory);
    RUN_TEST(test_inverted_atom_index);
    RUN_TEST(test_narsese);
    RUN_TEST(test_ruletable);
    RUN_TEST(test_stack);
    RUN_TEST(test_hashtable);

    // these are system tests
    RUN_TEST(test_multiple_steps);
    RUN_TEST(test_multiple_steps2);
    RUN_TEST(test_operation_execution);
    RUN_TEST(test_sequences);
    return UNITY_END();
}
