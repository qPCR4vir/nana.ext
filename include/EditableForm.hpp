/**
* Copyright (C) 2013-2019, Ariel Vina Rodriguez ( arielvina@yahoo.es )
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*
*  @file  nana.ext\include\EditableForm.hpp
*
*  @author Ariel Vina-Rodriguez (qPCR4vir)
*
*  @brief Provide base classes for GUI forms and controls (nana widgets)
*
* Extension to nana. From: https://github.com/qPCR4vir/nana.ext
*
* To be used together with:
*
*  - the Nana C++ GUI library, from: https://github.com/cnjinhao/nana
*
*/

#ifndef NANA_GUI_EditableForm_HPP
#define NANA_GUI_EditableForm_HPP

#include <iostream> 
#include <fstream> 
#include <cassert>

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/filebox.hpp>       

//#define USE_vPLACE 1

#if defined(USE_vPLACE)

#include <../../nana.ext/include/vplace.hpp>
namespace nana 
{
   using place=vplace;
}

#else

#include <nana/gui/place.hpp>

#endif



 std::ostream& operator<<(std::ostream& o,const nana::rectangle &r);
//{ o<<" rect("<<r.x<<","<<r.y<<","<<r.width <<","<<r.height <<")\n"; return o;}

/// \todo implement use
class EnablingEditing
{
 private:
    static bool _globalBlockInteratctiveEdition, _globalBlockConfig ;
           bool       _BlockInteratctiveEdition,       _BlockConfig ;
 public:
    static bool  globalBlockInteratctiveEdition(bool block=_globalBlockInteratctiveEdition)
    {
        return _globalBlockInteratctiveEdition=block;
    }
    static bool  globalBlockConfig(bool block=_globalBlockConfig)
    {
        return _globalBlockConfig=block;
    }
    bool  BlockInteratctiveEdition() const
    {
        return _BlockInteratctiveEdition;
    }
    bool  BlockConfig() const 
    {
        return _BlockConfig;
    }
    bool  BlockInteratctiveEdition(bool block)
    {
        return _BlockInteratctiveEdition=block;
    }
    bool  BlockConfig(bool block)
    {
        return _BlockConfig=block;
    }
};

class EditLayout_Form;


/// add functionality of editable layout at runtime \todo redesign to be member no base class
class EditableWidget: public EnablingEditing
{
 public:
    EditableWidget ( nana::widget& thisEdWd,      ///< the form or panel, owner of place and all other widgets of the editable widget
                     std::string Titel,			  ///<  todo: we need this??	
                     const std::filesystem::path &DefLayout_FileName=""           );

    static  void Click(nana::window w)
		{
			nana::arg_click ei;
			ei.window_handle = w;
			ei.mouse_args = nullptr;
			/// \todo revise 
			//ei.by_mouse = true; //    ????    .evt_code = nana::event_code::mouse_down;			// ei.pos.x=  ei.pos.y = 1;			// ei.left_button = true;			// ei.ctrl = ei.shift = false;
			nana::API::emit_event(nana::event_code::click,w, ei);
		}
	// todo: public???
    nana::widget   &_EdWd;                 ///< the form or panel, owner of place and all other widgets of the editable widget
	nana::place	    _place{_EdWd};                         //      nana::vplace	_place;
	std::filesystem::path     _DefLayout_FileName;
    std::string     _myLayout, _DefLayout;
	EditLayout_Form*    _myEdLayForm{nullptr};    	//std::unique_ptr <EditLayout_Form> _myEdLayForm;
	std::string	    _Titel;                    //  ???? todo: eliminate this

	/// another function: menu --> todo: move to other class
	nana::menu	    _menuProgram;

