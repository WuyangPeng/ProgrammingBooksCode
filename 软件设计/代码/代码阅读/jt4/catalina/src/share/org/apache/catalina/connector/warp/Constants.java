/* ========================================================================= *
 *                                                                           *
 *                 The Apache Software License,  Version 1.1                 *
 *                                                                           *
 *          Copyright (c) 1999-2001 The Apache Software Foundation.          *
 *                           All rights reserved.                            *
 *                                                                           *
 * ========================================================================= *
 *                                                                           *
 * Redistribution and use in source and binary forms,  with or without modi- *
 * fication, are permitted provided that the following conditions are met:   *
 *                                                                           *
 * 1. Redistributions of source code  must retain the above copyright notice *
 *    notice, this list of conditions and the following disclaimer.          *
 *                                                                           *
 * 2. Redistributions  in binary  form  must  reproduce the  above copyright *
 *    notice,  this list of conditions  and the following  disclaimer in the *
 *    documentation and/or other materials provided with the distribution.   *
 *                                                                           *
 * 3. The end-user documentation  included with the redistribution,  if any, *
 *    must include the following acknowlegement:                             *
 *                                                                           *
 *       "This product includes  software developed  by the Apache  Software *
 *        Foundation <http://www.apache.org/>."                              *
 *                                                                           *
 *    Alternately, this acknowlegement may appear in the software itself, if *
 *    and wherever such third-party acknowlegements normally appear.         *
 *                                                                           *
 * 4. The names  "The  Jakarta  Project",  "Tomcat",  and  "Apache  Software *
 *    Foundation"  must not be used  to endorse or promote  products derived *
 *    from this  software without  prior  written  permission.  For  written *
 *    permission, please contact <apache@apache.org>.                        *
 *                                                                           *
 * 5. Products derived from this software may not be called "Apache" nor may *
 *    "Apache" appear in their names without prior written permission of the *
 *    Apache Software Foundation.                                            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES *
 * INCLUDING, BUT NOT LIMITED TO,  THE IMPLIED WARRANTIES OF MERCHANTABILITY *
 * AND FITNESS FOR  A PARTICULAR PURPOSE  ARE DISCLAIMED.  IN NO EVENT SHALL *
 * THE APACHE  SOFTWARE  FOUNDATION OR  ITS CONTRIBUTORS  BE LIABLE  FOR ANY *
 * DIRECT,  INDIRECT,   INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL *
 * DAMAGES (INCLUDING,  BUT NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE GOODS *
 * OR SERVICES;  LOSS OF USE,  DATA,  OR PROFITS;  OR BUSINESS INTERRUPTION) *
 * HOWEVER CAUSED AND  ON ANY  THEORY  OF  LIABILITY,  WHETHER IN  CONTRACT, *
 * STRICT LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN *
 * ANY  WAY  OUT OF  THE  USE OF  THIS  SOFTWARE,  EVEN  IF  ADVISED  OF THE *
 * POSSIBILITY OF SUCH DAMAGE.                                               *
 *                                                                           *
 * ========================================================================= *
 *                                                                           *
 * This software  consists of voluntary  contributions made  by many indivi- *
 * duals on behalf of the  Apache Software Foundation.  For more information *
 * on the Apache Software Foundation, please see <http://www.apache.org/>.   *
 *                                                                           *
 * ========================================================================= */
package org.apache.catalina.connector.warp;

public class Constants {
    /** Our package name. */
    public static final String PACKAGE="org.apache.catalina.connector.warp";

    /** Compile-in debug flag. */
    public static final boolean DEBUG=false;

    /**
     * The WARP protocol major version.
     */
    public static final int VERS_MAJOR=0;

    /**
     * The WARP protocol minor version.
     */
    public static final int VERS_MINOR=10;

    /**
     * INVALID: The packet type hasn't been set yet.
     */
    public static final int TYPE_INVALID=-1;

    /**
     * ERROR: The last operation didn't completed correctly.
     * <br>
     * Payload description:<br>
     * [string] An error message.<br>
     */
    public static final int TYPE_ERROR=0x00;

    /**
     * DISCONNECT: The connection is being closed.
     * <br>
     * No payload:<br>
     */
    public static final int TYPE_DISCONNECT=0xfe;

