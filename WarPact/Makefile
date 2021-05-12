EXEC = main
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
HEADERS = $(wildcard *.hpp)
CXX = g++ -std=c++17

$(EXEC) : $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

$(OBJS) : $(HEADERS) $(SRCS)
	$(CXX) -c -O3 $(SRCS)

all : distclean
	$(CXX) -c -O3 $(SRCS)
	$(CXX) $(OBJS) -o $(EXEC)

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) $(EXEC)