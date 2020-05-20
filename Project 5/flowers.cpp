#define _CRT_SECURE_NO_DEPRECATE
#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

int playOneRound(const char words[][7], int nWords, int wordnum);

const char WORDFILENAME[] = "/Users/urvishah/Documents/words.txt";

int main()
{
    //array that can hold at least 9000 words with at most 6 six letters
    char w[9000][7];
    
    //number of words in the array
    int n = getWords(w, 9000, WORDFILENAME);
    
    cout.setf(ios::fixed);
    cout.precision(2);
    
    if (n < 1)
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }

    
    //asks for rounds and checks for valid number
    int rounds = 0;
    cout << "How many rounds do you want to play? ";
    cin >> rounds;
    cin.ignore(10000,'\n');
    if (rounds <= 0)
    {
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    double sum = 0.0;
    int max = 0;
    int min = 100000;
    
    //runs through the number of rounds that the user asked for
    for (int a = 1; a <= rounds; a++)
    {
        int num = randInt(0, n-1);
        cout << "\nRound " << a << endl;
        cout << "The mystery word is " << strlen(w[num]) << " letters long." << endl;
        //calls function that runs through one round of the game
        int score = playOneRound(w, n, num);
        
        //changes print statement based on the number of rounds it took to guess correctly
        if (score == 1)
            cout << "You got it in " << score << " try." << endl;
        else if (score == -1)
            return 0;
        else
            cout << "You got it in " << score << " tries." << endl;
        
        sum += score;
        
        //on the first run, the min and max score is set to the current score
        if (a == 1)
        {
            min = score;
            max = score;
        }
        //checks if the score is greater or less than the max or min score and changes values
        //for max and min accordingly
        else
        {
            if (score<min)
                min = score;
            if (score>max)
                max = score;
                
        }
        
        //calculates and prints the average of the scores and the minimum and maximum
        cout<< "Average: " << sum/a << ", minimum: " << min << ", maximum: " << max << endl;
    }
    
    
    
}

//runs through a round of the game
// three paramaters: words - an array containing all c-strings in the text file, nWords - the number
// of words in the array, wordnum - the position of the mystery word
int playOneRound(const char words[][7], int nWords, int wordnum)
{
    //returns -1 if the parameters are not valid
    if (nWords < 0 || wordnum < 0 || nWords <= wordnum)
        return -1;
    
    bool exit = false;
    int numRounds = 0;
    
    //continues asking for trial words and checking the mystery word until the user guesses correctly
    while (!exit)
    {
        numRounds++;
        int flowers = 0;
        int bees = 0;
        char trial[107];
        char mystery[7];
        strcpy(mystery, words[wordnum]);
    
        //gets trial word from user
        cout << "Trial word: ";
        cin.getline(trial, 107);
        
        //checks that every letter entered is lowercase
        bool notLower = false;
        for (int a = 0; trial[a] != '\0'; a++)
        {
            if (!islower(trial[a]))
                notLower = true;
        }
        //checks that the trial word is between 4 and 6 letters and that it is lowercase
        if (strlen(trial) < 4 || strlen(trial) > 6 || notLower)
        {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            
        }
        else //continues with the rest of the loop if trial word is valid length and case
        {
            //checks if trial word is in the text file
            bool notInFile = true;
            for (int a = 0; a < nWords; a++)
            {
                if (strcmp(trial, words[a]) == 0)
                {
                    notInFile = false;
                }
            }
            if (notInFile)
                cout << "I don't know that word." << endl;
            else //continues with the loop if the word is found in the text file
            {
                //checks for flowers by checking if the characters in the same position
                //in both c-strings equal each other
                for (int a = 0; mystery[a] != '\0'; a++)
                {
                   if (trial[a] == mystery[a])
                   {
                       flowers++;
                       //changes characters to spaces to indicate that they have already been accounted for
                       trial[a] = ' ';
                       mystery[a] = ' ';
                   }
                }
                
                //checks for bees by using a nested for loop that runs through every character in mystery and
                //every character in trial and checks to see if they are equal
                for (int m = 0; mystery[m] != '\0'; m++)
                {
                    for (int t = 0; trial[t] != '\0'; t++)
                    {
                        //does not check characters that are spaces
                        if (mystery[m] != ' ' && trial[t] != ' ' && trial[t] == mystery[m])
                        {
                            bees++;
                            //changes characters to spaces to indicate that they have already been accounted for
                            trial[t] = ' ';
                            mystery[m] = ' ';
                        }
                        
                    }
                }
                
                //checks to see if the user guessed the word correctly and exits the loops if it has
                if (strlen(trial) == strlen(mystery) && flowers == strlen(mystery))
                {
                    exit = true;
                }
                //prints number of flowers and bees
                else
                {
                    cout << "Flowers: " << flowers << ", Bees: " << bees << endl;
                }
            }
        }
    }
    
    //returns the number of rounds it took to complete the game
    return numRounds;
}
