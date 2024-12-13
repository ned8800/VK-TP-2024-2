#include <vector>

typedef unsigned char byte;

class IInputStream {
public:
  IInputStream(const std::vector<byte> &input) : buffer(input), bytesCount(0){};

  bool Read(byte &oneByte);

private:
  const std::vector<byte> buffer;
  int bytesCount;
};

class IOutputStream {
public:
  IOutputStream() = default;

  void Write(byte oneByte);

  std::vector<byte> GetOutput() const { return buffer; }

private:
  std::vector<byte> buffer;
};

void copyStream(IInputStream& input, IOutputStream& output);

void Encode(IInputStream &original, IOutputStream &compressed);

void Decode(IInputStream &compressed, IOutputStream &original);
