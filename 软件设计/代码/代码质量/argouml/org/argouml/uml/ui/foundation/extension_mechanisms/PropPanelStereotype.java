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


package org.argouml.uml.ui.foundation.extension_mechanisms;

import ru.novosoft.uml.foundation.extension_mechanisms.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.model_management.*;
import javax.swing.*;
import org.argouml.uml.ui.*;
import java.awt.*;
import java.awt.event.*;
import org.argouml.uml.ui.foundation.core.*;
import ru.novosoft.uml.foundation.core.*;

public class PropPanelStereotype extends PropPanelModelElement {

  ////////////////////////////////////////////////////////////////
  // contructors
  public PropPanelStereotype() {
    super("Stereotype", _stereotypeIcon ,2);

    Class mclass = MStereotype.class;

    addCaption("Name:",1,0,0);
    addField(nameField,1,0,0);

    addCaption("Base Class:",2,0,0);
    JComboBox baseClass = new UMLMetaclassComboBox(this,"baseClass","getBaseClass","setBaseClass");
    addField(baseClass,2,0,0);

    addCaption("Namespace:",3,0,0);
    addField(namespaceScroll,3,0,0);

    addCaption("Extends:",4,0,0);
    JList extendsList = new UMLList(new UMLGeneralizationListModel(this,"generalization",true),true);
    extendsList.setBackground(getBackground());
    extendsList.setForeground(Color.blue);
    addField(new JScrollPane(extendsList),4,0,0);

    addCaption("Modifiers:",5,0,1);
    JPanel modifiersPanel = new JPanel(new GridLayout(0,3));
    modifiersPanel.add(new UMLCheckBox(localize("abstract"),this,new UMLReflectionBooleanProperty("isAbstract",mclass,"isAbstract","setAbstract")));
    modifiersPanel.add(new UMLCheckBox(localize("final"),this,new UMLReflectionBooleanProperty("isLeaf",mclass,"isLeaf","setLeaf")));
    modifiersPanel.add(new UMLCheckBox(localize("root"),this,new UMLReflectionBooleanProperty("isRoot",mclass,"isRoot","setRoot")));
    addField(modifiersPanel,5,0,1);

    addCaption("Derived:",0,1,1);
    JList derivedList = new UMLList(new UMLSpecializationListModel(this,null,true),true);
    derivedList.setForeground(Color.blue);
    derivedList.setVisibleRowCount(1);
    addField(new JScrollPane(derivedList),0,1,1);

    new PropPanelButton(this,buttonPanel,_navUpIcon,localize("Go up"),"navigateNamespace",null);
    new PropPanelButton(this,buttonPanel,_navBackIcon,localize("Go back"),"navigateBackAction","isNavigateBackEnabled");
    new PropPanelButton(this,buttonPanel,_navForwardIcon,localize("Go forward"),"navigateForwardAction","isNavigateForwardEnabled");
    new PropPanelButton(this,buttonPanel,_stereotypeIcon,localize("New stereotype"),"newStereotype",null);
    new PropPanelButton(this,buttonPanel,_deleteIcon,localize("Delete package"),"removeElement",null);

  }


    public void newStereotype() {
        Object target = getTarget();
        if(target instanceof MStereotype) {
            MNamespace ns = ((MStereotype) target).getNamespace();
            if(ns != null) {
                MStereotype newStereo = ns.getFactory().createStereotype();
                ns.addOwnedElement(newStereo);
                navigateTo(newStereo);
            }
        }
    }

    public String getBaseClass() {
      String baseClass = "ModelElement";
      Object target = getTarget();
      if(target instanceof MStereotype) {
        baseClass = ((MStereotype) target).getBaseClass();
      }
      return baseClass;
    }

    public void setBaseClass(String baseClass) {
      Object target = getTarget();
      if(target instanceof MStereotype) {
        ((MStereotype) target).setBaseClass(baseClass);
      }
    }


    protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("Stereotype");
    }


} /* end class PropPanelStereotype */
