#include <iostream>

struct WAVFile {
  uint32_t ChunkID;
  uint32_t ChunkSize;
  char Format[4];
  uint32_t Subchunk1ID;
  uint32_t Subchunk1Size;
  uint16_t AudioFormat;
  uint16_t NumChannels;
  uint32_t SampleRate;
  uint32_t ByteRate;
  uint16_t BlockAlign;
  uint16_t BitsPerSample;
  uint32_t Subchunk2ID;
  uint32_t Subchunk2Size;
  char* data = nullptr;


};
  std::istream& operator>>(std::istream& is, WAVFile& wav);
  std::ostream& operator<<(std::ostream& os, WAVFile& wav);
