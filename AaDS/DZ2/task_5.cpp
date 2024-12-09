#include <iostream>
#include <fstream>

// #include "Huffman.h"


typedef char byte;

// interface IInputStream {
// // Возвращает false, если поток закончился
// virtual bool Read(byte& value) = 0;
// };

// interface IOutputStream {
// virtual void Write(byte value) = 0;
// };


static void copyStream(IInputStream& input, IOutputStream& output)
{
  byte value;
  while (input.Read(value)) 
  { 
    output.Write(value); 
  }
}

void Encode(IInputStream& original, IOutputStream& compressed) 
{
  copyStream(original, compressed); 
}

void Decode(IInputStream& compressed, IOutputStream& original) 
{ 
  copyStream(compressed, original); 
}
