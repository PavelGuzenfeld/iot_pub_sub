#bricks makefile
CXX = g++
CC = $(CXX)

WARNINGS = -pedantic
WARNINGS += -Wall -Werror
DEBUG = -g3
CXX_STD = c++17

CXXFLAGS = $(WARNINGS) $(DEBUG) -std=$(CXX_STD)
CPPFLAGS = $(INC_DIR)
INC_DIR = -I ../inc
INC_DIR += -I /home/linuxbrew/.linuxbrew/include/

LDLIBS = -L /home/linuxbrew/.linuxbrew/lib/ -lpthread -lsfml-graphics -lsfml-window -lsfml-system

TARGET = utest

OBJS = utest.o

$(TARGET): $(OBJS)

check: $(TARGET)
	./$(TARGET) -v

debug: $(TARGET)
	valgrind --leak-check=full ./${TARGET}
	gdb -q ${TARGET}

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --log-file=log_valgrin.log ./$(TARGET)
	valgrind --tool=helgrind --log-file=log_helgrind.log ./$(TARGET)
	valgrind --tool=drd --log-file=log_drd.log ./$(TARGET)

vala-git: $(TARGET)
	valgrind --leak-check=full --track-origins=yes  ./$(TARGET)
	valgrind --tool=helgrind  ./$(TARGET)
	valgrind --tool=drd  ./$(TARGET)
	
prod: CXXFLAGS += -O2 -DNDEBUG
prod: $(TARGET)
	./$(TARGET) -v

clean:
	@$(RM) $(TARGET) $(OBJS) *.txt

.PHONY: clean check debug
