#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int red, green, blue;
    float average;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            red = image[h][w].rgbtRed;
            green = image[h][w].rgbtGreen;
            blue = image[h][w].rgbtBlue;
            average = (red + green + blue) / 3.00;
            image[h][w].rgbtRed = round(average);
            image[h][w].rgbtGreen = round(average);
            image[h][w].rgbtBlue = round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    int originalRed, originalGreen, originalBlue;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            originalRed = image[h][w].rgbtRed;
            originalGreen = image[h][w].rgbtGreen;
            originalBlue = image[h][w].rgbtBlue;
            sepiaRed = 0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue;
            sepiaGreen = 0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue;
            sepiaBlue = 0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue;
            if (round(sepiaRed) > 255)
            {
                sepiaRed = 255;
            }
            if (round(sepiaGreen) > 255)
            {
                sepiaGreen = 255;
            }
            if (round(sepiaBlue) > 255)
            {
                sepiaBlue = 255;
            }
            image[h][w].rgbtRed = round(sepiaRed);
            image[h][w].rgbtGreen = round(sepiaGreen);
            image[h][w].rgbtBlue = round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            tmp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    float cnt;
    int sumRed, sumGreen, sumBlue;
    const int INTENSITY = 1;// Change here to custom the blur intensity

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            sumRed = sumGreen = sumBlue = 0;
            cnt = 0.00;
            // Box Blur
            for (int y = -INTENSITY; y <= INTENSITY; y++)
            {
                for (int x = -INTENSITY; x <= INTENSITY; x++)
                {
                    if (h + y >= 0 && h + y < height && w + x >= 0 && w + x < width)
                    {
                        sumRed += tmp[h + y][w + x].rgbtRed;
                        sumGreen += tmp[h + y][w + x].rgbtGreen;
                        sumBlue += tmp[h + y][w + x].rgbtBlue;
                        cnt++;
                    }
                }
            }
            image[h][w].rgbtRed = round(sumRed / cnt);
            image[h][w].rgbtGreen = round(sumGreen / cnt);
            image[h][w].rgbtBlue = round(sumBlue / cnt);
        }
    }
    return;
}
