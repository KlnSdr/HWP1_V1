CC=gcc
CPP=g++
CFLAGS=-I.
OBJ = serial_ctl.o 

%.o: %.c $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS)

serial_ctl: $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS)
