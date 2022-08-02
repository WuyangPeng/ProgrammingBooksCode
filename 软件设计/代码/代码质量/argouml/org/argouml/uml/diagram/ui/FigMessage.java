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

// File: FigMessage.java
// Original Author: agauthie@ics.uci.edu
// $Id: FigMessage.java,v 1.4 2001/10/12 20:20:31 thierrylach Exp $

package org.argouml.uml.diagram.ui;

import java.awt.*;
import java.util.*;
import java.beans.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.data_types.*;
import ru.novosoft.uml.behavior.collaborations.*;
import ru.novosoft.uml.behavior.common_behavior.*;

import org.tigris.gef.presentation.*;
import org.tigris.gef.graph.*;
import org.tigris.gef.base.PathConvPercent;
import org.tigris.gef.base.Layer;

import org.argouml.application.api.*;
import org.argouml.kernel.*;
import org.argouml.ui.*;
import org.argouml.uml.generator.*;
import org.argouml.uml.diagram.collaboration.ui.FigAssociationRole;

/** Class to display graphics for a UML collaboration in a diagram. */

public class FigMessage extends FigNodeModelElement {

  ////////////////////////////////////////////////////////////////
  // constants
  public int PADDING = 5;
  public static Vector ARROW_DIRECTIONS = new Vector();

  ////////////////////////////////////////////////////////////////
  // instance variables

  protected FigPoly _figPoly;
  protected int _arrowDirection = 0;
  //protected Polygon _polygon;

  ////////////////////////////////////////////////////////////////
  // constructors

  public FigMessage() {
    _name.setLineWidth(0);
    _name.setMultiLine(true);
    _name.setFilled(false);
    Dimension nameMin = _name.getMinimumSize();
    _name.setBounds(10, 10, 90, nameMin.height);

    _figPoly = new FigPoly(Color.black, Color.black);
    int[] xpoints = {75,75,77,75,73,75};
    int[] ypoints = {33,24,24,15,24,24};
    Polygon polygon = new Polygon(xpoints, ypoints, 6);
    _figPoly.setPolygon(polygon);
    _figPoly.setBounds(100,10,5,18);

    ARROW_DIRECTIONS.addElement("North");
    ARROW_DIRECTIONS.addElement("South");
    ARROW_DIRECTIONS.addElement("East");
    ARROW_DIRECTIONS.addElement("West");

    // add Figs to the FigNode in back-to-front order
    addFig(_name);
    addFig(_figPoly);

    Rectangle r = getBounds();
    setBounds(r.x, r.y, r.width, r.height);
  }

  public FigMessage(GraphModel gm, Object node) {
    this();
    setOwner(node);
  }

  public String placeString() { return "new Message"; }

  public Object clone() {
    FigMessage figClone = (FigMessage) super.clone();
    Vector v = figClone.getFigs();
    figClone._name = (FigText) v.elementAt(0);
    figClone._figPoly = (FigPoly) v.elementAt(1);
    //figClone._polygon = (Polygon) _polygon.clone();
    return figClone;
  }



  ////////////////////////////////////////////////////////////////
  // Fig accessors

  public void setLineColor(Color col) {
    _figPoly.setLineColor(col);
    _name.setLineColor(col);
  }
  public Color getLineColor() { return _figPoly.getLineColor(); }

  public void setFillColor(Color col) {
    _figPoly.setFillColor(col);
    _name.setFillColor(col);
  }
  public Color getFillColor() { return _figPoly.getFillColor(); }

  public void setFilled(boolean f) {  }
  public boolean getFilled() { return true; }

  public void setLineWidth(int w) { _figPoly.setLineWidth(w); }
  public int getLineWidth() { return _figPoly.getLineWidth(); }

