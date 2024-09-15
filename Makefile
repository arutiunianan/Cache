all:
	g++ main.cpp graph/graph.cpp -o main
	./main
	rm -rf *.o main