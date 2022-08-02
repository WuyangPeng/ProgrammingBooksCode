<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Registration.aspx.cs" Inherits="EventRegistrationWeb.Registration" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <style type="text/css">
        .style1
        {
            width: 100%;
        }
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <table class="style1">
            <tr>
                <td>
                    <asp:Label ID="labelEvent" runat="server" Text="Event:"></asp:Label>
                </td>
                <td>
                    <asp:DropDownList ID="dropDownListEvents" runat="server">
                        <asp:ListItem>Introduction to ASP.NET</asp:ListItem>
                        <asp:ListItem>Introduction to Windows Azure</asp:ListItem>
                        <asp:ListItem>Take off to .NET 4.0</asp:ListItem>
                    </asp:DropDownList>
                </td>
                <td>
                    &nbsp;</td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="labelFirstName" runat="server" Text="First name:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="textFirstName" runat="server"></asp:TextBox>
                </td>
                <td>
                    <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" 
                        ControlToValidate="textFirstName" ErrorMessage="First name is required."></asp:RequiredFieldValidator>
                </td>
            </tr>
            <tr>
                <td>
                    <asp:Label ID="labelLastName" runat="server" Text="Last name:"></asp:Label>
                </td>
                <td>
                    <asp:TextBox ID="textLastName" runat="server"></asp:TextBox>
                </td>
                <td>
                    <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" 
                        ControlToValidate="textLastName" ErrorMessage="Last name is required."></asp:RequiredFieldValidator>
                </td>
            </tr>
            <tr>
                <td>
                      <asp:Label ID="labelEmail" runat="server" Text="Email:"></asp:Label>
                    </td>
                <td>
                    <asp:TextBox ID="textEmail" runat="server"></asp:TextBox>
                </td>
                <td>
                    <asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" 
                        ControlToValidate="textEmail" ErrorMessage="Email is required."></asp:RequiredFieldValidator>
                    <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" 
                        ControlToValidate="textEmail" ErrorMessage="Enter a valid email." 
                        ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*"></asp:RegularExpressionValidator>
                </td>
            </tr>
            <tr>
                <td>
                    &nbsp;</td>
                <td>
                    <asp:Button ID="buttonSubmit" runat="server" Text="Submit" 
                        onclick="buttonSubmit_Click" PostBackUrl="~/ResultsPage.aspx" />
                </td>
                <td>
                    &nbsp;</td>
            </tr>
        </table>


    
    </div>
    <asp:Label ID="labelResult" runat="server"></asp:Label>
    </form>
</body>
</html>
