/*	$NetBSD: if_ne_isapnp.c,v 1.1.2.2 1997/12/17 23:36:34 mellon Exp $	*/

/*-
 * Copyright (c) 1997 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe of the Numerical Aerospace Simulation Facility,
 * NASA Ames Research Center and Matt Thomas of the 3am Software Foundry.
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
 *	This product includes software developed by the NetBSD
 *	Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "bpfilter.h"

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/errno.h>
#include <sys/syslog.h>
#include <sys/select.h>
#include <sys/device.h>

#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_ether.h>
#include <net/if_media.h>

#ifdef INET
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
#include <netinet/if_inarp.h>
#endif

#ifdef NS
#include <netns/ns.h>
#include <netns/ns_if.h>
#endif

#if NBPFILTER > 0
#include <net/bpf.h>
#include <net/bpfdesc.h>
#endif

#include <machine/intr.h>
#include <machine/bus.h>

#include <dev/ic/dp8390reg.h>
#include <dev/ic/dp8390var.h>

#include <dev/ic/ne2000reg.h>
#include <dev/ic/ne2000var.h>

#include <dev/isa/isavar.h>

#include <dev/isapnp/isapnpreg.h>
#include <dev/isapnp/isapnpvar.h>

#ifdef __BROKEN_INDIRECT_CONFIG
static int ne_isapnp_match __P((struct device *, void *, void *));
#else
static int ne_isapnp_match __P((struct device *, struct cfdata *, void *));
#endif
static void ne_isapnp_attach __P((struct device *, struct device *, void *));

struct ne_isapnp_softc {
	struct	ne2000_softc sc_ne2000;		/* real "ne2000" softc */

	/* ISA-specific goo. */
	void	*sc_ih;				/* interrupt cookie */
};

struct cfattach ne_isapnp_ca = {
	sizeof(struct ne_isapnp_softc), ne_isapnp_match, ne_isapnp_attach
};


/*
 * Names accepted by the match routine.
 */
static const struct ne_pnpid {
    const char *id_devlogic;
    const char *id_devcompat;
} if_ne_isapnp_pnpids[] = {
    { NULL, "PNP80D6" },		/* Digital DE305 ISAPnP */
    { NULL, NULL }
};

static int
ne_isapnp_match(
	struct device *parent,
#ifdef __BROKEN_INDIRECT_CONFIG
	void *match,
#else
	struct cfdata *match,
#endif
	void *aux)
{
	struct isapnp_attach_args *ipa = aux;
	const struct ne_pnpid *pnpid = if_ne_isapnp_pnpids;

	while (pnpid->id_devlogic != NULL || pnpid->id_devcompat != NULL) {
	    if (pnpid->id_devlogic != NULL
			&& !strcmp(ipa->ipa_devlogic, pnpid->id_devlogic))
		return(1);
	    if (pnpid->id_devcompat != NULL
			&& !strcmp(ipa->ipa_devcompat, pnpid->id_devcompat))
		return(1);
	    pnpid++;
	}

	return (0);
}

static void
ne_isapnp_attach(
	struct device *parent,
	struct device *self,
	void *aux)
{
	struct ne_isapnp_softc * const isc = (struct ne_isapnp_softc *)self;
	struct ne2000_softc * const nsc = &isc->sc_ne2000;
	struct dp8390_softc * const dsc = &nsc->sc_dp8390;
	struct isapnp_attach_args * const ipa = aux;
	bus_space_tag_t nict;
	bus_space_handle_t nich;
	bus_space_tag_t asict;
	bus_space_handle_t asich;
	const char *typestr;

	printf("\n");

	if (isapnp_config(ipa->ipa_iot, ipa->ipa_memt, ipa)) {
		printf("%s: can't configure isapnp resources\n",
		    dsc->sc_dev.dv_xname);
		return;
	}

	nict = ipa->ipa_iot;
	nich = ipa->ipa_io[0].h;

	asict = nict;

	if (bus_space_subregion(nict, nich, NE2000_ASIC_OFFSET,
	    NE2000_ASIC_NPORTS, &asich)) {
		printf("%s: can't subregion i/o space\n", dsc->sc_dev.dv_xname);
		return;
	}

	dsc->sc_regt = nict;
	dsc->sc_regh = nich;

	nsc->sc_asict = asict;
	nsc->sc_asich = asich;

	/*
	 * Detect it again, so we can print some information about the
	 * interface.
	 */
	switch (ne2000_detect(nict, nich, asict, asich)) {
	case NE2000_TYPE_NE1000:
		typestr = "NE1000";
		break;

	case NE2000_TYPE_NE2000:
		typestr = "NE2000";
		break;

	default:
		printf("%s: where did the card go?!\n", dsc->sc_dev.dv_xname);
		return;
	}

	printf("%s: %s Ethernet\n", dsc->sc_dev.dv_xname, typestr);

	/* This interface is always enabled. */
	dsc->sc_enabled = 1;

	/*
	 * Do generic NE2000 attach.  This will read the station address
	 * from the EEPROM.
	 */
	ne2000_attach(nsc, NULL);

	/* Establish the interrupt handler. */
	isc->sc_ih = isa_intr_establish(ipa->ipa_ic, ipa->ipa_irq[0].num,
	    ipa->ipa_irq[0].type, IPL_NET, dp8390_intr, dsc);
	if (isc->sc_ih == NULL)
		printf("%s: couldn't establish interrupt handler\n",
		    dsc->sc_dev.dv_xname);
}
