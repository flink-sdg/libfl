CC = gcc

BUILD = build
HEADERS = h
LIBFL = flarr fldict flutil fltime
LIBFL_O = ${addprefix ${BUILD}/, ${addsuffix .o,${LIBFL}}}

define COMPILE
${BUILD}/${1}.o: ${1}/${1}.c
ifeq (${DEBUG},true)
	${CC} -c -g -ggdb $$^ -I./${HEADERS} -o $$@
else
	${CC} -c $$^ -I./${HEADERS} -o $$@
endif
endef

build: dirs libflh ${BUILD}/libfl.a main

clean:
	rm -rf ./${BUILD}; rm -rf ./${HEADERS}; rm main

clean-build: clean build

dirs:
	mkdir -p ${BUILD}
	mkdir -p ${HEADERS}

libflh: 
	${foreach F,${LIBFL},cp ${F}/${F}.h ${HEADERS};}

${BUILD}/libfl.a: ${LIBFL_O}
	ar rcs ${BUILD}/libfl.a ${LIBFL_O}

main: ${BUILD}/libfl.a ${BUILD}/main.o
	${CC} ${BUILD}/main.o -L./${BUILD} -lfl -lm -o main

${BUILD}/main.o: main.c
ifeq (${DEBUG},true)
	${CC} -c -g -ggdb main.c -I./${HEADERS} -o ${BUILD}/main.o
else
	${CC} -c main.c -I./${HEADERS} -o ${BUILD}/main.o
endif

${foreach F,${LIBFL},${eval ${call COMPILE,${F}}}}
