ROOT = $(shell pwd)
BIN = $(ROOT)/bin
USC = $(ROOT)/src/User_Code
KNL = $(ROOT)/src/Kernal_Module

USR_EXE = $(BIN)/sys2018
SYSCALL = $(BIN)/syscall.ko

USC_SRC = $(wildcard $(USC)/*.c)
USC_OBJ = $(USC_SRC: .c=.o)

CURRENT = $(shell uname -r)
KDIR	=/lib/modules/$(CURRENT)/build

all: $(USR_EXE) $(SYSCALL)

$(USR_EXE) : $(USC_OBJ)
	mkdir -p $(BIN)
	$(CC) -o $@ $^

$(SYSCALL):
	$(MAKE) -C $(KDIR) M=$(KNL) modules

clean: 
	$(RM) -rf $(BIN)
	$(MAKE) -C $(KDIR) M=$(KNL) clean


.PHONY: clean all