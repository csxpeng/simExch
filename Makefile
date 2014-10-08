APP := simExch
CC := g++
OBJFILES := $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CPPFLAGS += -std=c++0x -g -Wall
LDFLAGS += -I $BOOST_ROOT -L $BOOST_ROOT/binary/lib

all: $(APP)

$(APP): $(OBJFILES)
	$(CC) $(LDFLAGS) -o $(APP) $(OBJFILES)

clean:
	rm -f *.o $(APP)
