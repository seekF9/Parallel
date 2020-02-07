#python mean, median, mode
#02/06/2020

# Numpy mean() finds the average speed
import numpy 

#the scipy mode() method helps tp find 
# the number that appears the most 
from scipy import stats

#finding mean from a list of variety of speed of
#different objects
speed = [1.33, 24, 12312, 343, 67,97,56,909]
x1 = numpy.mean(speed)

#finding median from a list of grades
grades = [77,98, 78, 87, 88, 92, 94, 102, 86]
x2 = numpy.median(grades)

#finding Mode from a list of Mass
mass = [99,86,87,88,111,86,103,87,94,78,77,85,86]
x3 = stats.mode(mass)

#prints the value of mean, median and mode
print(x1,"\n",x2)

