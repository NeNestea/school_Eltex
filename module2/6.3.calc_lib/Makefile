CC = gcc
CFLAGS = -Wall -Wextra -fPIC
LDFLAGS = -ldl

LIB_DIR = lib
LIBS = addition subtraction multiplication division

SRC = main.c calculator_v2.c
OBJ = main.o calculator_v2.o

.PHONY: all clean run libs

all: libs calculator_v2

calculator_v2: $(SRC)
	$(CC) $(CFLAGS) -o calculator_v2 $(SRC) $(LDFLAGS)

libs: $(LIB_DIR) $(LIBS:%=$(LIB_DIR)/%.so)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(LIB_DIR)/%.so: %.c
	$(CC) $(CFLAGS) -shared -o $@ $<

clean:
	rm -f calculator_v2 *.o
	rm -rf $(LIB_DIR)

run: all
	./calculator_v2
