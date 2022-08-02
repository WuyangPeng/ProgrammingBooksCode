<HTML>
<HEAD><TITLE>Regular Expression Test Page</TITLE></HEAD>
<BODY>
<% 
'****************************************************************************************
'File Name 	= resexptester.asp
'Author 	= Originally created by Nate Weiss and Ben Forta, modified by Qasim Rasheed
'Purpose	= An ASP page for crafting, testing, and debugging regular expressions
'*****************************************************************************************
%>

<STYLE>
  BODY {font-family:arial;font-size:12px}
  INPUT {font-size:11px}
  TEXTAREA {font-size:11px}
  TH {background:#8888FF;color:white;text-align:left}
  TD {background:#CCCC99;color:black;font-size:12px}
  TD.RowA {background:"blue"}
  TD.RowB {background:"silver"}
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
  
<FORM NAME="tester" ACTION="regextester.asp" METHOD="post">
<TABLE BORDER="1" CELLPADDING="4" CELLSPACING="0" WIDTH="550">
<TR> 
	<TH CLASS="">Regular Expression Tester</TH>
</TR>
<TR> 
	<TD CLASS=""> 
		<SPAN CLASS="header">Enter a regular expression:</SPAN><BR>
		<INPUT NAME="RegEx" TYPE="Text" SIZE="65" STYLE="font-size:13px" VALUE="<%=HTMLEditFormat(Request("RegEx"))%>">
		
		<%
			if request("CaseSensitive") = "" then
				lb_CaseSensitive = false 
			else
				lb_CaseSensitive = true 
			end if 
			checked = IIf(lb_CaseSensitive, "CHECKED","")%>
		<INPUT TYPE="Checkbox" NAME="CaseSensitive" ID="CaseSensitive" VALUE="True" <%=checked%>>
		<LABEL FOR="CaseSensitive">Case sensitive</LABEL>
		<BR>

		<%checked = IIf(request("Operation")= "find", "CHECKED","")%>	  
		<INPUT TYPE="Radio" NAME="Operation" ID="OperationFind" VALUE="find" <%=checked%> onClick="hideReplaceFields()">
		<LABEL FOR="OperationFind">Find</LABEL>

		<%checked = IIf(request("Operation")= "replace", "CHECKED","")%>	  	  
		<INPUT TYPE="Radio" NAME="Operation" ID="OperationReplace" VALUE="replace"  <%=checked%> onClick="showReplaceFields()">
		<LABEL FOR="OperationReplace">Replace</LABEL>
		<BR>

      
		<SPAN CLASS="header" ID="replaceheader">Enter the replace regular expression:</SPAN><BR>
		<INPUT ID="RegExReplace" NAME="RegExReplace" TYPE="Text" SIZE="65" STYLE="font-size:13px" VALUE="<%=HTMLEditFormat(Request("RegExReplace"))%>">
		<BR>
		<BR>

		<SPAN CLASS="header">And the text you wish to search:</SPAN><BR>
		<TEXTAREA NAME="SearchText" WRAP="off" COLS="70" ROWS="6"><%=HTMLEditFormat(request("SearchText"))%></TEXTAREA>
		<BR>

		<INPUT TYPE="Submit" VALUE="Match Now" name="cmd_submit" STYLE="font-weight:bold">
	</TD>
</TR>
</TABLE>
</FORM>


<%
'If the form is submitted
if request("cmd_submit") <> "" then

	'If the RegEx is using "multiline mode", adjust the text
	'so that only linefeed characters are used to separate lines
	If Left(request("RegEx"), 4) = "(?m)" then
		SearchText = AdjustNewlinesToLinefeeds(Request("SearchText"))
	End if 
  
	'on error resume next
  
	If Request("operation") = "find" then
		'Perform the regular expression search
		'Results are returned as a query object with three columns:
		'"Pos" - the position of the match
		'"Len" - the length of the match
		'"Found" - the actual text of the match
		set objRE = REFindMatches (request("RegEx"), request("SearchText"), lb_CaseSensitive)
	else
		if lb_CaseSensitive= true then
			ResultString=REReplace(request("SearchText"), request("RegEx"), request("RegExReplace"))
		else
			ResultString=REReplaceNoCase(request("SearchText"), request("RegEx") , request("RegExReplace"))
		end if 
    End if 
    
	If err.Description <> "" then
        Response.Write "<P><B>Sorry, there is a problem with your regular expression.</B><BR>"
        Response.Write "<STRONG>Error Description:</STRONG> " & Err.Description 
	end if 
	
	
	'Process display
	If Request("operation") = "find" then
	 	'Display the number of matches found
	 	Response.write "Matches Found: " &  objRE.Count & "<BR>"
		
	 	'If there is at least one match...
		if objRE.Count > 0 then
			'Display the matches in a simple HTML table%>
	 		<DIV STYLE="height:200px;overflow-y:auto;width:550"> 
	 		<TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">
			
	 		<TR>
	 			<TH WIDTH="*">Match</TH>  
	 			<TH WIDTH="75">Position</TH>
	 			<TH WIDTH="75">Length</TH></TR>
	 		</TR>
				  
	 		<% For Each objMatch in objRE
	 		  'Alternating row colors --->
	 		  CSSClass = IIF(CSSClass="'RowB'", "'RowA'", "'RowB'")%>
	 		  <TR>
	 			  <TD CLASS="<%=CSSClass%>" WIDTH="*"><%= HTMLEditFormat(objMatch.Value)%></TD>
	 			  <TD CLASS="<%=CSSClass%>" WIDTH="75"><%= objMatch.FirstIndex%></TD>
	 			  <TD CLASS="<%=CSSClass%>" WIDTH="75"><% = objMatch.Length %></TD>
	 		  </TR>
			<% Next %>
	 		</TABLE>
	 	<% End if %>

	<% Else 
	 	  'Display the matches in a simple HTML table%>
	 	  <DIV STYLE="height:200px;overflow-y:auto;width:550"> 
	 	  <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">		
	 		<TR><TH>New Text</TH></TR>
	 		<TR><TD><%= HTMLEditFormat(ResultString)%></TD></TR>
	 		</Table>
	 	  </div>
<%
	End if 
end if 
%>


<SCRIPT LANGUAGE="JavaScript">
<% If Request("operation") = "find" then %>
	hideReplaceFields();
<% else %>
	showReplaceFields();
<% End If %>
</SCRIPT>
  
</BODY>
</HTML>


<%
'***************************************************************************
'Immediate if function for ASP  (just as IIf for CF)
'***************************************************************************
Function IIf(i,j,k)
    if cbool(i) Then IIf = j Else IIf = k
End Function


'***************************************************************************
'Regular expression replace function for ASP (just as REReplace for CF)
'***************************************************************************
Function REReplace(rs_String, rs_RE, rs_SubString)
	Set RegularExpressionObject = New RegExp

	With RegularExpressionObject
	.Pattern = rs_RE
	.IgnoreCase = True
	.Global = True
	End With

	ReplacedString = RegularExpressionObject.Replace(rs_String, rs_SubString)
	Set RegularExpressionObject = nothing
	
	REReplace = ReplacedString
End Function

'***************************************************************************
'AdjustNewlinesToLinefeeds for ASP (just as AdjustNewlinesToLinefeeds in CF)
'***************************************************************************
Function AdjustNewlinesToLinefeeds(rs_String)
  var Result = REReplace(string, Chr(13)&Chr(10), Chr(10))
  Result = REReplace(string, Chr(13), Chr(10))

  AdjustNewlinesToLinefeeds = Result
End Function


'***************************************************************************
'Regular Expression find method (just as a REFindMatches n CF)
'***************************************************************************
Function REFindMatches(rs_RE, rs_String,rb_CaseSensitive)

	rb_CaseSensitive = iif(rb_CaseSensitive,false,true)
	
	Set RegularExpressionObject = New RegExp

	With RegularExpressionObject
		.Pattern = rs_RE
		.IgnoreCase = rb_CaseSensitive
		.Global = True
	End With

	Set expressionmatch = RegularExpressionObject.Execute(rs_String)

	set REFindMatches = expressionmatch
	
	set RegularExpressionObject = nothing 

End Function


'***************************************************************************
'Case Sensitive Regular Expression Replace method (just as a REReplace n CF)
'***************************************************************************
Function REReplace(rs_SearchString,rs_RE,rs_ReplaceString)

	Set RegularExpressionObject = New RegExp

	With RegularExpressionObject
	.Pattern = rs_RE
	.IgnoreCase = false
	.Global = True
	End With

	ReplacedString = RegularExpressionObject.Replace(rs_SearchString,cstr(rs_ReplaceString))
	Set RegularExpressionObject = nothing

	REReplace = ReplacedString
End Function


'***************************************************************************
'Regular Expression Replace method (just as a REReplaceNoCase n CF)
'***************************************************************************
Function REReplaceNoCase(rs_SearchString,rs_RE,rs_ReplaceString)

	Set RegularExpressionObject = New RegExp

	With RegularExpressionObject
	.Pattern = rs_RE
	.IgnoreCase = true
	.Global = True
	End With

	ReplacedString = RegularExpressionObject.Replace(rs_SearchString,cstr(rs_ReplaceString))
	Set RegularExpressionObject = nothing

	REReplaceNoCase = ReplacedString
End Function


'***************************************************************************
'Regular Expression HTML Stripping function (just as a HTMLEditFormat in CF)
'***************************************************************************
Function HTMLEditFormat(HTMLstring)
	Set RegularExpressionObject = New RegExp

	With RegularExpressionObject
	.Pattern = "<[^>]+>"
	.IgnoreCase = True
	.Global = True
	End With

	HTMLEditFormat = RegularExpressionObject.Replace(HTMLstring, "")
	Set RegularExpressionObject = nothing
End Function

%>


