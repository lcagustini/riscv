# ####################################################
# This is the Makefile for building the riscv ArchC model
# This file is automatically generated by ArchC
# WITHOUT WARRANTY OF ANY KIND, either express
# or implied.
# For more information on ArchC, please visit:   
# http://www.archc.org                           
#                                                
# The ArchC Team                                 
# Computer Systems Laboratory (LSC)              
# IC-UNICAMP                                     
# http://www.lsc.ic.unicamp.br                   
# ####################################################


INC_DIR := -I. `pkg-config --cflags systemc` `pkg-config --cflags archc` 

LIB_SYSTEMC := `pkg-config --libs systemc`
LIB_ARCHC := `pkg-config --libs archc`
LIB_POWERSC := 
LIB_DWARF := 
LIBS := $(LIB_SYSTEMC) $(LIB_ARCHC) $(LIB_POWERSC) $(LIB_DWARF) -lm $(EXTRA_LIBS)
CC :=   g++
OPT :=   -O3
DEBUG :=   -g
OTHER := -std=c++11  -DAC_MATCH_ENDIANNESS  -Wno-deprecated
CFLAGS := $(DEBUG) $(OPT) $(OTHER)  

TARGET := riscv

# These are the source files automatically generated by ArchC, that must appear in the SRCS variable
ACSRCS := $(TARGET)_arch.cpp $(TARGET)_arch_ref.cpp $(TARGET).cpp

# These are the source files automatically generated  by ArchC that are included by other files in ACSRCS
ACINCS := $(TARGET)_isa_init.cpp

# These are the header files automatically generated by ArchC
ACHEAD := $(TARGET)_parms.H $(TARGET)_arch.H $(TARGET)_arch_ref.H $(TARGET)_isa.H $(TARGET)_bhv_macros.H  $(TARGET)_syscall_inc.H $(TARGET).H


# These are the library files provided by ArchC
# They are stored in the archc/lib directory
ACLIBFILES := ac_decoder_rt.o ac_module.o ac_mem.o ac_utils.o ac_hltrace.o ac_syscall.o 

# These are the source files provided by the user + ArchC sources
SRCS := main.cpp $(ACSRCS)  $(TARGET)_syscall.cpp

OBJS := $(SRCS:.cpp=.o)

EXE := $(TARGET).x

.SUFFIXES: .cc .cpp .o .x

all:  $(TARGET)_syscall.H $(ACHEAD) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(INC_DIR) $(LIB_DIR) -o $@ $(OBJS) $(LIBS) 2>&1 | c++filt

# Copy from template if main.cpp not exist
main.cpp:
	cp main.cpp.tmpl main.cpp

# Copy from template if $(TARGET)_syscall.H not exist
$(TARGET)_syscall.H:
	cp $(TARGET)_syscall.H.tmpl $(TARGET)_syscall.H

$(TARGET).o: $(TARGET).cpp $(TARGET)_isa.cpp
	$(CC) $(CFLAGS) $(INC_DIR) -c $<

.cpp.o:
	$(CC) $(CFLAGS) $(INC_DIR) -c $<

.cc.o:
	$(CC) $(CFLAGS) $(INC_DIR) -c $<

clean:
	rm -f $(OBJS) *~ $(EXE) core *.o *.a 

model_clean:
	rm -f $(ACSRCS) $(ACHEAD) $(ACINCS) *.tmpl loader.ac 

sim_clean: clean model_clean

distclean: sim_clean
	rm -f main.cpp Makefile
