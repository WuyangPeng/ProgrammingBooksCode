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


// File: TableModelClass_in_DeplByProps.java
// Classes: TableModelClass_in_DeplByProps
// Original Author: 5eichler@informatik.uni-hamburg.de
// $Id: TableModelClass_in_DeplByProps.java,v 1.1.1.1 2000/09/04 12:50:19 1sturm Exp $

package org.argouml.uml.diagram.deployment;

import java.util.*;
import java.beans.*;

import ru.novosoft.uml.foundation.core.*;

import org.argouml.uml.*;
import org.argouml.uml.diagram.deployment.ui.*;

public class TableModelClass_in_DeplByProps extends TableModelComposite {
  ////////////////
  // constructor
  public TableModelClass_in_DeplByProps() { }

  public void initColumns() {
    addColumn(ColumnDescriptor.Name);
    addColumn(ColumnDescriptor.ImplLocation);
    addColumn(ColumnDescriptor.ClassVisibility);
    addColumn(ColumnDescriptor.ClassKeyword);
    addColumn(ColumnDescriptor.Extends);
	//nsuml problem realization    addColumn(ColumnDescriptor.Implements);
    addColumn(ColumnDescriptor.MStereotype);
  }

  public Vector rowObjectsFor(Object t) {
    if (!(t instanceof UMLDeploymentDiagram || t instanceof MComponentImpl)) return new Vector();
    if (t instanceof UMLDeploymentDiagram) {
      UMLDeploymentDiagram d = (UMLDeploymentDiagram) t;
      Vector nodes = d.getNodes();
      Vector res = new Vector();
      int size = nodes.size();
      for (int i = 0; i < size; i++) {
        Object node = nodes.elementAt(i);
        if (node instanceof MClassImpl) res.addElement(node);
      }
      return res;
    }
    else {
      MComponent d = (MComponent) t;
      Vector res = new Vector();
      Collection elementResidences = d.getResidentElements();
      Iterator it = elementResidences.iterator();
      while (it.hasNext()) {
        MElementResidence residence = (MElementResidence) it.next();
        MModelElement node = (MModelElement) residence.getResident();
        if (node instanceof MClassImpl) res.addElement(node);

      }
      return res;
    }
  }

  public String toString() { return "Classes vs. Properties"; }
} /* end class TableModelClass_in_DeplByProps */

