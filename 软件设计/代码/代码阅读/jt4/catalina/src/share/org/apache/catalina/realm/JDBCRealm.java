/*
* The Apache Software License, Version 1.1
*
* Copyright (c) 1999 The Apache Software Foundation.  All rights
* reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in
*    the documentation and/or other materials provided with the
*    distribution.
*
* 3. The end-user documentation included with the redistribution, if
*    any, must include the following acknowlegement:
*       "This product includes software developed by the
*        Apache Software Foundation (http://www.apache.org/)."
*    Alternately, this acknowlegement may appear in the software itself,
*    if and wherever such third-party acknowlegements normally appear.
*
* 4. The names "The Jakarta Project", "Tomcat", and "Apache Software
*    Foundation" must not be used to endorse or promote products derived
*    from this software without prior written permission. For written
*    permission, please contact apache@apache.org.
*
* 5. Products derived from this software may not be called "Apache"
*    nor may "Apache" appear in their names without prior written
*    permission of the Apache Group.
*
* THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
* ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
* USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
* SUCH DAMAGE.
* ====================================================================
*
* This software consists of voluntary contributions made by many
* individuals on behalf of the Apache Software Foundation.  For more
* information on the Apache Software Foundation, please see
* <http://www.apache.org/>.
*
* [Additional notices, if required by prior licensing conditions]
*
*/


package org.apache.catalina.realm;


import java.io.File;
import java.security.MessageDigest;
import java.security.Principal;
import java.sql.Connection;
import java.sql.Driver;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Properties;
import org.apache.catalina.Container;
import org.apache.catalina.Lifecycle;
import org.apache.catalina.LifecycleEvent;
import org.apache.catalina.LifecycleException;
import org.apache.catalina.LifecycleListener;
import org.apache.catalina.Logger;
import org.apache.catalina.Realm;
import org.apache.catalina.util.HexUtils;
import org.apache.catalina.util.LifecycleSupport;
import org.apache.catalina.util.StringManager;
import org.apache.catalina.util.Base64;


/**
*
* Implmentation of <b>Realm</b> that works with any JDBC supported database.
* See the JDBCRealm.howto for more details on how to set up the database and
* for configuration options.
*
* <p><strong>TODO</strong> - Support connection pooling (including message
* format objects) so that <code>authenticate()</code> does not have to be
* synchronized.</p>
*
* @author Craig R. McClanahan
* @author Carson McDonald
* @author Ignacio Ortega
* @version $Revision: 1.19 $ $Date: 2001/09/07 20:45:12 $
*/

