CC          = gcc
ECHO        = echo
STRIP       = strip
CFLAGS  		= -std=c99 -Wall -fnested-functions -O3 -fast -ffast-math -msse4.2 -mtune=core2
LFLAGS  		= -ll
TEST  			= test
BM					= bm
SRC         = strlib.c
OBJ         = ${SRC:.c=.o}

all: $(TEST) $(BM)
	@${ECHO} "[RUN]\t$(TEST)"
	@./$(TEST)
	@${ECHO} "[RUN]\t$(BM)"
	@./$(BM)

$(TEST): $(OBJ) test.o
	@${ECHO} "[LINK]\t$(TEST)"
	@${CC} ${CFLAGS} ${OBJ} test.o -o $(TEST) $(LFLAGS)
	@${ECHO} "[STRIP]\t$(TEST)"
	@${STRIP} $(TEST)

$(BM): $(OBJ) bm.o
	@${ECHO} "[LINK]\t$(BM)"
	@${CC} ${CFLAGS} ${OBJ} bm.o -o $(BM) $(LFLAGS)
	@${ECHO} "[STRIP]\t$(BM)"
	@${STRIP} $(BM)

test.o: test.c
	@${ECHO} "[CC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

bm.o: bm.c
	@${ECHO} "[CC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

%.o: %.c
	@${ECHO} "[CC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

clean:
	@${ECHO} "[CLEAN]"
	@rm -f $(TEST) $(BM) $(OBJ) bm.o test.o