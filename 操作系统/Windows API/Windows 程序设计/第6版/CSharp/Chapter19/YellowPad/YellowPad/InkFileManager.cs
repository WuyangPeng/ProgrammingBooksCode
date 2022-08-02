using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.UI;
using Windows.UI.Input.Inking;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace YellowPad
{
    public class InkFileManager
    {
        string id;
        bool isLoaded;

        public InkFileManager(string id)
        {
            this.id = id;
            this.InkManager = new InkManager();
            this.InkDrawingAttributes = new InkDrawingAttributes();
        }

        public InkManager InkManager
        {
            private set;
            get; 
        }

        public InkDrawingAttributes InkDrawingAttributes
        {
            private set;
            get;
        }

        public Panel RenderTarget
        {
            set;
            get;
        }

        public bool IsAnythingSelected
        {
            get
            {
                bool isAnythingSelected = false;

                foreach (InkStroke inkStroke in this.InkManager.GetStrokes())
                    isAnythingSelected |= inkStroke.Selected;

                return isAnythingSelected;
            }
        }

        public void UnselectAll()
        {
            if (IsAnythingSelected)
            {
                foreach (InkStroke inkStroke in this.InkManager.GetStrokes())
                    inkStroke.Selected = false;

                RenderAll();
            }
        }

        public void UpdateAttributes()
        {
            this.InkManager.SetDefaultDrawingAttributes(this.InkDrawingAttributes);
        }

        public void RenderAll()
        {
            this.RenderTarget.Children.Clear();

            foreach (InkStroke inkStroke in this.InkManager.GetStrokes())
                RenderStroke(inkStroke);
        }

        public void RenderStroke(InkStroke inkStroke)
        {
            Color color = inkStroke.DrawingAttributes.Color;
            double penSize = inkStroke.DrawingAttributes.Size.Width;

            if (inkStroke.Selected)
                RenderBeziers(this.RenderTarget, inkStroke, Colors.Silver, penSize + 24);

            RenderBeziers(this.RenderTarget, inkStroke, color, penSize);
        }

        static void RenderBeziers(Panel panel, InkStroke inkStroke, Color color, double penSize)
        {
            Brush brush = new SolidColorBrush(color);
            IReadOnlyList<InkStrokeRenderingSegment> inkSegments = inkStroke.GetRenderingSegments();

            for (int i = 1; i < inkSegments.Count; i++)
            {
                InkStrokeRenderingSegment inkSegment = inkSegments[i];

                BezierSegment bezierSegment = new BezierSegment
                {
                    Point1 = inkSegment.BezierControlPoint1,
                    Point2 = inkSegment.BezierControlPoint2,
                    Point3 = inkSegment.Position
                };

                PathFigure pathFigure = new PathFigure
                {
                    StartPoint = inkSegments[i - 1].Position,
                    IsClosed = false,
                    IsFilled = false
                };
                pathFigure.Segments.Add(bezierSegment);

                PathGeometry pathGeometry = new PathGeometry();
                pathGeometry.Figures.Add(pathFigure);

                Path path = new Path
                {
                    Stroke = brush,
                    StrokeThickness = penSize * inkSegment.Pressure,
                    StrokeStartLineCap = PenLineCap.Round,
                    StrokeEndLineCap = PenLineCap.Round,
                    Data = pathGeometry
                };
                panel.Children.Add(path);
            }
        }

        public async Task LoadAsync()
        {
            if (isLoaded)
                return;

            // Load previously saved ink
            StorageFolder storageFolder = ApplicationData.Current.LocalFolder;

            try
            {
                StorageFile storageFile = 
                    await storageFolder.GetFileAsync("Page" + id + ".ink");

                using (IRandomAccessStream stream = 
                            await storageFile.OpenAsync(FileAccessMode.Read))
                {
                    await this.InkManager.LoadAsync(stream.GetInputStreamAt(0));
                }
            }
            catch
            {
                // Do nothing if an exception occurs
            }

            // Load saved settings
            IPropertySet appData = ApplicationData.Current.LocalSettings.Values;

            // Pen size setting
            double penSize = 4;

            if (appData.ContainsKey("PenSize" + id))
                penSize = (double)appData["PenSize" + id];

            this.InkDrawingAttributes.Size = new Size(penSize, penSize);

            // Color setting
            if (appData.ContainsKey("Color" + id))
            {
                byte[] argb = (byte[])appData["Color" + id];
                this.InkDrawingAttributes.Color = 
                    Color.FromArgb(argb[0], argb[1], argb[2], argb[3]);
            }

            // Set default drawing attributes
            UpdateAttributes();
            isLoaded = true;
        }

        public async Task SaveAsync()
        {
            if (!isLoaded)
                return;

            // Save the ink
            StorageFolder storageFolder = ApplicationData.Current.LocalFolder;

            try
            {
                StorageFile storageFile = 
                    await storageFolder.CreateFileAsync("Page" + id + ".ink",
                                            CreationCollisionOption.ReplaceExisting);

                using (IRandomAccessStream stream = 
                        await storageFile.OpenAsync(FileAccessMode.ReadWrite))
                {
                    await this.InkManager.SaveAsync(stream.GetOutputStreamAt(0));
                }
            }
            catch
            {
                // Do nothing if an exception occurs
            }

            // Save settings
            IPropertySet appData = ApplicationData.Current.LocalSettings.Values;

            // Save pen size
            appData["PenSize" + id] = this.InkDrawingAttributes.Size.Width;

            // Save color
            Color color = this.InkDrawingAttributes.Color;
            byte[] argb = { color.A, color.R, color.G, color.B };
            appData["Color" + id] = argb;
        }
    }
}
