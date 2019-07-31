// This program demonstrates the linear search algorithm.
#include <iostream>
using namespace std;

// Function prototype
template <class ItemType>
int linearSearch(const ItemType[], const int, ItemType);

//int main()
//{
//   const int SIZE = 5;
//   string tests[SIZE] = { "a", "b", "c", "de", "fg" };
//   int results;
//
//   // Search the array for 100.
//   string value{"de"};
//   results = linearSearch(tests, SIZE, value);
//
//   // If linearSearch returned -1, then 100 was not found.
//   if (results == -1)
//      cout << "You did not earn 100 points on any test\n";
//   else
//   {
//      // Otherwise results contains the subscript of
//      // the first 100 in the array.
//      cout << "You earned 100 points on test ";
//      cout << (results + 1) << endl;
//   }
//   return 0;
//}

//*****************************************************************
// The linearSearch function performs a linear search on an       *
// integer array. The array arr, which has a maximum of size      *
// elements, is searched for the number stored in value. If the   *
// number is found, its array subscript is returned. Otherwise,   *
// -1 is returned indicating the value was not in the array.      *
//*****************************************************************
template<class ItemType>
int linearSearch(const ItemType arr[], int size, ItemType value)
{
   int index = 0;       // Used as a subscript to search array
   int position = -1;   // To record position of search value
   bool found = false;  // Flag to indicate if the value was found

   while (index < size && !found)
   {
      if (arr[index] == value)  // If the value is found
      {
         found = true;         // Set the flag
         position = index;     // Record the value's subscript
      }
      index++;                  // Go to the next element
   }
   return position;              // Return the position, or -1
}
