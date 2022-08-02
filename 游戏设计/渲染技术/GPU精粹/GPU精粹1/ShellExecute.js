
arg0 = WScript.Arguments.Item(0);

// Create an instance of the scripting Shell Object
WshShell = WScript.CreateObject("WScript.Shell");
 
// Have the Shell Object run/open the file specified
//  on the command line

WshShell.Run( arg0, 1, 0);
 
// Destroy the Shell Object
WScript.DisconnectObject(WshShell);

 
