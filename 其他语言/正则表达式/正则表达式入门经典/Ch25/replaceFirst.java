import java.util.regex.*;

public class replaceFirst{
 public static void main(String args[]){
  myReplace(args[0]);
 } // end main()
 
 public static boolean myReplace(String testString){
  String myMatch = "Star";
  
  Pattern myPattern = Pattern.compile(myMatch);
  Matcher myMatcher = myPattern.matcher(testString);
  String testResult = myMatcher.replaceFirst("Moon");
   
  System.out.println("The test string is: \n'" + testString + "'.");
  System.out.println();

if (testResult.length() > 0)
  {
   System.out.println("After replacement the string is: \n'" + testResult + "'." );
  }
  else
  {
   System.out.println("No match was found.");
  }
 return true;
 } // end myReplace()
 
}