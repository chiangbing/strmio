#include "typed_bytes.h"
#include <iostream>


int main() {
  strmio::TypedBytes key;
  strmio::TypedBytes value;

  // test a character before test good() in case that good() return true
  // while next read fails due to closed cin.
  std::cin.peek();

  while (std::cin.good()) {
    key.read(std::cin);
    value.read(std::cin);

    // update every key to "hello"
    key.set_string_val("hello");

    // output key & value
    key.write(std::cout);
    value.write(std::cout);

    // peek next character
    std::cin.peek();
  }
}