EXENAME1 = testimage
EXENAME2 = testscene
OBJS1 = testimage.o image.o png.o rgbapixel.o
OBJS2 = testscene.o scene.o image.o png.o rgbapixel.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME1) $(EXENAME2)

$(EXENAME1) : $(OBJS1)
	$(LD) $(OBJS1) $(LDFLAGS) -o $(EXENAME1)

$(EXENAME2) : $(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXENAME2)

testscene.o : testscene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testscene.cpp

testimage.o : testimage.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) testimage.cpp

scene.o : scene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) scene.cpp

image.o : image.cpp image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) image.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean :
	-rm -f *.o $(EXENAME1) $(EXENAME2)
