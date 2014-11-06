NAME=TuioClient
CSYM=TuioClient

current: pd_linux

# ----------------------- LINUX i386 -----------------------

pd_linux: $(NAME).pd_linux

.SUFFIXES: .pd_linux_o

OBJECTS = TuioWrapper.o TuioPureData.o ./TUIO/TuioClient.o ./TUIO/TuioDispatcher.o ./TUIO/OscReceiver.o ./TUIO/UdpReceiver.o \
	./TUIO/TuioTime.o ./TUIO/TuioPoint.o ./TUIO/TuioContainer.o ./TUIO/TuioCursor.o ./TUIO/TuioObject.o ./TUIO/TuioBlob.o \
	./oscpack/osc/OscTypes.o ./oscpack/osc/OscReceivedElements.o ./oscpack/osc/OscPrintReceivedElements.o \
	./oscpack/ip/posix/NetworkingUtils.o ./oscpack/ip/posix/UdpSocket.o

CXXFLAGS = -DOSC_HOST_LITTLE_ENDIAN -DPD -O2 -funroll-loops -fomit-frame-pointer -fPIC \
    $(CFLAGS) -I. -I./TUIO

$(NAME).pd_linux: $(OBJECTS)
	$(CXX) -shared -o ../$(NAME).pd_linux $(OBJECTS)  -lc  -lm

# ----------------------- Mac OSX -----------------------

UNAME = $(shell uname)

pd_darwin: $(NAME).pd_darwin

.SUFFIXES: .pd_darwin_o

OBJECTS = TuioWrapper.o TuioPureData.o ./TUIO/TuioClient.o ./TUIO/TuioDispatcher.o ./TUIO/OscReceiver.o ./TUIO/UdpReceiver.o \
	./TUIO/TuioTime.o ./TUIO/TuioPoint.o ./TUIO/TuioContainer.o ./TUIO/TuioCursor.o ./TUIO/TuioObject.o ./TUIO/TuioBlob.o \
	./oscpack/osc/OscTypes.o ./oscpack/osc/OscReceivedElements.o ./oscpack/osc/OscPrintReceivedElements.o \
	./oscpack/ip/posix/NetworkingUtils.o ./oscpack/ip/posix/UdpSocket.o

ifeq ($(UNAME),Darwin)
	CXXFLAGS = -stdlib=libstdc++ -DPD -g -O2 -arch i386 -arch x86_64 -funroll-loops -fomit-frame-pointer -I. -I./TUIO -I./oscpack -mmacosx-version-min=10.5
endif

$(NAME).pd_darwin: $(OBJECTS)
	$(CXX) -bundle -undefined suppress -flat_namespace -o ../$(NAME).pd_darwin $(OBJECTS) -lc -lm -arch i386 -arch x86_64 -mmacosx-version-min=10.5

# ----------------------------------------------------------

clean:
	rm -f $(OBJECTS) *.pd_* so_locations
