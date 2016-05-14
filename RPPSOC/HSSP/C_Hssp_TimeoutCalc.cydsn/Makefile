all: TimeoutCalc

TimeoutCalc: main.o Swd_PacketLayer.o Swd_PhysicalLayer.o TimeoutCalc.o
	gcc main.o Swd_PacketLayer.o Swd_PhysicalLayer.o TimeoutCalc.o  -lwiringPi -o TimeoutCalc

main.o: main.c main.h
	gcc -c main.c

Swd_PacketLayer.o: Swd_PacketLayer.c
	gcc -c Swd_PacketLayer.c

Swd_PhysicalLayer.o: Swd_PhysicalLayer.c Swd_PhysicalLayer.h
	gcc -c Swd_PhysicalLayer.c

TimeoutCalc.o: TimeoutCalc.c TimeoutCalc.h
	gcc -c TimeoutCalc.c

clean:
	rm *o TimeoutCalc
