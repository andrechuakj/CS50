#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
//this is a looooooooooooooooooong comment about how the code works
{
    float change;
    int counter = 0;
    do
    {
        change = get_float("Change owned: ");
    }
    while (change <= 0);
    
    int c = round(change * 100);
    
    while (c >= 25)
        //and this is another one for style points
    {
        c -= 25 ;
        counter ++;
    }
    while (c >= 10)
    {
        c -= 10 ;
        counter ++;
    }
    while (c >= 5)
    {
        c -= 5 ;
        counter ++;
    }
    //many many many comments alr
    
    while (c >= 1)
    {
        c -= 1 ;
        counter ++;
    }
    printf("%i\n", counter);
}
// this is alot of comments alr forsuch a simple code