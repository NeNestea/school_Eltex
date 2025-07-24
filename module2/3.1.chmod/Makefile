CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread
# Цели по умолчанию
all: main

# Сборка основной программы
main: main.c chmod.c chmod.h
	$(CC) -o main main.c chmod.c

# Сборка тестов
# test_build: test.o chmod.o
#	$(CC) -o test test.o chmod.o $(LDFLAGS)

chmod.o: chmod.c chmod.h
	$(CC) -c chmod.c -o chmod.o

#test.o: test.c chmod.h
#	$(CC) -c test.c -o test.o

# Запуск основной программы
run: main
	./main

# Запуск тестов
#test: test_build
#	./test

# Очистка
clean:
	rm -f *.o main test

# Ремейк — чистим и собираем заново
re: clean all
