using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CustomInterface
{
    // This interface defines the behavior of "having points."
    public interface IPointy
    {
        // Implicitly public and abstract.
        // byte GetNumberOfPoints();

        byte Points { get; }
    }

    // Models the ability to render a type in stunning 3D.
    public interface IDraw3D
    {
        void Draw3D();
    }

}
