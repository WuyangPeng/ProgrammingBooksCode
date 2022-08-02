using System;
using System.Collections.Generic;
using System.Text;

namespace CustomInterface
{
    // These types are just for testing purposes.
    // They illustrate how the same interface can be
    // supported in unique heirarchies.

    public class PitchFork : IPointy
    {
        public byte Points
        {
            get { return 3; }
        }
    }

    public class Fork : IPointy
    {
        public byte Points
        {
            get { return 4; }
        }
    }

    public class Knife : IPointy
    {
        public byte Points
        {
            get { return 1; }
        }
    }
}