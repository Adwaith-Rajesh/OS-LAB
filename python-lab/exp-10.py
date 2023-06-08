from math import sqrt


mean_1 = 20
mean_2 = 22
N = 16
SD = 3
std_error = SD / sqrt(N)
t = abs(mean_1-mean_2) / std_error

print('t-static: ' + str(t))
table_value = 1.753

if t > table_value:
    print('H0 accepted')
else:
    print('H0 rejected')

# output
# t-static: 2.6666666666666665
# H0 accepted
