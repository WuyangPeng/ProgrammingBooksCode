   M S B A M L   `   `   `  ????  	MyWordPad    MySpellChecker.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5        ? Title$  MySpellChecker??5      $	??331??6   $	??508??6)    ? WindowStartupLocation$ CenterScreen=?5       J? CommandBindings 5	      )  #System.Windows.Input.CommandBinding  5
   
   -   5           Command$ ApplicationCommands.Open??5
      5        5   
   -   5        $ ApplicationCommands.Save??5      5      .??5      ]? .+?5   
   o? $	??Top=?6   $
??Left=?5      
???????
???   ?.@?5      m? $??_File??6   .@?5      m?  m? Command$ ApplicationCommands.Open??6   m? 5      $ ApplicationCommands.Save??6   ?? 5      m? 5      -   5        $??_Exit??5      5      5!      m? 5"      $??_Edit??6   .@?5#      m? $ ApplicationCommands.Copy??6   m? 5$      $ ApplicationCommands.Cut??6   m? 5%      $ ApplicationCommands.Paste??6   5&      m? 5'      $??_Tools??6   .@?5(      m? -   5        $??_Spelling Hints??5(      5+   
   5,      5-      c? 50   
   $	??Top=?6   .@?51      ?? -   5        $
??Exit??51      52   (   ?? 53      ?? 54      -   5        $??Check??54       ? Cursor$
 Help??56      57      ?? 5:   
   $??Bottom=?6   
???????.@?5<      ?? .??5=      ?? -   5        $??statBarText??5=      $??Ready??6/   5>      5?      ? 5A   
   $
??Left=?6   
??????? ? ColumnDefinitions 5C      ?? 5D      ?? 5E      .+?5G      ?? $??0??6   $??5??6,   
???????67   ?? 5H      $??0??6   $??Stretch=?6)   .+?5I      ?? -   5        $??lblSpellingInstructions??5I      $??14(?5J   	   $??	10,10,0,0q?6   .??6*   Spelling Hints6:   9? 5K      -	   5        $??expanderSpelling??5K      $??
Try these!??63   $??10,10,10,10q?6H   .??5M      ?? -
   5        $??lblSpellingHints??5M      $??12(?65   5N      5O      ?? 5R      -   5        $??txtData??5U      $??1??5R       ?? 	IsEnabled .  ?? AcceptsReturn . $??14(?5U      
????  ?"	 ?? VerticalScrollBarVisibility$
	 Auto=?5V      $
 ?? HorizontalScrollBarVisibility$

 Auto=?6=   .??6b   5W      5X      5Y      5Z      