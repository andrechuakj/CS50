#include <stdio.h>
#include <cs50.h>

//  this is the first comment
int main(void)
{
    int i;
    do
    {
        i = get_int("Height: ");
        //this is a comment
    }
    while (i < 1 || i > 8);
     
    for (int j = 0; j < i; j++)
    {
        for (int k = 0; k < i - j - 1  ; k++)
        {
            printf(" ");
            //this is another comment
        }
        for (int l = 0; l < j + 1; l++)
        {
            printf("#");
        }
        
        printf("  ");
        
        for (int m = 0; m < j + 1; m++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}
// this is the last and most final comment cuz idk what to type for style
    