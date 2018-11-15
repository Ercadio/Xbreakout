#include "WAVFile.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

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
  return is;
}

std::ostream& operator<<(std::ostream& os, WAVFile& wav) {
  os << 
    "ChunkID: \t" << wav.ChunkID << std::endl <<
    "ChunkSize: \t" << wav.ChunkSize << std::endl <<
    "Format: \t" << wav.Format[0] << wav.Format[1] << wav.Format[2] << wav.Format[3] << std::endl <<
    "Subchunk1ID: \t" << wav.Subchunk1ID << std::endl <<
    "Subchunk1Size \t" << wav.
  return os;
}


int main() {
  std::ifstream fs ("Mainframe.wav", std::ios::in | std::ios::binary);
  if(not fs.is_open()) {
    std::cout << "Cannot read file\n";
  }
  WAVFile wav{ 0 };
  fs >> wav;
  std::cout << wav;
}
