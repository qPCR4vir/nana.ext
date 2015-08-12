/**
* Copyright (C) 2013-2015, Ariel Vina Rodriguez ( arielvina@yahoo.es )
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*
*	@file nana.ext\src\EditableForm.cpp
*  @autor Ariel Vina-Rodriguez (qPCR4vir)
*  @brief
*/
#include <../../nana.ext/include/EditableForm.hpp>
//#include <../../nana.ext/include/CompoWidget.hpp>

#include <nana/gui/widgets/textbox.hpp>

#include <iostream> 
#include <fstream> 

// std::ostream& operator<<(std::ostream& o,const nana::rectangle &r)
//{ o<<" rect("<<r.x<<","<<r.y<<","<<r.width <<","<<r.height <<")\n"; return o;}
//

    EditableWidget::EditableWidget  ( nana::window EdWd_owner,   ///< The ownwer of the form or panel: nullptr for "primary" forms 
                                      nana::widget& thisEdWd,  ///< the form or panel, owner of place and all other widgets of the editable widget
                                      nana::string Titel, 
                                      const nana::string &DefLayoutFileName)
            :  
               _EdWd_owner (EdWd_owner), 
               _thisEdWd   (thisEdWd), 
               _place      (_thisEdWd),    
               _Titel(std::move(Titel)),        //   ???
               _DefLayoutFileName(DefLayoutFileName) 
     {  
         //nana::rectangle r;  //debugg
      //  r=nana::API::window_size(ThisWidget);  //debugg
      //  //std::cerr<< "\nplace::implement::implement(window parent_widget [ "<<parent_widget<<" ]) with area: "<<r;  //debugg
      //  std::cerr<< "\nEditableWidget(parent_widget [ "<< std::string(nana::charset ( _Titel))<<" ]) with area: "<<r;  //debugg
   //      EditableWidget::~EditableWidget()
   //     {
   //         std::cerr<<"\nDestroying Editable Widget: ";    // debbug
   //         std::wcerr<< this->_Titel ;   // debbug
			//if (_myEdLayForm) 
   //         {
   //              std::cerr<<"\nContaining EditLayout_Form: ";    // debbug
   //             std::wcerr<< _myEdLayForm->caption() ;   // debbug
   //            _myEdLayForm->Closable();
   //             _myEdLayForm->close();
   //         }
   //     }
        //std::cerr<<"\nConstructing EditableWidget: "; // debbug
        //std::wcerr<< this->_Titel; // debbug

   //     ThisWidget.make_event<nana::events::unload>([this](const nana::eventinfo& ei)
   //     {
   //     std::cerr<<"\nClosing EditableWidget: "; // debbug
   //     std::wcerr<< this->_Titel; // debbug
			//if (_myEdLayForm) 
   //         {
   //              std::cerr<<"\nContaining EditLayout_Form: ";    // debbug
   //             std::wcerr<< _myEdLayForm->caption() ;   // debbug
   //            _myEdLayForm->Closable();
   //             _myEdLayForm->close();
   //         }
   //     });

        _thisEdWd.caption(_Titel);       //   ???
        InitMenu   (_menuProgram);
    }

	CompoWidget::CompoWidget (nana::window parent,            ///< The ownwer of the CompoWidget, that is: the owner of the CompoWidget�s form or panel 
                              nana::string Titel, 
                              const nana::string &DefLayoutFileName)
        :  nana::panel<false>(parent),  
           EditableWidget( parent,                                  ///< The ownwer of the form or panel 
                           *this,               ///< the form or panel, owner of place and all other widgets of the editable widget
                           Titel, DefLayoutFileName)
    {
        
            //std::cerr<<"\nConstructing CompoWidget: "; // debbug
        //std::wcerr<< this->_Titel;                 // debbug
                      //   ???????????????????????????????????????????????????????????????????????????????????
   //     EdWd_owner.make_event<nana::events::unload>([this](const nana::eventinfo& ei)
   //     {
   //         //std::cerr<<"\nClosing CompoWidget: "; // debbug
   //         //std::wcerr<< this->_Titel;            // debbug

			//if (_myEdLayForm) 
   //         {
   //              //std::cerr<<"\nContaining EditLayout_Form: ";    // debbug
   //              //std::wcerr<< _myEdLayForm->caption() ;          // debbug
   //             _myEdLayForm->Closable();
   //             _myEdLayForm->close();
   //         }
   //     });

    }

