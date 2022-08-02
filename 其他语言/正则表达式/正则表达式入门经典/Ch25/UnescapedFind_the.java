import java.util.regex.*;

public class UnescapedFind_the{
  public static void main(String args[])
  throws Exception{
  
  String myTestString = "The theatre is the greatest form of live entertainment according to thespians.";
  
  String myRegex = "the[a-z]*\b";
  
  Pattern myPattern = Pattern.compile(myRegex);
  
  Matcher myMatcher = myPattern.matcher(myTestString);
  String myGroup = "";
  
  System.out.println("The test string was '" + myTestString + "'.");
  System.out.println("The regular expression was: '" + myRegex + "'.");
  while (myMatcher.find())
  	{
  	 myGroup = myMatcher.group();
  	 System.out.println("A match '" + myGroup + "' was found.");
  	} // end while
  	 
  	 if (myGroup == ""){
  	  System.out.println("There were no matches.");
  	 } // end if
  	 
   
   } // end main()
  } 