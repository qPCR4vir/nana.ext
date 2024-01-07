/**
* Copyright (C) 2021, Ariel Vina Rodriguez ( arielvina@yahoo.es )
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*
*  @file  nana.ext\src\editable_place.hpp
*
*  @author Ariel Vina-Rodriguez (qPCR4vir)
*
*  @brief
*
* Extension to nana. From: https://github.com/qPCR4vir/nana.ext
*
* To be used together with:
*
*  - the Nana C++ GUI library, from: https://github.com/cnjinhao/nana
*
*/

#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/filebox.hpp>    

#include <../../nana.ext/include/editable_place.hpp>    
#include <../../nana.ext/include/EditableForm.hpp>


class edit_place_form : public nana::form
{
    OpenSaveBox     _OSbx{ *this, "Layout:" };
    nana::button	_ReCollocate{ *this, "Apply" }, 
                    _hide       { *this, "Hide" },
                    _panic      { *this, "Panic !" }, 
                    _def        { *this, "Default" },
                    _cpp        { *this, "C++ code" };
    nana::textbox	_textBox{ *this };
    nana::menu&     _menuFile{ _menuBar.push_back("&File") };
    nana::event_handle _hide_not_unload{ make_hidable() };  // hide_(),

public:
    edit_place_form(edit_place& owner, int i = 0);

    void make_closable()
    {
        if (_hide_not_unload)
        {
            umake_event(_hide_not_unload);
            _hide_not_unload = nullptr;
        }
    }

    ~edit_place_form()
    {
        make_closable();
    }

private:
    void SetDefLayout() override;
    void AsignWidgetToFields() override;
    void on_edited();
    void InitCaptions();

    nana::event_handle make_hidable()
    {
        //assert((    std::cerr<<"\nMaking Hidable EditLayout_Form: " , true ) );; // debbug
        //assert((    std::wcerr<< this->caption() , true ) ); ; // debbug

        return events().unload([this](const nana::arg_unload& ei)
            {
                //assert((    std::cerr<<"\n Hiding, not closing EditLayout_Form: "  , true) );;  // debbug
                //assert((    std::wcerr<< this->caption()  , true) );; // debbug

                ei.cancel = true;    //Stop closing and then
                hide();
            });
    };
    void MakeResponsive();
    void ReLayout();
    void ReloadDef();
    void OpenFile();
    void OpenFileN(const std::string& file = "");
    void SaveFileN(const std::string& fileTip = "", const std::string& tmp_title = std::string{});
    void ForceSave(const std::string& file);
    void SaveFile() {     // temporal !!!!!!!!!!!!!!
        if (!_OSbx.Canceled())
            ForceSave(_OSbx.FileName());
    };
    void toCppCode();
};

edit_place::edit_place(nana::place& to_edit, std::filesystem::path def_layout_file = {})
    : me{ to_edit }, def_layout_file{ std::move(def_layout_file) }
{}

edit_place::~edit_place() {}


void edit_place::edit()
{
    if (!my_edit_form)
        my_edit_form = new edit_place_form(*this, 0);

    my_edit_form->show();
}

void edit_place::init_menu(nana::menu& menuProgram)
{
    menuProgram.append("&Edit this windows Layout", [&](nana::menu::item_proxy& ip) {edit(); });
    menuProgram.append("&Reset this windows default Layout", [&](nana::menu::item_proxy& ip)
        {edit(); ReCollocate(); });
}