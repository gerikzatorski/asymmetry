EXECUTABLE = hello
SOURCES = main.cpp Waveform.cpp
OBJECTS = $(SOURCES:.cpp = .o)

CXX = g++
CXXFLAGS = -std=c++11 -c -Wall 
LDFLAGS = -std=c++11 -g

# define any directories containing header files other than /usr/include
INCLUDE = -I/usr/include/python2.7

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lm -lpython2.7


all: $(SOURCES) $(EXECUTABLE)

# link em
$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(INCLUDE) -o $@ $(OBJECTS) $(LDFLAGS) $(LIBS)

# create object files
.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

# remove object files and the executable
clean:
	$(RM) *.o *~ $(EXECUTABLE)

# run the executable
run:
	./$(EXECUTABLE)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
