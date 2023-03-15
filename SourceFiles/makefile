#compile:
#	g++ -o server.out  *.cpp -std=c++11
#	g++ -o client.out  *.cpp -std=c++11

all: server.out client.out

client.out: client.o
	g++ -std=c++11 -pthread -o client.out client.o

client.o: client.cpp
	g++ -std=c++11 -c client.cpp

server.out: server.o KnnEuclidean.o KnnManhattan.o KnnChebyshev.o  KnnCanberra.o KnnMinkowski.o FileValidate.o Knn.o CLI.o Command.o CommandBegin.o Upload.o Parameters.o Classification.o DefaultIO.o SocketIO.o  PreparedVectors.o Elements.o ResultFile.o
	g++ -std=c++11 -pthread -o server.out server.o KnnEuclidean.o KnnManhattan.o KnnChebyshev.o  KnnCanberra.o KnnMinkowski.o FileValidate.o Knn.o CLI.o Command.o CommandBegin.o Upload.o Parameters.o Classification.o DefaultIO.o SocketIO.o PreparedVectors.o Elements.o ResultFile.o

server.o: server.cpp KnnEuclidean.h  KnnManhattan.h KnnChebyshev.h KnnCanberra.h KnnMinkowski.h FileValidate.h
	g++ -std=c++11 -c server.cpp

Knn.o: Knn.cpp Knn.h
	g++ -std=c++11 -c Knn.cpp

KnnEuclidean.o: KnnEuclidean.cpp KnnEuclidean.h
	g++ -std=c++11 -c KnnEuclidean.cpp

KnnManhattan.o: KnnManhattan.cpp KnnManhattan.h
	g++ -std=c++11 -c KnnManhattan.cpp

KnnChebyshev.o: KnnChebyshev.cpp KnnChebyshev.h
	g++ -std=c++11 -c KnnChebyshev.cpp

KnnCanberra.o: KnnCanberra.cpp KnnCanberra.h
	g++ -std=c++11 -c KnnCanberra.cpp

KnnMinkowski.o: KnnMinkowski.cpp KnnMinkowski.h
	g++ -std=c++11 -c KnnMinkowski.cpp

FileValidate.o: FileValidate.cpp FileValidate.h
	g++ -std=c++11 -c FileValidate.cpp

Command.o: Command.cpp Command.h
	g++ -std=c++11 -c Command.cpp


CommandBegin.o: CommandBegin.cpp CommandBegin.h
	g++ -std=c++11 -c CommandBegin.cpp

Upload.o: Upload.cpp Upload.h
	g++ -std=c++11 -c Upload.cpp

Parameters.o: Parameters.cpp Parameters.h
	g++ -std=c++11 -c Parameters.cpp

SocketIO.o: SocketIO.cpp SocketIO.h
	g++ -std=c++11 -c SocketIO.cpp

DefaultIO.o: DefaultIO.cpp DefaultIO.h
	g++ -std=c++11 -c DefaultIO.cpp

CLI.o: CLI.cpp CLI.h
	g++ -std=c++11 -c CLI.cpp
Classification.o: Classification.cpp Classification.h
	g++ -std=c++11 -c Classification.cpp
PreparedVectors.o: PreparedVectors.cpp PreparedVectors.h
	g++ -std=c++11 -c PreparedVectors.cpp

Elements.o: Elements.cpp Elements.h
	g++ -std=c++11 -c Elements.cpp

ResultFile.o: ResultFile.cpp ResultFile.h
	g++ -std=c++11 -c ResultFile.cpp
clean:
	rm -f *.o server.out client.out

