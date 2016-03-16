#ifndef nanaBind_H
#define nanaBind_H

#include <memory>
#include <vector>
 
//#include "ThDySec\matrix.h" 
#include "common_basics.h" 
#include "init_prog_param.h" 
#include "ParamGUIBind.hpp" 
#include <../../nana.ext/include/EditableForm.hpp>
#include <../../nana.ext/include/Numer.hpp>  // #include <../../nana.ext/include/Numer.hpp>
#include <nana/gui/widgets/checkbox.hpp>


/// \todo implement a general template that use delegated and inherited constructors?
namespace ParamGUIBind 
{
class nanaWidgetBind : public virtual IParBind 
{
  protected:
    nana::widget& _w;
public: 
    nanaWidgetBind (nana::widget& w ): _w(w)
    {
        //_w.make_event <nana::events::focus>([&](const nana::eventinfo& ei)
        //        {  
        //            std::cerr<< "\nBefore " << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind: ";
        //            std::wcerr<< _w.caption() << std::endl;
        //            //if (!ei.focus.getting) 
        //            //    validate_edit( );
        //        }); 
        _w.events().focus([&](const nana::arg_focus& ei)
        {  
                    //assert((   std::cerr<< "\n" << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind: "  , true  ));;
                    //assert((   std::wcerr<< _w.caption() << std::endl  , true  ));;

            if (!ei.getting) 
                UpDateProg ();
        });
        //_w.make_event <nana::events::focus>([&](const nana::eventinfo& ei)
        //        {  
        //            std::cerr<< "\nAfter " << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind: ";
        //            std::wcerr<< _w.caption() << std::endl;
        //            //if (!ei.focus.getting) 
        //            //    validate_edit( );
        //        }); 
    }
    nanaWidgetBind (nana::widget& w, nana::widget& resp_w): _w(w)
    {
        //resp_w.make_event <nana::events::focus>([&](const nana::eventinfo& ei)
        //        {  
        //            std::cerr<< "\nBefore " << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind: ";
        //            std::wcerr<< _w.caption() << std::endl;
        //            //if (!ei.focus.getting) 
        //            //    validate_edit( );
        //        }); 
        resp_w.events().focus([&](const nana::arg_focus&ei)
        {  
                    //std::cerr<< "\n" << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind: ";
                    //std::wcerr<< _w.caption() << std::endl;
            
            if (!ei .getting) 
                UpDateProg ();
        });
        //resp_w.make_event <nana::events::focus>([&](const nana::eventinfo& ei)
        //        {  
        //            std::cerr<< "\nAfter " << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind: ";
        //            std::wcerr<< _w.caption() << std::endl;
        //            //if (!ei.focus.getting) 
        //            //    validate_edit( );
        //        }); 
    }
    nanaWidgetBind (CompoWidget & CW ): _w(CW)
    {
        //std::cerr<< "\nSetting validating: , nanaWidgetBind: ";
        //std::wcerr<< CW._Titel  << std::endl;
        //CW.add_validated ( [&]()
        //        {  
        //            std::cerr<< "\nBefore validated: , nanaWidgetBind: ";
        //            std::wcerr<< CW._Titel  << std::endl;
        //        }); 
        CW.add_validate ([&]()
        {  
            //assert((  std::cerr<< "\nBefore validated: , nanaWidgetBind, CompoWidget: "  , true  ));;
            //assert((  std::wcerr<< CW._Titel  << std::endl  , true  ));;
            UpDateProg ();
            return true;
        });
        //CW.add_validated ([&]()
        //        {  
        //            std::cerr<< "\nAfter validated: , nanaWidgetBind: ";
        //            std::wcerr<< CW._Titel  << std::endl;
        //        }); 
    }
    nanaWidgetBind (CompoWidget & CW, nana::widget& resp_w): _w(CW)
    {
        //std::wcerr<< _w.caption() <<(" Setting add_validate")<< std::endl;
        
        CW.add_validate ([&]()->bool
        {  
            //assert((  std::cerr<< "\nBefore validated: , nanaWidgetBind-duo, CompoWidget: " , true  ));;
            //assert((  std::wcerr<< CW._Titel  << std::endl , true  ));;
            UpDateProg ();/// \todo REVISE here or in validated ????? ------------!!!!!!
            return true;
        });
        //resp_w.make_event <nana::events::focus>([&](const nana::eventinfo& ei)
        //        {  
        //            std::cerr<< "\nBefore " << (ei.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind: ";
        //            std::wcerr<< _w.caption() << std::endl;
        //            //if (!ei.focus.getting) 
        //            //    validate_edit( );
        //        }); 
        resp_w.events().focus([&](const nana::arg_focus& ei)
        {  
                    //assert((  std::cerr<< "\n" << (ei.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind-duo: " , true  ));;
                    //assert((  std::wcerr<< _w.caption() << std::endl , true  ));;
            
            if (!ei.getting)    /// \ add a try ?????----!!!!! An exeption here go to message pumping and CRASH !!
                UpDateProg ();  // debiera ser:  CW.validate_only ???
        });
        //resp_w.make_event <nana::events::focus>([&](const nana::eventinfo& ei)
        //        {  
        //            std::cerr<< "\nAfter " << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , nanaWidgetBind: ";
        //            std::wcerr<< _w.caption() << std::endl;
        //            //if (!ei.focus.getting) 
        //            //    validate_edit( );
        //        }); 
    }