EditableForm::EditableForm ( nana::window EdWd_owner,                       ///< The ownwer of the form or panel 
                             nana::widget& thisEdWd,    ///< the form or panel, owner of place and all other widgets of the editable widget
                             nana::string Titel, 
                             const nana::string &DefLayoutFileName         ) 
            :  EditableWidget( EdWd_owner,                                  ///< The ownwer of the form or panel 
                               thisEdWd,               ///< the form or panel, owner of place and all other widgets of the editable widget
                               Titel, DefLayoutFileName),
              _menuBar (thisEdWd), 
              _menuProgramInBar(nullptr)
     {
         thisEdWd.caption(_Titel);
        //std::cerr<<"\nConstructing EditableForm: "; // debbug
        //std::wcerr<< this->_Titel; // debbug

   //     thisEdWd.make_event<nana::events::   unload>([this](const nana::eventinfo& ei)
   //     {
   //         //std::cerr<<"\nClosing EditableForm: "; // debbug
   //         //std::wcerr<< this->_Titel;             // debbug

			//if (_myEdLayForm) 
   //         {
   //              //std::cerr<<"\nContaining EditLayout_Form: ";    // debbug
   //              //std::wcerr<< _myEdLayForm->caption() ;          // debbug
   //              _myEdLayForm->Closable();
   //              _myEdLayForm->close();
   //         }
   //     });
    }

bool EnablingEditing::_globalBlockInteratctiveEdition=false;
bool EnablingEditing::_globalBlockConfig             =false;

void EditableWidget::EditMyLayout(/*nana::widget & EdWd_own, nana::widget &EdLyF_own*/)
		{
			if (!_myEdLayForm) 
				_myEdLayForm = new EditLayout_Form ( *this,0 ) ;
                //_myEdLayForm = nana::detail::bedrock::instance().rt_manager.create_form<EditLayout_Form, EditableWidget, int>(*this, 0);
                //_myEdLayForm = std::addressof(nana::form_loader<EditLayout_Form, true>() (*this, int{}));
				//_myEdLayForm.reset (new EditLayout_Form (  wd ));
			_myEdLayForm->show ();
		}
 	//void         EditMyLayout   (nana::widget & EdWd_own, nana::widget &EdLyF_own);

EditableWidget::~EditableWidget()
        {
            //std::cerr<<"\nDestroying Editable Widget: ";    // debbug
            //std::wcerr<< this->_Titel ;   // debbug
			if (_myEdLayForm) 
            {
                // std::cerr<<"\nContaining EditLayout_Form: ";    // debbug
                //std::wcerr<< _myEdLayForm->caption() ;   // debbug
               //_myEdLayForm->make_closable();
                delete _myEdLayForm/*->close()*/;
            }
        }



EditLayout_Form::EditLayout_Form  (	EditableWidget &EdWd_owner, int i)
		:nana::form (EdWd_owner._thisEdWd , nana::rectangle( nana::point(300,100), nana::size(500,300) )),
         EditableForm ((EdWd_owner._thisEdWd), *this,  STR("Editing Layout of: "),STR("Layout_Form.lay.txt")),
         _owner(EdWd_owner)
	{	
        caption(_Titel += _owner._Titel) ;  
		_textBox.tip_string		(STR("type or load a Layout to be applied to the calling window..."		));
		InitMyLayout();

		_textBox.editable(true);
		_OSbx.add_filter(STR("Layout File"), STR("*.lay.txt"));

	    if   ( _owner._myLayout.empty())    
        {    if (! _owner._DefLayoutFileName.empty())
             {   _OSbx.FileName	(   _owner._DefLayoutFileName  );
                 OpenFileN( _owner._DefLayoutFileName );
             }
        } else   		          
        {   _textBox.append(nana::string(nana::charset(_owner._myLayout)),false );
            _textBox.select(true);
            _textBox.show();

             if (! _owner._DefLayoutFileName.empty())
                _OSbx.FileName	(   _owner._DefLayoutFileName  );
        }

		MakeResponsive();
        //ReCollocate();
	}

