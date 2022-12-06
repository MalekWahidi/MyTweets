#ifndef TWEET_H
#define TWEET_H

#define TWEET_SIZE 2048
#define DATE_TIME_SIZE 32
#define DATE_SIZE 15
#define TIME_SIZE 10
#define BUFFER_SIZE 4096
#define DICT_SIZE 7518
#define DICT_BUFF_SIZE 32

#define CSV_FILE "C:\\Users\\Malek\\Desktop\\University\\Prog\\FinalC\\resources\\cleandata-modified.csv"
#define DICT "C:\\Users\\Malek\\Desktop\\University\\Prog\\FinalC\\resources\\VaderDictionary.csv"
#define OUTPUT "C:\\Users\\Malek\\Desktop\\University\\Prog\\FinalC\\output.txt"

typedef struct
{
    char text[TWEET_SIZE];
    int retweets;
    int likes;
    char date[DATE_SIZE];
    char time[TIME_SIZE];
    int id;
} tweet;

tweet *newTweet(char text[TWEET_SIZE], int retweets, int likes, char date[DATE_SIZE], char time[TIME_SIZE], int id);
int printTweet(tweet *twt, int save);
void printAllTweets(tweet *dataset[], const int NUM_TWEETS, int save);
int getAvg(tweet *dataset[], const int NUM_TWEETS, int option, int save);
int getMax(tweet *dataset[], const int NUM_TWEETS, int option, int save);
int getMin(tweet *dataset[], const int NUM_TWEETS, int option, int save);
int searchKeyword(tweet *dataset[], const int NUM_TWEETS, char *keyword, int save);
int findTweetByDate(tweet *dataset[], const int NUM_TWEETS, char *date, int save);
int findTweetByTime(tweet *dataset[], const int NUM_TWEETS, char *time, int save);
int findTweetByMonth(tweet *dataset[], const int NUM_TWEETS, int input_month, int save);
int getMostActiveMonth(tweet *dataset[], const int NUM_TWEETS);
int sortByLikes(tweet *dataset[], const int NUM_TWEETS);
int sortByRetweets(tweet *dataset[], const int NUM_TWEETS);
int sentimentAnalysis(tweet *twt);

#endif
