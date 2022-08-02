package com.pragprog.sample;

/**
  * From "Refactoring", the original shape example.
  */

//START:body
public class Shape {
  
  public static final int SQUARE   = 1;
  public static final int CIRCLE   = 2;
  public static final int RIGHT_TRIANGLE = 3;
  
  private int    shapeType;
  private double size;
  
  public Shape(int shapeType, double size) {
    this.shapeType = shapeType;
    this.size      = size;
  }
  
  // ... other methods ...


  
  public double area() {
    switch (shapeType) {
    case SQUARE:   return size*size;
    case CIRCLE:   return Math.PI*size*size/4.0;
    case RIGHT_TRIANGLE: return size*size/2.0;
    }
    return 0;
  }
}
//END:body


