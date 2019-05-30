
OBJS := ban.o string_manipulation.o linked_list.o variable_storage.o virtual_gates.o
SRCS := ban.c
CFLAGS := -O0 -ggdb -Wall -Wextra
CC := gcc

#.SUFFIXES:

all: ban

test: ban
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -v ./ban

ban: $(OBJS) Makefile
	$(CC) $(CFLAGS) -o ban $(OBJS)


%.o: %.c | %.h
	$(CC) $(CFLAGS) -c -o $@ $<

string_manipulation.o: string_manipulation/string_manipulation.c
	$(CC) $(CFLAGS) -c -o $@ $<

linked_list.o: memory/linked_list.c
	$(CC) $(CFLAGS) -c -o $@ $<

variable_storage.o: memory/variable_storage.c
	$(CC) $(CFLAGS) -c -o $@ $<

virtual_gates.o: logic/virtual_gates.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean test
clean:
	rm *.o
	rm ban
