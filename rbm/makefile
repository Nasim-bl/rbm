#make file - build PBM project

default: rbm.cpp mtutils.o utils.o random.o estJ.o Binder.o
	g++ -o rbm rbm.cpp mtutils.o utils.o random.o estJ.o Binder.o -std=c++11 -Ofast -march=native

utils.o: utils.cpp utils.h
	g++ -c utils.cpp -std=c++11 -Ofast -march=native

mtutils.o: mtutils.cpp mtutils.h
	g++ -c mtutils.cpp -std=c++11 -Ofast -march=native

random.o: random.cpp random.h
	g++ -c random.cpp -std=c++11 -Ofast -march=native

estJ.o: estJ.cpp estJ.h
	g++ -c estJ.cpp -std=c++11 -Ofast -march=native

Binder.o: Binder.cpp Binder.h
	g++ -c Binder.cpp -std=c++11 -Ofast -march=native

stat.o: stat.cpp stat.h
	g++ -c stat.cpp -std=c++11 -Ofast -march=native

doxygen: rbm.cpp
	doxygen doxyfile

debug: rbm.cpp mtutils.h mtutils.cpp utils.h utils.cpp random.h random.cpp estJ.h estJ.cpp Binder.cpp Binder.h
	g++ -o ~/Documents/Students/debug/rbm rbm.cpp mtutils.cpp utils.cpp random.cpp estJ.cpp Binder.cpp -std=c++11 -Ofast -g

release: rbm.cpp mtutils.h mtutils.cpp utils.h utils.cpp random.h random.cpp estJ.h estJ.cpp Binder.cpp Binder.h
	g++ -o rbm rbm.cpp mtutils.cpp utils.cpp random.cpp estJ.cpp Binder.cpp -std=c++11 -Ofast -DNDEBUG -march=native -fopenmp

clean:
	rm -f rbm *.o *~ thread?.log
