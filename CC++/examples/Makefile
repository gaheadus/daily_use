# 04/09/03 -- djh

CC = gcc

CFLAGS = -Wall -ansi -pedantic

OBJECTS = arrays_ptrs command_args count_char count_char2 hello hello2	\
filecopy filecopy2 func_ptrs io mem_mgt swap temps temps2 temps3	\
temps4

all:	${OBJECTS}

arrays_ptrs:	arrays_ptrs.c
	${CC} ${CFLAGS} arrays_ptrs.c -o $@

command_args:	command_args.c
	${CC} ${CFLAGS} command_args.c -o $@

count_char:	count_char.c
	${CC} ${CFLAGS} count_char.c -o $@

count_char2:	count_char2.c
	${CC} ${CFLAGS} count_char2.c -o $@

hello:	hello.c
	${CC} ${CFLAGS} hello.c -o $@

hello2:	hello2a.c hello2b.c hello2.h
	${CC} ${CFLAGS} hello2a.c hello2b.c -o $@

filecopy:	filecopy.c
	${CC} ${CFLAGS} filecopy.c -o $@

filecopy2:	filecopy2.c
	${CC} ${CFLAGS} filecopy2.c -o $@

func_ptrs:	func_ptrs.c
	${CC} ${CFLAGS} func_ptrs.c -o $@

io:	io.c
	${CC} ${CFLAGS} io.c -o $@

mem_mgt:	mem_mgt.c
	${CC} ${CFLAGS} mem_mgt.c -o $@

struct_ptrs:	struct_ptrs.c
	${CC} ${CFLAGS} struct_ptrs.c -o $@

swap:	swap.c
	${CC} ${CFLAGS} swap.c -o $@

temps:	temps.c
	${CC} ${CFLAGS} temps.c -o $@

temps2:	temps2.c
	${CC} ${CFLAGS} temps2.c -o $@

temps3:	temps3.c
	${CC} ${CFLAGS} temps3.c -o $@

temps4:	temps4.c
	${CC} ${CFLAGS} temps4.c -o $@

clean:	
	rm -f ${OBJECTS} *.o
