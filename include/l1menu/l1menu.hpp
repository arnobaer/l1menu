#ifndef l1menu_hpp
#define l1menu_hpp

#include <vector>
#include <string>

namespace l1menu {

using size_type = unsigned int;
using offset_type = signed int;
using text_type = std::string;
using decimal_type = long double;

class Cut;
class ObjectRequirement;
class Algorithm;
class Bin;
class Scale;
class ScaleSet;
class ExtSignal;
class ExtSignalSet;
class Menu;

const text_type DEFAULT_UUID {"00000000-0000-0000-0000-000000000000"};

class Cut
{
public:
    Cut() = default;
    Cut(const text_type& name, const text_type& object, const text_type& type,
        const decimal_type minimum, const decimal_type maximum,
        const text_type& data, const text_type& comment)
    : m_name(name), m_object(object), m_type(type), m_minimum(minimum),
      m_maximum(maximum), m_data(data), m_comment(comment) {}
    ~Cut() = default;

    const text_type& name() const { return m_name; }
    void set_name(const text_type& name) { m_name = name; }

    const text_type& object() const { return m_object; }
    void set_object(const text_type& object) { m_object = object; }

    const text_type& type() const { return m_type; }
    void set_type(const text_type& type) { m_type = type; }

    decimal_type minimum() const { return m_minimum; }
    void set_minimum(const decimal_type minimum) { m_minimum = minimum; }

    decimal_type maximum() const { return m_maximum; }
    void set_maximum(const decimal_type maximum) { m_maximum = maximum; }

    const text_type& data() const { return m_data; }
    void set_data(const text_type& data) { m_data = data; }

    const text_type& comment() const { return m_comment; }
    void set_comment(const text_type& comment) { m_comment = comment; }

private:
    text_type m_name;
    text_type m_object;
    text_type m_type;
    decimal_type m_minimum = 0;
    decimal_type m_maximum = 0;
    text_type m_data;
    text_type m_comment;
};

class ObjectRequirement
{
public:
    ObjectRequirement() = default;
    ObjectRequirement(const text_type& name, const text_type& type,
                      const text_type& comparison_operator,
                      const decimal_type threshold, const offset_type bx_offset,
                      const text_type& comment)
    : m_name(name), m_type(type), m_comparison_operator(comparison_operator),
      m_threshold(threshold), m_bx_offset(bx_offset), m_comment(comment) {}
    ~ObjectRequirement() = default;

    const text_type& name() const { return m_name; }
    void set_name(const text_type& name) { m_name = name; }

    const text_type& type() const { return m_type; }
    void set_type(const text_type& type) { m_type = type; }

    const text_type& comparison_operator() const { return m_comparison_operator; }
    void set_comparison_operator(const text_type& comparison_operator) { m_comparison_operator = comparison_operator; }

    decimal_type threshold() const { return m_threshold; }
    void set_threshold(const decimal_type threshold) { m_threshold = threshold; }

    offset_type bx_offset() const { return m_bx_offset; }
    void set_bx_offset(const offset_type bx_offset) { m_bx_offset = bx_offset; }

    const text_type& comment() const { return m_comment; }
    void set_comment(const text_type& comment) { m_comment = comment; }

private:
    text_type m_name;
    text_type m_type;
    text_type m_comparison_operator = ".ge.";
    decimal_type m_threshold = 0;
    offset_type m_bx_offset = 0;
    text_type m_comment;
};

class ExternalRequirement
{
public:
    ExternalRequirement() = default;
    ExternalRequirement(const text_type& name, const offset_type bx_offset,
                        const text_type& comment)
    : m_name(name), m_bx_offset(bx_offset), m_comment(comment) {}
    ~ExternalRequirement() = default;

    const text_type& name() const { return m_name; }
    void set_name(const text_type& name) { m_name = name; }

    offset_type bx_offset() const { return m_bx_offset; }
    void set_bx_offset(const offset_type bx_offset) { m_bx_offset = bx_offset; }

    const text_type& comment() const { return m_comment; }
    void set_comment(const text_type& comment) { m_comment = comment; }

private:
    text_type m_name;
    offset_type m_bx_offset = 0;
    text_type m_comment;
};

class Algorithm
{
public:
    using labels_type = std::vector<text_type>;
    using cut_type = l1menu::Cut;
    using cuts_type = std::vector<cut_type>;
    using object_requirement_type = l1menu::ObjectRequirement;
    using object_requirements_type = std::vector<object_requirement_type>;
    using external_requirement_type = l1menu::ExternalRequirement;
    using external_requirements_type = std::vector<external_requirement_type>;

