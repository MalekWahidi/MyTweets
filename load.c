#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\Users\Malek\Desktop\University\Prog\FinalC\headers\tweet.h"

int countTweets()
{
    FILE *fptr = fopen(CSV_FILE, "r");

    if (fptr == NULL)
    {
        printf("Error: Can't access %s.\n", CSV_FILE);
        exit(-1);
    }

    else
    {
        char *buffer = (char *)malloc(BUFFER_SIZE);

        int tweet_count = -1;

        while (fgets(buffer, BUFFER_SIZE, fptr))
            tweet_count++;

        fclose(fptr);

        return tweet_count;
    }
}

int loadDataset(tweet *dataset[])
{
    FILE *fptr = fopen(CSV_FILE, "r");

    if (fptr == NULL)
        exit(-1);

    else
    {
        printf("Loading dataset from '%s'...\n", CSV_FILE);

        char *buffer = (char *)malloc(BUFFER_SIZE);

        int row = 0, col = 0;
        char text[TWEET_SIZE], datetime[DATE_TIME_SIZE], date[DATE_SIZE], time[TIME_SIZE];
        int retweets, likes, id;

        // We use fgets to read lines from the csv file
        // (fgets uses '\n' as the delimiter instead of whitespace)
        while (fgets(buffer, BUFFER_SIZE, fptr))
        {
            col = 0;
            row++;

            // To avoid loading the column titles along with the data
            if (row == 1)
                continue;

            // Splitting the string array 'buffer'
            // Returns pointer to the first string until the ',' delimiter
            char *token;

            if (buffer[0] == '"')
                token = strtok(buffer, "\"");

            else
                token = strtok(buffer, ",");

            // while 'token' is not NULL
            while (token)
            {
                switch (col)
                {
                case 0:
                    strcpy(text, token);
                    break;
                case 1:
                    retweets = atoi(token);
                    break;
                case 2:
                    likes = atoi(token);
                    break;
                case 3:
                    strcpy(datetime, token);
                    break;
                }

                col++;

                // returns the pointer to the first element
                // of the next string after the delimiter ','
                token = strtok(NULL, ",");
            }

            strcpy(date, strtok(datetime, " "));
            strcpy(time, strtok(NULL, " "));

            // We replace the '\n' at the end of string 'time' with '\0'
            // (since the '\n' at the end of each 'time' usually creates problems later on in the code)
            time[strlen(time) - 1] = '\0';

            id = row - 2; // So that location of first element in array is 0 (we started reading from row 2)

            dataset[id] = newTweet(text, retweets, likes, date, time, id);
            // printTweet(dataset[id]);
        }

        fclose(fptr);

        printf("Dataset Loading Complete!\n\n");

        return 0;
    }
}

int readDictionary(char **wordlist, float polarities[DICT_SIZE])
{
    FILE *fptr = fopen(DICT, "r");

    if (fptr == NULL)
    {
        printf("Error: Can't access %s.\n", DICT);
        return -1;
    }

    else
    {
        char *buffer = (char *)malloc(DICT_BUFF_SIZE);

        float pol, norm_pol;

        int i = 0;

        while (fgets(buffer, DICT_BUFF_SIZE, fptr))
        {
            char *token;

            token = strtok(buffer, ",");

            // Allocate memory to the string wordlist[i] based on length of word
            wordlist[i] = malloc(strlen(token) + 1);
            strcpy(wordlist[i], token);

            token = strtok(NULL, ",");

            // Convert token string representing polarity score to a float number
            pol = atof(token);

            // Normalize values to range [-1, 1]
            // instead of the [-4, 4] range found in the dictionary
            norm_pol = 2 * ((pol - (-4)) / (4 - (-4))) - 1;
            polarities[i] = norm_pol;
            i++;
        }

        fclose(fptr);

        return 0;
    }
}