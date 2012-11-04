
CXX = g++
#CXXFLAGS = -O0 -g -Wall
CXXFLAGS = -O2 -Wall
INCLUDE = 
TLIB = 

#-----Suffix Rules---------------------------
# set up C++ suffixes and relationship between .cc and .o files

.SUFFIXES: .cpp

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<

.cpp :
	$(CXX) $(CXXFLAGS) $(INCLUDE) $< -o $@ -lm $(TLIB) -lg++

#-----File Dependencies----------------------

GOAL = SGA

SRC = ga.cpp GAmain.cpp myrand.cpp chromosome.cpp global.cpp mt19937ar.cpp


OBJ = $(addsuffix .o, $(basename $(SRC)))

$(GOAL): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(TLIB) -o $@ $(OBJ)

#-----Other stuff----------------------------
depend:
	makedepend $(SRC)

clean:
	rm -f $(OBJ) $(GOAL)
# DO NOT DELETE

ga.o: /usr/include/stdio.h /usr/include/features.h /usr/include/stdc-predef.h
ga.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
ga.o: /usr/include/gnu/stubs.h /usr/include/bits/types.h
ga.o: /usr/include/bits/typesizes.h /usr/include/libio.h
ga.o: /usr/include/_G_config.h /usr/include/wchar.h
ga.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ga.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
ga.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
ga.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
ga.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
ga.o: /usr/include/time.h /usr/include/sys/select.h
ga.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
ga.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
ga.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
ga.o: /usr/include/math.h /usr/include/bits/huge_val.h
ga.o: /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h
ga.o: /usr/include/bits/inf.h /usr/include/bits/nan.h
ga.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h global.h
ga.o: chromosome.h myrand.h mt19937ar.h statistics.h ga.h
GAmain.o: statistics.h /usr/include/math.h /usr/include/features.h
GAmain.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
GAmain.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
GAmain.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
GAmain.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
GAmain.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
GAmain.o: /usr/include/bits/mathcalls.h ga.h chromosome.h myrand.h
GAmain.o: mt19937ar.h global.h
myrand.o: /usr/include/math.h /usr/include/features.h
myrand.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
myrand.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
myrand.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
myrand.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
myrand.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
myrand.o: /usr/include/bits/mathcalls.h /usr/include/time.h
myrand.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
myrand.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
myrand.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
myrand.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
myrand.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
myrand.o: /usr/include/sys/select.h /usr/include/bits/select.h
myrand.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
myrand.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
myrand.o: /usr/include/alloca.h myrand.h mt19937ar.h
chromosome.o: /usr/include/stdio.h /usr/include/features.h
chromosome.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
chromosome.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
chromosome.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
chromosome.o: /usr/include/libio.h /usr/include/_G_config.h
chromosome.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
chromosome.o: /usr/include/bits/sys_errlist.h global.h chromosome.h myrand.h
chromosome.o: mt19937ar.h
global.o: /usr/include/stdio.h /usr/include/features.h
global.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
global.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
global.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
global.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
global.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
global.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
global.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
global.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
global.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
global.o: /usr/include/time.h /usr/include/sys/select.h
global.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
global.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
global.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
global.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
global.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
global.o: /usr/include/bits/posix2_lim.h global.h chromosome.h myrand.h
global.o: mt19937ar.h
mt19937ar.o: /usr/include/stdio.h /usr/include/features.h
mt19937ar.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
mt19937ar.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
mt19937ar.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
mt19937ar.o: /usr/include/libio.h /usr/include/_G_config.h
mt19937ar.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
mt19937ar.o: /usr/include/bits/sys_errlist.h