    Algorithm() = default;
    Algorithm(const text_type& name, const text_type& expression,
              const size_type index, const size_type module_id,
              const size_type module_index, const text_type& comment,
              const labels_type& labels)
    : m_name(name), m_expression(expression), m_index(index),
      m_module_id(module_id), m_module_index(module_index), m_comment(comment),
      m_labels(labels) {}
    ~Algorithm() = default;

    const text_type& name() const { return m_name; }
    void set_name(const text_type& name) { m_name = name; }

    const text_type& expression() const { return m_expression; }
    void set_expression(const text_type& expression) { m_expression = expression; }

    size_type index() const { return m_index; }
    void set_index(const size_type index) { m_index = index; }

    size_type module_id() const { return m_module_id; }
    void set_module_id(const size_type module_id) { m_module_id = module_id; }

    size_type module_index() const { return m_module_index; }
    void set_module_index(const size_type module_index) { m_module_index = module_index; }

    const labels_type& labels() const { return m_labels; }
    labels_type& labels() { return m_labels; }
    void set_labels(const labels_type& labels) { m_labels = labels; }
    void add_label(const text_type& label) { m_labels.emplace_back(label); }

    const text_type& comment() const { return m_comment; }
    void set_comment(const text_type& comment) { m_comment = comment; }

    const cuts_type& cuts() const { return m_cuts; }
    void set_cuts(const cuts_type& cuts) { m_cuts = cuts; }

    const object_requirements_type& object_requirements() const { return m_object_requirements; }
    void set_object_requirements(const object_requirements_type& object_requirements) { m_object_requirements = object_requirements; }

    const external_requirements_type& external_requirements() const { return m_external_requirements; }
    void set_external_requirements(const external_requirements_type& external_requirements) { m_external_requirements = external_requirements; }

private:
    text_type m_name;
    text_type m_expression;
    size_type m_index = 0;
    size_type m_module_id = 0;
    size_type m_module_index = 0;
    text_type m_comment;
    labels_type m_labels;
    cuts_type m_cuts;
    object_requirements_type m_object_requirements;
    external_requirements_type m_external_requirements;
};

class Bin
{
public:
    Bin() = default;
    Bin(const size_type number, const decimal_type minimum,
      const decimal_type maximum)
    : m_number(number), m_minimum(minimum), m_maximum(maximum) {}
    ~Bin() = default;

    size_type number() const { return m_number; }
    decimal_type minimum() const { return m_minimum; }
    decimal_type maximum() const { return m_maximum; }

private:
    size_type m_number = 0;
    decimal_type m_minimum = 0;
    decimal_type m_maximum = 0;
};

class Scale
{
public:
    using bin_type = l1menu::Bin;
    using bins_type = std::vector<bin_type>;

    Scale() = default;
    Scale(const text_type& object, const text_type& type,
        const decimal_type minimum, const decimal_type maximum,
        const decimal_type step, const size_type nbits, const bins_type& bins)
    : m_object(object), m_type(type), m_minimum(minimum), m_maximum(maximum),
    m_step(step), m_nbits(nbits), m_bins(bins) {}
    ~Scale() = default;

    const text_type& object() const { return m_object; }
    const text_type& type() const { return m_type; }
    decimal_type minimum() const { return m_minimum; }
    decimal_type maximum() const { return m_maximum; }
    decimal_type step() const { return m_step; }
    size_type nbits() const { return m_nbits; }
    const text_type& comment() const { return m_comment; }
    const bins_type& bins() const { return m_bins; }

private:
    text_type m_object;
    text_type m_type;
    decimal_type m_minimum;
    decimal_type m_maximum;
    decimal_type m_step;
    size_type m_nbits = 0;
    text_type m_comment;
    bins_type m_bins;
};

class ScaleSet
{
public:
    using scale_type = l1menu::Scale;
    using scales_type = std::vector<scale_type>;

    ScaleSet() = default;
    ~ScaleSet() = default;

    const text_type& name() const { return m_name; }
    void set_name(const text_type& name) { m_name = name; }

    const text_type& comment() const { return m_comment; }
    void set_comment(const text_type& comment) { m_comment = comment; }

    const scales_type& scales() const { return m_scales; }
    void add_scale(const scale_type& scale) { m_scales.emplace_back(scale); }

private:
    text_type m_name;
    text_type m_comment;
    scales_type m_scales;
};

class ExtSignal
{
public:
    ExtSignal() = default;
    ExtSignal(const text_type& name, const text_type& system,
               const size_type cable, const size_type channel,
               const text_type& description, const text_type& label)
    : m_name(name), m_system(system), m_cable(cable), m_channel(channel),
      m_description(description), m_label(label) {}
    ~ExtSignal() = default;

    const text_type& name() const { return m_name; }
    void set_name(const text_type& name) { m_name = name; }

    const text_type& system() const { return m_system; }
    void set_system(const text_type& system) { m_system = system; }

