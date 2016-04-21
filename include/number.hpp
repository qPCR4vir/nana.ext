/**
* Copyright (C) 2013-2016, Ariel Vina Rodriguez ( arielvina@yahoo.es )
*
*	Distributed under the Boost Software License, Version 1.0.
*	(See accompanying file LICENSE_1_0.txt or copy at
*	http://www.boost.org/LICENSE_1_0.txt)
*
*  @file  nana.ext\include\number.hpp
*
*  @author Ariel Vina-Rodriguez (qPCR4vir)
*
*  @brief Provide GUI controls (nana widgets) to represent numbers
*
* Extension to nana. From: https://github.com/qPCR4vir/nana.ext
*
* To be used together with:
*
*  - the Nana C++ GUI library, from: https://github.com/cnjinhao/nana
*
*/

#ifndef NANA_GUI_Number_HPP
#define NANA_GUI_Number_HPP
#pragma warning(disable : 4996)

//  From: https://github.com/qPCR4vir/nana.ext
#include <../../nana.ext/include/EditableForm.hpp>
#include <Units.hpp>


namespace nana {
 
class NumberLabel : public label
{
  public:
    NumberLabel (   widget &parent,    
                    double val=0, 
                    unsigned decimals=2,
                    unsigned width=6)
        :	label(parent),
			_val(val),  _decimals(decimals), _width(width)
    {
        display();
    }

    double    _val;
    unsigned  _decimals, 
		      _width;

    double    Value(          )const{                     return _val;}
    double    Value(double val)     {_val=val; display(); return _val;}

	void display()
	{
		std::string val(50,0);
		snprintf(&val[0],val.size(), (" %*.*f"), _width, _decimals, _val );
		caption (val.c_str());
	}
};


class NumberBox : public textbox
{
  public:
    NumberBox (   window parent,    
                    double val=0, 
                    unsigned decimals=2,
                    unsigned width=6)
        :	textbox(parent),
			_val(val),  _decimals(decimals), _width(width)
    {
        multi_lines(false);
        display();
        events().focus([&](const arg_focus  & ei)
                {  if (!ei.getting) 
                        validate_edit( );
                }); 
    }

    double    _val;
    unsigned  _decimals, 
		      _width;

    double Value(          )const{                    return _val;}
    double Value(double val)     {_val=val; display(); return _val;}

	void read()
	{
		try    {  _val=std::stod (caption()  );     }
		catch (...)     {;     }
	}

	void validate_edit()
	{
		read();
		display();
	}

	void display()
	{
		std::string val(50,0);
		snprintf(&val[0],val.size(), (" %*.*f"), _width, _decimals, _val );
		caption (val.c_str());
	}

};

class NumerUpDown : public  CompoWidget
{
    button      _up{*this, ("^")},   _down{*this, ("v")};  
    label       _label;
    double      _val, _min, _max, _step;
    unsigned    _decimals, _width;
 public:
    textbox     _num{*this};

   NumerUpDown (   widget &parent_,      const std::string &label,
                    double val,           double min, double max, 
                    const std::string         &DefFileName=("NumUpDown.VertCenter.lay.txt"),
                    double step=1,       unsigned width=6,    unsigned decimals=2  );

    double   Value    (         )const{              return _val;  }
    double   Min      (         )const{              return _min;  }
    double   Max      (         )const{              return _max;  }
    double   Step     (         )const{              return _step; }
    unsigned Width    (         )const{              return _width;}
    unsigned Decimals (         )const{              return _decimals;}
    double   Value    (double val)     
    { 
        auto old_v = _val;
        changed=false;

        // add_validate     // 
        if     (val < _min)   val = _min;
        else if(val > _max)   val = _max;
        if ( _val != val )
        {
            _val=val; 
            try{changed=Validate();} catch(...){}
            if (!changed )
                   _val=old_v;
        }
        display () ;  
        return _val;
    }
    double   Min      (double val)    { _min=val;  /*validate();*/   return _min;  }
    double   Max      (double val)    { _max=val;  /*validate(); */  return _max;  }
    double   Step     (double val)    { _step=val; /* ();*/          return _step; }
    unsigned Width    (unsigned val)  { _width=val;/* display ();*/  return _width;}
    unsigned Decimals (unsigned val)  { _decimals=val;/* display();*/return _decimals;}

