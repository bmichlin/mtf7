.PHONY = all

PACKAGE           := mtf7

UNKNOWN_OS_MARKER := UnknownOS
BAIL_UNKNOWN_OS   := 
LIB_TARGET        := ${UNKNOWN_OS_MARKER}


LOCAL_CFLAGS = -I ./include -O3

TEST_FILES := $(shell ls test/test*.cpp)
BIN_TARGET := $(patsubst test/%.cpp,bin/%,${TEST_FILES})

SRC_FILES := $(shell ls src/*.cpp)
OBJ_FILES := $(patsubst src/%.cpp,obj/%.o,${SRC_FILES})
HDR_FILES := $(patsubst src/%.cpp,include/mtf7/%.h,${SRC_FILES})

LD_BASE  :=
CXX_BASE :=

ifeq ($(OSTYPE), linux)
	CXX_BASE := g++ -fPIC
	LD_BASE  := g++ -shared
	LIB_TARGET := lib/lib${PACKAGE}.so
endif

ifeq ($(OSTYPE), darwin)
	LD_BASE  := clang++ -dynamiclib
	CXX_BASE := clang++ -fPIC
	LIB_TARGET := lib/lib${PACKAGE}.dylib
endif

ifeq (${LIB_TARGET}, ${UNKNOWN_OS_MARKER})
	BAIL_UNKNOWN_OS := @echo; echo "Unkown Operating System: ${OSTYPE}. Exiting."; echo; exit 1
endif


SILENT_BUILD = 1
ifeq (${SILENT_BUILD}, 1)
	LD  = @echo ++ Linking $@ ; ${LD_BASE}
	CXX = @echo -- Compiling $@ ; ${CXX_BASE}
else
	LD  := ${LD_BASE}
	CXX := ${CXX_BASE}
endif

DEBUG_FLAGS = 
ifeq ($(MTF7_DEBUG),1)
	DEBUG_FLAGS = -g -ggdb -DEBUG_BUILD
endif

all: ${LIB_TARGET} ${BIN_TARGET}
#	@echo LIB_TARGET: ${LIB_TARGET}
#	@echo BIN_TARGET: ${BIN_TARGET}
	@echo "+-------------------------------------+"
	@echo "| Binary targets built successfully   |"
	@echo "+-------------------------------------+"

bin/test% : ${LIB_TARGET} test/test%.cpp
	${CXX} ${ROOT_CFLAGS} ${DEBUG_FLAGS} ${LOCAL_CFLAGS} -o $@ $^ ${ROOT_LIBS}

${LIB_TARGET}: ${OBJ_FILES}
	${BAIL_UNKNOWN_OS}
	${LD} ${DEBUG_FLAGS} $^ -o $@ -lc
	@echo "+--------------------------------------------- "
	@echo "| Library ${LIB_TARGET} built successfully "
	@echo "+--------------------------------------------- "

obj/%.o: src/%.cpp 
	${CXX} ${DEBUG_FLAGS} ${LOCAL_CFLAGS} -o $@ -c $^

clean:
	@${RM} *~ */*~ */*/*~ 
	@${RM} obj/* ${LIB_TARGET} ${BIN_TARGET}
	@${RM} */*.d */*.so *.d *.so
