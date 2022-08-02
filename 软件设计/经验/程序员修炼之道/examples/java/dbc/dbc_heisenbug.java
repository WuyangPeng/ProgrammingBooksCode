package dbc;

/** 
  * From "Design by Contract", A 'heisenbug' is a bug due to effects
  * suggested by the Heisenburg Uncertainty Principle; i.e., the act
  * of observation can affect the test.  
  */

class dbc_heisenbug {

  //START:ans
  /**
    * @pre anItem != null   // Require real data
    * @post pop() == anItem // Verify that it's
    *                       // on the stack
    */
  public void push(final String anItem) 
  //END:ans
  {
  }

  public String pop() {
    return null;
  }

  public static void main(String args[]) {
      new dbc_heisenbug();
  }


}
