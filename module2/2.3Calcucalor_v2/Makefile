CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread
# Цели по умолчанию
all: main

# Сборка основной программы
main: main.c calculator_v2.c calculator_v2.h
	$(CC) -o main main.c calculator_v2.c

# Сборка тестов
test_build: test.o calculator_v2.o
	$(CC) -o test test.o calculator_v2.o $(LDFLAGS)

calculator.o: calculator_v2.c calculator_v2.h
	$(CC) -c calculator_v2.c -o calculator_v2.o

test.o: test.c calculator_v2.h
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
