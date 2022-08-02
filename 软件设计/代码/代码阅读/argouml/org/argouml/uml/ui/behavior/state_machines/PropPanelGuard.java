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



// File: PropPanelState.java
// Classes: PropPanelState
// Original Author: your email address here
// $Id: PropPanelGuard.java,v 1.5 2001/04/05 09:22:43 5heyden Exp $

package org.argouml.uml.ui.behavior.state_machines;

import java.awt.*;
import java.util.*;

import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.behavior.state_machines.*;
import ru.novosoft.uml.foundation.data_types.*;

import org.argouml.uml.ui.*;
import org.argouml.uml.ui.foundation.core.PropPanelModelElement;

public class PropPanelGuard extends PropPanelModelElement {

    ////////////////////////////////////////////////////////////////
    // contructors
    public PropPanelGuard() {
        super("Guard", _guardIcon, 2);

        Class mclass = MGuard.class;

	addCaption("Name:",1,0,0);
        addField(nameField,1,0,0);

        UMLExpressionModel expressionModel = new UMLExpressionModel(this,MGuard.class,"expression",
		    MBooleanExpression.class,"getExpression","setExpression");

        addCaption("Expression:",2,0,0);
        addField(new JScrollPane(new UMLExpressionBodyField(expressionModel,true),JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER),2,0,0);

        addCaption("Language:",3,0,0);
        addField(new UMLExpressionLanguageField(expressionModel,true),3,0,0);

        addCaption("Transition:",4,0,1);
	UMLModelElementListModel transitionModel=new UMLReflectionListModel(this,"transition",false,"getTransition",null,null,null);
	transitionModel.setUpperBound(1);
        JList transitionList = new UMLList(transitionModel,true);
	transitionList.setForeground(Color.blue);
	transitionList.setVisibleRowCount(1);
	transitionList.setFont(smallFont);
        addLinkField(new JScrollPane(transitionList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER),4,0,0);

	new PropPanelButton(this,buttonPanel,_navUpIcon,localize("Go up"),"navigateUp",null);
	new PropPanelButton(this,buttonPanel,_navBackIcon,localize("Go back"),"navigateBackAction","isNavigateBackEnabled");
	new PropPanelButton(this,buttonPanel,_navForwardIcon,localize("Go forward"),"navigateForwardAction","isNavigateForwardEnabled");
	//new PropPanelButton(this,buttonPanel,_deleteIcon,localize("Delete"),"removeElement",null);

  }

    public MTransition getTransition() {
        MTransition transition = null;
        Object target = getTarget();
        if(target instanceof MGuard) {
            transition = ((MGuard) target).getTransition();
        }
        return transition;
    }

    protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("Guard");
    }

} /* end class PropPanelState */



