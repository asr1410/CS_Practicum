all:main

main: server client

server: server-kv.c
	gcc server-kv.c -o server-kv

client: client-kv.c
	gcc client-kv.c -o client-kv

clean:
	rm -f server-kv client-kv