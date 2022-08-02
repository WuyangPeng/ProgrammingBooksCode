#pragma once

class CPrintData
{
public:
  UINT printWidth{ 750 };           // Printable page width - units 0.01 inches
  UINT printLength{ 1000 };         // Printable page length - units 0.01 inches
  UINT m_nWidths;                   // Page count for the width of the document
  UINT m_nLengths;                  // Page count for the length of the document
  CPoint m_DocRefPoint;             // Top-left corner of the document contents
  CString m_DocTitle;               // The name of the document
};
