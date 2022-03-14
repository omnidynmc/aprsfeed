CC=g++
CFLAGS=
LIBS=-lmysqlcppconn

OBJ = main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

m: $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)
