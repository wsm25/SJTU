TARGET = score-manager
OBJS = main.o row.o 

CPPFLAGS = -g -Wall

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm $(OBJS) $(TARGET)