CC = gcc

FILE = phonebook_v2
# Цели по умолчанию
all: main

# Сборка основной программы
main: libcontacts.a main.c $(FILE).c $(FILE).h
	$(CC) main.c -L. -lcontacts -o program

$(FILE).o: $(FILE).c $(FILE).h
	$(CC) -c $(FILE).c -o $(FILE).o

libcontacts.a: $(FILE).o
	ar rcs libcontacts.a $(FILE).o

# Запуск основной программы
run: main
	./program

# Очистка
clean:
	rm -f *.o *.a program

# Ремейк — чистим и собираем заново
re: clean all
