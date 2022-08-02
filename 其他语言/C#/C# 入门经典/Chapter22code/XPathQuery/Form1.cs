using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.IO;

namespace XPathQuery
{
  public partial class Form1 : Form
  {
    private XmlDocument document;

    public Form1()
    {
      InitializeComponent();

      document = new XmlDocument();
      // A Post event (on the properties page for the project) copies the XML to the
      // output folder whenever you compile, which is why no explicit path is needed.
      document.Load(@"Elements.xml");

      Update(document.DocumentElement.SelectNodes("."));
    }

    private void Update(XmlNodeList nodes)
    {
      if (nodes == null || nodes.Count == 0)
      {
        textBoxResult.Text = "The query yielded no results";
        return;
      }
      string text = "";
      foreach (XmlNode node in nodes)
      {
        text = FormatText(node, text, "") + "\r\n";
      }
      textBoxResult.Text = text;
    }

    private string FormatText(XmlNode node, string text, string indent)
    {
      if (node is XmlText)
      {
        text += node.Value;
        return text;
      }

      if (string.IsNullOrEmpty(indent))
        indent = "";
      else
      {
        text += "\r\n" + indent;
      }

      if (node is XmlComment)
      {
        text += node.OuterXml;
        return text;
      }

      text += "<" + node.Name;
      if (node.Attributes.Count > 0)
      {
        AddAttributes(node, ref text);
      }
      if (node.HasChildNodes)
      {
        text += ">";
        foreach (XmlNode child in node.ChildNodes)
        {
          text = FormatText(child, text, indent + "  ");
        }
        if (node.ChildNodes.Count == 1 &&
           (node.FirstChild is XmlText || node.FirstChild is XmlComment))
          text += "</" + node.Name + ">";
        else
          text += "\r\n" + indent + "</" + node.Name + ">";
      }
      else
        text += " />";
      return text;
    }

    private void AddAttributes(XmlNode node, ref string text)
    {
      foreach (XmlAttribute xa in node.Attributes)
      {
        text += " " + xa.Name + "='" + xa.Value + "'";
      }
    }

    private void buttonExecute_Click(object sender, EventArgs e)
    {
      try
      {
        XmlNodeList nodes = document.DocumentElement.SelectNodes(textBoxQuery.Text);
        Update(nodes);
      }
      catch (Exception err)
      {
        textBoxResult.Text = err.Message;
      }
    }
  }
}
