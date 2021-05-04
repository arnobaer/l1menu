%module l1menu
%{
#include "../include/l1menu/l1menu.hpp"
#include "../include/l1menu/l1menu_xml.hpp"
%}

%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>

// Parse the original header file
%include "../include/l1menu/l1menu.hpp"
%include "../include/l1menu/l1menu_xml.hpp"

// Instantiate some templates
%template(cut_vector) std::vector<l1menu::Cut>;
%template(object_requirement_vector) std::vector<l1menu::ObjectRequirement>;
%template(external_requirement_vector) std::vector<l1menu::ExternalRequirement>;
%template(algorithm_vector) std::vector<l1menu::Algorithm>;
%template(string_set) std::set<std::string>;
%template(bin_vector) std::vector<l1menu::Bin>;
%template(scale_vector) std::vector<l1menu::Scale>;
%template(ext_signal_vector) std::vector<l1menu::ExtSignal>;
