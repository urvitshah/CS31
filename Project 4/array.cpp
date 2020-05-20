//
//  array.cpp
//  array
//
//  Created by Urvi Shah on 11/5/19.
//  Copyright © 2019 Urvi Shah. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

int main()
{
    string h[7] = { "mick", "marie", "fiona", "rudy", "", "gordon", "lindsey" };
    assert(lookup(h, 7, "gordon") == 5);
    assert(lookup(h, 7, "fiona") == 2);
    assert(lookup(h, 2, "fiona") == -1);
    assert(positionOfMax(h, 7) == 3);
    
    string g[4] = { "mick", "marie", "lindsey", "nancy" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "mick?" && g[3] == "nancy?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "marie?");
    
    string e[4] = { "fiona", "rudy", "", "gordon" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "marie", "marie", "marie", "rudy", "rudy" };
    assert(countRuns(d, 5) == 2);
    
    string f[3] = { "lindsey", "fiona", "mike" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");
    assert(separate(h, 7, "lindsey") == 3);
    
    cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value)
{
    if (n<0)
        return -1;
    //goes through array with given size and adds value to each string in the array
    for (int i = 0; i < n; i++)
    {
        a[i] += value;
    }
    
    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n<0)
        return -1;
    
    //checks if each string in the array of given size is equal to target
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
            return i;
    }
    
    //returns -1 if not found
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if (n<0)
        return -1;
    
    //goes through entire array of given size
    for (int i = 0; i < n; i++)
    {
        bool greater = true;
        //goes through array and checks if the array at i is greater than or equal to every other element in the array
        for (int j = 0; j < n; j++)
        {
            if (a[i] < a[j])
                greater = false;
        }
        if (greater == true)
        {
            return i;
        }
    }
    
    return -1;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n<0 || pos<0)
        return -1;
    
    //stores array at pos in a variable so the for loop can write over it
    string temp = a[pos];
    
    //rotates every array element after pos to the left
    for (int i = pos; i < n-1; i++)
    {
        a[i] = a[i+1];
    }
    
    //sets the last element in the array to the original value at pos
    a[n-1] = temp;
    
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n<0)
        return -1;
    
    string temp = "";
    int count = 0;
    //runs through array of given size and adds one to the count if the string does not equal the string before it
    for (int i = 0; i < n; i++)
    {
        if (temp != a[i])
        {
            count++;
            temp = a[i];
        }
    }
    return count;
}

int flip(string a[], int n)
{
    if (n<0)
        return -1;
    
    int i = 0;
    int j = n-1;
    //runs through array from the end and from the beginning and breaks out when it reaches the middle of the array
    while (i < n && j >= 0 && j > i)
    {
        //switches the string in the array at position i and j
        string temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;
        j--;
    }
    
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1<0 || n2<0)
        return -1;
    int n = 0;
    //determines which size is bigger to see how many times to run through a loop
    if (n1 <= n2)
        n = n1;
    else
        n = n2;
    
    //looks for position where arrays are not equal to each other
    for (int i = 0; i < n; i++)
    {
       if (a1[i] != a2[i])
           return i;
    }
    
    return n;
}


int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1<0 || n2<0)
        return -1;
    
    bool check = true;
    //runs through first array of given size
    for (int i = 0; i < n1-1; i++)
    {
        check = true;
        //runs through second array and checks if every string in the second array shows up in order in the first array
        for (int j = 0; j < n2; j++)
        {
            if (a1[i + j] != a2[j])
                check = false;
        }
        //returns position in first array if the second array's elements appear in order
        if (check)
            return i;
    }
    
    //returns -1 if the second array is not found within the first array
    return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1<0 || n2<0)
        return -1;
    
    //runs through first array of given size
    for (int i = 0; i < n1; i++)
    {
        //runs through second array of given size and checks if any elements in the second array are equal to the first array at i
        for (int j = 0; j < n2; j++)
        {
           if (a2[j] == a1[i])
               return i;
        }
    }
    
    //returns -1 if nothing is found to be equal
    return -1;
}

int separate(string a[], int n, string separator)
{
    if (n<0)
        return -1;
    
    //moves string to the end of the array if it is equal to the separator
    for (int i = 0; i < n; i++)
    {
        if (a[i] == separator)
        {
            rotateLeft(a, n, i);
        }
    }
    
    //moves string to the end of the array if it is greater than the separator
    for (int i = 0; i < n; i++)
    {
        if (a[i] > separator)
        {
            rotateLeft(a, n, i);
        }
    }
    
    int num = 0;
    //finds the position in the array where the string becomes greater than or equal to the separator
    for (int i = 0; i < n; i++)
    {
        if (a[i] < separator)
        {
            num++;
        }
    }
    
    return num;
}
