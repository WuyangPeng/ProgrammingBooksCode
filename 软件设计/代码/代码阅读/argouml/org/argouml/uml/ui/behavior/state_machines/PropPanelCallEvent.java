// Copyright (c) 1996-99 The Regents of the University of California. All
// Rights Reserved. Permission to use, copy, modify, and distribute this
// software and its documentation without fee, and without a written
// agreement is hereby granted, provided that the above copyright notice
// and this paragraph appear in all copies.  This software program and
// documentation are copyrighted by The Regents of the University of
// California. The software program and documentation are supplied "AS
// IS", without any accompanying services from The Regents. The Regents
// does not warrant that the operation of the program will be
// uninterrupted or error-free. The end-user understands that the program
// was developed for research purposes and is advised not to rely
// exclusively on the program for any reason.  IN NO EVENT SHALL THE
// UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
// SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
// ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
// THE UNIVERSITY OF CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE. THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE SOFTWARE
// PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND THE UNIVERSITY OF
// CALIFORNIA HAS NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT,
// UPDATES, ENHANCEMENTS, OR MODIFICATIONS.



// File: PropPanelCallEvent.java
// Classes: PropPanelCallEvent
// Original Author: oliver.heyden@gentleware.de
// $Id:

package org.argouml.uml.ui.behavior.state_machines;

import java.awt.*;
import java.util.*;

import javax.swing.*;

import org.argouml.uml.ui.*;
import org.argouml.uml.ui.foundation.core.PropPanelModelElement;

import ru.novosoft.uml.behavior.state_machines.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.foundation.core.*;

public class PropPanelCallEvent extends PropPanelEvent {

    ////////////////////////////////////////////////////////////////
    // contructors
    public PropPanelCallEvent() {
        super("Call Event", null, 2);

        Class mclass = MCallEvent.class;

        addCaption("Name:",1,0,0);
        addField(nameField,1,0,0);

	addCaption("Parameters:",2,0,1);
	addField(paramScroll,2,0,1);

  }

    //needs-more-work: Operation should be selectable
    public MOperation getOperation() {
	MOperation operation=null;
        Object target = getTarget();
        if(target instanceof MCallEvent) {
            operation = ((MCallEvent) target).getOperation();
        }
        return operation;
    }

    public void setOperation(MOperation operation) {
        Object target = getTarget();
        if(target instanceof MCallEvent) {
            ((MCallEvent) target).setOperation(operation);
        }
    }

    protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("CallEvent");
    }

} /* end class PropPanelCallEvent */



