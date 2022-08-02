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

package org.argouml.xml;

import org.argouml.application.api.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;
import java.util.Stack;
import java.net.URL;
import java.io.*;
import org.xml.sax.*;
import javax.xml.parsers.SAXParserFactory;
import javax.xml.parsers.SAXParser;

/**
 * @author Jim Holt
 */

public abstract class SAXParserBase extends HandlerBase {

  ////////////////////////////////////////////////////////////////
  // constants

  protected static final String    _returnString  = new String("\n      ");

  ////////////////////////////////////////////////////////////////
  // constructors

  public SAXParserBase() {}

  ////////////////////////////////////////////////////////////////
  // static variables

  protected static  boolean       _dbg           = false;
  protected static  boolean       _verbose       = false;

  private   static  XMLElement    _elements[]    = new XMLElement[100];
  private   static  int           _nElements     = 0;
  private   static  XMLElement    _freeElements[]= new XMLElement[100];
  private   static  int           _nFreeElements = 0;
  private   static  boolean       _stats         = true;
  private   static  long          _parseTime     = 0;

  ////////////////////////////////////////////////////////////////
  // instance variables

  protected         boolean       _startElement  = false;

  ////////////////////////////////////////////////////////////////
  // accessors

  public void    setDebug(boolean debug) { _dbg = debug; }
  public void    setStats(boolean stats) { _stats = stats; }
  public boolean getStats()              { return _stats; }
  public long    getParseTime()          { return _parseTime; }

  ////////////////////////////////////////////////////////////////
  // main parsing method

  public void parse(URL url) throws Exception {
      parse(url.openStream());
  }

  public void parse(InputStream is) throws Exception {

    long start, end;

    SAXParserFactory factory = SAXParserFactory.newInstance();
    factory.setNamespaceAware(false);
    factory.setValidating(false);
    try {
      SAXParser parser = factory.newSAXParser();
      InputSource input = new InputSource(is);

      // what is this for?
      // input.setSystemId(url.toString());
      start = System.currentTimeMillis();
      parser.parse(input,this);
      end = System.currentTimeMillis();
      _parseTime = end - start;
      if (_stats) {
	Argo.log.info("Elapsed time: " + (end - start) + " ms");
      }
    } 
    catch(SAXException saxEx) {
        //
        //  a SAX exception could have been generated
        //    because of another exception.
        //    Get the initial exception to display the 
        //    location of the true error
        Exception ex = saxEx.getException();
        if(ex == null) {
            saxEx.printStackTrace();
        }
        else {
            ex.printStackTrace();
        }
    }
    catch (Exception se) {
      se.printStackTrace();
    }
  }

  ////////////////////////////////////////////////////////////////
  // abstract methods

  protected abstract void handleStartElement(XMLElement e);
  protected abstract void handleEndElement(XMLElement e);

  ////////////////////////////////////////////////////////////////
  // non-abstract methods

  public void startElement(String name, AttributeList atts)
       throws SAXException {
    _startElement = true;
    XMLElement e = null;
    if (_nFreeElements > 0) {
      e = _freeElements[-- _nFreeElements];
      e.setName(name);
      e.setAttributes(atts);
      e.resetText();
    }
    else e = new XMLElement(name, atts);

    if (_dbg) {
      System.out.println("START: " + name + " " + e);
      for (int i = 0; i < atts.getLength(); i++) {
	System.out.println("   ATT: " + atts.getName(i) + " " +
			   atts.getValue(i));
      }
    }

    _elements[_nElements++] = e;
    handleStartElement(e);
    _startElement = false;
  }

  public void endElement(String name) throws SAXException {
    XMLElement e = _elements[-- _nElements];
    if (_dbg) {
      System.out.println("END: " + e.getName() + " [" +
			 e.getText() + "] " + e);
      for (int i = 0; i < e.getNumAttributes(); i++) {
	System.out.println("   ATT: " + e.getAttributeName(i) + " " +
			   e.getAttributeValue(i));
      }
    }
    handleEndElement(e);
    _freeElements[_nFreeElements++] = e;
  }

  public void characters(char[] ch,int start,int length) throws SAXException {
    for (int i = 0; i < _nElements; i++) {
      XMLElement e = _elements[i];
      String test = e.getText();
      if (test.length() > 0)
	e.addText(_returnString);
      e.addText(new String(ch, start, length));
    }
  }


  public InputSource resolveEntity (String publicId, String systemId) {
    try {
      URL testIt = new URL(systemId);
      InputSource s = new InputSource(testIt.openStream());
      return s;
    } catch (Exception e) {
      if (_dbg || _verbose) {
	System.out.println("NOTE: Could not open DTD " + systemId);
      }
      String dtdName = systemId.substring(systemId.lastIndexOf('/')+1);
      String dtdPath = "/org/argouml/xml/dtd/" + dtdName;
      InputStream is = SAXParserBase.class.getResourceAsStream(dtdPath);
      if(is == null) {
        try {
            is = new FileInputStream(dtdPath.substring(1));
        }
        catch(Exception ex) {
        }
      }
      return new InputSource(is);
    }
  }

  ////////////////////////////////////////////////////////////////
  // convenience methods

  public void ignoreElement(XMLElement e) {
    System.out.println("NOTE: ignoring tag:" + e.getName());
  }

  public void notImplemented(XMLElement e) {
    System.out.println("NOTE: element not implemented: " + e.getName());
  }
} /* end class SAXParserBase */
