package com.yourcompany.app;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Retrieve username and password from the request
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Perform authentication logic here (e.g., check against a database)

        // If authentication succeeds, create a session
        HttpSession session = request.getSession();
        session.setAttribute("username", username);

        // Redirect the user to a protected page (e.g., home.jsp)
        response.sendRedirect("home.jsp");
    }
}
