CC=gcc

main:
	${CC} -c argumentize.c ls.c commandParser.c display.c execCmd.c input.c lineParser.c pinfo.c pipe.c redirection.c
	$(CC) main.c argumentize.o ls.o commandParser.o display.o execCmd.o input.o lineParser.o pinfo.o pipe.o redirection.o -o sonu

sonu:
	${CC} -c argumentize.c ls.c commandParser.c display.c execCmd.c input.c lineParser.c pinfo.c pipe.c redirection.c
	$(CC) main.c argumentize.o ls.o commandParser.o display.o execCmd.o input.o lineParser.o pinfo.o pipe.o redirection.o -o sonu



clean:
	rm *.o
	rm sonu
