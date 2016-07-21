#include "gdt.hpp"

GDTEntry __g_gdttable[3];
GDTPtr __g_gdt;

void GDTSet( size_t index, uint32_t addressBase, uint32_t addressLimit, unsigned char access, unsigned char granularity )
{
  GDTEntry& entry( __g_gdttable[index] );
  
  entry.m_base_low = addressBase & 0xFFFF;
  entry.m_base_middle = (addressBase >> 16) & 0xFF;
  entry.m_base_high = (addressBase >> 24) & 0xFF;
  
  entry.m_limit_low = addressLimit & 0xFFFF;
  entry.m_granularity = (addressLimit >> 16) & 0x0F;
  
  entry.m_granularity |= granularity & 0xF0;
  entry.m_access = access;
}

void GDTInit()
{
  __g_gdt.m_base = (uint32_t)( &__g_gdttable );
  __g_gdt.m_limit = sizeof( __g_gdttable ) - 1;
  
  // The null entry
  GDTSet( 0, 0x00000000U, 0x00000000U, 0x00, 0x00);
  // The code segment
  GDTSet( 1, 0x00000000U, 0xFFFFFFFFU, 0x9A, 0xCF);
  // The data segment
  GDTSet( 2, 0x00000000U, 0xFFFFFFFFU, 0x92, 0xCF);
  
  // Reload the GDT
  __gdt_load();
}
