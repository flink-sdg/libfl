CC = gcc

BUILD = build
HEADERS = h
LIBFL = flarr fldict flutil 
LIBFL_O = ${addprefix ${BUILD}/, ${addsuffix .o,${LIBFL}}}

define COMPILE
${BUILD}/$1.o: $1/$1.c
	${CC} -c $$^ -o $$@ 
endef

define CP_HEADER
${HEADERS}/$1.h:
	cp $1/$1.h ${HEADERS}
endef

build: dirs libflh ${BUILD}/libfl.a main

dirs:
	mkdir -p ${BUILD}
	mkdir -p ${HEADERS}

libflh: ${addprefix ${HEADERS}/, ${addsuffix .h,${LIBFL}}}

${BUILD}/libfl.a: ${LIBFL_O}
	ar rcs ${BUILD}/libfl.a ${LIBFL_O}

main: ${BUILD}/libfl.a ${BUILD}/main.o
	${CC} ${BUILD}/main.o -L./${BUILD} -lfl -o main

${BUILD}/main.o: main.c
	${CC} -c main.c -o ${BUILD}/main.o

${foreach F,${LIBFL},${eval ${call CP_HEADER,${F}}}}
${foreach F,${LIBFL},${eval ${call COMPILE,${F}}}}
