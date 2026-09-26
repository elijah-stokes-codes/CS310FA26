// Elijah Stokes
// CS310
// Lab 3: Heads or Tails
// Array-Based Unsorted List

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "unsorted.h"

using namespace std;

int main()
{
    UnsortedType list;
    ItemType item;

    srand(time(0));

    // Pick a random point between 1 and 49
    int randomPoint = (rand() % 49) + 1;

    cout << "ARRAY-BASED UNSORTED LIST" << endl;
    cout << "=========================" << endl;

    // Point 1: Empty list
    cout << "\n1. EMPTY LIST" << endl;
    cout << "List length: " << list.GetLength() << endl;
    cout << "Head: List is empty" << endl;
    cout << "Tail: List is empty" << endl;

    // Fill the list with 50 random integers
    for (int i = 1; i <= 50; i++)
    {
        int number = (rand() % 100) + 1;
        item.Initialize(number);
        list.PutItem(item);

        // Point 2: Random point during construction
        if (i == randomPoint)
        {
            cout << "\n2. RANDOM POINT DURING CONSTRUCTION" << endl;
            cout << "After adding " << i << " integers:" << endl;

            cout << "Head: ";
            list.Head().Print(cout);
            cout << endl;

            cout << "Tail: ";
            list.Tail().Print(cout);
            cout << endl;
        }
    }

    // Point 3: Completed list
    cout << "\n3. COMPLETED LIST" << endl;
    cout << "List length: " << list.GetLength() << endl;

    cout << "\nList Values:" << endl;

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

    cout << "\nHead: ";
    list.Head().Print(cout);
    cout << endl;

    cout << "Tail: ";
    list.Tail().Print(cout);
    cout << endl;

    return 0;
}