import rtree as rtreelib
import pytest
import math
import random

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
    assert Rtree.getHeight(Rtree.getRoot()) < 4

    # random generate points and insert them into the tree
    random.seed(10)
    for i in range(4):
        x1 = random.randint(0, 20)
        y1 = random.randint(0, 20)
        p1 = _Rtree.Point(x1, y1)

        x2 = random.randint(0, 20)
        y2 = random.randint(0, 20)
        p2 = _Rtree.Point(x2, y2)

        r = _Rtree.Rect(p1, p2, i)
        Rtree.insert(r)
    assert Rtree.getSize() == 8
    assert Rtree.getHeight(Rtree.getRoot()) <= 3

    Rtree.remove(Rtree.getRoot(), r2)
    assert Rtree.getSize() == 7
    assert Rtree.getHeight(Rtree.getRoot()) <= 3