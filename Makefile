test: prueba.x
executable: exe.x

%.o : %.cpp
	g++ -std=c++14 -c  $< -o $@

prueba.x : imp_tsp.o prueba.o
	g++ $^ -o $@

exe.x: MAIN_TSP_SP.o imp_tsp.o
	g++ -openmp  $^ -o $@

clean:
	rm -rf *.o *.x a.out

run_test:
	./prueba.x
