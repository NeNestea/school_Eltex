CC = gcc

FILE = phonebook_v2
# Цели по умолчанию
all: main

# Сборка основной программы
main: libcontacts.so main.c $(FILE).c $(FILE).h
	$(CC) main.c -L. -lcontacts -o program

$(FILE).o: $(FILE).c $(FILE).h
	$(CC) -fPIC -c $(FILE).c -o $(FILE).o

libcontacts.so: $(FILE).o
	gcc -shared -o libcontacts.so $(FILE).o

# Запуск основной программы
run: main
	LD_LIBRARY_PATH=. ./program

# Очистка
clean:
	rm -f *.o *.so program

# Ремейк — чистим и собираем заново
re: clean all
