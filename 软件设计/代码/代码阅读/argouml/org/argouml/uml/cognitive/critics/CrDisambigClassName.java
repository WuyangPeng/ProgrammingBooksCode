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



// File: CrDisambigClassName.java
// Classes: CrDisambigClassName
// Original Author: jrobbins@ics.uci.edu
// $Id: CrDisambigClassName.java,v 1.1.1.1 2000/09/04 12:50:24 1sturm Exp $

package org.argouml.uml.cognitive.critics;

import java.util.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.model_management.*;

import org.argouml.kernel.*;
import org.argouml.cognitive.*;
import org.argouml.cognitive.critics.*;

/** Well-formedness rule [1] for MNamespace. See page 33 of UML 1.1
 *  Semantics. OMG document ad/97-08-04. */

public class CrDisambigClassName extends CrUML {

  public CrDisambigClassName() {
    setHeadline("Choose a Unique Name for <ocl>self</ocl>");
    sd("Every class and interface within a package must have a unique "+
       "name. There are at least two elements in this package named "+
       "\"<ocl>self</ocl>\".\n\n"+
       "Clear and unambiguous naming is key to code generation and "+
       "the understandability and maintainability of the design. \n\n"+
       "To fix this, use the \"Next>\" button, or manually select one of the "+
       "conflicting classes and use the Properties tab to change their names.");
    addSupportedDecision(CrUML.decNAMING);
    setKnowledgeTypes(Critic.KT_SYNTAX);
    addTrigger("name");
    addTrigger("elementOwnership");
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    if (!(dm instanceof MClassifier)) return NO_PROBLEM;
    MClassifier cls = (MClassifier) dm;
    String myName = cls.getName();
    //@ if (myName.equals(Name.UNSPEC)) return NO_PROBLEM;
    String myNameString = myName;
    if (myNameString.length() == 0) return NO_PROBLEM;
    Collection pkgs = cls.getElementImports2();
    if (pkgs == null) return NO_PROBLEM;
    for (Iterator iter = pkgs.iterator(); iter.hasNext();) {
      MElementImport imp = (MElementImport)iter.next();
      MNamespace ns = imp.getPackage();
      Collection siblings = ns.getOwnedElements();
      if (siblings == null) return NO_PROBLEM;
      Iterator enum = siblings.iterator();
      while (enum.hasNext()) {
        MElementImport eo = (MElementImport) enum.next();
        MModelElement me = (MModelElement) eo.getModelElement();
        if (!(me instanceof MClassifier)) continue;
        if (me == cls) continue;
        String meName = me.getName();
        if (meName == null || meName.equals("")) continue;
        if (meName.equals(myNameString)) return PROBLEM_FOUND;
      }
    };
    return NO_PROBLEM;
  }

  public Icon getClarifier() {
    return ClClassName.TheInstance;
  }

  public void initWizard(Wizard w) {
    if (w instanceof WizMEName) {
      ToDoItem item = w.getToDoItem();
      MModelElement me = (MModelElement) item.getOffenders().elementAt(0);
      String sug = me.getName();
      String ins = "Change the name to something different.";
      ((WizMEName)w).setInstructions(ins);
      ((WizMEName)w).setSuggestion(sug);
      ((WizMEName)w).setMustEdit(true);
    }
  }
  public Class getWizardClass(ToDoItem item) { return WizMEName.class; }


} /* end class CrDisambigClassName.java */

