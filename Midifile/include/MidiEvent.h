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
// Creation Date: Sat Feb 14 21:47:39 PST 2015
// Last Modified: Sat Feb 14 21:54:52 PST 2015
// Filename:      midifile/include/MidiEvent.h
// Website:       http://midifile.sapp.org
// Syntax:        C++11
// vim:           ts=3 expandtab
//
// Description:   A class which stores a MidiMessage and a timestamp
//                for the MidiFile class.
//

#ifndef _MIDIEVENT_H_INCLUDED
#define _MIDIEVENT_H_INCLUDED

#include "MidiMessage.h"
#include <vector>

using namespace std;

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned long  ulong;

class MidiEvent : public MidiMessage {
   public:
                 MidiEvent     (void);
                 MidiEvent     (int command);
                 MidiEvent     (int command, int param1);
                 MidiEvent     (int command, int param1, int param2);
                 MidiEvent     (int aTime, int aTrack, vector<uchar>& message);
                 MidiEvent     (const MidiMessage& message);
                 MidiEvent     (const MidiEvent& mfevent);

                ~MidiEvent     ();

      MidiEvent& operator=     (MidiEvent& mfevent);
      MidiEvent& operator=     (MidiMessage& message);
      MidiEvent& operator=     (vector<uchar>& bytes);
      MidiEvent& operator=     (vector<char>& bytes);
      MidiEvent& operator=     (vector<int>& bytes);
      void       clearVariables(void);

      // functions related to event linking (note-ons to note-offs).
      void       unlinkEvent   (void);
      void       unlinkEvents  (void);
      void       linkEvent     (MidiEvent* mev);
      void       linkEvents    (MidiEvent* mev);
      void       linkEvent     (MidiEvent& mev);
      void       linkEvents    (MidiEvent& mev);
      int        isLinked      (void);
      MidiEvent* getLinkedEvent(void);
      int        getTickDuration(void);
      double     getDurationInSeconds(void);

      int       tick;
      int       track;
      double    seconds;

   private:
      MidiEvent* eventlink;      // used to match note-ons and note-offs

};


#endif /* _MIDIEVENT_H_INCLUDED */



