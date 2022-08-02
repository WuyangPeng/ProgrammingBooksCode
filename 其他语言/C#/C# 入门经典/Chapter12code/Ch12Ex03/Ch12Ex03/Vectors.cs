using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Ch12Ex03
{
    public class Vectors : List<Vector>
    {
        public Vectors()
        {
        }

        public Vectors(IEnumerable<Vector> initialItems)
        {
            foreach (Vector vector in initialItems)
            {
                Add(vector);
            }
        }

        public string Sum()
        {
            StringBuilder sb = new StringBuilder();
            Vector currentPoint = new Vector(0.0, 0.0);
            sb.Append("origin");
            foreach (Vector vector in this)
            {
                sb.AppendFormat(" + {0}", vector);
                currentPoint += vector;
            }
            sb.AppendFormat(" = {0}", currentPoint);
            return sb.ToString();
        }
    }

}
