#include "Huffman.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <vector>


typedef unsigned long long EncodedT;
const int ENCODED_BITS_SIZE = sizeof(EncodedT) * 8;


typedef unsigned char byte;



class InBitStream {
private:
	std::vector<unsigned char> buffer;
	int bitsCount = 0;
	int tailBitsQuantity = 0;

public:
	bool ReadBit(byte &bit);
	bool ReadByte(byte &oneByte);

	InBitStream(const std::vector<byte> &input, int _tailBitsQuantity = 0)
	 : buffer(input), bitsCount(0), tailBitsQuantity(_tailBitsQuantity) {};
	~InBitStream() = default;

	std::vector<byte> GetResult() const {
		return buffer;
	}

	int GetBitsCount() const {
		return bitsCount;
	}
};

bool InBitStream::ReadBit(byte &bit) {
	if (bitsCount + 1 > 8 * buffer.size() - tailBitsQuantity) {
    	return false;
  	}
	int offset = bitsCount % 8;
	int byteOffset = (bitsCount) / 8;

	byte mask = 1 << (7 - offset);
    byte target = 0;
    // Установка соответствующего бита в target
    target = ((buffer[byteOffset] & mask) >> (7 - offset));

	bit = target;
	++bitsCount;
	return true;
}



bool InBitStream::ReadByte(byte &oneByte) {
	if (bitsCount + 8 > 8 * buffer.size() - tailBitsQuantity) {
    	return false;
  	}

    if (bitsCount % 8 == 0) {
        int byteOffset = bitsCount / 8;
        oneByte = buffer[byteOffset];
        bitsCount += 8;
    } else {
        int offset = bitsCount % 8;
		int byteOffset = (bitsCount) / 8;
        byte bufferByte = 0;
        // write в него всё, что осталось в 1 байте
        bufferByte |= buffer[(byteOffset)] << offset;

        byteOffset += 1;
        // write в него всё, что откусили от 2 байта
        bufferByte |= buffer[(byteOffset)] >> (8 - offset);

		oneByte = bufferByte;
        bitsCount += 8;
    }

	return true;
}


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////


class OutBitStream {
private:
	std::vector<byte> buffer;
	int bitsCount = 0;

public:
	void WriteBit(byte bit);
	void WriteByte(byte byte);

	OutBitStream() = default;


	std::vector<byte> GetOutput() const { return buffer; }

	int GetBitsCount() {
		return bitsCount;
	};
};

void OutBitStream::WriteBit(byte bit) {
	if (bitsCount + 1 > 8 * buffer.size()) {
		buffer.push_back(0);
	}

	if (1 & bit) {
		int offset = bitsCount % 8;
		buffer[buffer.size() - 1] |= (1 << (7-offset));
	}

	++bitsCount;
}



void OutBitStream::WriteByte(byte byte) {
	if (bitsCount % 8 == 0) {
		buffer.push_back(byte);
	} else {
		// пишем часть в существующий байт и добавляем остальное в новый
		int offset = bitsCount % 8;
		buffer[buffer.size() - 1] |= (byte >> (offset));
		buffer.push_back( byte << (8 - offset));
	}
	bitsCount += 8;
}



/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

struct  Node {
	Node *left = nullptr;
	Node *right = nullptr;
	byte Byte = 0;
	int Count = 0;

	Node(byte Byte, int freq, Node *left, Node *right)
      : Byte(Byte), Count(freq), left(left), right(right) {};
};


struct TableEntry {
  byte oneByte = 0;
  EncodedT encoded = 0;
  int len = 0;

  TableEntry() = default;

  TableEntry(byte byte_, EncodedT encoded_, int len_)
      : oneByte(byte_), encoded(encoded_), len(len_) {}
};

void DeleteTree(Node *node) {
  if (node == nullptr) {
    return;
  }
  DeleteTree(node->left);
  DeleteTree(node->right);
  delete node;
}

std::vector<Node *> GetTreeNodes(const std::vector<byte> &bytes) {
  byte max = bytes[0];
  for (int i = 0; i < bytes.size(); ++i) {
    max = std::max(max, bytes[i]);
  }

  int *cnt = new int[max + 1];
  memset(cnt, 0, (max + 1) * sizeof(int));

  for (int i = 0; i < bytes.size(); ++i) {
    ++cnt[bytes[i]];
  }

  bool *added = new bool[1 << (sizeof(byte) * 8)];
  memset(added, false, (1 << (sizeof(byte) * 8)) * sizeof(bool));

  std::vector<Node *> nodes;

  for (int i = 0; i < bytes.size(); ++i) {
    if (!added[bytes[i]] && cnt[bytes[i]] > 0) {
      nodes.push_back(new Node(bytes[i], cnt[bytes[i]], nullptr, nullptr));
      added[bytes[i]] = true;
    }
  }

  delete[] cnt;
  delete[] added;

  return nodes;
}

