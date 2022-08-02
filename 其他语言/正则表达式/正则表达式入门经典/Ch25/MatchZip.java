import java.util.regex.*;

public class MatchZip{
  public static void main(String args[])
  throws Exception{
  
  String myTestString = "12345-1234 23456 45678 01234-1234";
  
  // Attempt to match US Zip codes.
  // The pattern matches five numeric digits followed by a hyphen followed by four numeric digits.
  String myRegex = "\\d{5}(-\\d{4})*";
  
  Pattern myPattern = Pattern.compile(myRegex);
  
  Matcher myMatcher = myPattern.matcher(myTestString);
  String myMatch = "";
  
  System.out.println("The test string was '" + myTestString + "'.");
  System.out.println("The pattern was '" + myRegex + "'.");
  while (myMatcher.find())
  	{
  	 myMatch = myMatcher.group();
  	 System.out.println("The match '" + myMatch + "' was found.");
  	} // end while
  	 
  	 if (myMatch == ""){
  	  System.out.println("There were no matches.");
  	 } // end if
  	 
   
   } // end main()
  } 