import java.util.regex.*;

public class lookingAt{
 public static void main(String args[]){
  isMatchPresent(args[0]);
 } // end main()
 
 public static boolean isMatchPresent(String testString){
  boolean testResult = false;
  String LastNameFirstName = "\\w+,\\s+\\w+";
  
  Pattern myPattern = Pattern.compile(LastNameFirstName);
  Matcher myMatcher = myPattern.matcher(testString);
  testResult = myMatcher.lookingAt();
  String matchIs = myMatcher.group();
  
  System.out.println("The test string is: " + testString);
  System.out.println("It is " + testString.length() + " characters long.");

  if (testResult){
   System.out.println("There was a match: " + myMatcher.group() );
   System.out.println("It started at: " + myMatcher.start() );
   System.out.println("It ended at: " + myMatcher.end() );
  }
  else
  {
   System.out.println("No match was found.");
  }
 return testResult;
 } // end isMatchPresent()
 
}