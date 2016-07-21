
# Exposed functions
# Reload the GDT
.global __gdt_load

# Externs
.extern __g_gdt # The kernel's GDTPtr

__gdt_load:
  lgdt __g_gdt # The kernel's GDT
  mov %ax, 0x10
  mov %ds, %ax
  mov %es, %ax
  mov %fs, %ax
  mov %gs, %ax
  mov %ss, %ax
  ret
