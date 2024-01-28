CXX = g++
CXXFLAGS = -O2

all: asn1_a asn1_b

asn1_a: asn1_a.o
	$(CXX) $(CXXFLAGS) -o asn1_a asn1_a.o

asn1_b: asn1_b.o
	$(CXX) $(CXXFLAGS) -o asn1_b asn1_b.o

asn_1a.o: lucas_number_forward_dp.cpp
	$(CXX) $(CXXFLAGS) -c asn_1a.cpp

asn_1b.o: asn1_b.cpp
	$(CXX) $(CXXFLAGS) -c asn_1b.cpp

clean:
	rm -f *.o asn1_a asn1_b
