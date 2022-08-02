import java.io.*;
import java.util.regex.*;

public final class MatcherMethods {
 private static String myRegex;
 private static String testString;
 private static BufferedReader myBufferedReader;
 private static Pattern myPattern;
 private static Matcher myMatcher;
  
 public static void main(String[] argv) {
  initResources();
  processTest();
  closeResources(); }
  
  private static void initResources() {
   try {
    myBufferedReader = new BufferedReader(new FileReader("MatcherMethods.txt"));
       }
   catch (FileNotFoundException fnfe) { 
    System.out.println("Cannot locate input file! "+fnfe.getMessage());
    System.exit(0); }
    try { myRegex = myBufferedReader.readLine();
     testString = myBufferedReader.readLine();
     }
     catch (IOException ioe) {} 
    myPattern = Pattern.compile(myRegex);
    myMatcher = myPattern.matcher(testString);
    System.out.println("Current myRegex is: "+myRegex);
    System.out.println("Current testString is: "+testString);
    } 
    
    private static void processTest() 
    {

     StringBuffer myStringBuffer = new StringBuffer();
     while (myMatcher.find())
     {
      myMatcher.appendReplacement(myStringBuffer, "Moon");
     } // end while loop
     myMatcher.appendTail(myStringBuffer);
     System.out.println();
     System.out.println(myStringBuffer.toString());
    } 
      
      private static void closeResources() 
      { 
       try{ myBufferedReader.close(); 
      }catch(IOException ioe){} 
    } 
  }