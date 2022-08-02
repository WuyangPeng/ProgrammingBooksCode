<?php

define("MATCHES_ARRAY_INDEX", 0);
define("MATCHES_ITEM_INDEX", 0);
define("MATCHES_POS_INDEX", 1);

class RegEx
{
  // class variables
  var $output;

  // default constructor
  function RegEx()
  {
    $this->output = "";
  }  // RegEx


  // outputs results to screen
  function displayString()
  {
    echo $this->output;
  }  // displayString


  // process a find
  function processRegexFind($text, $regex, $flags)
  {
    $current_match = 0;
    $total_matches = 0;
    $this->output = '<DIV STYLE="height:200px;overflow-y:auto;width:550">' .
                    '<TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">' .
                    '<TR><TH WIDTH="*">Match</TH><TH WIDTH="50">Position</TH><TH WIDTH="50">Length</TH></TR>';


    // Run through the text and find all occurences of $regex
    if($flags == "g" && $regex && $text)
    {
      $delimited_regex = '/' . $regex . '/';
      $total_matches = preg_match_all($delimited_regex, $text, $matches, PREG_OFFSET_CAPTURE);

      for ($current_match = 0; $current_match < $total_matches; $current_match++)
      {
        $this->output = $this->output . '<TR CLASS="RowA"><TD>' . 
                        $matches[MATCHES_ARRAY_INDEX][$current_match][MATCHES_ITEM_INDEX] . "</TD><TD>" .
                        $matches[MATCHES_ARRAY_INDEX][$current_match][MATCHES_POS_INDEX] . "</TD><TD>" . 
                        strlen($matches[MATCHES_ARRAY_INDEX][$current_match][MATCHES_ITEM_INDEX]) . "</TD></TR>";
      }  // for loop
    }  // if statement
    // Same thing, but case-insensitive
    else if ($flags == "gi" && $regex && $text)
    {
      $delimited_regex = '/' . $regex . '/i';	// the 'i' in the delimiter indicates case-insensitive
      $total_matches = preg_match_all($delimited_regex, $text, $matches, PREG_OFFSET_CAPTURE);

      for ($current_match = 0; $current_match < $total_matches; $current_match++)
      {
        $this->output = $this->output . '<TR CLASS="RowA"><TD>' . 
                        $matches[MATCHES_ARRAY_INDEX][$current_match][MATCHES_ITEM_INDEX] . "</TD><TD>" .
                        $matches[MATCHES_ARRAY_INDEX][$current_match][MATCHES_POS_INDEX] . "</TD><TD>" . 
                        strlen($matches[MATCHES_ARRAY_INDEX][$current_match][MATCHES_ITEM_INDEX]) . "</TD></TR>";
      }  // for loop
    }  // else if statement

    if ($total_matches)
      $this->output = "Matches Found: " . $total_matches . "<br/>" . $this->output . "</TABLE>";
    else
      $this->output = "No matches";
  }  // processRegexFind


  // process a replace
  function processRegexReplace($text, $regexfind, $regexreplace, $flags)
  {
    // Run through the text and replaces all occurrences of $regexfind
    if($flags == "g" && $regexfind && $text)
      $new_text = ereg_replace($regexfind , $regexreplace , $text);
    // Same thing, but case-insensitive
    else if ($flags == "gi" && $regexfind && $text)
      $new_text = eregi_replace($regexfind , $regexreplace , $text);

    $this->output =  '<DIV STYLE="height:200px;overflow-y:auto;width:550">' .
                     '<TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">' .
                     '<TR><TH>New Text</TH></TR><TR><TD>' . $new_text . '</TD></TR>';
  }  // processRegexReplace

}  // class declaration

?>
