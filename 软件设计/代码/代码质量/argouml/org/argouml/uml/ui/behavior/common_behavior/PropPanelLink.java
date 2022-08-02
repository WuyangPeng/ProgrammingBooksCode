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



// File: PropPanelLink.java
// Classes: PropPanelLink
// Original Author: jrobbins@ics.uci.edu
// $Id: PropPanelLink.java,v 1.6 2001/07/10 11:53:21 1sturm Exp $

package org.argouml.uml.ui.behavior.common_behavior;


import java.awt.*;
import javax.swing.*;
import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import org.argouml.uml.ui.*;
import org.argouml.uml.*;
import org.argouml.uml.ui.foundation.core.*;
import ru.novosoft.uml.behavior.common_behavior.*;


public class PropPanelLink extends PropPanelModelElement {


  ////////////////////////////////////////////////////////////////
  // contructors
  public PropPanelLink() {
    
    super("Link Properties",_linkIcon, 2);

    Class mclass = MLink.class;
    addCaption("Name:",1,0,0);
    addField(new UMLTextField(this,new UMLTextProperty(mclass,"name","getName","setName")),1,0,0);


    addCaption("Stereotype:",2,0,0);
    JComboBox stereotypeBox = new UMLStereotypeComboBox(this);
    addField(stereotypeBox,2,0,0);


    addCaption("Namespace:",3,0,1);
    addLinkField(namespaceScroll,3,0,1);


    new PropPanelButton(this,buttonPanel,_navUpIcon,localize("Go up"),"navigateNamespace",null);
    new PropPanelButton(this,buttonPanel,_navBackIcon,localize("Go back"),"navigateBackAction","isNavigateBackEnabled");
    new PropPanelButton(this,buttonPanel,_navForwardIcon,localize("Go forward"),"navigateForwardAction","isNavigateForwardEnabled");
    new PropPanelButton(this,buttonPanel,_deleteIcon,localize("Delete object"),"removeElement",null);

  
  }

     public void navigateNamespace() {
        Object target = getTarget();
        if(target instanceof MModelElement) {
            MModelElement elem = (MModelElement) target;
            MNamespace ns = elem.getNamespace();
            if(ns != null) {
                navigateTo(ns);
            }
        }
    }

    protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("Link");
    }

    public void removeElement() {
	MLink target = (MLink) getTarget();        
	MModelElement newTarget = (MModelElement) target.getNamespace();
                
        MMUtil.SINGLETON.remove(target);
	if(newTarget != null) navigateTo(newTarget);
    }



} /* end class PropPanelLink */



