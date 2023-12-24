import rtree as rtreelib
import pytest
import math
import random
import matplotlib.pyplot as plt
import matplotlib.patches as patches

import _Rtree

def create_a_rect(Rtree, ax, x, y, w, h, id, text):
    p1 = _Rtree.Point(x, y)
    p2 = _Rtree.Point(x + w, y + h)
    r = _Rtree.Rect(p1, p2, id)
    Rtree.insert(r)

    # draw the rectangle on the figure
    rect = patches.Rectangle((x, y), w, h, linewidth=1, edgecolor='r', facecolor='none')
    ax.add_patch(rect)
    ax.text(x, y, f'{text}', fontsize=8, ha='right')

# main function
def main():
    fig, ax = plt.subplots()
    Rtree = _Rtree.Rtree()
    create_a_rect(Rtree, ax, 0, 0, 2, 2, 1, 'Rect 1')
    create_a_rect(Rtree, ax, 3, 3, 1, 1, 2, 'Rect 2')
    create_a_rect(Rtree, ax, 0, 0, 1, 1, 3, 'Rect 3')
    create_a_rect(Rtree, ax, 5, 5, 1, 1, 4, 'Rect 4')
    create_a_rect(Rtree, ax, 7, 7, 1, 1, 5, 'Rect 5')
    create_a_rect(Rtree, ax, 9, 9, 1, 1, 6, 'Rect 6')
    create_a_rect(Rtree, ax, 3, 1, 1, 1, 7, 'Rect 7')
    create_a_rect(Rtree, ax, 4, 7, 1, 1, 8, 'Rect 8')
    create_a_rect(Rtree, ax, 6, 3, 1, 3, 9, 'Rect 9')
    create_a_rect(Rtree, ax, 8, 2, 1, 4, 10, 'Rect 10')

    # remove a rect
    p1 = _Rtree.Point(0, 0)
    p2 = _Rtree.Point(1, 1)
    r = _Rtree.Rect(p1, p2, 3)
    Rtree.remove(Rtree.getRoot(), r)

    # draw the figure
    ax.set_xlabel('X-axis')
    ax.set_ylabel('Y-axis')
    ax.set_title('R tree visualization')

    ax.legend()
    plt.savefig('output.jpg')
    plt.show()

if __name__ == "__main__":
    main()