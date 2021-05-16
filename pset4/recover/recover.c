#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;


bool starting(BYTE bf[], int *counter);

int main(int argc, char *argv[])
{
    FILE *infile = fopen(argv[1], "r");
    char *file = argv[1];
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file);

        return 2;
    }
    
    
  //  int numblocks = 0;
//    BLOCK *bf = malloc(sizeof(BLOCK));
    
    //fseek(infile, 0, SEEK_END);
   // numblocks = (ftell(infile) / 512) + 1;
    //fseek(infile, 0, SEEK_SET);
    
   // BLOCK blocks[numblocks];
    
   // for (int i = 0; i < numblocks; i++)
   // {
    //    fread(&blocks[i], sizeof(BLOCK), 1, infile);
   // }
    BYTE bf[512];
    int counter = -1;
    bool started = false;
    bool writing = false;
    char *filesname = malloc(8);
    FILE *outfile = NULL;

    while(fread(bf, 512, 1, infile))
    {
        started = starting(bf, &counter);
        
        
        if (started == true)
        {
            if (counter > 0)
            {
                fclose(outfile);
            }
            //make file name
            sprintf(filesname, "%03i.jpg", counter);
            
            //open file
            outfile = fopen(filesname, "w");
            
            //write to file
            fwrite(bf, 512, 1, outfile);
            
            writing = true;
        }
        if (started == false)
        {
            if (writing == true)
            {
                //continue writing to file
                fwrite(bf, 512, 1, outfile);
            }
        }
    }
    return 0;
    free(bf);
    free(filesname);
    fclose(outfile);
    fclose(infile);

}

bool starting(BYTE bf[], int *counter)
{
    if (bf[0] == 0xff && bf[1] == 0xd8 && bf[2] == 0xff && (bf[3] & 0xf0) == 0xe0)
    {
        *counter += 1;
        return true;
    }
    else
    {
        return false;
    }
}
//bool ending(BYTE bytes)
//{
//    if
//