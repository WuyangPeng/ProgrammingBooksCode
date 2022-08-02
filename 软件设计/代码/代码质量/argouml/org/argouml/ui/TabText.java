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

package org.argouml.ui;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.tree.*;
import javax.swing.text.*;

import org.argouml.uml.ui.*;

/** A tab that contains textual information.
 */
public class TabText extends TabSpawnable
implements TabModelTarget, DocumentListener {
  ////////////////////////////////////////////////////////////////
  // instance variables
  protected Object _target;
  protected JTextArea _text = new JTextArea();
  protected boolean _parseChanges = true;
  protected boolean _shouldBeEnabled = false;
  /** The optional toolbar.
   *  Contains null if no toolbar was requested.
   */
  protected JToolBar _toolbar = null;

  ////////////////////////////////////////////////////////////////
  // constructor

  /** Create a text tab without a toolbar.
   */
  public TabText(String title) {
      this(title, false);
  }

  /** Create a text tab and optionally request a toolbar.
   *  @since ARGO0.9.4
   */
  public TabText(String title, boolean withToolbar) {
    super(title);
    setLayout(new BorderLayout());
    _text.setFont(new Font("Monospaced", Font.PLAIN, 12));
    _text.setTabSize(4);
    add(new JScrollPane(_text), BorderLayout.CENTER);
    _text.getDocument().addDocumentListener(this);

    // If a toolbar was requested, create an empty one.
    if (withToolbar) {
        _toolbar = new JToolBar();
        _toolbar.setFloatable(false);
        _toolbar.setOrientation(JToolBar.HORIZONTAL);
        add(_toolbar, BorderLayout.NORTH);
    }
  }

  ////////////////////////////////////////////////////////////////
  // accessors

  public void setTarget(Object t) {
    _target = t;
    _parseChanges = false;
    if (_target == null) {
      _text.setEnabled(false);
      _text.setText("Nothing selected");
      _shouldBeEnabled = false;
    }
    else {
      _text.setEnabled(true);
      String generatedText = genText();
      if (generatedText != null) {
	_text.setText(generatedText);
	_shouldBeEnabled = true;
	_text.setCaretPosition(0);
      }
      else {
	_text.setEnabled(false);
	_text.setText("N/A");
	_shouldBeEnabled = false;
      }
    }
    _parseChanges = true;
  }

  public Object getTarget() { return _target; }

  public void refresh() { setTarget(_target); }

  public boolean shouldBeEnabled() { return _shouldBeEnabled; }

  protected String genText() {
    if (_target == null) return "nothing selected";
    return _target.toString();
  }

  protected void parseText(String s) {
    if (s == null) s = "(null)";
    System.out.println("parsing text:" + s); // THN
  }

  ////////////////////////////////////////////////////////////////
  // event handlers
  public void insertUpdate(DocumentEvent e) {
    //needs-more-work: should fire its own event and ProjectBrowser
    //should register a listener
    //System.out.println(getClass().getName() + " insert");
    if (_parseChanges) parseText(_text.getText());
  }

  public void removeUpdate(DocumentEvent e) {
    //needs-more-work: should fire its own event and ProjectBrowser
    //should register a listener
    //System.out.println(getClass().getName() +  " remove");
    if (_parseChanges) parseText(_text.getText());
  }

  public void changedUpdate(DocumentEvent e) {
    //needs-more-work: should fire its own event and ProjectBrowser
    //should register a listener
    //System.out.println(getClass().getName() + " changed");
    if (_parseChanges) parseText(_text.getText());
  }

} /* end class TabText */
