<%@ Page Title="" Language="C#" MasterPageFile="~/Events.Master" AutoEventWireup="true" CodeBehind="EventsManagement.aspx.cs" Inherits="EventRegistrationWeb.Admin.EventsManagement" %>

<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolderMain" runat="server">
    <asp:GridView ID="GridView1" runat="server" AllowPaging="True" 
    AllowSorting="True" AutoGenerateColumns="False" BackColor="White" 
    BorderColor="#DEDFDE" BorderStyle="None" BorderWidth="1px" CellPadding="4" 
    DataKeyNames="Id" DataSourceID="EventsDataSource" ForeColor="Black" 
    GridLines="Vertical" PageSize="5">
        <AlternatingRowStyle BackColor="White" />
        <Columns>
            <asp:CommandField ShowEditButton="True" ShowSelectButton="True" />
            <asp:BoundField DataField="Id" HeaderText="Id" InsertVisible="False" 
                ReadOnly="True" SortExpression="Id" Visible="False" />
            <asp:BoundField DataField="Title" HeaderText="Title" SortExpression="Title" />
            <asp:BoundField DataField="Date" DataFormatString="{0:D}" HeaderText="Date" 
                SortExpression="Date" />
            <asp:BoundField DataField="Location" HeaderText="Location" 
                SortExpression="Location" />
        </Columns>
        <FooterStyle BackColor="#CCCC99" />
        <HeaderStyle BackColor="#6B696B" Font-Bold="True" ForeColor="White" />
        <PagerStyle BackColor="#F7F7DE" ForeColor="Black" HorizontalAlign="Right" />
        <RowStyle BackColor="#F7F7DE" />
        <SelectedRowStyle BackColor="#CE5D5A" Font-Bold="True" ForeColor="White" />
        <SortedAscendingCellStyle BackColor="#FBFBF2" />
        <SortedAscendingHeaderStyle BackColor="#848384" />
        <SortedDescendingCellStyle BackColor="#EAEAD3" />
        <SortedDescendingHeaderStyle BackColor="#575357" />
    </asp:GridView>
<asp:SqlDataSource ID="EventsDataSource" runat="server" 
    ConnectionString="<%$ ConnectionStrings:BegVCSharpEventsConnectionString %>" 
    DeleteCommand="DELETE FROM [Events] WHERE [Id] = @Id" 
    InsertCommand="INSERT INTO [Events] ([Title], [Date], [Location]) VALUES (@Title, @Date, @Location)" 
    SelectCommand="SELECT [Id], [Title], [Date], [Location] FROM [Events]" 
    UpdateCommand="UPDATE [Events] SET [Title] = @Title, [Date] = @Date, [Location] = @Location WHERE [Id] = @Id">
    <DeleteParameters>
        <asp:Parameter Name="Id" Type="Int32" />
    </DeleteParameters>
    <InsertParameters>
        <asp:Parameter Name="Title" Type="String" />
        <asp:Parameter Name="Date" Type="DateTime" />
        <asp:Parameter Name="Location" Type="String" />
    </InsertParameters>
    <UpdateParameters>
        <asp:Parameter Name="Title" Type="String" />
        <asp:Parameter Name="Date" Type="DateTime" />
        <asp:Parameter Name="Location" Type="String" />
        <asp:Parameter Name="Id" Type="Int32" />
    </UpdateParameters>
</asp:SqlDataSource>
</asp:Content>
