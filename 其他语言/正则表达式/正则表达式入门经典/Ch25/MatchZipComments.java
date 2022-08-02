import java.util.regex.*;

public class MatchZipComments{
  public static void main(String args[])
  throws Exception{
  
  String myTestString = "12345-1234 23456 45678 01234-1234";
  
  // Attempt to match US Zip codes.
  // The pattern matches five numeric digits followed by a hyphen followed by four numeric digits.
  String myRegex = 
   "\\d{5} " +
   "# Matches five numeric digits" + 
   "\n(-\\d{4})* " +
   "# Matches four numeric digits and a hyphen, all of which are optional";
  
  Pattern myPattern = Pattern.compile(myRegex, Pattern.COMMENTS);
  
  Matcher myMatcher = myPattern.matcher(myTestString);
  String myMatch = "";
  
  System.out.println("The test string was '" + myTestString + "'.");
  System.out.println("The pattern was '\\d{5}-\\d{4}'.");
  while (myMatcher.find())
  	{
  	 myMatch = myMatcher.group();
  	 System.out.println("A match '" + myMatch + "' was found.");
  	} // end while
  	 
  	 if (myMatch == ""){
  	  System.out.println("There were no matches.");
  	 } // end if
  	 
   
   } // end main()
  } 