// Elijah Stokes
// CS310
// Lab 2: Randomly Unique Integers

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "unsorted.h"

using namespace std;

int main()
{
    UnsortedType list;
    ItemType item;
    bool found;

    // Seed the random number generator
    srand(time(0));

    // Keep adding numbers until there are 50 unique integers
    while (list.GetLength() < 50)
    {
        int number = rand() % 100;

        item.Initialize(number);

        // Check if the number is already in the list
        list.GetItem(item, found);

        // Only add the number if it is not already in the list
        if (!found)
        {
            list.PutItem(item);
        }
    }

    // Display the 50 unique integers in rows of 10
    cout << "50 Randomly Unique Integers:" << endl << endl;

    list.ResetList();

    for (int i = 1; i <= list.GetLength(); i++)
    {
        item = list.GetNextItem();
        item.Print(cout);

        if (i % 10 == 0)
            cout << endl;
        else
            cout << "\t";
    }

    return 0;
}