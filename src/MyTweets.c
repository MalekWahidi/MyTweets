#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\Users\Malek\Desktop\University\Prog\FinalC\headers\tweet.h"
#include "C:\Users\Malek\Desktop\University\Prog\FinalC\src\functions.c"

void printHelp()
{
    printf("\n\n"
           "--------------------------------------------------------------------------------------------------------------\n"
           "Usage: MyTweets.exe --option <argument>\n\n"
           "* Only 1 input argument is accepted after each option\n"
           "options:\n"
           "-s, --save              Tweets printed out by functions called after --save will be written to 'output.txt'\n"
           "                        (sentiment analysis and sorting functions do not support this feature yet)\n"
           "-h, --help              Print help text for program usage with arguments\n"
           "-a, --all               Print all Elon Musk tweets found in the dataset\n"
           "-id <id>                Print Elon Musk tweet that has the corresponding 'id' in the dataset\n"
           "                        (e.g: MyTweet.exe -id 1000)\n"
           "--min-likes             Find the least liked Elon Musk tweet\n"
           "--min-retweets          Find the least retweeted Elon Musk tweet\n"
           "--max-likes             Find the most liked Elon Musk tweet\n"
           "--max-retweets          Find the most retweeted Elon Musk tweet\n"
           "--avg-likes             Calculate the average likes for all Elon Musk tweets in the dataset\n"
           "--avg-retweets          Calculate the average retweets for all Elon Musk tweets in the dataset\n"
           "--max-month             Find the month with the most Elon Musk tweets posted\n"
           "--sort-likes            Sort the entire dataset by number of likes for each tweet from highest to lowest\n"
           "--sort-retweets         Sort the entire dataset by number of retweets for each tweet from highest to lowest\n"
           "-w, --search <keyword>  Find all tweets that contain the given 'keyword' (keyword should be a single word)\n"
           "                        (e.g: MyTweet.exe -s Journalism)\n"
           "-d, --date <date>       Find all tweets posted on the given day (date format should be MM/DD/YY)\n"
           "                        (e.g: MyTweet.exe -d 10/26/2022)\n"
           "-t, --time <time>       Find all tweets posted on the given 'time' (time format should be in 24h format HH:MM)\n"
           "                        (e.g: MyTweet.exe -t 21:51)\n"
           "-m, --month <month>     Find all tweets posted on the given 'month' (argument should be an int in the range 1-12)\n"
           "                        (e.g: MyTweet.exe -m 5)\n"
           "-n, --analyse <id>      Perform dictionary-based sentiment analysis on the Elon Musk tweet with the corresponding 'id',\n"
           "                        and return a polarity score in range [-1, 1] indicating postive or negative tweet sentiment\n"
           "                        (e.g: MyTweet.exe -n 1200)\n"
           "--------------------------------------------------------------------------------------------------------------\n\n");
}

// Check if the entire string is purely a number
// (no alphabet or symbol characters)
int isNumString(char *str)
{
    while (*str)
    {
        if (isdigit(*str++) == 0)
            return 0;
    }

    return 1;
}

