CXX = g++
CXXFLAGS = -Wall -pedantic
LFFLAGS = 

OBJS = main.o card.o card_deck.o foundation.o tableau.o waste.o

all: solitaire

solitaire: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@


clean:
	rm -f *.o solitaire

.PHONY: all clean