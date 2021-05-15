SRCS_MPI = main_MPI.cpp
EXEC_MPI = $(SRCS_MPI:.cpp=)
OBJS_MPI = $(SRCS_MPI:.cpp=.o)

SRCS_OMP = main_OMP.cpp
EXEC_OMP = $(SRCS_OMP:.cpp=)
OBJS_OMP = $(SRCS_OMP:.cpp=.o)

HEADERS = $(wildcard *.hpp)

CXX_OMP = g++ -fopenmp -std=c++17
CXX_MPI = mpicxx -std=c++17

$(EXEC_MPI) : $(OBJS_MPI)
	$(CXX_MPI) $(OBJS_MPI) -o $(EXEC_MPI)

$(OBJS_MPI) : $(HEADERS) $(SRCS_MPI)
	$(CXX_MPI) -c -O3 $(SRCS_MPI)

$(EXEC_OMP) : $(OBJS_OMP)
	$(CXX_OMP) $(OBJS_OMP) -o $(EXEC_OMP)

$(OBJS_OMP) : $(HEADERS) $(SRCS_OMP)
	$(CXX_OMP) -c -O3 $(SRCS_OMP)

all : distclean
	$(CXX_MPI) -c -O3 $(SRCS_MPI)
	$(CXX_MPI) $(OBJS_MPI) -o $(EXEC_MPI)
	$(CXX_OMP) -c -O3 $(SRCS_OMP)
	$(CXX_OMP) $(OBJS_OMP) -o $(EXEC_OMP)

clean :
	$(RM) $(OBJS_MPI) $(OBJS_OMP)

distclean : clean
	$(RM) $(EXEC_MPI) $(EXEC_OMP)
