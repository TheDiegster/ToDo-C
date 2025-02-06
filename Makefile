# Can compile into c object file using gcc, but must use g++ to turn object
# object file into executable
main: main.o
	@g++ main.o -o main -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lglad
main.o:
	@gcc -c main.c
test1: test1.o
	@g++ test1.o -o test1
test1.o:
	@gcc -c test1.c -g
test2: test2.o
	@g++ test2.o -o test2
test2.o:
	@gcc -c test2.c -g
clean:
	@rm -f main.o test1.o test2.o main test1 test2 