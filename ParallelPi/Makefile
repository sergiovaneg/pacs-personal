SRCS = $(wildcard main*.cpp)
EXEC = $(SRCS:.cpp=)
OBJS = $(SRCS:.cpp=.o)
HEADERS = $(wildcard *.hpp)
CXX = g++ -fopenmp -std=c++17

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