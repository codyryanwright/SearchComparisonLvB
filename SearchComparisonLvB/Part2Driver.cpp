// Author: Cody Wright
// Lab: Lab 6 Part 2
// Purpose: Timing of Search Functions
// Data Structures:
// Date: 4/25/2018

#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <cstdlib>
#include <algorithm>
#include "binarySearch.cpp"
#include "linearSearch.cpp"

using namespace std;

// helper functions
template<class ItemType>
bool verifySorted(ItemType[], int);

void intDriver(string mode)
{
  const string filename = "int_search_results.csv";
  ofstream outfile(filename);
  outfile << ",Binary,Linear"<<endl;
  cout<<"Now processing..."<<endl;  
  
  static float bin_duration = 0.0; // time in milliseconds
  static float lin_duration = 0.0; // time in milliseconds    
  int count{1};
  int iterations{1000}; // Requires at least 100 iterations to show that binary out performs linear
                        // otherwise the sorting of large files is slower than linear search of said file
  int size{100000000}; //starts at 100M
  bool run_driver{true};
  
  while(run_driver)
  {
    // Set unsorted arrays
    int* intArray = new int[size];
    for(int index = 0; index < size; ++index)
    {
      intArray[index] = (rand() % 100000000) + 1;
    }
    
    int searchValue{0};
    string strVal{""};
    int position{0};
    
    cout<<"size == "<<size<<endl;
        
    while(count<=iterations) // five iterations of each size for avg time
    {
      cout<<"count == "<<count<<endl;
      
      if(mode=="1") searchValue=(rand()%100000000)+1; // search for new random integer (allows new time without having to rebuild/sort array)
      if(mode=="2")
      {
        while(true)
        {
          cout<<"Please enter an integer: ";
          cin>>strVal;
          
          if(isalpha(strVal[0])) cout<<"Invalid Entry"<<endl;
          else
          {
            searchValue=stoi(strVal);
            break;
          }
       }
      }
      
      int startTime = clock(); // start the test clock
      if(count==1) sort(intArray, intArray+size);  // post clock sort, sort time will be averaged in to the final time
      position=binarySearch(intArray, 0, size-1, searchValue);
      int stopTime = clock();  // stop the test clock
      bin_duration += stopTime - startTime;
      
      cout<<"Position = "<<position<<endl; // Just for testing purposes
      
      if(count==1) outfile << size; // first iteration print legend
      if(count==iterations) outfile << "," << bin_duration/count; // on last iteration print duration average
      ++count;
      cout<<"duration == "<<bin_duration<<endl;
    }
    while(count<=(iterations*2)) // Loop will cycle iterations times
    {
      cout<<"count == "<<count<<endl;
      
      if(mode=="1") searchValue=(rand()%100000000)+1; // search for new random integer (allows new time without having to rebuild/sort array)
      if(mode=="2")
      {
        while(true)
        {
          cout<<"Please enter an integer: ";
          cin>>strVal;
          
          if(isalpha(strVal[0])) cout<<"Invalid Entry"<<endl;
          else
          {
            searchValue=stoi(strVal);
            break;
          }
       }
      }
      
      int startTime = clock(); // start the test clock
      position=linearSearch(intArray, size, searchValue);
      int stopTime = clock();  // stop the test clock
      lin_duration += stopTime - startTime;
      
      cout<<"Position = "<<position<<endl; // Just for testing purposes
      
      if(count==iterations*2) outfile << "," << lin_duration/iterations << endl;
      cout<<"duration == "<<lin_duration<<endl;
      ++count;
    }

    // Memory Management & Reset for new run
    delete [] intArray;
    intArray = nullptr;
    bin_duration = 0.0;
    lin_duration = 0.0;
    
    if(count>(iterations*2) & size==100000000) //exit condition for loop and first step
    {
      size+=150000000;
      count=1;
    }
    else if(count>(iterations*2))
    {
      size+=250000000;
      count=1;
    }
    
    if(size>1000000000) break; //1B is last test size        
  }
  outfile.close();
  cout<<"\nTime results written to "<<filename <<endl;
}

