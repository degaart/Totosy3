.PHONY: all clean
.SUFFIXES:

CC := cc
CXX := c++
CPPFLAGS := -DWIN32_LEAN_AND_MEAN -DUNICODE
CFLAGS :=
CXXFLAGS := -std=gnu++98
LDFLAGS := -municode

all: totosy3.exe

totosy3.exe: main.o FlexLayout.o Window.o Util.o
	$(CXX) -o $@ $(LDFLAGS) $^

main.o: main.cpp FlexLayout.h Window.h
	$(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

Window.o: Window.cpp Window.h
	$(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

Util.o: Util.cpp Util.h
	$(CXX) -c -o $@ $(CPPFLAGS) $(CXXFLAGS) $<

FlexLayout.o: FlexLayout.c FlexLayout.h
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $<

clean:
	rm -f *.o *.exe

