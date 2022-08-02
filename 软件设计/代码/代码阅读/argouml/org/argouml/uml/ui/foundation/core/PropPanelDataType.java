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


package org.argouml.uml.ui.foundation.core;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.model_management.*;
import javax.swing.*;
import org.argouml.uml.ui.*;
import java.awt.*;
import java.util.*;

public class PropPanelDataType extends PropPanelClassifier {


  ////////////////////////////////////////////////////////////////
  // contructors
  public PropPanelDataType() {
    super("DataType", _dataTypeIcon,2);

    Class mclass = MDataType.class;

    addCaption("Name:",1,0,0);
    addField(new UMLTextField(this,new UMLTextProperty(mclass,"name","getName","setName")),1,0,0);


    addCaption("Stereotype:",2,0,0);
    addField(new UMLComboBoxNavigator(this,"NavStereo",stereotypeBox),2,0,0);

    addCaption("Extends:",3,0,0);
    addField(extendsScroll,3,0,0);

    addCaption("Implements:",4,0,0);
    addField(implementsScroll,4,0,0);

    addCaption("Modifiers:",5,0,0);
    addField(_modifiersPanel,5,0,0);

    addCaption("Namespace:",6,0,0);
    addField(namespaceScroll,6,0,0);

    addCaption("Derived:",7,0,1);
    addField(derivedScroll,7,0,1);

    addCaption("Literals:",1,1,0.5);
    JList attrList = new UMLList(new UMLAttributesListModel(this,"feature",true),true);
    attrList.setForeground(Color.blue);
    attrList.setVisibleRowCount(1);
    JScrollPane attrScroll= new JScrollPane(attrList);
    addField(attrScroll,1,1,0.5);

    addCaption("Operations:",0,1,0.5);
    addField(opsScroll,0,1,0.5);

    new PropPanelButton(this,buttonPanel,_navUpIcon,localize("Go up"),"navigateNamespace",null);
    new PropPanelButton(this,buttonPanel,_navBackIcon,localize("Go back"),"navigateBackAction","isNavigateBackEnabled");
    new PropPanelButton(this,buttonPanel,_navForwardIcon,localize("Go forward"),"navigateForwardAction","isNavigateForwardEnabled");
    new PropPanelButton(this,buttonPanel,_dataTypeIcon,localize("New data type"),"newDataType",null);
    new PropPanelButton(this,buttonPanel,_addAttrIcon,localize("Add enumeration literal"),"addAttribute",null);
    new PropPanelButton(this,buttonPanel,_deleteIcon,localize("Delete datatype"),"removeElement",null);
  }

    public void addAttribute() {
        Object target = getTarget();
        if(target instanceof MClassifier) {
            MClassifier classifier = (MClassifier) target;
            MStereotype stereo = classifier.getStereotype();
            if(stereo == null) {
                //
                //  if there is not an enumeration stereotype as
                //     an immediate child of the model, add one
                MModel model = classifier.getModel();
                Object ownedElement;
                boolean match = false;
                if(model != null) {
                    Collection ownedElements = model.getOwnedElements();
                    if(ownedElements != null) {
                        Iterator iter = ownedElements.iterator();
                        while(iter.hasNext()) {
                            ownedElement = iter.next();
                            if(ownedElement instanceof MStereotype) {
                                stereo = (MStereotype) ownedElement;
                                String stereoName = stereo.getName();
                                if(stereoName != null && stereoName.equals("enumeration")) {
                                    match = true;
                                    break;
                                }
                            }
                        }
                        if(!match) {
                            stereo = classifier.getFactory().createStereotype();
                            stereo.setName("enumeration");
                            model.addOwnedElement(stereo);
                        }
                        classifier.setStereotype(stereo);
                    }
                }
            }

            MAttribute attr = classifier.getFactory().createAttribute();
            attr.setOwnerScope(MScopeKind.CLASSIFIER);
            attr.setChangeability(MChangeableKind.FROZEN);
            attr.setVisibility(MVisibilityKind.PUBLIC);
            attr.setType(classifier);
            classifier.addFeature(attr);
            navigateTo(attr);
        }
    }

    protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("DataType") ||
            baseClass.equals("Classifier") ||
            baseClass.equals("GeneralizableElement");
    }

    public void newDataType() {
        Object target = getTarget();
        if(target instanceof MDataType) {
            MDataType dt = (MDataType) target;
            MNamespace ns = dt.getNamespace();
            MDataType newDt = dt.getFactory().createDataType();
            ns.addOwnedElement(newDt);
            navigateTo(newDt);
        }
    }
} /* end class PropPanelDataType */
