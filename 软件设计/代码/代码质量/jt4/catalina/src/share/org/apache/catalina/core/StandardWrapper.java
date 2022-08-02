/*
 * $Header: /home/cvspublic/jakarta-tomcat-4.0/catalina/src/share/org/apache/catalina/core/StandardWrapper.java,v 1.29 2001/08/23 16:42:26 craigmcc Exp $
 * $Revision: 1.29 $
 * $Date: 2001/08/23 16:42:26 $
 *
 * ====================================================================
 *
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


package org.apache.catalina.core;


import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.Enumeration;
import java.util.HashMap;
import javax.servlet.Servlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.SingleThreadModel;
import javax.servlet.UnavailableException;
import javax.servlet.http.HttpServletResponse;
import org.apache.catalina.Container;
import org.apache.catalina.ContainerServlet;
import org.apache.catalina.Context;
import org.apache.catalina.InstanceEvent;
import org.apache.catalina.InstanceListener;
import org.apache.catalina.Lifecycle;
import org.apache.catalina.LifecycleException;
import org.apache.catalina.Loader;
import org.apache.catalina.Logger;
import org.apache.catalina.Request;
import org.apache.catalina.Response;
import org.apache.catalina.Wrapper;
import org.apache.catalina.loader.StandardClassLoader;
import org.apache.catalina.util.Enumerator;
import org.apache.catalina.util.InstanceSupport;


/**
 * Standard implementation of the <b>Wrapper</b> interface that represents
 * an individual servlet definition.  No child Containers are allowed, and
 * the parent Container must be a Context.
 * <p>
 * <b>IMPLEMENTATION NOTE</b>:  This implementation does <i>not</i> support
 * a pool of instances for servlets that implement SingleThreadModel.  IMHO
 * developers should not be encouraged to use this technique, so efforts to
 * make them efficient are counter-productive.
 *
 * @author Craig R. McClanahan
 * @version $Revision: 1.29 $ $Date: 2001/08/23 16:42:26 $
 */

