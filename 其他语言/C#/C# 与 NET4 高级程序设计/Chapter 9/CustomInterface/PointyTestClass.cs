using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CustomInterface
{
    class PointyTestClass : IPointy 
    {
        #region IPointy Members

        public byte Points
        {
            get { throw new NotImplementedException(); }
        }

        #endregion
    }
}
