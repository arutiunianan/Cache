all:
	g++ main.cpp graph/graph.cpp -o main
	./main 3

tests:
	g++ main.cpp graph/graph.cpp -o main
	python3.8 test/test_gen.py 100000
	./main 3 test/test.txt

lfu:
	g++ main.cpp graph/graph.cpp -o lfu
	./lfu 1

pca:
	g++ main.cpp graph/graph.cpp -o pca
	./pca 2

lfu_tests:
	g++ main.cpp graph/graph.cpp -o lfu_tests
	python3.8 test/test_gen.py 100000
	./lfu_tests 1 test/test.txt

pca_tests:
	g++ main.cpp graph/graph.cpp -o pca_tests
	python3.8 test/test_gen.py 100000
	./pca_tests 2 test/test.txt