public class JDBCRealm
    extends RealmBase {


    // ----------------------------------------------------- Instance Variables


    /**
     * The connection username to use when trying to connect to the database.
     */
    protected String connectionName = null;


    /**
     * The connection URL to use when trying to connect to the database.
     */
    protected String connectionPassword = null;


    /**
     * The connection URL to use when trying to connect to the database.
     */
    protected String connectionURL = null;


    /**
     * The connection to the database.
     */
    protected Connection dbConnection = null;


    /**
     * Instance of the JDBC Driver class we use as a connection factory.
     */
    protected Driver driver = null;


    /**
     * The JDBC driver to use.
     */
    protected String driverName = null;


    /**
     * Descriptive information about this Realm implementation.
     */
    protected static final String info =
        "org.apache.catalina.realm.JDBCRealm/1.0";


    /**
     * Descriptive information about this Realm implementation.
     */
    protected static final String name = "JDBCRealm";


    /**
     * The PreparedStatement to use for authenticating users.
     */
    protected PreparedStatement preparedCredentials = null;


    /**
     * The PreparedStatement to use for identifying the roles for
     * a specified user.
     */
    protected PreparedStatement preparedRoles = null;


    /**
     * The column in the user role table that names a role
     */
    protected String roleNameCol = null;


    /**
     * The string manager for this package.
     */
    protected static final StringManager sm =
        StringManager.getManager(Constants.Package);


    /**
     * The column in the user table that holds the user's credintials
     */
    protected String userCredCol = null;


    /**
     * The column in the user table that holds the user's name
     */
    protected String userNameCol = null;


    /**
     * The table that holds the relation between user's and roles
     */
    protected String userRoleTable = null;


    /**
     * The table that holds user data.
     */
    protected String userTable = null;


    // ------------------------------------------------------------- Properties


    /**
     * Set the username to use to connect to the database.
     *
     * @param connectionName Username
     */
    public void setConnectionName(String connectionName) {
        this.connectionName = connectionName;
    }


    /**
     * Set the password to use to connect to the database.
     *
     * @param connectionPassword User password
     */
    public void setConnectionPassword(String connectionPassword) {
        this.connectionPassword = connectionPassword;
    }


    /**
     * Set the URL to use to connect to the database.
     *
     * @param connectionURL The new connection URL
     */
    public void setConnectionURL( String connectionURL ) {
      this.connectionURL = connectionURL;
    }


    /**
     * Set the JDBC driver that will be used.
     *
     * @param driverName The driver name
     */
    public void setDriverName( String driverName ) {
      this.driverName = driverName;
    }


    /**
     * Set the column in the user role table that names a role.
     *
     * @param roleNameCol The column name
     */
    public void setRoleNameCol( String roleNameCol ) {
        this.roleNameCol = roleNameCol;
    }


    /**
     * Set the column in the user table that holds the user's credentials.
     *
     * @param userCredCol The column name
     */
    public void setUserCredCol( String userCredCol ) {
       this.userCredCol = userCredCol;
    }


    /**
     * Set the column in the user table that holds the user's name.
     *
     * @param userNameCol The column name
     */
    public void setUserNameCol( String userNameCol ) {
       this.userNameCol = userNameCol;
    }


    /**
     * Set the table that holds the relation between user's and roles.
     *
     * @param userRoleTable The table name
     */
    public void setUserRoleTable( String userRoleTable ) {
        this.userRoleTable = userRoleTable;
    }


    /**
     * Set the table that holds user data.
     *
     * @param userTable The table name
     */
    public void setUserTable( String userTable ) {
      this.userTable = userTable;
    }


    // --------------------------------------------------------- Public Methods


    /**
     * Return the Principal associated with the specified username and
     * credentials, if there is one; otherwise return <code>null</code>.
     *
     * If there are any errors with the JDBC connection, executing
     * the query or anything we return null (don't authenticate). This
     * event is also logged, and the connection will be closed so that
     * a subsequent request will automatically re-open it.
     *
     * @param username Username of the Principal to look up
     * @param credentials Password or other credentials to use in
     *  authenticating this username
     */
    public Principal authenticate(String username, String credentials) {

        Connection dbConnection = null;

        try {

            // Ensure that we have an open database connection
            dbConnection = open();

            // Acquire a Principal object for this user
            Principal principal = authenticate(dbConnection,
                                               username, credentials);

            // Release the database connection we just used
            release(dbConnection);

            // Return the Principal (if any)
            return (principal);

        } catch (SQLException e) {

            // Log the problem for posterity
            log(sm.getString("jdbcRealm.exception"), e);

            // Close the connection so that it gets reopened next time
            if (dbConnection != null)
                close(dbConnection);

            // Return "not authenticated" for this request
            return (null);

        }

    }


    // -------------------------------------------------------- Package Methods


    // ------------------------------------------------------ Protected Methods


    /**
     * Return the Principal associated with the specified username and
     * credentials, if there is one; otherwise return <code>null</code>.
     *
     * @param dbConnection The database connection to be used
     * @param username Username of the Principal to look up
     * @param credentials Password or other credentials to use in
     *  authenticating this username
     *
     * @exception SQLException if a database error occurs
     */
    public synchronized Principal authenticate(Connection dbConnection,
                                               String username,
                                               String credentials)
        throws SQLException {

        // Look up the user's credentials
        String dbCredentials = null;
        PreparedStatement stmt = credentials(dbConnection, username);
        ResultSet rs = stmt.executeQuery();
        while (rs.next()) {
            dbCredentials = rs.getString(1).trim();
        }
        rs.close();
        if (dbCredentials == null) {
            return (null);
        }

        // Validate the user's credentials
        boolean validated = false;
        if (hasMessageDigest()) {
            // Hex hashes should be compared case-insensitive
            validated = (digest(credentials).equalsIgnoreCase(dbCredentials));
        } else
            validated = (digest(credentials).equals(dbCredentials));

        if (validated) {
            if (debug >= 2)
                log(sm.getString("jdbcRealm.authenticateSuccess",
                                 username));
        } else {
            if (debug >= 2)
                log(sm.getString("jdbcRealm.authenticateFailure",
                                 username));
            return (null);
        }

        // Accumulate the user's roles
        ArrayList list = new ArrayList();
        stmt = roles(dbConnection, username);
        rs = stmt.executeQuery();
        while (rs.next()) {
            list.add(rs.getString(1).trim());
        }
        rs.close();
        dbConnection.commit();

        // Create and return a suitable Principal for this user
        return (new GenericPrincipal(this, username, credentials, list));

    }


    /**
     * Close the specified database connection.
     *
     * @param dbConnection The connection to be closed
     */
    protected void close(Connection dbConnection) {

        // Do nothing if the database connection is already closed
        if (dbConnection == null)
            return;

        // Close our prepared statements (if any)
        try {
            preparedCredentials.close();
        } catch (Throwable f) {
            ;
        }
        try {
            preparedRoles.close();
        } catch (Throwable f) {
            ;
        }

        // Close this database connection, and log any errors
        try {
            dbConnection.close();
        } catch (SQLException e) {
            log(sm.getString("jdbcRealm.close"), e); // Just log it here
        }

        // Release resources associated with the closed connection
        this.dbConnection = null;
        this.preparedCredentials = null;
        this.preparedRoles = null;

    }


    /**
     * Return a PreparedStatement configured to perform the SELECT required
     * to retrieve user credentials for the specified username.
     *
     * @param dbConnection The database connection to be used
     * @param username Username for which credentials should be retrieved
     *
     * @exception SQLException if a database error occurs
     */
    protected PreparedStatement credentials(Connection dbConnection,
                                            String username)
        throws SQLException {

        if (preparedCredentials == null) {
            StringBuffer sb = new StringBuffer("SELECT ");
            sb.append(userCredCol);
            sb.append(" FROM ");
            sb.append(userTable);
            sb.append(" WHERE ");
            sb.append(userNameCol);
            sb.append(" = ?");
            preparedCredentials =
                dbConnection.prepareStatement(sb.toString());
        }

        preparedCredentials.setString(1, username);
        return (preparedCredentials);

    }


    /**
     * Return a short name for this Realm implementation.
     */
    protected String getName() {

        return (this.name);

    }


    /**
     * Return the password associated with the given principal's user name.
     */
    protected String getPassword(String username) {

        return (null);

    }


    /**
     * Return the Principal associated with the given user name.
     */
    protected Principal getPrincipal(String username) {

        return (null);

    }


    /**
     * Open (if necessary) and return a database connection for use by
     * this Realm.
     *
     * @exception SQLException if a database error occurs
     */
    protected Connection open() throws SQLException {

        // Do nothing if there is a database connection already open
        if (dbConnection != null)
            return (dbConnection);

        // Instantiate our database driver if necessary
        if (driver == null) {
            try {
                Class clazz = Class.forName(driverName);
                driver = (Driver) clazz.newInstance();
            } catch (Throwable e) {
                throw new SQLException(e.getMessage());
            }
        }

        // Open a new connection
        Properties props = new Properties();
        if (connectionName != null)
            props.put("user", connectionName);
        if (connectionPassword != null)
            props.put("password", connectionPassword);
        dbConnection = driver.connect(connectionURL, props);
        dbConnection.setAutoCommit(false);
        return (dbConnection);

    }


    /**
     * Release our use of this connection so that it can be recycled.
     *
     * @param dbConnnection The connection to be released
     */
    protected void release(Connection dbConnection) {

        ; // NO-OP since we are not pooling anything

    }


    /**
     * Return a PreparedStatement configured to perform the SELECT required
     * to retrieve user roles for the specified username.
     *
     * @param dbConnection The database connection to be used
     * @param username Username for which roles should be retrieved
     *
     * @exception SQLException if a database error occurs
     */
    protected PreparedStatement roles(Connection dbConnection, String username)
        throws SQLException {

        if (preparedRoles == null) {
            StringBuffer sb = new StringBuffer("SELECT ");
            sb.append(roleNameCol);
            sb.append(" FROM ");
            sb.append(userRoleTable);
            sb.append(" WHERE ");
            sb.append(userNameCol);
            sb.append(" = ?");
            preparedRoles =
                dbConnection.prepareStatement(sb.toString());
        }

        preparedRoles.setString(1, username);
        return (preparedRoles);

    }


    // ------------------------------------------------------ Lifecycle Methods


    /**
     *
     * Prepare for active use of the public methods of this Component.
     *
     * @exception IllegalStateException if this component has already been
     *  started
     * @exception LifecycleException if this component detects a fatal error
     *  that prevents it from being started
     */
    public void start() throws LifecycleException {

        // Validate that we can open our connection
        try {
            open();
        } catch (SQLException e) {
            throw new LifecycleException(sm.getString("jdbcRealm.open"), e);
        }

        // Perform normal superclass initialization
        super.start();

    }


    /**
     * Gracefully shut down active use of the public methods of this Component.
     *
     * @exception IllegalStateException if this component has not been started
     * @exception LifecycleException if this component detects a fatal error
     *  that needs to be reported
     */
    public void stop() throws LifecycleException {

        // Perform normal superclass finalization
        super.stop();

        // Close any open DB connection
        close(this.dbConnection);

    }


}
