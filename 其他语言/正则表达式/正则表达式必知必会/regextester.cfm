<!-- 
  Filename: RegExTester.cfm
  Author:   Originally created by Nate Weiss, modified by Ben Forta.
            Also modified by Shaene M. Siders, http://www.DragonUnderGlass.com.
  Purpose:  A page for crafting, testing, and debugging regular expressions
-->

<!--- Some UDFs --->

<!--- REFindMatches() function --->
<CFFUNCTION NAME="REFindMatches" RETURNTYPE="query">
  <!--- Function arguments --->
  <CFARGUMENT NAME="RegEx" TYPE="string" REQUIRED="Yes">
  <CFARGUMENT NAME="String" TYPE="string" REQUIRED="Yes">
  <CFARGUMENT NAME="CaseSensitive" TYPE="boolean" REQUIRED="No" DEFAULT="No">

  <!--- Local variables (visible to this function only) --->
  <CFSET var QueryColNames = "Found,Len,Pos">  
  <CFSET var Result = QueryNew(QueryColNames)>
  <CFSET var StartPos = 1>
  <CFSET var RegExMatch = "">
  
  <!--- Begin looping: this continues looping until a <CFBREAK> tag --->
  <!--- The first time through this loop will find the first match, --->
  <!--- the second iteration will find the second match, and so on. --->
  <CFLOOP CONDITION="true">
    <!--- Perform the actual regular expression search --->
    <!--- Use the case sensitive or insensitive function as appropriate --->
    <CFIF ARGUMENTS.CaseSensitive>
      <CFSET RegExMatch = REFind(RegEx, String, StartPos, "Yes")>
    <CFELSE>
      <CFSET RegExMatch = REFindNoCase(RegEx, String, StartPos, "Yes")>
    </CFIF>

    <!--- If a match was found --->  
    <CFIF RegExMatch.len[1] GT 0>

      <!--- Add a row to the Result query --->
      <CFSET QueryAddRow(Result, 1)>
      <CFSET QuerySetCell(Result, "Pos", RegExMatch.pos[1])>
      <CFSET QuerySetCell(Result, "Len", RegExMatch.len[1])>
      <CFSET QuerySetCell(Result, "Found", Mid(String, RegExMatch.pos[1], RegExMatch.len[1]))>
      
      <!--- Advance the StartPos variable, so that the next --->      
      <!--- iteration of the loop will start right after this match --->
      <CFSET StartPos = RegExMatch.pos[1] + RegExMatch.len[1]>

    <!--- If no match was found, then our work here is done --->
    <CFELSE>
      <CFBREAK>  
    </CFIF>
  </CFLOOP>  
  
  <!--- Return the completed query object --->
  <CFRETURN Result>
</CFFUNCTION>

<!--- AdjustNewlinesToLinefeeds() function --->
<CFFUNCTION NAME="AdjustNewlinesToLinefeeds" RETURNTYPE="string">
  <!--- argument: string --->
  <CFARGUMENT NAME="string" TYPE="string" REQUIRED="Yes">
  
  <!--- Replace all CRLF sequences with just LF --->
  <CFSET var Result = REReplace(string, Chr(13)&Chr(10), Chr(10), "ALL")>
  <!--- Replace any remaining CR characters with LF --->
  <CFSET Result = REReplace(string, Chr(13), Chr(10), "ALL")>
  
  <!--- Return the result --->
  <CFRETURN Result>
</CFFUNCTION>


<!--- Form parameters --->
<CFPARAM NAME="FORM.RegEx" TYPE="string" DEFAULT="">
<CFPARAM NAME="FORM.RegExReplace" TYPE="string" DEFAULT="">
<CFPARAM NAME="FORM.SearchText" TYPE="string" DEFAULT="">
<CFPARAM NAME="FORM.CaseSensitive" TYPE="boolean" DEFAULT="No">
<CFPARAM NAME="FORM.Operation" TYPE="string" DEFAULT="find">


<!--- Obtain the filename of the current ColdFusion page --->
<CFSET CurrentPage = GetFileFromPath(GetBaseTemplatePath())>


<HTML>
<HEAD><TITLE>Regular Expression Test Page</TITLE></HEAD>
<BODY>

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


