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

// File: CrNoOperations.javoa
// Classes: CrNoOperations
// Original Author: jrobbins@ics.uci.edu
// $Id: CrNoOperations.java,v 1.2 2000/09/21 18:48:15 carnold Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;

import org.argouml.cognitive.*;
import org.argouml.cognitive.critics.*;

/** A critic to detect when a class can never have instances (of
 *  itself of any subclasses). */

public class CrNoOperations extends CrUML {

  public CrNoOperations() {
    setHeadline("Add Operations to <ocl>self</ocl>");
    sd("You have not yet specified operations for <ocl>self</ocl>. "+
       "Normally classes provide operations that define their behavior. \n\n"+
       "Defining operations is needed to complete the behavioral "+
       "specification part of your design. \n\n"+
       "To fix this, press the \"Next>\" button, or add operations manually "+
       "by clicking on <ocl>self</ocl> in the navigator pane and "+
       "using the Create menu to make a new operations. ");

    addSupportedDecision(CrUML.decBEHAVIOR);
    setKnowledgeTypes(Critic.KT_COMPLETENESS);
    addTrigger("behavioralFeature");
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MClass)) return NO_PROBLEM;
    MClass cls = (MClass) dm;
    //if (cls.containsStereotype(MStereotype.UTILITY)) return NO_PROBLEM;
    // stereotype <<record>>?
    //needs-more-work: different critic or special message for classes
    //that inherit all ops but define none of their own.

    Collection beh = getInheritedBehavioralFeatures(cls,0);
    if (beh == null) return PROBLEM_FOUND;
    for (Iterator iter = beh.iterator(); iter.hasNext();) {
      MBehavioralFeature bf = (MBehavioralFeature) iter.next();
      MScopeKind sk = bf.getOwnerScope();
      if (MScopeKind.INSTANCE.equals(sk)) return NO_PROBLEM;
    }
    //needs-more-work?: don't count static or constants?
    return PROBLEM_FOUND;
  }

  public Icon getClarifier() {
    return ClOperationCompartment.TheInstance;
  }

  private Collection getInheritedBehavioralFeatures(MClassifier cls,int depth)
  {
     Collection res = new Vector();
     Collection features = cls.getFeatures();
     for (Iterator iter = features.iterator(); iter.hasNext();) {
       Object feature = iter.next();
       if (feature instanceof MBehavioralFeature)
         res.add(feature);
     };
     Collection inh = cls.getGeneralizations();
     for (Iterator iter = inh.iterator(); iter.hasNext();) {
       MGeneralization gen = (MGeneralization)iter.next();
       MGeneralizableElement parent = gen.getParent();
       if (parent != cls && parent instanceof MClassifier && depth < 50) {
         Collection superassocs = getInheritedBehavioralFeatures((MClassifier) parent,depth+1);
         res.addAll(superassocs);
       };
     };
     return res;
  };

} /* end class CrNoOperations */

