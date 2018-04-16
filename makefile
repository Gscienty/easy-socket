PWD := $(shell pwd)
SHELL := /bin/bash
BIN_DIR := $(PWD)/bin/
OBJS_DIR := $(PWD)/objs/
SRC_DIR := $(PWD)/src/
INC_DIR := $(PWD)/include/

AR_RV = ar rv
CC = g++
FLAGS = -shared -fPIC
STANDARD = -std=c++11

$(shell mkdir -p ${BIN_DIR})
$(shell mkdir -p ${OBJS_DIR})

SOURCE = $(patsubst %.cc,%,$(notdir $(wildcard $(SRC_DIR)*.cc)))


all: libeys.a libeys.so

libeys.so: $(SOURCE)
	$(CC) $(STANDARD) $(SOURCE:%=$(OBJS_DIR)%.o) $(FLAGS) -o $(BIN_DIR)$@

libeys.a: $(SOURCE)
	$(AR_RV) $(BIN_DIR)$@ $(SOURCE:%=$(OBJS_DIR)%.o)

$(SOURCE):
	$(CC) $(STANDARD) $(FLAGS) -I $(INC_DIR) -c $(SRC_DIR)$@.cc -o $(OBJS_DIR)$@.o

clean:
	rm -rf $(OBJS_DIR) $(BIN_DIR)
