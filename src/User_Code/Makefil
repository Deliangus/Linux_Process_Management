all: bin

remake: clean all

clean:
	@$(RM) -rf bin

bin:
	gcc -o sys2018 monitor.c log.c loader.c -lrt -lpthread
