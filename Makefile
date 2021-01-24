all:
	g++ -Wall Graph.cpp  GraphTests.cpp -o gTests
	g++ -Wall Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpqTests
run:
	./gTests
run2:
	./bpqTests
try: all run

try2: all run2




