/******************************************************
 * This is the main file for the riscv ArchC model    *
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
 

const char *project_name="riscv";
const char *project_file="riscv.ac";
const char *archc_version="2.4.1";
const char *archc_options="-abi ";

#include  <iostream>
#include  <systemc.h>
#include  "ac_stats_base.H"
#include  "riscv.H"



int sc_main(int ac, char *av[])
{

  //!  ISA simulator
  riscv riscv_proc1("riscv");

#ifdef AC_DEBUG
  ac_trace("riscv_proc1.trace");
#endif 

  riscv_proc1.init(ac, av);
  riscv_proc1.set_prog_args();
  cerr << endl;

  sc_start();

  riscv_proc1.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  ac_stats_base::print_all_stats(std::cerr);
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  return riscv_proc1.ac_exit_status;
}
