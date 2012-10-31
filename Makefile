CC          = clang
ECHO        = echo
STRIP       = strip
CFLAGS  		= -std=c99 -Wall -O4 -ffast-math -msse4.2 -mtune=native -Iinclude
LDFLAGS  		= -ll
TEST  			= build/test
BM					= build/bm
SRC         = src/libstr.c
LIB					= build/libstr.dylib
OBJ         = ${SRC:src/%.c=build/%.o}

all: $(TEST) $(BM) $(LIB)
	@${ECHO} "[EXEC]\t$(TEST)"
	@./$(TEST)
	@${ECHO} "[EXEC]\t$(BM)"
	@./$(BM)

$(TEST): $(OBJ) build/test.o
	@${ECHO} "[LINK]\t$@"
	@${CC} ${CFLAGS} ${OBJ} build/test.o -o $@ $(LDFLAGS)
	@${ECHO} "[STRIP]\t$@"
	@${STRIP} $@

$(BM): $(OBJ) build/bm.o
	@${ECHO} "[LINK]\t$@"
	@${CC} ${CFLAGS} ${OBJ} build/bm.o -o $@ $(LDFLAGS)
	@${ECHO} "[STRIP]\t$@"
	@${STRIP} $@

$(LIB): build/libstr.o
	@${ECHO} "[LIB]\t$<"
	@${CC} ${CFLAGS} -shared $< -o $@ $(LDFLAGS)

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
	@rm -f $(TEST) $(BM) $(OBJ) $(LIB) build/bm.o build/test.o