
// SSE headers
#include <emmintrin.h> //v3
#include <smmintrin.h> //v4
#include <stdio.h>

#define COLS 8
#define RAWS 2


void setData(int *pRaw){
		printf("Fill Raw \n");
		for (int j = 0; j <8 ; ++j)
		{		
				printf("Inser number in position  %d\n",j+1);
				int number;
				pRaw[j]= number;
				scanf("%d",&pRaw[j]);
				
		}

}

void setMatrix(__m128i *pMatrix,int *pRaw1, int *pRaw2){
	pMatrix[0]= _mm_setr_epi16 (pRaw1[7],pRaw1[6],pRaw1[5],pRaw1[4]
								,pRaw1[3],pRaw1[2],pRaw1[1],pRaw1[0]);
	pMatrix[1]= _mm_setr_epi16 (pRaw2[7],pRaw2[6],pRaw2[5],pRaw2[4]
								,pRaw2[3],pRaw2[2],pRaw2[1],pRaw2[0]);
}

void printRes(__m128i *result ){
	printf("Result *********************** \n");
	int data = 0;
	data = _mm_extract_epi16(*result,0); 
	printf("Biggest in %d is %d \n",0,data);
	data = _mm_extract_epi16(*result,1); 
	printf("Biggest in %d is %d \n",1,data);
	data = _mm_extract_epi16(*result,2); 
	printf("Biggest in %d is %d \n",2,data);
	data = _mm_extract_epi16(*result,3); 
	printf("Biggest in %d is %d \n",3,data);
	data = _mm_extract_epi16(*result,4); 
	printf("Biggest in %d is %d \n",4,data);
	data = _mm_extract_epi16(*result,5); 
	printf("Biggest in %d is %d \n",5,data);
	data = _mm_extract_epi16(*result,6); 
	printf("Biggest in %d is %d \n",6,data);
	data = _mm_extract_epi16(*result,7); 
	printf("Biggest in %d is %d \n",7,data);
}

int main(){

__m128i _matrix [RAWS];
int _raw1 [COLS];
int _raw2 [COLS];
setData(_raw1);
setData(_raw2);
setMatrix(_matrix,_raw1,_raw2);
__m128i result = _mm_max_epi16 (_matrix[0],_matrix[1]);
printRes(&result);


//printf("\n");
return 1;
}