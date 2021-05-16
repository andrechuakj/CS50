#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string text;
    int stringlen;
    float letters = 0.0, words = 1.0, sntc = 0.0;
    float grade, L, S;
    
    text = get_string("Text: ");
    stringlen = strlen(text);
    
    for (int i = 0; i < stringlen; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
        if (isblank(text[i]))
        {
            words += 1;
        }
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sntc += 1;
        }
    }
    
    L = (letters / words) * 100;
    S = (sntc / words) * 100;
    grade = round(0.0588 * L - 0.296 * S - 15.8);
    
    if (grade < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    if (grade >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %.0f\n", grade);
    return 0;
}