using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;

namespace LoopThroughXmlDocument
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }

    private void buttonLoopThroughDocument_Click(object sender, EventArgs e)
    {
      XmlDocument document = new XmlDocument();

      // A Post event (on the properties page for the project) copies the XML to the
      // output folder whenever you compile, which is why no explicit path is needed.
      document.Load(@"Books.xml");
      textBoxResult.Text = FormatText(document.DocumentElement as XmlNode, "", "");
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

    private void buttonCreateNode_Click(object sender, EventArgs e)
    {
      // Load the XML document.
      XmlDocument document = new XmlDocument();
      document.Load(@"Books.xml");
           
      // Get the root element.
      XmlElement root = document.DocumentElement;
           
      // Create the new nodes.
      XmlElement newBook = document.CreateElement("book");
      XmlElement newTitle = document.CreateElement("title");
      XmlElement newAuthor = document.CreateElement("author");
      XmlElement newCode = document.CreateElement("code");
      XmlText title = document.CreateTextNode("Beginning Visual C# 2008");
      XmlText author = document.CreateTextNode("Karli Watson et al");
      XmlText code = document.CreateTextNode("1234567890");
      XmlComment comment = document.CreateComment("The previous edition This book is the book you are reading");
           
      // Insert the elements.
      newBook.AppendChild(comment);
      newBook.AppendChild(newTitle);
      newBook.AppendChild(newAuthor);
      newBook.AppendChild(newCode);
      newTitle.AppendChild(title);
      newAuthor.AppendChild(author);
      newCode.AppendChild(code);
      root.InsertAfter(newBook, root.FirstChild);
           
      document.Save(@"Books.xml");

    }
  }
}
