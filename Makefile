all:bin

bin:
	@mkdir -p ${dir $@}
	gcc -o bin/sys2018 src/User_Code/monitor.c src/User_Code/log.c src/User_Code/loader.c -lrt -lpthread

clean:
	@$(RM) -rf bin