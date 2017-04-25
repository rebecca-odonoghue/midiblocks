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
// Filename:      midifile/include/MidiEventList.h
// Website:       http://midifile.sapp.org
// Syntax:        C++11
// vim:           ts=3 expandtab
//
// Description:   A class which stores a MidiEvents for a MidiFile track.
//

#ifndef _MIDIEVENTLIST_H_INCLUDED
#define _MIDIEVENTLIST_H_INCLUDED

#include "MidiEvent.h"
#include <vector>

using namespace std;

class MidiEventList {
   public:
                  MidiEventList    (void);

                 ~MidiEventList    ();

      MidiEvent&  operator[]       (int index);
      MidiEvent&  back             (void);
      MidiEvent&  last             (void);
      MidiEvent&  getEvent         (int index);
      void        clear            (void);
      void        reserve          (int rsize);
      int         getSize          (void);
      int         size             (void);
      int         linkNotePairs    (void);
      void        clearLinks       (void);
      MidiEvent** data             (void);

      int         push             (MidiEvent& event);
      int         push_back        (MidiEvent& event);
      int         append           (MidiEvent& event);

      // careful when using these, intended for internal use in MidiFile class:
      void        detach              (void);
      int         push_back_no_copy   (MidiEvent* event);

   private:
      vector<MidiEvent*>     list;

};


#endif /* _MIDIEVENTLIST_H_INCLUDED */



