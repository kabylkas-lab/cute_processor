#include <iostream>

int main() {
  std::cout << "Hello World!\n";
  unsigned int c : 4; // bit field
  //int test = 0;

  for (int i=0; i<15; i++){
    c = rand() % 10;
    std::cout << c << "\n";
  }    
}
