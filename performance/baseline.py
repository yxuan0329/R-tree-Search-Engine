import math
import time

from rtree import index

def create_a_rect(line, Rtree):
    # Extracting coordinates and id from the line
    x1, y1, x2, y2, id = map(float, line.split(','))
    
    start_insert_time = time.perf_counter()
    p1 = index.Property()
    Rtree.insert(int(id), (x1, y1, x2, y2), obj=p1)
    end_insert_time = time.perf_counter()
    insert_duration = end_insert_time - start_insert_time
    return insert_duration

def remove_by_id_of_3(Rtree):
    start_remove_time = time.perf_counter()
    for id in range(3, 31, 3):
        Rtree.delete(id, (0, 0, 1, 1))
    end_remove_time = time.perf_counter()
    remove_duration = end_remove_time - start_remove_time
    return remove_duration

def traverse_rects(Rtree):
    start_traverse_time = time.perf_counter()
    for _ in Rtree.intersection((0, 0, 1, 1), objects=True):
        pass
    end_traverse_time = time.perf_counter()
    traverse_duration = end_traverse_time - start_traverse_time
    return traverse_duration

def search_by_id_of_4(Rtree):
    start_search_time = time.perf_counter()
    for _ in Rtree.intersection((0, 0, 1, 1), objects=True):
        pass
    end_search_time = time.perf_counter()
    search_duration = end_search_time - start_search_time
    return search_duration

# main function
def main():
    Rtree = index.Index()

    insert_durations = []
    remove_durations = []
    traverse_duration = 0
    search_durations = []

    with open('./R-tree-Search-Engine/datasets/testdata.txt', 'r') as file:
        for line in file:
            insert_durations.append(create_a_rect(line, Rtree))

    remove_durations.append(remove_by_id_of_3(Rtree))

    traverse_duration = traverse_rects(Rtree)

    search_durations.append(search_by_id_of_4(Rtree))

    return insert_durations, remove_durations, traverse_duration, search_durations

if __name__ == "__main__":
    start_time = time.perf_counter()
    insert_durations, remove_durations, traverse_duration, search_durations = main()
    end_time = time.perf_counter()
    total_duration = end_time - start_time
    print(f"Total time taken: {total_duration:.6f} seconds")

    avg_insert_duration = sum(insert_durations) / len(insert_durations)
    avg_remove_duration = sum(remove_durations) / len(remove_durations)
    avg_search_duration = sum(search_durations) / len(search_durations)

    print(f"Average Insert Duration: {avg_insert_duration:.6f} seconds")
    print(f"Average Remove Duration: {avg_remove_duration:.6f} seconds")
    print(f"Traverse Duration: {traverse_duration:.6f} seconds")
    print(f"Average Search Duration: {avg_search_duration:.6f} seconds")
