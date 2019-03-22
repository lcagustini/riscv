/*************************************************
**************************************************
*	@file		riscv_syscall.cpp
*	@author		Dário Dias
*	@email		dsd@cin.ufpe.br		
*	@version	0.20
*	@date		8 July 2016
*	@brief		The ArchC Risc-V functional model.
**************************************************
*************************************************/

#define _RISCV_SYSCALL_CPP_

#include "riscv_syscall_inc.H"

// 'using namespace' statement to allow access to all
// riscv-specific datatypes
using namespace riscv_parms;
unsigned procNumber = 0;

//void riscv_syscall::get_buffer(int argn, unsigned char* buf, unsigned int size)
_AC_SYSCALL_IMPL_(void, get_buffer, int argn, unsigned char* buf, unsigned int size)
{
  unsigned int addr = RB[10+argn];

  for (unsigned int i = 0; i<size; i++, addr++) {
    buf[i] = DATA_PORT->read_byte(addr);
  }
}

_AC_SYSCALL_IMPL_(void, guest2hostmemcpy, unsigned char *dst, uint32_t src,
                                    unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    dst[i] = DATA_PORT->read_byte(src++);
  }
}

//void riscv_syscall::set_buffer(int argn, unsigned char* buf, unsigned int size)
_AC_SYSCALL_IMPL_(void, set_buffer, int argn, unsigned char* buf, unsigned int size)
{
  unsigned int addr = RB[10+argn];

  for (unsigned int i = 0; i<size; i++, addr++) {
    DATA_PORT->write_byte(addr, buf[i]);
  }
}

_AC_SYSCALL_IMPL_(void, host2guestmemcpy, uint32_t dst, unsigned char *src,
                                    unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    DATA_PORT->write_byte(dst++, src[i]);
  }
}

//void riscv_syscall::set_buffer_noinvert(int argn, unsigned char* buf, unsigned int size)
_AC_SYSCALL_IMPL_(void, set_buffer_noinvert, int argn, unsigned char* buf, unsigned int size)
{
  unsigned int addr = RB[10+argn];

  for (unsigned int i = 0; i<size; i+=4, addr+=4) {
    DATA_PORT->write(addr, *(unsigned int *) &buf[i]);
  }
}

//int riscv_syscall::get_int(int argn)
_AC_SYSCALL_IMPL_(int, get_int, int argn)
{
  return RB[10+argn];
}

//void riscv_syscall::set_int(int argn, int val)
_AC_SYSCALL_IMPL_(void, set_int, int argn, int val)
{
  RB[10+argn] = val;
}

//void riscv_syscall::return_from_syscall()
_AC_SYSCALL_IMPL_(void, return_from_syscall)
{
  ac_pc = RB[1];
}

//void riscv_syscall::set_prog_args(int argc, char **argv)
_AC_SYSCALL_IMPL_(void, set_prog_args, int argc, char **argv)
{
  int i, j, base;

  unsigned int ac_argv[30];
  char ac_argstr[512];

  base = AC_RAM_END - 512 - procNumber * 64 * 1024;
  for (i=0, j=0; i<argc; i++) {
    int len = strlen(argv[i]) + 1;
    ac_argv[i] = base + j;
    memcpy(&ac_argstr[j], argv[i], len);
    j += len;
  }

  RB[10] = base;
  set_buffer(0, (unsigned char*) ac_argstr, 512);   //$25 = $29(sp) - 4 (set_buffer adds 4)


  RB[10] = base - 120;
  set_buffer_noinvert(0, (unsigned char*) ac_argv, 120);

  //RB[4] = AC_RAM_END-512-128;

  //Set %o0 to the argument count
  RB[10] = argc;

  //Set %o1 to the string pointers
  RB[11] = base - 120;

  procNumber ++;
}

#define RISCV__NR_restart_syscall 128
#define RISCV__NR_exit 93
#define RISCV__NR_fork 1079
#define RISCV__NR_read 63
#define RISCV__NR_write 64
#define RISCV__NR_open 1024
#define RISCV__NR_close 57
#define RISCV__NR_creat 1064
#define RISCV__NR_time 1062
#define RISCV__NR_lseek 1057
#define RISCV__NR_getpid 172
#define RISCV__NR_access 1033
#define RISCV__NR_kill 129
#define RISCV__NR_dup 23
#define RISCV__NR_times 153
#define RISCV__NR_brk 214
#define RISCV__NR_mmap 1058
#define RISCV__NR_munmap 215
#define RISCV__NR_stat 1049
#define RISCV__NR_lstat 1050
#define RISCV__NR_fstat 1051
#define RISCV__NR_uname 160
#define RISCV__NR__llseek 62
#define RISCV__NR_readv 65
#define RISCV__NR_writev 66
#define RISCV__NR_mmap2 222
#define RISCV__NR_stat64 1038
#define RISCV__NR_lstat64 1039
#define RISCV__NR_fstat64 80
#define RISCV__NR_getuid 174
#define RISCV__NR_getgid 176
#define RISCV__NR_geteuid 175
#define RISCV__NR_getegid 177
#define RISCV__NR_fcntl64 25
#define RISCV__NR_exit_group 94
#define RISCV__NR_socketcall -1
#define RISCV__NR_gettimeofday 169
#define RISCV__NR_settimeofday 170
#define RISCV__NR_clock_gettime 113


_AC_SYSCALL_IMPL_(int *, get_syscall_table) {
  static int syscall_table[] = {
    RISCV__NR_restart_syscall,
    RISCV__NR_exit,
    RISCV__NR_fork,
    RISCV__NR_read,
    RISCV__NR_write,
    RISCV__NR_open,
    RISCV__NR_close,
    RISCV__NR_creat,
    RISCV__NR_time,
    RISCV__NR_lseek,
    RISCV__NR_getpid,
    RISCV__NR_access,
    RISCV__NR_kill,
    RISCV__NR_dup,
    RISCV__NR_times,
    RISCV__NR_brk,
    RISCV__NR_mmap,
    RISCV__NR_munmap,
    RISCV__NR_stat,
    RISCV__NR_lstat,
    RISCV__NR_fstat,
    RISCV__NR_uname,
    RISCV__NR__llseek,
    RISCV__NR_readv,
    RISCV__NR_writev,
    RISCV__NR_mmap2,
    RISCV__NR_stat64,
    RISCV__NR_lstat64,
    RISCV__NR_fstat64,
    RISCV__NR_getuid,
    RISCV__NR_getgid,
    RISCV__NR_geteuid,
    RISCV__NR_getegid,
    RISCV__NR_fcntl64,
    RISCV__NR_exit_group,
    RISCV__NR_socketcall,
    RISCV__NR_gettimeofday,
    RISCV__NR_settimeofday,
    RISCV__NR_clock_gettime
  };
  return syscall_table;
}
