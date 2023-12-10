import rtree as rtreelib
import pytest
import math

import _Rtree

def test_init():
    Rtree = rtreelib.Rtree()
    Rtree.insert(0, (0, 0, 0, 0))
    Rtree.insert(1, (1, 1, 1, 1))
    assert Rtree.count((0, 0, 1, 1)) == 2

    Rtree = _Rtree.Rtree()
    p1 = _Rtree.Point(0, 0)
    p2 = _Rtree.Point(1, 1)
    r1 = _Rtree.Rect(p1, p2, 1)
    Rtree.insert(r1)
    assert Rtree.getSize() == 2

def test_split():
    Rtree = _Rtree.Rtree()
    p1 = _Rtree.Point(0, 0)
    p2 = _Rtree.Point(2, 2)
    r1 = _Rtree.Rect(p1, p2, 1)
    Rtree.insert(r1)
    assert Rtree.getSize() == 2
    print(Rtree.getRoot()) # this will cause segmentation fault

    # add another rect and check the tree size is three
    p3 = _Rtree.Point(3, 3)
    p4 = _Rtree.Point(4, 4)
    r2 = _Rtree.Rect(p3, p4, 2)
    Rtree.insert(r2)
    assert Rtree.getSize() == 3

    # add another rect and check the tree size is four
    p5 = _Rtree.Point(1, 1)
    r3 = _Rtree.Rect(p1, p5, 3) # this should be inside r1
    Rtree.insert(r3)
    assert Rtree.getSize() == 4



    
    