    size_type cable() const { return m_cable; }
    void set_system(const size_type cable) { m_cable = cable; }

    size_type channel() const { return m_channel; }
    void set_channel(const size_type channel) { m_channel = channel; }

    const text_type& description() const { return m_description; }
    void set_description(const text_type& description) { m_description = description; }

    const text_type& label() const { return m_label; }
    void set_label(const text_type& label) { m_label = label; }

private:
    text_type m_name;
    text_type m_system;
    size_type m_cable = 0;
    size_type m_channel = 0;
    text_type m_description;
    text_type m_label;
};

class ExtSignalSet
{
public:
    using ext_signal_type = l1menu::ExtSignal;
    using ext_signals_type = std::vector<ext_signal_type>;

    ExtSignalSet() = default;
    ExtSignalSet(const text_type& name, const text_type& comment,
                   const ext_signals_type& ext_signals)
    : m_name(name), m_comment(comment), m_ext_signals(ext_signals) {}
    ~ExtSignalSet() = default;

    const text_type& name() const { return m_name; }
    void set_name(const text_type& name) { m_name = name; }

    const text_type& comment() const { return m_comment; }
    void set_comment(const text_type& comment) { m_comment = comment; }

    const ext_signals_type& ext_signals() const { return m_ext_signals; }
    void add_ext_signal(const ext_signal_type& ext_signal) { m_ext_signals.emplace_back(ext_signal); }

private:
    text_type m_name;
    text_type m_comment;
    ext_signals_type m_ext_signals;
};

class Menu
{
public:
    using size_type = unsigned int;
    using algorithm_type = l1menu::Algorithm;
    using algorithms_type = std::vector<algorithm_type>;
    using scale_set_type = l1menu::ScaleSet;
    using ext_signal_set_type = l1menu::ExtSignalSet;

    Menu() = default;
    Menu(const text_type& name): m_name(name) {}
    Menu(const text_type& name, const text_type& uuid_menu,
         const text_type& uuid_firmware, const text_type& grammar_version,
         const size_type n_modules, const text_type& comment)
    : m_name(name), m_uuid_menu(uuid_menu), m_uuid_firmware(uuid_firmware),
      m_grammar_version(grammar_version), m_n_modules(n_modules),
      m_comment(comment) {}
    Menu(const text_type& name, const text_type& uuid_menu,
         const text_type& uuid_firmware, const text_type& grammar_version,
         const size_type n_modules, const text_type& comment,
         const algorithms_type& algorithms, const scale_set_type& scale_set,
         const ext_signal_set_type& ext_signal_set)
    : m_name(name), m_uuid_menu(uuid_menu), m_uuid_firmware(uuid_firmware),
      m_grammar_version(grammar_version), m_n_modules(n_modules),
      m_comment(comment), m_algorithms(algorithms), m_scale_set(scale_set),
      m_ext_signal_set(ext_signal_set) {}
    ~Menu() = default;

    const text_type& name() const { return m_name; }
    void set_name(const text_type& name) { m_name = name; }

    const text_type& uuid_menu() const { return m_uuid_menu; }
    void set_uuid_menu(const text_type& uuid_menu) { m_uuid_menu = uuid_menu; }

    const text_type& uuid_firmware() const { return m_uuid_firmware; }
    void set_uuid_firmware(const text_type& uuid_firmware) { m_uuid_firmware = uuid_firmware; }

    const text_type& grammar_version() const { return m_grammar_version; }
    void set_grammar_version(const text_type& version) { m_grammar_version = version; }

    size_type n_modules() const { return m_n_modules; }
    void set_n_modules(const size_type n_modules) { m_n_modules = n_modules; }

    const text_type& comment() const { return m_comment; }
    void set_comment(const text_type& comment) { m_comment = comment; }

    const algorithms_type& algorithms() const { return m_algorithms; }
    void add_algorithm(const algorithm_type& algorithm) { m_algorithms.emplace_back(algorithm); }

    const scale_set_type& scale_set() const { return m_scale_set; }
    void set_scale_set(const scale_set_type& scale_set) { m_scale_set = scale_set; }

    const ext_signal_set_type& ext_signal_set() const { return m_ext_signal_set; }
    void set_ext_signal_set(const ext_signal_set_type& ext_signal_set) { m_ext_signal_set = ext_signal_set; }

private:
    text_type m_name;
    text_type m_uuid_menu = DEFAULT_UUID;
    text_type m_uuid_firmware = DEFAULT_UUID;
    text_type m_grammar_version;
    size_type m_n_modules = 0;
    text_type m_comment;
    algorithms_type m_algorithms;
    scale_set_type m_scale_set;
    ext_signal_set_type m_ext_signal_set;
};

} // l1menu

#endif // l1menu_hpp
