import java.util.regex.*;

public class stringMatches{
 public static void main(String args[]){
  findMatch(args[0]);
 } // end main()
 
 public static boolean findMatch(String testString){
  String myRegex = "\\b[a-z]*hip[a-z]*\\b";
  boolean testResult = testString.matches(myRegex);
    
  System.out.println("The string was: " + testString);
  System.out.println("The regular expression pattern was:" + myRegex);
  if (testResult)
  	{
  	System.out.println("There was a match.");
  	} // end if
  	else
  	{
  	System.out.println("There was no match.");
  	}
  	return true; 
 } // findMatch()
 
}