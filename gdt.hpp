#ifndef GDT_HPP
#define GDT_HPP

#include <stddef.h>
#include <stdint.h>

struct GDTEntry
{
  unsigned short m_limit_low;
  unsigned short m_base_low;
  unsigned char m_base_middle;
  unsigned char m_access;
  unsigned char m_granularity;
  unsigned char m_base_high;
} __attribute__((packed));

struct GDTPtr
{
  unsigned short m_limit;
  unsigned int m_base;
} __attribute__((packed));

// The Kernel's GDT table
// Null, Code, and Data segments
extern GDTEntry __g_gdttable[3];
extern GDTPtr __g_gdt;


extern "C" 
{
// Defined in boot.s
extern void __gdt_load(void);
}

// Set a GDT table entry
void GDTSet( size_t index, uint32_t addressBase, uint32_t addressLimit, unsigned char access, unsigned char granularity );
void GDTInit();


#endif
