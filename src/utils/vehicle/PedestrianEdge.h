/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    PedestrianEdge.h
/// @author  Jakob Erdmann
/// @author  Michael Behrisch
/// @author  Robert Hilbrich
/// @date    Mon, 03 March 2014
/// @version $Id: PedestrianEdge.h v0_32_0+0134-9f1b8d0bad oss@behrisch.de 2018-01-04 21:53:06 +0100 $
///
// The pedestrian accessible edges for the Intermodal Router
/****************************************************************************/
#ifndef PedestrianEdge_h
#define PedestrianEdge_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#define TL_RED_PENALTY 20

//#define IntermodalRouter_DEBUG_EFFORTS


// ===========================================================================
// class definitions
// ===========================================================================
/// @brief the pedestrian edge type that is given to the internal router (SUMOAbstractRouter)
template<class E, class L, class N, class V>
class PedestrianEdge : public IntermodalEdge<E, L, N, V> {
public:
    PedestrianEdge(int numericalID, const E* edge, const L* lane, bool forward, const double pos = -1.) :
        IntermodalEdge<E, L, N, V>(edge->getID() + (edge->isWalkingArea() ? "" : (forward ? "_fwd" : "_bwd")) + toString(pos), numericalID, edge, "!ped"),
        myLane(lane),
        myForward(forward),
        myStartPos(pos >= 0 ? pos : (forward ? 0. : edge->getLength())) { }

    bool includeInRoute(bool allEdges) const {
        return allEdges || (!this->getEdge()->isCrossing() && !this->getEdge()->isWalkingArea());
    }

    bool prohibits(const IntermodalTrip<E, N, V>* const trip) const {
        if (trip->node == 0) {
            // network only includes IntermodalEdges
            return false;
        } else {
            // limit routing to the surroundings of the specified node
            return (this->getEdge()->getFromJunction() != trip->node
                    && this->getEdge()->getToJunction() != trip->node);
        }
    }

    virtual double getTravelTime(const IntermodalTrip<E, N, V>* const trip, double time) const {
        double length = this->getLength();
        if (this->getEdge() == trip->from && !myForward && trip->departPos < myStartPos) {
            length = trip->departPos - (myStartPos - this->getLength());
        }
        if (this->getEdge() == trip->to && myForward && trip->arrivalPos < myStartPos + this->getLength()) {
            length = trip->arrivalPos - myStartPos;
        }
        if (this->getEdge() == trip->from && myForward && trip->departPos > myStartPos) {
            length -= (trip->departPos - myStartPos);
        }
        if (this->getEdge() == trip->to && !myForward && trip->arrivalPos > myStartPos - this->getLength()) {
            length -= (trip->arrivalPos - (myStartPos - this->getLength()));
        }
        // ensure that 'normal' edges always have a higher weight than connector edges
        length = MAX2(length, NUMERICAL_EPS);
        double tlsDelay = 0;
        // @note pedestrian traffic lights should never have LINKSTATE_TL_REDYELLOW
        if (this->getEdge()->isCrossing() && myLane->getIncomingLinkState() == LINKSTATE_TL_RED) {
            // red traffic lights occurring later in the route may be green by the time we arrive
            tlsDelay += MAX2(double(0), TL_RED_PENALTY - (time - STEPS2TIME(trip->departTime)));
        }
#ifdef IntermodalRouter_DEBUG_EFFORTS
        std::cout << " effort for " << trip->getID() << " at " << time << " edge=" << edge->getID() << " effort=" << length / trip->speed + tlsDelay << " l=" << length << " s=" << trip->speed << " tlsDelay=" << tlsDelay << "\n";
#endif
        return length / trip->speed + tlsDelay;
    }

private:
    /// @brief  the original edge
    const L* myLane;

    /// @brief the direction of this edge
    const bool myForward;

    /// @brief the starting position for split edges
    const double myStartPos;

};


#endif

/****************************************************************************/
