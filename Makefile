TARGET1=sum_on_thread
TARGET2=sum_on_many_thread

#CROSS COMPILER
CC_COMPILER=gcc

#FLAGS
CF_FLAGS= -Wall -g -std=c99 -Werror

all: clean ${TARGET1} ${TARGET2}

${TARGET1}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

${TARGET2}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

clean:
	rm -f ${TARGET1} ${TARGET2}
