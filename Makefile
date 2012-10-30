CC          = gcc
ECHO        = echo
STRIP       = strip
CFLAGS  		= -std=c99 -Wall -fnested-functions -O3 -fast -ffast-math -msse4.2 -mtune=core2 -Iinclude
LFLAGS  		= -ll
TEST  			= build/test
BM					= build/bm
SRC         = src/strlib.c
OBJ         = ${SRC:src/%.c=build/%.o}

all: $(TEST) $(BM)
	@${ECHO} "[EXEC]\t$(TEST)"
	@./$(TEST)
	@${ECHO} "[EXEC]\t$(BM)"
	@./$(BM)

$(TEST): $(OBJ) build/test.o
	@${ECHO} "[LINK]\t$(TEST)"
	@${CC} ${CFLAGS} ${OBJ} build/test.o -o $(TEST) $(LFLAGS)
	@${ECHO} "[STRIP]\t$(TEST)"
	@${STRIP} $(TEST)

$(BM): $(OBJ) build/bm.o
	@${ECHO} "[LINK]\t$(BM)"
	@${CC} ${CFLAGS} ${OBJ} build/bm.o -o $(BM) $(LFLAGS)
	@${ECHO} "[STRIP]\t$(BM)"
	@${STRIP} $(BM)

build/test.o: src/test.c
	@${ECHO} "[CC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

build/bm.o: src/bm.c
	@${ECHO} "[CC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

build/%.o: $(SRC)
	@${ECHO} "[CC]\t$<"
	@${CC} -c ${CFLAGS} -o $@ $<

clean:
	@${ECHO} "[CLEAN]"
	@rm -f $(TEST) $(BM) $(OBJ) build/bm.o build/test.o