	/// another function: validation --> todo: move to other class
    std::vector<std::function<bool(void)>> _validate, _validated;
    bool changed{false}, validated{true};
    bool validate_only(/*bool validate_only=true*/)
    {
        try
        {
            for(auto &v:_validate)
               if( !v()) return false;                /// \todo: change to return bool: validated &= v();
            return true;
        }
        catch ( ... )
        { 
            std::cerr << "\nError in Validate of "<< _Titel;
            return false; 
        }
    }
    bool Validated()
    {
        try
        {
            for ( auto &v : _validated )
                validated &= v ();             /// \todo: change to return bool: validated &= v();   ???? actualize validate ????????
            return validated;
        }
        catch ( ... )
        { 
            std::cerr << "\nError in Validated of " << _Titel;
            return false; 
        }
    }
    bool Validate(bool _validate_only=false)
    {
        bool validate{false};
        if (validate=(validate_only() && !_validate_only))
              Validated();    /// return ?????
        return validate;
    }
	virtual    void add_validate(const std::function<bool(void)>& v)
		{
			_validate.push_back (v); 
		}
	virtual    void add_validated(const std::function<bool(void)>& v)
		{
			_validated.push_back (v); 
		}

    virtual     ~EditableWidget     ();
    virtual void SetDefLayout       ()=0;
    virtual void AsignWidgetToFields()=0;

	void InitMyLayout       ()
	{   
        SetDefLayout   ();
        _myLayout= _DefLayout;
        std::string lay_from_file;
        readLayout( _DefLayout_FileName.string(), lay_from_file);
        if (lay_from_file.empty() )
            lay_from_file=_DefLayout;

        AsignWidgetToFields();
        //_place.div(_myLayout.c_str ());     
        //_place.div(lay_from_file.c_str ());     
	    //_place.collocate ();
        //ReCollocate( lay_from_file );  // ???????????????????????????????????????????????????????????????????
        InitDiv( lay_from_file );  // ???????????????????????????????????????????????????????????????????
	}

    void InitMenu   (nana::menu& menuProgram)
    {
       menuProgram.append("&Edit this windows Layout",[&](nana::menu::item_proxy& ip)
	                                                            {EditMyLayout(); }                  );
       menuProgram.append("&Reset this windows default Layout",[&](nana::menu::item_proxy& ip)
	                                                            {ResetDefLayout(); ReCollocate( );} );
    }

    void SelectClickableWidget(nana::widget& wdg, nana::menu& menuProgram)
    {
        wdg.events().mouse_down (nana::menu_popuper(menuProgram) );   
    }

    void SelectClickableWidget(nana::widget& wdg)
    {
        SelectClickableWidget(wdg, _menuProgram);
    }


    void ResetDefLayout()
    {
        _myLayout=_DefLayout;
        //ReCollocate( );
                //_place.div(_myLayout.c_str ());     //    ?????????????????

    }
 
	void ResetDefLayout( std::string  Layout)
    {
        _DefLayout.swap(Layout);
        ResetDefLayout();
        ReCollocate( );
    }

    const std::string& DefLayout() const
    {
        return _DefLayout;
    }

 	void         EditMyLayout   (/*nana::widget & EdWd_own, nana::widget &EdLyF_own*/);

    static const char* readLayout(const std::string& FileName, std::string& Layout);

