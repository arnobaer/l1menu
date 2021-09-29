#ifndef l1menu_xml_hpp
#define l1menu_xml_hpp

#include <l1menu/l1menu_xml.hpp>

#include <pugixml.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

#include <sstream>

namespace l1menu {

template<typename T>
std::string
format_decimal(const T& v)
{
  return boost::str(boost::format("%+23.16E") % (v));
}

std::vector<std::string>
tokenize(const std::string& text)
{
  std::vector<std::string> s;
  boost::char_separator<char> sep(",");
  boost::tokenizer<boost::char_separator<char>> tokens(text, sep);
  for (const auto& token: tokens)
    s.emplace_back(boost::algorithm::trim_copy(token));
  return s;
}

template<typename T, typename N>
T get_value(const N& node, const std::string& key)
{
  auto value = node.child(key.c_str()).text().as_string();
  try
  {
    return boost::lexical_cast<T>(value);
  }
  catch (const boost::bad_lexical_cast& e)
  {
    std::ostringstream oss;
    oss << "invalid type for key " << key << " '" << value << "'";
    throw std::runtime_error(oss.str());
  }
}

l1menu::Menu
read_xml(const std::string& filename)
{
  pugi::xml_document doc;

  pugi::xml_parse_result result = doc.load_file(filename.c_str(), pugi::parse_default, pugi::encoding_utf8);

  if (not result)
  {
    throw std::runtime_error(result.description());
  }

  const auto& menu_node = doc.child("tmxsd:menu");

  auto name = get_value<text_type>(menu_node, "name");
  auto uuid_menu = get_value<text_type>(menu_node, "uuid_menu");
  auto uuid_firmware = get_value<text_type>(menu_node, "uuid_firmware");
  auto grammar_version = get_value<text_type>(menu_node, "grammar_version");
  auto n_modules = get_value<size_type>(menu_node, "n_modules");
  auto comment = get_value<text_type>(menu_node, "comment");

  l1menu::Menu::algorithms_type algorithms;

  for (const auto& algorithm_node: menu_node.children("algorithm"))
  {
    auto name = get_value<text_type>(algorithm_node, "name");
    auto expression = get_value<text_type>(algorithm_node, "expression");
    auto index = get_value<size_type>(algorithm_node, "index");
    auto module_id = get_value<size_type>(algorithm_node, "module_id");
    auto module_index = get_value<size_type>(algorithm_node, "module_index");
    auto comment = get_value<text_type>(algorithm_node, "comment");
    auto labels = tokenize(get_value<text_type>(algorithm_node, "labels"));

    l1menu::Algorithm algorithm(
      name, expression, index, module_id, module_index, comment, labels
    );

    l1menu::Algorithm::cuts_type cuts;

    for (const auto& cut_node: algorithm_node.children("cut"))
    {
      auto name = get_value<text_type>(cut_node, "name");
      auto object = get_value<text_type>(cut_node, "object");
      auto type = get_value<text_type>(cut_node, "type");
      auto minimum = get_value<decimal_type>(cut_node, "minimum");
      auto maximum = get_value<decimal_type>(cut_node, "maximum");
      auto data = get_value<text_type>(cut_node, "data");
      auto comment = get_value<text_type>(cut_node, "comment");

      cuts.emplace_back(l1menu::Algorithm::cut_type(
        name, object, type, minimum, maximum, data, comment
      ));
    }

    algorithm.set_cuts(cuts);

    l1menu::Algorithm::object_requirements_type object_requirements;

    for (const auto& object_requirement_node: algorithm_node.children("object_requirement"))
    {
      auto name = get_value<text_type>(object_requirement_node, "name");
      auto type = get_value<text_type>(object_requirement_node, "type");
      auto comparison_operator = get_value<text_type>(object_requirement_node, "comparison_operator");
      auto threshold = get_value<decimal_type>(object_requirement_node, "threshold");
      auto bx_offset = get_value<offset_type>(object_requirement_node, "bx_offset");
      auto comment = get_value<text_type>(object_requirement_node, "comment");

      object_requirements.emplace_back(l1menu::Algorithm::object_requirement_type(
        name, type, comparison_operator, threshold, bx_offset, comment
      ));
    }

    algorithm.set_object_requirements(object_requirements);

    l1menu::Algorithm::external_requirements_type external_requirements;

    for (const auto& external_requirement_node: algorithm_node.children("external_requirement"))
    {
      auto name = get_value<text_type>(external_requirement_node, "name");
      auto bx_offset = get_value<offset_type>(external_requirement_node, "bx_offset");
      auto comment = get_value<text_type>(external_requirement_node, "comment");

      external_requirements.emplace_back(l1menu::Algorithm::external_requirement_type(
        name, bx_offset, comment
      ));
    }

    algorithm.set_external_requirements(external_requirements);

    algorithms.emplace_back(algorithm);
  }

  const auto& scale_set_node = menu_node.child("scale_set");

  auto scale_set = l1menu::ScaleSet();
  scale_set.set_name(get_value<text_type>(scale_set_node, "name"));

  for (const auto& scale_node: scale_set_node.children("scale"))
  {
    auto object = get_value<text_type>(scale_node, "object");
    auto type = get_value<text_type>(scale_node, "type");
    auto minimum = get_value<decimal_type>(scale_node, "minimum");
    auto maximum = get_value<decimal_type>(scale_node, "maximum");
    auto step = get_value<decimal_type>(scale_node, "step");
    auto n_bits = get_value<size_type>(scale_node, "n_bits");

    l1menu::Scale::bins_type bins;

    for (const auto& bin_node: scale_node.children("bin"))
    {
      auto number = get_value<size_type>(bin_node, "number");
      auto minimum = get_value<decimal_type>(bin_node, "minimum");
      auto maximum = get_value<decimal_type>(bin_node, "maximum");

      bins.emplace_back(l1menu::Bin(
        number, minimum, maximum
      ));
    }

    scale_set.add_scale(l1menu::Scale(
      object, type, minimum, maximum, step, n_bits, bins
    ));
  }

  const auto& ext_signal_set_node = menu_node.child("ext_signal_set");

  auto ext_signal_set = l1menu::ExtSignalSet();
  ext_signal_set.set_name(get_value<text_type>(ext_signal_set_node, "name"));

  for (const auto& ext_signal_node: ext_signal_set_node.children("ext_signal"))
  {
    auto name = get_value<text_type>(ext_signal_node, "name");
    auto system = get_value<text_type>(ext_signal_node, "system");
    auto cable = get_value<size_type>(ext_signal_node, "cable");
    auto channel = get_value<size_type>(ext_signal_node, "channel");
    auto description = get_value<text_type>(ext_signal_node, "description");
    auto label = get_value<text_type>(ext_signal_node, "label");

    ext_signal_set.add_ext_signal(l1menu::ExtSignal(
      name, system, cable, channel, description, label
    ));
  }

  return l1menu::Menu(
    name, uuid_menu, uuid_firmware, grammar_version, n_modules, comment,
    algorithms, scale_set, ext_signal_set
  );
}

template<typename Node, typename Key, typename Value>
void xml_append_node(Node& node, const Key& key, const Value& value)
{
  std::string text = boost::lexical_cast<std::string>(value);
  node.append_child(key).append_child(pugi::node_pcdata).set_value(text.c_str());
}

template<typename Node, typename Key, typename Value>
void xml_append_node_empty(Node& node, const Key& key, const Value& value)
{
  std::string text = boost::lexical_cast<std::string>(value);
  if (text.size()) node.append_child(key).append_child(pugi::node_pcdata).set_value(text.c_str());
  else node.append_child(key);
}

template<typename Node, typename Key, typename Value>
void xml_append_node_optional(Node& node, const Key& key, const Value& value)
{
  std::string text = boost::lexical_cast<std::string>(value);
  if (text.size()) node.append_child(key).append_child(pugi::node_pcdata).set_value(text.c_str());
}

std::string
write_xml(const l1menu::Menu& menu)
{
  pugi::xml_document doc;

  auto declaration_node = doc.append_child(pugi::node_declaration);
  declaration_node.append_attribute("version") = "1.0";
  declaration_node.append_attribute("encoding") = "utf-8";
  declaration_node.append_attribute("standalone") = "no";

  auto menu_node = doc.append_child("tmxsd:menu");
  menu_node.append_attribute("xmlns:tmxsd") = "http://www.cern.ch/tmxsd/1.0.0";
  menu_node.append_attribute("xmlns:xsi") = "http://www.w3.org/2001/XMLSchema-instance";
  menu_node.append_attribute("xsi:schemaLocation") ="http://www.cern.ch/tmxsd/1.0.0 menu.xsd";

  xml_append_node(menu_node, "ancestor_id", 0);
  xml_append_node(menu_node, "name", menu.name());
  xml_append_node(menu_node, "uuid_menu", menu.uuid_menu());
  xml_append_node(menu_node, "uuid_firmware", menu.uuid_firmware());
  menu_node.append_child("global_tag");
  xml_append_node(menu_node, "grammar_version", menu.grammar_version());
  xml_append_node(menu_node, "n_modules", menu.n_modules());
  xml_append_node(menu_node, "is_valid", "true");
  xml_append_node(menu_node, "is_obsolete", "false");

  if (menu.comment().size()) xml_append_node(menu_node, "comment", menu.comment());

  for (const auto& algorithm: menu.algorithms())
  {
    auto algorithm_node = menu_node.append_child("algorithm");
    xml_append_node(algorithm_node, "name", algorithm.name());
    xml_append_node(algorithm_node, "expression", algorithm.expression());
    xml_append_node(algorithm_node, "index", algorithm.index());
    xml_append_node(algorithm_node, "module_id", algorithm.module_id());
    xml_append_node(algorithm_node, "module_index", algorithm.module_index());
    xml_append_node_optional(algorithm_node, "comment", algorithm.comment());
    xml_append_node_optional(algorithm_node, "labels", boost::join(algorithm.labels(), ","));
    for (const auto& cut: algorithm.cuts())
    {
      auto cut_node = algorithm_node.append_child("cut");
      xml_append_node(cut_node, "name", cut.name());
      xml_append_node_empty(cut_node, "object", cut.object());
      xml_append_node(cut_node, "type", cut.type());
      xml_append_node(cut_node, "minimum", format_decimal(cut.minimum()));
      xml_append_node(cut_node, "maximum", format_decimal(cut.maximum()));
      xml_append_node_empty(cut_node, "data", cut.data());
      xml_append_node_optional(cut_node, "comment", cut.comment());
    }
    for (const auto& object_requirement: algorithm.object_requirements())
    {
      auto object_requirement_node = algorithm_node.append_child("object_requirement");
      xml_append_node(object_requirement_node, "name", object_requirement.name());
      xml_append_node(object_requirement_node, "type", object_requirement.type());
      xml_append_node(object_requirement_node, "comparison_operator", object_requirement.comparison_operator());
      xml_append_node(object_requirement_node, "threshold", format_decimal(object_requirement.threshold()));
      xml_append_node(object_requirement_node, "bx_offset", object_requirement.bx_offset());
      xml_append_node_optional(object_requirement_node, "comment", object_requirement.comment());
    }
    for (const auto& external_requirement: algorithm.external_requirements())
    {
      auto external_requirement_node = algorithm_node.append_child("external_requirement");
      xml_append_node(external_requirement_node, "name", external_requirement.name());
      xml_append_node(external_requirement_node, "bx_offset", external_requirement.bx_offset());
      xml_append_node_optional(external_requirement_node, "comment", external_requirement.comment());
    }
  }

  auto scale_set_node = menu_node.append_child("scale_set");
  xml_append_node(scale_set_node,"name", menu.scale_set().name());

  for (const auto& scale: menu.scale_set().scales())
  {
    auto scale_node = scale_set_node.append_child("scale");
    xml_append_node(scale_node, "object", scale.object());
    xml_append_node(scale_node, "type", scale.type());
    xml_append_node(scale_node, "minimum", format_decimal(scale.minimum()));
    xml_append_node(scale_node, "maximum", format_decimal(scale.maximum()));
    xml_append_node(scale_node, "step", format_decimal(scale.step()));
    xml_append_node(scale_node, "n_bits", scale.nbits());
    for (const auto& bin: scale.bins())
    {
        auto bin_node = scale_node.append_child("bin");
        xml_append_node(bin_node, "number", bin.number());
        xml_append_node(bin_node, "minimum", format_decimal(bin.minimum()));
        xml_append_node(bin_node, "maximum", format_decimal(bin.maximum()));
    }
  }

  auto ext_signal_set_node = menu_node.append_child("ext_signal_set");
  xml_append_node(ext_signal_set_node, "name", menu.ext_signal_set().name());

  for (const auto& ext_signal: menu.ext_signal_set().ext_signals())
  {
    auto ext_signal_node = ext_signal_set_node.append_child("ext_signal");
    xml_append_node(ext_signal_node, "name", ext_signal.name());
    xml_append_node(ext_signal_node, "system", ext_signal.system());
    xml_append_node(ext_signal_node, "cable", ext_signal.cable());
    xml_append_node(ext_signal_node, "channel", ext_signal.channel());
    xml_append_node_optional(ext_signal_node, "description", ext_signal.description());
    xml_append_node_optional(ext_signal_node, "label", ext_signal.label());
  }

  std::ostringstream oss;
  doc.save(oss, "  ", pugi::format_default, pugi::encoding_utf8);

  return oss.str();
}

} // l1menu

#endif // l1menu_xml_hpp
