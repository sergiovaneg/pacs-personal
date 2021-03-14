EXEC_NAME=LeibnizPi

$(EXEC_NAME):main.o
	g++ main.o -o $(EXEC_NAME)

clean:
	rm -f main.o $(EXEC_NAME)

main.o:main.cpp
	g++ main.cpp -c
