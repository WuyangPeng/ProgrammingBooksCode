   M S B A M L   `   `   `  ????\  XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35fGclr-namespace:System.Windows.Annotations;assembly=PresentationFrameworkSystem.Windows.Annotations  5       WpfControlsAndAPIs#   WpfControlsAndAPIs.MainWindow   5      R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml      5      @d2http://schemas.microsoft.com/expression/blend/2008      5      Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006      6?   UaGclr-namespace:System.Windows.Annotations;assembly=PresentationFramework      5      -   5          ?Name$  Window??5       ? Title$ 
MainWindow??5	      $	??856??5
      $	??375??6    ? WindowStartupLocation$ CenterScreen=?6   .??5      ? -   5         ?Name$ 
LayoutRoot??5      .+?5      ?? -   5         ??Name$ myTabSystem??5      $??8q?6$   .@?5      ?? -   5         ??Name$ tabInk??5      $??Ink API??6   .??5      ?? .+?5      c? -   5         c?Name$ 
inkToolbar??5      $??60??6#   .@?5      ?? $??0,2.5q?6   $	??300??6   ._?5   	   ? .+?5   
   	? -   5         	?Name$ inkRadio??5       	? 	GroupName$ InkMode??6(   $??	Ink Mode!??6<   $??	0,0,200,0q?6P   6?   	? 5   
   -   5        $ selectRadio??5      $??Select Mode!??6+   $??100,0q?6B   $ InkMode??6Q   6?   	? 5   
   -   5        $ 
eraseRadio??5      $??Erase Mode!??6*   $??	200,0,0,0q?6@   $ InkMode??6S   6?   5   
   5   	   ?? 5      ?? 5      -	   5        	 ??Name$	 comboColors??5      $	??200??6&   .@?5   
   ?? 
 ?? Orientation$
 
Horizontal=?6   
 ? Tag$	 Red??6/   .+?5      A? 
???  ??$??50??6    $??50??6-   ?? 5      $??20(?6   $??Center=?6!   $??Center=?5      $	??Red??6-   5      ?? 5    
   $
 
Horizontal=?6   $ Green??6/   .+?5!      A? 
??? ? ?$??50??6"   $??50??6/   ?? 5"      $??20(?6   $??Center=?6!   $??Center=?5#      $??Green??6-   5$      ?? 5&   
   $
 
Horizontal=?6   $
 Blue??6/   .+?5'      A? 
????  ?$??50??6!   $??50??6.   ?? 5(      $??20(?6   $??Center=?6!   $??Center=?5)      $
??Blue??6-   5*      5+   	   ?? 5,      -
   5         ??Name$ btnSave??5,      $??Stretch=?6    $??Stretch=?6>   $??75??6Z   $??	Save Data??6e   6y   ?? 5-      -   5        $ btnLoad??5-      $??Stretch=?6    $??Stretch=?6>   $??75??6Z   $??	Load Data??6e   6y   ?? 5.      -   5        $ btnClear??5.      $??Stretch=?6!   $??Stretch=?6?   $??75??6[   $??Clear??6f   6v   5/      ?? 50      -   5         ??Name$ myInkCanvas??50      $	??227??6&    ?? 
Background ?	#FF4AE6D663   51      52      ?? 53      -   5        $ tabDocuments??53      $??	Documents??6#   $??Bottom=?66   $??19.96??6Q   .??54      ?? .+?55   
   c? .@?56      ?? 
??? ? ?$??Add Sticky Note??6'   $5??/a:AnnotationService.CreateTextStickyNoteCommand??57      ?? 58      
??? ? ?$??Delete Sticky Notes??6'   $2??,a:AnnotationService.DeleteStickyNotesCommand??59      ?? 5:      
??? ? ?$??Highlight Text??6'   $0??*a:AnnotationService.CreateHighlightCommand??5;      ?? 5<   	   -   5        $ 
btnSaveDoc??5<      $??Stretch=?6$   $??Stretch=?6B   $??75??6^   $??Save Doc??6i   ?? 5=   	   -   5        $ 
btnLoadDoc??5=      $??Stretch=?6$   $??Stretch=?6B   $??75??6^   $??Load Doc??6i   5>      -? 5?   
   -   5         -?Name$ myDocumentReader??5?      $	??260??67   .??5@      /? -   5         /?Name$ 
myDocument??5@      .T?5A      ?? 
??? ???
???   ?.?5B      J? $??20(?6   .*?6+   ?? $9?3Here are some fun facts about the WPF Document API!??6/   6m   5C      ?? 5D      -   5         ??Name$ listOfFunFacts??5D      J? 5E      -   5         J?Name$ paraBodyText??5E      5F      5G      5H      5I      ?? 5J      -   5        $ tabDataBinding??5J      $??Data Binding??6%   .??5L      ?? $	??250??6    ? DataContext 6   ??  ?? ElementName$
 mySB??.+?5M      ?? $2??,Move the scroll bar to see the current value??6   ?? 5O      -   5         ??Name$
 mySB??5O   6    ?? Orientation$ 
Horizontal=?6   $??30??6*    ? Maximum$	 100Q?5P       ? LargeChange$ 1Q?6    ? SmallChange$ 1Q?6'   ?? 5R      -   5         ??Name$ labelSBThumb??5R      $??30??6#   
????  ?$??2q?6B   $??0??5S      ?? 5U      $??Click??6   $	??200??6   ??5V      ?? *Value+5W      5X      ?? 5Y      -   5        $ tabDataGrid??5Y      $??DataGrid??6"   .??5Z      ?? .+?5[      &    System.Windows.Controls.DataGrid  -   5          Name$ gridInventory??5[      $	??288??6'    ?? AlternationCount$ 2??64      AlternatingRowBackground ?	#FFE8ADAD   RowBackground ?	#FF5FDB5F6n   5\      5]      5^      5_      5`      