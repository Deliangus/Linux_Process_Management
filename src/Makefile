CC       := gcc
FLAGS    := -Wall -Os

TOOLSRCS := $(shell find src/tools -type f -name *.c)
SRCS  := $(filter-out $(TOOLSRCS) $(wildcard src/*.c), $(shell find src -type f -name *.c))

OBJS     := $(patsubst src/%,obj/%,$(SRCS:.c=.o))

all: bin bin/Syscall

remake: clean all

clean:
	@$(RM) -rf obj
	@$(RM) -rf bin

-include $(OBJS:.o=.d)

bin: $(OBJS) src/User_Code
	@mkdir -p $(dir $@)
	$(CC) -o bin $^ $(LIB)

bin/Syscall: $(OBJS) src/Kernal_Module
	$(MAKE) -C $(dir $@) M=$(PWD) modules

.PHONY: all remake clean
