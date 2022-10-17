struct Point
{
    double x, y;
};

struct Shape
{
    enum ShapeType
    {
        square,
        circle
    } itsType;

    Shape(ShapeType t)
        : itsType(t)
    {
    }
};

struct Circle : public Shape
{
    Circle()
        : Shape(circle)
    {
    }
    void Draw() const;
    Point itsCenter;
    double itsRadius;
};

struct Square : public Shape
{
    Square()
        : Shape(square)
    {
    }
    void Draw() const;
    Point itsTopLeft;
    double itsSide;
};

void DrawShape(const Shape& s)
{
    if (s.itsType == Shape::square)
        static_cast<const Square&>(s).Draw();
    else if (s.itsType == Shape::circle)
        static_cast<const Circle&>(s).Draw();
}