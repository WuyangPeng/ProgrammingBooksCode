<?php 

  require_once( 'regextester.inc.php' ); 

  $reg_ex = new RegEx();

  // re-post previous values
  $posted_text = $_POST['SearchText'];
  $posted_regexfind = $_POST['RegEx'];
  $posted_regexreplace = $_POST['RegExReplace'];
  $is_case_sensitive = $_POST['CaseSensitive'];
  $is_find_or_replace = $_POST['Operation'];
  $is_checked;
  $is_find;
  $is_replace;
  $is_replace_disabled;

  if ($is_case_sensitive)
  {
    $is_checked = "CHECKED";
  }  // if statement
  else
  {
    $is_checked = "";
  }  // else statement

  if ($is_find_or_replace == "replace")
  {
    $is_find = "";
    $is_replace = "CHECKED";
    $is_replace_disabled = "";
  }  // if statement
  else
  {
    $is_find = "CHECKED";
    $is_replace = "";
    $is_replace_disabled = "DISABLED=true";
  }  // else statement

?>

<!-- Start Content -->
<HTML>
<HEAD>
<TITLE>Regular Expression Test Page</TITLE>

<!-- Some styles to make the page look nice -->
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

<!-- Script section grabbed from regextester.html using JavaScript -->
<SCRIPT LANGUAGE="JavaScript">
  // Turn off fields used only by replace
  function hideReplaceFields() 
  {
    document.getElementById('RegExReplace').disabled=true;
    document.getElementById('replaceheader').disabled=true;
  }

  // Turn on fields used only by replace
  function showReplaceFields() 
  {
    document.getElementById('RegExReplace').disabled=false;
    document.getElementById('replaceheader').disabled=false;
  }
</SCRIPT>

<BODY>

<FORM NAME="tester" ACTION="" METHOD="post" onSubmit="processRegex(this);return false">
    
<TABLE BORDER="1" CELLPADDING="4" CELLSPACING="0" WIDTH="550">
  <TR>
    <TH CLASS="Dialog">Regular Expression Tester</TH>
  </TR>
  <TR> 
    <TD CLASS="Dialog"> 

    <!-- Text input for the regular expression itself -->
    <SPAN CLASS="header">Enter a regular expression:</SPAN><BR>
    <INPUT NAME="RegEx" TYPE="Text" SIZE="65" STYLE="font-size:13px" VALUE="<? echo $posted_regexfind ?>">

    <!-- Checkbox to control case-sensitivity -->
    <INPUT TYPE="Checkbox" NAME="CaseSensitive" ID="CaseSensitive" VALUE="Yes" <? echo $is_checked ?>>
    <LABEL FOR="CaseSensitive">Case sensitive</LABEL>
    <BR>

    <!-- Radio buttons to display find vs. replace -->
    <INPUT TYPE="Radio" NAME="Operation" ID="OperationFind" VALUE="find" <? echo $is_find ?> onClick="hideReplaceFields()">
    <LABEL FOR="OperationFind">Find</LABEL>
    <INPUT TYPE="Radio" NAME="Operation" ID="OperationReplace" VALUE="replace" <? echo $is_replace ?> onClick="showReplaceFields()">
    <LABEL FOR="OperationReplace">Replace</LABEL>
    <BR>

    <!-- Text input for the replace regular expression -->
    <SPAN CLASS="header" ID="replaceheader" <? echo $is_replace_disabled ?>>Enter the replace regular expression:</SPAN><BR>
    <INPUT ID="RegExReplace" NAME="RegExReplace" TYPE="Text" SIZE="65" STYLE="font-size:13px" <? echo $is_replace_disabled ?> VALUE="<? echo $posted_regexreplace ?>" >
    <BR><BR>

    <!-- Textarea where user can type the text to search -->  
    <SPAN CLASS="header">And the text you wish to search:</SPAN><BR>
    <TEXTAREA NAME="SearchText" WRAP="off" COLS="70" ROWS="6"><? echo $posted_text ?></TEXTAREA>
    <BR>

    <!-- Submit button to start the search -->  
    <INPUT NAME="Submit" TYPE="Submit" STYLE="font-weight:bold" VALUE="Match Now"></TD>
  </TR>
</TABLE>

</FORM>

<!-- Display any results here -->
<SPAN id="output">

<?php

  // if submitting, set flags and process request
  if ( isset( $_POST['Submit'] ))
  {
    $str_command = $_POST['Submit'];

    switch ( $str_command )
    {
      case 'Match Now':

        if ($is_case_sensitive == "Yes")
          $posted_flags = "g";
        else
          $posted_flags = "gi";
        
        if ($is_find_or_replace == "find")
          $output = $reg_ex->processRegexFind($posted_text, $posted_regexfind, $posted_flags);
        else if ($is_find_or_replace == "replace")
          $output = $reg_ex->processRegexReplace($posted_text, $posted_regexfind, $posted_regexreplace, $posted_flags);

        break;

      default:
        echo "NOT POSTING";				// should never see this!
        break;	
    }  // switch statement  	

    $reg_ex->displayString();
  }  // if statement

?>

</SPAN> 

</BODY>
</HTML>