    void ReCollocate( std::string  Layout)
    {
        _myLayout.swap(Layout);
        try 
        {
            ReCollocate( );
        }
        catch(std::exception& e)
        {
             (nana::msgbox(_EdWd, "std::exception during EditableWidget ReCollocation: ")
                    .icon(nana::msgbox::icon_error)
                                 <<"\n   in widget: "  << nana::API::window_caption( _EdWd)
                                 <<"\n   Title: "      << _Titel
                                 <<"\n   owned by: "   << nana::API::window_caption(_EdWd)
                                 <<"\n   trying to layout: \n "   << _myLayout
                                 <<"\n   occurred exception: "     << e.what() 
             ).show();
        }
		catch(...)
		{
             (nana::msgbox(_EdWd, "An uncaptured exception during EditableWidget ReCollocation: ")
                    .icon(nana::msgbox::icon_error)
                                 <<"\n   in widget: "  << nana::API::window_caption( _EdWd)
                                 <<"\n   Title: "      << _Titel
                                 <<"\n   owned by: "   << nana::API::window_caption(_EdWd)
                                 <<"\n   trying to layout: \n "   << _myLayout
             ).show();
	    }
        _myLayout.swap(Layout); /// call ReCollocate again???
	}
    void ReCollocate( )
    {
        _place.div(_myLayout.c_str() );     
        //_place.div(_myLayout );

	    _place.collocate ();

    }
    void InitDiv( std::string  Layout)
    {
        _myLayout.swap(Layout);
        try 
        {
            InitDiv( );
        }
        catch(std::exception& e)
        {
             (nana::msgbox(_EdWd, "std::exception during EditableWidget InitDiv: ")
                    .icon(nana::msgbox::icon_error)
                                 << "\n   in widget: "  << nana::API::window_caption( _EdWd)
                                 << "\n   Title: "      << _Titel
                                 << "\n   owned by: "   << nana::API::window_caption(_EdWd)
                                 << "\n   trying to layout: \n "   << _myLayout
                                 << "\n   occurred exception: "     << e.what() 
             ).show();
        }
		catch(...)
		{
             (nana::msgbox(_EdWd,  "An uncaptured exception during EditableWidget InitDiv: ") 
                    .icon(nana::msgbox::icon_error)
                                 << "\n   in widget: "   << nana::API::window_caption( _EdWd)
                                 << "\n   Title: "       << _Titel
                                 << "\n   owned by: "    << nana::API::window_caption(_EdWd)
                                 << "\n   trying to layout: \n "    << _myLayout
             ).show();
	    }
        _myLayout.swap(Layout); /// call InitDiv again???
	}
    void InitDiv( )
    {
        _place.div(_myLayout.c_str() );     
        //_place.div(_myLayout );     
	    //_place.collocate ();

    }
};


class EditableForm: public EditableWidget
{ public:
    EditableForm ( nana::window EdWd_owner,       ///< The owner of the form or panel 
                   nana::widget& thisEdWd,        ///< the form or panel, owner of place and all other widgets of the editable widget
                   std::string Title,             ///< the title or caption displayed on top of the windows
                   const std::string &DefLayoutFileName=""           
		);

	nana::menubar	_menuBar;
	nana::menu*	_menuProgramInBar;
    //virtual ~EditableForm();

    void AddMenuProgram ()
    {
        assert (!_menuProgramInBar );
        _menuProgramInBar=&_menuBar.push_back("&Program");
        InitMenu   (*_menuProgramInBar);
    }

    void InitMyLayout       ()
	{   try{
				EditableWidget::InitMyLayout();
				//_place.div(_myLayout.c_str ());     

				ReCollocate( );
		}
		catch (std::exception & e)
		{
			throw std::runtime_error(std::string("An error occurred during initialization of the windows layout of ")+this->_Titel + "\n" + e.what());
		}
		catch (...)
		{
			throw std::runtime_error(std::string("An unknown error occurred during initialization of the windows of ") + this->_Titel + "\n" );
		}
	}

};

//#include <../temp/CompoWidget.hpp>

class CompoWidget : public  nana::panel<false> , public EditableWidget  
{public:
	CompoWidget ( nana::window parent,              ///< The owner of the panel 
                  std::string Titel, 
                  const std::string &DefLayoutFileName=""
		);
};

/// \todo use fs::path
class FilePickBox : public  CompoWidget
{	nana::label	    _label   {*this};
	nana::combox	_fileName{*this};    //   Only temporal public   !!!!!!!!!!!!!!!!!!!!!!!!!!!
	nana::button	 Pick    {*this, "..."};

	nana::filebox   fb_p    {*this, true};
    nana::folderbox folb_p  {*this};

    void SetDefLayout       () override ;
    void AsignWidgetToFields() override ;
	void		pick(const std::string &file_tip="");

 protected:
	void select_file(nana::filebox&     fb,
	                 const std::string &action,
	                 const std::string &file_tip,
	                 bool select_only=false);
    void select_dir (nana::folderbox&     fb,
                     const std::string &action,
                     const std::string &file_tip,
                     bool select_only=false);
    bool                _user_selected { false }, 
		                _validate_only { false },
                        _canceled      { false };

