PACKAGE    := mtf7
LIB_TARGET := LIB_TARGET_unknown_os_type

BIN_TARGET = 

LOCAL_CFLAGS = -I ./include -O3

SRC = src/*.cpp

SRC_FILES := $(shell ls src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,${SRC_FILES})
HDR_FILES := $(patsubst src/%.cpp,include/mtf7/%.h,${SRC_FILES})


ifeq ($(OSTYPE), linux)
	CXX := g++ -fPIC
	LD  := g++ -shared
	LIB_TARGET := lib/lib${PACKAGE}.so
endif

ifeq ($(OSTYPE), darwin)
	LD  := clang++ -dynamiclib
	CXX := clang++ -fPIC
	LIB_TARGET := lib/lib${PACKAGE}.dylib
endif

all: ${LIB_TARGET} ${BIN_TARGET}

bin/test% : ${LIB_TARGET} test/test%.cpp
#	@echo -----
#	@echo ostype: ${OSTYPE}
#	@echo -----
	${CXX} ${ROOT_CFLAGS} ${LOCAL_CFLAGS} -o $@ $^ ${ROOT_LIBS}

${LIB_TARGET}: ${OBJ_FILES}
	${LD} $^ -o $@ -lc

obj/%.o: src/%.cpp
	${CXX} ${LOCAL_CFLAGS} -o $@ -c $^

clean:
	@${RM} *~ */*~ */*/*~ 
	@${RM} obj/* ${LIB_TARGET} ${BIN_TARGET}
	@${RM} */*.d */*.so *.d *.so
