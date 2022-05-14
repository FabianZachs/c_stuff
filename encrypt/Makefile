CC=clang
CFLAGS=-pthread
OBJS=encrypter.o
# no header files DEPS=

KEY=23

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

encrypter: $(OBJS)
	$(CC) -o $@ $^ 

check: encrypter
	time ./encrypter files/random.txt $(KEY) 
	diff files/random.txt.encrypted references/random.txt.encrypted

.PHONY: clean
clean:
	rm -f *.o encrypter *encrypted
