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
 * 4. The names  "The  Jakarta  Project",  "WebApp",  and  "Apache  Software *
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

/* @version $Id: dso-dyld.c,v 1.1 2001/06/26 01:36:18 pier Exp $ */
#include "jsvc.h"

#ifdef DSO_DYLD

#include <mach-o/dyld.h>

/* Print an error message and abort all if a specified symbol wasn't found */
static void nosymbol(const char *s) {
    log_error("Cannot find symbol '%s' in library",s);
    abort();
}

/* We found two symbols for the same name in two different modules */
static NSModule multiple(NSSymbol s, NSModule om, NSModule nm) {
    NSModule ret=nm;

    log_debug("Symbol \"%s\" found in modules \"%s\" and \"%s\" (using %s)",
        NSNameOfSymbol(s), NSNameOfModule(om), NSNameOfModule(nm),
        NSNameOfModule(ret));

    return(ret);
}

/* We got an error while linking a module, and if it's not a warning we have
   to abort the whole program */
static void linkedit(NSLinkEditErrors category, int number, const char *file,
                     const char *message) {
    log_error("Errors during link edit of file \"%s\" (error=%d): %s", file,
              number,message);
    /* Check if this error was only a warning */
    if (category!=NSLinkEditWarningError) {
        log_error("Cannot continue");
        abort();
    }
}

/* Initialize all DSO stuff */
bool dso_init() {
    NSLinkEditErrorHandlers h;

    h.undefined=nosymbol;
    h.multiple=multiple;
    h.linkEdit=linkedit;

    NSInstallLinkEditErrorHandlers(&h);
    return(true);
}

/* Attempt to link a library from a specified filename */
dso_handle dso_link(const char *path) {
    /* We need to load the library publically as NSModuleFileImage is not
       yet implemented (at least for non MH_BUNDLE libraries */
    if (NSAddLibrary(path)!=TRUE) return(NULL);
    /* We need to return a non-null value, even if it has no meaning. One day
       this whole crap will be fixed */
    return((void *)!NULL);
}

/* Attempt to unload a library */
bool dso_unlink(dso_handle libr) {
    /* Check the handle */
    if (libr==NULL) {
        log_error("Attempting to unload a module without handle");
        return(false);
    }

    /* We don't have a module, so, we don't really have to do anything */
    return(true);
}

/* Get the address for a specifed symbol */
void *dso_symbol(dso_handle hdl, const char *nam) {
    NSSymbol sym=NULL;
    NSModule mod=NULL;
    char *und=NULL;
    void *add=NULL;
    int x=0;

    /* Check parameters */
    if (hdl==NULL) {
        log_error("Invalid library handler specified");
        return(NULL);
    }

    if (nam==NULL) {
        log_error("Invalid symbol name specified");
        return(NULL);
    }

    /* Process the correct name (add a _ before the name) */
    while (nam[x]!='\0') x++;
    und=(char*)malloc(sizeof(char)*(x+2));
    while(x>=0) und[x+1]=nam[x--];
    und[0]='_';

    /* Find the symbol */
    sym=NSLookupAndBindSymbol(und);
    free(und);
    if (sym==NULL) return(NULL);

    /* Dump some debugging output since this part is shaky */
    mod=NSModuleForSymbol(sym);
    add=NSAddressOfSymbol(sym);
    log_debug("Symbol \"%s\" found in module \"%s\" at address \"0x%08X\"",
              NSNameOfSymbol(sym),NSNameOfModule(mod),add);

    /* We want to return the address of the symbol */
    return(add);
}

#endif /* ifdef DSO_DYLD */
