/****************************************************************************/
// Eclipse SUMO, Simulation of Urban MObility; see https://eclipse.org/sumo
// Copyright (C) 2001-2018 German Aerospace Center (DLR) and others.
// This program and the accompanying materials
// are made available under the terms of the Eclipse Public License v2.0
// which accompanies this distribution, and is available at
// http://www.eclipse.org/legal/epl-v20.html
// SPDX-License-Identifier: EPL-2.0
/****************************************************************************/
/// @file    GNEDialogACChooser.h
/// @author  Pablo Alvarez Lopez
/// @date    Apr 2018
/// @version $Id$
///
// Class for the window that allows to choose a street, junction or vehicle
/****************************************************************************/

#ifndef GNEDialogACChooser_h
#define GNEDialogACChooser_h


// ===========================================================================
// included modules
// ===========================================================================

#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <string>
#include <vector>
#include <set>
#include <fx.h>
#include <utils/gui/globjects/GUIGlObject.h>


// ===========================================================================
// class declarations
// ===========================================================================

class GUIGlChildWindow;
class GUIGlObjectStorage;
class GUIGlObject;

// ===========================================================================
// class definition
// ===========================================================================
/**
 * @class GNEDialogACChooser
 * Instances of this class are windows that display the list of instances
 * from a given artifact like vehicles, edges or junctions and allow
 * one of their items
 */
class GNEDialogACChooser : public FXMainWindow {
    // FOX-declarations
    FXDECLARE(GNEDialogACChooser)

public:
    /** @brief Constructor
     * @param[in] parent The calling view
     * @param[in] icon The icon to use
     * @param[in] title The title to use
     * @param[in] glStorage The storage to retrieve ids from
     */
    GNEDialogACChooser(GUIGlChildWindow* parent, FXIcon* icon, const FXString& title,
                           const std::vector<GUIGlID>& ids,
                           GUIGlObjectStorage& glStorage);

    /// @brief Destructor
    ~GNEDialogACChooser();

    /// @brief Returns the chosen (selected) object
    GUIGlObject* getObject() const {
        return static_cast<GUIGlObject*>(mySelected);
    }

    /// @name FOX-callbacks
    /// @{

    /// @brief Callback: The selected item shall be centered within the calling view
    long onCmdCenter(FXObject*, FXSelector, void*);

    /// @brief Callback: The dialog shall be closed
    long onCmdClose(FXObject*, FXSelector, void*);

    /// @brief Callback: Something has been typed into the the field
    long onChgText(FXObject*, FXSelector, void*);

    /// @brief Callback: Selects to current item if enter is pressed
    long onCmdText(FXObject*, FXSelector, void*);

    /// @brief Callback: Selects to current item if enter is pressed
    long onListKeyPress(FXObject*, FXSelector, void*);

    /// @brief Callback: Hides unselected items if pressed
    long onCmdFilter(FXObject*, FXSelector, void*);

    /// @brief Callback: Toggle selection status of current object
    long onCmdToggleSelection(FXObject*, FXSelector, void*);
    /// @}

    /// @brief sets the focus after the window is created to work-around bug in libfox
    void show();

protected:
    /// FOX needs this
    GNEDialogACChooser() {}

private:
    /// @brief The list that holds the ids
    FXList* myList;

    /// @brief The button that triggers centering on the select object
    FXButton* myCenterButton;

    /// @brief The parent window
    GUIGlChildWindow* myParent;

    /// @brief The chosen id
    GUIGlObject* mySelected;

    /// @brief The text field
    FXTextField* myTextEntry;

    /// myList contains (void) pointers to elements of myIDs instead of the more
    //volatile pointers to GUIGlObject
    std::set<GUIGlID> myIDs;
};


#endif

/****************************************************************************/
