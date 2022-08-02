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

// File: CrUML.java
// Classes: CrUML
// Original Author: jrobbins@ics.uci.edu
// $Id: CrUML.java,v 1.6 2001/07/23 10:49:58 toby Exp $

package org.argouml.uml.cognitive.critics;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;

import org.tigris.gef.util.*;

import org.argouml.kernel.*;
import org.argouml.ui.*;
import org.argouml.cognitive.*;
import org.argouml.cognitive.critics.*;
import org.argouml.ocl.OCLEvaluator;
import java.io.*;
import java.util.*;

/** "Abstract" Critic subclass that captures commonalities among all
 *  critics in the UML domain.  This class also defines and registers
 *  the categories of design decisions that the critics can
 *  address.
 *
 * @see org.argouml.cognitive.Designer
 * @see org.argouml.cognitive.DecisionModel
 */

public class CrUML extends Critic {
  public static final Decision decINHERITANCE = new
  Decision("Inheritance", 5);

  public static final Decision decCONTAINMENT = new
  Decision("Containment", 5);

  public static final Decision decPATTERNS = new
  Decision("Design Patterns", 5); //??

  public static final Decision decRELATIONSHIPS = new
  Decision("Relationships", 5);

  public static final Decision decSTORAGE = new
  Decision("Storage", 5);

  public static final Decision decBEHAVIOR = new
  Decision("Behavior", 5);

  public static final Decision decINSTANCIATION = new
  Decision("Instantiation", 5);

  public static final Decision decNAMING = new
  Decision("Naming", 5);

  public static final Decision decMODULARITY = new
  Decision("Modularity", 5);

  public static final Decision decCLASS_SELECTION = new
  Decision("Class Selection", 5);

  public static final Decision decEXPECTED_USAGE = new
  Decision("Expected Usage", 5);

  public static final Decision decMETHODS = new
  Decision("Methods", 5); //??

  public static final Decision decCODE_GEN = new
  Decision("Code Generation", 5); //??

  public static final Decision decPLANNED_EXTENSIONS = new
  Decision("Planned Extensions", 5);

  public static final Decision decSTEREOTYPES = new
  Decision("Stereotypes", 5);

  public static final Decision decSTATE_MACHINES = new
  Decision("MState Machines", 5);

  public static String CRITICS_SITE = "http://www.ics.uci.edu/pub/arch/uml/critics/";

  /** Static initializer for this class. Called when the class is
   *  loaded (which is before any subclass instances are instanciated). */
  static {
    Designer d = Designer.theDesigner();
    d.startConsidering(decCLASS_SELECTION);
    d.startConsidering(decNAMING);
    d.startConsidering(decSTORAGE);
    d.startConsidering(decINHERITANCE);
    d.startConsidering(decCONTAINMENT);
    d.startConsidering(decPLANNED_EXTENSIONS);
    d.startConsidering(decSTATE_MACHINES);
    d.startConsidering(decPATTERNS);
    d.startConsidering(decRELATIONSHIPS);
    d.startConsidering(decINSTANCIATION);
    d.startConsidering(decMODULARITY);
    d.startConsidering(decEXPECTED_USAGE);
    d.startConsidering(decMETHODS);
    d.startConsidering(decCODE_GEN);
    d.startConsidering(decSTEREOTYPES);
  }



  ////////////////////////////////////////////////////////////////
  // constructor

  public CrUML() {
  }

