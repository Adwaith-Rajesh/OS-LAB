import numpy as np
from scipy.stats import chi2_contingency

observed_data = np.array([
    [60, 54, 46, 41,],
    [40, 44, 53, 57,],
])

chi2, p_value, dof, expected_data = chi2_contingency(observed_data)

print('Observed frequencies')
print(observed_data)

print('Expected frequencies')
print(expected_data)

print('Chi-square statistic: ', chi2)
print('P-value: ', p_value)
print('Degrees Of Freedom: ', dof)

alpha = 0.5
if p_value < alpha:
    print('There is a significant association between gender and education level')
else:
    print('There is no significant association between gender and education level')

# output
# Observed frequencies
# [[60 54 46 41]
#  [40 44 53 57]]

# Expected frequencies
# [[50.88607595 49.86835443 50.37721519 49.86835443]
#  [49.11392405 48.13164557 48.62278481 48.13164557]]

# Chi-square statistic:  8.006066246262538
# P-value:  0.045886500891747214
# Degrees Of Freedom:  3
# There is a significant association between gender and education level