    /**
     * FATAL: A protocol error occourred, the connection must be closed.
     * <br>
     * Payload description:<br>
     * [string] An error message.<br>
     */
    public static final int TYPE_FATAL=0xff;

    /**
     * CONF_WELCOME: The server issues this packet when a connection is
     * opened. The server awaits for configuration information.
     * <br>
     * Payload description:<br>
     * [ushort] Major protocol version.<br>
     * [ushort] Minor protocol version.<br>
     * [integer] The server unique-id.<br>
     */
    public static final int TYPE_CONF_WELCOME=0x01;

    /**
     * CONF_ENUM: The client requests to the server to enumerate all
     * web-applications available for a specified virtual host. In response
     * to this request, the server replies with a set of CONF_ENUM messages
     * terminated by a CONF_ENUM_DONE message.
     * <br>
     * Payload description:<br>
     * [string] The virtual host name.<br>
     * [ushort] The virtual host port.<br>
     */
    public static final int TYPE_CONF_ENUM=0x02;

    /**
     * CONF_ENUM_APPL: The server specifies the name of a web-application
     * available for deployment in response to a CONF_ENUMERATE message.
     * <br>
     * Payload description:<br>
     * [string] The web-application name.<br>
     */
    public static final int TYPE_CONF_ENUM_APPL=0x03;

    /**
     * CONF_ENUM_DONE: The server specifies all web-application names
     * available for deployment for the host specified in the CONF_ENUM
     * message have been transfered.
     * <br>
     * No payload:<br>
     */
    public static final int TYPE_CONF_ENUM_DONE=0x04;

    /**
     * CONF_DEPLOY: The client attempts deploy a web application.
     * <br>
     * Payload description:<br>
     * [string] The application name.<br>
     * [string] The virtual host name.<br>
     * [ushort] The virtual host port.<br>
     * [string] The web-application URL path.<br>
     */
    public static final int TYPE_CONF_DEPLOY=0x05;

    /**
     * CONF_APPLIC: The server replies to a CONF_DEPLOY message with the web
     * application identifier of the configured application.
     * <br>
     * Payload description:<br>
     * [integer] The web application unique id for this server.<br>
     * [string] The web application real path (where it's expanded).<br>
     */
    public static final int TYPE_CONF_APPLIC=0x06;

    /**
     * CONF_MAP: The client requests to the server to enumerate all mappings
     * for a specified web-application. The server replies to this message
     * with a serie of MAP_ALLOW and MAP_DENY packets, terminated by a
     * MAP_DONE packet.
     * <br>
     * Payload description:<br>
     * [integer] The web application unique id for this server.<br>
     */
    public static final int TYPE_CONF_MAP=0x07;

    /**
     * CONF_MAP_ALLOW: The server replies to a CONF_MAP message with this
     * packet to indicate a mapping to a static page, or a resource that
     * can be served autonomously by the remote end (the web server).
     * <br>
     * Payload description:<br>
     * [string] An url-pattern as defined by the Servlet specification.
     */
    public static final int TYPE_CONF_MAP_ALLOW=0x08;

    /**
     * CONF_MAP_DENY: The server replies to a CONF_MAP message with this
     * packet to indicate a mapping to a resource that must be served by
     * the server (servlet container).
     * <br>
     * Payload description:<br>
     * [string] An url-pattern as defined by the Servlet specification.
     */
    public static final int TYPE_CONF_MAP_DENY=0x09;

    /**
     * CONF_MAP_DONE: The server replies to a CONF_MAP message with this
     * packet to indicate that all servlet mappings have been successfully
     * transfered to the other end
     * <br>
     * No payload:<br>
     */
    public static final int TYPE_CONF_MAP_DONE=0x0a;

    /**
     * CONF_DONE: Client issues this message when all configurations have been
     * processed.
     * <br>
     * No payload:<br>
     */
    public static final int TYPE_CONF_DONE=0x0e;

    /**
     * CONF_PROCEED: Server issues this message in response to a CONF_DONE
     * message, to acknowledge its readiness to accept requests.
     * <br>
     * No payload:<br>
     */
    public static final int TYPE_CONF_PROCEED=0x0f;