    void          updateForm(std::string val){
                                                    _w.caption(val); nana::API::update_window (_w);
                                              }
    std::string  getFormVal(       ){ return   _w.caption (   );
                                     }
};


class Bind_checkbox : public nanaWidgetBind  
{ 	
 public:				
    Bind_checkbox ( nana::checkbox& c):nanaWidgetBind(c){} 

    void updateForm(bool val){  static_cast <nana::checkbox&>(_w).check  (val); nana::API::update_window (_w);
                             }
    bool getFormVal()/*const*/ {  return  static_cast <nana::checkbox&>(_w).checked(   ); 
                               }
};

/// \todo: adapt to new nana::spinbox
class Bind_NumUpDw : public nanaWidgetBind  
{ 	
 public:				
    Bind_NumUpDw ( nana::NumerUpDown & c):nanaWidgetBind(c,c._num){} 

    void   updateForm(double val){  static_cast <nana::NumerUpDown&>(_w).Value  (val); nana::API::update_window (_w);}
    double getFormVal(  ){  return  static_cast <nana::NumerUpDown&>(_w).Value  (   ); }
};

/// \todo: adapt to new nana::spinbox
class Bind_UnitUpDw : public nanaWidgetBind  
{ 	
 public:				
    Bind_UnitUpDw ( nana::NumUnitUpDown & c):nanaWidgetBind(c    ,c._num._num){} 

    void   updateForm(double val){  static_cast <nana::NumUnitUpDown&>(_w).Value  (val); nana::API::update_window (_w);
                                 }
    double getFormVal(  )/*const*/{  return  static_cast <nana::NumUnitUpDown&>(_w).Value  (   ); 
                                  }
    void   updateForm(double val, const CUnit::unit_name &un){  static_cast <nana::NumUnitUpDown&>(_w).Value  (val, un);nana::API::update_window (_w);
                                                             }
    double getFormVal/*const*/(const CUnit::unit_name &un    ){  return  static_cast <nana::NumUnitUpDown&>(_w).Value  (un     );
                                                              }
};

class Bind_FilePickBox : public nanaWidgetBind  
{ 	
 public:				
    Bind_FilePickBox ( FilePickBox & c):nanaWidgetBind(c/*,c._file_w()*/ ){} 

    void         updateForm(std::string file)
    {  
        static_cast <FilePickBox&>(_w).FileNameOnly (file);
        nana::API::update_window (_w); 
    }
    std::string getFormVal(  ){  return  static_cast <FilePickBox&>(_w).FileName  (   ); }
};

class Bind_CParamStr_widget : public nanaWidgetBind, public Bind_CParamString  
{ 	
 public:				
    Bind_CParamStr_widget (CParamString &p, nana::widget& c):Bind_CParamString(p),nanaWidgetBind(c){SetDef();} 

    void UpDateForm()override { updateForm(             nana::charset ( getProgVal() ))         ;}
	void UpDateProg()override { updateProg(std::string( nana::charset ( getFormVal() )))        ;}
};

/// \deprecate
class Bind_CParamC_str_widget : public nanaWidgetBind, public Bind_CParamC_str  
{ 	
 public:				
    Bind_CParamC_str_widget (CParamC_str &p, nana::widget& c):Bind_CParamC_str(p),nanaWidgetBind(c){SetDef();} 

    void UpDateForm()override { updateForm(             nana::charset ( getProgVal() ))         ;}
	void UpDateProg()override { updateProg(std::string( nana::charset ( getFormVal() )).c_str());}
};

class BindBool   : public Bind_checkbox, public Bind_CParamBool  
{ 	
 public:				
    BindBool (CParamBool &p, nana::checkbox& c):Bind_CParamBool(p),Bind_checkbox(c){SetDef();} 

