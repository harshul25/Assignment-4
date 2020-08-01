warnings_BAD: *.c
	gcc -Werror -Wall -g -std=gnu99 -o 160365750_193292800_a04 *.c -lrt -lpthread
	
warnings_OK: *.c
	gcc -Wall -g -std=gnu99 -o 160365750_193292800_a04 *.c -lrt -lpthread
	
clean: *.c
	rm 160365750_193292800_a04
