//
//  plot.cpp
//  plot
//
//  Created by Urvi Shah on 10/24/19.
//  Copyright © 2019 Urvi Shah. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include "grid.h"
using namespace std;

//constants that indicate if the line is horizontal or vertical
const int HORIZ = 0;
const int VERT = 1;

//constants that indicate if the character is in the foreground or background
const int FG = 0;
const int BG = 1;

int performCommands(string commandString, char& plotChar, int& mode, int& badPos);
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg);
void plotHorizontalLine(int r, int c, int distance, char ch, int fgbg);
void plotVerticalLine(int r, int c, int distance, char ch, int fgbg);

int main()
{
    setSize(20, 30);
    char currentChar = '*';
    int currentMode = FG;
    for (;;)
    {
        cout << "Enter a command string: ";
        string cmd;
        getline(cin, cmd);
        if (cmd == "")
            break;
        int position;
        int status = performCommands(cmd, currentChar, currentMode, position);
        switch (status)
        {
            case 0:
                cout << "Here!";
                draw();
                break;
            case 1:
                cout << "Syntax error at position " << position+1 << endl;
                break;
            case 2:
                cout << "Cannot perform command at position " << position+1 << endl;
                break;
            default:
                // It should be impossible to get here.
                cerr << "performCommands returned " << status << "!" << endl;
        }
    }
}

int performCommands(string commandString, char& plotChar, int& mode, int& badPos)
{
    int r = 1;
    int c = 1;
    bool plot = false;
    
    //checks for any syntax issues before running through commands in the commandString
    for (int a = 0; a < commandString.size(); a++)
    {
        int pos = a;
        
        
        if (tolower(commandString[a]) == 'h' || tolower(commandString[a]) == 'v' || tolower(commandString[a]) == 'f' || tolower(commandString[a]) == 'b')
        {
            if (a+1 == commandString.size())
            {
                badPos = pos+1;
                return 1;
            }
        }
    }
    
    //loop that runs through each possible command in commandString
    for (int a = 0; a < commandString.size(); a++)
    {
        //variable that keeps track of current position, since a changes throughout the code
        int pos = a;
        
        //checks for c in the commandString and resets grid if found
        if (tolower(commandString[a]) == 'c')
        {
            clearGrid();
            mode = FG;
            plotChar = '*';
            r = 1;
            c = 1;
        }
        //checks for f in the command string
        else if (tolower(commandString[a]) == 'f')
        {
            //if there is nothing after the 'f' character, then the function stops and reports a syntax error
            if (a+1 == commandString.size())
            {
                badPos = pos+1;
                return 1;
            }
            
            //sets mode to foreground
            mode = FG;
            
            //changes current character to character in commandString if it is printable
            if (isprint(commandString[a+1]))
            {
                plotChar = commandString[a+1];
                a++;
            }
            //if the character is not printable, the function stops and reports a syntax error
            else
            {
                badPos = pos;
                return 1;
            }
        }
        //checks for b in the command string
        else if (tolower(commandString[a]) == 'b')
        {
            //if there is nothing after the 'b' character, then the function stops and reports a syntax error
            if (a+1 == commandString.size())
            {
                badPos = pos+1;
                return 1;
            }
            
            //sets mode to background
            mode = BG;
            
            //changes current character to character in commandString if it is printable
            if (isprint(commandString[a+1]))
            {
                plotChar = commandString[a+1];
                a++;
            }
            //if the character is not printable, the function stops and reports a syntax error
            else
            {
                badPos = pos;
                return 1;
            }
        }
        //checks for 'h' in the command string
        else if (tolower(commandString[a]) == 'h')
        {
            //if there is nothing after the 'h' character, then the function stops and reports a syntax error
            if (a+1 == commandString.size())
            {
                badPos = pos+1;
                return 1;
            }
            
            //checks if there is a negative sign in front of the number
            bool neg = false;
            if (commandString[a+1] == '-')
            {
                neg = true;
                a++;
            }
           
            //checks if next character is a digit, if not the function stops and returns a syntax error
            if (!isdigit(commandString[a+1]))
            {
                badPos = pos+1;
                if (neg)
                    badPos++;
                return 1;
            }
            
            //translates the string into an integer variable that can be used in plotLine
            int num = 0;
            int count = 0;
            while (isdigit(commandString[a+1]) && count < 2)
            {
                num = num*10 + (commandString[a+1] - '0');
                a++;
                count++;
            }
            //if there was a negative sign in front of the digit, the number is made to be negative
            if (neg)
                num = -num;
            
            //calls plotLine with the current values
            plot = plotLine(r, c, num, HORIZ, plotChar, mode);
            
            //checks if plot line succeeded: if it did, the number of columns is increased by the distance
            //                               if it didn't, the function stops and reports a performance error
            if (plot)
            {
                c += num;
            }
            else
            {
                badPos = pos;
                return 2;
            }
        }
        //checks for 'v' in the command string
        else if (tolower(commandString[a]) == 'v')
        {
            //if there is nothing after the 'v' character, then the function stops and reports a syntax error
            if (a+1 == commandString.size())
            {
                badPos = pos+1;
                return 1;
            }
            
            //checks if there is a negative sign in front of the number
            bool neg = false;
            if (commandString[a+1] == '-')
            {
                neg = true;
                a++;
            }
            
            //checks if next character is a digit, if not the function stops and returns a syntax error
            int num = 0;
            int count = 0;
            if (!isdigit(commandString[a+1]))
            {
                badPos = pos+1;
                if (neg)
                    badPos++;
                return 1;
            }
            
            //translates the string into an integer variable that can be used in plotLine
            while (isdigit(commandString[a+1]) && count < 2)
            {
                num = num*10 + (commandString[a+1] - '0');
                a++;
                count++;
            }
            
            //if there was a negative sign in front of the digit, the number is made to be negative
            if (neg)
                num = -num;
            
            //calls plotLine with the current values
            plot = plotLine(r, c, num, VERT, plotChar, mode);
            
            //checks if plot line succeeded: if it did, the number of rows is increased by the distance
            //                               if it didn't, the function stops and reports a performance error
            if (plot)
            {
                r += num;
            }
            else
            {
                badPos = pos;
                return 2;
            }
        }
        //if the next character in the command string isn't 'c', 'b', 'f', 'h', or 'v', the function stops
        //and reports a syntax error
        else if (commandString.size() != 0)
        {
            badPos = pos;
            return 1;
        }
    }
    return 0;
}

