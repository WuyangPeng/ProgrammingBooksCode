using System;
using System.Windows.Forms;

namespace CarLibrary
{
    public class SportsCar : Car
    {
        public SportsCar() { }
        public SportsCar(string name, int maxSp, int currSp)
            : base(name, maxSp, currSp) { }

        public override void TurboBoost()
        {
            MessageBox.Show("Ramming speed!", "Faster is better...");
        }

        public void TurnOnRadio(bool turnOn, int volumn)
        {
            MessageBox.Show("Cranking tunes!");
        }
    }

    public class MiniVan : Car
    {
        public MiniVan() { }
        public MiniVan(string name, int maxSp, int currSp)
            : base(name, maxSp, currSp) { }

        public override void TurboBoost()
        {
            // Minivans have poor turbo capabilities!
            egnState = EngineState.engineDead;
            MessageBox.Show("Eek!", "Your engine block exploded!");
        }
    }
}
