#include <iostream>

namespace audio {

struct WAVFile {
  char ChunkID[4];
  uint32_t ChunkSize;
  char Format[4];
  char Subchunk1ID[4];
  uint32_t Subchunk1Size;
  uint16_t AudioFormat;
  uint16_t NumChannels;
  uint32_t SampleRate;
  uint32_t ByteRate;
  uint16_t BlockAlign;
  uint16_t BitsPerSample;
  char Subchunk2ID[4];
  uint32_t Subchunk2Size;
  char* data = nullptr;
  ~WAVFile();

};
  std::istream& operator>>(std::istream& is, WAVFile& wav);
  std::ostream& operator<<(std::ostream& os, WAVFile& wav);

} // namespace