  public void setResource(String key) {
        String head = Localizer.localize("Cognitive",key + "_head");
        super.setHeadline(head);
        String desc = Localizer.localize("Cognitive",key + "_desc");
        super.setDescription(desc);
  }

/*
   the following code was used to build UMLCognitiveResourceBundle
       from calls made during the construction of critics


  static public String makeKey(Class cls,String type) {
    String className = cls.getName();
    int lastDot = className.lastIndexOf('.');
    if(lastDot >= 0) {
        className = className.substring(lastDot+1);
    }
    return className + "_" + type;
  }

//  private final void log(String s) {}
  private static boolean _logAppend = false;
  static public final void log(String s) {
    if(!_logAppend) {
        System.out.println("Logging resources to UMLCognitiveResourceBundle.log");
    }
    try {
        PrintWriter writer = new PrintWriter(
            new FileOutputStream("UMLCognitiveResourceBundle.log",_logAppend));
        writer.println(s);
        writer.close();
    }
    catch(Exception e) {
        if(!_logAppend) {
            e.printStackTrace();
        }
    }
    _logAppend = true;
  }

  static public String escape(String s,char special,String escape) {
    int nextQuote = s.indexOf(special);
    //
    //   if there was a quote mark within the string
    //     expand it to a \"
    if(nextQuote >= 0) {
        StringBuffer buf = new StringBuffer(s.length() + 20);
        char[] chars = s.toCharArray();
        int position = 0;
        while(nextQuote >= 0) {
            if(nextQuote > 0) {
                buf.append(chars,position,nextQuote-position);
            }
            buf.append(escape);
            position = nextQuote + 1;
            if(position+1 == chars.length) break;
            nextQuote = s.indexOf(special,position);
        }
        //
        //  append text after last quote
        //
        if(position < chars.length) {
            buf.append(chars,position,chars.length - position);
        }
        return buf.toString();
    }
    return s;
  }

*/

  /**
   *    To be deprecated
   *
   */
  public final void setDescription(String s) {
//       no-op since description is loaded from ResourceFile
//
//    super.setDescription(s);
//    log("{ \"" + makeKey(getClass(),"desc") + "\" ,\n        \"" + escape(escape(s,'\"',"\\\""),'\n',"\\n") + "\" },");
  }

  /**
   *   Will be deprecated in good time
   */
  public final void setHeadline(String s) {
      //
      //   current implementation ignores the argument
      //     and triggers setResource()
      String className = getClass().getName();
      setResource(className.substring(className.lastIndexOf('.')+1));
//    super.setHeadline(s);
//    log("{ \"" + makeKey(getClass(),"head") + "\" ,\n        \"" + escape(escape(s,'\"',"\\\""),'\n',"\\n") + "\" },");
  }



  public boolean predicate(Object dm, Designer dsgr) {
    Project p = ProjectBrowser.TheInstance.getProject();
    if (p.isInTrash(dm)) {
      //System.out.println("in trash:" + dm);
      return NO_PROBLEM;
    }
    else return predicate2(dm, dsgr);
  }

  public boolean predicate2(Object dm, Designer dsgr) {
    return super.predicate(dm, dsgr);
  }

  public String getMoreInfoURL(VectorSet offenders, Designer dsgr) {
    String clsName = getClass().getName();
    clsName = clsName.substring(clsName.lastIndexOf(".") + 1);
    return CRITICS_SITE + clsName + ".html";
  }

  ////////////////////////////////////////////////////////////////
  // coding shorthand

  protected void sd(String s) {
    setDescription(s);
  }


  ////////////////////////////////////////////////////////////////
  // display related methods

  private static String OCL_START = "<ocl>";
  private static String OCL_END = "</ocl>";



  public String expand(String res, VectorSet offs) {
      //System.out.println("expanding: " + res);
    if (offs.size() == 0) return res;
    Object off1 = offs.firstElement();
    if (!(off1 instanceof MElement)) return res;

    int searchPos = 0;
    int matchPos = res.indexOf(OCL_START, searchPos);

    // replace all occurances of OFFENDER with the name of the first offender
    while (matchPos != -1) {
      int endExpr = res.indexOf(OCL_END, matchPos + 1);
      //check if there is no OCL_END; if so, the critic expression s not correct and can not be expanded
      if (endExpr == -1) return res; 
      String expr = res.substring(matchPos + OCL_START.length(), endExpr);
      String evalStr = OCLEvaluator.SINGLETON.evalToString(off1, expr);
      //System.out.println("expr='" + expr + "' = '" + evalStr + "'");
      if (expr.endsWith("") && evalStr.equals(""))
	evalStr = "(anon)";
      res = res.substring(0, matchPos) +
	evalStr +
	res.substring(endExpr + OCL_END.length());
      searchPos = endExpr + 1;
      matchPos = res.indexOf(OCL_START, searchPos);
    }
    return res;
  }

} /* end class CrUML */
