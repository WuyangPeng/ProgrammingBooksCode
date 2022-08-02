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



// File: CrSeqInstanceWithoutClassifier.java
// Classes: CrSeqInstanceWithoutClassifier
// Original Author: 5eichler@informatik.uni-hamburg.de
// $Id: CrSeqInstanceWithoutClassifier.java,v 1.1 2000/09/29 16:02:25 boger Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.behavior.common_behavior.*;

import org.argouml.cognitive.*;
import org.argouml.uml.diagram.sequence.ui.FigSeqLink;
import org.argouml.uml.diagram.sequence.ui.FigSeqObject;
import org.argouml.uml.diagram.sequence.ui.UMLSequenceDiagram;
import org.argouml.uml.diagram.ui.FigNodeModelElement;

import org.tigris.gef.util.VectorSet;



/**
 * A critic to detect when an object in a deployment-diagram
 * is not inside a component or a component-instance
 **/

public class CrSeqInstanceWithoutClassifier extends CrUML {

  public CrSeqInstanceWithoutClassifier() {
    setHeadline("Set classifier");
    sd(" Instances have a classifier");
    addSupportedDecision(CrUML.decPATTERNS);
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof UMLSequenceDiagram)) return NO_PROBLEM;
    UMLSequenceDiagram sd = (UMLSequenceDiagram) dm;
    VectorSet offs = computeOffenders(sd);
    if (offs == null) return NO_PROBLEM;
    return PROBLEM_FOUND;
  }

  public ToDoItem toDoItem(Object dm, Designer dsgr) {
    UMLSequenceDiagram sd = (UMLSequenceDiagram) dm;
    VectorSet offs = computeOffenders(sd);
    return new ToDoItem(this, offs, dsgr);
  }

  public boolean stillValid(ToDoItem i, Designer dsgr) {
    if (!isActive()) return false;
    VectorSet offs = i.getOffenders();
    UMLSequenceDiagram sd = (UMLSequenceDiagram) offs.firstElement();
    //if (!predicate(dm, dsgr)) return false;
    VectorSet newOffs = computeOffenders(sd);
    boolean res = offs.equals(newOffs);
    return res;
  }

  /**
   * If there are instances that have no classifiers they belong to
   * the returned vector-set is not null. Then in the vector-set
   * are the UMLSequenceDiagram and all FigObjects, FigComponentInstances
   * and FigMNodeInstances with no classifier.
   **/
  public VectorSet computeOffenders(UMLSequenceDiagram sd) { 
    Vector figs = sd.getLayer().getContents();
    VectorSet offs = null;
    int size = figs.size();
    for (int i=0; i<size; i++) {
      Object obj = figs.elementAt(i);
      if (!(obj instanceof FigNodeModelElement)) continue;
      FigNodeModelElement fn = (FigNodeModelElement) obj;
      if (fn != null && (fn.getOwner() instanceof MInstance)) {
        MInstance minst = (MInstance) fn.getOwner();
        if (minst != null) {
          Collection col = minst.getClassifiers();
          if (col.size()>0) continue;     
        }       
        if (offs == null) {
          offs = new VectorSet();
          offs.addElement(sd);
        }
        offs.addElement(fn);
      }
    }
    return offs;
  } 
 
} /* end class CrSeqInstanceWithoutClassifier.java */

