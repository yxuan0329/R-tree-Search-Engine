import random

def generate_random_data(num_points):
    data = []
    for _ in range(num_points):
        longitude = round(random.uniform(0, 1000000000), 5)
        latitude = round(random.uniform(0, 1000000000), 5)
        altitude = round(random.uniform(0, 1000000000), 5)
        data.append((longitude, latitude, altitude))
    return data

num_points = 600
random_data = generate_random_data(num_points)

with open('small_random_data.txt', 'w') as file:
    for i, point in enumerate(random_data):
        file.write(f"{point[0]}, {point[1]}, {point[2]}\n")

print(f"write file finished, {num_points}")
