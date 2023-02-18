//*****************************************************************************
// Name: songlist.cpp
// Descrtiption: This is the executable file for the SongList class object.
//*****************************************************************************
#include "songlist.h"

// name: SongList()
// description: constructor
// input: none
// output: none
SongList::SongList() : head(nullptr) {}

// name: ~SongList()
// description: destructor
// input: none
// output: none
SongList::~SongList()
{
   destroy(head);
}

// name: destroy()
// description: this function destroys every Node of the SongList recursively
// input: none
// output: none
void SongList::destroy(Node *head)
{
   if (head)
   {
      destroy(head->next);
   }
   delete head;
}

// name: add()
// description: this function adds a new song
// input: none
// output: a result(success/error) message
void SongList::add(char *artist, char *title, float length, int likes)
{
   Node *curr = nullptr;
   Node *prev = nullptr;
   Node *insert = new Node(artist, title, length, likes);
   int pos = 0;

   if (!head) // insert first song in SongList
   {
      head = insert;
      cout << "\"" << title << "\" was successfully added to the song list." << endl;
   }
   else if (!duplicate(title)) // insert song alphabetically if no duplicates found
   {
      for (curr = head; curr; curr = curr->next)
      {
         pos = curr->data->songcmp(title);
         if (pos > 0)
         {
            break;
         }
         prev = curr;
      }

      if (!prev) // insert as new first element
      {
         insert->next = curr;
         head = insert;
      }
      else if (!curr) // insert as new last element
      {
         prev->next = insert;
      }
      else if (prev && curr) // insert in between first and last element
      {
         prev->next = insert;
         insert->next = curr;
      }
      cout << "\"" << title << "\" was successfully added to the song list." << endl;
   }
   else // do not add and release memory
   {
      cerr << "\"" << title << "\" has already been added." << endl
           << endl;
      delete insert;
   }
}

// name: copy overloading operator
// description: this function deletes and dealocates all existing data from the heap and then performs a deep copy of the contents of aList to *this.
// input: none
// output: none
const SongList &SongList::operator=(const SongList &aList)
{
   if (this == &aList)
      return *this;
   destroy(head);

   if (!aList.head)
   {
      head = nullptr;
      return *this;
   }

   Node *newNode = new Node(*(aList.head->data));
   head = newNode;

   Node *nextSrc = aList.head->next;
   Node *nextDes = head;
   while (nextSrc)
   {
      newNode = new Node(*(nextSrc->data));
      nextDes->next = newNode;
      nextSrc = nextSrc->next;
      nextDes = nextDes->next;
   }
   return *this;
}

// name: edit()
// description: this function edits the number of likes for a song.
// input: none
// output: fail/success message
bool SongList::edit(char *title, int update)
{
   for (Node *curr = head; curr; curr = curr->next)
   {
      if (curr->data->titlecmp(title) == true)
      {
         curr->data->setLikes(update);
         cout << "- Update was successfull -" << endl;
         return true;
      }
   }
   cerr << "- Update was not successfull -" << endl;
   return false;
}

// name: output overloading operator
// description: this function displays all songs
// input: none
// output: progress message
ostream &operator<<(ostream &out, const SongList &aSongList)
{
   SongList::Node *curr;
   out << endl
       << "Displaying the list ... " << endl
       << endl;
   for (curr = aSongList.head; curr; curr = curr->next)
   {
      out << *(curr->data) << endl;
   }

   return out;
}

// name: loadFromFile()
// description: this function opens and reads from a file, then after extracting information, it calls the add function to add a Song to the linked list.
void SongList::loadFromFile(const char *fileName)
{
   fstream file;
   const int MAX_CHAR = 100;
   char artist[MAX_CHAR + 1];
   char title[MAX_CHAR + 1];
   float length = 0.0;
   int likes = 0;

   cout << "Please wait. Loading from file..." << endl
        << endl;
   file.open(fileName);
   if (!file)
   {
      cerr << "ERROR: File did not open." << endl;
      exit(1);
   }
   file.get(artist, MAX_CHAR, ';');
   while (!file.eof())
   {
      file.ignore(1);
      file.get(title, MAX_CHAR, ';');
      file.ignore(1);
      file >> length;
      file.ignore(1);
      file >> likes;
      file.ignore(MAX_CHAR, '\n');
      add(artist, title, length, likes);
      file.get(artist, MAX_CHAR, ';');
   }
   file.close();
   cout << endl
        << "- Upload complete -" << endl
        << endl;
}

// name: display()
// description: this function displays all songs for an artist in order of popularity
// input: none
// output: message displaying the progress and number of songs found 
void SongList::display(char *artist) const
{
   Node *curr = nullptr;
   int size = 0, count = 0, pos = 0;

   cout << "Please wait. Fetching songs by \"" << artist << "\"..." << endl
        << endl;
   for (curr = head; curr; curr = curr->next)
   {
      if (curr->data->artistcmp(artist) == true)
      {
         size++;
      }
   }
   cout << "- " << size << " total songs found -" << endl
        << endl;
   Node **array = new Node *[size];
   for (curr = head; curr; curr = curr->next)
   {
      if (curr->data->artistcmp(artist) == true)
      {
         for (int i = 0; i < count; i++)
         {
            pos = i;
            if (array[i]->data->getLikes() < curr->data->getLikes())
            {
               break;
            }
         }
         for (int j = pos + 1; count > 0 && j > pos; j--)
         {
            array[j] = array[j - 1];
         }
         array[pos] = curr;
         count++;
      }
   }
   for (int i = 0; i < size; i++)
   {
      cout << i + 1 << ". ";
      array[i]->data->displayTitle();
      cout << ":\t" << array[i]->data->getLikes() << " Likes" << endl;
   }
   delete[] array;

   cout << endl
        << "- End of search -" << endl;
   array = nullptr;
}

// name: remove()
// description: this function removes all songs with fewer than X likes
// input: none
// output: message displaying the progress
void SongList::remove(int userParam)
{
   Node *curr = head;
   Node *target = nullptr;
   Node *prev = nullptr;

   while (curr)
   {
      if (curr->data->getLikes() < userParam)
      {
         target = curr;
         if (!prev)
         {
            curr = curr->next;
            head = curr;
            cout << "Removing \"";
            target->data->displayTitle();
            cout << "\"... " << endl;
            delete target;
            continue;
         }
         else
         {
            curr = prev;
            curr->next = target->next;
            cout << "Removing \"";
            target->data->displayTitle();
            cout << "\"... " << endl;
            delete target;
         }
      }
      prev = curr;
      curr = curr->next;
   }
   cout << endl << "- Removal complete -" << endl;
}

// name: duplicate()
// description: this function checks if there are duplicate song titles and returns a bool value
// input: none
// output: none
bool SongList::duplicate(char *songTitle) const
{
   for (Node *curr = head; curr; curr = curr->next) // find any duplicates
   {
      if (curr->data->titlecmp(songTitle) == true)
      {
         return true;
      }
   }
   return false;
}
