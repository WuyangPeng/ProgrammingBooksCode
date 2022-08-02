using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PartialMethods
{
  // CarLocator.cs
  partial class CarLocator
  {
    // This member will always be part of the
    // CarLocator class.
    public bool CarAvailableInZipCode(string zipCode)
    {
      // This call *may* be part of this method
      // implementation.
      VerifyDuplicates(zipCode);

      // Assume some interesting database logic
      // here...
      OnZipCodeLookup(zipCode);
      return true;
    }

    // This member *may* be part of the CarLocator class!
    partial void VerifyDuplicates(string make);

    // A 'lightweight' event handler.
    partial void OnZipCodeLookup(string make);
  }
}
