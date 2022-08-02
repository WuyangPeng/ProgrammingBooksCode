<%@ Page Language="C#" AutoEventWireup="true"  CodeFile="Default.aspx.cs" Inherits="_Default" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
  <title>Dynamic Control Test</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
      <hr />
      <h1>Dynamic Controls</h1>
      <asp:Label ID="lblTextBoxText" runat="server"></asp:Label>
      <hr />
    </div>
        <!-- The Panel has three contained controls -->
    <asp:Panel ID="myPanel" runat="server" Width="200px" 
        BorderColor="Black" BorderStyle="Solid" >
      <asp:TextBox ID="TextBox1" runat="server"></asp:TextBox><br/>
      <asp:Button ID="Button1" runat="server" Text="Button"/><br/>
      <asp:HyperLink ID="HyperLink1" runat="server">HyperLink
      </asp:HyperLink>
    </asp:Panel>
    <br />
    <asp:Button ID="btnAddWidgets" runat="server" onclick="btnAddWidgets_Click" 
        Text="Add Controls!" />

    &nbsp;

    <asp:Button ID="btnClearPanel" runat="server" onclick="btnClearPanel_Click" 
        Text="Clear Panel!" />
    <br />
    <asp:Button ID="btnGetTextData" runat="server" onclick="btnGetTextData_Click" 
        Text="Get New Text Data" />
    <br />
    <br />
    <asp:Label ID="lblTextBoxData" runat="server"></asp:Label>
    <br />
    <br />
    <asp:Label ID="lblControlInfo" runat="server"></asp:Label>
    </form>
  </body>
</html>