    void	UpDateForm(	 )	override {         updateForm(getProgVal()); }
	void	UpDateProg(	 )	override {         updateProg(getFormVal()); }
};


/// \todo: adapt to new nana::spinbox
template <class Num>
class Bind_NumR_UnitUpDw   : public Bind_UnitUpDw, public Bind_CParamRang<Num>  
{ 	
 public:				
    Bind_NumR_UnitUpDw (CParamNumRange<Num>  &p, nana::NumUnitUpDown& c):Bind_CParamRang<Num> (p), Bind_UnitUpDw(c)
    {
        //CUnit::unit_name gui(static_cast <nana::NumUnitUpDown&>(_w)._unit._defUnit);
        //CUnit::unit_name                  prog( _p.Unit());
        //CUnit u( static_cast <nana::NumUnitUpDown&>(_w)._unit._defUnit
        //assert(   );
        SetDef();
    } 

    void	UpDateForm(	 )	override {     updateForm(getProgVal(), _p.Unit() ); 
                                     }
	void	UpDateProg(	 )	override {     updateProg(Num (getFormVal(   _p.Unit()))); 
                                     }
};

/// \todo: adapt to new nana::spinbox
template <class Num>
class Bind_MinMaxUnitUpDw : public BindGroup 
{public:
    Bind_MinMaxUnitUpDw(CParamNumMinMax<Num>&p, nana::NumUnitUpDown& min, 
                                                nana::NumUnitUpDown& max)
    {
         add(upPbind(new  Bind_NumR_UnitUpDw<Num> ( p.Min() ,min)  ));
         add(upPbind(new  Bind_NumR_UnitUpDw<Num> ( p.Max() ,max)  ));
    }
};

/// \todo eliminate charset use?
template <typename enumType>
class Bind_EnumRange_combox   : public nanaWidgetBind, public Bind_CParamEnumRange<enumType>
{ 	
 public:				
    Bind_EnumRange_combox (CParamEnumRange<enumType>&  p, nana::combox& c, bool initialize=true)
                       :Bind_CParamEnumRange<enumType> (p),    nanaWidgetBind(c)
    {
        if (initialize)
            for (const auto& e: p.StrValues())//static_cast <CParamEnumRange<enumType>& >(_p)
                c.push_back (nana::charset (e.first));
        SetDef();
    } 

    void UpDateForm()override { updateForm(             nana::charset ( getProgVal() ))         ;}
	void UpDateProg()override { updateProg(std::string( nana::charset ( getFormVal() )).c_str());}
};

/// \todo eliminate charset use?
class Bind_CParamStr_FilePickBox : public Bind_FilePickBox, public Bind_CParamString
{ 	
 public:				
    Bind_CParamStr_FilePickBox (CParamString &p, FilePickBox& c):Bind_CParamString(p),Bind_FilePickBox(c){SetDef();} 

    void UpDateForm()override { updateForm(             nana::charset ( getProgVal() ))         ;}
	void UpDateProg()override { updateProg(std::string( nana::charset ( getFormVal() )))        ;}
};


inline upPbind link(CParamString &p,            nana::widget&      w)
{
    return  upPbind(new Bind_CParamStr_widget (p, w));
}

inline upPbind link(CParamString &p,            FilePickBox&            w)
{
    return  upPbind(new Bind_CParamStr_FilePickBox  (p, w ));
}

/// \deprecate?
inline upPbind link(CParamC_str &p,            nana::widget&      w)
{
    return  upPbind(new Bind_CParamC_str_widget (p, w));
}
 //inline upPbind link(CParamC_str &p,            FilePickBox&            w)
//{
//    return  link(p, w._file_w());
//}


inline upPbind link(CParamBool &p,             nana::checkbox&    c)
{
    return  upPbind(new BindBool (p, c));
}



/// \todo: adapt to new nana::spinbox
template <class Num>
inline upPbind link(CParamNumRange<Num>  &p, nana::NumUnitUpDown& c)
{
    return  upPbind(new  Bind_NumR_UnitUpDw<Num> (p,  c) );
}
             
             template <class Num> 
inline upPbind link(CParamNumMinMax<Num> &p, nana::NumUnitUpDown& min, 
                                      nana::NumUnitUpDown& max)
{
    return  upPbind(new  Bind_MinMaxUnitUpDw<Num> (p,min,max) );
}
             
             template <typename enumType>
inline upPbind link(CParamEnumRange<enumType>& p, nana::combox& c, bool initialize=true)
{
    return  upPbind(new  Bind_EnumRange_combox<enumType>(p,c,initialize));
}







