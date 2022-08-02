// Copyright (c) 1996-2001 The Regents of the University of California. All
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

package org.argouml.uml.ui;
import ru.novosoft.uml.*;
import javax.swing.*;
import ru.novosoft.uml.foundation.core.*;
import java.util.*;
import java.awt.*;

public class UMLSpecializationListModel extends UMLModelElementListModel  {

    private final static String _nullLabel = "(null)";
    
    public UMLSpecializationListModel(UMLUserInterfaceContainer container,String property,boolean showNone) {
        super(container,property,showNone);
    }
    
    protected int recalcModelElementSize() {
        int size = 0;
        Collection specializations = getSpecializations();
        if(specializations != null) {
            size = specializations.size();
        }
        return size;
    }
    
    protected MModelElement getModelElementAt(int index) {
        MModelElement elem = null;
        Collection specializations = getSpecializations();
        if(specializations != null) {
            elem = elementAtUtil(specializations,index,MGeneralization.class);
        }
        return elem;
    }
            
        
    private Collection getSpecializations() {
        Collection specializations = null;
        Object target = getTarget();
        if(target instanceof MGeneralizableElement) {
            MGeneralizableElement genElement = (MGeneralizableElement) target;
            specializations = genElement.getSpecializations();
        }
        return specializations;
    }
    
    public Object formatElement(MModelElement element) {
        Object value = _nullLabel;
        if(element != null) {
            MGeneralization gen = (MGeneralization) element;
            MGeneralizableElement target = gen.getChild();
            if(target != null) {
                value = getContainer().formatElement(target);
            }
        }
        return value;
    }
    
    public boolean buildPopup(JPopupMenu popup,int index) {
        UMLUserInterfaceContainer container = getContainer();
        UMLListMenuItem open = new UMLListMenuItem(container.localize("Open"),this,"open",index);
        //
        //  if there are no real elements (just a none placeholder)
        //     then disable the Open popup
        if(getModelElementSize() == 0) {
            open.setEnabled(false);
        }
        popup.add(open);
        return true;
    }

            
}




