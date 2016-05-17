all: progsoc

progsoc: main.o DataFetch.o DeviceAcquire.o HexImage.o ProgrammingSteps.o Swd_PacketLayer.o Swd_PhysicalLayer.o
	gcc main.o DataFetch.o DeviceAcquire.o HexImage.o ProgrammingSteps.o Swd_PacketLayer.o Swd_PhysicalLayer.o -lwiringPi -o progsoc

main.o: main.c
	gcc -c main.c

DataFetch.o: DataFetch.c
	gcc -c DataFetch.c

DeviceAcquire.o: DeviceAcquire.c
	gcc -c DeviceAcquire.c

HexImage.o: HexImage.c
	gcc -c HexImage.c

ProgrammingSteps.o: ProgrammingSteps.c
	gcc -c ProgrammingSteps.c

Swd_PacketLayer.o: Swd_PacketLayer.c
	gcc -c Swd_PacketLayer.c

Swd_PhysicalLayer.o: Swd_PhysicalLayer.c
	gcc -c Swd_PhysicalLayer.c

clean:
	rm *o progsoc
