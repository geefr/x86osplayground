
#include "vga.hpp"

VGADisplayCharacters::VGADisplayCharacters()
: m_fb( (uint16_t*) VGA_FB )
{}

VGADisplayCharacters::~VGADisplayCharacters()
{}
  
VGADisplayCharacters::VGAColour VGADisplayCharacters::makeColour( VGADisplayCharacters::Colour foreground, VGADisplayCharacters::Colour background )
{
  return foreground | background << 4;
}

VGADisplayCharacters::VGAEntry VGADisplayCharacters::makeVGAEntry( char c, VGADisplayCharacters::VGAColour col )
{
  VGADisplayCharacters::VGAEntry cvga( c );
  VGADisplayCharacters::VGAEntry colvga( col );
  return cvga | colvga << 8;
}

void VGADisplayCharacters::putc( char c, VGADisplayCharacters::VGAColour col, size_t offset )
{
  m_fb[offset] = makeVGAEntry( c, col );
}
  
