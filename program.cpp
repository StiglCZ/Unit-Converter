#include "program.hpp"
#include "gtkmm/enums.h"
#include "gtkmm/treeiter.h"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>

const std::vector<std::string> FormatNames = {
    "nanometers",
    "centimeters",
    "inches",
    "feet",
    "yards",
    "meters",
    "kilometers",
    "miles",
    "megameters",
    "gigameters",
};

const std::vector<float> FormatValues = {
    1.000000,
    1.000e+7,
    2.540e+7,
    3.048e+8,
    9.144e+8,
    1.000e+9,
    1.00e+12,
    1.609344e+12,
    1.00e+15,
    1.00e+18,
};

UnitConvert::UnitConvert() {
    g = Gtk::Grid();

    // Add labels to everything
    srcLabel = Gtk::Label("From: ");
    dstLabel = Gtk::Label("  To: ");
    outLabel = Gtk::Label("Result:");
    convertButton.set_label("Convert");

    // Input textbox(RW)
    input = Gtk::Entry();
    input.set_input_purpose(Gtk::InputPurpose::NUMBER);
    input.set_editable(true);
    input.set_overwrite_mode(false);
    input.set_overflow(Gtk::Overflow::VISIBLE);

    // Output textbox(RO)
    output = Gtk::Entry();
    output.set_editable(false);
    output.set_can_focus(false);

    // Fill comboboxes
    formats = Gtk::ListStore::create(columns);
    Gtk::TreeIter<Gtk::TreeRow> iter;
    Gtk::TreeRow row;

    for(std::string key : FormatNames) {
        iter = formats->append();
        row = *iter;
        row[columns.primary] = key;
    }

    src.set_model(formats);
    src.pack_start(columns.primary);

    dst.set_model(formats);
    dst.pack_start(columns.primary);

    src.set_active(1);
    dst.set_active(2);

    // Main container settings
    set_title("App");
    set_default_size(600, 300);
    set_child(g);

    g.attach(input,         0, 0, 3, 1);
    g.attach(convertButton, 3, 0, 1, 1);

    g.attach(outLabel, 0, 1, 1, 1);
    g.attach(output,   1, 1, 3, 1);

    g.attach(srcLabel, 0, 2, 1, 1);
    g.attach(src,      1, 2, 1, 1);
    g.attach(dstLabel, 2, 2, 1, 1);
    g.attach(dst,      3, 2, 1, 1);

    // Setup events
    convertButton.signal_clicked().connect(sigc::mem_fun(*this, &UnitConvert::ConvertClicked));
}

UnitConvert::~UnitConvert() {
    
}

void UnitConvert::ConvertClicked() {
    int pos = 0;
    std::string str = input.get_text();
    while((pos = str.find(',', pos)) != std::string::npos)
        str.replace(pos, 1, ".");

    // Calculate the result
    char *pEnd;
    double nanometers = strtod(str.c_str(), &pEnd)
        * FormatValues[src.get_active_row_number()]
        / FormatValues[dst.get_active_row_number()];

    // Convert to high precision string
    std::ostringstream os;
    os.precision(std::numeric_limits<double>::digits10 + 2);
    os << std::fixed << nanometers;
    std::string out = std::move(os).str();

    // Remove trailing zeroes
    if(out.find('.') != std::string::npos) {
        int last = out.size();
        while(out[--last] == '0') out.resize(last);
        if(out[last] == '.') out.resize(last);
    }

    output.set_text(out);
}

int main(int argc, char** argv) {
    auto app = Gtk::Application::create("org.test.unitconvert");
    return app->make_window_and_run<UnitConvert>(argc, argv);
}