<CFOUTPUT>
  <!--- Create a self-submitting form --->
  <FORM NAME="tester" ACTION="#CurrentPage#" METHOD="post">
    
  <TABLE BORDER="1" CELLPADDING="4" CELLSPACING="0" WIDTH="550">
    <TR> 
      <TH CLASS="Dialog">Regular Expression Tester</TH>
    </TR>
    <TR> 
    <TD CLASS="Dialog"> 
    
      <!--- Text input for the regular expression itself --->
      <SPAN CLASS="header">Enter a regular expression:</SPAN><BR>
      <INPUT NAME="RegEx" TYPE="Text" SIZE="65" STYLE="font-size:13px" VALUE="#HTMLEditFormat(FORM.RegEx)#">

       <!--- Checkbox to control case-sensitivity --->
	  <CFSET checked = IIf(FORM.CaseSensitive, DE("CHECKED"), DE(""))>
      <INPUT TYPE="Checkbox" NAME="CaseSensitive" ID="CaseSensitive" VALUE="Yes" #checked#>
      <LABEL FOR="CaseSensitive">Case sensitive</LABEL>
      <BR>

      <!--- Radio buttons to display find vs. replace --->
	  <CFSET checked = IIf(FORM.operation IS "find", DE("CHECKED"), DE(""))>
      <INPUT TYPE="Radio" NAME="Operation" ID="OperationFind" VALUE="find" #checked# onClick="hideReplaceFields()">
      <LABEL FOR="OperationFind">Find</LABEL>
	  <CFSET checked = IIf(FORM.operation IS "replace", DE("CHECKED"), DE(""))>
      <INPUT TYPE="Radio" NAME="Operation" ID="OperationReplace" VALUE="replace" #checked# onClick="showReplaceFields()">
      <LABEL FOR="OperationReplace">Replace</LABEL>
      <BR>

      <!--- Text input for the replace regular expression --->
      <SPAN CLASS="header" ID="replaceheader">Enter the replace regular expression:</SPAN><BR>
      <INPUT ID="RegExReplace" NAME="RegExReplace" TYPE="Text" SIZE="65" STYLE="font-size:13px" VALUE="#HTMLEditFormat(FORM.RegExReplace)#">
      <BR><BR>

      <!--- Textarea where user can type the text to search --->  
      <SPAN CLASS="header">And the text you wish to search:</SPAN><BR>
      <TEXTAREA NAME="SearchText" WRAP="off" COLS="70" ROWS="6">#HTMLEditFormat(FORM.SearchText)#</TEXTAREA>
      <BR>

      <!--- Submit button to start the search --->  
      <INPUT TYPE="Submit" VALUE="Match Now" STYLE="font-weight:bold">

    </TD>
    </TR>
  </TABLE>
  
  </FORM>
