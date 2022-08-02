/*
 *
 * ====================================================================
 * 
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution, if
 *    any, must include the following acknowlegement:  
 *       "This product includes software developed by the 
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowlegement may appear in the software itself,
 *    if and wherever such third-party acknowlegements normally appear.
 *
 * 4. The names "The Jakarta Project", "Tomcat", and "Apache Software
 *    Foundation" must not be used to endorse or promote products derived
 *    from this software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
 *    permission of the Apache Group.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 */ 

package org.apache.jasper.compiler;

import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;
import java.util.StringTokenizer;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.File;
import java.io.ObjectOutputStream;
import java.io.FileOutputStream;
import java.net.URL;
import java.net.MalformedURLException;

import javax.servlet.jsp.tagext.TagInfo;
import javax.servlet.jsp.tagext.TagLibraryInfo;

import org.apache.jasper.JasperException;
import org.apache.jasper.Constants;
import org.apache.jasper.JspCompilationContext;

/**
 * Generates original "Jakarta"-style comments
 *
 * @author Mandar Raje [patch submitted by Yury Kamen]
 */
public class JakartaCommentGenerator implements CommentGenerator {
    
    // -------------------- Generate comments --------------------
    // The code generator also maintains line number info.

    // JakartaCommentGenerator can generate the line numbers
    // ( the way it generates the comments )
    JspLineMapItem lineMapItem;

    /**
     * Generates "start-of the JSP-embedded code block" comment
     *
     * @param out The ServletWriter
     * @param start Start position of the block
     * @param stop End position of the block
     * @exception JasperException 
     */
    public void generateStartComment(Generator generator, ServletWriter out, 
                                     Mark start, Mark stop) 
        throws JasperException 
    {
	String html = "";

        if (generator instanceof CharDataGenerator) {
	   html = "// HTML ";
	}
 	if (start != null && stop != null) {
	    if (start.fileid == stop.fileid) {
		String fileName = out.quoteString(start.getFile ());
		out.println(html + "// begin [file=" + fileName+";from=" + start.toShortString() + ";to=" + stop.toShortString() + "]");
	    } else {
		out.println(html + "// begin [from="+start+";to="+stop+"]");
            }
	} else {
	    out.println(html + "// begin");
        }

        // add the jsp to servlet line mappings
        lineMapItem = new JspLineMapItem();
        lineMapItem.setBeginServletLnr(out.getJavaLine());

        out.pushIndent();
    }

   /**
     * Generates "end-of the JSP-embedded code block" comment
     *
     * @param out The ServletWriter
     * @param start Start position of the block
     * @param stop End position of the block
     * @exception JasperException
     */
    public void generateEndComment(Generator generator, ServletWriter out, Mark start, Mark stop) throws JasperException {

	out.popIndent();
        out.println("// end");

        JspLineMap myLineMap = out.getLineMap();

        // add the jsp to servlet line mappings
        lineMapItem.setEndServletLnr(out.getJavaLine());
        lineMapItem.setStartJspFileNr(myLineMap.addFileName(start.getSystemId()));
        lineMapItem.setBeginJspLnr(start.getLineNumber() + 1);
        lineMapItem.setBeginJspColNr(start.getColumnNumber() + 1);
        lineMapItem.setStopJspFileNr(myLineMap.addFileName(stop.getSystemId()));
        lineMapItem.setEndJspLnr(stop.getLineNumber() + 1);
        lineMapItem.setEndJspColNr(stop.getColumnNumber() + 1);

        myLineMap.add(lineMapItem);
    }


    // The format may change
    private String toShortString( Mark mark ) {
        return "("+mark.getLineNumber() + ","+mark.getColumnNumber() +")";
    }

    //
    private String toString( Mark mark ) {
        return mark.getSystemId()+"("+mark.getLineNumber()+","+mark.getColumnNumber() +")";
    }


}
//        String fileName = "null";
//         if(start != null) {
//              fileName = out.quoteString(start.getFile());
//         }
//         String startString = "null";
//         if(null != start) {
//            startString =  start.toShortString();
//         }

//         String stopString = "null";
//         if(null != stop) {
//            stopString =  stop.toShortString();
//         }
//         out.println("// begin [file="+fileName+";from="+startString+";to="+stopString+"]");