void strDriver(string mode)
{
  const string filename = "str_search_results.csv";
  ofstream outfile(filename);
  
  outfile << ",Binary,Linear"<<endl;
  
  cout<<"Now processing..."<<endl;  
  
  float bin_duration = 0.0; // time in milliseconds
  float lin_duration = 0.0; // time in milliseconds
  int count{1};
  int iterations{1000};
  int size{100000}; //starts at 100M
  while(true)
  {
    const string infileName = "LastName2010new.txt"; // 435,670 names
    ifstream inFile(infileName);
    if (!inFile)
    {
      cout << "Unable to open file " << infileName << endl;
      exit(1);
    }

    string* strArray = new string[size];
      
    if(inFile)
    {  
      int index{0};
      cout << "\nBuilding string array from " << infileName << endl;
      while(inFile>>strArray[index])
      {
        ++index;
        if(index==size) break; //break after last wanted size is added
      }
    }
    else
    {
      cout << "Filename not found."; 
      exit(1); 
    }
            
    int position{0};
    int testCount{0};
    string searchValue{""};
    string testModeArray[]={"WRIGHT", "KU", "MOTEN", "BACON", "WILLNOTFIND"}; // Just some random search values
      
    cout<<"size == "<<size<<endl;
        
    while(count<=iterations) // five iterations of each size for avg time
    {
      cout<<"count == "<<count<<endl;
      if(mode=="3")searchValue=testModeArray[testCount];
      else if (mode=="4")
      {
        cout<<"Please enter a name: ";
        cin>>searchValue;
      }
      
      int startTime = clock(); // start the test clock
      if(count==1) sort(strArray, strArray+size);  // post clock sort, only on first so averaged in to time
      position=binarySearch(strArray, 0, size-1, searchValue);
      int stopTime = clock();  // stop the test clock
      bin_duration += stopTime - startTime;
      
      cout<<"Position = "<<position<<endl; // Just for testing purposes
      
      if(count==1) outfile << size; // first iteration print legend
      if(count==iterations) outfile << "," << bin_duration/count; // on last iteration print duration average
      ++count;
      cout<<"duration == "<<bin_duration<<endl;
      
      testCount==4? testCount=0 : ++testCount; // array[5] indexes 0-4
    }
    
    while(count<=(iterations*2))
    {
      cout<<"count == "<<count<<endl;
      
      if(mode=="3")searchValue=testModeArray[testCount];
      else if (mode=="4")
      {
        cout<<"Please enter a name: ";
        cin>>searchValue;
      }
      
      int startTime = clock(); // start the test clock
      position=linearSearch(strArray, size, searchValue);
      int stopTime = clock();  // stop the test clock
      lin_duration += stopTime - startTime;
      
      cout<<"Position = "<<position<<endl; // Just for testing purposes
      
      if(count==(iterations*2)) outfile << "," << lin_duration/iterations << endl;
      cout<<"duration == "<<lin_duration<<endl;
      ++count;
      
      testCount==4? testCount=0 : ++testCount; // array[5] indexes 0-4
    }

    // Memory Management & Reset for new run
    delete [] strArray;
    strArray = nullptr;
    
    if(count>iterations*2)//exit condition for final test loop
    {
      size+=67000;
      count=1;
    }
    
    if(size>435000) break; //435,000 is last test size
  }
  outfile.close();
  cout<<"\nTime results written to "<<filename <<endl;
}

int main()
{
  cout<<"This program will build and search dynamic array's of varying sizes\n\twith either random integer values or strings from a file..."<<endl;

  string mode{""};

  while(true)
  {
    cout<<"\nYou can choose between entering your own search values,\n\tor a test mode with computer generated search values for faster testing...\n"<<endl;
    cout<<"Please Choose a Search Mode"<<endl;
    cout<<"1) Test Mode Integer Search\n"<<
          "2) User Defined Integer Search\n"<<
          "3) Test Mode Name Search\n"<<
          "4) User Defined String Names Search\n"<<
          "0) Exit"<<endl;
                  
    //validation loop
    while(true)
    {
      cout<< "\nSearch Mode: ";
      cin>>mode;
      
      if(mode=="1" || mode=="2" || mode=="3" || mode=="4" || mode=="0")
      {
        cout<<endl; //line break after menu
        break;
      }
      else cout<<" Invalid mode"<<endl;
    }
    
    if(mode=="0") break;
    else if(mode=="1"||mode=="2") intDriver(mode);
    else if(mode=="3"||mode=="4") strDriver(mode);
  }
  
}


