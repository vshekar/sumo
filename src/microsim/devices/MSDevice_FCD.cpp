/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2013-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    MSDevice_FCD.cpp
/// @author  Daniel Krajzewicz
/// @author  Michael Behrisch
/// @author  Jakob Erdmann
/// @date    11.06.2013
/// @version $Id$
///
// A device which stands as an implementation FCD and which outputs movereminder calls
/****************************************************************************/

// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <utils/common/TplConvert.h>
#include <utils/options/OptionsCont.h>
#include <utils/iodevices/OutputDevice.h>
#include <utils/vehicle/SUMOVehicle.h>
#include <microsim/MSNet.h>
#include <microsim/MSLane.h>
#include <microsim/MSEdge.h>
#include <microsim/MSVehicle.h>
#include "MSDevice_Tripinfo.h"
#include "MSDevice_FCD.h"


// ===========================================================================
// method definitions
// ===========================================================================
// ---------------------------------------------------------------------------
// static initialisation methods
// ---------------------------------------------------------------------------
void
MSDevice_FCD::insertOptions(OptionsCont& oc) {
    oc.addOptionSubTopic("FCD Device");
    insertDefaultAssignmentOptions("fcd", "FCD Device", oc);

    oc.doRegister("device.fcd.period", new Option_String("0"));
    oc.addDescription("device.fcd.period", "FCD Device", "Recording period for FCD-data");
}


void
MSDevice_FCD::buildVehicleDevices(SUMOVehicle& v, std::vector<MSDevice*>& into) {
    OptionsCont& oc = OptionsCont::getOptions();
    if (equippedByDefaultAssignmentOptions(oc, "fcd", v, oc.isSet("fcd-output"))) {
        MSDevice_FCD* device = new MSDevice_FCD(v, "fcd_" + v.getID());
        into.push_back(device);
    }
}


// ---------------------------------------------------------------------------
// MSDevice_FCD-methods
// ---------------------------------------------------------------------------
MSDevice_FCD::MSDevice_FCD(SUMOVehicle& holder, const std::string& id) :
    MSDevice(holder, id) {
}


MSDevice_FCD::~MSDevice_FCD() {
}


/****************************************************************************/

