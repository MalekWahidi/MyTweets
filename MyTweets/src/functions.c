#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "C:\Users\Malek\Desktop\University\Prog\FinalC\headers\tweet.h"
#include "C:\Users\Malek\Desktop\University\Prog\FinalC\src\load.c"

#define dataset_loop() \
    for (i = 0; i < NUM_TWEETS; i++)

tweet *newTweet(char *text, int retweets, int likes, char *date, char *time, int id)
{
    // allocate location in memory for the matrix
    tweet *twt = (tweet *)malloc(sizeof(tweet));

    strcpy(twt->text, text);
    twt->retweets = retweets;
    twt->likes = likes;
    strcpy(twt->date, date);
    strcpy(twt->time, time);
    twt->id = id;

    return twt;
}

int printTweet(tweet *twt, int save)
{
    printf("ID: %d\n", twt->id);
    printf("Text: %s\n", twt->text);
    printf("Retweets: %d\n", twt->retweets);
    printf("Likes: %d\n", twt->likes);
    printf("Date: %s\n", twt->date);
    printf("Time: %s\n", twt->time);
    printf("\n");

    if (save == 1)
    {
        FILE *fptr = fopen(OUTPUT, "a");

        if (fptr == NULL)
        {
            printf("Error: Can't access %s.\n", CSV_FILE);
            return -1;
        }

        fprintf(fptr, "ID: %d\n", twt->id);
        fprintf(fptr, "Text: %s\n", twt->text);
        fprintf(fptr, "Retweets: %d\n", twt->retweets);
        fprintf(fptr, "Likes: %d\n", twt->likes);
        fprintf(fptr, "Date: %s\n", twt->date);
        fprintf(fptr, "Time: %s\n", twt->time);
        fprintf(fptr, "\n");

        fclose(fptr);
    }

    return 0;
}

void printAllTweets(tweet *dataset[], const int NUM_TWEETS, int save)
{
    for (int i = 0; i < NUM_TWEETS; i++)
    {
        printTweet(dataset[i], save);
    }
}

int getMax(tweet *dataset[], const int NUM_TWEETS, int option, int save)
{
    int max_value, max_id;

    if (option == 1)
    {
        for (int i = 0; i < NUM_TWEETS; i++)
        {
            if (dataset[i]->retweets > max_value)
            {
                max_id = dataset[i]->id;
                max_value = dataset[i]->retweets;
            }
        }

        printf("Most retweeted tweet found!\n");
    }

    else if (option == 2)
    {
        for (int i = 0; i < NUM_TWEETS; i++)
        {
            if (dataset[i]->likes > max_value)
            {
                max_id = dataset[i]->id;
                max_value = dataset[i]->likes;
            }
        }

        printf("Most liked tweet found!\n");
    }

    else
        return -1;

    printTweet(dataset[max_id], save);

    return 0;
}

int getMin(tweet *dataset[], const int NUM_TWEETS, int option, int save)
{
    int min_value = dataset[0]->likes, min_id;

    if (option == 1)
    {
        for (int i = 0; i < NUM_TWEETS; i++)
        {
            if (dataset[i]->retweets < min_value)
            {
                min_id = dataset[i]->id;
                min_value = dataset[i]->retweets;
            }
        }

        printf("Least retweeted tweet found!\n");
    }

    else if (option == 2)
    {
        for (int i = 0; i < NUM_TWEETS; i++)
        {
            if (dataset[i]->likes < min_value)
            {
                min_id = dataset[i]->id;
                min_value = dataset[i]->likes;
            }
        }

        printf("Least liked tweet found!\n");
    }

    else
        return -1;

    printTweet(dataset[min_id], save);

    return 0;
}

int getAvg(tweet *dataset[], const int NUM_TWEETS, int option, int save)
{
    if (option == 1)
    {
        int avg_retweets;

        for (int i = 0; i < NUM_TWEETS; i++)
        {
            avg_retweets += dataset[i]->retweets;
        }

        avg_retweets = avg_retweets / NUM_TWEETS;

        printf("Average retweets: %d\n\n", avg_retweets);
    }

    else if (option == 2)
    {
        int avg_likes;

        for (int i = 0; i < NUM_TWEETS; i++)
        {
            avg_likes += dataset[i]->likes;
        }

        avg_likes = avg_likes / NUM_TWEETS;

        printf("Average likes: %d\n\n", avg_likes);
    }

    else
        return -1;

    return 0;
}

