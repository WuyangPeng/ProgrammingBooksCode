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


// File: TableModelSeqLinkByProps.java
// Classes: TableModelSeqLinkByProps
// Original Author: 5eichler@informatik.uni-hamburg.de
// $Id: TableModelSeqLinkByProps.java,v 1.1 2000/09/29 16:02:26 boger Exp $


package org.argouml.uml.diagram.sequence;

import java.util.*;
import java.beans.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.behavior.common_behavior.*;

import org.argouml.uml.*;
import org.argouml.uml.diagram.sequence.ui.*;


public class TableModelSeqLinkByProps extends TableModelComposite {
  ////////////////
  // constructor
  public TableModelSeqLinkByProps() { }

  public void initColumns() {
    addColumn(ColumnDescriptor.Name);
    addColumn(ColumnDescriptor.SrcLinkType);
    addColumn(ColumnDescriptor.DstLinkType);
    addColumn(ColumnDescriptor.MStereotype);
  }

  public Vector rowObjectsFor(Object t) {
    if (!(t instanceof UMLSequenceDiagram)) return new Vector();
    UMLSequenceDiagram d = (UMLSequenceDiagram) t;
    Vector edges = d.getEdges();
    Vector res = new Vector();
    int size = edges.size();
    for (int i = 0; i < size; i++) {
      Object edge = edges.elementAt(i);
      if (edge instanceof MLinkImpl) res.addElement(edge);
    }
    return res;
  }

  public String toString() { return "SeqLinks vs. Properties"; }
} /* end class TableModelSeqLinkByProps */

