#pragma once
#include <memory>
#include "Element.h"

// Class defining a text element
class CText : public CElement
{
  DECLARE_SERIAL(CText)
public:
  // Constructor for a text element
  CText(const CPoint& start, const CPoint& end, const CString& aString, COLORREF color);
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
  virtual void Move(const CSize& aSize) override;  // Move a text element
  virtual ~CText() {}
  virtual void Serialize(CArchive& ar) override;   // Serialize object

protected:
  CString m_String;                                // Text to be displayed
  CText(){}
};
