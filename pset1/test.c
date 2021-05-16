#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

string print(int i)
{
    return ("hello world %s", (string) i);
}
int main(void)
{
    int i = get_int("?: ");
    if (i == 1)
    {
        printf("%s", print(i));
    }
}