void EditLayout_Form::InitCaptions()
	{
	}
void EditLayout_Form::MakeResponsive()
	{
        _OSbx.onOpenAndSelectFile([this]( const nana::string   &file){ this->OpenFileN(file) ;} );
		_OSbx.onSaveFile         ([this]( const nana::string   &file){ this->ForceSave(file) ;} );

        _textBox.events().first_change(  [&](){on_edited();});
        //_textBox.events().click([&](const nana::eventinfo& ei)
        //{
        //   if (ei.mouse.right_button)
        //   {
        //       std::wcout<<std::endl<<STR("Rigth Click: x,y=")<<ei.mouse.x<<STR(",")<<ei.mouse.y  <<std::endl;
        //       _menuProgram->popup (_textBox.handle(),ei.mouse.x,ei.mouse.y,false);
        //   }
        //   if (ei.mouse.left_button )         std::wcout<<std::endl<<STR("Left  Click")<<std::endl;
        //}); 
		_menuFile.append  (STR("&Open..."   ),[this](nana::menu::item_proxy& ip)  {  _OSbx.OpenClick(); } );
        _menuFile.append  (STR("&Save"      ),[this](nana::menu::item_proxy& ip)
        {  
            ForceSave(nana::string(nana::charset(_textBox.filename())) ) ;
        }   );
		_menuFile.append  (STR("Save &As..."),[this](nana::menu::item_proxy& ip)  {  _OSbx.SaveClick(); } );
         AddMenuProgram ();

         //InitMenu    ();
        _menuProgramInBar->append_splitter();
		_menuProgramInBar->append (STR("&Apply Layout to calling windows"         ),[&](nana::menu::item_proxy& ip) {ReLayout ();});
		_menuProgramInBar->append (STR("&Restet Default Layout to calling windows"),[&](nana::menu::item_proxy& ip) {ReloadDef();});

        SelectClickableWidget( _textBox, *_menuProgramInBar );
        SelectClickableWidget( _menuBar, *_menuProgramInBar);

        _panic      .events().click([&](){ _owner.ResetDefLayout(); _owner.ReCollocate( );}); 
        _def        .events().click([&](){ ReloadDef() ;}   ); 
        _hide       .events().click([&](){ hide()      ;}   ); 
        _cpp        .events().click([&](){ toCppCode() ;}   ); 
        _ReCollocate.events().click([&](){ ReLayout()  ;}   ); 

        _textBox.set_highlight("place_keywords", nana::colors::blue, nana::colors::white);
        _textBox.set_keywords ("place_keywords", true,true, { "arrange", "collapse", "gap", "grid", 
                                "margin", "min", "max", "repeated", "variable", "vertical", "vert", "weight", "horizontal" });
        _textBox.set_highlight("place_simbols", nana::colors::blue, nana::colors::yellow);
        _textBox.set_keywords ("place_simbols", true,false, {"<",">", "|", "%", "[","]" });

	}
