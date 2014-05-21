#include <iostream>
#include <fstream>

std::ifstream::pos_type filesize(const char* filename)
{
  // Return the size in Bytes.
  std::ifstream in(filename, std::ifstream::in | std::ifstream::binary);
  in.seekg(0, std::ifstream::end);
  return in.tellg();
}

int main(int argc, char * argv[]) {
  std::cout << filesize(argv[1]) << std::endl;
  return 0;
}
