#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
//library for all the functions i need

void cipher(string a, int c);

int main(int argc, string argv[])//command line arg
{
    if (argc != 2)
        // to filter out all command line arg with non-single key
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    else
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key");
                return 1;
            }
        }
    }
    string s = get_string("plaintext: ");
    int c = atoi(argv[1]);
    cipher(s, c);
    return 0;
}

void cipher(string a, int c)
//function to cipher all the plaintext
{
    int n = strlen(a);
    printf("ciphertext: ");
    for (int i = 0; i < n; i++)
        //go thru each char one by one and cipher accordingly
    {
        if (!isalpha(a[i]))
        {
            printf("%c", a[i]);
        }
        else
        {
            if (isupper(a[i]))
            {
                printf("%c", 65 + (((a[i] - 65) + c) % 26));
            }
            else if (islower(a[i]))
            {
                printf("%c", 97 + (((a[i] - 97) + c) % 26));
            }
        }
        
    }
    printf("\n");// to make the extra line at then end of everthing
}