//method that plots lines and checks to make sure that the parameters are reasonable before calling other methods
bool plotLine(int r, int c, int distance, int dir, char plotChar, int fgbg)
{
    //checks that the character is printable and that the integer fgbg is either 0 or 1
    if ((fgbg != FG && fgbg != BG) || !isprint(plotChar))
    {
        return false;
    }
    //calls plotHorizontalLine if the user wants a horizontal line
    if (dir == HORIZ)
    {
        //checks that the entire line is within the grid, otherwise exits the function
        if (r<0 || c<0 || (c+distance) > getCols() || r>getRows() || (c+distance) < 0)
        {
            return false;
        }
        else
            plotHorizontalLine(r,c,distance,plotChar, fgbg);
    }
    //calls plotVerticalLine if the user wants a vertical line
    else if (dir == VERT)
    {
        //checks that the entire line is within the grid, otherwise returns false
        if (r<0 || c<0 || (r+distance) > getRows() || c>getCols() || (r+distance) < 0)
        {
            return false;
        }
        else
            plotVerticalLine(r,c,distance,plotChar, fgbg);
    }
    //if the direction is not horizontal or vertical, the function returns false
    else
    {
        return false;
    }
    
    return true;
}

//plots a horizontal line based on the parameters
void plotHorizontalLine(int r, int c, int distance, char ch, int fgbg)
{
    if (distance < 0)
    {
        //sets characters in row to the provided character and goes backward since distance is negative
        for (int a = c; a>= (distance+c); a--)
        {
            if ((a>=0 && fgbg == FG) || (a>=0 && fgbg == BG && getChar(r,a) == ' '))
                setChar(r,a,ch);
        }
    }
    else
    {
        //sets characters in row to the provided character and goes forward since distance is positive
        for (int a = c; a<= (distance+c); a++)
        {
            if ((a<getCols() && fgbg == FG) || (a<getCols() && fgbg == BG && getChar(r,a) == ' '))
                setChar(r,a,ch);
        }
    }
}

//plots a vertical line based on the parameters
void plotVerticalLine(int r, int c, int distance, char ch, int fgbg)
{
    if (distance<0)
    {
        //sets characters in column to the provided character and goes backward since distance is negative
        for (int a = r; a>= (distance+r); a--)
        {
            if ((a>=0 && fgbg == FG) || (a>=0 && fgbg == BG && getChar(a,c) == ' '))
                setChar(a,c,ch);
        }
    }
    else
    {
        //sets characters in column to the provided character and goes forward since distance is positive
        for (int a = r; a<= (distance+r); a++)
        {
            if ((a<getRows() && fgbg == FG) || (a<getRows() && fgbg == BG && getChar(a,c) == ' '))
                setChar(a,c,ch);
        }
    }
}

