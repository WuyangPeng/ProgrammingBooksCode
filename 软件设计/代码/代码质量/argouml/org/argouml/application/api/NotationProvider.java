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

package org.argouml.application.api;
// import org.argouml.application.events.*;
import org.argouml.language.*;
import org.argouml.uml.diagram.ui.*;

import java.awt.*;
import java.util.*;
import java.beans.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;
import ru.novosoft.uml.behavior.common_behavior.*;
import ru.novosoft.uml.behavior.activity_graphs.*;
import ru.novosoft.uml.behavior.state_machines.*;
import ru.novosoft.uml.behavior.use_cases.*;
import ru.novosoft.uml.behavior.collaborations.*;
import ru.novosoft.uml.model_management.*;

public interface NotationProvider {

  public NotationName getNotation();

  public String generateOperation(MOperation op);
  public String generateAttribute(MAttribute attr);
  public String generateParameter(MParameter param);
  public String generateName(String name);
  public String generatePackage(MPackage pkg);
  public String generateExpression(MExpression expr);
  public String generateClassifier(MClassifier cls);
  public String generateStereotype(MStereotype s);
  public String generateTaggedValue(MTaggedValue s);
  public String generateAssociation(MAssociation a);
  public String generateAssociationEnd(MAssociationEnd ae);
  public String generateMultiplicity(MMultiplicity m);
  public String generateState(MState m);
  public String generateStateBody(MState stt);
  public String generateTransition(MTransition m);
  public String generateAction(MAction m);
  public String generateGuard(MGuard m);
  public String generateMessage(MMessage m);
  public String generateClassifierRef(MClassifier m);

  /** Can the notation be parsed for this object?
   */
  public boolean canParse(Object o);

  /** Can the notation be parsed at all?
   */
  public boolean canParse();

  // public void parseOperationCompartment(MClassifier cls, String s);
  // public void parseAttributeCompartment(MClassifier cls, String s);
  // public MOperation parseOperation(String s);
  // public MAttribute parseAttribute(String s);
  // public String parseOutVisibility(MFeature f, String s);
  // public String parseOutKeywords(MFeature f, String s);
  // public String parseOutReturnType(MOperation op, String s);
  // public String parseOutParams(MOperation op, String s);
  // public String parseOutName(MModelElement me, String s);
  // public String parseOutType(MAttribute attr, String s);
  // public String parseOutInitValue(MAttribute attr, String s);
  // public String parseOutColon(String s);
  // public MParameter parseParameter(String s);
  // public Package parsePackage(String s);
  // public MClassImpl parseClassifier(String s);
  // public MStereotype parseStereotype(String s);
  // public MTaggedValue parseTaggedValue(String s);
  // public MAssociation parseAssociation(String s);
  // public MAssociationEnd parseAssociationEnd(String s);
  // public MMultiplicity parseMultiplicity(String s);
  // public MState parseState(String s);
  // public void parseStateBody(MState st, String s);
  // public void parseStateEntyAction(MState st, String s);
  // public void parseStateExitAction(MState st, String s);
  // public MTransition parseTransition(MTransition trans, String s);
  // public void parseClassifierRole(MClassifierRole cls, String s);
  // public void parseMessage(MMessage mes, String s);
  // public void parseStimulus(MStimulus sti, String s);
  // public MAction parseAction(String s);
  // public MGuard parseGuard(String s);
  // public MEvent parseEvent(String s);
  // public void parseObject(MObject obj, String s);
  // public void parseNodeInstance(MNodeInstance noi, String s);
  // public void parseComponentInstance(MComponentInstance coi, String s);
}

