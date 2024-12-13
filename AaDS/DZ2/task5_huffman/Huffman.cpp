#include "Huffman.h"
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

bool IInputStream::Read(byte &byte) {
  if (bytesCount + 1 > buffer.size()) {
    return false;
  }

  byte = buffer[bytesCount];
  ++bytesCount;
  return true;
}

void IOutputStream::Write(byte byte) { buffer.push_back(byte); }

void Test() {
  for (int t = 0; t < 1000; ++t) {
    int size = 1 + 1000000;
    // int size = 1 + std::rand();
    std::vector<byte> bytes(size, 0);
    for (int i = 0; i < size; ++i) {
      bytes[i] = static_cast<byte>(std::rand() % 5);
    }

    // std::vector<Byte> bytes = {'a', 'b'};
    // for (int i = 0; i < 24; ++i) {
    //   for (int j = 0; j < 3 * std::pow(2, i); ++j) {
    //     bytes.push_back('c' + i);
    //   }
    // }

    IInputStream original_in(bytes);
    IOutputStream compressed_out;
    Encode(original_in, compressed_out);

    IInputStream compressed_in(compressed_out.GetOutput());
    IOutputStream original_out;
    Decode(compressed_in, original_out);

    assert(bytes == original_out.GetOutput());

    std::cout << (static_cast<float>(compressed_out.GetOutput().size()) /
                  static_cast<float>(bytes.size()))
              << std::endl;
  }
}

int main() {
  Test();
  std::cout << "OK" << std::endl;
  return 0;
}