            template <class Bind_Param,class Bind_Widget> 
class Bind_Param_Widget : public     Bind_Param, public Bind_Widget
{
    //Bind_Param  & _p;
    //Bind_Widget & _w;
public:
    template <class Param,class Widget> 
    Bind_Param_Widget (Param &p, Widget& w):Bind_Param(p),Bind_Widget(w){SetDef();} 

    void	UpDateForm(	 )	override {         updateForm(getProgVal()); }
	void	UpDateProg(	 )	override {         updateProg(getFormVal()); }

};
            template <class Bind_Param,class Bind_Widget,class Param,class Widget> 
inline upPbind link( Param &p,  Widget&  w)
{
    return  upPbind(new Bind_Param_Widget<Bind_Param,Bind_Widget> (p, w));
}

}
#endif

//class Bind_C_str_txtbox : public Bind_txtbox, public Bind_C_str //    Bind a Control.CheckBox with a bool variable ---- TagBinding_bool    :
//{ 	
// public:				
//    Bind_C_str_txtbox (CParamC_str &p, nana::textbox& c):Bind_C_str(p),Bind_txtbox(c){SetDef();} 
//
//    void UpDateForm()override { updateForm(             nana::charset ( getProgVal() ))         ;}
//	void UpDateProg()override { updateProg(std::string( nana::charset ( getFormVal() )).c_str());}
//};
//class PrgPrmNanaBind : public nanaWidgetBind, public ProgPBind
//{
//  public:
//      PrgPrmNanaBind(IParam& p,nana::widget& w):ProgPBind(p), nanaWidgetBind(w){}
//
//};
//class Bind_bool : public PrgPrmNanaBind //    Bind a Control.CheckBox with a bool variable ---- TagBinding_bool    :
//{ 	
// public:				
//    Bind_bool (CParamBool &p, nana::checkbox& c):PrgPrmNanaBind(p,c){} 
//
//    void updateForm(bool val){ static_cast <nana::checkbox&>(_w).check  (val); }
//    void updateProg(bool val){ static_cast <CParamBool&         >(_p).set    (val); }
//    bool getProgVal(){ return  static_cast <CParamBool&         >(_p).get    () ; }
//    bool getFormVal(){ return  static_cast <nana::checkbox&>(_w).checked() ; }
//    
//    void	UpDateForm(	 )	override { updateForm(getProgVal()); }
//	void	UpDateProg(	 )	override { updateProg(getFormVal()); }
//};
//class Bind_txtbox : public nanaWidgetBind  
//{ 	
// public:				
//    Bind_txtbox ( nana::textbox& c):nanaWidgetBind(c){} 
//
//    //void          updateForm(std::string val){ static_cast <nana::textbox&>(_w).caption (val); }
//    //std::string  getFormVal(       ){ return   static_cast <nana::textbox&>(_w).caption (   ); }
//};
     //BindGroup&	operator<<	(upPbind&& pb){  _pb.push_back(std::move(pb)) ;	  return *this;	 }
//upPbind link(CParamC_str &p, nana::textbox& c)
//{
//    return  upPbind(new Bind_C_str_txtbox (p, c));
//}

