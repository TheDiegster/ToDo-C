# Can compile into c object file using gcc, but must use g++ to turn object
# object file into executable
main: main.o
	@g++ main.o -o main -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lglad
main.o:
	@gcc -c main.c
test: test.o
	@g++ test.o -o test
test.o:
	@gcc -c test.c -g
clean:
	@rm -f main.o test.o main test