void EditLayout_Form::on_edited()
{
   nana::string newTitel  = _Titel  +  STR(" <") ;
                newTitel +=  _textBox.filename() ;
                newTitel += (_textBox.edited() ? STR(" * >"): STR(">")  );
    caption	( newTitel);
}
void EditLayout_Form::SetDefLayout   ()
{
    _DefLayout=
        "vertical   gap=2                                    \n\t"
                            "<weight=25>                             \n\t"
                            "<weight=25  OpenSave>                   \n\t"
                            "<textBox>                               \n\t"
                            "<weight=25 <weight=15>                  \n\t" 
                            "           <re weight=50 gap=2>         \n\t"
                            "           <panic weight=50>            \n\t"
                            "           < >                          \n\t"
                            "           <def  gap=2 weight=120>      \n\t"
                            "           < >                          \n\t"
                            "           <hide weight=50>             \n\t"
                            "           <weight=15> >                \n\t" 
                            "<weight=5>                              \n\t";
}
void EditLayout_Form::AsignWidgetToFields() 
{
	_place.field("OpenSave"	   )<< _OSbx;
	_place.field("textBox"	   )<< _textBox;
	_place.field("re"		   )<< _ReCollocate ;
	_place.field("panic"	   )<< _panic ;
	_place.field("def"		   )<< _def << _cpp ;
	_place.field("hide"		   )<< _hide ;
}
void EditLayout_Form::ReLayout()
	{   nana::string lay,line;
		for (size_t linum=0; _textBox.getline(linum , line) ; ++linum )
			lay+=line;
        _owner.ReCollocate( std::string(nana::charset (lay)) );  // try std::runtime_error msgbox
	}
void EditLayout_Form::toCppCode()
{
    if ( _textBox.edited () )
        SaveFileN(nana::string(nana::charset(_textBox.filename())),STR("Do you want to save your edited Layout?")); 
    nana::string lay,line;
	for (size_t linum=0; _textBox.getline(linum , line) ; ++linum )
			lay+= STR("\t\"")+ line + STR("\t\\n\\t\"\n");

    _textBox.reset(lay );
    _textBox.select(true);
    _textBox.copy();
    _textBox.show();
}



void EditLayout_Form::ReloadDef()
{
    if ( _textBox.edited () )
        SaveFileN(nana::string(nana::charset(_textBox.filename())),STR("Do you want to save your edited Layout?")); 
    _owner.ResetDefLayout(); 
    _owner.ReCollocate( );
    _textBox.reset(nana::string(nana::charset(_owner._myLayout)) );
    _textBox.select(true);
    _textBox.show();
}

//void EditLayout_Form::OpenFile()
//	{	 
//      if(_OSbx.Canceled () ) return;
//      //std::wcout<<std::endl<<STR("OpenFile: ")<<std::endl;   // debbug
//
//	  OpenFileN(_OSbx.FileName());
//	}
//void EditLayout_Form::SaveFile()
//	{	
//      if( ! _OSbx.Canceled () ) 
//          ForceSave(_OSbx.FileName()  );
//	}
void EditLayout_Form::OpenFileN(const nana::string   &file)
	{	  
		if( file.empty() ) 
            return;
        //std::wcout<<std::endl<<STR("OpenFileN: ")<<file<<std::endl;   // debbug
        if ( _textBox.edited () )
            SaveFileN(_textBox.filename(), STR("Do you want to save your edited Layout?")); 
		_textBox.load( file );
        _textBox.select(true);
        _textBox.show();
        //std::wcout<<std::endl<<STR("OpenedFileN: ")<<file<<std::endl;   // debbug
}
void EditLayout_Form::SaveFileN(const nana::string   &fileTip, const nana::string   &tmp_title )
	{	
        //std::wcout<<std::endl<<STR("Seaving tip: ")<<fileTip<<std::endl;   // debbug
        _OSbx.save(fileTip, tmp_title);
        SaveFile();
	}
void EditLayout_Form::ForceSave(const nana::string   &file)
	{	
        ////std::wcout<<std::endl<<STR("Direct save file: ")<<file<<std::endl;   // debbug
		_textBox.store(file.c_str () );
		//assert(( std::wcout<<std::endl<<STR("SavedFIle: ")<<file<<std::endl               , true) );   // debbug
    }   
const char* EditableWidget::readLayout(const nana::string& FileName, std::string& Layout)
    {
		std::ifstream loy(FileName);
		std::string temp;
		while (std::getline(loy,temp)) Layout+=temp + "\n";
		//assert((     std::cout<<std::endl<< Layout   , true  ));;
		return Layout.c_str();
    }	


