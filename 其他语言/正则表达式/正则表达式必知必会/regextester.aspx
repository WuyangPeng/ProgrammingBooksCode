<%@ Page Language="C#" ValidateRequest="false" %>
<%@ Import Namespace="System.Text.RegularExpressions" %>

<script runat="server">
	/*
		Filename:	RegExTester.aspx
		Author:		Scott Van Vliet (svanvliet@hitachiconsulting.com)
		Purpose:  	A page for crafting, testing, and debugging regular expressions
	*/
	
	public void MatchNow_Click(object sender, EventArgs args)
	{
		if (this.txtRegExFind.Text.Trim() != "") 
		{
			this.pnlErrorMessage.Visible = false;
			this.lblMatchesFound.Visible = false;
			this.pnlFindResults.Visible = false;
			this.pnlReplaceResults.Visible = false;
			
			RegexOptions options = RegexOptions.None;
			if (!this.chkCaseSensitive.Checked)
			{
				options |= RegexOptions.IgnoreCase;
			}
			if (this.txtRegExFind.Text.Substring(0, (this.txtRegExFind.Text.Length >= 4) ? 4 : this.txtRegExFind.Text.Length) == "(?m)") 
			{
				options |= RegexOptions.Multiline;
			}
			
			if (this.rdbFind.Checked)
			{
				MatchCollection matches;
				try
				{
					matches = Regex.Matches(this.txtSearchText.Text.Trim(), this.txtRegExFind.Text.Trim(), options);
				}
				catch (Exception e)
				{
					this.pnlErrorMessage.Visible = true;
					this.lblErrorMessage.Text = e.Message;
					return;
				}
						
				this.lblMatchesFound.Visible = true;
				this.lblMatchesFound.Text = "Matches Found: " + matches.Count.ToString();
				
				if (matches.Count > 0)
				{
					this.pnlFindResults.Visible = true;
					this.rptMatches.DataSource = matches;
					this.rptMatches.DataBind();
				}	
			}
			else
			{
				string resultString;
				try
				{
					resultString = Regex.Replace(this.txtSearchText.Text.Trim(), this.txtRegExFind.Text.Trim(), this.txtRegExReplace.Text.Trim(), options);
				}
				catch (Exception e)
				{
					this.pnlErrorMessage.Visible = true;
					this.lblErrorMessage.Text = e.Message;
					return;
				}
				
				this.pnlReplaceResults.Visible = true;
				this.lblReplaceResults.Text = Server.HtmlEncode(resultString);
			}
		}
	}
</script>

<HTML>
<HEAD>
	<TITLE>Regular Expression Test Page</TITLE>
</HEAD>
<STYLE>
  BODY {font-family:arial;font-size:12px}
  INPUT {font-size:11px}
  TEXTAREA {font-size:11px}
  TH {background:#8888FF;color:white;text-align:left}
  TD {background:#CCCC99;color:black;font-size:12px}
  TD.RowA {background:#CCCC99}
  TD.RowB {background:#EEEEBB}
  .header {font-weight:bold}
</STYLE>
<SCRIPT LANGUAGE="JavaScript">
	function showHideReplaceFields() {
		var disabled = document.getElementById("rdgOperations").checked;
		document.getElementById("txtRegExReplace").disabled = document.getElementById("hdrRegExReplace").disabled = disabled;
	}
</SCRIPT>
<BODY onLoad="showHideReplaceFields()">
  <FORM runat="server">
  <TABLE BORDER="1" CELLPADDING="4" CELLSPACING="0" WIDTH="550">
    <TR> 
      <TH CLASS="Dialog">Regular Expression Tester</TH>
    </TR>
    <TR> 
    <TD CLASS="Dialog"> 
    
      <SPAN CLASS="header">Enter a regular expression:</SPAN><BR>
	  <asp:TextBox Id="txtRegExFind" Size="65" Style="font-size:13px" runat="server" />

	  <asp:CheckBox Id="chkCaseSensitive" runat="server" />
      <LABEL FOR="CaseSensitive">Case sensitive</LABEL>
      <BR>
	  
	  <asp:RadioButton Id="rdbFind" GroupName="rdgOperations" Checked="true" OnClick="showHideReplaceFields()" runat="server" />
      <LABEL FOR="OperationFind">Find</LABEL>
	  <asp:RadioButton Id="rdbReplace" GroupName="rdgOperations" OnClick="showHideReplaceFields()" runat="server" />
      <LABEL FOR="OperationReplace">Replace</LABEL>
      <BR>

      <SPAN CLASS="header" ID="hdrRegExReplace">Enter the replace regular expression:</SPAN><BR>
	  <asp:TextBox Id="txtRegExReplace" Size="65" Style="font-size:13px" runat="server" />
      <BR><BR>

      <SPAN CLASS="header">And the text you wish to search:</SPAN><BR>
	  <asp:TextBox Id="txtSearchText" TextMode="MultiLine" Wrap="false" Columns="70" Rows="6" runat="server" />
      <BR>

	  <asp:Button Id="btnMatchNow" Text="Match Now" Style="font-weight:bold" OnClick="MatchNow_Click" runat="server" />

    </TD>
    </TR>
  </TABLE>
  </FORM>
 
<asp:Panel Id="pnlErrorMessage" Visible="false" runat="server">
	<P><B>Sorry, there is a problem with your regular expression.</B><BR>
	<asp:Label Id="lblErrorMessage" runat="server" /><BR>
</asp:Panel>   

<asp:Label Id="lblMatchesFound" runat="server" /><BR>
<asp:Panel Id="pnlFindResults" Style="height:200px;overflow-y:auto;width:550" Visible="false" runat="server">
  <asp:Repeater Id="rptMatches" runat="server">
	<HeaderTemplate>
	  <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">
		<TR>
			<TH WIDTH="*">Match</TH>  
			<TH WIDTH="50">Position</TH>
			<TH WIDTH="50">Length</TH></TR>
		</TR>
	</HeaderTemplate>
	<ItemTemplate>
		<TR>
			<TD CLASS="RowB" WIDTH="450"><%# Server.HtmlEncode(DataBinder.Eval(Container.DataItem, "Value").ToString()) %></TD>
			<TD CLASS="RowB" WIDTH="50"><%# DataBinder.Eval(Container.DataItem, "Index")%></TD>
			<TD CLASS="RowB" WIDTH="50"><%# DataBinder.Eval(Container.DataItem, "Length")%></TD>
		</TR>
	</ItemTemplate>
	<alternatingitemtemplate>
		<TR>
			<TD CLASS="RowA" WIDTH="450"><%# Server.HtmlEncode(DataBinder.Eval(Container.DataItem, "Value").ToString()) %></TD>
			<TD CLASS="RowA" WIDTH="50"><%# DataBinder.Eval(Container.DataItem, "Index") %></TD>
			<TD CLASS="RowA" WIDTH="50"><%# DataBinder.Eval(Container.DataItem, "Length") %></TD>
		</TR>
	</alternatingitemtemplate>
	<FooterTemplate>
	  </TABLE>
	</FooterTemplate>
  </asp:Repeater>
</asp:Panel>
	
<asp:Panel Id="pnlReplaceResults" Style="height:200px;overflow-y:auto;width:550" Visible="false" runat="server">
  <TABLE BORDER="0" CELLPADDING="2" CELLSPACING="0" WIDTH="550">		
	<TR><TH>New Text</TH></TR>
	<TR><TD><asp:Label Id="lblReplaceResults" runat="server" /></TD></TR>
  </TABLE>
</asp:Panel>
  
</BODY>
</HTML>