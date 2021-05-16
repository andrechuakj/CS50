#include <stdio.h>
#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int greyavg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            greyavg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = greyavg;
            image[i][j].rgbtGreen = greyavg;
            image[i][j].rgbtBlue = greyavg;

        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }        
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp.rgbtRed = image[i][j].rgbtRed;
            temp.rgbtGreen = image[i][j].rgbtGreen;
            temp.rgbtBlue = image[i][j].rgbtBlue;
            
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            
            image[i][width - 1 - j].rgbtRed = temp.rgbtRed;
            image[i][width - 1 - j].rgbtGreen = temp.rgbtGreen;
            image[i][width - 1 - j].rgbtBlue = temp.rgbtBlue;
            
        }
    }

    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    RGBTRIPLE average;
    char *red = "rgbtRed";
    char *green = "rgbtGreen";
    char *blue = "rgbtBlue";
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;

        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {        
                
            float totalR = 0;
            float counterR = 1.0;
            if (j - 1 >= 0)
            {
                totalR += temp[i][j - 1].rgbtRed;
                counterR++;
            }
            if (j + 1 < width)
            {
                totalR += temp[i][j + 1].rgbtRed;
                counterR++;
            }
            if (i - 1 >= 0)
            {
                totalR += temp[i - 1][j].rgbtRed;
                counterR++;
            }
            if (i + 1 < height)
            {
                totalR += temp[i + 1][j].rgbtRed;
                counterR++;
            }
            if (i + 1 < height && j + 1 < width)
            {
                totalR += temp[i + 1][j + 1].rgbtRed;
                counterR++;
            } 
            if (i + 1 < height && j - 1 >= 0)
            {
                totalR += temp[i + 1][j - 1].rgbtRed;
                counterR++;
            } 
            if (i - 1 >= 0 && j + 1 < width)
            {
                totalR += temp[i - 1][j + 1].rgbtRed;
                counterR++;
            } 
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                totalR += temp[i - 1][j - 1].rgbtRed;
                counterR++;
            } 
            
            totalR += temp[i][j].rgbtRed;
            
    
            float totalG = 0;
            float counterG = 1.0;
            if (j - 1 >= 0)
            {
                totalG += temp[i][j - 1].rgbtGreen;
                counterG++;
            }
            if (j + 1 < width)
            {
                totalG += temp[i][j + 1].rgbtGreen;
                counterG++;
            }
            if (i - 1 >= 0)
            {
                totalG += temp[i - 1][j].rgbtGreen;
                counterG++;
            }
            if (i + 1 < height)
            {
                totalG += temp[i + 1][j].rgbtGreen;
                counterG++;
            }
            if (i + 1 < height && j + 1 < width)
            {
                totalG += temp[i + 1][j + 1].rgbtGreen;
                counterG++;
            } 
            if (i + 1 < height && j - 1 >= 0)
            {
                totalG += temp[i + 1][j - 1].rgbtGreen;
                counterG++;
            } 
            if (i - 1 >= 0 && j + 1 < width)
            {
                totalG += temp[i - 1][j + 1].rgbtGreen;
                counterG++;
            } 
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                totalG += temp[i - 1][j - 1].rgbtGreen;
                counterG++;
            } 
            
            totalG += temp[i][j].rgbtGreen;
            
            
            float totalB = 0;
            float counterB = 1.0;
            if (j - 1 >= 0)
            {
                totalB += temp[i][j - 1].rgbtBlue;
                counterB++;
            }
            if (j + 1 < width)
            {
                totalB += temp[i][j + 1].rgbtBlue;
                counterB++;
            }
            if (i - 1 >= 0)
            {
                totalB += temp[i - 1][j].rgbtBlue;
                counterB++;
            }
            if (i + 1 < height)
            {
                totalB += temp[i + 1][j].rgbtBlue;
                counterB++;
            }
            if (i + 1 < height && j + 1 < width)
            {
                totalB += temp[i + 1][j + 1].rgbtBlue;
                counterB++;
            } 
            if (i + 1 < height && j - 1 >= 0)
            {
                totalB += temp[i + 1][j - 1].rgbtBlue;
                counterB++;
            } 
            if (i - 1 >= 0 && j + 1 < width)
            {
                totalB += temp[i - 1][j + 1].rgbtBlue;
                counterB++;
            } 
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                totalB += temp[i - 1][j - 1].rgbtBlue;
                counterB++;
            } 
            
            totalB += temp[i][j].rgbtBlue;

            
            image[i][j].rgbtRed = round(totalR / counterR);
            image[i][j].rgbtGreen = round(totalG / counterG);
            image[i][j].rgbtBlue = round(totalB / counterB);
             
        }
    }
    return;
}


    
    
    




//average.rgbtRed = image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed; 
//average.rgbtGreen = image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;
//average.rgbtBlue = image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;
                