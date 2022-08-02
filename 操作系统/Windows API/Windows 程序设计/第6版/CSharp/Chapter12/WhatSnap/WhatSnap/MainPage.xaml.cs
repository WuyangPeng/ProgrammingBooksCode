using System;
using Windows.Graphics.Display;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace WhatSnap
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
                String.Format("ApplicationViewState = {0}\r\n" +
                              "Window size = {1} x {2}\r\n" +
                              "ResolutionScale = {3}\r\n" +
                              "Logical DPI = {4}\r\n" +
                              "Pixel size = {5} x {6}",
                              ApplicationView.Value,
                              this.ActualWidth, this.ActualHeight,
                              DisplayProperties.ResolutionScale,
                              DisplayProperties.LogicalDpi,
                              pixelWidth, pixelHeight);
        }
    }
}
