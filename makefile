
main:main.cpp config.h
	g++ -g  main.cpp -o main -O3 -I/usr/include/mysql -lmysqlclient -L/usr/lib/mysql -lpthread
