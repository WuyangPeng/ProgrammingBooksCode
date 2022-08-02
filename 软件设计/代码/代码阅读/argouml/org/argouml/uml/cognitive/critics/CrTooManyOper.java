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

// File: CrTooManyOper.java
// Classes: CrTooManyOper
// Original Author: jrobbins@ics.uci.edu
// $Id: CrTooManyOper.java,v 1.1.1.1 2000/09/04 12:50:25 1sturm Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;

import org.argouml.cognitive.*;

/** A critic to detect when a class can never have instances (of
 *  itself of any subclasses). */

public class CrTooManyOper extends CrUML {

  ////////////////////////////////////////////////////////////////
  // constants
  public static String THRESHOLD = "Threshold";

  ////////////////////////////////////////////////////////////////
  // constructor
  public CrTooManyOper() {
    setHeadline("Reduce Operations on <ocl>self</ocl>");
    sd("There are too many Operations on class <ocl>self</ocl>.  Whenever one class "+
       "becomes too central to the design it may become a maintenance "+
       "bottleneck that must be updated frequently. \n\n"+
       "Defining the operations of objects is an important "+
       "part of your design. \n\n"+
       "To fix this, press the \"Next>\" button, or remove attributes manually "+
       "by double-clicking on the operation compartment of the  "+
       "highlighted class in the diagram and removing the line of text "+
       "for an operation. ");

    addSupportedDecision(CrUML.decMETHODS);
    setArg(THRESHOLD, new Integer(20));
    addTrigger("behavioralFeature");
  }

  ////////////////////////////////////////////////////////////////
  // critiquing API
  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MClassifier)) return NO_PROBLEM;
    MClassifier cls = (MClassifier) dm;
    // needs-more-work: consider inherited attributes?
    int threshold = ((Integer)getArg(THRESHOLD)).intValue();
    Collection str = cls.getFeatures();
    if (str == null) return NO_PROBLEM;
    int n=0;
    for (Iterator iter = str.iterator(); iter.hasNext();) {
      if (iter.next() instanceof MBehavioralFeature)
        n++;
    };
    if (n <= threshold) return NO_PROBLEM;
    return PROBLEM_FOUND;
  }

} /* end class CrTooManyOper */

