import java.util.regex.*;

public class CharClassSubtraction{
 public static void main(String args[]){
  findMatches(args[0]);
 } // end main()
 
 public static boolean findMatches(String testString){
  String myRegex = "[A-Z&&[^H-M]]\\d";
  
  Pattern myPattern = Pattern.compile(myRegex);
  Matcher myMatcher = myPattern.matcher(testString);
  String myMatch = null;
  
  System.out.println("The test string was: " + testString);
  System.out.println("The regular expression pattern was:" + myRegex);
  while (myMatcher.find())
  	{
  	 myMatch = myMatcher.group();
  	 System.out.println("Match found: " + myMatch);
  	} // end while
  	 
  	 if (myMatch == null){
  	  System.out.println("There were no matches.");
  	 } // end if
   
 return true;
 } // findMatches()
 
}