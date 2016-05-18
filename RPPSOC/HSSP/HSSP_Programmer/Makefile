all: progsoc

progsoc: main.o DataFetch.o DeviceAcquire.o HexImage.o ProgrammingSteps.o Swd_PacketLayer.o Swd_PhysicalLayer.o
	gcc main.o DataFetch.o DeviceAcquire.o HexImage.o ProgrammingSteps.o Swd_PacketLayer.o Swd_PhysicalLayer.o -lwiringPi -o progsoc

main.o: main.c ProgrammingSteps.h HexImage.h
	gcc -c main.c

DataFetch.o: DataFetch.c DataFetch.h HexImage.h
	gcc -c DataFetch.c

DeviceAcquire.o: DeviceAcquire.c DeviceAcquire.h Swd_PhysicalLayer.h Swd_PacketLayer.h
	gcc -c DeviceAcquire.c

HexImage.o: HexImage.c HexImage.h
	gcc -c HexImage.c

ProgrammingSteps.o: ProgrammingSteps.c ProgrammingSteps.h Swd_PacketLayer.h DeviceAcquire.h DataFetch.h HexImage.h
	gcc -c ProgrammingSteps.c

Swd_PacketLayer.o: Swd_PacketLayer.c Swd_PacketLayer.h Swd_PhysicalLayer.h
	gcc -c Swd_PacketLayer.c

Swd_PhysicalLayer.o: Swd_PhysicalLayer.c Swd_PhysicalLayer.h
	gcc -c Swd_PhysicalLayer.c

clean:
	rm *o progsoc
