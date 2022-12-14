<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" Trace="true" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
<div>
  <asp:Label ID="lblInfo" runat="server"
    Text="Click on the Button to Fill the Grid"> </asp:Label>
  <br />
  <br />
  <asp:GridView ID="carsGridView" runat="server" BackColor="White" 
        BorderColor="#E7E7FF" BorderStyle="None" BorderWidth="1px" CellPadding="3" 
        GridLines="Horizontal">
      <AlternatingRowStyle BackColor="#F7F7F7" />
      <FooterStyle BackColor="#B5C7DE" ForeColor="#4A3C8C" />
      <HeaderStyle BackColor="#4A3C8C" Font-Bold="True" ForeColor="#F7F7F7" />
      <PagerStyle BackColor="#E7E7FF" ForeColor="#4A3C8C" HorizontalAlign="Right" />
      <RowStyle BackColor="#E7E7FF" ForeColor="#4A3C8C" />
      <SelectedRowStyle BackColor="#738A9C" Font-Bold="True" ForeColor="#F7F7F7" />
      <SortedAscendingCellStyle BackColor="#F4F4FD" />
      <SortedAscendingHeaderStyle BackColor="#5A4C9D" />
      <SortedDescendingCellStyle BackColor="#D8D8F0" />
      <SortedDescendingHeaderStyle BackColor="#3E3277" />
  </asp:GridView>
  <br />
  <asp:Button ID="btnFillData" runat="server" Text="Fill Grid" 
        onclick="btnFillData_Click" />
</div>
    </form>
</body>
</html>
