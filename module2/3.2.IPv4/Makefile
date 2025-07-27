CC = gcc
LDFLAGS = -lcheck -lsubunit -lm -lpthread

FILE = IPv4
# Цели по умолчанию
all: main

# Сборка основной программы
main: main.c $(FILE).c $(FILE).h
	$(CC) -o main main.c $(FILE).c

# Сборка тестов
test_build: test.o $(FILE).o
	$(CC) -o test test.o $(FILE).o $(LDFLAGS)

$(FILE).o: $(FILE).c $(FILE).h
	$(CC) -c $(FILE).c -o $(FILE).o

test.o: test.c $(FILE).h
	$(CC) -c test.c -o test.o

# Запуск основной программы
run: main
	./main 192.168.1.10 255.255.255.0 1000

# Запуск тестов
test: test_build
	./test

# Очистка
clean:
	rm -f *.o main test

# Ремейк — чистим и собираем заново
re: clean all
