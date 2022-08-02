import java.util.regex.*;

public class CombinedClass2{
  public static void main(String args[])
  throws Exception{
  
  String TestString = args[0];
  
  String regex = "[A-Z&&[^B-D]]";
  
  Pattern p = Pattern.compile(regex);
  
  Matcher m = p.matcher(TestString);
  String match = null;
  
  System.out.println("INPUT: " + TestString);
  System.out.println("REGEX: " + regex);
  while (m.find())
  	{
  	 match = m.group();
  	 System.out.println("MATCH: " + match);
  	} // end while
  	 
  	 if (match == null){
  	  System.out.println("There were no matches.");
  	 } // end if
  	 

   
   } // end main()
  } 