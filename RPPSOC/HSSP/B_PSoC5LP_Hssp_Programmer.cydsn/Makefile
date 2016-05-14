all: progsoc

progsoc: main.o DataFetch.o DeviceAcquire.o HexImage.o ProgrammingSteps.o Swd_PacketLayer.o Swd_PhysicalLayer.o Timeout.o
	g++ main.o DataFetch.o DeviceAcquire.o HexImage.o ProgrammingSteps.o Swd_PacketLayer.o Swd_PhysicalLayer.o Timeout.o -o progsoc

main.o: main.cpp
	g++ -c main.cpp

DataFetch.o: DataFetch.c
	g++ -c DataFetch.cpp

DeviceAcquire.o: DeviceAcquire.cpp
	g++ -c DeviceAcquire.cpp

HexImage.o: HexImage.cpp
	g++ -c HexImage.cpp

ProgrammingSteps.o: ProgrammingSteps.cpp
	g++ -c ProgrammingSteps.cpp

Swd_PacketLayer.o: Swd_PacketLayer.cpp
	g++ -c Swd_PacketLayer.cpp

Swd_PhysicalLayer.o: Swd_PhysicalLayer.cpp
	g++ -c Swd_PhysicalLayer.cpp

Timeout.o: Timeout.cpp
	g++ -c Timeout.cpp

clean:
	rm *o progsoc