    /**
     * REQ_INIT: The client requests to the WARP server that a request is
     * about to be processed.
     * <br>
     * Payload description:<br>
     * [integer] The web-application unique ID for this server.<br>
     * [string] The HTTP method used for this request.<br>
     * [string] The request URI.<br>
     * [string] The request query arguments.<br>
     * [string] The request protocol (HTTP/1.0, HTTP/1.1...).<br>
     */
    public static final int TYPE_REQ_INIT=0x10;

    /**
     * REQ_CONTENT: The mime content type and length of this request.
     * <br>
     * Payload description:<br>
     * [string] The MIME content type of this reques.<br>
     * [integer] The content length of this request.<br>
     */
    public static final int TYPE_REQ_CONTENT=0x11;

    /**
     * REQ_SCHEME: The scheme description of this request.
     * <br>
     * Payload description:<br>
     * [string] The scheme (part before :// in the URL) of this request.<br>
     */
    public static final int TYPE_REQ_SCHEME=0x12;

    /**
     * REQ_AUTH: Authentication information of the HTTP remote peer.
     * <br>
     * Payload description:<br>
     * [string] The remote-user name.<br>
     * [string] The authentication information.<br>
     */
    public static final int TYPE_REQ_AUTH=0x13;

    /**
     * REQ_HEADER: An HTTP request header.
     * <br>
     * Payload description:<br>
     * [string] The header name.<br>
     * [string] The header value.<br>
     */
    public static final int TYPE_REQ_HEADER=0x14;

    /**
     * REQ_SERVER: The HTTP server information.
     * <br>
     * Payload description:<br>
     * [string] The HTTP server host name.
     * [string] The HTTP server IP address.
     * [ushort] The port receiving the HTTP request.
     */
    public static final int TYPE_REQ_SERVER=0x15;

    /**
     * REQ_CLIENT: The HTTP client (remote peer) information.
     * <br>
     * Payload description:<br>
     * [string] The HTTP client host name.
     * [string] The HTTP client IP address.
     * [ushort] The remote port originating the HTTP request.
     */
    public static final int TYPE_REQ_CLIENT=0x16;

    /**
     * REQ_PROCEED: The client finished transmitting the request. The server
     * can now proceed and process the request.
     * <br>
     * No payload.<br>
     */
    public static final int TYPE_REQ_PROCEED=0x1f;

    /**
     * RES_STATUS: The server replies with the HTTP response status for the
     * request.
     * <br>
     * Payload description:<br>
     * [ushort] The HTTP status of the response.<br>
     * [string] The HTTP response message.<br>
     */
    public static final int TYPE_RES_STATUS=0x20;

    /**
     * RES_HEADER: An HTTP MIME response header to send to the client.
     * <br>
     * Payload description:<br>
     * [string] The MIME header name.<br>
     * [string] The MIME header value.<br>
     */
    public static final int TYPE_RES_HEADER=0x21;

    /**
     * RES_COMMIT: The server indicates that the first part of the response
     * (HTTP status line and MIME headers) are to be committed to the client
     * (remote peer).
     * <br>
     * No payload.<br>
     */
    public static final int TYPE_RES_COMMIT=0x2f;

    /**
     * RES_BODY: The HTTP response body.
     * <br>
     * Payload description:<br>
     * [raw] A chunk of the response body.<br>
     */
    public static final int TYPE_RES_BODY=0x30;

    /**
     * RES_DONE: The server finished transmitting the response.
     * <br>
     * No payload.<br>
     */
    public static final int TYPE_RES_DONE=0x3f;

    /**
     * CBK_READ: A request callback. The WARP server queries the WARP client
     * (HTTP server) to transmit a chunk of the request body.
     * <br>
     * Payload description:<br>
     * [ushort] The number of bytes the server needs to transmit.<br>
     */
    public static final int TYPE_CBK_READ=0x40;

    /**
     * CBK_DATA: As requested by the WARP server, the WARP client (HTTP
     * server) transmits a chunk of the request body.
     * <br>
     * Payload description:<br>
     * [raw] A chunk of the request body.<br>
     */
    public static final int TYPE_CBK_DATA=0x41;

    /**
     * CBK_DATA: The WARP client (HTTP server) informs the WARP server that
     * the request body has been fully transmitted.
     * <br>
     * No payload.<br>
     */
    public static final int TYPE_CBK_DONE=0x42;
}
