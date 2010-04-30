CC = gcc
GCC = g++
RC = windres
CFLAGS = -Wall -O2
LDFLAGS = -mwindows -lgdi32 -lcomctl32

DIR_SRC = src
DIR_RES = res
DIR_OBJ = obj
DIR_BIN = bin

APPLICATION = emitter
BINARY = $(APPLICATION).exe

FILES_SRC = $(wildcard $(DIR_SRC)/*.cpp)
FILES_H   = $(wildcard $(DIR_SRC)/*.h)
FILES_RES = $(wildcard $(DIR_RES)/*.rc)
FILES_OBJ = $(patsubst $(DIR_SRC)/%.cpp, $(DIR_OBJ)/%.o, $(FILES_SRC)) $(patsubst $(DIR_RES)/%.rc, $(DIR_OBJ)/%.res, $(FILES_RES))
SQLITE_OBJ = $(DIR_OBJ)/sqlite3.o

all: $(APPLICATION)

clean:
	rm $(DIR_OBJ)/*

$(SQLITE_OBJ): $(DIR_SRC)/sqlite/sqlite3.c
	$(CC) $(CFLAGS) -Wno-uninitialized -c -o$(SQLITE_OBJ) $(DIR_SRC)/sqlite/sqlite3.c

$(APPLICATION): $(DIR_BIN)/$(BINARY)

$(DIR_BIN)/$(BINARY): $(FILES_OBJ) $(SQLITE_OBJ)
	$(GCC) $(CFLAGS) -o$@ $(FILES_OBJ) $(SQLITE_OBJ) $(LDFLAGS)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp $(DIR_SRC)/%.h
	$(GCC) $(CFLAGS) -Wno-unused-variable -c -I"$(DIR_RES)" -o$@ $<

$(DIR_OBJ)/%.res: $(DIR_RES)/%.rc
	$(RC) --input-format=rc --output-format=coff --input=$< --output=$@
