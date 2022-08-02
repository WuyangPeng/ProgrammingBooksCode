import java.util.regex.*;

public class stringReplaceFirst{
 public static void main(String args[]){
  myReplaceFirst(args[0]);
 } // end main()
 
 public static boolean myReplaceFirst(String testString){
  String myRegex = "twinkle";
  String testResult = testString.replaceFirst(myRegex, "TWINKLE");
    
  System.out.println("The string was: '" + testString + "'.");
  System.out.println("The regular expression pattern was: '" + myRegex +"'.");
  System.out.println("After replacement the string was: '" + testResult + "'.");
  	return true; 
 } // myReplaceFirst()
 
}