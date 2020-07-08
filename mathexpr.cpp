#include <iostream>
#include <string>

#include "rpn.h"


void process_line(std::string str)
{
  std::cout << " =======> " << str << std::endl;
  std::cout << " <======= " << math_rpn(str) << std::endl;
  std::cout << std::endl;
}

int main()
{
  std::string str = "<пусто>";

  bool eof;
  eof = std::getline(std::cin, str).eof();
  if (!str.empty()) process_line(str);

  while (!eof) {
    eof = std::getline(std::cin, str).eof();
    process_line(str);
  };

  return 0;
}