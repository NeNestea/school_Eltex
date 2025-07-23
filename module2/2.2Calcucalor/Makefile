CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread
# Цели по умолчанию
all: main

# Сборка основной программы
main: main.c calculator.c calculator.h
	$(CC) -o main main.c calculator.c

# Сборка тестов
test_build: test.o calculator.o
	$(CC) -o test test.o calculator.o $(LDFLAGS)

calculator.o: calculator.c calculator.h
	$(CC) -c calculator.c -o calculator.o

test.o: test.c calculator.h
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
