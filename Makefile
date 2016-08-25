CXX = g++
STD = -std=c++11
INCL = -I/usr/include
LIBDIR = -L/usr/lib 
LIBS = -lprotobuf -lpthread

OBJS = addressbook.pb.o

PROTO_C = protoc
PROTO_CPP = --cpp_out=${PWD}
PROTO_FILE = addressbook.proto

.PHONY: clean addressbook all

# Prevent deletion of intermediate .pb.cc files 
.PRECIOUS: %.pb.cc

%.o: %.cpp
	$(CXX) $(STD) $(INCL) $(LIBDIR) -c $< $(LIBS)

%.pb.cc: %.proto
	$(PROTO_C) $(PROTO_CPP) $(PROTO_FILE)

%.o: %.pb.cc
	$(CXX) $(STD) $(INCL) $(LIBDIR) -c $< $(LIBS)

write: addressbook.o writeContact.o
	$(CXX) $(STD) $(INCL) $(LIBDIR) $(OBJS) writeContact.o -o write.out $(LIBS)

read: addressbook.o readContacts.o
	$(CXX) $(STD) $(INCL) $(LIBDIR) $(OBJS) readContacts.o -o read.out $(LIBS)

addressbook: addressbook.o

all: read write

clean:
	@rm -f *.o *.out *.contacts 
	@rm -f *.pb.h *.pb.cc