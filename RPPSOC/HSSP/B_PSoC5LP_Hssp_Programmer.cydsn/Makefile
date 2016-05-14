all: progsoc

progsoc: main.o DataFetch.o DeviceAcquire.o HexImage.o ProgrammingSteps.o Swd_PacketLayer.o Swd_PhysicalLayer.o Timeout.o
	g++ main.o DataFetch.o DeviceAcquire.o HexImage.o ProgrammingSteps.o Swd_PacketLayer.o Swd_PhysicalLayer.o Timeout.o -o progsoc

main.o: main.c
	g++ -c main.c

DataFetch.o: DataFetch.c
	g++ -c DataFetch.c

DeviceAcquire.o: DeviceAcquire.c
	g++ -c DeviceAcquire.c

HexImage.o: HexImage.c
	g++ -c HexImage.c

ProgrammingSteps.o: ProgrammingSteps.c
	g++ -c ProgrammingSteps.c

Swd_PacketLayer.o: Swd_PacketLayer.c
	g++ -c Swd_PacketLayer.c

Swd_PhysicalLayer.o: Swd_PhysicalLayer.c
	g++ -c Swd_PhysicalLayer.c

Timeout.o: Timeout.c
	g++ -c Timeout.c

clean:
	rm *o progsoc
