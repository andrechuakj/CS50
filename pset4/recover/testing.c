#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    FILE *infile = fopen(argv[1], "r");
    char *file = argv[1];
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }
    if (infile == NULL)
    {
        printf("Unable to open %s.\n", file);
        fclose(infile);
        return 2;
    }


    int numblocks = 0;
    BYTE *bf = malloc(sizeof(BYTE));
    int counter = 0;
    fseek(infile, 0, SEEK_END);
    numblocks = ftell(infile);
    fseek(infile, 0, SEEK_SET);

    for (int i = 0; i < numblocks; i++)
    {
        fread(&bf, sizeof(BYTE), 1, infile);
        if (*bf == 0xff)
        {

            counter += 1;
            printf("%i\n", counter);
        }
    }
    return 0;
}