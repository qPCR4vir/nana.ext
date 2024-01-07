/**
* Copyright (C) 2021, Ariel Vina Rodriguez ( arielvina@yahoo.es )
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*
*  @file  nana.ext\include\editable_place.hpp
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

#ifndef NANA_GUI_Editable_Place_HPP
#define NANA_GUI_Editable_Place_HPP

#include <nana/gui.hpp>
#include <nana/gui/widgets/menubar.hpp>
   
class edit_place_form;

class edit_place
{
 public:
	 edit_place(nana::place& to_edit,                         ///< reference to the place to edit - make sure it stay valid
		        std::filesystem::path def_layout_file = {}    ///< optional source of initial div-text
	            );

	 ~edit_place();

	 void edit();

	 void init_menu(nana::menu& your_menu); ///< append menu items to Edit the layout and to Reset it to default
	 void init_menu() { init_menu(menu_program); } ///< use onw menu

	 void select_Clickable(nana::widget& wdg, nana::menu& your_menu) ///< the widget to trigget
	 {
		 wdg.events().mouse_down(nana::menu_popuper(your_menu));
	 }
	 void select_Clickable(nana::widget& wdg)
	 {
		 select_Clickable(wdg, menu_program);
	 }

	 std::string set_in_use_div_text_as_default() 	 { return def_layout = layout = me.div(); }
	 std::string set_default(std::string div_text)   { return def_layout = div_text; }
	 std::string reset_div_text_to_default()         { if (div(def_layout)) collocate(); return def_layout; }

	 bool div() try
	 {
		 me.div(layout);
		 return true;
	 }
		 catch (std::exception& e)
		 {
			 (nana::msgbox(me.window_handle(), "std::exception ocurred setting the editable layout ")
				 .icon(nana::msgbox::icon_error)
				 << "\n   in widget: " << nana::API::window_caption(me.window_handle())
				 << "\n   trying layout: \n " << layout
				 << "\n\n Occurred exception: \n\n" << e.what()
				 ).show();
			 return false;
		 }
		 catch (...)
		 {
			 (nana::msgbox(me.window_handle(), "An uncaptured exception ocurred setting the editable layout ")
				 .icon(nana::msgbox::icon_error)
				 << "\n   in widget: " << nana::API::window_caption(me.window_handle())
				 << "\n\n   trying layout: \n\n " << layout
				 ).show();
			 return false;
		 }
	 
	 bool div(std::string div_text) { layout = div_text; return div(); }


	 bool collocate() try  ///< set my div-text layout and collocate the place
	 {
	     me.collocate();
		 return true;
	 }
		 catch (std::exception& e)
		 {
			 (nana::msgbox(me.window_handle(), "std::exception during editable Widget collocation: ")
				 .icon(nana::msgbox::icon_error)
				 << "\n   in widget: " << nana::API::window_caption(me.window_handle())
				 << "\n   trying to layout: \n " << layout
				 << "\n\n Occurred exception: \n\n" << e.what()
				 ).show();
			 return false;
		 }
		 catch (...)
		 {
			 (nana::msgbox(me.window_handle(), "An uncaptured exception during editable Widget collocation: ")
				 .icon(nana::msgbox::icon_error)
				 << "\n   in widget: " << nana::API::window_caption(me.window_handle())
				 << "\n\n   trying to layout: \n\n " << layout
				 ).show();
			 return false;
		 }

	 bool test_collocate(std::string  try_layout)  ///< temporaly set this layout and collocate the place
	 {
		 layout.swap(try_layout);
		 bool res = div() && collocate();
		 layout.swap(try_layout);
		 return res;
	 }


 private:
	nana::place&          me;
	std::filesystem::path def_layout_file;
	nana::menu	          menu_program;
	std::string           layout, def_layout;
	std::unique_ptr<edit_place_form>       my_edit_form ;

};


#endif 