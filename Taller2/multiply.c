
// SSE headers
#include <emmintrin.h> //v3
#include <smmintrin.h> //v4
#include <xmmintrin.h>
#include <stdio.h>

#define COLS 4
#define RAWS 4
#define bits 241 /*Dato el cual corresponde a 11110001 esto para 
					sumar todas las multiplicaciones de entre las 
					posiciones de un vector y otro. Además para almacenarlo 
					en la primera posición del vector resultante*/

//Generador de Datos para la matriz
void generateMats(__m128 *matA,__m128 *matB){
	
	__m128 vector1 =_mm_set_ps (1.0,2.0,3.0,4.0);
	__m128 vector2 =_mm_set_ps (12.2,14.5,4.0,5.1);
	__m128 vector3 =_mm_set_ps (9.54,8.45,16.23,15.11);
	__m128 vector4 =_mm_set_ps (12.11,23.4,45.34,19.66);
	//Matriz A
	matA[3]= vector1;
	matA[2]= vector2;
	matA[1]= vector3;
	matA[0]= vector4;

	//Matriz A
	matB[0]= vector2;
	matB[1]= vector1;
	matB[2]= vector4;
	matB[3]= vector3;
}
/*
Imprimir matriz
*/
void PrintMatA(__m128 *mat){
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			printf("%f   ",mat[i][j]);
		}
		printf("\n");
	}
}

/*
Imprimir matriz transpuesta
*/
void PrintMatB(__m128 *mat){
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			printf("%f    ",mat[j][i]);
		}
		printf("\n");
	}
}

/*
Se realiza la multiplicacion de matrices
*/
void multiplyMats(__m128 *matA,__m128 *matB){
	float lastMat[4][4];
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			__m128 result =_mm_dp_ps (matA[i],matB[j],bits);
			float data = _mm_cvtss_f32(result); 
			lastMat[i][j] = data;
			printf("%f    ",data);
		}
		printf("\n");
	}
}

int main(){
//Matrices 
__m128 _matrixA [RAWS];
__m128 _matrixB [COLS];


generateMats(_matrixA,_matrixB);
printf("----------Matriz A---------\n");
PrintMatA(_matrixA);
printf("\n---------Matriz B---------\n");
PrintMatB(_matrixB);
printf("\n---------Result Matriz---------\n");
multiplyMats(_matrixA,_matrixB);
return 1;
}