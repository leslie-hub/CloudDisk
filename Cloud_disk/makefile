#SrcFiles=$(wildcard *.c)

IncPath=-I/usr/include/mysql/ -I/home/itcast/driver/mongo/include -I/home/itcast/driver/boost/include
LibPath=-L/usr/lib64/mysql/ -L/home/itcast/driver/boost/lib -L/home/itcast/driver/mongo/lib
PubLib=-lmysqlclient -ldl -lpthread -lrt -lmongoclient -lboost_thread -lboost_filesystem -lboost_program_options


all:main
main:main.cpp CCMysql.cpp CCMongo.cpp
	g++ -o $@ $^ -I$(IncPath) -L$(LibPath) $(PubLib)

clean:
	-rm -f main

