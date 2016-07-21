
#include <stddef.h>
#include <stdint.h>
  
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
#include "terminal/vgaterminal.hpp"
#include "gdt.hpp"
 
 static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}
 
 /*
PS/2 keyboard code.
Dependencies:
inb function and scancode table.
*/
char getScancode()
{
  char c=0;
  do 
  {
    if(inb(0x60)!=c)
    {
      c=inb(0x60);
      if(c>0)
        return c;
    }
  } while(1);
}
/*
char getchar()
{
  return scancode[getScancode()+1];
}
*/

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
	// So we're here, and thanks to multiboot:
	// -In 32-bit protected mode
	// -A20 line is enabled (Allows access to full 4GB of memory)
	
	
	// Create and attach a basic terminal
	VGATerminal terminal;
	
	terminal.puts("Hello, world!\n");
	
	// Setup the GDT
	GDTInit();
	
	terminal.puts("GDT Init OK!\n");
	while( true )
	{
		char c( getScancode() );
		terminal.putc(c);
	}
}
