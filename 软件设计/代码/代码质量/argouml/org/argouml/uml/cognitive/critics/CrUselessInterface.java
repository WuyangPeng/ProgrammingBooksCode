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



// File: CrUselessInterface.java
// Classes: CrUselessInterface
// Original Author: jrobbins@ics.uci.edu
// $Id: CrUselessInterface.java,v 1.1.1.1 2000/09/04 12:50:26 1sturm Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;
import java.awt.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;

import org.argouml.cognitive.*;
import org.argouml.cognitive.critics.*;

/** A critic to detect when a class can never have instances (of
 *  itself of any subclasses). */

public class CrUselessInterface extends CrUML {

  public CrUselessInterface() {
    setHeadline("Define Class to Implement <ocl>self</ocl>");
    String s;
    s = "<ocl>self</ocl> can never be used because "+
      "no classes implement it.\n\n"+
      "To fix this problem, press the \"Next>\" button or manually "+
      "use the toolbar \"Class\" button to define classes and the "+
      "\"Realizes\" button to make a relationship from the class to "+
      "the highlighted interface.";
    setDescription(s);
    addSupportedDecision(CrUML.decINHERITANCE);
    addSupportedGoal(Goal.UNSPEC);
    setKnowledgeTypes(Critic.KT_COMPLETENESS);
    addTrigger("realization");
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MInterface)) return false;
    MInterface intf = (MInterface) dm;
    Collection realization = getRealizations(intf);
    if (realization == null || realization.size() == 0)
      return PROBLEM_FOUND;
    else return NO_PROBLEM;
  }
  private Collection getRealizations(MClassifier cls)
  {
     Vector res = new Vector();
     Collection deps = cls.getSupplierDependencies();
     if (deps==null) return res;
     for (Iterator iter = deps.iterator(); iter.hasNext();) {
       MDependency dependency = (MDependency)iter.next();
       MStereotype stereotype = dependency.getStereotype();
       if ((stereotype==null) || ("realize".equals(stereotype.getName())))
         res.addAll(dependency.getClients());
     };
     return res;
  };

} /* end class CrUselessInterface */
