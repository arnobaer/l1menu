#include <l1menu/l1menu.hpp>
#include <l1menu/l1menu_xml.hpp>
#include <l1menu/l1menu_print.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
  const std::string filename = argv[1];

  auto menu = l1menu::read_xml(filename);

  std::cout << l1menu::write_xml(menu);

}
