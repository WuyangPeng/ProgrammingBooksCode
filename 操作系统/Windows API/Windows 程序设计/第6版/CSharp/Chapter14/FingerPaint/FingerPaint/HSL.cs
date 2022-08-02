using System;
using Windows.UI;

namespace FingerPaint
{
    public struct HSL
    {
        public HSL(byte hue, byte saturation, byte lightness) :
            this(360 * hue / 255.0, saturation / 255.0, lightness / 255.0)
        {
        }

        // Hue from 0 to 360, saturation and lightness from 0 to 1
        public HSL(double hue, double saturation, double lightness) : this()
        {
            this.Hue = hue;
            this.Saturation = saturation;
            this.Lightness = lightness;

            double chroma = saturation * (1 - Math.Abs(2 * lightness - 1));
            double h = hue / 60;
            double x = chroma * (1 - Math.Abs(h % 2 - 1));
            double r = 0, g = 0, b = 0;

            if (h < 1)
            {
                r = chroma;
                g = x;
            }
            else if (h < 2)
            {
                r = x;
                g = chroma;
            }
            else if (h < 3)
            {
                g = chroma;
                b = x;
            }
            else if (h < 4)
            {
                g = x;
                b = chroma;
            }
            else if (h < 5)
            {
                r = x;
                b = chroma;
            }
            else
            {
                r = chroma;
                b = x;
            }

            double m = lightness - chroma / 2;
            this.Color = Color.FromArgb(255, (byte)(255 * (r + m)),
                                             (byte)(255 * (g + m)),
                                             (byte)(255 * (b + m)));
        }

        public HSL(Color color)
            : this()
        {
            this.Color = color;

            double r = color.R / 255.0;
            double g = color.G / 255.0;
            double b = color.B / 255.0;
            double max = Math.Max(r, Math.Max(g, b));
            double min = Math.Min(r, Math.Min(g, b));

            double chroma = max - min;
            this.Lightness = (max + min) / 2;

            if (chroma != 0)
            {
                if (r == max)
                    this.Hue = 60 * (g - b) / chroma;

                else if (g == max)
                    this.Hue = 120 + 60 * (b - r) / chroma;

                else
                    this.Hue = 240 + 60 * (r - g) / chroma;

                this.Hue = (this.Hue + 360) % 360;

                if (this.Lightness < 0.5)
                    this.Saturation = chroma / (2 * this.Lightness);
                else
                    this.Saturation = chroma / (2 - 2 * this.Lightness);
            }
        }

        public double Hue { private set; get; }

        public double Saturation { private set; get; }

        public double Lightness { private set; get; }

        public Color Color { private set; get; }
    }
}
