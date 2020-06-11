CC := g++

CFLAGS := -std=c++11 

SRCS := test_flex.cpp test_stack1.cpp 

OBJS := ${SRCS:.cpp=.o} opnum.o

PROGS := ${SRCS:.cpp=} 

.PHONY: all
all: ${PROGS}

test_flex: test_flex.o opnum.o
	${CC} ${CFLAGS} $^ -o $@ -ll

opnum.cpp: opnum.fl
	flex -o opnum.cpp opnum.fl
	
test_stack1: test_stack1.o 
	${CC} ${CFLAGS} $^ -o $@ 

%.o: %.cpp
	${CC} ${CFLAGS} -c $<

clean:
	rm -f ${PROGS} opnum.cpp ${OBJS} *.bak *~
