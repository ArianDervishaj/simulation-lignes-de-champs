CC := gcc
CFLAGS := -g -Ofast -Wall -Wextra -fsanitize=address,undefined -fsanitize=leak -std=gnu11

LDFLAGS := -lm -lSDL2
VPATH := utils utils/gfx

# Object files for the project
OBJ := main.o vec2.o gfx.o utils.o

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

run_main: main
	./$< 3

run_tests: tests
	./$<

tests: vec_tests.o vec2.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

rebuild: clean main

clean:
	rm -f *.o main tests
