<%@ WebService Language="C#" Class="HelloWebService" %>
using System;
using System.Web.Services;

public class HelloWebService
{
  [WebMethod]
  public string HelloWorld()
  {
    return "Hello World";
  }
}
