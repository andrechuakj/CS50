# program to determine whether credit card number is valid
# 3 requirements:
# correct number of digits
# correct starting numbers
# passes Luhn's algorithm
from cs50 import get_int

n = -1
while n < 0:
    n = get_int("Number: ")
    
sum1a = 0
sum1b = 0
sum2 = 0
c = 10
m = n
m15 = (m - (m % 10000000000000))/10000000000000
m13 = (m - (m % 1000000000000))/1000000000000
m16 = (m - (m % 100000000000000))/100000000000000
m16v = (m - (m % 1000000000000000))/1000000000000000
while n > 0:
    sum2 += (n % c)/(c/10) 
    n -= n % c 
    if n > 0:
        sum1a += 2 * ((n % (c * 10))/c) 
        sum1b += sum1a % 10 + (sum1a - sum1a % 10)/10 
        n -= (n % (c * 10)) 
        c *= 100 
        sum1a = 0 
    
i = sum1b + sum2 

if i % 10 == 0:
    if m15 == 34 or m15 == 37:
        print("AMEX") 
    elif (m16 == 51 or m16 == 52 or m16 == 53 or m16 == 54 or m16 == 55):
        print("MASTERCARD")
    elif (m13 == 4 or m16v == 4):
        print("VISA") 
    else:
        print("INVALID") 
else:
    print("INVALID") 