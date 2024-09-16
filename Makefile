all:
	g++ main.cpp graph/graph.cpp -o main
	python3.8 test/test_gen.py 1000
	./main test/test.txt
	rm -rf *.o main