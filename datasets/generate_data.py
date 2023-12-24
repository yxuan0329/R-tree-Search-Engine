import random

def generate_random_data(num_points):
    data = []
    random.seed(10)
    for i in range(num_points):
        longitude = round(random.uniform(0, 100), 0)
        latitude = round(random.uniform(0, 100), 0)
        longitude_2 = round(random.uniform(0, 100), 0)
        latitude_2 = round(random.uniform(0, 100), 0)
        if longitude > longitude_2:
            longitude, longitude_2 = longitude_2, longitude
        if latitude > latitude_2:
            latitude, latitude_2 = latitude_2, latitude
        data.append((longitude, latitude, longitude_2, latitude_2, i+1))
    return data

num_points = 30
random_data = generate_random_data(num_points)

with open('testdata.txt', 'w') as file:
    for i, point in enumerate(random_data):
        file.write(f"{point[0]}, {point[1]}, {point[2]}, {point[3]}, {i}\n")

print(f"write file finished, {num_points}")
