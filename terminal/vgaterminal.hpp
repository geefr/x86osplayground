#ifndef VGATERMINAL_HPP
#define VGATERMINAL_HPP

#include <stddef.h>
#include <stdint.h>

#include "drivers/display/vga.hpp"

class VGATerminal
{
public:  
  VGATerminal( size_t width = 80, size_t height = 25 );
  ~VGATerminal();
 
  void setColour( VGADisplayCharacters::VGAColour col );
  void putc( char c );
  void puts( const char* s );
private: 
  size_t m_width;
  size_t m_height;
  VGADisplayCharacters::VGAColour m_colour;
  size_t m_cursorX;
  size_t m_cursorY;
  
  // Should really be static, but that would need __dso_handle and __dso_atexit
  VGADisplayCharacters m_charDisplay;
};

#endif
