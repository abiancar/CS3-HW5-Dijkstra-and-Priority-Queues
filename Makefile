all:
	g++ -Wall Graph.cpp  GraphTests.cpp -o gTests
	g++ -Wall Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpqTests
	g++ -Wall Dijkstra.cpp Graph.cpp BetterPriorityQueue.cpp -o dijkstra
run:
	./gTests
run2:
	./bpqTests
run3:
	./dijkstra
try: all run

try2: all run2

try3: all run3



