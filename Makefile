CXX = g++
TARGET = a.out
SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.h)

.PHONY: all run demo clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) *.cpp -o $@

run: $(TARGET) | Rapoarte
	./$(TARGET)

demo: $(TARGET) | Rapoarte
	printf '%s\n' 1 4 0 2 1 0 3 1 3 4 0 0 | ./$(TARGET)

Rapoarte:
	mkdir -p $@

clean:
	rm -f $(TARGET)
