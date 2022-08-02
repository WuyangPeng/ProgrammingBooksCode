package dbc;

/**
  * From "Design by Contract", examples of bad contracts.
  */

class dbc_bad {

  public class Node {
    public Node(String s) {}
    public Node next() { return this; }
    public Node prev() { return this; }
  }
  public static int max = 100;
  //START:ans
  private int data[];
  /**
    * @post data[index-1] < data[index] &&
    *       data[index] == aValue
    */
  public Node insertNumber (final int aValue) 
  {
    int index = findPlaceToInsert(aValue);
  //END:ans
    /*
  //START:ans
    ...
  //END:ans
  */
    return null;
  }

  private int findPlaceToInsert(final int aValue) {
    return 0;
  }

  public static void main(String args[]) {
      new dbc_bad();
  }

}
