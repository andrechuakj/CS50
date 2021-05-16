#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int sum1a = 0, sum1b = 0, sum2 = 0;
    long c = 10;
    long n = get_long("Number: ");
    long m = n;
    int m15 = (m - (m % 10000000000000))/10000000000000;
    int m13 = (m - (m % 1000000000000))/1000000000000;
    int m16 = (m - (m % 100000000000000))/100000000000000;
    int m16v = (m - (m % 1000000000000000))/1000000000000000;
    while (n > 0)
    {
        sum2 += (n % c)/(c/10);
        n -= n % c;
        if (n > 0)
        {
            sum1a += 2 * (( n % (c * 10))/c);
            sum1b += sum1a % 10 + (sum1a - sum1a % 10)/10;
            n -= ( n % (c * 10));
            c *= 100;
            sum1a = 0;
        }
        
    }
    
    int i = sum1b + sum2;
    
    if (i % 10 == 0)
    {
        if (m15 == 34 || m15 == 37 )
        {
            printf("AMEX\n");
        }
        else if (m16 == 51 || m16 == 52 || m16 == 53 || m16 == 54 || m16 == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (m13 == 4 || m16v == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }    
    else
    {
        printf("INVALID\n");
    }    
}