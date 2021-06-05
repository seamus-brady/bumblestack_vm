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

#include "io.h"

void setupLogging() {// Enable all logging levels
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

void printConcepts(){
    slog_info("Printing concepts:");
    for (int opi = 0; opi < OPERATIONS_MAX; opi++) {
        if (operations[opi].term.atoms[0]) {
            printf("*setopname %d ", opi + 1);
            Narsese_PrintTerm(&operations[opi].term);
            puts("");
        }
    }
    for (int i = 0; i < concepts.itemsAmount; i++) {
        Concept *c = concepts.items[i].address;
        assert(c != NULL, "Concept is null");
        fputs("//", stdout);
        Narsese_PrintTerm(&c->term);
        printf(": { \"priority\": %f, \"usefulness\": %f, \"useCount\": %ld, \"lastUsed\": %ld, \"frequency\": %f, \"confidence\": %f, \"termlinks\": [",
               c->priority, concepts.items[i].priority, c->usage.useCount, c->usage.lastUsed,
               c->belief.truth.frequency, c->belief.truth.confidence);
        Term left = Term_ExtractSubterm(&c->term, 1);
        Term left_left = Term_ExtractSubterm(&left, 1);
        Term left_right = Term_ExtractSubterm(&left, 2);
        Term right = Term_ExtractSubterm(&c->term, 2);
        Term right_left = Term_ExtractSubterm(&right, 1);
        Term right_right = Term_ExtractSubterm(&right, 2);
        fputs("\"", stdout);
        Narsese_PrintTerm(&left);
        fputs("\", ", stdout);
        fputs("\"", stdout);
        Narsese_PrintTerm(&right);
        fputs("\", ", stdout);
        fputs("\"", stdout);
        Narsese_PrintTerm(&left_left);
        fputs("\", ", stdout);
        fputs("\"", stdout);
        Narsese_PrintTerm(&left_right);
        fputs("\", ", stdout);
        fputs("\"", stdout);
        Narsese_PrintTerm(&right_left);
        fputs("\", ", stdout);
        fputs("\"", stdout);
        Narsese_PrintTerm(&right_right);
        fputs("\"", stdout);
        puts("]}");
        if (c->belief.type != EVENT_TYPE_DELETED) {
            Memory_printAddedEvent(&c->belief, 1, true, false, false, false);
        }
        for (int opi = 0; opi < OPERATIONS_MAX; opi++) {
            for (int h = 0; h < c->precondition_beliefs[opi].itemsAmount; h++) {
                Implication *imp = &c->precondition_beliefs[opi].array[h];
                Memory_printAddedImplication(&imp->term, &imp->truth, imp->occurrenceTimeOffset, 1, true, false,
                                             false);
            }
        }
    }
    slog_info("Finished printing concepts.");
}

void printAtomTable(){
    invertedAtomIndexPrint();
}

void printCyclingBeliefEvents(){
    slog_info("Printing cycling belief_events:");
    for (int i = 0; i < cycling_belief_events.itemsAmount; i++) {
        Event *e = cycling_belief_events.items[i].address;
        assert(e != NULL, "Event is null");
        Narsese_PrintTerm(&e->term);
        printf(": { \"priority\": %f, \"time\": %ld } ", cycling_belief_events.items[i].priority,
               e->occurrenceTime);
        Truth_Print(&e->truth);
    }
    slog_info("Finished printing cycling belief_events.");
}

void printCyclingGoalEvents(){
    slog_info("Printing cycling goal events:");
    for (int i = 0; i < cycling_goal_events.itemsAmount; i++) {
        Event *e = cycling_goal_events.items[i].address;
        assert(e != NULL, "Event is null");
        Narsese_PrintTerm(&e->term);
        printf(": {\"priority\": %f, \"time\": %ld } ", cycling_goal_events.items[i].priority,
               e->occurrenceTime);
        Truth_Print(&e->truth);
    }
    slog_info("Finished printing cycling goal events.");
}