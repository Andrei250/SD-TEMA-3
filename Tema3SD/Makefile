build: build_p1 build_p2 build_p3 build_p4 build_bonus

build_p1:
	gcc -g -std=gnu99 p1.c -o p1 -Wall -lm

build_p2:
	gcc -g -std=gnu99 p2.c -o p2 -Wall -lm

build_p3:
	gcc -g -std=gnu99 p3.c -o p3 -Wall -lm

build_p4:
	gcc -g -std=gnu99 p4.c -o p4 -Wall -lm

build_bonus:
	gcc -g -std=gnu99 bonus.c -o bonus -Wall -lm

clean:
	rm -rf p1 p2 p3 p4 bonus

run:
	valgrind --leak-check=full  --show-leak-kinds=all ./p1
