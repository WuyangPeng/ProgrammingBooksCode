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

// File: FigClassifierRole.java
// Original Author: agauthie@ics.uci.edu
// $Id: FigClassifierRole.java,v 1.5 2001/10/12 20:20:30 thierrylach Exp $

package org.argouml.uml.diagram.collaboration.ui;

import java.awt.*;
import java.util.*;
import java.beans.*;
import java.awt.event.*;
import javax.swing.*;

import ru.novosoft.uml.foundation.core.*;
import ru.novosoft.uml.foundation.extension_mechanisms.*;
import ru.novosoft.uml.behavior.collaborations.*;

import org.tigris.gef.presentation.*;
import org.tigris.gef.graph.*;

import org.argouml.application.api.*;
import org.argouml.language.helpers.*;
import org.argouml.kernel.*;
import org.argouml.ui.*;
import org.argouml.uml.generator.*;
import org.argouml.uml.diagram.ui.*;

/** Class to display graphics for a UML collaboration in a diagram. */

public class FigClassifierRole extends FigNodeModelElement {

  ////////////////////////////////////////////////////////////////
  // constants
  public int PADDING = 5;
  ////////////////////////////////////////////////////////////////
  // instance variables

  FigRect _bigPort;
  FigRect _cover;

  // add other Figs here aes needed

  ////////////////////////////////////////////////////////////////
  // constructors

  public FigClassifierRole() {
    _bigPort = new FigRect(10, 10, 90, 50, Color.cyan, Color.cyan);
    _cover = new FigRect(10, 10, 90, 50, Color.black, Color.white);
    _name.setLineWidth(0);
    _name.setMultiLine(true);
    _name.setFilled(false);
    _name.setUnderline(true);
    Dimension nameMin = _name.getMinimumSize();
    _name.setBounds(10, 10, 90, nameMin.height);

    _stereo.setLineWidth(0);
    _stereo.setFilled(false);
    _stereo.setJustifciaionByName("Center");
    Dimension stereoMin = _stereo.getMinimumSize();
    _stereo.setBounds(10, 10, 90, stereoMin.height);

    // add Figs to the FigNode in back-to-front order
    addFig(_bigPort);
    addFig(_cover);
    addFig(_stereo);
    addFig(_name);

    Rectangle r = getBounds();
    setBounds(r.x, r.y, r.width, r.height);
  }

  public FigClassifierRole(GraphModel gm, Object node) {
    this();
    setOwner(node);
  }

  public String placeString() { return "new ClassifierRole"; }

  public Object clone() {
    FigClassifierRole figClone = (FigClassifierRole) super.clone();
    Vector v = figClone.getFigs();
    figClone._bigPort = (FigRect) v.elementAt(0);
    figClone._cover = (FigRect) v.elementAt(1);
    figClone._stereo = (FigText) v.elementAt(2);
    figClone._name = (FigText) v.elementAt(3);
    return figClone;
  }


  protected void updateStereotypeText() {
    MModelElement me = (MModelElement) getOwner();
    if (me == null) return;
    _stereo.setText(Notation.generateStereotype(this, me.getStereotype()));
    Rectangle oldBounds = getBounds();
    _stereo.calcBounds();
    calcBounds();
    firePropChange("bounds", oldBounds, getBounds());
  
  }

  ////////////////////////////////////////////////////////////////
  // Fig accessors

  public void setLineColor(Color col) { _cover.setLineColor(col); }
  public Color getLineColor() { return _cover.getLineColor(); }

  public void setFillColor(Color col) { _cover.setFillColor(col); }
  public Color getFillColor() { return _cover.getFillColor(); }

  public void setFilled(boolean f) { _cover.setFilled(f); }
  public boolean getFilled() { return _cover.getFilled(); }

  public void setLineWidth(int w) { _cover.setLineWidth(w); }
  public int getLineWidth() { return _cover.getLineWidth(); }

  public void setOwner(Object node) {
    super.setOwner(node);
    Object onlyPort = node;
    bindPort(onlyPort, _bigPort);
	modelChanged();
  }

  public Dimension getMinimumSize() {
    Dimension bigPortMin = _bigPort.getMinimumSize();
    Dimension coverMin = _cover.getMinimumSize();
    Dimension nameMin = _name.getMinimumSize();

    int h = Math.max(bigPortMin.height, Math.max(coverMin.height, nameMin.height + PADDING*2));
    int w = Math.max(bigPortMin.width, Math.max(coverMin.width, nameMin.width + PADDING * 2));
    return new Dimension(w, h);
  }

  /* Override setBounds to keep shapes looking right */
  public void setBounds(int x, int y, int w, int h) {
    if (_name == null) return;

    Rectangle oldBounds = getBounds();
    _bigPort.setBounds(x, y, w, h);
    _cover.setBounds(x, y, w, h);

    Dimension nameMin = _name.getMinimumSize();

    int extra_each = (h - nameMin.height) / 2;

    _name.setBounds(x+1, y+extra_each, w-2, nameMin.height);
    //_bigPort.setBounds(x+1, y+1, w-2, h-2);
    _x = x; _y = y; _w = w; _h = h;

    firePropChange("bounds", oldBounds, getBounds());
    calcBounds(); //_x = x; _y = y; _w = w; _h = h;
    updateEdges();
  }

  
  ////////////////////////////////////////////////////////////////
  // event handlers

  protected void textEdited(FigText ft) throws PropertyVetoException {
	  // super.textEdited(ft);
    MClassifierRole cls = (MClassifierRole) getOwner();
    if (ft == _name) {
       String s = ft.getText();
       // System.out.println("S ist: "+s);
      ParserDisplay.SINGLETON.parseClassifierRole(cls, s);
    }
  }

  protected void modelChanged() {
    super.modelChanged();
    MClassifierRole cr = (MClassifierRole) getOwner();
    if (cr == null) return;
    String nameStr = Notation.generate(this, cr.getName()).trim();
    String baseString = "";
    if (cr.getBases() != null && cr.getBases().size()>0) {
	Vector bases = new Vector(cr.getBases());
	baseString += ((MClassifier)bases.elementAt(0)).getName();
        for(int i=1; i<bases.size(); i++)
	    baseString += ", "  + ((MClassifier)bases.elementAt(i)).getName();
    }

    if (_readyToEdit) {
      if( nameStr == "" && baseString == "")
	_name.setText("");
      else
	_name.setText(nameStr.trim() + " : " + baseString);
    }
  }

//  public void keyPressed(KeyEvent ke) {}

  public void dispose() {
    if (!(getOwner() instanceof MElement)) return;
    MElement elmt = (MElement) getOwner();
    Project p = ProjectBrowser.TheInstance.getProject();
    p.moveToTrash(elmt);
    super.dispose();
  }



} /* end class FigClassifierRole */
