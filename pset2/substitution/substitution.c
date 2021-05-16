#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
//library for all the functions i need
string const refer = ("abcdefghijklmnopqrstuvwxyz");
int counter = 0;
void cipher(string a, string c);

int main(int argc, string argv[])//command line arg
//string condiions:
//26 unique characters
//case insensitive
//single key
//only alphabets
{
    char keya[26];
    if (argc != 2 || strlen(argv[1]) != 26)
        // to filter out all command line arg with non-single key
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // check if all alphabet
    else if (argc == 2 && strlen(argv[1]) == 26)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    
    for (int l = 0; l < 26; l++)
    {
        keya[l] = tolower(argv[1][l]);
    }

    
    for (int j = 0; j < 26; j++)
    {
        for (int k = 0; k < 26; k++)
        {
            if (refer[j] == keya[k])
            {
                counter++;
                break;
            }
        }
    }
    printf("%i\n", counter);
    if (counter != 26)
    {
        printf("Please insert 26 unique alphabets.\n");
        return 1;
    }
    
    string pt = get_string("plaintext: ");
    
    cipher(pt, keya);
    return 0;
}

void cipher(string a, string c)
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
                printf("%c", toupper(c[(int) a[i] - 65]));
            }
            else if (islower(a[i]))
            {
                printf("%c", tolower(c[(int) a[i] - 97 ]));
            }
        }

    }
    printf("\n");// to make the extra line at then end of everthing
}

