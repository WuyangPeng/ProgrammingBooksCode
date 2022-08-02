<%@page contentType="text/html"%>
<html>
<head><TITLE>Regular Expression Test Page</TITLE></head>
<body>

<%-- <jsp:useBean id="beanInstanceName" scope="session" class="package.class" /> --%>
<%-- <jsp:getProperty name="beanInstanceName"  property="propertyName" /> --%>
<%@ page import = "java.util.regex.*"%>
<%@ page import = "java.util.*"%>
<!--- Some styles to make the page look nice --->
<STYLE>
  BODY {font-family:arial;font-size:12px}
  INPUT {font-size:11px}
  TEXTAREA {font-size:11px}
  TH {background:#8888FF;color:white;text-align:left}
  TD {background:#CCCC99;color:black;font-size:12px}
  TD.RowA {background:#CCCC99}
  TD.RowB {background:#EEEEBB}
  .header {font-weight:bold}
</STYLE>
<SCRIPT LANGUAGE="JavaScript">
// Turn off fields used only by replace
function hideReplaceFields() {
  document.getElementById('RegExReplace').disabled=true;
  document.getElementById('replaceheader').disabled=true;
}

// Turn on fields used only by replace
function showReplaceFields() {
  document.getElementById('RegExReplace').disabled=false;
  document.getElementById('replaceheader').disabled=false;
}
</SCRIPT>
<%
    String operation = request.getParameter("operation");
    String isFormSubmitted = request.getParameter("cmd_submit");
    String strRegEx = (request.getParameter("RegEx")!=null)?request.getParameter("RegEx"):"";
    String strSearchText = (request.getParameter("SearchText")!=null)?request.getParameter("SearchText"):"";
    String strRegExReplace = (request.getParameter("RegExReplace")!=null)?request.getParameter("RegExReplace"):"";
    String strCaseSensitive = (request.getParameter("CaseSensitive")!=null)?"checked":"";
    String checkedFind = "";
    String checkedReplace = "";
    if (operation == null){
        checkedFind = "checked";
    }
    else {
        checkedReplace = (operation.equals("replace"))?"checked":"";
        checkedFind = (operation.equals("find"))?"checked":"";
    }
    
%>
<FORM NAME="tester" ACTION="regextester.jsp" METHOD="post">
<TABLE BORDER="1" CELLPADDING="4" CELLSPACING="0" WIDTH="550">
<TR> 
	<TH CLASS="Dialog">Regular Expression Tester</TH>
</TR>
<TR> 
	<TD CLASS="Dialog"> 
		<SPAN CLASS="header">Enter a regular expression:</SPAN><BR>
		<INPUT NAME="RegEx" TYPE="Text" SIZE="65" STYLE="font-size:13px" VALUE="<%=HTMLEditFormat(strRegEx)%>">
		<INPUT TYPE="Checkbox" NAME="CaseSensitive" ID="CaseSensitive" VALUE="True" <%=strCaseSensitive%>>
		<LABEL FOR="CaseSensitive">Case sensitive</LABEL>
		<BR>
	  
		<INPUT TYPE="Radio" NAME="operation" ID="OperationFind" VALUE="find" onClick="hideReplaceFields()" <%=checkedFind%>>
		<LABEL FOR="OperationFind">Find</LABEL>
	  	  
		<INPUT TYPE="Radio" NAME="operation" ID="OperationReplace" VALUE="replace" onClick="showReplaceFields()" <%=checkedReplace%>>
		<LABEL FOR="OperationReplace">Replace</LABEL>
		<BR>

      
		<SPAN CLASS="header" ID="replaceheader">Enter the replace regular expression:</SPAN><BR>
		<INPUT ID="RegExReplace" NAME="RegExReplace" TYPE="Text" SIZE="65" STYLE="font-size:13px" VALUE="<%=HTMLEditFormat(strRegExReplace)%>">
		<BR>
		<BR>

		<SPAN CLASS="header">And the text you wish to search:</SPAN><BR>
		<TEXTAREA NAME="SearchText" WRAP="off" COLS="70" ROWS="6"><%=HTMLEditFormat(strSearchText)%></TEXTAREA>
		<BR>

		<INPUT TYPE="Submit" VALUE="Match Now" name="cmd_submit" STYLE="font-weight:bold">
	</TD>
</TR>
</TABLE>
</FORM>
<%
if ((isFormSubmitted != null) && (strSearchText.trim().length() > 0)){
    if (strSearchText.substring(0,4).equals("(?m)")){
        strSearchText = AdjustNewlinesToLinefeeds(request.getParameter("SearchText"));
    }
    if ((operation.equals("find")) && (strRegEx.trim().length() > 0)){
        Vector resultVector = new Vector();
         if (strCaseSensitive.equals("checked")){
            resultVector = REFindMatches(strRegEx,strSearchText,true);
        }
        else {
            resultVector = REFindMatches(strRegEx,strSearchText,false);
        }
        if (resultVector.size() > 0){
            Iterator thisIterator = resultVector.iterator();
            %>
            Matched found : <%=resultVector.size()%>
            <DIV STYLE="height:200px;overflow-y:auto;width:550"> 
            <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">
            <TR>
                <TH WIDTH="*">Match</TH>  
                <TH WIDTH="75">Position</TH>
                <TH WIDTH="75">Length</TH>
            </TR>
            <%
            String CSSClass = "RowB";
            while (thisIterator.hasNext()){
                Hashtable test = (Hashtable)thisIterator.next();
                CSSClass = (CSSClass.equals("RowB"))?"RowA":"RowB";
                %>
                <tr>
                    <td class='<%=CSSClass%>'><%=HTMLEditFormat(test.get("String").toString().trim())%></td>
                    <td class='<%=CSSClass%>'><%=test.get("Position").toString().trim()%></td>
                    <td class='<%=CSSClass%>'><%=test.get("Length").toString().trim()%></td>
                </tr>

            <%}
            %>
            </table>
            </div>
            <%
       }
    }
    else if ((operation.equals("replace")) && (strSearchText.trim().length() > 0) && (strRegExReplace.trim().length() > 0)){
        String strResult = "";
        if (strCaseSensitive.equals("checked")){
            strResult = REReplace(strRegEx,strSearchText,strRegExReplace);
        }
        else {
            strResult = REReplaceNoCase(strRegEx,strSearchText,strRegExReplace);
        }
        if (strResult.length() > 0){%>
            <DIV STYLE="height:200px;overflow-y:auto;width:550"> 
                <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">		
                    <TR><TH>New Text</TH></TR>
                    <TR><TD><%= HTMLEditFormat(strResult)%></TD></TR>
                </Table>
            </div>
       <%}
    }
}
%>
<SCRIPT LANGUAGE="JavaScript">
<% 
if (operation == null){
%>
    hideReplaceFields();
 <% } else {
        if (operation.equals("find")){%>
            hideReplaceFields();
        <%}
         else {
         %>
           showReplaceFields();
        <%
        }
}
%>
</script>
<%!
    /*'***************************************************************************
     Regular Expression find method (just as a REFindMatches n CF)
    '****************************************************************************/
    public Vector REFindMatches(String strRE, String strString,boolean blnCaseSensitive){
	Vector returnVector = new Vector();
	Pattern pattern;
	if (blnCaseSensitive){
		pattern = Pattern.compile(strRE);
	}
	else {
		pattern = Pattern.compile(strRE,Pattern.CASE_INSENSITIVE);
	}
	CharSequence inputStr = strString;
	Matcher matcher = pattern.matcher(inputStr);
	boolean matchFound = matcher.find();   
	if (matchFound){
            while (matchFound){
                Hashtable myHashTable = new Hashtable();
                int start = matcher.start();   
                int end = matcher.end();
                myHashTable.put("String",inputStr.subSequence(start,end).toString());
                myHashTable.put("Position","" + (start+1) + "");
                myHashTable.put("Length","" + (end - start) + "");
                returnVector.addElement(myHashTable);
                matchFound = matcher.find();
            }
	}
	return returnVector;
    }

    /*'***************************************************************************
     Regular expression replace function for JSP (just as REReplace for CF)
    '****************************************************************************/
    public String REReplace(String strRE, String strString, String strSubString){
	Pattern pattern = Pattern.compile(strRE);
	CharSequence inputStr = strString;
	Matcher matcher = pattern.matcher(inputStr);
	return matcher.replaceAll(strSubString);
    }

    /*'***************************************************************************
     Regular Expression Case Insensitive Replace method (just as a REReplaceNoCase for CF)
    '****************************************************************************/
    public String REReplaceNoCase(String strRE, String strString, String strSubString){
	Pattern pattern = Pattern.compile(strRE,Pattern.CASE_INSENSITIVE);
	CharSequence inputStr = strString;
	Matcher matcher = pattern.matcher(inputStr);
	return matcher.replaceAll(strSubString);
    }

    /*'***************************************************************************
     Regular Expression HTML Stripping function (just as a HTMLEditFormat in CF)
    '****************************************************************************/
    public String HTMLEditFormat(String HTMLstring){
	Pattern p = Pattern.compile("<[^>]+>",Pattern.CASE_INSENSITIVE);
	Matcher m = p.matcher(HTMLstring);
	return m.replaceAll("");
    }

    /*'***************************************************************************
     AdjustNewlinesToLinefeeds for JSP (just as AdjustNewlinesToLinefeeds in CF)
    '****************************************************************************/
    public String AdjustNewlinesToLinefeeds(String strString){
	String first = "" + (char)13 + (char)10;
	String second = "" + (char)10;
	return REReplace(strString,first,second);
    }   
%>
</body>
</html>

