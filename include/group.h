
#include <nana/gui/wvl.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/form.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/drawing.hpp>

// see: http://qpcr4vir.github.io/nana-docs/nana-doxy/d5/d39/a_group_impl_8cpp-example.html
// or: https://github.com/qPCR4vir/nana-demo/blob/master/Examples/a_group_impl.cpp

namespace nana
{
    class group: public panel<true>
    {
       public:
        place       plc {*this};
        label       titel/* {*this}*/;
        std::string fmt;

        group ( widget &owner, 
                 ::nana::string titel_={}, 
                 bool format=false, 
                 unsigned gap=2, 
                 rectangle r={})
        : panel (owner, r),
          titel (*this, titel_)
        {
            titel.format(format);
            nana::size sz = titel.measure(1000);
            std::stringstream ft;

            ft << "vertical margin=[0," << gap << "," << gap << "," << gap << "]"
               << " <weight=" << sz.height << " <weight=5> <titel weight=" << sz.width+1 << "> >";
            fmt = ft.str();

            plc["titel"] << titel;

            color obg = owner.bgcolor();
            titel.bgcolor(obg.blend(colors::black, 0.975) );
            color bg=obg.blend(colors::black, 0.950 );
            bgcolor(bg);

            drawing dw(*this);
		    dw.draw([gap,sz,bg,obg](paint::graphics& graph)
		    {
			    graph.rectangle(true, obg);
                graph.round_rectangle(rectangle(       point ( gap-1,   sz.height/2), 
                                                 nana::size  (graph.width()-2*(gap-1),   graph.height()-sz.height/2-(gap-1))),
                                      3,3, colors::gray_border,     true, bg);
           });

           plc.div(fmt.c_str());
        }
    };
}

