Imports CarLibrary

' This VB type is deriving from the C# SportsCar.
Public Class PerformanceCar
    Inherits SportsCar
    Public Overrides Sub TurboBoost()
        Console.WriteLine("Zero to 60 in a cool 4.8 seconds...")
    End Sub
End Class