    double read  ()
        {
            try{  return std::stod (_num.caption()  ); }
            catch (...)  {  return _val; }
        }
    void validate()
    {
        if     (_val < _min)   _val = _min;
        else if(_val > _max)   _val = _max;
        display();
    }
    void validate_edit()        {      Value (read());       }
    void add     (double step)  {      Value (step+Value()); }
    void display ()
    {
        std::string val(50,0);
        snprintf(&val[0],val.size(), (" %*.*f"), _width, _decimals, _val );
        _num.caption (val.c_str());
    }

    void SetDefLayout       () override
    {
        _DefLayout= "  <       <vertical weight=60 <><label weight=15 gap=1><> >      \n"
                    "          <vertical weight=50 <><Num weight=19><> >   \n"
                    "          <vertical weight=30 <><UpDown weight=19><> > \n"
                    "  > " ;
    }
     void AsignWidgetToFields() override
    {
	    _place.field("Num"    ) << _num ;
	    _place.field("UpDown" ) << _up << _down ;
	    _place.field("label"  ) << _label;
    }
};

class UnitPicker : public combox
{
 
	RTunits::unit_name             _defUnitName;
	RTunits::CUnit                 _defUnit{_defUnitName};
    const RTunits::magnitude_name  magnitude= RTunits::magnitude_name{_defUnit.magnitude};
  public: 
    UnitPicker(widget &wd, const RTunits::unit_name& def)
                :combox(wd), _defUnitName(def) 
    {
        editable(false);
        for(const RTunits::unit_name& un : RTunits::MagnitudesDic().at(magnitude) )
            push_back (  un  );     /*CUnit::UnitsDic().at(un).to_string ()*/ 
        caption( def  );
        //ext_event().selected=[&](combox& cb)
        //{
        //    _cb.caption(_cb.caption().substr(6, _cb.caption().find_first_of((" ="),6)-6 )); 
        //};
    }

