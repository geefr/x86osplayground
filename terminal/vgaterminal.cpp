
#include "vgaterminal.hpp"

VGATerminal::VGATerminal( size_t width, size_t height )
: m_width( width )
, m_height( height )
, m_colour( 0 )
, m_cursorX( 0 )
, m_cursorY( 0 )
{
  m_colour = m_charDisplay.makeColour( VGADisplayCharacters::White, VGADisplayCharacters::Black );
  
  for( size_t y(0); y < m_height; ++y )
  {
    for( size_t x(0); x < m_width; ++x )
    {
      size_t offset( y * m_width + x );
      m_charDisplay.putc(' ', m_colour, offset);
    }
  }
}

VGATerminal::~VGATerminal()
{}
 
void VGATerminal::setColour( VGADisplayCharacters::VGAColour col )
{
  m_colour = col;
}

void VGATerminal::putc( char c )
{
  if( c == '\n' )
  {
    m_cursorX = 0;
    if( ++m_cursorY == m_height )
    {
      m_cursorY = 0;
    }
    return;
  }
  size_t offset( m_cursorY * m_width + m_cursorX );
  m_charDisplay.putc( c, m_colour, offset );
  if( ++m_cursorX == m_width )
  {
    m_cursorX = 0;
    if( ++m_cursorY == m_height )
    {
      m_cursorY = 0;
    }
  }
}

void VGATerminal::puts( const char* s )
{
  while( *s != '\0' )
  {
    putc( *s++ );
  }
}
