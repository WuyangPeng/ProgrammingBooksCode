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



// File: PropPanelEvent.java
// Classes: PropPanelEvent
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

public abstract class PropPanelEvent extends PropPanelModelElement {

    protected JScrollPane paramScroll;
    
    ////////////////////////////////////////////////////////////////
    // contructors
    public PropPanelEvent(String name, int columns) {
	this(name, null, columns);
    }

    public PropPanelEvent(String name, ImageIcon icon, int columns) {
        super(name,icon,columns);

        Class mclass = MEvent.class;

        JList paramList = new UMLList(new UMLReflectionListModel(this,"parameter",true,"getParameters","setParameters","addParameter",null),true);
        paramList.setForeground(Color.blue);
        paramList.setVisibleRowCount(1);
	paramList.setFont(smallFont);
	paramScroll=new JScrollPane(paramList);

	new PropPanelButton(this,buttonPanel,_navUpIcon,localize("Go up"),"navigateUp",null);
	new PropPanelButton(this,buttonPanel,_navBackIcon,localize("Go back"),"navigateBackAction","isNavigateBackEnabled");
	new PropPanelButton(this,buttonPanel,_navForwardIcon,localize("Go forward"),"navigateForwardAction","isNavigateForwardEnabled");
	new PropPanelButton(this,buttonPanel,_parameterIcon,localize("Add parameter"),"buttonAddParameter",null);
  }

    public java.util.List getParameters() {
        java.util.List params = null;
        Object target = getTarget();
        if(target instanceof MEvent) {
            params = ((MEvent) target).getParameters();
        }
        return params;
    }

    public void setParameters(Collection newParams) {
        Object target = getTarget();
        if(target instanceof MEvent) {
            if(newParams instanceof java.util.List) {
                ((MEvent) target).setParameters((java.util.List) newParams);
            }
            else {
                ((MEvent) target).setParameters(new ArrayList(newParams));
            }
        }
    }

    public void addParameter(Integer indexObj) {
	buttonAddParameter();
    }

   public void buttonAddParameter() {
        Object target = getTarget();
        if(target instanceof MEvent) {
            MEvent ev = (MEvent) target;
            MParameter newParam = ev.getFactory().createParameter();
            newParam.setKind(MParameterDirectionKind.INOUT);
            ev.addParameter(newParam);
            navigateTo(newParam);
        }
    }

    protected boolean isAcceptibleBaseMetaClass(String baseClass) {
        return baseClass.equals("Event");
    }

} /* end class PropPanelEvent */



