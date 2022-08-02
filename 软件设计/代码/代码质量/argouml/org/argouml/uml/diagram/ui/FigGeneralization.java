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

// File: FigGeneralization.java
// Classes: FigGeneralization
// Original Author: abonner@ics.uci.edu
// $Id: FigGeneralization.java,v 1.1.1.1 2000/09/04 12:50:18 1sturm Exp $

package org.argouml.uml.diagram.ui;

import java.awt.*;
import java.beans.*;
import java.util.*;

import ru.novosoft.uml.foundation.core.*;
//import ru.novosoft.uml.foundation.extension_mechanisms.*;

import org.tigris.gef.base.*;
import org.tigris.gef.presentation.*;

public class FigGeneralization extends FigEdgeModelElement {

  ////////////////////////////////////////////////////////////////
  // constructors

  public FigGeneralization() {
    addPathItem(_stereo, new PathConvPercent(this, 50, 10));
    ArrowHeadTriangle endArrow = new ArrowHeadTriangle();
    endArrow.setFillColor(Color.white);
    setDestArrowHead(endArrow);
    setBetweenNearestPoints(true);
  }

  public FigGeneralization(Object edge) {
    this();
    setOwner(edge);
  }

  protected boolean canEdit(Fig f) { return false; }

  ////////////////////////////////////////////////////////////////
  // event handlers

  /** This is called aftern any part of the UML MModelElement has
   *  changed. This method automatically updates the name FigText.
   *  Subclasses should override and update other parts. */
  protected void modelChanged() {
    // do not set _name
    updateStereotypeText();
  }



} /* end class FigGeneralization */

