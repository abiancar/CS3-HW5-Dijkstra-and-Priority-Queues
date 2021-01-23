all:
	g++ -Wall Graph.cpp  GraphTests.cpp -o gTests

run:
	./gTests
run2:
	./nasa
run3:
	./pdt

try: all run

try2: all run2

try3: all run3