  public void setArrow(int direction) {
    Rectangle bbox = getBounds();
    
    _arrowDirection = direction;
    switch (direction) {
      // south
      case 1: {
        int[] xpoints = {75,75,77,75,73,75};
        int[] ypoints = {15,24,24,33,24,24};
        Polygon polygon = new Polygon(xpoints, ypoints, 6);
        _figPoly.setPolygon(polygon);
        break;
      }
      // east
      case 2: {
        int[] xpoints = {66,75,75,84,75,75};
        int[] ypoints = {24,24,26,24,22,24};
        Polygon polygon = new Polygon(xpoints, ypoints, 6);
        _figPoly.setPolygon(polygon);
        break;
      }
      // west
      case 3: {
        int[] xpoints = {84,75,75,66,75,75};
        int[] ypoints = {24,24,26,24,22,24};
        Polygon polygon = new Polygon(xpoints, ypoints, 6);
        _figPoly.setPolygon(polygon);
        break;
      }
      // north
      default: {
        int[] xpoints = {75,75,77,75,73,75};
        int[] ypoints = {33,24,24,15,24,24};
        Polygon polygon = new Polygon(xpoints, ypoints, 6);
        _figPoly.setPolygon(polygon);
      }
    }
    setBounds(bbox);
  }
  public int getArrow() { return _arrowDirection; }

  public Dimension getMinimumSize() {
    Dimension nameMin = _name.getMinimumSize();
    Dimension figPolyMin = _figPoly.getSize();

    int h = Math.max(figPolyMin.height, nameMin.height);
    int w = figPolyMin.width + nameMin.width;
    return new Dimension(w, h);
  }

  /* Override setBounds to keep shapes looking right */
  public void setBounds(int x, int y, int w, int h) {
    if (_name == null) return;

    Rectangle oldBounds = getBounds();

    Dimension nameMin = _name.getMinimumSize();

    int ht = 0;

    if (nameMin.height > _figPoly.getHeight()) 
      ht = (nameMin.height - _figPoly.getHeight()) / 2;

    _name.setBounds(x, y, w-_figPoly.getWidth(), nameMin.height);
    _figPoly.setBounds(x + _name.getWidth(), y + ht,
		       _figPoly.getWidth(), _figPoly.getHeight());

    firePropChange("bounds", oldBounds, getBounds());
    calcBounds(); //_x = x; _y = y; _w = w; _h = h;
    updateEdges();
  }

  protected void textEdited(FigText ft) throws PropertyVetoException {
    super.textEdited(ft);
    MMessage mes = (MMessage) getOwner();
    if (ft == _name) {
       String s = ft.getText();
       ParserDisplay.SINGLETON.parseMessage(mes, s);
    }
  }

  protected void modelChanged() {
    super.modelChanged();
    MMessage mes = (MMessage) getOwner();
    if (mes == null) return;
    String nameStr = Notation.generate(this, mes.getName()).trim();
	String actionString = "new Action";
	if (mes.getAction() != null && mes.getAction().getScript() != null 
		&&  mes.getAction().getScript().getBody() != null)
		actionString = (((MActionExpression)((MAction)mes.getAction()).getScript()).getBody()).trim();

//     System.out.println("nameStr = " + nameStr);
//     System.out.println("name = " + _name);
//     System.out.println("actionString = " + actionString);
    if( nameStr.equals("") && actionString.equals("") )
      _name.setText("");
    else
      _name.setText(nameStr.trim() + " : " + actionString);
  }

  public void dispose() {
    if (!(getOwner() instanceof MElement)) return;
    MElement elmt = (MElement) getOwner();
    Project p = ProjectBrowser.TheInstance.getProject();
    p.moveToTrash(elmt);
    super.dispose();
  }

  /** add the FigMessage to the Path Items of its FigAssociationRole */
  public void addPathItemToFigAssociationRole(Layer lay) {

    MAssociationRole ar = ((MMessage) getOwner()).getCommunicationConnection();
    if (ar != null && lay != null) {
      FigAssociationRole figAssocRole = (FigAssociationRole) lay.presentationFor(ar);
      if (figAssocRole != null) {
        Collection messages = ar.getMessages();
        int size=0;
        if (messages != null) {
          size = messages.size();
        }
        int percent = 15 + size*10;
        if (percent > 100) percent = 100;
        figAssocRole.addPathItem(this, new PathConvPercent(figAssocRole, percent, 10));
        figAssocRole.updatePathItemLocations();
        lay.bringToFront(this);
      }
    }
  }

 
} /* end class FigMessage */