</CFOUTPUT>
  
  
<!--- When the form is submitted... --->  
<CFIF FORM.RegEx NEQ "">

  <!--- If the RegEx is using "multiline mode", adjust the text --->
  <!--- so that only linefeed characters are used to separate lines --->
  <CFIF Left(FORM.RegEx, 4) EQ "(?m)">
    <CFSET FORM.SearchText = AdjustNewlinesToLinefeeds(FORM.SearchText)>
  </CFIF>
  
  <CFTRY>
    <CFIF FORM.operation IS "find">
      <!--- Perform the regular expression search --->
      <!--- Results are returned as a query object with three columns: --->
      <!--- "Pos" - the position of the match --->
      <!--- "Len" - the length of the match --->
      <!--- "Found" - the actual text of the match --->
      <CFSET MatchQuery = REFindMatches(FORM.RegEx, FORM.SearchText, FORM.CaseSensitive)>
    <CFELSE>
      <CFIF FORM.CaseSensitive>
         <CFSET ResultString=REReplace(FORM.SearchText, FORM.RegEx, FORM.RegExReplace, "ALL")>
      <CFELSE>
         <CFSET ResultString=REReplaceNoCase(FORM.SearchText, FORM.RegEx, FORM.RegExReplace, "ALL")>
      </CFIF>
    </CFIF>
  
    <!--- If any errors occur --->  
    <CFCATCH TYPE="Expression">
      <!--- If it has to do with regular expression, show friendly message --->
      <CFIF CFCATCH.Message contains "malformed regular expression">
        <P><B>Sorry, there is a problem with your regular expression.</B><BR>
        <CFOUTPUT>#CFCATCH.Detail#<BR></CFOUTPUT>
        <CFABORT>
        
      <CFELSE>
        <CFRETHROW>  
      </CFIF>
    </CFCATCH>
  </CFTRY>      

  <!--- Process display --->
  <CFIF FORM.operation IS "find">
	  <CFOUTPUT>
		<!--- Display the number of matches found --->
		Matches Found: #MatchQuery.RecordCount#<BR>
	
		<!--- If there is at least one match... --->
		<CFIF MatchQuery.RecordCount GT 0>
		
		  <!--- Display the matches in a simple HTML table --->  
		  <DIV STYLE="height:200px;overflow-y:auto;width:550"> 
		  <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">
		
			<TR>
				<TH WIDTH="*">Match</TH>  
				<TH WIDTH="50">Position</TH>
				<TH WIDTH="50">Length</TH></TR>
			</TR>
		<!---Let's go one step further and display the text with the matches highlighted so
			the user can actually see the match.--->

		<!---The string which we will replace with a highlighted version of itself--->		
		<CFSET replacestring=#searchtext#>
		
		<!---The beginning position of the highlighting --->		
		<CFSET 	hiPos=0>
		<!---The ending position of the highlighting--->
		<CFSET newpos=0>
		
		<!---Counting the number of times we're looping through the query because each time we loop through,
			we insert HTML highlighting tags, which means we're adding to the text in the search string.--->
		<CFSET loopcount=0>
		
			<CFLOOP QUERY="MatchQuery">
			  <CFSET loopcount =loopcount+1>
			  <!--- Alternating row colors --->
			  <CFSET Class = IIF(CurrentRow MOD 2 EQ 0, "'RowA'", "'RowB'")>
			 
			  <TR>
				  <TD CLASS="#Class#" WIDTH="450">#HTMLEditFormat(MatchQuery.Found)#</TD>
				  <TD CLASS="#Class#" WIDTH="50">#MatchQuery.Pos# </TD>
				  <TD CLASS="#Class#" WIDTH="50">#MatchQuery.Len#</TD>
			
				<!--- If we're on the first loop, we haven't added any HTML text yet, nor has hiPos been incremented. --->
				<cfif hiPos is 0>
					<cfset hiPos=#MatchQuery.Pos#-1>
					
				<!--- If we're not on the first loop, find the position where we should insert the HTML
					highlighting tag.  That is the match position -1, plus the number of characters we insert
					at each loop (for the open and close highlighting tags) multiplied by the number of times
					we've looped through (-1 because loopcount is the loop we're on, not the loops completed)  --->			
				<cfelse>	
					<cfset hiPos=#MatchQuery.Pos#-1+(46*(loopcount-1))>
					
				</cfif>
				<!--- Insert a span tag with a style to highlight the text--->
				<cfset replacestring=insert('<span style="background-color:##ffff99">',replacestring,hiPos)>
				
				<!--- Calculate where to end the highlighting.  The position + the length of the highlighted
					text + the length of the HTML code we added to get the opening span--->		
				<cfset newpos = #hiPos# + #MatchQuery.Len#+39>

				<!--- Insert the closing span tag--->			
				<cfset replacestring=insert("</span>",replacestring,newpos)>
	
			  </TR>
			</CFLOOP>
			<tr>
				<td style="background-color:##ffffff" rowspan="3">
				<!--- Print the string with the "found" text highlighted--->
				#replacestring#
				</td>
			</tr>
		  </TABLE>
		  </DIV>
	
		</CFIF>
	  </CFOUTPUT>
   <CFELSE>
	  <CFOUTPUT>
		  <!--- Display the matches in a simple HTML table --->  
		  <DIV STYLE="height:200px;overflow-y:auto;width:550"> 
		  <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">		
			<TR><TH>New Text</TH></TR>
			<TR><TD>#HTMLEditFormat(ResultString)#</TD></TR>
	  </CFOUTPUT>
   </CFIF>
</CFIF>

<!--- Set initial fields --->
<SCRIPT LANGUAGE="JavaScript">
<CFIF FORM.operation IS "find">
  hideReplaceFields();
<CFELSE>
  showReplaceFields();
</CFIF>
</SCRIPT>
  
</BODY>
</HTML>