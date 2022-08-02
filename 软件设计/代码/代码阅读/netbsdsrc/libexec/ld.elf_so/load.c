/*	$NetBSD: load.c,v 1.1 1996/12/16 20:37:59 cgd Exp $	*/

/*
 * Copyright 1996 John D. Polstra.
 * Copyright 1996 Matt Thomas <matt@3am-software.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by John Polstra.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Dynamic linker for ELF.
 *
 * John Polstra <jdp@polstra.com>.
 */

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <dirent.h>

#include "debug.h"
#include "rtld.h"

/*
 * Load a shared object into memory, if it is not already loaded.  The
 * argument must be a string allocated on the heap.  This function assumes
 * responsibility for freeing it when necessary.
 *
 * Returns a pointer to the Obj_Entry for the object.  Returns NULL
 * on failure.
 */
Obj_Entry *
_rtld_load_object(
    char *filepath)
{
    Obj_Entry *obj;

    for (obj = _rtld_objlist->next;  obj != NULL;  obj = obj->next)
	if (strcmp(obj->path, filepath) == 0)
	    break;

    if (obj == NULL) {	/* First use of this object, so we must map it in */
	int fd;

	if ((fd = open(filepath, O_RDONLY)) == -1) {
	    _rtld_error("Cannot open \"%s\"", filepath);
	    return NULL;
	}
	obj = _rtld_map_object(filepath, fd);
	close(fd);
	if (obj == NULL) {
	    free(filepath);
	    return NULL;
	}

	obj->path = filepath;
	_rtld_digest_dynamic(obj);

	*_rtld_objtail = obj;
	_rtld_objtail = &obj->next;
#ifdef RTLD_LOADER
	_rtld_linkmap_add(obj);		/* for GDB */
#endif

	dbg("  %p .. %p: %s", obj->mapbase,
	    obj->mapbase + obj->mapsize - 1, obj->path);
	if (obj->textrel)
	    dbg("  WARNING: %s has impure text", obj->path);
    } else
	free(filepath);

    ++obj->refcount;
    return obj;
}

/*
 * Given a shared object, traverse its list of needed objects, and load
 * each of them.  Returns 0 on success.  Generates an error message and
 * returns -1 on failure.
 */
int
_rtld_load_needed_objects(
    Obj_Entry *first)
{
    Obj_Entry *obj;
    int status = 0;

    for (obj = first;  obj != NULL;  obj = obj->next) {
	Needed_Entry *needed;

	for (needed = obj->needed;  needed != NULL;  needed = needed->next) {
	    const char *name = obj->strtab + needed->name;
	    char *libpath = _rtld_find_library(name, obj);

	    if (libpath == NULL) {
		status = -1;
	    } else {
		needed->obj = _rtld_load_object(libpath);
		if (needed->obj == NULL)
		    status = -1;		/* FIXME - cleanup */
	    }
#ifdef RTLD_LOADER
	    if (status == -1)
		return status;
#endif
	}
    }

    return status;
}
