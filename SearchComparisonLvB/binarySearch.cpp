#include <iostream>
#include <string>

using namespace std;

template<class ItemType>
int binarySearch(ItemType anArray[], int first, int last, ItemType target)
{
   int index;
   if (first > last)
      index = -1; // target not in original array
   else
   {
      // If target is in anArray,
      // anArray[first] <= target <= anArray[last]
      int mid = first + (last - first) / 2;
      if (target == anArray[mid])
         index = mid; // target found at anArray[mid]
      else if (target < anArray[mid])
         // Point X
         index = binarySearch(anArray, first, mid - 1, target);
      else
         // Point Y
         index = binarySearch(anArray, mid + 1, last, target);
   }  // end if
   
   return index;
}  // end binarySearch

//int main()
//{  
//   int IntArray[] = {1, 5, 9, 12, 15, 21, 29, 31};
//   int target1 = 9;
//   cout <<  "Searching for 9: binarySearch returns: " << binarySearch(IntArray, 0, 7, target1) << endl << endl;
//   
//   string stringArray[] = {"david","john", "josh", "mason","richard"};
//   string target2 = "mason";
//   cout << "Searching for " << target2 <<  ": binarySearch returns: " << binarySearch(stringArray, 0, 4, target2) << endl;
//}


