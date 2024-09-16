all:
	g++ main.cpp graph/graph.cpp -o main
	./main
	rm -rf *.o main

tests:
	g++ main.cpp graph/graph.cpp -o main
	python3.8 test/test_gen.py 100000
	./main test/test.txt
	rm -rf *.o main