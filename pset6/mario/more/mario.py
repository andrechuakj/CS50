# printing a mario pyramid
from cs50 import get_int

# my main function


def main():
    num = 0
    # only accept int between 1 to 8 inclusively
    while num < 1 or num > 8:
        num = get_int("What height shoud the pyramid be? ")
    number = num
    printing(num, number)

# defining a printing function to use recursion


def printing(number, num):
    # base line
    if number == 0:
        return
    # function calling itself
    printing(number - 1, num)
    # prints a single row
    print(" " * (num - number) + "#" * number + "  " + "#" * number)
        
        
if __name__ == "__main__":
    main()