int main(int argc, char **argv)
{
    const int NUM_TWEETS = countTweets();
    int ID, save = 0;

    // create an array of tweets
    tweet *dataset[NUM_TWEETS];

    loadDataset(dataset);

    for (int i = 1; i <= argc; i++)
    {
        if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h"))
            printHelp();

        if (!strcmp(argv[i], "--save") || !strcmp(argv[i], "-s"))
            save = 1;

        else if (!strcmp(argv[i], "--all") || !strcmp(argv[i], "-a"))
            printAllTweets(dataset, NUM_TWEETS, save);

        else if (!strcmp(argv[i], "-id"))
        {
            if (argc == i + 1)
                printf("Error: Input argument for <ID> not found.\n");

            else if (isNumString(argv[i + 1]))
            {
                ID = atoi(argv[i + 1]);

                if (ID < 0 || ID > NUM_TWEETS)
                {
                    printf("Error: Tweet ID out of range.\n");
                    printf("Number of tweets: %d\n", NUM_TWEETS);
                }
                else if (ID > 0 && ID <= NUM_TWEETS)
                    printTweet(dataset[ID], save);
                i++;
            }
            else
                printf("Error: Invalid Tweet ID.\n");
        }

        else if (!strcmp(argv[i], "--min-retweets"))
            getMin(dataset, NUM_TWEETS, 1, save);

        else if (!strcmp(argv[i], "--min-likes"))
            getMin(dataset, NUM_TWEETS, 2, save);

        else if (!strcmp(argv[i], "--max-retweets"))
            getMax(dataset, NUM_TWEETS, 1, save);

        else if (!strcmp(argv[i], "--max-likes"))
            getMax(dataset, NUM_TWEETS, 2, save);

        else if (!strcmp(argv[i], "--avg-retweets"))
            getAvg(dataset, NUM_TWEETS, 1, save);

        else if (!strcmp(argv[i], "--avg-likes"))
            getAvg(dataset, NUM_TWEETS, 2, save);

        else if (!strcmp(argv[i], "--max-month"))
            getMostActiveMonth(dataset, NUM_TWEETS);

        else if (!strcmp(argv[i], "--sort-likes"))
            sortByLikes(dataset, NUM_TWEETS);

        else if (!strcmp(argv[i], "--sort-retweets"))
            sortByRetweets(dataset, NUM_TWEETS);

        else if (!strcmp(argv[i], "--search") || !strcmp(argv[i], "-w"))
        {
            if (argc == i + 1)
                printf("Error: Input argument <keyword> not found.\n");

            else
            {
                searchKeyword(dataset, NUM_TWEETS, argv[i + 1], save);
                i++;
            }
        }

        else if (!strcmp(argv[i], "--date") || !strcmp(argv[i], "-d"))
        {
            if (argc == i + 1)
                printf("Error: Input argument <date> not found.\n");

            else
            {
                findTweetByDate(dataset, NUM_TWEETS, argv[i + 1], save);
                i++;
            }
        }

        else if (!strcmp(argv[i], "--time") || !strcmp(argv[i], "-t"))
        {

            if (argc == i + 1)
                printf("Error: Input argument <time> not found.\n");

            else
            {
                findTweetByTime(dataset, NUM_TWEETS, argv[i + 1], save);
                i++;
            }
        }

        else if (!strcmp(argv[i], "--month") || !strcmp(argv[i], "-m"))
        {
            if (argc == i + 1)
                printf("Error: Input argument <month> not found.\n");

            else if (isNumString(argv[i + 1]) && atoi(argv[i + 1]) > 0 && atoi(argv[i + 1]) <= 12)
            {
                int month = atoi(argv[i + 1]);
                findTweetByMonth(dataset, NUM_TWEETS, month, save);
                i++;
            }
            else
            {
                printf("Error: Invalid input argument <month>.\n ");
                printf("(argument should be an integer in range [1-12])\n ");
            }
        }

        else if (!strcmp(argv[i], "--analyse") || !strcmp(argv[i], "-n"))
        {
            if (argc == i + 1)
                printf("Error: Input argument <ID> not found.\n");

            else if (isNumString(argv[i + 1]))
            {
                ID = atoi(argv[i + 1]);

                if (ID < 0 || ID > NUM_TWEETS)
                {
                    printf("Error: Tweet ID out of range.\n");
                    printf("Number of tweets: %d\n", NUM_TWEETS);
                }
                else if (ID > 0 && ID <= NUM_TWEETS)
                    sentimentAnalysis(dataset[ID]);
                i++;
            }
            else
                printf("Error: Invalid Tweet ID.\n");
        }

        else
        {
            printf("Error: Invalid argument at position %d.\n", i);
            return -1;
        }
    }

    return 0;
}