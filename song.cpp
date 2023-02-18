//*****************************************************************************
// Name: song.cpp
// Descrtiption: This is the executable file for the Song class object.
//*****************************************************************************
#include "song.h"

// name: Song()
// description: constructor
// input: none
// output: none
Song::Song() : artist(nullptr), title(nullptr), length(0.0), likes(0) {}

// name: setData()
// description: this function sets all of the ADT's private members
// input: none
// output: none
Song::Song(char *artist, char *title, float length, int likes)
{
   this->artist = new char[strlen(artist) + 1];
   strcpy(this->artist, artist);
   this->title = new char[strlen(title) + 1];
   strcpy(this->title, title);
   this->length = length;
   this->likes = likes;
}

// name: ~Song()
// description: destructor
// input: none
// output: none
Song::~Song()
{
   if (this->artist)
   {
      delete[] this->artist;
      this->artist = nullptr;
   }
   if (this->title)
   {
      delete[] this->title;
      this->title = nullptr;
   }
   length = 0.0;
   likes = 0;
}

// name: copy overloading operator
// description: this function deletes and dealocates all existing data from the heap and the performs a deep copy of aSong type to *this.
// input: none
// output: none
const Song &Song::operator=(const Song &aSong)
{
   if (this == &aSong)
   {
      return *this;
   }
   setArtist(aSong.artist);
   setTitle(aSong.title);
   setLength(aSong.length);
   setLikes(aSong.likes);
   return *this;
}

// name: artistcmp()
// description: this function compares the artist name with the source and returns a bool value
// input: none
// output: none
bool Song::artistcmp(char *source) const
{
   int result = strcmp(source, artist);
   bool match = false;
   if (result == 0)
   {
      match = true;
   }
   return match;
}

// name: titlecmp()
// description: this function compares the title name with the source and returns a bool value
// input: none
// output: none
bool Song::titlecmp(char *source) const
{
   int result = strcmp(source, title);
   bool match = false;
   if (result == 0)
   {
      match = true;
   }
   return match;
}

// name: songcmp()
// descriptipn: this function returns an integer less than zero if the first parameter is less than the second parameter or an integer greater than zero if the first parameter is greater than the second parameter
// input: none
// output: none
int Song::songcmp(char *song) const
{
   int result = strcmp(this->title, song);
   return result;
}

// name: setArtist()
// description: this function sets the private member artist with param song artist name
// input: none
// output: none
void Song::setArtist(char *source)
{
   if (this->artist)
   {
      delete[] this->artist;
   }
   this->artist = new char[strlen(source) + 1];
   strcpy(this->artist, source);
}

// name: setTitle()
// description: this function sets the private member title with param song name
// input: none
// output: none
void Song::setTitle(char *source)
{
   if (this->title)
   {
      delete[] this->title;
   }
   this->title = new char[strlen(source) + 1];
   strcpy(this->title, source);
}

// displayTitle()
// description: this function displays the song title
// input: none
// output: char *title
void Song::displayTitle() const
{
   cout << this->title;
}

// name: getTitleLen()
// description: this function returns the character length of the song title
// input: none
// output: none
int Song::getTitleLen() const
{
   return strlen(title);
}

// name: setLength()
// description: this function sets the private member length
// input: none
// output: none
void Song::setLength(float source)
{
   this->length = source;
}

// name: getLength()
// description: this function returns the song length
// input: none
// output: none
float Song::getLength() const
{
   return length;
}

// name: setLikes()
// description: this function updates the number of likes
// input: none
// output: none
void Song::setLikes(int likes)
{
   this->likes = likes;
}

// name: getLikes()
// description: this function returns the number of likes
// input: none
// output: none
int Song::getLikes() const
{
   return likes;
}

// name: ouput overloading operator
// discription: this function outputs all the data stored in the Song ADT
// input: none
// output: char *artist, char*title, float length, int likes
ostream &operator<<(ostream &out, const Song &aSong)
{
   out << "Artist Name: " << aSong.artist << endl
       << "Title: " << aSong.title << endl
       << "Length: " << aSong.length << endl
       << "Number of likes: " << aSong.likes << endl;
   return out;
}