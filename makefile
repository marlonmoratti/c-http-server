all:
	@gcc -o main app/main.c server/src/server.c

clean:
	@rm -f main
