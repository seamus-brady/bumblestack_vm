/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
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

#include "nars_inference.h"
#include "nars_term.h"

#define DERIVATION_STAMP(a, b) Stamp conclusionStamp = stamp_make(&a->stamp, &b->stamp); \
                              long creationTime = MAX(a->creationTime, b->creationTime);
#define DERIVATION_STAMP_AND_TIME(a, b) DERIVATION_STAMP(a,b) \
                long conclusionTime = b->occurrenceTime; \
                Truth truthA = truth_projection(a->truth, a->occurrenceTime, conclusionTime); \
                Truth truthB = b->truth;

static double
weighted_average(double a1, double a2, double w1, double w2)
{
	return (a1 * w1 + a2 * w2) / (w1 + w2);
}

//{Event a., Event b.} |- Event (&/,a,b).
Event
inference_belief_intersection(Event *a, Event *b, bool *success)
{
	ASSERT(b->occurrenceTime >= a->occurrenceTime, "after(b,a) violated in inference_belief_intersection");
	DERIVATION_STAMP_AND_TIME(a, b)
	Term conclusionTerm = narsese_sequence(&a->term, &b->term, success);
	return *success ? (Event) {.term = conclusionTerm,
		.type = EVENT_TYPE_BELIEF,
		.truth = truth_intersection(truthA, truthB),
		.stamp = conclusionStamp,
		.occurrenceTime = conclusionTime,
		.creationTime = creationTime}
	                : (Event) {0};
}

//{Event a., Event b., after(b,a)} |- Implication <a =/> b>.
Implication
inference_belief_induction(Event *a, Event *b, bool *success)
{
	ASSERT(b->occurrenceTime > a->occurrenceTime, "after(b,a) violated in inference_belief_induction");
	DERIVATION_STAMP_AND_TIME(a, b)
	Term term = {0};
	term.atoms[0] = narsese_atomic_term_index("$");
	*success = term_override_subterm(&term, 1, &a->term) && term_override_subterm(&term, 2, &b->term);
	return *success ? (Implication) {.term = term,
		.truth = truth_eternalise(truth_induction(truthB, truthA)),
		.stamp = conclusionStamp,
		.occurrenceTimeOffset = b->occurrenceTime - a->occurrenceTime,
		.creationTime = creationTime}
	                : (Implication) {0};
}

//{Event a., Event a.} |- Event a.
//{Event a!, Event a!} |- Event a!
static Event
inference_event_revision(Event *a, Event *b)
{
	DERIVATION_STAMP_AND_TIME(a, b)
	return (Event) {.term = a->term,
		.type = a->type,
		.truth = truth_revision(truthA, truthB),
		.stamp = conclusionStamp,
		.occurrenceTime = conclusionTime,
		.creationTime = creationTime};
}

//{Implication <a =/> b>., <a =/> b>.} |- Implication <a =/> b>.
Implication
inference_implication_revision(Implication *a, Implication *b)
{
	DERIVATION_STAMP(a, b)
	double occurrenceTimeOffsetAvg = weighted_average(a->occurrenceTimeOffset, b->occurrenceTimeOffset,
	                                                  truth_c2w(a->truth.confidence), truth_c2w(b->truth.confidence));
	return (Implication) {.term = a->term,
		.truth = truth_revision(a->truth, b->truth),
		.stamp = conclusionStamp,
		.occurrenceTimeOffset = occurrenceTimeOffsetAvg,
		.sourceConcept = a->sourceConcept,
		.sourceConceptId = a->sourceConceptId,
		.creationTime = creationTime,
		.isUserKnowledge = a->isUserKnowledge || b->isUserKnowledge};
}

//{Event b!, Implication <a =/> b>.} |- Event a!
Event
inference_goal_deduction(Event *component, Implication *compound)
{
	ASSERT(narsese_copula_equals(compound->term.atoms[0], '$'), "Not a valid implication term!");
	DERIVATION_STAMP(component, compound)
	Term precondition = term_extract_subterm(&compound->term, 1);
	//extract precondition: (plus unification once vars are there)
	return (Event) {.term = narsese_get_precondition_without_op(&precondition),
		.type = EVENT_TYPE_GOAL,
		.truth = truth_deduction(compound->truth, component->truth),
		.stamp = conclusionStamp,
		.occurrenceTime = component->occurrenceTime - compound->occurrenceTimeOffset,
		.creationTime = creationTime};
}

//{Event a.} |- Event a. updated to g_currentTime
Event
inference_event_update(Event *ev, long currentTime)
{
	Event ret = *ev;
	ret.truth = truth_projection(ret.truth, ret.occurrenceTime, currentTime);
	ret.occurrenceTime = currentTime;
	return ret;
}

//{Event (&/,a,b)!, Event a.} |- Event b! truth_deduction
Event
Inference_GoalSequenceDeduction(Event *compound, Event *component, long currentTime)
{
	DERIVATION_STAMP(component, compound)
	Event compoundUpdated = inference_event_update(compound, currentTime);
	Event componentUpdated = inference_event_update(component, currentTime);
	return (Event) {.term = compound->term,
		.type = EVENT_TYPE_GOAL,
		.truth = truth_deduction(compoundUpdated.truth, componentUpdated.truth),
		.stamp = conclusionStamp,
		.occurrenceTime = currentTime,
		.creationTime = creationTime};
}

//{Event a!, Event a!} |- Event a! (revision and choice)
Event
inference_revision_and_choice(Event *existing_potential, Event *incoming_spike, long currentTime, bool *revised)
{
	if (revised != NULL)
	{
		*revised = false;
	}
	if (existing_potential->type == EVENT_TYPE_DELETED)
	{
		return *incoming_spike;
	}
	else
	{
		double confExisting = inference_event_update(existing_potential, currentTime).truth.confidence;
		double confIncoming = inference_event_update(incoming_spike, currentTime).truth.confidence;
		//check if there is evidental overlap
		bool overlap = stamp_check_overlap(&incoming_spike->stamp, &existing_potential->stamp);
		//if there is or the terms aren't equal, apply choice, keeping the stronger one:
		if (overlap || (existing_potential->occurrenceTime != OCCURRENCE_ETERNAL &&
			existing_potential->occurrenceTime != incoming_spike->occurrenceTime) ||
			!term_equal(&existing_potential->term, &incoming_spike->term))
		{
			if (confIncoming > confExisting)
			{
				return *incoming_spike;
			}
		}
		else
			//and else revise, increasing the "activation potential"
		{
			Event revised_spike = inference_event_revision(existing_potential, incoming_spike);
			if (revised_spike.truth.confidence >= existing_potential->truth.confidence)
			{
				if (revised != NULL)
				{
					*revised = true;
				}
				return revised_spike;
			}
			//lower, also use choice
			if (confIncoming > confExisting)
			{
				return *incoming_spike;
			}
		}
	}
	return *existing_potential;
}

//{Event a., Implication <a =/> b>.} |- Event b.
Event
inference_belief_deduction(Event *component, Implication *compound)
{
	ASSERT(narsese_copula_equals(compound->term.atoms[0], '$'), "Not a valid implication term!");
	DERIVATION_STAMP(component, compound)
	Term postcondition = term_extract_subterm(&compound->term, 2);
	return (Event) {.term = postcondition,
		.type = EVENT_TYPE_BELIEF,
		.truth = truth_deduction(compound->truth, component->truth),
		.stamp = conclusionStamp,
		.occurrenceTime = component->occurrenceTime == OCCURRENCE_ETERNAL ?
		                  OCCURRENCE_ETERNAL : component->occurrenceTime + compound->occurrenceTimeOffset,
		.creationTime = creationTime};
}
