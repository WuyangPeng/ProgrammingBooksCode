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



// File: PropPanelTransition.java
// Classes: PropPanelTransition
// Original Author: jrobbins@ics.uci.edu
// $Id: PropPanelTransition.java,v 1.6 2001/04/05 09:22:43 5heyden Exp $

package org.argouml.uml.ui.behavior.state_machines;

import java.awt.*;
import java.util.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.behavior.state_machines.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.common_behavior.*;
import ru.novosoft.uml.MFactory;

import org.argouml.uml.ui.foundation.core.*;
import org.argouml.uml.ui.*;
import org.argouml.kernel.Project;
import org.argouml.ui.ProjectBrowser;

public class PropPanelTransition extends PropPanelModelElement {

    ////////////////////////////////////////////////////////////////
    // contructors
    public PropPanelTransition() {
        super("Transition",_transitionIcon,3);

        Class mclass = MTransition.class;

        addCaption("Name:",1,0,0);
        addField(nameField,1,0,0);

        addCaption("Stereotype:",2,0,1);
        addField(new UMLComboBoxNavigator(this,"NavStereo",stereotypeBox),2,0,0);

	addCaption("Source:",0,1,0);
        UMLModelElementListModel sourceModel = new UMLReflectionListModel(this,"source",true,"getTransitionSource",null,null,null);
        sourceModel.setUpperBound(1);
       	JList sourceList=new UMLList(sourceModel,true);
	sourceList.setForeground(Color.blue);
	sourceList.setVisibleRowCount(1);
	sourceList.setFont(smallFont);
	addLinkField(new JScrollPane(sourceList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER),0,1,0);

	addCaption("Target:",1,1,1);
        UMLModelElementListModel targetModel = new UMLReflectionListModel(this,"target",true,"getTransitionTarget",null,null,null);
        targetModel.setUpperBound(1);
	JList targetList=new UMLList(targetModel,true);
	targetList.setForeground(Color.blue);
	targetList.setVisibleRowCount(1);
	targetList.setFont(smallFont);
        addLinkField(new JScrollPane(targetList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER),1,1,0);

        addCaption("Trigger:",0,2,0);
        UMLModelElementListModel trigModel = new UMLReflectionListModel(this,"trigger",true,"getTrigger",null,"addTrigger","deleteTrigger");
	trigModel.setUpperBound(1);
        UMLList trigList=new UMLList(trigModel,true);
	trigList.setForeground(Color.blue);
	trigList.setVisibleRowCount(1);
	trigList.setFont(smallFont);
        JScrollPane trigScroll = new JScrollPane(trigList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        addLinkField(trigScroll,0,2,0);

        addCaption("Guard:",1,2,0);
        UMLModelElementListModel guardModel = new UMLReflectionListModel(this,"guard",true,"getGuard",null,"addGuard","deleteGuard");
        guardModel.setUpperBound(1);
        UMLList guardList=new UMLList(guardModel,true);
	guardList.setForeground(Color.blue);
	guardList.setVisibleRowCount(1);
	guardList.setFont(smallFont);
        JScrollPane guardScroll = new JScrollPane(guardList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        addLinkField(guardScroll,1,2,0);

        addCaption("Effect:",2,2,1);
        UMLModelElementListModel effectModel = new UMLReflectionListModel(this,"effect",true,"getEffect",null,"addEffect","deleteEffect");
        effectModel.setUpperBound(1);
        UMLList effectList=new UMLList(effectModel,true);
	effectList.setForeground(Color.blue);
	effectList.setVisibleRowCount(1);
	effectList.setFont(smallFont);
        JScrollPane effectScroll = new JScrollPane(effectList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
        addLinkField(effectScroll,2,2,0);

	new PropPanelButton(this,buttonPanel,_navUpIcon,localize("Go up"),"navigateUp",null);
	new PropPanelButton(this,buttonPanel,_navBackIcon,localize("Go back"),"navigateBackAction","isNavigateBackEnabled");
	new PropPanelButton(this,buttonPanel,_navForwardIcon,localize("Go forward"),"navigateForwardAction","isNavigateForwardEnabled");
	new PropPanelButton(this,buttonPanel,_deleteIcon,localize("Delete"),"removeElement",null);
  }

    public void navigateUp() {
        Object target = getTarget();
        if(target instanceof MTransition) {
            MTransition elem = (MTransition) target;
            MStateMachine stateMachine = elem.getStateMachine();
            if(stateMachine != null) {
                navigateTo(stateMachine);
            }
        }
    }

    public MStateMachine getStateMachine() {
        MStateMachine machine = null;
        Object target = getTarget();
        if(target instanceof MTransition) {
            machine = ((MTransition) target).getStateMachine();
        }
	if (machine==null) System.out.println("PropPanelTransition: StateMachine is null!");
        return machine;
    }


    public MStateVertex getTransitionSource() {
        MStateVertex source = null;
	Object target = getTarget();
        if(target instanceof MTransition) {
            source = ((MTransition) target).getSource();
        }
        return source;
    }

    public MStateVertex getTransitionTarget() {
        MStateVertex transitionTarget = null;
	Object target = getTarget();
        if(target instanceof MTransition) {
            transitionTarget = ((MTransition) target).getTarget();
        }
        return transitionTarget;
    }

    public MEvent getTrigger() {
        MEvent trigger = null;
        Object target = getTarget();
        if(target instanceof MTransition) {
            trigger= ((MTransition) target).getTrigger();
        }
        return trigger;
    }

   public MCallEvent addTrigger(Integer index) {
        MCallEvent trigger = null;
        Object target = getTarget();
        if(target instanceof MTransition) {
	    MTransition trans=(MTransition) target;
	    MFactory factory=trans.getFactory();
            trigger = factory.createCallEvent();
	    trigger.setName("anon");
	    //needs-more-work
	    trigger.setNamespace(ProjectBrowser.TheInstance.getProject().getModel());
            trans.setTrigger(trigger);
        }
	return trigger;
	//is done in UMLReflectionListModel navigateTo(trigger);
    }

    public void deleteTrigger(Integer index) {
        Object target = getTarget();
        if(target instanceof MTransition) {
            ((MTransition) target).setTrigger(null);
        }
    }


    public MGuard getGuard() {
	MGuard guard = null;
        Object target = getTarget();
        if(target instanceof MTransition) {
	    guard = ((MTransition)target).getGuard();
        }
        return guard;
    }

    public MGuard addGuard(Integer index) {
        MGuard guard = null;
        Object target = getTarget();
        if(target instanceof MTransition) {
            MFactory factory=((MTransition) target).getFactory();
            guard = factory.createGuard();
            guard.setName("anon");
            ((MTransition) target).setGuard(guard);
        }
        return guard;
    }

    public void deleteGuard(Integer index) {
        Object target = getTarget();
        if(target instanceof MTransition) {
            ((MTransition) target).setGuard(null);
        }
    }

    public MAction getEffect() {
        MAction effect = null;
        Object target = getTarget();
        if(target instanceof MTransition) {
            effect = ((MTransition) target).getEffect();
        }
        return effect;
    }

    public MAction addEffect(Integer index) {
        MAction effect = null;
        Object target = getTarget();
        if(target instanceof MTransition) {
            effect = new MCallActionImpl();
            effect.setName("anon");
            ((MTransition) target).setEffect(effect);
        }
        return effect;
    }

    public void deleteEffect(Integer index) {
        Object target = getTarget();
        if(target instanceof MTransition) {
            ((MTransition) target).setEffect(null);
        }
    }

    protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("Transition");
    }




} /* end class PropPanelTransition */

