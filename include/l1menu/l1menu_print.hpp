#ifndef l1menu_print_hpp
#define l1menu_print_hpp

#include <l1menu/l1menu_xml.hpp>

#include <boost/algorithm/string.hpp>

#include <sstream>

std::ostream&
operator<<(std::ostream& os, const l1menu::Algorithm& algorithm)
{
  os << "l1menu::Algorithm(\n";
  os << "  index: " << algorithm.index() << "\n";
  os << "  name: " << algorithm.name() << "\n";
  os << "  labels: " << boost::algorithm::join( algorithm.labels(), ", ") << "\n";
  os << "  expression: " << algorithm.expression() << "\n";
  os << ")";
  return os;
}

std::ostream&
operator<<(std::ostream& os, const l1menu::Bin& bin)
{
  os << "l1menu::Bin(\n";
  os << "  number: " << bin.number() << "\n";
  os << "  minimum: " << bin.minimum() << "\n";
  os << "  maximum: " << bin.maximum() << "\n";
  os << ")";
  return os;
}

std::ostream&
operator<<(std::ostream& os, const l1menu::Scale& scale)
{
  os << "l1menu::Scale(\n";
  os << "  object: " << scale.object() << "\n";
  os << "  type: " << scale.type() << "\n";
  os << "  minimum: " << scale.minimum() << "\n";
  os << "  maximum: " << scale.maximum() << "\n";
  os << "  step: " << scale.step() << "\n";
  os << "  n_bits: " << scale.nbits() << "\n";
  os << ")";
  return os;
}

std::ostream&
operator<<(std::ostream& os, const l1menu::ExtSignal& ext_signal)
{
  os << "l1menu::ExtSignal(\n";
  os << "  name: " << ext_signal.name() << "\n";
  os << "  system: " << ext_signal.system() << "\n";
  os << "  cable: " << ext_signal.cable() << "\n";
  os << "  channel: " << ext_signal.channel() << "\n";
  os << "  description: " << ext_signal.description() << "\n";
  os << "  label: " << ext_signal.label() << "\n";
  os << ")";
  return os;
}

std::ostream&
operator<<(std::ostream& os, const l1menu::Menu::algorithms_type& algorithms)
{
  for (const auto& algorithm: algorithms)
    os << algorithm << std::endl;
  return os;
}

std::ostream&
operator<<(std::ostream& os, const l1menu::Menu& menu)
{
  os << "l1menu::Menu(\n";
  os << "  name: " << menu.name() << "\n";
  os << "  uuid_menu: " << menu.uuid_menu() << "\n";
  os << "  uuid_firmware: " << menu.uuid_firmware() << "\n";
  os << "  grammar_version: " << menu.grammar_version() << "\n";
  os << "  comment: " << menu.comment() << "\n";
  os << ")";
  return os;
}

#endif // l1menu_print_hpp
