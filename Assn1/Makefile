#Makefile for CSCI 261 Assignment 1

CC = gcc
WFLAG = -Wall
CFLAG = -c
DFLAG = -ggdb
IFLAG = -I
OFLAG = -o

BINARY = C:\csci261\bin
BUILD = C:\csci261\build
INCLUDE = C:\csci261\include
SOURCE = C:\csci261\src
TEST = test
EXAMPLE = C:\csci261\example

all: ${BINARY}/convert

${BINARY}/convert: ${BUILD}/main.o ${BUILD}/convert.o ${BUILD}/utility.o
	${CC} ${WFLAG} ${DFLAG} -lm ${OFLAG} ${BINARY}/convert ${BUILD}/main.o ${BUILD}/convert.o ${BUILD}/utility.o

${BUILD}/main.o: ${SOURCE}/main.c ${INCLUDE}/convert.h 
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} ${OFLAG} ${BUILD}/main.o ${SOURCE}/main.c 

${BUILD}/convert.o: ${SOURCE}/convert.c ${INCLUDE}/convert.h ${INCLUDE}/utility.h
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} -lm ${OFLAG} ${BUILD}/convert.o ${SOURCE}/convert.c

${BUILD}/utility.o: ${SOURCE}/utility.c ${INCLUDE}/utility.h
	${CC} ${WFLAG} ${CFLAG} ${DFLAG} ${IFLAG} ${INCLUDE} ${OFLAG} ${BUILD}/utility.o ${SOURCE}/utility.c


.PHONY: clean run run-example debug debug-example

clean:
	rm ${BINARY}/* ${BUILD}/*

run: ${BINARY}/convert
	${BINARY}/convert

debug: ${BINARY}/convert
	gdb ${BINARY}/convert