template <typename T, typename CmpT> class DynHeap : private std::vector<T> {
public:
  DynHeap(const std::vector<T> &dyn_array, CmpT cmp) : cmp_(cmp) {
    this->build(dyn_array);
  }

  void insert(const T &element) {
    this->push_back(element);
    
    size_t idx = this->size() - 1;
    
    while (idx > 0 && !cmp_((*this)[idx / 2], (*this)[idx])) {
      std::swap((*this)[idx / 2], (*this)[idx]);
      idx /= 2;
    }
  }

    T extractTop() {
    assert(this->isEmpty() == false);
    T prev_top = (*this)[0];
    
    std::swap((*this)[0], (*this)[this->size() - 1]);
    this->pop_back();
    
    this->heapify(0);
    
    return prev_top;
  }

  bool isEmpty() const { return this->empty(); }

private:
  CmpT cmp_;

  void build(const std::vector<T> &dyn_array) {
    // скопировать dyn_array в себя
    *dynamic_cast<std::vector<T> *>(this) = dyn_array;
    for (size_t i = (this->size() - 1) / 2; i >= 1; --i) {
      this->heapify(i);
    }
  }

  void heapify(size_t idx) {
    while (true) {
      size_t len = this->size();
      // левый и правый ребенок
      size_t left = idx * 2 + 1;
      size_t right = idx * 2 + 2;
      
      size_t toBeTop = idx;
      
      if (left < len && cmp_((*this)[left], (*this)[idx])) {
        toBeTop = left;
      }
      if (right < len && cmp_((*this)[right], (*this)[toBeTop])) {
        toBeTop = right;
      }

      if (toBeTop == idx) {
        return;
      }

      std::swap((*this)[idx], (*this)[toBeTop]);
      idx = toBeTop;
    }
  }
};

struct TreeNodeCmp {
  bool operator()(const Node *a, const Node *b) const {
    return a->Count < b->Count;
  }
};

void WriteTreeRepr(const Node *node, OutBitStream &out, int &bits) {
  if (node == nullptr) {
    return;
  }
  if (node->left == nullptr && node->right == nullptr) {
    out.WriteBit(1);
    out.WriteByte(node->Byte);
    bits += 9;
    return;
  }
  WriteTreeRepr(node->left, out, bits);
  WriteTreeRepr(node->right, out, bits);
  out.WriteBit(0);
  ++bits;
}

Node *ReadTreeRepr(InBitStream &in) {
  std::vector<Node *> nodes;
  byte byte;

  while (true) {
    in.ReadBit(byte);
    if (byte == 1) {
      in.ReadByte(byte);
      nodes.push_back(new Node(byte, 0, nullptr, nullptr));
    } else {
      if (nodes.size() == 1) {
        return nodes[0];
      }
      Node *right = nodes.back();
      nodes.pop_back();
      Node *left = nodes.back();
      nodes.pop_back();
      nodes.push_back(new Node(0, 0, left, right));
    }
  }
}

void FillEncodeTable(const Node *node,
                     std::vector<TableEntry> &encodeTable,
                     EncodedT encoded = 0, int enc_len = 0) {
  if (node == nullptr) {
    return;
  }
  if (node->left == nullptr && node->right == nullptr) {
    TableEntry entry(node->Byte, encoded, std::max(1, enc_len));
    encodeTable.push_back(entry);
    return;
  }
  FillEncodeTable(node->left, encodeTable, encoded, enc_len + 1);
  FillEncodeTable(node->right, encodeTable,
                  encoded | (1ull << (ENCODED_BITS_SIZE - 1 - enc_len)),
                  enc_len + 1);
}

void FillDecodeTable(const Node *node,
                     std::vector<TableEntry> &decodeTable,
                     EncodedT encoded = 0, int enc_len = 0) {
  if (node == nullptr) {
    return;
  }
  if (node->left == nullptr && node->right == nullptr) {
    TableEntry entry(node->Byte, encoded, std::max(1, enc_len));
    decodeTable.push_back(entry);
    return;
  }
  FillDecodeTable(node->left, decodeTable, encoded, enc_len + 1);
  FillDecodeTable(node->right, decodeTable,
                  encoded | (1ull << (ENCODED_BITS_SIZE - 1 - enc_len)),
                  enc_len + 1);
}

