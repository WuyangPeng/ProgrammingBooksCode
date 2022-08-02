/* $XConsortium: XAuth.c /main/10 1996/11/29 20:43:59 lehors $ */
/*

Copyright (C) 1996 X Consortium

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Soft-
ware"), to deal in the Software without restriction, including without
limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to
whom the Software is furnished to do so, subject to the following condi-
tions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABIL-
ITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT
SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABIL-
ITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization from
the X Consortium.

*/

#include "RxI.h"
#include <X11/Xlib.h>
#include <X11/extensions/security.h>
#include <X11/Xauth.h>

static void
printhexdigit(char *ptr, unsigned int d)
{
    if (d > 9)
	d += 'A' - 10;
    else
	d += '0';

    sprintf(ptr, "%c", d);
}

static void
printhex(char *buffer, unsigned char *data, int len)
{
    char *ptr;
    unsigned int c;

    ptr = buffer;
    while (len--) {
	c = *data++;
	printhexdigit(ptr++, c >> 4);
	printhexdigit(ptr++, c & 0xf);
    }
    *ptr = '\0';
}

static int
MakeAuthString(char *auth_name, char *data, int len, char **auth_ret)
{
    char *auth, *ptr;
    int name_len;

    name_len = strlen(auth_name);
    /* we'll have the name + ':' + 2 characters per byte + '\0' */
    auth = (char *) Malloc(name_len + 1 + 2*len + 1);
    if (auth == NULL)
	return 1;

    strcpy(auth, auth_name);
    ptr = auth + name_len;
    *ptr++ = ':';
    printhex(ptr, (unsigned char *)data, len);

    *auth_ret = auth;

    return 0;
}

int
GetXAuth(Display *dpy, RxXAuthentication auth_name, char *auth_data,
	 Bool trusted, XID group, unsigned int timeout, Bool want_revoke_event,
	 char **auth_string_ret, XSecurityAuthorization *auth_id_ret,
	 int *event_type_base_ret)
{
    unsigned int trust =
	trusted ? XSecurityClientTrusted : XSecurityClientUntrusted;
    int dum, major_version, minor_version;
    int status;
    Xauth *auth_in, *auth_return;
    XSecurityAuthorizationAttributes xsa;
    unsigned long xsamask;

    auth_return = NULL;
    if (!XQueryExtension(dpy, "SECURITY", &dum, event_type_base_ret, &dum)) {
	fprintf(stderr, "Warning: Cannot setup authorization as requested, \
SECURITY extension not supported\n");
	return 1;
    }

    if (auth_name == MitMagicCookie1) {
	auth_in = XSecurityAllocXauth();
	auth_in->name = "MIT-MAGIC-COOKIE-1";
    } else {
	fprintf(stderr,
		"Error: Unknown authentication protocol name requested\n");
	return 1;
    }
    /* auth_data is not used for now */

    status = XSecurityQueryExtension(dpy, &major_version, &minor_version);
    if (status == 0) {
	fprintf(stderr, "Error: Failed to setup authorization\n");
	goto error;
    }

    auth_in->name_length = strlen(auth_in->name);
    if (auth_in->data)
	auth_in->data_length = strlen(auth_in->data);

    xsa.timeout     = timeout;
    xsa.trust_level = trust;
    xsa.group       = group;
    xsamask         = XSecurityTimeout | XSecurityTrustLevel | XSecurityGroup;
    if (want_revoke_event == True) {
	xsa.event_mask  = XSecurityAuthorizationRevokedMask;
	xsamask |= XSecurityEventMask;
    }
    auth_return = XSecurityGenerateAuthorization(dpy, auth_in, xsamask,
						 &xsa, auth_id_ret);
    if (auth_return == 0) {
	fprintf(stderr,
		"Error: Failed to setup authorization, cannot create key\n");
	goto error;
    }
    status = MakeAuthString(auth_in->name,
			    auth_return->data, auth_return->data_length,
			    auth_string_ret);
    if (status != 0) {
	fprintf(stderr,
		"Error: Failed to setup authorization, not enough memory\n");
	goto error;
    }
    XSecurityFreeXauth(auth_in);
    XSecurityFreeXauth(auth_return);

    return 0;

error:
    XSecurityFreeXauth(auth_in);
    if (auth_return != NULL)
	XSecurityFreeXauth(auth_return);

    return 1;
}