//class Bind_C_str_b : public PrgPrmNanaBind //    Bind a Control.Text with a C_str variable ---- TagBinding_C_str    :
//{ 	protected:	 ;
//	public:				Bind_C_str_b (C_str &s, Control^ c):TagBinding(c)	, _p(s)	{} 
//
//	virtual void		set(Object^ s)	override{						_p.Take (  CreateCharFromManString((String^ )s)	) ; }
//	virtual Object^		get(		 )	override{ return  gcnew String(	_p.Get()								) ; }
//	virtual void		UpDateForm(	 )	override{ _c->Text = (String^)get()	;}
//	virtual void		UpDateP(	 )	override{ set (_c->Text)				;}
//};
//ref		  class TagBinding_C_str    : public TagBinding_C_str_b  //    Bind a Control.Text with a C_str variable using Trim ---- TagBinding_strTrim    :
//{ 	public:				TagBinding_C_str   (C_str &s, Control^ c):TagBinding_C_str_b(s,c)		{SetDef()		;}
//};
//ref		  class TagBinding_strTrim  : public TagBinding_C_str_b  //    Bind a Control.Text with a C_str variable using Trim ---- TagBinding_strTrim    :
//{ 	public:				TagBinding_strTrim (C_str &s, Control^ c):TagBinding_C_str_b(s,c)		{SetDef()		;}
//	virtual void		set(Object^ s)	override{						_p.TakeTrim (  CreateCharFromManString((String^ )s)	) ; }
//};
//
//template<typename Num>
//ref		  class TagBinding_Dec    : public TagBinding //    Bind a NumericUpDown.Value with a float variable ---- TagBinding_Dec    :
//{ 	protected:	Num		&_p; 
//				float	_k ;
//	public:				TagBinding_Dec (Num &p, NumericUpDown^ c, float k):TagBinding(c), _p(p), _k(k)	{SetDef()		;}
//
//	virtual void		set(Object^ f)	override{	_p	 = (Num)(_k * Decimal::ToSingle( *(Decimal^)(f) )); }
//	virtual Object^		get(		 )	override{ return  gcnew Decimal(	_p / _k) ; }
//	virtual void		UpDateForm(	 )	override{	   ((NumericUpDown^)(_c))->Value =  *(Decimal^) get()	;}
//	virtual void		UpDateP(	 )	override{ set( ((NumericUpDown^)(_c))->Value )  					;}	
//};
//
//	template<typename Num>
//ref		  class TagBinding_Rang_Min_b    : public TagBinding //    Bind a NumericUpDown.Value with a min of NumRang float variable ---- TagBinding_Rang_Min_b    :
//{ 	protected:	float			_k ;
//				NumRang<Num> &_p;
//
//	public:				TagBinding_Rang_Min_b (NumRang<Num> &p, NumericUpDown^ c, float k)	:TagBinding(c)	, _p(p), _k(k){ }
//
//	virtual void		set(Object^ f)	override{	_p.SetMin( (Num)(_k * Decimal::ToSingle( *(Decimal^)(f) ))); }
//	virtual Object^		get(		 )	override{ return  gcnew Decimal(	_p.Min() / _k) ; }
//	virtual void		UpDateForm(	 )	override{	   ((NumericUpDown^)(_c))->Value =  *(Decimal^) get()	;}
//	virtual void		UpDateP(	 )	override{ set( ((NumericUpDown^)(_c))->Value )  					;}	
//};
//	template<typename Num>
//ref		  class TagBinding_Rang_Min    : public TagBinding_Rang_Min_b<Num> //    Bind a NumericUpDown.Value with a a min of NumRang float variable ---- TagBinding_Rang_Min
//{ 	public:				TagBinding_Rang_Min (NumRang<Num> &p, NumericUpDown^ c, float k)	:TagBinding_Rang_Min_b<Num>(p,c,k)	{ SetDef()		;}
//};
//	template<typename Num>
//ref		  class TagBinding_Rang_Max    : public TagBinding_Rang_Min_b<Num> //    Bind a NumericUpDown.Value with a a max of NumRang float variable ---- TagBinding_Rang_Max
//{ 	public:				TagBinding_Rang_Max (NumRang<Num> &p, NumericUpDown^ c, float k)	:TagBinding_Rang_Min_b<Num>(p,c,k)	{ SetDef()		;}
//	virtual void		set(Object^ f)	override{	_p.SetMax((Num)(_k * Decimal::ToSingle( *(Decimal^)(f) ))); }
//	virtual Object^		get(		 )	override{ return  gcnew Decimal(	_p.Max() / _k) ; }
//};
//	template<typename Num>
//ref		  class TagBinding_Rang    : public TagBindGroup //    Bind a NumericUpDown.Value with a float variable ---- TagBinding_Dec    :
//{ 	public:				TagBinding_Rang (NumericUpDown^ cmin, NumericUpDown^ cmax, NumRang<Num> &p, float k)
//							{   Add( gcnew TagBinding_Rang_Min<Num>(p,cmin,k));
//								Add( gcnew TagBinding_Rang_Max<Num>(p,cmax,k));}
//};
//
//
//					TagBinding_C_str^		TagBind		(Control^	c	, C_str &s							);
//					TagBinding_strTrim^		TagBind_Trim(Control^	c	, C_str &s							);
//template<class Num>	TagBinding_Dec<Num>^	TagBind(NumericUpDown^ c, Num &p, float k						){ return gcnew TagBinding_Dec<Num>(p,c,k)	;}	
//template<class Num>	TagBinding_Dec<Num>^	TagBind(NumericUpDown^ c, Num &p								){ return TagBind<Num>(c,p,1)	;}	
//template<class Num>	TagBinding_Rang<Num>^	TagBind(NumericUpDown^ cmin, NumericUpDown^ cmax, NumRang<Num> &p, float k){ return gcnew TagBinding_Rang<Num>(cmin, cmax,p,k)	;}	
//template<class Num>	TagBinding_Rang<Num>^	TagBind(NumericUpDown^ cmin, NumericUpDown^ cmax, NumRang<Num> &p		  ){ return TagBind<Num>(cmin, cmax,p,1)	;}	
//
//TagBinding_bool^	TagBind(CheckBox^	  c , bool  &p			);
//
//}
//
