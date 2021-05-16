#include <stdio.h>
#include <math.h>

#include "helpers.h"

int max(int a);


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


    
    
    



// Convert image to edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double gxred = 0;
            double gxgreen = 0;
            double gxblue = 0;
            double gyred = 0;
            double gygreen = 0;
            double gyblue = 0;
            
            for (int k = -1; k < 2; k++)
            {
                if (i + k >= 0 && i + k < height)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        if (j + l >= 0 && j + l < width)
                        {
                            if (k == -1 && l == -1)
                            {
                                gxred += image[i + k][j + l].rgbtRed * -1;
                                gxgreen += image[i + k][j + l].rgbtGreen * -1;
                                gxblue += image[i + k][j + l].rgbtBlue * -1;
                                gyred += image[i + k][j + l].rgbtRed * -1;
                                gygreen += image[i + k][j + l].rgbtGreen * -1;
                                gyblue += image[i + k][j + l].rgbtBlue * -1;
                            }
                            if (k == -1 && l == 0)
                            {
                                gyred += image[i + k][j + l].rgbtRed * -2;
                                gygreen += image[i + k][j + l].rgbtGreen * -2;
                                gyblue += image[i + k][j + l].rgbtBlue * -2;
                            }
                            if (k == -1 && l == 1)
                            {
                                gxred += image[i + k][j + l].rgbtRed;
                                gxgreen += image[i + k][j + l].rgbtGreen;
                                gxblue += image[i + k][j + l].rgbtBlue;
                                gyred += image[i + k][j + l].rgbtRed * -1;
                                gygreen += image[i + k][j + l].rgbtGreen * -1;
                                gyblue += image[i + k][j + l].rgbtBlue * -1;
                            }
                            if (k == 0 && l == -1)
                            {
                                gxred += image[i + k][j + l].rgbtRed * -2;
                                gxgreen += image[i + k][j + l].rgbtGreen * -2;
                                gxblue += image[i + k][j + l].rgbtBlue * -2;
                            }
                            if (k == 0 && l == 1)
                            {
                                gxred += image[i + k][j + l].rgbtRed * 2;
                                gxgreen += image[i + k][j + l].rgbtGreen * 2;
                                gxblue += image[i + k][j + l].rgbtBlue * 2;
                            }
                            if (k == 1 && l == -1)
                            {
                                gxred += image[i + k][j + l].rgbtRed * -1;
                                gxgreen += image[i + k][j + l].rgbtGreen * -1;
                                gxblue += image[i + k][j + l].rgbtBlue * -1;
                                gyred += image[i + k][j + l].rgbtRed;
                                gygreen += image[i + k][j + l].rgbtGreen;
                                gyblue += image[i + k][j + l].rgbtBlue;
                            }
                            if (k == 1 && l == 0)
                            {
                                gyred += image[i + k][j + l].rgbtRed * 2;
                                gygreen += image[i + k][j + l].rgbtGreen * 2;
                                gyblue += image[i + k][j + l].rgbtBlue * 2;
                            }
                            if (k == 1 && l == 1)
                            {
                                gxred += image[i + k][j + l].rgbtRed;
                                gxgreen += image[i + k][j + l].rgbtGreen;
                                gxblue += image[i + k][j + l].rgbtBlue;
                                gyred += image[i + k][j + l].rgbtRed;
                                gygreen += image[i + k][j + l].rgbtGreen;
                                gyblue += image[i + k][j + l].rgbtBlue;
                            }
                        }
                    }
                }
            }
            double finalRed;
            double finalGreen;
            double finalBlue;
            
            finalRed = round(sqrt((gxred * gxred) + (gyred * gyred)));
            finalBlue = round(sqrt((gxblue * gxblue) + (gyblue * gyblue)));
            finalGreen = round(sqrt((gxgreen * gxgreen) + (gygreen * gygreen)));
            
            temp[i][j].rgbtRed = max(finalRed);
            temp[i][j].rgbtGreen = max(finalGreen);
            temp[i][j].rgbtBlue = max(finalBlue);
        }
    }
    
    
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

int max(int a)
{
    if (a > 255)
    {
        a = 255;
    }
    return a;
}
