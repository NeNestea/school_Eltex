CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread
# Цели по умолчанию
all: main

# Сборка основной программы
main: main.c phonebook.c phonebook.h
	$(CC) -o main main.c phonebook.c

# Сборка тестов
test_build: test.o phonebook.o
	$(CC) -o test test.o phonebook.o $(LDFLAGS)

phonebook.o: phonebook.c phonebook.h
	$(CC) -c phonebook.c -o phonebook.o

test.o: test.c phonebook.h
	$(CC) -c test.c -o test.o

# Запуск основной программы
run: main
	./main

# Запуск тестов
test: test_build
	./test

# Очистка
clean:
	rm -f *.o main test

# Ремейк — чистим и собираем заново
re: clean all
