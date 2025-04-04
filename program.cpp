#include "program.hpp"
#include "gtkmm/enums.h"
#include "gtkmm/label.h"
#include "gtkmm/treeiter.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include "sigc++/functors/mem_fun.h"
#include "types.hh"

UnitConvert::UnitConvert() {
    historyWriter = std::ofstream(".unitcv_history");

    // Add labels to everything
    srcLabel = Gtk::Label("From:");
    dstLabel = Gtk::Label("To:");
    outLabel = Gtk::Label("Result:");
    typeLabel= Gtk::Label("Meassurement:");
    convertButton.set_label("Save");

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
    Gtk::TreeIter<Gtk::TreeRow> iter;
    Gtk::TreeRow row;
    MainFormats = Gtk::ListStore::create(columns);
    
    for(auto ConversionType : ConversionTypes) {
        formats.push_back(Gtk::ListStore::create(columns));
        Glib::RefPtr<Gtk::ListStore>& ref = formats[formats.size() -1];
        for(std::string key : ConversionType.second.first) {
            iter = ref->append();
            row = *iter;
            row[columns.primary] = key;
        }
        
        (*MainFormats->append())[columns.primary] =  ConversionType.first;
    }

    src.set_model(formats[SelectedFormat]);
    src.pack_start(columns.primary);

    dst.set_model(formats[SelectedFormat]);
    dst.pack_start(columns.primary);

    src.set_active(0);
    dst.set_active(1);

    type.set_model(MainFormats);
    type.pack_start(columns.primary);
    type.set_active(0);
    
    
    // Main container settings
    g = Gtk::Grid();
    set_title("Unit Convertor");
    set_default_size(350, 200);
    set_child(g);

    g.set_row_spacing(1);
    g.set_column_spacing(1);

    g.attach(typeLabel, 0, 0, 2, 1);
    g.attach(type,      2, 0, 1, 1);

    g.attach(srcLabel, 0, 1, 1, 1);
    g.attach(src,      1, 1, 3, 1);
    
    g.attach(dstLabel, 0, 2, 1, 1);
    g.attach(dst,      1, 2, 3, 1);
    
    g.attach(input,         0, 3, 3, 1);
    g.attach(convertButton, 3, 3, 1, 1);

    g.attach(outLabel, 0, 4, 1, 1);
    g.attach(output,   1, 4, 3, 1);
    
    // Setup events
    type.signal_changed().connect(sigc::mem_fun(*this, &UnitConvert::TypesChanged));
    convertButton.signal_clicked().connect(sigc::mem_fun(*this, &UnitConvert::Convert), false);

    convertButton.signal_clicked().connect(sigc::mem_fun(*this, &UnitConvert::SaveInHistory), true);
    type.signal_changed().connect(sigc::mem_fun(*this, &UnitConvert::Convert));
    dst.  signal_changed().connect(sigc::mem_fun(*this, &UnitConvert::Convert));
    src.  signal_changed().connect(sigc::mem_fun(*this, &UnitConvert::Convert));
    input.signal_changed().connect(sigc::mem_fun(*this, &UnitConvert::Convert));
}

UnitConvert::~UnitConvert() {
    historyWriter.close();
}

void UnitConvert::TypesChanged() {
    SelectedFormat = type.get_active_row_number();

    src.clear();
    src.set_model(formats[SelectedFormat]);
    src.pack_start(columns.primary);
    src.set_active(0);

    dst.clear();
    dst.set_model(formats[SelectedFormat]);
    dst.pack_start(columns.primary);
    dst.set_active(0);

    output.set_text("");
}

void UnitConvert::Convert() {
    int pos = 0;
    std::string str = input.get_text();
    while((pos = str.find(',', pos)) != std::string::npos)
        str.replace(pos, 1, ".");

    // Calculate the result
    char *pEnd;
    auto it = ConversionTypes.begin();
    std::advance(it, SelectedFormat);
    std::vector<double> Values = it->second.second;
    double result = strtod(str.c_str(), &pEnd)
        * Values[src.get_active_row_number()]
        / Values[dst.get_active_row_number()];
    
    // Convert to high precision string
    std::string out;
    std::stringstream ss;
    ss.precision(std::numeric_limits<double>::digits10 + 2);
    ss << std::fixed << result;
    ss >> out;
    
    // Remove trailing zeroes
    if(out.find('.') != std::string::npos) {
        int last = out.size();
        while(out[--last] == '0') out.resize(last);
        if(out[last] == '.') out.resize(last);
    }

    output.set_text(out);
}

void UnitConvert::SaveInHistory() {
    historyWriter
        << input.get_text().c_str()
        << ConversionTypes.begin()->second.first[src.get_active_row_number()] << " = "
        << std::fixed << output.get_text()
        << ConversionTypes.begin()->second.first[dst.get_active_row_number()] << std::endl;
}

int main(int argc, char** argv) {
    auto app = Gtk::Application::create("org.test.unitconvert");
    
    return app->make_window_and_run<UnitConvert>(argc, argv);
}
