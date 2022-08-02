#region Using directives

using System;
using System.Collections.Generic;
using System.Text;

#endregion

using System.Collections;

namespace CallbackInterface
{
    public class Car
    {
        // The set of connected sinks.
        ArrayList clientSinks = new ArrayList();

        // Attach or disconnect from the source of events.
        public void Advise(IEngineNotification sink)
        { clientSinks.Add(sink); }

        public void Unadvise(IEngineNotification sink)
        { clientSinks.Remove(sink); }

        #region Basic Car members...

        #region Nested radio
        // Radio as nested type
        public class Radio
        {
            public void TurnOn(bool on)
            {
                if (on)
                    Console.WriteLine("Jamming...");
                else
                    Console.WriteLine("Quiet time...");
            }
        }
        #endregion

        // Internal state data.
        public int CurrentSpeed { get; set; }
        private int maxSpeed;
        private string petName;

        // Is the car alive or dead?
        bool carIsDead;

        // A car has-a radio.
        private Radio theMusicBox = new Radio();

        public Car()
        {
            maxSpeed = 100;
        }

        public Car(string name, int max, int curr)
        {
            CurrentSpeed = curr;
            maxSpeed = max;
            petName = name;
        }

        public void CrankTunes(bool state)
        {
            theMusicBox.TurnOn(state);
        }
        #endregion

        public void Accelerate(int delta)
        {
            // If the car is dead, send Exploded event.
            if (carIsDead)
            {
                foreach (IEngineNotification sink in clientSinks)
                    sink.Exploded("Sorry, this car is dead...");
            }
            else
            {
                CurrentSpeed += delta;

                // Almost dead?
                if (10 == (maxSpeed - CurrentSpeed))
                {
                    foreach (IEngineNotification sink in clientSinks)
                        sink.AboutToBlow("Careful buddy!  Gonna blow!");
                }

                // Still OK!
                if (CurrentSpeed >= maxSpeed)
                    carIsDead = true;
                else
                    Console.WriteLine("-> CurrentSpeed = " + CurrentSpeed);
            }
        }
    }
}
