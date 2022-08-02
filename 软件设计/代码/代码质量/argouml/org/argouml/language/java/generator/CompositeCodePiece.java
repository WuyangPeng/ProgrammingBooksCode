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

/*
  JavaRE - Code generation and reverse engineering for UML and Java
  Author: Marcus Andersson andersson@users.sourceforge.net
*/


package org.argouml.language.java.generator;

import java.util.*;

/**
   This piece of code is a composition of several adjacent pieces of
   code. The code piece can have holes.
*/
public class CompositeCodePiece extends CodePiece
{
    /** The code pieces this code piece consists of. */
    private Vector codePieces;

    /**
       Create a composite piece of code.

       @param codePiece A starter code piece.
    */
    public CompositeCodePiece(CodePiece codePiece)
    {
	codePieces = new Vector();
	if(codePiece != null) {
	    codePieces.addElement(codePiece);
	}
    }

    /**
       Append a code piece to the end.
    */
    public void add(CodePiece codePiece)
    {
	if(codePiece != null) {
	    codePieces.addElement(codePiece);
	}
    }

    /**
       Return the string representation for this piece of code.
    */
    public String getText()
    {
	Iterator i = codePieces.iterator();
	CodePiece cp = (CodePiece)i.next();
	String text = cp.getText();
	int prevEnd = cp.getEndPosition();
	int prevLine = cp.getEndLine();

	for(; i.hasNext(); ) {
	    cp = (CodePiece)i.next();
	    int spaces = cp.getStartPosition() - prevEnd;
	    if(prevLine != cp.getStartLine()) {
		text += '\n';
		spaces--;
	    }
	    for(int j=0; j < spaces; j++) {
		text += ' ';
	    }
	    text += cp.getText();
	    prevEnd = cp.getEndPosition();
	    prevLine = cp.getEndLine();
	}
	return text;
    }

    /**
       Return the start position.
    */
    public int getStartPosition()
    {
	return ((CodePiece)codePieces.firstElement()).getStartPosition();
    }

    /**
       Return the end position.
    */
    public int getEndPosition()
    {
	return ((CodePiece)codePieces.lastElement()).getEndPosition();
    }

    /**
	Return the start line
    */
    public int getStartLine()
    {
	return ((CodePiece)codePieces.firstElement()).getStartLine();
    }

    /**
	Return the end line
    */
    public int getEndLine()
    {
	return ((CodePiece)codePieces.lastElement()).getEndLine();
    }
}
