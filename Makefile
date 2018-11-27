ROOT = $(shell pwd)
BIN = $(ROOT)/bin
USC = $(ROOT)/src/User_Code
KNL = $(ROOT)/src/Kernel_Module
LOG = $(ROOT)/log

USR_EXE = $(BIN)/sys2018
SYSCALL = $(KNL)/system_call.ko

USC_SRC = $(wildcard $(USC)/*.c)
USC_OBJ = $(USC_SRC:.c=.o)

CURRENT = $(shell uname -r)
KDIR	= /lib/modules/$(CURRENT)/build

all: $(USR_EXE) $(SYSCALL) $(LOG)

$(USR_EXE) : $(USC_OBJ)
	mkdir -p $(BIN)
	$(CC) $^ -o $@ $(LDFLAGS)

$(SYSCALL):
	$(MAKE) -C $(KDIR) M=$(KNL) modules

$(LOG):
	mkdir -p $(LOG)

clean:
	$(RM) -rf $(BIN)
	$(RM) -rf $(LOG)
	$(MAKE) -C $(KDIR) M=$(KNL) clean

.PHONY: clean all