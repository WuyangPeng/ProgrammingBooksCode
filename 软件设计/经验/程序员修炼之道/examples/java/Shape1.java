package com.pragprog.sample;

/**
  * From "Refactoring", the sample refactored version
  * of the code.
  */
public abstract class Shape1 {
  //START:body
  public class Shape {
    
    private double size;
    
    public Shape(double size) {
      this.size = size;
    }
    
    public double getSize() { return size; }

    public abstract double area();
  }
  
  public class Square extends Shape {
    public Square(double size) {
      super(size);
    }
    
    public double area() {
      double size = getSize();
      return size*size;
    }
  }
  
  public class Circle extends Shape {
    public Circle(double size) {
      super(size);
    }
    
    public double area() {
      double size = getSize();
      return Math.PI*size*size/4.0;
    }
  }
  //END:body
}


