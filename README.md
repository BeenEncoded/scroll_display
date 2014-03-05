Scroll Display Class:

---

I simple class I designed to make it easy to create and use a scroll display.  This is **NOT** a graphical scroll display.  This is a text-based one, that makes it very easy to write a scroll menu.  You can write the selection text-art yourself.  It uses a vector for the display.  When you set it to the vector, it does not allocate any new memory.  Rather, it uses a pointer to the vector.  You should NOT use this class if it does not point to a pre-existing vector.  I chose this design for a number of reasons, one of which is that the display often must be modified and handled outside of the class (waaay outside of it).

scroll_display_class functions:

---

**void mv_up():**  moves the selected position in the display up one (-- index of the vector)
**void mv_down():**  moves the selected position in the display down one.  (++ index in the vector)
**void pg_up():**  moves the selected position 1 "page" up (--).  This is equivilant to 1 window, or window_size indeices.
**void pg_down():**  moves the selected position 1 "page" down.  This is equivilant to 1 window, or window_size indeices.

**void operator=(const scroll_display_class&):**  This is added for assigning a vector after initialization.  You can initialize the class with a vector, but if you can't, then this is how you can do it.

**std::vector<std::string> window():**  returns a vector that contains the current window of items.
**const position_data& gpos():**  returns position structure:  [whole]-  position relative with the entire display.  This can be used to reference the item in your vector directly.  [part]-  Position relative to the window.  This can be use to represent the user's currently selected item in the window.

**long &window_size():** returns a reference to the window's size.  can be safely set to anything.

**const signed long& window_beg():**  Returns the window's starting position relative to the entire vector.  Can be used to access the section of the entire display that represents the window.

This was written by me, because NCurses is far too bloated for what I need.  I just need a simple display, and that's exactly what this is.

-  Never use it if it isn't initialized with a vector.  Operator=() can let you do this, however, if you set it equal to an initialized display with a vector.

This is a text based scroll display.  It's bare minimum.  You can add other things, without modifying the class.

This display is especially good when large lists need to be used.  Example: a filesystem can have over 2,000 entries.  If you write a filesystem browser, this would be a great solution for the menu.

Have fun!
