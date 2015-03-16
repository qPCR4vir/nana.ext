
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
            drawing dw(*this);
            dw.draw([gap,sz](paint::graphics& graph)
            {
                graph.rectangle(rectangle(gap-1, sz.height/2, 
                                          graph.width()-2*(gap-1), graph.height()-sz.height/2-(gap-1)),
                                 false, colors::gray_border);
            });
            plc.div(fmt.c_str());
        }
    };
}