int searchKeyword(tweet *dataset[], const int NUM_TWEETS, char keyword[20], int save)
{
    int flag = 0;
    char *sentence, *word;

    printf("Keyword: %s", keyword);
    printf("\n");

    for (int i = 0; i < NUM_TWEETS; i++)
    {
        // Copying text from the dataset to a new string "sentence"
        // to avoid the strtok() function modifying the original text
        // located in the dataset array
        strcpy(sentence, dataset[i]->text);

        // The delimiter " ,.-" indicates that we should
        // only consider SPACE characters as delimiters
        // and not similar whitespace characters such as '\n', '\t', etc.
        word = strtok(sentence, " ,.-");

        while (word != NULL)
        {
            if (!strcmp(word, keyword))
            {
                printTweet(dataset[i], save);
                flag++;
            }

            word = strtok(NULL, " ,.-");
        }
    }

    if (!flag)
        printf("'%s' could not be found anywhere in the dataset.\n\n", keyword);

    printf("%d tweets contain the keyword '%s'.\n", flag, keyword);
    printf("%d tweets searched.\n\n", NUM_TWEETS);

    return 0;
}

int findTweetByDate(tweet *dataset[], const int NUM_TWEETS, char date[20], int save)
{
    int flag = 0;

    printf("Date: %s", date);
    printf("\n");

    for (int i = 0; i < NUM_TWEETS; i++)
    {
        if (!strcmp(dataset[i]->date, date))
        {
            printTweet(dataset[i], save);
            flag++;
        }
    }

    if (!flag)
        printf("It seems like Elon Musk did not tweet on this date.\n\n");

    printf("%d tweets where posted on '%s'.\n", flag, date);
    printf("%d tweets searched.\n\n", NUM_TWEETS);

    return 0;
}

int findTweetByTime(tweet *dataset[], const int NUM_TWEETS, char *time, int save)
{
    int flag = 0;

    printf("Time: %s", time);
    printf("\n");

    for (int i = 0; i < NUM_TWEETS; i++)
    {
        if (!strcmp(dataset[i]->time, time))
        {
            printTweet(dataset[i], save);
            flag++;
        }
    }

    if (!flag)
        printf("It seems like Elon Musk did not tweet on this specific time.\n\n");

    printf("%d tweets where posted at '%s'.\n", flag, time);
    printf("%d tweets searched.\n\n", NUM_TWEETS);

    return 0;
}

char *getMonth(int month)
{
    char *mon;

    if (month == 1)
        mon = "January";
    else if (month == 2)
        mon = "February";
    else if (month == 3)
        mon = "March";
    else if (month == 4)
        mon = "April";
    else if (month == 5)
        mon = "May";
    else if (month == 6)
        mon = "June";
    else if (month == 7)
        mon = "July";
    else if (month == 8)
        mon = "August";
    else if (month == 9)
        mon = "September";
    else if (month == 10)
        mon = "October";
    else if (month == 11)
        mon = "November";
    else if (month == 12)
        mon = "December";

    return mon;
}

int findTweetByMonth(tweet *dataset[], const int NUM_TWEETS, int input_month, int save)
{
    char *m = getMonth(input_month);
    printf("Printing all tweets posted on %s: \n", m);

    int twt_month, count = 0;
    char date[20];

    for (int i = 0; i < NUM_TWEETS; i++)
    {
        // Copying the date from the dataset to a new string "m"
        // to avoid the strtok() function modifying the original
        // date string located in the dataset array
        strcpy(date, dataset[i]->date);

        // Get the month of the tweet by parsing
        // the first number before '/' in the saved date
        // Convert the month number from string to int for easier comparison
        twt_month = atoi(strtok(date, "/"));

        if (twt_month == input_month)
        {
            printTweet(dataset[i], save);
            count++;
        }
    }

    printf("%d tweets found from %s 2022.\n", count, m);
    printf("%d tweets searched.\n\n", NUM_TWEETS);

    return 0;
}

