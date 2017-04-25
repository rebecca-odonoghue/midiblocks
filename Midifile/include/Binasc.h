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
// Creation Date: Mon Feb 16 12:26:32 PST 2015 Adapted from binasc program.
// Last Modified: Wed Feb 18 14:48:21 PST 2015
// Filename:      midifile/include/Binasc.cpp
// Syntax:        C++11
// vim:           ts=3 expandtab
//
// description:   Interface to convert bytes between binary and ASCII forms.
//

#ifndef _BINASC_H_INCLUDED
#define _BINASC_H_INCLUDED

#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

class Binasc {
   public:
               Binasc         (void);
              ~Binasc         ();

      // functions for setting options:
      int      setLineLength  (int length);
      int      getLineLength  (void);
      int      setLineBytes   (int length);
      int      getLineBytes   (void);
      void     setComments    (int state);
      void     setCommentsOn  (void);
      void     setCommentsOff (void);
      int      getComments    (void);
      void     setBytes       (int state);
      void     setBytesOn     (void);
      void     setBytesOff    (void);
      int      getBytes       (void);
      void     setMidi        (int state);
      void     setMidiOn      (void);
      void     setMidiOff     (void);
      int      getMidi        (void);

      // functions for converting into a binary file:
      int      writeToBinary  (const string& outfile, const string& infile);
      int      writeToBinary  (const string& outfile, istream& input);
      int      writeToBinary  (ostream& out, const string& infile);
      int      writeToBinary  (ostream& out, istream& input);

      // functions for converting into an ASCII file with hex bytes:
      int      readFromBinary (const string& outfile, const string& infile);
      int      readFromBinary (const string& outfile, istream& input);
      int      readFromBinary (ostream& out, const string& infile);
      int      readFromBinary (ostream& out, istream& input);

      // static functions for writing ordered bytes:
      static ostream& writeLittleEndianUShort (ostream& out, ushort value);
      static ostream& writeBigEndianUShort    (ostream& out, ushort value);
      static ostream& writeLittleEndianShort  (ostream& out, short  value);
      static ostream& writeBigEndianShort     (ostream& out, short  value);
      static ostream& writeLittleEndianULong  (ostream& out, ulong  value);
      static ostream& writeBigEndianULong     (ostream& out, ulong  value);
      static ostream& writeLittleEndianLong   (ostream& out, long   value);
      static ostream& writeBigEndianLong      (ostream& out, long   value);
      static ostream& writeLittleEndianFloat  (ostream& out, float  value);
      static ostream& writeBigEndianFloat     (ostream& out, float  value);
      static ostream& writeLittleEndianDouble (ostream& out, double value);
      static ostream& writeBigEndianDouble    (ostream& out, double value);

   protected:
      // helper functions for reading ASCII content to conver to binary:
      int      processLine        (ostream& out, char* word, int lineNum);
      int      processAsciiWord   (ostream& out, const char* word, int lineNum);
      int      processBinaryWord  (ostream& out, const char* word, int lineNum);
      int      processDecimalWord (ostream& out, const char* word, int lineNum);
      int      processHexWord     (ostream& out, const char* word, int lineNum);
      int      processVlvWord     (ostream& out, const char* word, int lineNum);
      int      processMidiPitchBendWord(ostream& out, const char* word, 
                                   int lineNum);

      // helper functions for reading binary content to convert to ASCII:
      int      outputStyleAscii   (ostream& out, istream& input);
      int      outputStyleBinary  (ostream& out, istream& input);
      int      outputStyleBoth    (ostream& out, istream& input);
      int      outputStyleMidi    (ostream& out, istream& input);

      // MIDI parsing helper functions:
      int      readMidiEvent  (ostream& out, istream& infile, int& trackbytes, 
                               int& command);
      int      getVLV         (istream& infile, int& trackbytes);

   private:
      int bytesQ;        // option for printing hex bytes in ASCII output.
      int commentsQ;     // option for printing comments in ASCII output.
      int midiQ;         // output ASCII data as parsed MIDI file.
      int maxLineLength; // number of character in ASCII output on a line.
      int maxLineBytes;  // number of hex bytes in ASCII output on a line.
};


#endif /* _BINASC_H_INCLUDED */



