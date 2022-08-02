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
// $Id: PropPanelState.java,v 1.7 2001/04/05 09:22:43 5heyden Exp $

package org.argouml.uml.ui.behavior.state_machines;

import java.awt.*;
import java.util.*;

import javax.swing.*;

import org.argouml.uml.ui.*;

import ru.novosoft.uml.MFactory;
import ru.novosoft.uml.behavior.state_machines.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.common_behavior.*;
import ru.novosoft.uml.foundation.core.*;

public abstract class PropPanelState extends PropPanelStateVertex {

    protected JScrollPane entryScroll;
    protected JScrollPane exitScroll;
    protected JScrollPane doScroll;
    protected JScrollPane internalTransitionsScroll;
    protected JList entryList;
    protected JList exitList;
    protected JList doList;
    protected JList internalTransitionsList;

    public PropPanelState(String name, int columns) {
	this(name, null, columns);
    }

    public PropPanelState(String name,ImageIcon icon, int columns) {
	super(name, icon, columns);

        UMLModelElementListModel entryModel=new UMLReflectionListModel(this, "entry",true,"getEntryAction",null, "addEntryAction","deleteEntryAction");
	entryModel.setUpperBound(1);
	entryList = new UMLList(entryModel,true);
	entryList.setForeground(Color.blue);
	entryList.setVisibleRowCount(1);
	entryList.setFont(smallFont);
        entryScroll = new JScrollPane(entryList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

	UMLModelElementListModel exitModel=new UMLReflectionListModel(this,"exit",true,"getExitAction",null,"addExitAction","deleteExitAction");
	exitModel.setUpperBound(1);
	exitList = new UMLList(exitModel,true);
	exitList.setForeground(Color.blue);
	exitList.setVisibleRowCount(1);
	exitList.setFont(smallFont);
        exitScroll = new JScrollPane(exitList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

	UMLModelElementListModel doModel=new UMLReflectionListModel(this,"doActivity",true,"getDoActivity",null,"addDoActivity","deleteExitAction");
	doModel.setUpperBound(1);
	doList = new UMLList(doModel,true);
	doList.setForeground(Color.blue);
	doList.setVisibleRowCount(1);
	doList.setFont(smallFont);
        doScroll = new JScrollPane(doList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

	UMLModelElementListModel internalTransitionsModel=new UMLReflectionListModel(this,"internalTransitions",true,"getInternalTransitions",null,"addInternalTransition",null);
	internalTransitionsList = new UMLList(internalTransitionsModel,true);
	internalTransitionsList.setForeground(Color.blue);
	internalTransitionsList.setFont(smallFont);
        internalTransitionsScroll = new JScrollPane(internalTransitionsList);

    }

     public MAction getEntryAction() {
        MAction entryAction = null;
        Object target = getTarget();
        if(target instanceof MState) {
            entryAction = ((MState) target).getEntry();
        }
        return entryAction;
     }

    public MCallAction addEntryAction(Integer index) {
        MCallAction entryAction = null;
        Object target = getTarget();
        if(target instanceof MState) {
            MFactory factory=((MState) target).getFactory();
            entryAction = factory.createCallAction();
            entryAction.setName("anon");
            ((MState) target).setEntry(entryAction);
        }
        return entryAction;
    }

    public void deleteEntryAction(Integer index) {
        Object target = getTarget();
        if(target instanceof MState) {
            ((MState) target).setEntry(null);
        }
    }

    public MAction getExitAction() {
        MAction exitAction = null;
        Object target = getTarget();
        if(target instanceof MState) {
            exitAction = ((MState) target).getExit();
        }
        return exitAction;
     }

    public MCallAction addExitAction(Integer index) {
        MCallAction exitAction = null;
        Object target = getTarget();
        if(target instanceof MState) {
            MFactory factory=((MState) target).getFactory();
            exitAction = factory.createCallAction();
            exitAction.setName("anon");
            ((MState) target).setExit(exitAction);
        }
        return exitAction;
    }

    public void deleteExitAction(Integer index) {
        Object target = getTarget();
        if(target instanceof MState) {
            ((MState) target).setExit(null);
        }
    }

    public MAction getDoActivity() {
        MAction doActivity = null;
        Object target = getTarget();
        if(target instanceof MState) {
            doActivity = ((MState) target).getDoActivity();
        }
        return doActivity;
     }

    public MCallAction addDoActivity(Integer index) {
        MCallAction doActivity = null;
        Object target = getTarget();
        if(target instanceof MState) {
            MFactory factory=((MState) target).getFactory();
            doActivity = factory.createCallAction();
            doActivity.setName("anon");
            ((MState) target).setDoActivity(doActivity);
        }
        return doActivity;
    }

    public void deleteDoActivity(Integer index) {
        Object target = getTarget();
        if(target instanceof MState) {
            ((MState) target).setDoActivity(null);
        }
    }

    public java.util.List getInternalTransitions() {
        java.util.Collection internals = null;
        Object target = getTarget();
        if(target instanceof MState) {
            internals = ((MState) target).getInternalTransitions();
        }
        return new Vector(internals);
    }

      public MTransition addInternalTransition(Integer index) {
        MTransition transition = null;
        Object target = getTarget();
        if(target instanceof MState) {
            MState state=(MState) target;
            MFactory factory=((MState) target).getFactory();
            transition = factory.createTransition();
            transition.setName("anon");
            transition.setSource(state);
            transition.setTarget(state);
            ((MState) target).addInternalTransition(transition);
        }
        return transition;
    }

       protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("State");
    }



} /* end class PropPanelState */



