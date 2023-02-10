#include "application.h"

TApplication::TApplication() {}

int TApplication::exec() {
  int ch;
  int dim = 2;
  TMatrix a(dim);

  while (true) {
    ch = menu();
    switch (ch) {
    case 1:
      a.set();
      break;
    case 2:
      std::cout << a.det() << "\n\n";
      break;
    case 3:
      a.transpose();
      break;
    case 4:
      std::cout << a.rank() << "\n\n";
      break;
    case 5:
      std::cout << a << "\n";
      break;
    case 0:
      return 0;
    default:
      break;
    }
  }
  return 0;
}

int TApplication::menu() {
  int ch;
  std::cout << "1 - enter data\n";
  std::cout << "2 - determinant\n";
  std::cout << "3 - transpose\n";
  std::cout << "4 - rank\n";
  std::cout << "5 - print\n";
  std::cout << "0 - exit\n> ";
  std::cin >> ch;
  std::cout << "\n";
  return ch;
}