    double to_def   (double val) ///< Convert a value in user selected Unit into Default Unit 
    {
        return RTunits::CUnit( caption()  ,  _defUnitName  ).conv (val);
    }
    double to_def   (double val, const RTunits::unit_name& un ) ///< Convert a value in Unit un into Default Unit 
    {
        return RTunits::CUnit(un ,  _defUnitName  ).conv (val);
    }
    double from_def (double val) ///< Convert a value in Default Unit into user selected Unit 
    {
        return RTunits::CUnit( _defUnitName,  caption()   ).conv (val);
    }
    double from_def (double val, const RTunits::unit_name& un ) ///< Convert a value in Default Unit into Unit un 
    {
        return RTunits::CUnit( _defUnitName,  caption()   ).conv (val);
    }
    double convert_to(double val, const RTunits::unit_name& un) ///< Convert a value in user selected Unit into Unit un 
    {
        return RTunits::CUnit(  caption() , un ).conv (val);
    }
    double convert_from(double val, const RTunits::unit_name& un) ///< Convert a value in Unit un into the user selected Unit
    {
        return RTunits::CUnit(un ,   caption()  ).conv (val);
    }

};

class NumUnitUpDown : public CompoWidget
{
    //double      _val;
	RTunits::unit_name _curr_un;
public:
    NumerUpDown _num; /// \todo: make private and provide a function to change the def lay, especially the length of the label
    UnitPicker  _unit; /// \todo: make private and provide a function to change the def lay, especially the length of the label
    NumUnitUpDown ( window wd,        
                    const std::string& label,
                    double defVal,    double min,     double max,    
                    const RTunits::unit_name& def  ,
                    const std::string& DefLayFile =("NumUnitUpDonw.Lay.txt"),
                    double step=1,   unsigned width=6, unsigned decimals=2)
        : CompoWidget (wd,label,("NumUnitUpDonw.Lay.txt")),
          _num(*this,label, defVal, min,max,("Vert-Invert.NumUpDonw.Lay.txt"),step,width,decimals),
          _unit(*this, def), _curr_un(def) //_val(defVal)
    {
        _unit.events().selected([&](const nana::arg_combox& arg_cb)
                                    {
										RTunits::CUnit u(_curr_un , /*charset*/( _unit.caption() ));   /*CUnit::unit_name ( nana::charset(cb.option ()) ) */
                                        if(u.error )
                                        {    _unit.caption (_unit.caption ()+("?"));
                                             return;
                                        }
                                        _num.Max   ( u.conv(_num.Max  () )  );
                                        _num.Min   ( u.conv(_num.Min  () )  );
                                        _num.Value ( u.conv(_num.Value() )  );
                                        if (u.conv.linear )
                                          _num.Step( u.conv.c*_num.Step()   );
                                       
                                        _curr_un=/*charset*/(_unit.caption ());
                                    });
        InitMyLayout();
        SelectClickableWidget( _num);
        SelectClickableWidget( _unit);
        
        //_num.add_validated ( [&](){Validated ();}        );
    }
    virtual    void add_validated(const std::function<bool(void)>& v) override
    {
        _num.add_validated (v); 
        //_validated.push_back (v); 
    }
    virtual    void add_validate(const std::function<bool(void)>& v) override
    {
        _num.add_validate (v); 
        //_validated.push_back (v); 
    }

     void SetDefLayout       () override
    {
        SetDefLayout       (60);
    }
     void SetDefLayout       (unsigned lab, unsigned n=50, unsigned unit=50)
    {
        std::stringstream lay;

         // redefine layout of this complete widget: NumUnitUpDown
        lay << "  <    \n"
               "  <vertical   min="  << lab+15+n << "              Num                 >   \n"
               "  <vertical   min="  << unit     << " <><vertical  Unit  weight=21><>  >   \n"
               " > ";   
        _DefLayout = lay.str(); // move a copy

         // redefine layout of the NumUpDown part (inside the previous Num)
        lay.str("  <           \n"); 
        lay <<  "              \n"
                "  <vertical weight="  <<  lab << "  <>< gap=1   label  weight=15> <>   >  \n"
                "  <vertical weight="  <<  15  << "  <><vertical UpDown weight=21> <>   >  \n"
                "  <vertical min="     <<  n   << "  <><         Num    weight=21> <>   >  \n"
                " > ";
        _num._DefLayout = lay.str(); // move a copy
     }
    void ResetLayout       (unsigned lab, unsigned n=50, unsigned unit=50)
    {
        SetDefLayout       (lab, n, unit);
        ResetDefLayout();  _num. ResetDefLayout();
        ReCollocate( );    _num.ReCollocate( );
    }

     void AsignWidgetToFields() override
    {
	    _place.field("Num"    ) << _num ;
	    _place.field("Unit"   ) << _unit ;
    }
     /// expressed in default Units
     double Value()
     {
         return _unit.to_def(_num.Value()); 
     }
     /// expressed in the specified "un" Units
     double Value(const RTunits::unit_name& un)
     {
         return _unit.convert_to(_num.Value(),un); 
     }
     /// expressed in default Units
     void   Value(double val_in_default_Units)
     {
         _num.Value(_unit.from_def(val_in_default_Units)); 
     }
     /// expressed in the specified "un" Units
     void   Value(double val, const RTunits::unit_name& un)
     {
         _num.Value(_unit.convert_from(val,un)); 
     }

};


}  // namespace nana  

        //cb.caption(_cb.caption().substr(6, _cb.caption().find_first_of((" ="),6)-6 )); 

#endif 
