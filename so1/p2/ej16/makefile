CC = gcc
CFLAGS = -pthread
SRC = main.c ./hash/hash.c
OUT = program

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)
