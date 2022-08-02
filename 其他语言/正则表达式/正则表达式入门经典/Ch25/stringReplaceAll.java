import java.util.regex.*;

public class stringReplaceAll{
 public static void main(String args[]){
  myReplaceAll(args[0]);
 } // end main()
 
 public static boolean myReplaceAll(String testString){
  String myRegex = "twinkle";
  String testResult = testString.replaceAll(myRegex, "TWINKLE");
    
  System.out.println("The string was: '" + testString + "'.");
  System.out.println("The regular expression pattern was: '" + myRegex +"'.");
  System.out.println("After replacement the string was: '" + testResult + "'.");
  	return true; 
 } // myReplaceAll()
 
}