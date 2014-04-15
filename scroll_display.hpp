#ifndef SCROLL_DISPLAY_HPP_INCLUDED
#define SCROLL_DISPLAY_HPP_INCLUDED
#include <vector>
#include <string>
#include <assert.h>

#include "global_defines.hpp"

namespace scrollDisplay
{
    class scroll_display_class;
    
    struct window_data
    {
        void operator=(const window_data& wd)
        {
            if(this != & wd)
            {
                this->beg = wd.beg;
                this->size = wd.size;
            }
        }
        
        signed long size = 15, beg = 0;
    };
    
    struct position_data
    {
        void operator=(const position_data& pd)
        {
            if(this != &pd)
            {
                this->part = pd.part;
                this->whole = pd.whole;
            }
        }
        
        short part = 0;
        unsigned int whole = 0;
    };
    
    /* scroll_display_class: a class designed to manage a window and make 
     * it easy to create a scroll display.*/
    class scroll_display_class
    {
    public:
        explicit scroll_display_class() : display(NULL), 
                wind(), 
                pos() {}
        
        explicit scroll_display_class(std::vector<std::string>& d) : display(&d),
                    wind(),
                    pos()
        {
            assert(&d != NULL);
        }
        
        ~scroll_display_class(){}
        
        void operator=(const scroll_display_class& sdc)
        {
            if(this != &sdc)
            {
                assert(sdc.display != NULL);
                this->display = sdc.display;
                this->pos = sdc.pos;
                this->wind = sdc.wind;
            }
        }
        
        bool mv_up();
        bool mv_down();
        bool pg_up();
        bool pg_down();
        
        /* Returns the "window" as a list of strings.  This can
         be displayed. */
        std::vector<std::string> window();
        
        /* Returns the current position in the window.  part
         represents the position relative to the window, and
         whole represents the position relative to the entire
         display.*/
        const position_data& gpos();
        
        /* Returns the size of the scroll display.  can be 
         modified directly. */
        long &window_size()
        {
            return this->wind.size;
        }
        
        /* Returns the first position of the window, relative to the 
         entire display. */
        const signed long& window_beg()
        {
            assert(this->display != NULL);
            this->sync();
            return this->wind.beg;
        }
        
    private:
        std::vector<std::string> *display;
        window_data wind;
        position_data pos;
        
        void sync();
        bool scroll_up();
        bool scroll_down();
        bool scroll_pg_up();
        bool scroll_pg_down();
        
        /* Calculates the last possible index that can
         be safely referenced from the pointed vector, based on where the window
         is positioned.*/
        signed long end_pos() const
        {
            assert(this->display != NULL);
            signed long temp(this->wind.beg + (this->wind.size - 1));
            switch(this->display->size() > 0)
            {
                case true:
                {
                    if(temp > 0)
                    {
                        if(unsigned(temp) >= this->display->size()) temp = (this->display->size() - 1);
                    }
                    if(temp < this->wind.beg)
                    {
                        throw "Error:  signed long end_pos() const (end_pos < wind.begin)!!!";
                    }
                }
                break;
                
                case false:
                {
                    temp = (-1);
                }
                break;
                
                default:
                {
                    temp = (-1);
                }
                break;
            }
            return temp;
        }
        
        /* Returns the size of the window which has been "resized"
         to fit within the pointed vector.  Does not reflect
         the value of wind.size.  (this should be <= wind.size)*/
        signed long current_wsize() const
        {
            return ((this->end_pos() - this->wind.beg) + 1);
        }
        
        
    };
    
    
}

#endif