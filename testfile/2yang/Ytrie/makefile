all: strsearch

strsearch: main.o trie.o
	cc -o strsearch -Wall -O3 -pedantic main.o trie.o

main.o: main.c trie.h
	cc -o main.o -Wall -pedantic -ansi -c main.c

trie.o: trie.c trie.h
	cc -o trie.o -Wall -pedantic -ansi -c trie.c

clean:
	rm main.o trie.o
