import java.io.*;
import java.util.regex.*;

public final class RegexTester {
 private static String myRegex;
 private static String testString;
 private static BufferedReader myPatternBufferedReader;
 private static BufferedReader myTestTextBufferedReader;
 private static Pattern myPattern;
 private static Matcher myMatcher;
 private static boolean foundOrNot;
 
 public static void main(String[] argv) {
  findFiles();
  doMatching();
  tidyUp(); }
  
  private static void findFiles() {
   // Find and open the file containing the regular expression pattern
   try {
       myPatternBufferedReader = new BufferedReader(new FileReader("Pattern.txt"));
       }
   catch (FileNotFoundException fnfe) { 
    System.out.println("Cannot find the Pattern input file! "+fnfe.getMessage());
    System.exit(0); }
    try { 
        myRegex = myPatternBufferedReader.readLine();
        }
     catch (IOException ioe) {} 
     
     // Find and open the file containing the test text
     try {
    myTestTextBufferedReader = new BufferedReader(new FileReader("TestText.txt"));
       }
   catch (FileNotFoundException fnfe) { 
    System.out.println("Cannot locate Test Text input file! "+fnfe.getMessage());
    System.exit(0); }
    try {
     testString = myTestTextBufferedReader.readLine();
     }
     catch (IOException ioe) {} 
     
    myPattern = Pattern.compile(myRegex);
    myMatcher = myPattern.matcher(testString);
    System.out.println("The regular expression is: " + myRegex);
    System.out.println("The test text is: " + testString);
    } // end of findFiles()
    
    private static void doMatching() 
    {
     while(myMatcher.find())
      { 
      System.out.println("The text \""
       + myMatcher.group() + "\" was found, starting at index "
       + myMatcher.start() + " and ending at index "
       + myMatcher.end() + ".");
      foundOrNot = true; }
      if(!foundOrNot){ System.out.println("No match was found."); 
      } 
    } // end of doMatching()
      
      private static void tidyUp() 
      { 
       try{ 
       myPatternBufferedReader.close(); 
       myTestTextBufferedReader.close();
      }catch(IOException ioe){} 
    } // end of tidyUp()
  }