public final class StandardWrapper
    extends ContainerBase
    implements ServletConfig, Wrapper {


    // ----------------------------------------------------------- Constructors


    /**
     * Create a new StandardWrapper component with the default basic Valve.
     */
    public StandardWrapper() {

        super();
        pipeline.setBasic(new StandardWrapperValve());

    }


    // ----------------------------------------------------- Instance Variables


    /**
     * Has our SingleThreadModel servlet instance been allocated already?
     */
    private boolean allocated = false;


    /**
     * The date and time at which this servlet will become available (in
     * milliseconds since the epoch), or zero if the servlet is available.
     * If this value equals Long.MAX_VALUE, the unavailability of this
     * servlet is considered permanent.
     */
    private long available = 0L;


    /**
     * The count of allocations that are currently active (even if they
     * are for the same instance, as will be true on a non-STM servlet).
     */
    private int countAllocated = 0;


    /**
     * The debugging detail level for this component.
     */
    private int debug = 0;


    /**
     * The facade associated with this wrapper.
     */
    private StandardWrapperFacade facade =
        new StandardWrapperFacade(this);


    /**
     * The descriptive information string for this implementation.
     */
    private static final String info =
        "org.apache.catalina.core.StandardWrapper/1.0";


    /**
     * The (single) initialized instance of this servlet.
     */
    private Servlet instance = null;


    /**
     * The support object for our instance listeners.
     */
    private InstanceSupport instanceSupport = new InstanceSupport(this);


    /**
     * The specialized class loader for the Jasper JSP servlet.
     */
    private ClassLoader jasperLoader = null;


    /**
     * The context-relative URI of the JSP file for this servlet.
     */
    private String jspFile = null;


    /**
     * The load-on-startup order value (negative value means load on
     * first call) for this servlet.
     */
    private int loadOnStartup = -1;


    /**
     * The initialization parameters for this servlet, keyed by
     * parameter name.
     */
    private HashMap parameters = new HashMap();


    /**
     * The security role references for this servlet, keyed by role name
     * used in the servlet.  The corresponding value is the role name of
     * the web application itself.
     */
    private HashMap references = new HashMap();


    /**
     * The run-as identity for this servlet.
     */
    private String runAs = null;


    /**
     * The fully qualified servlet class name for this servlet.
     */
    private String servletClass = null;


    /**
     * Does this servlet implement the SingleThreadModel interface?
     */
    private boolean singleThreadModel = false;


    /**
     * Are we unloading our servlet instance at the moment?
     */
    private boolean unloading = false;


    // ------------------------------------------------------------- Properties


    /**
     * Return the available date/time for this servlet, in milliseconds since
     * the epoch.  If this date/time is in the future, any request for this
     * servlet will return an SC_SERVICE_UNAVAILABLE error.  If it is zero,
     * the servlet is currently available.  A value equal to Long.MAX_VALUE
     * is considered to mean that unavailability is permanent.
     */
    public long getAvailable() {

        return (this.available);

    }


    /**
     * Set the available date/time for this servlet, in milliseconds since the
     * epoch.  If this date/time is in the future, any request for this servlet
     * will return an SC_SERVICE_UNAVAILABLE error.
     *
     * @param available The new available date/time
     */
    public void setAvailable(long available) {

        long oldAvailable = this.available;
        if (available > System.currentTimeMillis())
            this.available = available;
        else
            this.available = 0L;
        support.firePropertyChange("available", new Long(oldAvailable),
                                   new Long(this.available));

    }


    /**
     * Return the number of active allocations of this servlet, even if they
     * are all for the same instance (as will be true for servlets that do
     * not implement <code>SingleThreadModel</code>.
     */
    public int getCountAllocated() {

        return (this.countAllocated);

    }


    /**
     * Return the debugging detail level for this component.
     */
    public int getDebug() {

        return (this.debug);

    }


    /**
     * Set the debugging detail level for this component.
     *
     * @param debug The new debugging detail level
     */
    public void setDebug(int debug) {

        int oldDebug = this.debug;
        this.debug = debug;
        support.firePropertyChange("debug", new Integer(oldDebug),
                                   new Long(this.debug));

    }


    /**
     * Return descriptive information about this Container implementation and
     * the corresponding version number, in the format
     * <code>&lt;description&gt;/&lt;version&gt;</code>.
     */
    public String getInfo() {

        return (info);

    }


    /**
     * Return the InstanceSupport object for this Wrapper instance.
     */
    public InstanceSupport getInstanceSupport() {

        return (this.instanceSupport);

    }


    /**
     * Return the context-relative URI of the JSP file for this servlet.
     */
    public String getJspFile() {

        return (this.jspFile);

    }


    /**
     * Set the context-relative URI of the JSP file for this servlet.
     *
     * @param jspFile JSP file URI
     */
    public void setJspFile(String jspFile) {

        //        if ((jspFile != null) && !jspFile.startsWith("/"))
        //        throw new IllegalArgumentException
        //                (sm.getString("standardWrapper.jspFile.format", jspFile));

        String oldJspFile = this.jspFile;
        this.jspFile = jspFile;
        support.firePropertyChange("jspFile", oldJspFile, this.jspFile);

    }


    /**
     * Return the load-on-startup order value (negative value means
     * load on first call).
     */
    public int getLoadOnStartup() {

        return (this.loadOnStartup);

    }


    /**
     * Set the load-on-startup order value (negative value means
     * load on first call).
     *
     * @param value New load-on-startup value
     */
    public void setLoadOnStartup(int value) {

        int oldLoadOnStartup = this.loadOnStartup;
        this.loadOnStartup = value;
        support.firePropertyChange("loadOnStartup",
                                   new Integer(oldLoadOnStartup),
                                   new Integer(this.loadOnStartup));

    }



    /**
     * Set the load-on-startup order value from a (possibly null) string.
     * Per the specification, any missing or non-numeric value is converted
     * to a zero, so that this servlet will still be loaded at startup
     * time, but in an arbitrary order.
     *
     * @param value New load-on-startup value
     */
    public void setLoadOnStartupString(String value) {

        try {
            setLoadOnStartup(Integer.parseInt(value));
        } catch (NumberFormatException e) {
            setLoadOnStartup(0);
        }

    }



    /**
     * Set the parent Container of this Wrapper, but only if it is a Context.
     *
     * @param container Proposed parent Container
     */
    public void setParent(Container container) {

        if ((container != null) &&
            !(container instanceof Context))
            throw new IllegalArgumentException
                (sm.getString("standardWrapper.notContext"));
        super.setParent(container);

    }


    /**
     * Return the run-as identity for this servlet.
     */
    public String getRunAs() {

        return (this.runAs);

    }


    /**
     * Set the run-as identity for this servlet.
     *
     * @param value New run-as identity value
     */
    public void setRunAs(String runAs) {

        String oldRunAs = this.runAs;
        this.runAs = runAs;
        support.firePropertyChange("runAs", oldRunAs, this.runAs);

    }


    /**
     * Return the fully qualified servlet class name for this servlet.
     */
    public String getServletClass() {

        return (this.servletClass);

    }


    /**
     * Set the fully qualified servlet class name for this servlet.
     *
     * @param servletClass Servlet class name
     */
    public void setServletClass(String servletClass) {

        String oldServletClass = this.servletClass;
        this.servletClass = servletClass;
        support.firePropertyChange("servletClass", oldServletClass,
                                   this.servletClass);

    }



    /**
     * Set the name of this servlet.  This is an alias for the normal
     * <code>Container.setName()</code> method, and complements the
     * <code>getServletName()</code> method required by the
     * <code>ServletConfig</code> interface.
     *
     * @param name The new name of this servlet
     */
    public void setServletName(String name) {

        setName(name);

    }


    /**
     * Return <code>true</code> if the servlet class represented by this
     * component implements the <code>SingleThreadModel</code> interface.
     */
    public boolean isSingleThreadModel() {

        try {
            load();
        } catch (Throwable t) {
            ;
        }
        return (singleThreadModel);

    }


    /**
     * Is this servlet currently unavailable?
     */
    public boolean isUnavailable() {

        if (available == 0L)
            return (false);
        else if (available <= System.currentTimeMillis()) {
            available = 0L;
            return (false);
        } else
            return (true);

    }


    // --------------------------------------------------------- Public Methods


    /**
     * Refuse to add a child Container, because Wrappers are the lowest level
     * of the Container hierarchy.
     *
     * @param child Child container to be added
     */
    public void addChild(Container child) {

        throw new IllegalStateException
            (sm.getString("standardWrapper.notChild"));

    }


    /**
     * Add a new servlet initialization parameter for this servlet.
     *
     * @param name Name of this initialization parameter to add
     * @param value Value of this initialization parameter to add
     */
    public void addInitParameter(String name, String value) {

        synchronized (parameters) {
            parameters.put(name, value);
        }
        fireContainerEvent("addInitParameter", name);

    }


    /**
     * Add a new listener interested in InstanceEvents.
     *
     * @param listener The new listener
     */
    public void addInstanceListener(InstanceListener listener) {

        instanceSupport.addInstanceListener(listener);

    }


    /**
     * Add a new security role reference record to the set of records for
     * this servlet.
     *
     * @param name Role name used within this servlet
     * @param link Role name used within the web application
     */
    public void addSecurityReference(String name, String link) {

        synchronized (references) {
            references.put(name, link);
        }
        fireContainerEvent("addSecurityReference", name);

    }


    /**
     * Allocate an initialized instance of this Servlet that is ready to have
     * its <code>service()</code> method called.  If the servlet class does
     * not implement <code>SingleThreadModel</code>, the (only) initialized
     * instance may be returned immediately.  If the servlet class implements
     * <code>SingleThreadModel</code>, the Wrapper implementation must ensure
     * that this instance is not allocated again until it is deallocated by a
     * call to <code>deallocate()</code>.
     * <p>
     * <b>FIXME:  Provide a way to avoid waiting forever.</b>
     *
     * @exception ServletException if the servlet init() method threw
     *  an exception
     * @exception ServletException if a loading error occurs
     */
    public Servlet allocate() throws ServletException {

        if (debug >= 1)
            log("Allocating an instance");

        // If we are currently unloading this servlet, throw an exception
        if (unloading)
            throw new ServletException
              (sm.getString("standardWrapper.unloading", getName()));

        // Load and initialize our instance if necessary
        if (instance == null) {
            try {
                load();
            } catch (ServletException e) {
                throw e;
            } catch (Throwable e) {
                throw new ServletException
                    (sm.getString("standardWrapper.allocate"), e);
            }
        }

        // If not SingleThreadedModel, return the same instance every time
        if (!singleThreadModel) {
            if (debug >= 2)
                log("  Returning non-STM instance");
            countAllocated++;
            return (instance);
        }

        // Lock and return this instance
        synchronized (instance) {
            if (allocated) {
                if (debug >= 2)
                    log("  Waiting for allocated STM instance");
                try {
                    instance.wait();
                } catch (InterruptedException e) {
                    ;
                }
            }
            if (debug >= 2)
                log("  Returning allocated STM instance");
            allocated = true;
            countAllocated++;
            return (instance);
        }

    }


    /**
     * Return this previously allocated servlet to the pool of available
     * instances.  If this servlet class does not implement SingleThreadModel,
     * no action is actually required.
     *
     * @param servlet The servlet to be returned
     *
     * @exception ServletException if a deallocation error occurs
     */
    public void deallocate(Servlet servlet) throws ServletException {

        countAllocated--;

        // If not SingleThreadModel, no action is required
        if (!singleThreadModel)
            return;

        // Unlock and free this instance
        synchronized (instance) {
            allocated = false;
            instance.notify();
        }

    }


    /**
     * Return the value for the specified initialization parameter name,
     * if any; otherwise return <code>null</code>.
     *
     * @param name Name of the requested initialization parameter
     */
    public String findInitParameter(String name) {

        synchronized (parameters) {
            return ((String) parameters.get(name));
        }

    }


    /**
     * Return the names of all defined initialization parameters for this
     * servlet.
     */
    public String[] findInitParameters() {

        synchronized (parameters) {
            String results[] = new String[parameters.size()];
            return ((String[]) parameters.keySet().toArray(results));
        }

    }


    /**
     * Return the security role link for the specified security role
     * reference name, if any; otherwise return <code>null</code>.
     *
     * @param name Security role reference used within this servlet
     */
    public String findSecurityReference(String name) {

        synchronized (references) {
            return ((String) references.get(name));
        }

    }


    /**
     * Return the set of security role reference names associated with
     * this servlet, if any; otherwise return a zero-length array.
     */
    public String[] findSecurityReferences() {

        synchronized (references) {
            String results[] = new String[references.size()];
            return ((String[]) references.keySet().toArray(results));
        }

    }


    /**
     * Load and initialize an instance of this servlet, if there is not already
     * at least one initialized instance.  This can be used, for example, to
     * load servlets that are marked in the deployment descriptor to be loaded
     * at server startup time.
     * <p>
     * <b>IMPLEMENTATION NOTE</b>:  Servlets whose classnames begin with
     * <code>org.apache.catalina.</code> (so-called "container" servlets)
     * are loaded by the same classloader that loaded this class, rather than
     * the classloader for the current web application.
     * This gives such classes access to Catalina internals, which are
     * prevented for classes loaded for web applications.
     *
     * @exception ServletException if the servlet init() method threw
     *  an exception
     * @exception ServletException if some other loading problem occurs
     */
    public synchronized void load() throws ServletException {

        // Nothing to do if we already have an instance
        if (instance != null)
            return;

        // If this "servlet" is really a JSP file, get the right class.
        // HOLD YOUR NOSE - this is a kludge that avoids having to do special
        // case Catalina-specific code in Jasper - it also requires that the
        // servlet path be replaced by the <jsp-file> element content in
        // order to be completely effective
        String actualClass = servletClass;
        if ((actualClass == null) && (jspFile != null)) {
            Wrapper jspWrapper = (Wrapper)
                ((Context) getParent()).findChild(Constants.JSP_SERVLET_NAME);
            if (jspWrapper != null)
                actualClass = jspWrapper.getServletClass();
        }

        // Complain if no servlet class has been specified
        if (actualClass == null) {
            unavailable(null);
            throw new ServletException
                (sm.getString("standardWrapper.notClass", getName()));
        }

        // Acquire an instance of the class loader to be used
        Loader loader = getLoader();
        if (loader == null) {
            unavailable(null);
            throw new ServletException
                (sm.getString("standardWrapper.missingLoader", getName()));
        }

        ClassLoader classLoader = loader.getClassLoader();

        // Special case class loader for a Catalina internal servlet
        if (isContainerServlet(actualClass)) {
            classLoader = this.getClass().getClassLoader();
            log(sm.getString
                  ("standardWrapper.containerServlet", getName()));
        }

        // Special case class loader for the Jasper JSP servlet
        if (actualClass.equals(Constants.JSP_SERVLET_CLASS)) {
            classLoader = ((StandardContext) getParent()).getJasperLoader();
            log(sm.getString("standardWrapper.jasperLoader", getName()));
        }

        // Load the specified servlet class from the appropriate class loader
        Class classClass = null;
        try {
            if (classLoader != null) {
                classClass = classLoader.loadClass(actualClass);
            } else {
                classClass = Class.forName(actualClass);
            }
        } catch (ClassNotFoundException e) {
            unavailable(null);
            throw new ServletException
                (sm.getString("standardWrapper.missingClass", actualClass),
                 e);
        }
        if (classClass == null) {
            unavailable(null);
            throw new ServletException
                (sm.getString("standardWrapper.missingClass", actualClass));
        }

        // Instantiate and initialize an instance of the servlet class itself
        Servlet servlet = null;
        try {
            servlet = (Servlet) classClass.newInstance();
        } catch (ClassCastException e) {
            unavailable(null);
            // Restore the context ClassLoader
            throw new ServletException
                (sm.getString("standardWrapper.notServlet", actualClass), e);
        } catch (Throwable e) {
            unavailable(null);
            // Restore the context ClassLoader
            throw new ServletException
                (sm.getString("standardWrapper.instantiate", actualClass), e);
        }

        // Special handling for ContainerServlet instances
        if ((servlet instanceof ContainerServlet) &&
            isContainerServlet(actualClass)) {
            ((ContainerServlet) servlet).setWrapper(this);
        }


        // Call the initialization method of this servlet
        try {
            instanceSupport.fireInstanceEvent(InstanceEvent.BEFORE_INIT_EVENT,
                                              servlet);
            servlet.init(facade);
            instanceSupport.fireInstanceEvent(InstanceEvent.AFTER_INIT_EVENT,
                                              servlet);
        } catch (UnavailableException f) {
            instanceSupport.fireInstanceEvent(InstanceEvent.AFTER_INIT_EVENT,
                                              servlet);
            unavailable(f);
            throw f;
        } catch (ServletException f) {
            instanceSupport.fireInstanceEvent(InstanceEvent.AFTER_INIT_EVENT,
                                              servlet);
            // If the servlet wanted to be unavailable it would have
            // said so, so do not call unavailable(null).
            throw f;
        } catch (Throwable f) {
            instanceSupport.fireInstanceEvent(InstanceEvent.AFTER_INIT_EVENT,
                                              servlet);
            // If the servlet wanted to be unavailable it would have
            // said so, so do not call unavailable(null).
            throw new ServletException
                (sm.getString("standardWrapper.initException", getName()), f);
        }

        // Register our newly initialized instance
        instance = servlet;
        singleThreadModel = instance instanceof SingleThreadModel;
        fireContainerEvent("load", this);

    }


    /**
     * Remove the specified initialization parameter from this servlet.
     *
     * @param name Name of the initialization parameter to remove
     */
    public void removeInitParameter(String name) {

        synchronized (parameters) {
            parameters.remove(name);
        }
        fireContainerEvent("removeInitParameter", name);

    }


    /**
     * Remove a listener no longer interested in InstanceEvents.
     *
     * @param listener The listener to remove
     */
    public void removeInstanceListener(InstanceListener listener) {

        instanceSupport.removeInstanceListener(listener);

    }


    /**
     * Remove any security role reference for the specified role name.
     *
     * @param name Security role used within this servlet to be removed
     */
    public void removeSecurityReference(String name) {

        synchronized (references) {
            references.remove(name);
        }
        fireContainerEvent("removeSecurityReference", name);

    }


    /**
     * Return a String representation of this component.
     */
    public String toString() {

        StringBuffer sb = new StringBuffer();
        if (getParent() != null) {
            sb.append(getParent().toString());
            sb.append(".");
        }
        sb.append("StandardWrapper[");
        sb.append(getName());
        sb.append("]");
        return (sb.toString());

    }


    /**
     * Process an UnavailableException, marking this servlet as unavailable
     * for the specified amount of time.
     *
     * @param unavailable The exception that occurred, or <code>null</code>
     *  to mark this servlet as permanently unavailable
     */
    public void unavailable(UnavailableException unavailable) {
        log(sm.getString("standardWrapper.unavailable", getName()));
        if (unavailable == null)
            setAvailable(Long.MAX_VALUE);
        else if (unavailable.isPermanent())
            setAvailable(Long.MAX_VALUE);
        else {
            int unavailableSeconds = unavailable.getUnavailableSeconds();
            if (unavailableSeconds <= 0)
                unavailableSeconds = 60;        // Arbitrary default
            setAvailable(System.currentTimeMillis() +
                         (unavailableSeconds * 1000L));
        }

    }


    /**
     * Unload all initialized instances of this servlet, after calling the
     * <code>destroy()</code> method for each instance.  This can be used,
     * for example, prior to shutting down the entire servlet engine, or
     * prior to reloading all of the classes from the Loader associated with
     * our Loader's repository.
     *
     * @exception ServletException if an exception is thrown by the
     *  destroy() method
     */
    public synchronized void unload() throws ServletException {

        // Nothing to do if we have never loaded the instance
        if (instance == null)
            return;
        unloading = true;

        // Loaf a while if the current instance is allocated
        // (possibly more than once if non-STM)
        if (countAllocated > 0) {
            boolean first = true;
            while (countAllocated > 0) {
                if (first) {
                    log("Waiting for " + countAllocated +
                        " instance(s) to be deallocated");
                    first = false;
                }
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    ;
                }
            }
        }

        ClassLoader oldCtxClassLoader =
            Thread.currentThread().getContextClassLoader();
        ClassLoader classLoader = instance.getClass().getClassLoader();

        // Call the servlet destroy() method
        try {
            instanceSupport.fireInstanceEvent
              (InstanceEvent.BEFORE_DESTROY_EVENT, instance);
            Thread.currentThread().setContextClassLoader(classLoader);
            instance.destroy();
            instanceSupport.fireInstanceEvent
              (InstanceEvent.AFTER_DESTROY_EVENT, instance);
        } catch (Throwable t) {
            instanceSupport.fireInstanceEvent
              (InstanceEvent.AFTER_DESTROY_EVENT, instance);
            instance = null;
            fireContainerEvent("unload", this);
            unloading = false;
            throw new ServletException
                (sm.getString("standardWrapper.destroyException", getName()),
                 t);
        } finally {
            // restore the context ClassLoader
            Thread.currentThread().setContextClassLoader(oldCtxClassLoader);
        }

        // Deregister the destroyed instance
        instance = null;
        jasperLoader = null;
        unloading = false;
        fireContainerEvent("unload", this);

    }


    // -------------------------------------------------- ServletConfig Methods


    /**
     * Return the initialization parameter value for the specified name,
     * if any; otherwise return <code>null</code>.
     *
     * @param name Name of the initialization parameter to retrieve
     */
    public String getInitParameter(String name) {

        return (findInitParameter(name));

    }


    /**
     * Return the set of initialization parameter names defined for this
     * servlet.  If none are defined, an empty Enumeration is returned.
     */
    public Enumeration getInitParameterNames() {

        synchronized (parameters) {
            return (new Enumerator(parameters.keySet()));
        }

    }


    /**
     * Return the servlet context with which this servlet is associated.
     */
    public ServletContext getServletContext() {

        if (parent == null)
            return (null);
        else if (!(parent instanceof Context))
            return (null);
        else
            return (((Context) parent).getServletContext());

    }


    /**
     * Return the name of this servlet.
     */
    public String getServletName() {

        return (getName());

    }


    // -------------------------------------------------------- Package Methods


    // -------------------------------------------------------- Private Methods


    /**
     * Add a default Mapper implementation if none have been configured
     * explicitly.
     *
     * @param mapperClass Java class name of the default Mapper
     */
    protected void addDefaultMapper(String mapperClass) {

        ;       // No need for a default Mapper on a Wrapper

    }


    /**
     * Return <code>true</code> if the specified class name represents a
     * container class that should be loaded by the system class loader.
     *
     * @param name Name of the class to be checked
     */
    private boolean isContainerServlet(String classname) {

        if (classname.startsWith("org.apache.catalina."))
            return (true);
        else
            return (false);

    }


    /**
     * Log the abbreviated name of this Container for logging messages.
     */
    protected String logName() {

        StringBuffer sb = new StringBuffer("StandardWrapper[");
        if (getParent() != null)
            sb.append(getParent().getName());
        else
            sb.append("null");
        sb.append(':');
        sb.append(getName());
        sb.append(']');
        return (sb.toString());

    }


    // ------------------------------------------------------ Lifecycle Methods


    /**
     * Start this component, pre-loading the servlet if the load-on-startup
     * value is set appropriately.
     *
     * @exception LifecycleException if a fatal error occurs during startup
     */
    public void start() throws LifecycleException {

        // Start up this component
        super.start();

        // Load and initialize an instance of this servlet if requested
        // MOVED TO StandardContext START() METHOD

    }


    /**
     * Stop this component, gracefully shutting down the servlet if it has
     * been initialized.
     *
     * @exception LifecycleException if a fatal error occurs during shutdown
     */
    public void stop() throws LifecycleException {

        // Shut down our servlet instance (if it has been initialized)
        try {
            unload();
        } catch (ServletException e) {
            log(sm.getString("standardWrapper.unloadException", getName()), e);
        }

        // Shut down this component
        super.stop();

    }


}
