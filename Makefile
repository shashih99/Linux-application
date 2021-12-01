TARGET1=sum_on_thread
TARGET2=sum_on_many_thread
TARGET3=sum_on_malloc
TARGET4=thread_sync_issue
TARGET5=semaphore
TARGET6=synchronization_issue_mutex
TARGET7=mutex
#CROSS COMPILER
CC_COMPILER=gcc

#FLAGS
CF_FLAGS= -Wall -g -std=c99 -Werror

all: clean ${TARGET1} ${TARGET2} ${TARGET3} ${TARGET4} ${TARGET5} ${TARGET6} ${TARGET7}

${TARGET1}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

${TARGET2}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

${TARGET3}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

${TARGET4}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

${TARGET5}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

${TARGET6}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

${TARGET7}:
	${CC_COMPILER} ${CF_FLAGS} $@.c -o $@ -pthread

clean:
	rm -f ${TARGET1} ${TARGET2} ${TARGET3} ${TARGET4} ${TARGET5} ${TARGET6} ${TARGET7}
