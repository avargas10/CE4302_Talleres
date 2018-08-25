CE4302-Taller1
Autor: Andrés Vargas Rivera

Ejercicios Prácticos:

1) El ejercicio 1 se encuentra en el archiv saxpy.c y se  debe  compilar de la siguiente manera:

-Compilar: gcc -o saxpy -fopenmp saxpy.c -lm
-Ejecutar: ./saxpy

2) El ejercicio 2 se encuentra en el archivo integrate.cpp y se debe compilar de la siguiente manera:

-Compilar: g++ -c integrate.cpp -o integrate.o -fopenmp
		   g++ integrate.o -o integrate -fopenmp -lpthread

-Ejecutar: ./integrate
