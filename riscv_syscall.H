/******************************************************
 * ArchC Architecture Dependent Syscall header file.  *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/
 

#ifndef RISCV_SYSCALL_H
#define RISCV_SYSCALL_H

#include "riscv_syscall_inc.H"

//riscv system calls
_AC_SYSCALL_CLASS_
{
public:
  _AC_SYSCALL_ARCH_USING_
  _AC_SYSCALL_CTOR_ {};
  virtual ~riscv_syscall() {};

  void get_buffer(int argn, unsigned char* buf, unsigned int size);
  void guest2hostmemcpy(unsigned char *dst, uint32_t src, unsigned int size);
  void set_buffer(int argn, unsigned char* buf, unsigned int size);
  void host2guestmemcpy(uint32_t dst, unsigned char *src, unsigned int size);
  void set_buffer_noinvert(int argn, unsigned char* buf, unsigned int size);
  int  get_int(int argn);
  void set_int(int argn, int val);
  void return_from_syscall();
  void set_prog_args(int argc, char **argv);
  int *get_syscall_table();
};

#endif
