import matplotlib.pyplot as plt


categories = ['Total Time', 'Insert', 'Remove', 'Traverse', 'Search']
ours_data = [0.000471, 0.000002, 0.000031, 0.000227, 0.000017]
base_data = [0.002516, 0.000067, 0.000096, 0.000062, 0.000019]


bar_width = 0.35
bar_positions_base = range(len(categories))
bar_positions_ours = [pos + bar_width for pos in bar_positions_base]

plt.bar(bar_positions_base, base_data, width=bar_width, label='Baseline')
plt.bar(bar_positions_ours, ours_data, width=bar_width, label='Ours')


plt.xlabel('Operations')
plt.ylabel('Time (seconds)')
plt.title('Comparison of Execution Time')
plt.xticks([pos + bar_width/2 for pos in bar_positions_base], categories)
plt.legend()
plt.show()
