<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="index.aspx.cs" Inherits="WebApplication2.index" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server" method="post">
        <div>
    <%
        int m = 100;
        if (!String.IsNullOrEmpty(Request["number"]))
        {
            m = int.Parse(Request["number"]);
        }
    %>
            <input type="number" id="number" name="number" min="0" max="100" value="<% Response.Write(m); %>" />
            <input type="submit" />
        </div>
    </form>
    <%
        int n = 0;
        if (!String.IsNullOrEmpty(Request["number"]))
        {
            n = int.Parse(Request["number"]);
        }
        String text = String.Empty;
        for(int i = 1; i <= n; i++)
        {
            if (i % 3 == 0 && i % 5 == 0)
            {
                text += "FizzBuzz";
            }
            else if (i % 3 == 0)
            {
                text += "Fizz";
            }else if (i % 5 == 0)
            {
                text += "Buzz";
            }
            else
            {
                text += i.ToString();
            }
            text += "<br />\n\t";
        }
        Response.Write(text);
    %>
</body>
</html>
