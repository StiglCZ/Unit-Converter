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
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
        public:
        ModelColumns() { add(primary); }
        Gtk::TreeModelColumn<Glib::ustring> primary;
    };

    // Widgets
    Gtk::Entry input, output;
    Gtk::Button convertButton;
    Gtk::ComboBox src, dst;
    Gtk::Label srcLabel, dstLabel, outLabel;
    
    // For comboboxes
    Gtk::Grid g;
    Glib::RefPtr<Gtk::ListStore> formats;
    ModelColumns columns;
    
};

#endif
