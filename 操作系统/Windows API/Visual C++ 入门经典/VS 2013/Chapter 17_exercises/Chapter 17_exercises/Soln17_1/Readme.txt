Solutions to Exercise 1 in Chapter 17


-I started with the Sketcher version that is the last in Chapter 17. The solution is trivial if you understand CPrintInfo. I changed one line on the OnPrint() member of CSketcherView to:

  str.Format(_T("Page %u of %u") , pInfo->m_nCurPage, pInfo->GetMaxPage());

Calling GetMaxPage() returns the maximum number of pages so all you need to do is write it to the page.





