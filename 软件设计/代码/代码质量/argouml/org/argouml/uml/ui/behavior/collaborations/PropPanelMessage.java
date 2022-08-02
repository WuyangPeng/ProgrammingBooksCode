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



// File: PropPanelMessage.java
// Classes: PropPanelMessage
// Original Author: agauthie@ics.uci.edu
// $Id: PropPanelMessage.java,v 1.6 2001/07/10 11:53:21 1sturm Exp $

package org.argouml.uml.ui.behavior.collaborations;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.model_management.*;
import ru.novosoft.uml.behavior.collaborations.*;
import ru.novosoft.uml.MFactory;
import ru.novosoft.uml.behavior.common_behavior.*;

import javax.swing.*;

import org.argouml.uml.ui.*;
import org.argouml.uml.ui.foundation.core.PropPanelModelElement;

import java.awt.*;
import java.util.*;

public class PropPanelMessage extends PropPanelModelElement {

  ////////////////////////////////////////////////////////////////
  // constants


  ////////////////////////////////////////////////////////////////
  // contructors
  public PropPanelMessage() {
    super("Message",null, 2);

    Class mclass = MMessage.class;

    addCaption("Name:",1,0,0);
    addField(nameField,1,0,0);

    addCaption("Stereotype:",2,0,0);
    addField(stereotypeBox,2,0,0);

    addCaption("Namespace:",3,0,0);
    addField(namespaceScroll,3,0,0);

    addCaption("Sender:",4,0,0);
    UMLModelElementListModel senderModel=new UMLReflectionListModel(this, "sender",true,"getSender",null, null,null);
    JList senderList = new UMLList(senderModel,true);
    senderList.setForeground(Color.blue);
    senderList.setFont(smallFont);
    JScrollPane senderScroll = new JScrollPane(senderList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
    addField(senderScroll,4,0,0);

    addCaption("Receiver:",5,0,1);
    UMLModelElementListModel receiverModel=new UMLReflectionListModel(this, "receiver",true,"getReceiver",null, null,null);
    JList receiverList = new UMLList(receiverModel,true);
    receiverList.setForeground(Color.blue);
    receiverList.setFont(smallFont);
    JScrollPane receiverScroll = new JScrollPane(receiverList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
    addField(receiverScroll,5,0,0);

    addCaption("Predecessor:",0,1,0);
    UMLModelElementListModel predecessorModel=new UMLReflectionListModel(this, "predecessor",true,"getPredecessor",null, null,null);
    JList predecessorList = new UMLList(predecessorModel,true);
    predecessorList.setForeground(Color.blue);
    predecessorList.setFont(smallFont);
    JScrollPane predecessorScroll = new JScrollPane(predecessorList);
    addField(predecessorScroll,0,1,0.4);

    addCaption("Activator:",1,1,0);
    UMLModelElementListModel activatorModel=new UMLReflectionListModel(this, "activator",true,"getActivator",null, null,null);
    JList activatorList = new UMLList(activatorModel,true);
    activatorList.setForeground(Color.blue);
    activatorList.setFont(smallFont);
    JScrollPane activatorScroll = new JScrollPane(activatorList);
    addField(activatorScroll,1,1,0.4);

    addCaption("Action:",2,1,1);
    UMLModelElementListModel actionModel=new UMLReflectionListModel(this, "action",true,"getAction",null,"addAction","deleteAction");
    JList actionList = new UMLList(actionModel,true);
    actionList.setForeground(Color.blue);
    actionList.setFont(smallFont);
    JScrollPane actionScroll = new JScrollPane(actionList,JScrollPane.VERTICAL_SCROLLBAR_NEVER,JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
    addField(actionScroll,2,1,0);

    new PropPanelButton(this,buttonPanel,_navUpIcon,localize("Go up"),"navigateNamespace",null);
    new PropPanelButton(this,buttonPanel,_navBackIcon,localize("Go back"),"navigateBackAction","isNavigateBackEnabled");
    new PropPanelButton(this,buttonPanel,_navForwardIcon,localize("Go forward"),"navigateForwardAction","isNavigateForwardEnabled");
    new PropPanelButton(this,buttonPanel,_deleteIcon,localize("Delete"),"removeElement",null);
 }

    public MClassifierRole getSender() {
        MClassifierRole sender = null;
        Object target = getTarget();
        if(target instanceof MMessage) {
            sender = ((MMessage) target).getSender();
        }
        return sender;
    }

    public MClassifierRole getReceiver() {
        MClassifierRole receiver = null;
        Object target = getTarget();
        if(target instanceof MMessage) {
            receiver = ((MMessage) target).getReceiver();
        }
        return receiver;
    }
    
    public MMessage getActivator() {
        MMessage activator = null;
        Object target = getTarget();
        if(target instanceof MMessage) {
            activator = ((MMessage) target).getActivator();
        }
        return activator;
    }
    
    public java.util.List getPredecessor() {
       java.util.Collection predecessor = null;
       Object target = getTarget();
       if(target instanceof MMessage) {
	   predecessor = ((MMessage) target).getPredecessors();
       }
       return new Vector(predecessor);
    }
    
    public MAction getAction() {
        MAction action = null;
        Object target = getTarget();
        if(target instanceof MMessage) {
            action = ((MMessage) target).getAction();
        }
        return action;
    }
    
    public MCallAction addAction(Integer index) {
        MCallAction action = null;
        Object target = getTarget();
        if(target instanceof MMessage) {
            MFactory factory=((MMessage) target).getFactory();
            action = factory.createCallAction();
            action.setName("action");
            ((MMessage) target).setAction(action);
        }
        return action;
    }
    
    public void deleteAction(Integer index) {
        Object target = getTarget();
        if(target instanceof MMessage) {
            ((MMessage) target).setAction(null);
        }
    }
    
   protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("Message");
    }



} /* end class PropPanelMessage */
