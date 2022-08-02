#ifndef CCC_SHAP_H
#define CCC_SHAP_H

#include <string>

using namespace std;

/**
   A point in the plane.
*/
class Point
{
public:
   /**
      Constructs a point and initializes it to the origin.
   */
   Point();
   /**
      Constructs a point with the given x- and y-values.
      @param x1 the x-value
      @param y1 the y-value
   */
   Point(double x1, double y1);
   /**
      Gets the x-value of this point.
      @return the x-value
   */
   double get_x() const;
   /**
      Gets the y-value of this point.
      @return the y-value
   */
   double get_y() const;
   /**
      Moves this point.
      @param dx the amount to move in the x-direction
      @param dy the amount to move in the y-direction
   */
   void move(double dx, double dy);
private:
   double x;
   double y;
};


/**
   A circle in the plane.
*/
class Circle
{
public:
   /**
      Constructs a circle with center at the origin and radius 0.
   */
   Circle();
   /**
      Constructs a circle with a given center and radius.
      @param p the center
      @param r the radius
   */
   Circle(Point p, double r);
   /**
      Returns the center of this circle.
      @return the center
   */
   Point get_center() const;
   /**
      Returns the radius of this circle.
      @return the radius
   */
   double get_radius() const;
   /**
      Moves this circle.
      @param dx the amount to move in the x-direction
      @param dy the amount to move in the y-direction
   */
   void move(double dx, double dy);
private:
   Point center;
   double radius;
};

/**
   A line segment in the plane.
*/
class Line
{
public:
   /**
      Constructs a line whose start and end point are the origin.
   */
   Line();
   /**
      Constructs a line with given start and end points.
      @param p1 the start point
      @param p2 the end point
   */
   Line(Point p1, Point p2);
   /**
      Gets the start point of this line.
      @return the start point
   */
   Point get_start() const;
   /**
      Gets the end point of this line.
      @return the end point
   */
   Point get_end() const;
   /**
      Moves this line.
      @param dx the amount to move in the x-direction
      @param dy the amount to move in the y-direction
   */
   void move(double dx, double dy);
private:
   Point from;
   Point to;
};

/**
   A message that is placed at a given point in the plane.
*/
class Message
{
public:
   /**
      Constructs an empty message at the origin.
   */
   Message();
   /**
      Constructs a message that displays the value of a number.
      @param s the top left corner of the message
      @param x the value to be displayed
   */
   Message(Point s, double x);
   /**
      Constructs a message that displays a string
      @param s the top left corner of the message
      @param m the message text
   */
   Message(Point s, const string& m);
   /**
      Gets the start point of this message.
      @return the start point
   */
   Point get_start() const;
   /**
      Gets the text of this message.
      @return the message text
   */
   string get_text() const;
   /**
      Moves this message.
      @param dx the amount to move in the x-direction
      @param dy the amount to move in the y-direction
   */
   void move(double dx, double dy);
private:
   Point start;
   string text;
};

#endif
