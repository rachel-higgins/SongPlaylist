//*****************************************************************************
// Author: Rachel Higgins
// Date: October 10, 2022
// Course: CS260 Data Structures
// Assignment: C++ Project Assignment 1
// Descrtiption: This is the test program for SongList.cpp and Song.cpp
// Input: int option, char artist, char title, float length, int likes,  
//        int update, int min.
// Output: SongList aList
//*****************************************************************************
#include "main.h"

int main()
{
   SongList aList;
   int option = 0;
   const int MAX_CHAR = 100;
   char artist[MAX_CHAR + 1];
   char title[MAX_CHAR + 1];
   char fileName[] = "songs.txt";
   float length = 0.0;
   int likes = 0, update = 0, min = 0;

   
   aList.loadFromFile(fileName); // test loadFromFile()

   while ((option = menu()) != 6)
   {
      cin.ignore(101, '\n');
      switch (option)
      {
      case 1: // add new song
         cout << "Enter the artist's name: ";
         cin.getline(artist, MAX_CHAR, '\n');
         cout << "Enter the song title: ";
         cin.getline(title, MAX_CHAR, '\n');
         cout << "Enter the song length: ";
         cin >> length;
         cout << "Enter number of likes: ";
         cin >> likes;
         cout << endl;
         aList.add(artist, title, length, likes);
         cout << aList << endl; // test output
         break;
      case 2: // edit number of like
         cout << "Which song would you like to update?: ";
         cin.getline(title, MAX_CHAR, '\n');
         cout << "Enter the new number of likes: ";
         cin >> update;
         cout << endl;
         aList.edit(title, update);
         cout << aList << endl; // test output
         break;
      case 3: // display list
         cout << aList << endl;
         break;
      case 4: // display songs of artist
         cout << "Enter artist's name: ";
         cin.getline(artist, MAX_CHAR, '\n');
         cout << endl;
         aList.display(artist);
         cout << endl;
         break;
      case 5: // delete songs using user input as delimiter
         cout << "Enter the minimum number of likes: ";
         cin >> min;
         cout << endl;
         aList.remove(min);
         cout << aList << endl;
         break;
      default:
         break;
      }
   }

   return 0;
}

// name: menu()
// description: this function displays a menue and gets input from the user.
// input: int option
// output: menu options as text
int menu()
{
   int option = 0;
   cout << "Select one of the following options:" << endl
        << "1. Add a new song" << endl
        << "2. Edit the number of likes for a song" << endl
        << "3. Display entire list" << endl
        << "4. Display songs for a specific artist" << endl
        << "5. Delete songs with fewer likes" << endl
        << "6. Exit" << endl
        << "Enter option: ";
   cin >> option;
   cout << endl;
   return option;
}
