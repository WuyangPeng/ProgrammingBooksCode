﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace AssertionDemo
{
   class Program
   {
      static void Main(string[] args)
      {
         int myVar = 11;
         Trace.Assert(myVar < 10, "Variable out of bounds.",
             "Please contact vendor with the error code KCW001.");
      }
   }
}
