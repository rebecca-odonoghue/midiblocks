//Copyright (c) 1999-2015, Craig Stuart Sapp
//All rights reserved.

//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:

//1. Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//2. Redistributions in binary form must reproduce the above copyright notice,
//   and the following disclaimer in the documentation and/or other materials
//   provided with the distribution.

//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
//ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Feb 14 21:55:38 PST 2015
// Last Modified: Sat Feb 14 21:55:40 PST 2015
// Filename:      midifile/src-library/MidiEventList.cpp
// Website:       http://midifile.sapp.org
// Syntax:        C++11
// vim:           ts=3 expandtab
//
// Description:   A class which stores a MidiEvents for a MidiFile track.
//


#include "MidiEventList.h"

#include <vector>
#include <iostream>

using namespace std;


//////////////////////////////
//
// MidiEventList::MidiEventList -- Constructor.
//

MidiEventList::MidiEventList(void) {
   reserve(1000);
}



//////////////////////////////
//
// MidiEventList::~MidiEventList -- Deconstructor.  Deallocate all stored
//   data.
//

MidiEventList::~MidiEventList() {
   clear();
}



//////////////////////////////
//
// MidiEventList::operator[] --
//

MidiEvent&  MidiEventList::operator[](int index) {
   return *list[index];
}



//////////////////////////////
//
// MidiEventList::back -- Return the last element in the list.
//

MidiEvent& MidiEventList::back(void) {
   return *list.back();
}

// Alias for back:

MidiEvent& MidiEventList::last(void) {
   return back();
}



//////////////////////////////
//
// MidiEventList::getEvent -- The same thing as operator[], for 
//      internal use when operator[] would look more messy.
//   

MidiEvent& MidiEventList::getEvent(int index) {
     return *list[index];
}



//////////////////////////////
//
// MidiEventList::clear -- De-allocate any MidiEvents present in the list
//    and set the size of the list to 0.
//

void MidiEventList::clear(void) {
   for (int i=0; i<list.size(); i++) {
      if (list[i] != NULL) {
         delete list[i];
         list[i] = NULL;
      }
   }
   list.resize(0);
}



//////////////////////////////
//
// MidiEventList::data --
//

MidiEvent** MidiEventList::data(void) {
   return list.data();
}



//////////////////////////////
//
// MidiEventList::reserve --  Pre-allocate space in the list for storing
//     elements.
//

void MidiEventList::reserve(int rsize) {
   if (rsize > list.size()) {
      list.reserve(rsize);
   }
}


//////////////////////////////
//
// MidiEventList::getSize --
//

int MidiEventList::getSize(void) {
   return list.size();
}


int MidiEventList::size(void) {
   return getSize();
}



//////////////////////////////
//
// MidiEventList::append -- add a MidiEvent at the end of the list.  Returns
//     the index of the appended event.
//

int MidiEventList::append(MidiEvent& event) { 
   MidiEvent* ptr = new MidiEvent(event);
   list.push_back(ptr);
   return list.size()-1;
}


int MidiEventList::push(MidiEvent& event) { 
   return append(event);
}


int MidiEventList::push_back(MidiEvent& event) { 
   return append(event);
}


//////////////////////////////
//
// MidiEventList::linkNotePairs -- Match note-ones and note-offs together
//   There are two models that can be done if two notes are overlapping
//   on the same pitch: the first note-off affects the last note-on,
//   or the first note-off affects the first note-on.  Currently  the 
//   first note-off affects the last note-on, but both methods could
//   be implemented with user selectability.  The current state of the
//   track is assumed to be in time-sorted order.  Returns the number
//   of linked notes (note-on/note-off pairs).
//

int MidiEventList::linkNotePairs(void) {
   // dimension 1: MIDI channel (0-15)
   // dimension 2: MIDI key     (0-127)  (but 0 not used for note-ons)
   // dimension 3: List of active note-ons or note-offs.
   vector<vector<vector<MidiEvent*> > > noteons;
   noteons.resize(16);
   int i;
   for (i=0; i<noteons.size(); i++) {
      noteons[i].resize(128);
   }

   // Now iterate through the MidiEventList keeping track of note
   // states and linking notes as needed.
   int channel;
   int key;
   int counter = 0;
   MidiEvent* mev;
   MidiEvent* noteon;
   for (i=0; i<getSize(); i++) {
      mev = &getEvent(i);
      mev->unlinkEvent();
      if (mev->isNoteOn()) {
         // store the note-on to pair later with a note-off message.
         key = mev->getKeyNumber();
         channel = mev->getChannel();
         noteons[channel][key].push_back(mev);
      } else if (mev->isNoteOff()) {
         key = mev->getKeyNumber();
         channel = mev->getChannel();
         if (noteons[channel][key].size() > 0) {
            noteon = noteons[channel][key].back();
            noteons[channel][key].pop_back();
            noteon->linkEvent(mev);
            counter++;
         }
      }
   }
   return counter;
}



//////////////////////////////
//
// MidiEventList::clearLinks -- remove all note-on/note-off links.
//

void MidiEventList::clearLinks(void) {
   for (int i=0; i<getSize(); i++) {
      getEvent(i).unlinkEvent();
   }
}


///////////////////////////////////////////////////////////////////////////
//
// protected functions --
//


//////////////////////////////
//
// MidiEventList::detach -- De-allocate any MidiEvents present in the list
//    and set the size of the list to 0.
//


void MidiEventList::detach(void) {
   list.resize(0);
}



//////////////////////////////
//
// MidiEventList::push_back_no_copy -- add a MidiEvent at the end of 
//     the list.  The event is not copied, but memory from the 
//     remote location is used.  Returns the index of the appended event.
//

int MidiEventList::push_back_no_copy(MidiEvent* event) { 
   list.push_back(event);
   return list.size()-1;
}




