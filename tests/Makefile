CC		:= riscv64-unknown-elf-gcc
OBJDUMP := riscv64-unknown-elf-objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.data

TARGET	:= add
GCC_OPTS = -g -march=rv32imafd -std=gnu99 -mabi=ilp32d
LINK_OPTS = -nostartfiles -lc -lm
LIB_DIR	:=	-L../riscv/tests/libac_sysc
LIBS	:=	-lc -lac_sysc
HAL		:=	../riscv/tests/rv_hal/get_id.S
SRCS	:=

all:	$(TARGET).c
	$(CC) -c ../riscv/tests/rv_hal/crt.S $(GCC_OPTS)
	$(CC) $(TARGET).c -o $(TARGET).run $(SRCS) $(HAL) $(LIB_DIR) $(LIBS) -T ../riscv/tests/rv_hal/test.ld $(GCC_OPTS) $(LINK_OPTS)
	$(OBJDUMP) $(TARGET).run > $(TARGET).out

clean:
	rm $(TARGET).run crt.o $(TARGET).out

run: all
	../riscv/riscv.x -- $(TARGET).run
