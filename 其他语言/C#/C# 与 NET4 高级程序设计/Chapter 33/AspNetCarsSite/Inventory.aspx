<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Inventory.aspx.cs" Inherits="Default2" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" 
    DataKeyNames="CarID" DataSourceID="SqlDataSource1" 
    EmptyDataText="There are no data records to display." AllowPaging="True" 
        AllowSorting="True" CellPadding="4" ForeColor="#333333" GridLines="None">
        <AlternatingRowStyle BackColor="White" />
    <Columns>
        <asp:CommandField ShowDeleteButton="True" ShowEditButton="True" />
        <asp:BoundField DataField="CarID" HeaderText="CarID" ReadOnly="True" 
            SortExpression="CarID" />
        <asp:BoundField DataField="Make" HeaderText="Make" SortExpression="Make" />
        <asp:BoundField DataField="Color" HeaderText="Color" SortExpression="Color" />
        <asp:BoundField DataField="PetName" HeaderText="PetName" 
            SortExpression="PetName" />
    </Columns>
        <EditRowStyle BackColor="#7C6F57" />
        <FooterStyle BackColor="#1C5E55" Font-Bold="True" ForeColor="White" />
        <HeaderStyle BackColor="#1C5E55" Font-Bold="True" ForeColor="White" />
        <PagerStyle BackColor="#666666" ForeColor="White" HorizontalAlign="Center" />
        <RowStyle BackColor="#E3EAEB" />
        <SelectedRowStyle BackColor="#C5BBAF" Font-Bold="True" ForeColor="#333333" />
        <SortedAscendingCellStyle BackColor="#F8FAFA" />
        <SortedAscendingHeaderStyle BackColor="#246B61" />
        <SortedDescendingCellStyle BackColor="#D4DFE1" />
        <SortedDescendingHeaderStyle BackColor="#15524A" />
</asp:GridView>
<asp:SqlDataSource ID="SqlDataSource1" runat="server" 
    ConnectionString="<%$ ConnectionStrings:AutoLotConnectionString1 %>" 
    DeleteCommand="DELETE FROM [Inventory] WHERE [CarID] = @CarID" 
    InsertCommand="INSERT INTO [Inventory] ([CarID], [Make], [Color], [PetName]) VALUES (@CarID, @Make, @Color, @PetName)" 
    ProviderName="<%$ ConnectionStrings:AutoLotConnectionString1.ProviderName %>" 
    SelectCommand="SELECT [CarID], [Make], [Color], [PetName] FROM [Inventory]" 
    UpdateCommand="UPDATE [Inventory] SET [Make] = @Make, [Color] = @Color, [PetName] = @PetName WHERE [CarID] = @CarID">
    <DeleteParameters>
        <asp:Parameter Name="CarID" Type="Int32" />
    </DeleteParameters>
    <InsertParameters>
        <asp:Parameter Name="CarID" Type="Int32" />
        <asp:Parameter Name="Make" Type="String" />
        <asp:Parameter Name="Color" Type="String" />
        <asp:Parameter Name="PetName" Type="String" />
    </InsertParameters>
    <UpdateParameters>
        <asp:Parameter Name="Make" Type="String" />
        <asp:Parameter Name="Color" Type="String" />
        <asp:Parameter Name="PetName" Type="String" />
        <asp:Parameter Name="CarID" Type="Int32" />
    </UpdateParameters>
</asp:SqlDataSource>
</asp:Content>

