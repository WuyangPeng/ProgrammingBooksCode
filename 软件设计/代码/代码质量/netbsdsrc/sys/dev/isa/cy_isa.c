/*	$NetBSD: cy_isa.c,v 1.7 1997/10/20 18:43:08 thorpej Exp $	*/

/*
 * cy.c
 *
 * Driver for Cyclades Cyclom-8/16/32 multiport serial cards
 * (currently not tested with Cyclom-32 cards)
 *
 * Timo Rossi, 1996
 *
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/device.h>

#include <machine/bus.h>
#include <machine/intr.h>

#include <dev/isa/isavar.h>
#include <dev/isa/isareg.h>

#include <dev/ic/cd1400reg.h>
#include <dev/ic/cyreg.h>
#include <dev/ic/cyvar.h>

static int cy_probe_isa __P((struct device *, void *, void *));
static void cy_attach_isa   __P((struct device *, struct device *, void *));

struct cfattach cy_isa_ca = {
	sizeof(struct cy_softc), cy_probe_isa, cy_attach_isa
};

static int
cy_probe_isa(parent, match, aux)
	struct device  *parent;
	void *match, *aux;
{
	struct isa_attach_args *ia = aux;
	struct cy_softc sc;
	int found;

	memcpy(&sc.sc_dev, match, sizeof(struct device));

	sc.sc_memt = ia->ia_memt;
	sc.sc_bustype = CY_BUSTYPE_ISA;

	/* Disallow wildcarded i/o address. */
	if (ia->ia_iobase == ISACF_PORT_DEFAULT)
		return (0);

	if (ia->ia_irq == IRQUNK) {
		printf("%s: interrupt not defined\n", sc.sc_dev.dv_xname);
		return 0;
	}

	if (bus_space_map(ia->ia_memt, ia->ia_maddr, CY_MEMSIZE, 0,
	    &sc.sc_bsh) != 0)
		return 0;

	found = cy_find(&sc);

	bus_space_unmap(ia->ia_memt, sc.sc_bsh, CY_MEMSIZE);

	if (found) {
		ia->ia_iosize = 0;
		ia->ia_msize = CY_MEMSIZE;
	}

	return found;
}

static void
cy_attach_isa(parent, self, aux)
	struct device  *parent, *self;
	void *aux;
{
	struct cy_softc *sc = (void *) self;
	struct isa_attach_args *ia = aux;

	sc->sc_memt = ia->ia_memt;
	sc->sc_bustype = CY_BUSTYPE_ISA;

	if (bus_space_map(ia->ia_memt, ia->ia_maddr, CY_MEMSIZE, 0,
	    &sc->sc_bsh) != 0) {
		printf(": cannot map mem space\n");
		return;
	}

	if (cy_find(sc) == 0) {
		printf(": cy_find failed\n");
		return;
	}

	cy_attach(parent, self, aux);

	sc->sc_ih = isa_intr_establish(ia->ia_ic, ia->ia_irq,
	    IST_EDGE, IPL_TTY, cy_intr, sc);

	if (sc->sc_ih == NULL)
		printf("%s: couldn't establish interrupt", sc->sc_dev.dv_xname);
}
