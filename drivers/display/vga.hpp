#ifndef VGA_HPP
#define VGA_HPP

#include <stddef.h>
#include <stdint.h>

#define VGA_FB 0xB8000

class VGADisplayCharacters
{
public:
  enum Colour
  {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGrey = 7,
    DarkGrey = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    LightBrown = 14,
    White = 15
  };
  typedef uint8_t VGAColour;
  typedef uint16_t VGAEntry;

  VGADisplayCharacters();
  ~VGADisplayCharacters();
  
  VGAColour makeColour( Colour foreground, Colour background );
  VGAEntry makeVGAEntry( char c, VGAColour col );
  void putc( char c, VGAColour col, size_t offset );
private:
  VGAEntry* m_fb;
};

#endif
