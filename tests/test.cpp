#include <iostream>

struct test{
  unsigned int c : 4; // bit field
}

int main() {
  std::cout << "Hello World!\n";
  struct test a;
  //int test = 0;

  for (int i=0; i<15; i++){
    a.c = rand() % 10;
    std::cout << a.c << "\n";
  }    
}
