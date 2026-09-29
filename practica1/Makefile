CC = gcc

objects = p1 p2 p3

all: $(objects)

%: %.c
	$(CC) -o $@ $<

clean:
	rm -f $(objects)