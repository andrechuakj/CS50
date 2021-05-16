# printing a mario pyramid
from cs50 import get_int

num = 0
# only accept int between 1 to 8 inclusively
while num < 1 or num > 8:
    num = get_int("What height shoud the pyramid be? ")

# for loop to print out row by row
for i in range(num):
    print(" " * (num - i - 1) + "#" * (i + 1))