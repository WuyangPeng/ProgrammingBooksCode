using System;
using System.Collections.Generic;

namespace PrintableTomKitten
{
    public class CustomPageRange
    {
        // Structure used internally 
        struct PageRange
        {
            public PageRange(int from, int to) : this()
            {
                this.From = from;
                this.To = to;
            }

            public int From { private set; get; }
            public int To { private set; get; }
        }

        public CustomPageRange(string str, int maxPageNumber)
        {
            List<PageRange> pageRanges = new List<PageRange>();
            string[] strRanges = str.Split(',');

            foreach (string strRange in strRanges)
            {
                int dashIndex = strRange.IndexOf('-');

                // Just one page number
                if (dashIndex == -1)
                {
                    int page;

                    if (Int32.TryParse(strRange.Trim(), out page) &&
                        page > 0 && page <= maxPageNumber)
                    {
                        pageRanges.Add(new PageRange(page, page));
                    }
                    else
                    {
                        return;
                    }
                }
                // Two page numbers separated by a dash
                else
                {
                    string strFrom = strRange.Substring(0, dashIndex);
                    string strTo = strRange.Substring(dashIndex + 1);
                    int from, to;

                    if (Int32.TryParse(strFrom.Trim(), out from) &&
                        Int32.TryParse(strTo.Trim(), out to) &&
                        from > 0 && from <= maxPageNumber && 
                        to > 0 && to <= maxPageNumber &&
                        from <= to)
                    {
                        pageRanges.Add(new PageRange(from, to));
                    }
                    else
                    {
                        return;
                    }
                }
            }

            // If we made it to this, the input string is valid
            this.PageMapping = new List<int>();

            // Define a mapping to page numbers
            foreach (PageRange pageRange in pageRanges)
                for (int page = pageRange.From; page <= pageRange.To; page++)
                    this.PageMapping.Add(page);
        }

        // Zero-based in, one-based out
        public IList<int> PageMapping { private set; get; }

        public bool IsValid 
        {
            get { return this.PageMapping != null; }
        }
    }
}
