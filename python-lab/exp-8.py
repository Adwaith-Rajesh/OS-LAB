import math

# Given data
data = {'0-10': 5, '10-20': 10, '20-30': 20, '30-40': 40,
        '40-50': 30, '50-60': 20, '60-70': 10, '70-80': 5}

# Calculate the midpoints and frequencies of the class intervals
midpoints = [sum(map(int, i.split('-'))) / 2 for i in data.keys()]
frequencies = [i for i in data.values()]

print('Midpoints(x) =', midpoints)
print('Frequency(f) =', frequencies)
# Calculate the total frequency
total_frequency = sum(frequencies)
print('Total frequency =', total_frequency)

# mean
ms = sum([i * j for i, j in zip(midpoints, frequencies)])
mean = ms / sum(frequencies)

# variance
vs = sum([(i ** 2) * j for i, j in zip(midpoints, frequencies)])
variance = vs / total_frequency - mean ** 2

sd = math.sqrt(variance)
cv = (sd / mean) * 100

print('Mean:', mean)
print('Variance:', variance)
print('Standard Deviation : ', sd)
print('Coefficient of Variation : ', cv)


# output
# Midpoints(x) = [5.0, 15.0, 25.0, 35.0, 45.0, 55.0, 65.0, 75.0]
# Frequency(f) = [5, 10, 20, 40, 30, 20, 10, 5]
# Total frequency = 140
# Mean: 39.642857142857146
# Variance: 253.44387755102025
# Standard Deviation :  15.919920777159046
# Coefficient of Variation :  40.15835871715795
