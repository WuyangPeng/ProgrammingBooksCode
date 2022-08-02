#!/usr/bin/env python
# $Id: split.py,v 2.2 2004/07/17 11:09:18 zeller Exp $

def split(c, n):
    """Stub to overload in subclasses"""
    subsets = []
    start = 0
    for i in range(n):
        len_subset = int((len(c) - start) / float(n - i) + 0.5)
        subset = c[start:start + len_subset]
        subsets.append(subset)
        start = start + len(subset)

    assert len(subsets) == n
    for s in subsets:
        assert len(s) > 0

    return subsets
