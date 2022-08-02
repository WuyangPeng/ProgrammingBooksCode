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

package org.argouml.uml.diagram.ui;

import java.util.*;
import java.awt.*;
import java.beans.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;

import org.tigris.gef.base.*;

import org.argouml.ui.*;

public class UMLDiagram extends ArgoDiagram {

  ////////////////////////////////////////////////////////////////
  // actions for toolbar

  protected static Action _actionSelect =
  new CmdSetMode(ModeSelect.class, "Select");

  protected static Action _actionBroom =
  new CmdSetMode(ModeBroom.class, "Broom");

  protected static Action _actionRectangle =
  new CmdSetMode(ModeCreateFigRect.class, "Rectangle");

  protected static Action _actionRRectangle =
  new CmdSetMode(ModeCreateFigRRect.class, "RRect");

  protected static Action _actionCircle =
  new CmdSetMode(ModeCreateFigCircle.class, "Circle");

  protected static Action _actionLine =
  new CmdSetMode(ModeCreateFigLine.class, "Line");

  protected static Action _actionText =
  new CmdSetMode(ModeCreateFigText.class, "Text");

  protected static Action _actionPoly =
  new CmdSetMode(ModeCreateFigPoly.class, "Polygon");

  protected static Action _actionSpline =
  new CmdSetMode(ModeCreateFigSpline.class, "Spline");

  protected static Action _actionInk =
  new CmdSetMode(ModeCreateFigInk.class, "Ink");


  ////////////////////////////////////////////////////////////////
  // instance variables
  protected MNamespace  _namespace;
  protected DiagramInfo _diagramName = new DiagramInfo(this);


  ////////////////////////////////////////////////////////////////
  // constructors

  public UMLDiagram() { }

  public UMLDiagram(MNamespace ns) {
    _namespace = ns;
  }

  public UMLDiagram(String diagramName, MNamespace ns) {
    try { setName(diagramName); }
    catch (PropertyVetoException pve) { }
    _namespace = ns;
  }

  public void initialize(Object owner) {
    super.initialize(owner);
    if (owner instanceof MNamespace) setNamespace((MNamespace) owner);
    else System.out.println("unknown object in UMLDiagram initialize:"
			    + owner);
  }


  ////////////////////////////////////////////////////////////////
  // accessors

  public MNamespace getNamespace() { return _namespace; }
  public void setNamespace(MNamespace m) { _namespace = m; }

  public String getClassAndModelID() {
     String s = super.getClassAndModelID();
     if (getOwner() == null) return s;
     String id = (String) (getOwner().getUUID());
     return s + "|" + id;
  }

	// needs-more-work: should be overwritten by each subclass of UMLDiagram
	public MModelElement  getOwner() { return _namespace; }
    
  public void setName(String n) throws PropertyVetoException {
    super.setName(n);
    _diagramName.updateName();
  }

  static final long serialVersionUID = -401219134410459387L;

} /* end class UMLDiagram */
