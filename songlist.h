//*****************************************************************************
// Name: songlist.h
// Descrtiption: This is the header file for the SongList class object.
//*****************************************************************************
#ifndef SONGLIST_H
#define SONGLIST_H
#include "song.h"
using namespace std;

class SongList
{
public:
   SongList();
   ~SongList();
   void add(char *, char *, float, int);
   bool edit(char *, int);
   const SongList &operator=(const SongList &aList);
   friend ostream &operator<<(ostream &out, const SongList &aSongList);
   void loadFromFile(const char * fileName);
   void display(char *) const;
   void remove(int);
   bool duplicate(char *) const;

private:
   struct Node
   {
      Node()
      {
         data = nullptr;
         next = nullptr;
      }
      Node(const Song &aSong)
      {
         data = new Song(aSong);
         next = nullptr;
      }
      Node(char *artist, char *title, float length, int likes)
      {
         data = new Song(artist, title, length, likes);
         next = nullptr;
      }
      ~Node()
      {
         if (data)
         {
            delete data;
            data = nullptr;
            next = nullptr;
         }
      }
      Song *data;
      Node *next;
   };
   Node *head;
   void destroy(Node *);
};
#endif