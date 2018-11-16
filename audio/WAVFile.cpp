#include "WAVFile.hpp"
#include <iostream>
#include <fstream>
#include <pulse/simple.h>
#include <pulse/error.h>

namespace audio {

WAVFile::~WAVFile() {
  delete[] data;
}

std::istream& operator>>(std::istream& is, WAVFile& wav) {
  is.read(reinterpret_cast<char*>(&wav.ChunkID), sizeof(wav.ChunkID));
  is.read(reinterpret_cast<char*>(&wav.ChunkSize), sizeof(wav.ChunkSize));
  is.read(reinterpret_cast<char*>(&wav.Format), sizeof(wav.Format));
  is.read(reinterpret_cast<char*>(&wav.Subchunk1ID), sizeof(wav.Subchunk1ID));
  is.read(reinterpret_cast<char*>(&wav.Subchunk1Size), sizeof(wav.Subchunk1Size));
  is.read(reinterpret_cast<char*>(&wav.AudioFormat), sizeof(wav.AudioFormat));
  is.read(reinterpret_cast<char*>(&wav.NumChannels), sizeof(wav.NumChannels));
  is.read(reinterpret_cast<char*>(&wav.SampleRate), sizeof(wav.SampleRate));
  is.read(reinterpret_cast<char*>(&wav.ByteRate), sizeof(wav.ByteRate));
  is.read(reinterpret_cast<char*>(&wav.BlockAlign), sizeof(wav.BlockAlign));
  is.read(reinterpret_cast<char*>(&wav.BitsPerSample), sizeof(wav.BitsPerSample));
  is.read(reinterpret_cast<char*>(&wav.Subchunk2ID), sizeof(wav.Subchunk2ID));
  is.read(reinterpret_cast<char*>(&wav.Subchunk2Size), sizeof(wav.Subchunk2Size));
  wav.data = new char[wav.Subchunk2Size];
  is.read(wav.data, wav.Subchunk2Size);
  return is;
}

std::ostream& operator<<(std::ostream& os, WAVFile& wav) {
  os << 
    "ChunkID: \t" << wav.ChunkID[0] << wav.ChunkID[1] << wav.ChunkID[2] << wav.ChunkID[3] << std::endl <<
    "ChunkSize: \t" << wav.ChunkSize << std::endl <<
    "Format: \t" << wav.Format[0] << wav.Format[1] << wav.Format[2] << wav.Format[3] << std::endl <<
    "Subchunk1ID: \t" << wav.Subchunk1ID[0] << wav.Subchunk1ID[1] << wav.Subchunk1ID[2] << wav.Subchunk1ID[3] << std::endl <<
    "Subchunk1Size: \t" << wav.Subchunk1Size << std::endl <<
    "AudioFormat: \t" << wav.AudioFormat << std::endl <<
    "NumChannels: \t" << wav.NumChannels << std::endl <<
    "SampleRate: \t" << wav.SampleRate << std::endl <<
    "ByteRate: \t" << wav.ByteRate << std::endl <<
    "BlockAlign: \t" << wav.BlockAlign << std::endl <<
    "BitsPerSample: \t" << wav.BitsPerSample << std::endl <<
    "Subchunk2ID: \t" << wav.Subchunk2ID[0] << wav.Subchunk2ID[1] << wav.Subchunk2ID[2] << wav.Subchunk2ID[3] << std::endl <<
    "Subchunk2Size: \t" << wav.Subchunk2Size << std::endl;
  return os;
}

} // namespace
