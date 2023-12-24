import rtree as rtreelib
import pytest
import math
import random
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import time

import _Rtree

def create_a_rect(Rtree, x, y, w, h, id):
    start_insert_time = time.perf_counter()
    p1 = _Rtree.Point(x, y)
    p2 = _Rtree.Point(x + w, y + h)
    r = _Rtree.Rect(p1, p2, id)
    
    Rtree.insert(r)
    end_insert_time = time.perf_counter()
    insert_duration = end_insert_time - start_insert_time

    # draw the rectangle on the figure
    # rect = patches.Rectangle((x, y), w, h, linewidth=1, edgecolor='r', facecolor='none')
    # ax.add_patch(rect)
    # ax.text(x, y, f'{text}', fontsize=8, ha='right')

    return insert_duration

# main function
def main():
    # fig, ax = plt.subplots()
    Rtree = _Rtree.Rtree()

    durations = []

    durations.append(create_a_rect(Rtree, 0, 0, 2, 2, 1))
    durations.append(create_a_rect(Rtree, 3, 3, 1, 1, 2))
    durations.append(create_a_rect(Rtree, 0, 0, 1, 1, 3))
    durations.append(create_a_rect(Rtree, 5, 5, 1, 1, 4))
    durations.append(create_a_rect(Rtree, 7, 7, 1, 1, 5))
    durations.append(create_a_rect(Rtree, 9, 9, 1, 1, 6))
    durations.append(create_a_rect(Rtree, 3, 1, 1, 1, 7))
    durations.append(create_a_rect(Rtree, 4, 7, 1, 1, 8))
    durations.append(create_a_rect(Rtree, 6, 3, 1, 3, 9))
    durations.append(create_a_rect(Rtree, 8, 2, 1, 4, 10))

    # remove a rect
    start_remove_time = time.perf_counter()
    p1 = _Rtree.Point(0, 0)
    p2 = _Rtree.Point(1, 1)
    r = _Rtree.Rect(p1, p2, 3)
    Rtree.remove(Rtree.getRoot(), r)
    end_remove_time = time.perf_counter()
    remove_duration = end_remove_time - start_remove_time
    durations.append(remove_duration)

    # # draw the figure
    # ax.set_xlabel('X-axis')
    # ax.set_ylabel('Y-axis')
    # ax.set_title('R tree visualization')

    # ax.legend()
    # plt.savefig('output.jpg')
    # plt.show()

    return durations

if __name__ == "__main__":
    start_time = time.perf_counter()
    durations = main()
    end_time = time.perf_counter()
    total_duration = end_time - start_time
    print(f"Total time taken: {total_duration:.6f} seconds")

    for i, duration in enumerate(durations, start=1):
        print(f"Operation {i} duration: {duration:.6f} seconds")
