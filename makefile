CFLAGS = -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs -O3
all: Gauss.out GaussSimple.out clear
%.out: %.o matrix.o
	gcc $(CFLAGS) -g $^ -lm -o $@
%.o: %.c matrix.h task.h
	gcc -c $(CFLAGS) $<
clear:
	rm -f *.o
clearOut:
	rm -f aTest.out a.out
