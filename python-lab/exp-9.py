
# a.
from scipy.stats import poisson
from scipy.stats import binom


print('Exactly 4 success')
print(binom.pmf(4, 6, 0.25))

print('Exactly 1 success')
y = 1 - binom.pmf(0, 6, 0.25)
print(y)

# output
# Exactly 4 success
# 0.03295898437499997
# Exactly 1 success
# 0.822021484375

# b.


print(poisson.pmf(k=6, mu=3.4))

# output
# 0.07160440945982202