 public:
    bool            folder {false};
	FilePickBox     (	nana::window parent,
						const std::string   &label,
						const std::string   &DefLayoutFileName=""
		);

    void SetDefLayout       (unsigned lab) ;
    void ResetLayout        (unsigned lab )
    {
        SetDefLayout       (lab );
        ResetDefLayout();  
        ReCollocate( );    
    }

    virtual FilePickBox& add_filter(const std::string& description, const std::string& filetype)
	{ 
		fb_p.add_filter(description, filetype);
        return *this;
	}
            
    using filtres = std::vector<std::pair<std::string, std::string>>;

	virtual FilePickBox& add_filter(const filtres &filtres)
        {
            fb_p.add_filter(filtres );
            //for (auto &f : filtres)
            //    add_filter(f.first, f.second);
            return *this;
        };
    void        onSelectFile( std::function<void(const std::string& file)> slt)
	{	 
        add_validate([this, slt](/*nana::combox&cb*/)
                    { 
                      slt ( this->FileName() ) ;
                      return true;   // or catch exception to said false
                    } ); 
        //_fileName.ext_event().selected = (

  //      _fileName.ext_event().selected = [&]()
		//{
		//    if(! _OSbx.UserSelected()) return;
  //          std::string   fileN= FileName();  // The newly selected name
  //          //std::wcout<<std::endl<<("Selected: ")<<fileN<<std::endl;   // debbug
		//	OpenFileN(fileN );
		//};
 	}

	std::string FileName()const						
	{  return _fileName.caption();}

	void		 FileName(const std::string&  FileName)
    { 
		/*std::cout << "/n Setting filename: " << FileName << " in FilePickBox: "
			<< this->_Titel;
		std::cout << " /n Original caption: " << _fileName.caption();*/
		_fileName.push_back(FileName); 
		_fileName.option(_fileName.the_number_of_options() - 1);
        //std::cout << " /n Final caption: " << _fileName.caption();
		nana::API::update_window (_fileName);
    }

	void		 FileNameOnly(const std::string&  FileN )  /// validate only
    { 
        bool  vo{ true };
        std::swap(vo,_validate_only);
        FileName ( FileN  ) ;
        std::swap(vo,_validate_only);
    }

    void         FileNameOpen(const std::string&  item)  /// validate and validated
    {
        bool us{ false }, vo{ false };
        //std::swap(us,_user_selected); 
        std::swap(vo,_validate_only);
        FileName(item) ;
        //std::swap(us,_user_selected); 
        std::swap(vo,_validate_only);
    }

    bool        UserSelected() const {return _user_selected ;}

    bool        Canceled()     const {return _canceled;}

    //nana::widget& _file_w()
    //{
    //    return _fileName;
    //}
};

/// \todo use fs::path
class OpenSaveBox : public  FilePickBox
{
    nana::button	Open{*this, "Open" }, 
                    Save{*this, "Save"};

	nana::filebox  fb_o{*this, true },                      //   Only temporal public   !!!!!!!!!!!!!!!!!!!!!!!!!!!
                   fb_s{*this, false };

    void SetDefLayout       () override ;
    void AsignWidgetToFields() override ;

public:
	OpenSaveBox     (	nana::window parent, 
						const std::string   &label,
						const std::string   &DefLayoutFileName="" );

	OpenSaveBox& add_filter(const std::string& description, const std::string& filetype) override
	{ 
		FilePickBox::add_filter(description, filetype);
		fb_o.add_filter(description, filetype);
		fb_s.add_filter(description, filetype);
        return *this;
	}
	OpenSaveBox& add_filter(const filtres &filtres) override
	{ 
		FilePickBox::add_filter(filtres);
		fb_o.add_filter(filtres);
		fb_s.add_filter(filtres);
        return *this;
	}

    OpenSaveBox& onOpenAndSelect(std::function<bool( )> opn)    {    add_validated( opn);  return *this; }
    OpenSaveBox& onSave         (std::function<void( )> sve)	{	 _onSave_     ( sve);  return *this; }

    void OpenClick() 	{Click(Open);}
	void SaveClick() 	{Click(Save);}

