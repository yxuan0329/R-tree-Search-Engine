import rtree as rtreelib
import pytest
import math
import random
import matplotlib.pyplot as plt
import matplotlib.patches as patches

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

def test_zero():
    """Test the empty tree case."""
    Rtree = _Rtree.Rtree()
    assert Rtree.getSize() == 1
    assert Rtree.getHeight(Rtree.getRoot()) == 0

def test_split_insert_delete():
    # Create a figure and axis
    fig, ax = plt.subplots()

    Rtree = _Rtree.Rtree()
    p1 = _Rtree.Point(0, 0)
    p2 = _Rtree.Point(2, 2)
    r1 = _Rtree.Rect(p1, p2, 1)
    Rtree.insert(r1)
    assert Rtree.getSize() == 2
    # draw the rectangle on the figure
    rect = patches.Rectangle((0, 0), 2, 2, linewidth=1, edgecolor='r', facecolor='none')
    ax.add_patch(rect)
    ax.text(0, 0, f'Rect 2', fontsize=8, ha='right')

    # add another rect and check the tree size is three
    p3 = _Rtree.Point(3, 3)
    p4 = _Rtree.Point(4, 4)
    r2 = _Rtree.Rect(p3, p4, 2)
    Rtree.insert(r2)
    assert Rtree.getSize() == 3
    # draw the rectangle on the figure
    rect = patches.Rectangle((3, 3), 1, 1, linewidth=1, edgecolor='r', facecolor='none')
    ax.add_patch(rect)
    ax.text(3, 3, f'Rect 2', fontsize=8, ha='right')

    # add another rect and check the tree size is four
    p5 = _Rtree.Point(1, 1)
    r3 = _Rtree.Rect(p1, p5, 3) # this should be inside r1
    Rtree.insert(r3)
    assert Rtree.getSize() == 4
    assert Rtree.getHeight(Rtree.getRoot()) < 4
    # draw the rectangle on the figure
    rect = patches.Rectangle((0, 0), 1, 1, linewidth=1, edgecolor='r', facecolor='none')
    ax.add_patch(rect)
    ax.text(0, 0, f'Rect 3', fontsize=8, ha='right')

    # random generate points and insert them into the tree
    random.seed(10)
    for i in range(4):
        x1 = i
        y1 = i+1
        p1 = _Rtree.Point(x1, y1)

        x2 = i+2
        y2 = i+2
        p2 = _Rtree.Point(x2, y2)

        r = _Rtree.Rect(p1, p2, i)
        Rtree.insert(r)
        
        # draw the rectangle on the figure
        rect = patches.Rectangle((x1, y1), x2-x1, y2-y1, linewidth=1, edgecolor='r', facecolor='none')
        ax.add_patch(rect)
        ax.text(x1, y1, f'Rect {i+4}', fontsize=8, ha='right')

                
    assert Rtree.getSize() == 8
    assert Rtree.getHeight(Rtree.getRoot()) < 3

    Rtree.remove(Rtree.getRoot(), r2)
    assert Rtree.getSize() == 7
    assert Rtree.getHeight(Rtree.getRoot()) < 3

    # Set labels and title
    ax.set_xlabel('X-axis')
    ax.set_ylabel('Y-axis')
    ax.set_title('R tree visualization')

    # Add legend
    ax.legend()
    plt.savefig('output.jpg')
    plt.show()

def test_traverse():
    """ Create a tree with 3 nodes and traverse the nodes"""
    # nodes: (0, 0, 1, 1), (2, 2, 3, 3), (4, 4, 5, 5)
    Rtree = _Rtree.Rtree()
    p1 = _Rtree.Point(0, 0)
    p2 = _Rtree.Point(1, 1)
    r1 = _Rtree.Rect(p1, p2, 1)
    Rtree.insert(r1)
    p3 = _Rtree.Point(2, 2)
    p4 = _Rtree.Point(3, 3)
    r3 = _Rtree.Rect(p3, p4, 3)
    Rtree.insert(r3)
    p5 = _Rtree.Point(4, 4)
    p6 = _Rtree.Point(5, 5)
    r2 = _Rtree.Rect(p5, p6, 2)
    Rtree.insert(r2)

    # search for the nodes
    list1 = []
    list1 = Rtree.traverse(Rtree.getRoot())
    assert len(list1) == 4
    assert list1[2] == 3