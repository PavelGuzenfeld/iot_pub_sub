#IOT Pub Sub makefile
CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall
WARNINGS += -Werror
DEBUG = -g3
CXX_STD = c++17

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)
CPPFLAGS = $(INC_DIR)
INC_DIR = -I ../inc
INC_DIR += -I /home/linuxbrew/.linuxbrew/include/
LDFLAGS = -L /home/linuxbrew/.linuxbrew/lib/
LDLIBS = -lpthread

TARGET = utest 

OBJS = utest.o ../src/iot_sensor.o ../src/iot_controller.o ../src/iot_backlog.o ../src/iot_utils.o ../src/iot_event_router.o

$(TARGET): $(OBJS)

all : $(TARGET)

check: $(TARGET)
	./$(TARGET) -v

vala-git: $(TARGET)
	valgrind --leak-check=full --track-origins=yes  ./$(TARGET)
	valgrind --tool=helgrind  ./$(TARGET)
	valgrind --tool=drd  ./$(TARGET)
	
prod: CXXFLAGS += -O2 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v

clean:
	@$(RM) $(TARGET) $(OBJS) *.txt

.PHONY: clean check debug prod all
