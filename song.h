//*****************************************************************************
// Name: song.h
// Descrtiption: This is the header file for the Song class object.
//*****************************************************************************
#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

class Song
{
public:
   Song();
   Song(char *, char *, float, int);
   ~Song();
   const Song &operator=(const Song &aSong);
   friend ostream &operator<<(ostream &out, const Song &aSong);
   bool artistcmp(char *) const;
   bool titlecmp(char *) const;
   int songcmp(char *) const;
   void setArtist(char *);
   void setTitle(char *);
   void displayTitle() const;
   int getTitleLen() const;
   void setLength(float);
   float getLength() const;
   void setLikes(int);
   int getLikes() const;
private:
   char *artist;
   char *title;
   float length;
   int likes;
};

#endif