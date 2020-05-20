//
//  fine.cpp
//
//  Created by Urvi Shah on 10/10/19.
//  Copyright © 2019 Urvi Shah. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    
    //makes sure that the printed number only has one number to the right of the decimal point
    cout.setf(ios::fixed);
    cout.precision(1);

    //gets name of defendant
    cout << "Defendant: ";
    string defendant;
    getline(cin, defendant);
    
   //gets amount of money paid and ignores the new line
    double fine = 20.0;
    cout << "Amount paid (in thousands): ";
    double amount;
    cin >> amount;
    cin.ignore(10000,'\n');
    
    //gets whether or not the person was a fake athlete
    cout << "Fake athlete? (y/n): ";
    string athlete;
    getline(cin, athlete);

    if (amount <= 40) //adds 66% of the fine to fines under 40 thousand dollars
    {
        fine = fine + 0.66 * amount;
        //cout << fine << "\n";
    }
    else
    {
        fine = fine + 0.66*40; //adds 66% of the fine for the first 40 thousand dollars
        //cout << fine << "\n";
    
        if (amount <= 250)
        {
            if (athlete == "y")
            {
                fine = fine + (amount-40)*0.22; //adds 22% of the fine for the rest of the amount
                //cout << fine << "\n";
            }
            else
            {
                fine = fine + ((amount-40)*0.10); //adds 10% of the fine for the rest of the amount
                //cout << fine << "\n";
            }
        }
        else
        {
            if (athlete == "y")
            {
                fine = fine + (250-40)*0.22; //adds 22% of the fine for the next 210 thousand dollars
                //cout << fine << "\n";
            }
            else
            {
                fine = fine + (250-40)*0.10; //adds 10% of the fine for the next 210 thousand dollars
                //cout << fine << "\n";
            }
            
            if (amount > 250)
            {
                fine = fine + (amount-250)*0.14; //adds 14% for the remaining fine if it is greater than 250 thousand dollars
                //cout << fine << "\n";
            }
        }
    }
        
    //prints out three hyphens and a statement displaying an error message or the fine they should pay
    cout << "---" << endl;
    if (defendant == "")
        cout << "You must enter a defendant name." << endl;
    else if (amount < 0)
        cout << "The amount paid must not be negative." << endl;
    else if (athlete != "y" and athlete != "n")
        cout << "You must enter y or n." << endl;
    else
        cout << "The suggested fine for " << defendant << " is $" << fine << " thousand." << endl;
    return 0;
}
