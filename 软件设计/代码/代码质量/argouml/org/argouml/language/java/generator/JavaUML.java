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


package org.argouml.language.java.generator;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.beans.*;

import org.argouml.uml.UUIDManager;
import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.model_management.*;
import ru.novosoft.uml.xmi.*;

/** A file of information about the Java language.  This is used to
 *  fill in the offered data types in variable and operation
 *  declarations.
 * In the end, it would be better to have these in XMI files that are loaded at starting time.
*/

public class JavaUML {

  // java.lang

  public static MClass STRING_CLASS = new MClassImpl();

  public static MDataType VOID_TYPE = new MDataTypeImpl();
  public static MDataType CHAR_TYPE = new MDataTypeImpl();
  public static MDataType INT_TYPE = new MDataTypeImpl();
  public static MDataType BOOLEAN_TYPE = new MDataTypeImpl();
  public static MDataType BYTE_TYPE = new MDataTypeImpl();
  public static MDataType LONG_TYPE = new MDataTypeImpl();
  public static MDataType FLOAT_TYPE = new MDataTypeImpl();
  public static MDataType DOUBLE_TYPE = new MDataTypeImpl();

  public static MClass CHAR_CLASS = new MClassImpl();
  public static MClass INT_CLASS = new MClassImpl();
  public static MClass BOOLEAN_CLASS = new MClassImpl();
  public static MClass BYTE_CLASS = new MClassImpl();
  public static MClass LONG_CLASS = new MClassImpl();
  public static MClass FLOAT_CLASS = new MClassImpl();
  public static MClass DOUBLE_CLASS = new MClassImpl();


  // java.awt
  public static MClass RECTANGLE_CLASS = new MClassImpl();
  public static MClass POINT_CLASS = new MClassImpl();
  public static MClass COLOR_CLASS = new MClassImpl();


  // java.util
  public static MClass VECTOR_CLASS = new MClassImpl();
  public static MClass HASHTABLE_CLASS = new MClassImpl();
  public static MClass STACK_CLASS = new MClassImpl();

	public static MModel javastandards = new MModelImpl();

  static{
   STRING_CLASS.setName("String");
   CHAR_CLASS.setName("Character");
   INT_CLASS.setName("Integer");
   BOOLEAN_CLASS.setName("Boolean");
   BYTE_CLASS.setName("Byte");
   LONG_CLASS.setName("Long");
   FLOAT_CLASS.setName("Float");
   DOUBLE_CLASS.setName("Double");
   RECTANGLE_CLASS.setName("Rectangle");
   POINT_CLASS.setName("Point");
   COLOR_CLASS.setName("Color");
   VECTOR_CLASS.setName("Vector");
   HASHTABLE_CLASS.setName("Hashtable");
   STACK_CLASS.setName("Stack");

   VOID_TYPE.setName("void");
   CHAR_TYPE.setName("char");
   INT_TYPE.setName("int");
   BOOLEAN_TYPE.setName("boolean");
   BYTE_TYPE.setName("byte");
   LONG_TYPE.setName("long");
   FLOAT_TYPE.setName("float");
   DOUBLE_TYPE.setName("double");

//    javastandards.addOwnedElement(STRING_CLASS);
//    javastandards.addOwnedElement(CHAR_CLASS);
//    javastandards.addOwnedElement(INT_CLASS);
//    javastandards.addOwnedElement(BOOLEAN_CLASS);
//    javastandards.addOwnedElement(BYTE_CLASS);
//    javastandards.addOwnedElement(LONG_CLASS);
//    javastandards.addOwnedElement(FLOAT_CLASS);
//    javastandards.addOwnedElement(DOUBLE_CLASS);
//    javastandards.addOwnedElement(RECTANGLE_CLASS);
//    javastandards.addOwnedElement(POINT_CLASS);
//    javastandards.addOwnedElement(COLOR_CLASS);
//    javastandards.addOwnedElement(VECTOR_CLASS);
//    javastandards.addOwnedElement(HASHTABLE_CLASS);
//    javastandards.addOwnedElement(STACK_CLASS);
//    javastandards.addOwnedElement(VOID_TYPE);
//    javastandards.addOwnedElement(CHAR_TYPE);
//    javastandards.addOwnedElement(INT_TYPE);
//    javastandards.addOwnedElement(BOOLEAN_TYPE);
//    javastandards.addOwnedElement(BYTE_TYPE);
//    javastandards.addOwnedElement(LONG_TYPE);
//    javastandards.addOwnedElement(FLOAT_TYPE);
//    javastandards.addOwnedElement(DOUBLE_TYPE);

//    UUIDManager.SINGLETON.createModelUUIDS(javastandards);
//    javastandards.setName("Javastandards");
   //try {XMIWriter writer = new XMIWriter(javastandards, "java.xmi");writer.gen();} catch (Exception e) {}

  }


} /* end class JavaUML */
