CC=clang
CFLAGS=-pthread
OBJS=encrypter.o
# no header files DEPS=

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

encrypter: $(OBJS)
	$(CC) -o $@ $^ 


.PHONY: clean
clean:
	rm -f *.o encrypter
