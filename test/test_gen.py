import random
import sys

test_file = open('test/test.txt', 'w')

number_of_elements = int(sys.argv[1])
sequence = str(random.randint(1, 5)) + ' ' + str(sys.argv[1])

for i in range(number_of_elements):
    sequence = sequence + ' ' + str(random.randint(0, 10))

test_file.write(sequence)