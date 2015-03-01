#include <../../nana.ext/include/Numer.hpp>

namespace nana { 

NumerUpDown::NumerUpDown (  widget &parent_,      const string &label, 
                            double val,           double min, double max, 
                            const nana::string   &DefFileName/*=STR("NumUpDown.VertCenter.lay.txt")*/, 
                            double step/*=1*/,    unsigned width/*=6*/,    unsigned decimals/*=2*/  ) 
        :	CompoWidget( parent_, label, DefFileName),
			 _label(*this,label),
            _val(val), _min(min), _max(max), _step(step), _decimals(decimals), _width(width)
    {
        _num.multi_lines(false);
        display();        
        _label.text_align(align::right  ); 

        InitMyLayout();
        SelectClickableWidget( *this);
        SelectClickableWidget( _label);
        SelectClickableWidget( _num);

          _up.events().click    ([&](){add( _step); });
          _up.events().dbl_click([&](){add( _step); });
        _down.events().click    ([&](){add(-_step); });
        _down.events().dbl_click([&](){add(-_step); });
         //_num.make_event <events::focus>([&](const eventinfo& ei)
         //       {  
         //           std::cerr<< "\nBefore " << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , NumerUpDown: ";
         //           std::wcerr<< _Titel << std::endl;
         //           //if (!ei.focus.getting) 
         //           //    validate_edit( );
         //       }); 


         _num.events().focus([&](const arg_focus& ei)
                {  
                    std::cerr << std::endl<< (ei.getting ? "geting ":"lossing ") << "Focus: , NumerUpDown: ";
                    std::wcerr<< _label.caption() << std::endl;
                    if ( !ei.getting )
                    {
                        std::cerr   << "And validating: " << _val << "Cap:" << std::string(charset(_num.caption ()));
                        validate_edit ();
                    }
                }); 
         //_num.make_event <events::focus>([&](const eventinfo& ei)
         //       {  
         //           std::cerr<< "After " << (ei.focus.getting ? "geting ":"lossing ") << "Focus: , NumerUpDown: ";
         //           std::wcerr<< _Titel << std::endl;
         //           //if (!ei.focus.getting) 
         //           //    validate_edit( );
         //       }); 
    }

} // namespace nana { 

