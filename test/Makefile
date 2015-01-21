#dummy make file for testing

SOURCES=block_operator.cpp \
	data_operator.cpp \
	emutf_counter_block_operator.cpp \
	emutf_data_operator.cpp \
	emutf_header_block_operator.cpp \
	emutf_operator_builder.cpp \
	emutf_event_generator.cpp \
	emutf_cscmedata_block_operator.cpp \
	emutf_rpcdata_block_operator.cpp \
	emutf_spoutputdata_block_operator.cpp \
	emutf_trailer_block_operator.cpp \
	emutf_amc13_header_block_operator.cpp \
	emutf_amc13_trailer_block_operator.cpp

OBJECTS=$(SOURCES:.cpp=.o)

BIN_TARGET = test_data_operator
#test_event_generator
#test_data_operator

INCLUDES = -I ../include/

CC = g++

all: $(OBJECTS) $(BIN_TARGET) 
	@echo Simple compiler

$(BIN_TARGET): $(BIN_TARGET).cpp $(OBJECTS) 
	$(CC) $(INCLUDES) $(OBJECTS) $(BIN_TARGET).cpp -o $(BIN_TARGET)


# all: test_event_generator emutf_event_generator.o

# emutf_event_generator.o: ../src/emutf_event_generator.cpp ../include/mtf7/emutf_event_generator.h
# 	g++ -I ../include/ -c ../src/emutf_event_generator.cpp


#block_operator.o : ../src/block_operator.cpp ../include/mtf7/block_operator.h
#	g++ -I ../include/ -c ../src/block_operator.cpp

#$(OBJECTS): ../src/$(SOURCES) 
#	$(CC) $(INCLUDES) -c ../src/$(SOURCES).cpp


%.o: ../src/%.cpp
	$(CC) $(INCLUDES) -c $<

# test_event_generator: emutf_event_generator.o test_event_generator.cpp
# 	g++ -I ../include/ emutf_event_generator.o -o test_event_generator test_event_generator.cpp


clean:
	$(RM) $(BIN_TARGET) ../src/$(LIB_TARGET).o