const TableEntry &EncodeByte(const byte &oneByte,
                             const std::vector<TableEntry> &encodeTable) {
  for (int i = 0; i < encodeTable.size() - 1; ++i) {
    if (encodeTable[i].oneByte == oneByte) {
      return encodeTable[i];
    }
  }
  return encodeTable[encodeTable.size() - 1];
}


const TableEntry &DecodeByte(const EncodedT &encoded,
                             const std::vector<TableEntry> &decodeTable) {
  for (int i = 0; i < decodeTable.size() - 1; ++i) {
    if (decodeTable[i].encoded == encoded) {
      return decodeTable[i];
    }
  }
  return decodeTable[decodeTable.size() - 1];
}

Node *BuildEncodeTree(const std::vector<byte> &bytes) {
  std::vector<Node *> nodes = GetTreeNodes(bytes);

  DynHeap<Node *, TreeNodeCmp> treeHeap(nodes, TreeNodeCmp{});

  Node *tree;

  while (!treeHeap.isEmpty()) {
    Node *left = treeHeap.extractTop();
    if (treeHeap.isEmpty()) {
      tree = left;
      break;
    }
    Node *right = treeHeap.extractTop();
    tree = new Node(0, left->Count + right->Count, left, right);
    treeHeap.insert(tree);
  }

  return tree;
}

bool DecodeByteStream(InBitStream &in,
                      const std::vector<TableEntry> &decodeTable,
                      byte &decoded) {
  EncodedT encoded = 0;
  int len = 0;

  while (len == 0 || DecodeByte(encoded, decodeTable).len != len) {
    byte bit;
    if (len == ENCODED_BITS_SIZE || !in.ReadBit(bit)) {
      return false;
    }
    encoded |= static_cast<EncodedT>(bit) << (ENCODED_BITS_SIZE - 1 - len);
    ++len;
  }

  decoded = DecodeByte(encoded, decodeTable).oneByte;
  return true;
}

void Encode(IInputStream &original, IOutputStream &compressed) {
  byte oneByte;
  std::vector<byte> bytes;
  while (original.Read(oneByte)) {
    bytes.push_back(oneByte);
  }

  if (bytes.empty()) {
    return;
  }

  Node *tree = BuildEncodeTree(bytes);

  OutBitStream outBits;

  int bits = 1; // учитывая хвостовой бит 0
  WriteTreeRepr(tree, outBits, bits);
  
  outBits.WriteBit(0);
  
  std::vector<TableEntry> encodeTable;
  FillEncodeTable(tree, encodeTable);
  encodeTable.push_back(TableEntry(0, 0, -1)); 

  DeleteTree(tree);

  for (int i = 0; i < bytes.size(); ++i) {
    TableEntry enc = EncodeByte(bytes[i], encodeTable);
    for (int j = 0; j < enc.len; ++j) {
      outBits.WriteBit(enc.encoded >> (ENCODED_BITS_SIZE - 1 - j));
      ++bits;
    }
  }
  
  int tailBits = (8 - (bits % 8)) % 8;
  compressed.Write(tailBits);
  
  std::vector<byte> outBytesVector = outBits.GetOutput();
  for (int i = 0; i < outBytesVector.size(); ++i) {
    compressed.Write(outBytesVector[i]);
  }
}

void Decode(IInputStream &compressed, IOutputStream &original) {
  byte oneByte;
  std::vector<byte> bytes;
  while (compressed.Read(oneByte)) {
    bytes.push_back(oneByte);
  }

  if (bytes.empty()) {
    return;
  }
  
  int tailBits = bytes[0];

  InBitStream incomingBits(bytes, tailBits);
  
  incomingBits.ReadByte(oneByte);

  Node *tree = ReadTreeRepr(incomingBits);

  std::vector<TableEntry> decodeTable;
  FillDecodeTable(tree, decodeTable);
  decodeTable.push_back(TableEntry(0, 0, -1));

  DeleteTree(tree);

  while (true) {
    if (!DecodeByteStream(incomingBits, decodeTable, oneByte)) {
      return;
    }
    original.Write(oneByte);
  }
}
