import numpy as np
import scipy.stats as stats
from scipy.stats import ttest_ind

# Data for two teaching methods
teaching_method1 = np.array([82, 78, 86, 90, 87, 91, 79, 85, 88, 80])
teaching_method2 = np.array([77, 81, 79, 83, 75, 82, 80, 84, 78, 85, 81, 87])
alpha = 0.05

# Calculate means and standard deviations
# mean_1 = sum(teaching_method1) / len(teaching_method1)
mean_1 = np.mean(teaching_method1)
# mean_2 = sum(teaching_method2) / len(teaching_method2)
mean_2 = np.mean(teaching_method2)
std_1 = stats.tstd(teaching_method1)
std_2 = stats.tstd(teaching_method2)


# We use the "ttest_ind function" from the "scipy.stats" library to perform the t-test for the difference of means with unequal variances.
# Note: If the variances were assumed to be equal, we would use equal_var=True.
t_statistic, p_value = ttest_ind(teaching_method1, teaching_method2, equal_var=False)

# Print results
print("Teaching Method 1 Mean:", mean_1)
print("Teaching Method 2 Mean:", mean_2)
print("Teaching Method 1 S.D:", std_1)
print("Teaching Method 2 S.D:", std_2)
print("t-Statistic:", t_statistic)
print("significant level alpha=", alpha)
print("p-Value:", p_value)

# Interpret results

if p_value < alpha:
    print("There is a significant difference in mean scores between the two teaching methods.")
else:
    print("There is not enough evidence to suggest a significant difference in mean scores between the two teaching methods.")
