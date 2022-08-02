using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.Graphics.Display;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace WhatRes
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            this.SizeChanged += OnMainPageSizeChanged;
            DisplayProperties.LogicalDpiChanged += OnLogicalDpiChanged;

            Loaded += (sender, args) =>
            {
                UpdateDisplay();
            };
        }

        void OnMainPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            UpdateDisplay();
        }

        void OnLogicalDpiChanged(object sender)
        {
            UpdateDisplay();
        }

        void UpdateDisplay()
        {
            double logicalDpi = DisplayProperties.LogicalDpi;
            int pixelWidth = (int)Math.Round(logicalDpi * this.ActualWidth / 96);
            int pixelHeight = (int)Math.Round(logicalDpi * this.ActualHeight / 96);

            textBlock.Text =
                String.Format("Window size = {0} x {1}\r\n" +
                              "ResolutionScale = {2}\r\n" +
                              "Logical DPI = {3}\r\n" +
                              "Pixel size = {4} x {5}",
                              this.ActualWidth, this.ActualHeight,
                              DisplayProperties.ResolutionScale,
                              DisplayProperties.LogicalDpi,
                              pixelWidth, pixelHeight);
        }
    }
}