int getMostActiveMonth(tweet *dataset[], const int NUM_TWEETS)
{
    int month, counter[12];
    char *m;

    // Set all elements of the array to 0 (some may contain garbage values)
    for (int i = 0; i <= 12; i++)
    {
        counter[i] = 0;
    }

    // First, get the number of tweets for each month
    // Our 'array' of size 12 has an element for each month of the year
    // We will increment each element according to how many tweets were made on that month
    for (int i = 0; i < NUM_TWEETS; i++)
    {
        // Copying the date from the dataset to a new string "m"
        // to avoid the strtok() function modifying the original
        // date string located in the dataset array
        strcpy(m, dataset[i]->date);

        // Get the month of the tweet by parsing
        // the first number before '/' in the saved date
        month = atoi(strtok(m, "/"));
        counter[month]++;
    }

    int max_value = 0, max_month = 0;

    for (int i = 1; i <= 12; i++)
    {
        if (counter[i] > max_value)
        {
            max_month = i;
            max_value = counter[i];
        }
    }

    char *mon;
    mon = getMonth(max_month);

    printf("Elon Musk was most active in %s 2022 (%d tweets).\n\n", mon, max_value);

    return 0;
}

void swap(tweet *x, tweet *y)
{
    tweet temp = *x;
    *x = *y;
    *y = temp;
}

int sortByLikes(tweet *dataset[], const int NUM_TWEETS)
{
    int i, j, max_id;

    printf("Sorting dataset in descending order according to number of likes...\n");

    for (i = 0; i < NUM_TWEETS; i++)
    {
        max_id = i;
        for (j = i + 1; j < NUM_TWEETS; j++)
            if (dataset[j]->likes > dataset[max_id]->likes)
                max_id = j;

        swap(dataset[max_id], dataset[i]);
    }

    printf("Dataset sorted succesfully!\n\n");

    return 0;
}

int sortByRetweets(tweet *dataset[], const int NUM_TWEETS)
{
    int i, j, max_id;

    printf("Sorting dataset in descending order according to number of retweets...\n");

    for (i = 0; i < NUM_TWEETS; i++)
    {
        max_id = i;
        for (j = i + 1; j < NUM_TWEETS; j++)
            if (dataset[j]->retweets > dataset[max_id]->retweets)
                max_id = j;

        swap(dataset[max_id], dataset[i]);
    }

    printf("Dataset sorted succesfully!\n\n");

    return 0;
}

void filter_word(char *str)
{
    for (char *p = str; *p; ++p)
    {
        if (isalpha(*p))
            *str++ = *p;
    }

    *str = '\0';
}

int analyseTweet(char **wordlist, float *polarities, char *twt_text)
{
    if (wordlist == NULL || polarities == NULL || twt_text == NULL)
        return -1;

    int word_counter = 0;
    float total_pol = 0, word_pol = 0;
    char sentence[strlen(twt_text)];
    char *word;

    strcpy(sentence, twt_text);
    word = strtok(sentence, " ,.-");

    while (word != NULL)
    {
        // Filter out any non-alphabet characters in word
        // before comparing with dictionary words
        filter_word(word);
        for (int i = 0; i <= DICT_SIZE; i++)
        {
            if (!strcmp(wordlist[i], word))
            {
                word_pol = polarities[i];
                total_pol += word_pol;
                word_counter++;
            }
        }
        word = strtok(NULL, " ,.-");
    }

    if (!word_counter)
    {
        printf("Error: Unable to perform sentiment analysis on this tweet.\n");
        printf("None of the words in this tweet are found in the sentiment analysis dictionary.\n");
        printf("VADER dictionary size: %d words.\n\n", DICT_SIZE);
    }

    else
    {
        // Get average tweet polarity for this sentence
        total_pol /= word_counter;

        if (total_pol > 0)
            printf("Elon Musk seems positive in this tweet.\n");
        else
            printf("Elon Musk seems negative in this tweet.\n");

        printf("Sentiment Score: %.2f\n\n", total_pol);
    }

    return 0;
}

int sentimentAnalysis(tweet *twt)
{
    printf("Working!\n");
    char *wordlist[DICT_SIZE];
    float polarities[DICT_SIZE];

    if (readDictionary(wordlist, polarities) == -1)
        return -1;

    printf("Performing sentiment analysis on the following tweet:\n\n");
    printTweet(twt, 0);

    if (analyseTweet(wordlist, polarities, twt->text) == -1)
        return -1;

    return 0;
}
