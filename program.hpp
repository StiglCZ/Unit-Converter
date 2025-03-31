#ifndef PROGRAM_HH
#define PROGRAM_HH
#include "glibmm/refptr.h"
#include "gtkmm/liststore.h"
#include "gtkmm/treemodelcolumn.h"
#include <gtkmm-4.0/gtkmm.h>

class UnitConvert : public Gtk::Window {
    public:
    UnitConvert();
    ~UnitConvert() override;
    
    private:
    void ConvertClicked();
    void TypesChanged();
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
        public:
        ModelColumns() { add(primary); }
        Gtk::TreeModelColumn<Glib::ustring> primary;
    };

    // Widgets
    Gtk::Grid g;
    Gtk::Entry input, output;
    Gtk::Button convertButton;
    Gtk::ComboBox type, src, dst;
    Gtk::Label typeLabel, srcLabel, dstLabel, outLabel;
    
    // For comboboxes
    ushort SelectedFormat = 0;
    std::vector<Glib::RefPtr<Gtk::ListStore>> formats;
    Glib::RefPtr<Gtk::ListStore> MainFormats;
    ModelColumns columns;
    
};

#endif