    OpenSaveBox& onOpenAndSelectFile(std::function<void(const std::string& file)> opn)
    {
        add_validated([this, opn](/*nana::combox&cb*/)
                    { 
                      if( this->UserSelected() )   
                          opn ( this->FileName() ) ;
                      return true;
                    } ); 
        
        return *this;
    }
	
    void		open(const std::string &file_tip =""); 
    void		save(const std::string &file_tip = "",  const std::string &action="");
    
    nana::event_handle onOpenFile(std::function<void(const std::string& file)> opn)
    {
        return Open.events().click([this, opn]()
                    { 
                      if( ! this->Canceled () )   
                         opn ( this->FileName() ) ; 
                    } );
 	}
    nana::event_handle onOpen    (std::function<void(                       )> opn)
	{	 
        return Open.events().click([this, opn]()
                    { 
                      if( ! Canceled () )   
                         opn (  ) ; 
                    } );
 	}
    nana::event_handle onSaveFile(std::function<void(const std::string& file)> sve)
	{	 
        return Save.events().click ([this,sve]()
                    { 
                      if( ! Canceled () )   
                         sve ( FileName() ) ; 
                    } );
 	}
    nana::event_handle _onSave_  (std::function<void(                       )> sve)
	{	 
        return Save.events().click([this,sve]()
                    { 
                      if( ! Canceled () )   
                         sve (  ) ; 
                    } );
 	}

};

class EditLayout_Form : public nana::form, public EditableForm
{
    EditableWidget &_owner;   /// intercambiar nombre con owner de EditableWidget
	OpenSaveBox     _OSbx       {*this, "Layout:" };
	nana::button	_ReCollocate{*this, "Apply"	  },   _hide{*this, "Hide"	    }, 
                    _panic      {*this, "Panic !" },   _def {*this, "Default"  }, 
                    _cpp        {*this, "C++ code"};
    nana::textbox	_textBox    { *this };
    nana::menu	      &_menuFile        {_menuBar.push_back("&File")};
    nana::event_handle _hide_not_unload { make_hidable()};  // hide_(),

public:
	EditLayout_Form (EditableWidget &EdWd_owner , int i=0);

    void make_closable()
    { 
         //assert((     std::cerr<<"\nMaking Closeable EditLayout_Form: "   , true) );;   // debbug
         //assert((     std::wcerr<< this->caption()  , true ) ); ;  // debbug
 
        if (_hide_not_unload) 
        {
            umake_event ( _hide_not_unload);
            _hide_not_unload = nullptr;
        }
    }

    ~EditLayout_Form()
    {
          //assert((    std::cerr<<"\nDestroying EditLayout_Form: " , true   ));;   // debbug
          //assert((    std::wcerr<< this->caption()  , true  )); ;  // debbug
        //umake_event ( hide_);
        make_closable();
    }

 private:
    void SetDefLayout       () override ;
    void AsignWidgetToFields() override ;
    void on_edited();
	void InitCaptions();

    nana::event_handle make_hidable()
    { 
        //assert((    std::cerr<<"\nMaking Hidable EditLayout_Form: " , true ) );; // debbug
        //assert((    std::wcerr<< this->caption() , true ) ); ; // debbug

        return events().unload ([this](const nana::arg_unload  & ei)
        {
            //assert((    std::cerr<<"\n Hiding, not closing EditLayout_Form: "  , true) );;  // debbug
            //assert((    std::wcerr<< this->caption()  , true) );; // debbug

            ei .cancel = true;    //Stop closing and then
            hide();
        });
    };
    void MakeResponsive();
	void ReLayout ();
    void ReloadDef();
	void OpenFile ();
	void OpenFileN(const std::string   &file="");
	void SaveFileN(const std::string   &fileTip="" , const std::string   &tmp_title = std::string{} );
    void ForceSave(const std::string   &file);
    void SaveFile(){     // temporal !!!!!!!!!!!!!!
        if (!_OSbx.Canceled())
            ForceSave(_OSbx.FileName());
    };
    void toCppCode();
}	;
#endif 

				