/*

This program will build and search dynamic array's of varying sizes
        with either random integer values or strings from a file...

You can choose between entering your own search values,
        or a test mode with computer generated search values for faster testing...

Please Choose a Search Mode
1) Test Mode Integer Search
2) User Defined Integer Search
3) Test Mode Name Search
4) User Defined String Names Search
0) Exit

Search Mode: 1

Now processing...
size == 100000000
count == 1
Position = 93984983
duration == 25312
count == 2
Position = 8273314
duration == 25312
count == 3
Position = 75552366
duration == 25312
count == 4
Position = 38760374
duration == 25312
count == 5
Position = 17599486
duration == 25312
count == 6
Position = 34850324
duration == 107
count == 7
Position = 94396756
duration == 383
count == 8
Position = 14017421
duration == 426
count == 9
Position = 13846770
duration == 468
count == 10
Position = 27915228
duration == 554
size == 250000000
count == 1
Position = 235771176
duration == 94750
count == 2
Position = 223579404
duration == 94750
count == 3
Position = 3784178
duration == 94750
count == 4
Position = 13687132
duration == 94750
count == 5
Position = 63224790
duration == 94750
count == 6
Position = 159613311
duration == 1038
count == 7
Position = 61994564
duration == 1230
count == 8
Position = 125269745
duration == 1618
count == 9
Position = 213936284
duration == 2278
count == 10
Position = 218277154
duration == 2931
size == 500000000
count == 1
Position = 201950071
duration == 229621
count == 2
Position = 79071043
duration == 229621
count == 3
Position = 334304807
duration == 229621
count == 4
Position = 304046628
duration == 229621
count == 5
Position = 252593992
duration == 229621
count == 6
Position = 391140252
duration == 4109
count == 7
Position = 100731521
duration == 4416
count == 8
Position = 112480407
duration == 4749
count == 9
Position = 356744835
duration == 5822
count == 10
Position = 432590120
duration == 7120
size == 750000000
count == 1
Position = 147720334
duration == 434673
count == 2
Position = 312492368
duration == 434673
count == 3
Position = 489692686
duration == 434673
count == 4
Position = 267837522
duration == 434673
count == 5
Position = 156028746
duration == 434673
count == 6
Position = 492544415
duration == 8585
count == 7
Position = 97755921
duration == 8886
count == 8
Position = 209290441
duration == 9527
count == 9
Position = 403279773
duration == 10758
count == 10
Position = 680015622
duration == 12800
size == 1000000000
count == 1
Position = 985992429
duration == 721458
count == 2
Position = 522735593
duration == 721458
count == 3
Position = 438964842
duration == 721458
count == 4
Position = 112487791
duration == 721458
count == 5
Position = 321044920
duration == 721458
count == 6
Position = 21088774
duration == 12864
count == 7
Position = 404183661
duration == 14066
count == 8
Position = 923851482
duration == 16865
count == 9
Position = 501897445
duration == 18395
count == 10
Position = 424476944
duration == 19664

Time results written to int_search_results3.csv

You can choose between entering your own search values,
        or a test mode with computer generated search values for faster testing...

Please Choose a Search Mode
1) Test Mode Integer Search
2) User Defined Integer Search
3) Test Mode Name Search
4) User Defined String Names Search
0) Exit

Search Mode: 3

Now processing...

Building string array from LastName2010new.txt
size == 100000
count == 1
Position = 98827
duration == 1217
count == 2
Position = -1
duration == 1217
count == 3
Position = 62919
duration == 1217
count == 4
Position = 3611
duration == 1217
count == 5
Position = -1
duration == 1217
count == 6
Position = 98683
duration == 190
count == 7
Position = -1
duration == 193
count == 8
Position = 62915
duration == 195
count == 9
Position = 3608
duration == 195
count == 10
Position = -1
duration == 198

Building string array from LastName2010new.txt
size == 167000
count == 1
Position = 165042
duration == 1332
count == 2
Position = -1
duration == 1332
count == 3
Position = 105178
duration == 1332
count == 4
Position = 5950
duration == 1332
count == 5
Position = -1
duration == 1332
count == 6
Position = 164824
duration == 204
count == 7
Position = -1
duration == 209
count == 8
Position = 105175
duration == 214
count == 9
Position = 5939
duration == 215
count == 10
Position = -1
duration == 220

Building string array from LastName2010new.txt
size == 234000
count == 1
Position = 231257
duration == 1504
count == 2
Position = 115716
duration == 1504
count == 3
Position = 147433
duration == 1504
count == 4
Position = 8339
duration == 1504
count == 5
Position = -1
duration == 1504
count == 6
Position = 230938
duration == 228
count == 7
Position = 115716
duration == 232
count == 8
Position = 147429
duration == 237
count == 9
Position = 8336
duration == 237
count == 10
Position = -1
duration == 244

Building string array from LastName2010new.txt
size == 301000
count == 1
Position = 297472
duration == 1725
count == 2
Position = 148715
duration == 1725
count == 3
Position = 189574
duration == 1725
count == 4
Position = 11057
duration == 1725
count == 5
Position = -1
duration == 1725
count == 6
Position = 297008
duration == 255
count == 7
Position = 148715
duration == 260
count == 8
Position = 189570
duration == 267
count == 9
Position = 11047
duration == 267
count == 10
Position = -1
duration == 276

Building string array from LastName2010new.txt
size == 368000
count == 1
Position = 362249
duration == 2003
count == 2
Position = 181049
duration == 2003
count == 3
Position = 229987
duration == 2003
count == 4
Position = 13744
duration == 2003
count == 5
Position = -1
duration == 2003
count == 6
Position = 362057
duration == 290
count == 7
Position = 181049
duration == 295
count == 8
Position = 229977
duration == 303
count == 9
Position = 13727
duration == 303
count == 10
Position = -1
duration == 315

Building string array from LastName2010new.txt
size == 435000
count == 1
Position = 426503
duration == 2337
count == 2
Position = 212803
duration == 2337
count == 3
Position = 268195
duration == 2337
count == 4
Position = 16618
duration == 2337
count == 5
Position = -1
duration == 2337
count == 6
Position = 426072
duration == 332
count == 7
Position = 212803
duration == 339
count == 8
Position = 268188
duration == 349
count == 9
Position = 16601
duration == 349
count == 10
Position = -1
duration == 362

Time results written to str_search_results.csv

You can choose between entering your own search values,
        or a test mode with computer generated search values for faster testing...

Please Choose a Search Mode
1) Test Mode Integer Search
2) User Defined Integer Search
3) Test Mode Name Search
4) User Defined String Names Search
0) Exit

Search Mode: a
 Invalid mode

Search Mode: 0


--------------------------------
Process exited after 1290 seconds with return value 0
Press any key to continue . . .
*/
