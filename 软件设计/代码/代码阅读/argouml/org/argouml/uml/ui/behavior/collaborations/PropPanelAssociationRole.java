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

package org.argouml.uml.ui.behavior.collaborations;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.model_management.*;
import ru.novosoft.uml.behavior.collaborations.*;

import javax.swing.*;

import org.argouml.uml.ui.*;
import org.argouml.uml.ui.foundation.core.PropPanelModelElement;
import org.argouml.uml.MMUtil;

import java.awt.*;
import java.util.*;

public class PropPanelAssociationRole extends PropPanelModelElement {


  ////////////////////////////////////////////////////////////////
  // contructors
  public PropPanelAssociationRole() {
    super("Association Role",_associationRoleIcon, 2);

    Class mclass = MAssociationRole.class;

    addCaption("Name:",1,0,0);
    addField(nameField,1,0,0);

    addCaption("Stereotype:",2,0,0);
    addField(stereotypeBox,2,0,0);

    addCaption("Namespace:",3,0,1);
    addField(namespaceScroll,3,0,0);

    addCaption("Messages:",0,1,0);
    JList messageList = new UMLList(new UMLReflectionListModel(this,"message",true,"getMessages","setMessages",null,null),true);
    messageList.setBackground(getBackground());
    messageList.setForeground(Color.blue);
    addField(new JScrollPane(messageList),0,1,0.75);

    addCaption("AssociationRole Ends:",1,1,0);
    JList assocEndList = new UMLList(new UMLReflectionListModel(this,"connection",true,"getAssociationEnds","setAssociationEnds",null,null),true);
    assocEndList.setBackground(getBackground());
    assocEndList.setForeground(Color.blue);
    addField(new JScrollPane(assocEndList),1,1,0.25);


    new PropPanelButton(this,buttonPanel,_navUpIcon,localize("Go up"),"navigateNamespace",null);
    new PropPanelButton(this,buttonPanel,_navBackIcon,localize("Go back"),"navigateBackAction","isNavigateBackEnabled");
    new PropPanelButton(this,buttonPanel,_navForwardIcon,localize("Go forward"),"navigateForwardAction","isNavigateForwardEnabled");
    new PropPanelButton(this,buttonPanel,_deleteIcon,localize("Delete"),"removeElement",null);

  }

    public Collection getAssociationEnds() {
        Collection ends = null;
        Object target = getTarget();
        if(target instanceof MAssociationRole) {
            ends = ((MAssociationRole) target).getConnections();
        }
        return ends;
    }

    public void setAssociationEnds(Collection ends) {
        Object target = getTarget();
        if(target instanceof MAssociationRole) {
            java.util.List list = null;
            if(ends instanceof java.util.List) {
                list = (java.util.List) ends;
            }
            else {
                list = new ArrayList(ends);
            }
            ((MAssociationRole) target).setConnections(list);
        }
    }

   public Collection getMessages() {
        Collection messages = null;
        Object target = getTarget();
        if(target instanceof MAssociationRole) {
            messages = ((MAssociationRole) target).getMessages();
        }
        return messages;
    }

    public void setMessages(Collection messages) {
        Object target = getTarget();
        if(target instanceof MAssociationRole) {
            java.util.List list = null;
            if(messages instanceof java.util.List) {
                list = (java.util.List) messages;
            }
            else {
                messages = new ArrayList(messages);
            }
            ((MAssociationRole) target).setMessages(list);
        }
    }

    public Object addMessage(Integer index) {
	//needs-more-work: a fig must be generated

        Object target = getTarget();
        MMessage newMessage = null;
        if(target instanceof MAssociationRole) {
            return MMUtil.SINGLETON.buildMessage((MAssociationRole)target,"");
        }
        return newMessage;
    }

    protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("AssociationRole");
    }


} /* end class PropPanelAssociationRole */
