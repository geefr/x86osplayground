
# Exposed functions
# Reload the IDT
.global __idt_load

# Externs
.extern __g_idt # The kernel's IDTPtr

__idt_load:
  lgdt __g_gdt # The kernel's IDT
  mov %ax, 0x10
  mov %ds, %ax
  mov %es, %ax
  mov %fs, %ax
  mov %gs, %ax
  mov %ss, %ax
  ret
