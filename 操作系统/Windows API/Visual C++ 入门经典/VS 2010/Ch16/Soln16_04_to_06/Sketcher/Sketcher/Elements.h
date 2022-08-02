#pragma once
#include <vector>

// CElement command target

class CElement : public CObject
{
   protected:
      int m_PenWidth;                  // Pen width
      COLORREF m_Color;                // Color of an element
      int m_LineStyle;                 // Line style for the element
      CRect m_EnclosingRect;           // Rectangle enclosing an element

   public:
      virtual ~CElement();  
      virtual void Draw(CDC* pDC) {}   // Virtual draw operation

      CRect GetBoundRect() const;      // Get the bounding rectangle for an element

   protected:
      CElement();                      // Here to prevent it being called
};

class CLine : public CElement
{
   public:
      ~CLine(void);
      virtual void Draw(CDC* pDC);     // Function to display a line

      // Constructor for a line object
      CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int lineStyle);

   protected:
      CPoint m_StartPoint;             // Start point of line
      CPoint m_EndPoint;               // End point of line

      CLine(void);                     // Default constructor should not be used
};

class CRectangle : public CElement
{
   public:
      ~CRectangle(void);
      virtual void Draw(CDC* pDC);     // Function to display a rectangle

      // Constructor for a rectangle object
      CRectangle(const CPoint& start, const CPoint& end, COLORREF aColor, int lineStyle);

   protected:
      CRectangle(void);                // Default constructor - should not be used
};

class CCircle : public CElement
{
   public:
      ~CCircle(void);
      virtual void Draw(CDC* pDC);     // Function to display a circle

      // Constructor for a circle object
      CCircle(const CPoint& sStart, const CPoint& eEnd, COLORREF aColor, int lineStyle);

   protected:
      CCircle(void);                   // Default constructor - should not be used
};

class CCurve: public CElement
{
  public:
    ~CCurve(void);
    virtual void Draw(CDC* pDC);   // Function to display a curve

    // Constructor for a curve object
    CCurve(const CPoint& first, const CPoint& second, COLORREF aColor, int lineStyle);
    void AddSegment(const CPoint& point); // Add a segment to the curve

 protected:
    std::vector<CPoint> m_Points;  // Points defining the curve
    CCurve(void);                  // Default constructor - should not be used
};

class CEllipse : public CElement
{
   public:
      ~CEllipse(void);
      virtual void Draw(CDC* pDC);     // Function to display a circle

      // Constructor for a circle object
      CEllipse(const CPoint& sStart, const CPoint& eEnd, COLORREF aColor, int lineStyle);

   protected:
      CEllipse(void);                   // Default constructor - should not be used
};
