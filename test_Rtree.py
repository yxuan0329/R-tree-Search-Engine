import rtree as rtreelib
import pytest
import math

import _myRtree

def test_init():
    Rtree = rtreelib.Rtree()
    Rtree.insert(0, (0, 0, 0, 0))
    Rtree.insert(1, (1, 1, 1, 1))
    assert Rtree.count((0, 0, 1, 1)) == 2

    myRtree = _myRtree.Rtree()
    p1 = _myRtree.Point(0, 0)
    p2 = _myRtree.Point(1, 1)
    r1 = _myRtree.Rect(p1, p2, 1)
    myRtree.insert(r1)
    assert myRtree.getSize() == 1
    
    