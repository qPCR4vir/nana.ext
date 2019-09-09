/**
* Copyright (C) 2013-2018, Ariel Vina Rodriguez ( arielvina@yahoo.es )
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*
*  @file  nana.ext\src\CompoWidget.cpp
*  @autor Ariel Vina-Rodriguez (qPCR4vir)
*  @brief
*/

#include <../../nana.ext/include/EditableForm.hpp>

#include <iostream>    // temp, for debugging
#include <fstream>     // temp, for debugging

FilePickBox::FilePickBox (nana::window parent, 
						  const std::string   &label,
						  const std::string   &DefLayoutFileName )
				:	CompoWidget(parent, label, DefLayoutFileName) 
{
    _label.caption(caption());
    _label.text_align(nana::align::right  ); 

    fb_p.title(("Pick ") + caption());

	Pick.events().click([&](){pick(FileName());}	); 

	_fileName.editable(true);

    InitMyLayout();
    SelectClickableWidget( _label);

    _fileName .events().selected   ([this](const nana::arg_combox& arg_cb)
            { 
            //assert((  std::cerr<< "\nBefore calling Validate,in select FilePickBox._fileName: " , true  ));;
            //assert((  std::wcerr<< caption() << std::endl , true  ));;
                      
                //if( this->UserSelected() )   
                    this->Validate(this->_validate_only);
            } );
    _fileName.events().focus([this](const nana::arg_focus & ei)
        {  
            //assert((  std::cerr<< "\nBefore calling validating_only," << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , FilePickBox._fileName: " , true  ));;
            //assert((  std::wcerr<< caption() << std::endl , true  ));;
            
            if (!ei .getting) 
                          this->validate_only();
        });


    _user_selected=true;
}
    void FilePickBox::SetDefLayout       () 
    {
       SetDefLayout       (49); 
    }

    void FilePickBox::SetDefLayout       (unsigned lab) 
{
    std::stringstream lay;
    lay<<
        "vertical   <weight=1>    \n"
        "           <weight=20 <weight=3><weight="<<lab<<"   vertical  <><weight=15 label><>     ><weight=1>     \n"
        "					   <cbFL >       \n"
        "					   <pick weight=30>  \n"
        "					   <weight=3> 	>" 
        "            <weight=2>    \n"          ;  
    _DefLayout=lay.str();    //ResetDefLayout();
}


    void FilePickBox::AsignWidgetToFields() 
{
	_place.field("cbFL"        ) << _fileName ;
	_place.field("label"       ) << _label;
	_place.field("pick"        ) << Pick;
}
void FilePickBox::pick(const std::string &file_tip)
{
    bool  vo{ true };
    std::swap(vo,_validate_only);
    if (folder)
        select_dir(folb_p, (""), file_tip,true);
    else
        select_file( fb_p, (""), file_tip,true);
    std::swap(vo,_validate_only);
}
void FilePickBox::select_dir(nana::folderbox   &fb,
                             const std::string &action,
                             const std::string &file_tip,
                             bool               select_only)
{
    std::string old_t;
    //if (!action.empty())
    //    old_t=fb.title(action);
    //fb.init_file(file_tip);

    if(auto path=fb(); ! path.empty())
    {
        select_only ? FileNameOnly (path[0].string()) : FileNameOpen (path[0].string());
        _canceled= false;
    }
    else
        _canceled= true;
    //if (!action.empty()) // revisar !!
    //    fb.title(old_t);
}
void FilePickBox::select_file(nana::filebox&  fb, const std::string &action, const std::string &file_tip, bool select_only)
{
    //std::string old_t;
    //if (!action.empty())
    //{
    //    //old_t = fb.title();
    //    fb.title(action);
    //}

    fb.init_file(file_tip); 
	if(auto path=fb(); ! path.empty())
	{	
        select_only ? FileNameOnly (path[0].string()) : FileNameOpen (path[0].string());
        _canceled= false;
    }
    else 
        _canceled= true;

    /*if (!action.empty()) // revisar !!
        fb.title(old_t);*/
 }


OpenSaveBox::OpenSaveBox (nana::window parent, 
						  const std::string   &label,
						  const std::string   &DefLayoutFileName )
				:	FilePickBox(parent, label, DefLayoutFileName) 
{
    fb_o.title(("Open ") + caption());
    fb_s.title(("Save ") + caption());

    Open.events().click ([&](){open(FileName());}	);
	Save.events().click ([&](){save(FileName());}    );

    InitMyLayout();
}
    void OpenSaveBox::SetDefLayout       () 
{
    _DefLayout= 
        "vertical   <weight=1>    \n"
        "           <weight=20 <weight=3><weight=49    vertical <>                                       \n"
        "                                                       <weight=15 label >                       \n"
        "                                                       <>               ><weight=1>      \n"
        "		               <weight=74 proj_buttons gap=1>                                     \n"
        "					   <cbFL >       \n"
        "					   <weight=30 pick >  \n"
        "					   <weight=3> 	>" 
        "            <weight=2>    \n"          ;  
}
    void OpenSaveBox::AsignWidgetToFields() 
{
	_place.field("proj_buttons") << Open << Save;
    //FilePickBox::AsignWidgetToFields() ;
}
	
void OpenSaveBox::open(const std::string &file_tip)
{
    bool us{ false }, vo{ false };
    std::swap(vo,_validate_only);
	select_file( fb_o, (""), file_tip,false);
    std::swap(vo,_validate_only);
}
void OpenSaveBox::save(const std::string &file_tip,  const std::string &action)
{
    bool  vo{ true };
    std::swap(vo,_validate_only);
	select_file( fb_s, action , file_tip, true);
    std::swap(vo,_validate_only);
}

