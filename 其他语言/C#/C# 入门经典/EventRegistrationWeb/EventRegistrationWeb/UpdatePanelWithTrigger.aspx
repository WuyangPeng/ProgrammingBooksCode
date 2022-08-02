<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="UpdatePanelWithTrigger.aspx.cs"
    Inherits="EventRegistrationWeb.UpdatePanelWithTrigger" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
        <asp:ScriptManager ID="ScriptManager1" runat="server">
        </asp:ScriptManager>
    </div>
    <asp:UpdatePanel ID="UpdatePanel1" runat="server" UpdateMode="Conditional">
        <ContentTemplate>
            <asp:Label ID="Label1" runat="server" Text="Label"></asp:Label>
            <asp:Button ID="Button1" runat="server" Text="Button" OnClick="OnButtonClick" />
        </ContentTemplate>
        <Triggers>
            <asp:AsyncPostBackTrigger ControlID="Button2" EventName="Click" />
        </Triggers>
    </asp:UpdatePanel>
    <asp:UpdatePanel ID="UpdatePanel2" runat="server" UpdateMode="Conditional">
        <ContentTemplate>
            <asp:Label ID="Label2" runat="server" Text="Label"></asp:Label>
            <asp:Button ID="Button2" runat="server" Text="Button" OnClick="OnButtonClick" />
        </ContentTemplate>
    </asp:UpdatePanel>
    </form>
</body>
</html>
