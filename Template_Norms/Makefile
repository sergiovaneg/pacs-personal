CXX      ?= clang++
CXXFLAGS ?= -std=c++17
LINK.o := $(LINK.cc) # Use C++ linker (for implicit rule in line 25).

CPPFLAGS += -O3 -I. -I/home/sergiovaneg/pacs-examples/Examples/include
LDLIBS += -L/home/sergiovaneg/pacs-examples/Examples/lib -Wl,-rpath=/home/sergiovaneg/pacs-examples/Examples/lib -lpacs

SRCS=$(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
HEADERS=$(wildcard *.hpp)

exe_sources=$(filter main%.cpp,$(SRCS))
EXEC=$(exe_sources:.cpp=)

.phony= all parallel clean distclean

.DEFAULT_GOAL = all

all: $(EXEC)

parallel: CPPFLAGS += -DPARALLELEXEC -I$(mkTbbInc)
parallel: LDLIBS += -L$(mkTbbLib) -ltbb
parallel: all

$(EXEC): $(OBJS)

$(OBJS): $(SRCS) $(HEADERS)

clean:
	$(RM) -f $(OBJS)

distclean: clean
	$(RM) -f $(EXEC)
	$(RM) *.out *.bak *~