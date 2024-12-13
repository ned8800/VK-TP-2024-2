void Encode(IInputStream &original, IOutputStream &compressed);

void Decode(IInputStream &compressed, IOutputStream &original);

class InBitStream {
private:
	std::vector<unsigned char> buffer;
	int bitsCount = 0;
	int tailBitsQuantity = 0;

public:
	bool ReadBit(byte &bit);
	bool ReadByte(byte &oneByte);

	InBitStream(const std::vector<byte> &input, int _tailBitsQuantity = 0) : 
		buffer(input), bitsCount(0), tailBitsQuantity(_tailBitsQuantity) {};
	~InBitStream() = default;

	std::vector<byte> GetResult() const {
		return buffer;
	}

	int GetBitsCount() const {
		return bitsCount;
	}
};

class OutBitStream {
private:
	std::vector<unsigned char> buffer;
	int bitsCount = 0;

public:
	void WriteBit(unsigned char bit);
	void WriteByte(unsigned char byte);

	OutBitStream() = default;
	~OutBitStream() = default;

	std::vector<byte> GetResult() const {
		return buffer;
	}

	int GetBitsCount() const {
		return bitsCount;
	}
};