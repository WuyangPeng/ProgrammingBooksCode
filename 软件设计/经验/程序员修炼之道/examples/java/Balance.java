package com.pragprog.sample;

import java.io.*;

/**
  * From "How to Balance Resources", a simple example of try..catch.
  */

public class Balance {

  String tmpFileName = "tmpfile";

  /*****************************************************************/
  /* Constructors                                                  */
  /*****************************************************************/

  public Balance() throws IOException {
    doSomething();
  }

  /*****************************************************************/
  /* Command                                                       */
  /*****************************************************************/

  //START:code
  public void doSomething() throws IOException {

    File tmpFile = new File(tmpFileName);
    FileWriter tmp = new FileWriter(tmpFile);

    try {
      // do some work
    }
    finally {
      tmpFile.delete();
    }
  }
  //END:code

  /*****************************************************************/
  /* Queries                                                       */
  /*****************************************************************/

  /*****************************************************************/
  /* Property Access                                               */
  /*****************************************************************/

  public final static void main(String args[]) throws IOException {

    new Balance();
  }

}


