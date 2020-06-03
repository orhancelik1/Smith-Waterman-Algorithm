
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int match= 5, gap=-5, missmatch=-3;   //scoring part

//finding max cells 

int Max(int num1,int num2,int num3){   

	int max;
	if(num1 > num2)
    {
        if(num1 > num3)
        {
            max = num1;
        }
        else
        {
            max = num3;
        }
    }
    else
    {
        if(num2 > num3)
        {
            max = num2;
        }
        else
        {
            max = num3;
        }
    }
    if(max<0)         
    max=0;               // '0' comes from "smith-waterman algorithm"
	return max;
}

int main(){
	int i,j,num1,num2,num3,c1,c2,zeroCounter,c,d;
   	char seq1[30]="-CTCGCAGC";    
	char seq2[30]="-CATTCAC";  
	int lenseq1 = strlen(seq1);
	int lenseq2 = strlen(seq2);
	char *Tbseq1;  //storing traceback array for seq1
	char *Tbseq2;  //storing traceback array for seq2
	int scoreMatrix[lenseq1][lenseq2];
	
   

//building score matrix  part
    printf("\t");
	for(j=0;j<lenseq2;j++){
    	printf("%c \t",seq2[j]);	
	}
	printf("\n");
	
	for(i=0; i<lenseq1; i++){
		printf("%c \t",seq1[i]);
		
		for(j=0; j<lenseq2; j++){
			if(i==0 || j==0){   //putting '0's most top and mostleft on the matrix -coming from smith waterman algorithm-
				if(i==0){
					scoreMatrix[0][j]=0;
					printf("%d\t",scoreMatrix[0][j]);
				}
				else{//j==0
					scoreMatrix[i][0]=0;
					printf("%d\t",scoreMatrix[i][0]);
				}
			}
			else{
				if(seq1[i]==seq2[j]){
					num1=scoreMatrix[i-1][j-1]+match;
					num2=scoreMatrix[i-1][j]+gap;
					num3=scoreMatrix[i][j-1]+gap;
					printf("%d\t",scoreMatrix[i][j]=Max(num1,num2,num3));
				}
				else{
					num1=scoreMatrix[i-1][j-1]+missmatch;
					num2=scoreMatrix[i-1][j]+gap;
					num3=scoreMatrix[i][j-1]+gap;
					printf("%d\t",scoreMatrix[i][j]=Max(num1,num2,num3));
				}
			}
		}
		
		printf("\n\n");
	}



//traceback part using smith waterman  algorithm
    int max=0;
    for (i = 0; i < lenseq1; i++){               //finding max values on the matrix
		for (j = 0; j < lenseq2; j++){
			if (scoreMatrix[i][j] > max)
            max = scoreMatrix[i][j];
           // printf("max:%d indises i:%d j:%d matrixScore:%d\n",max,i,j,scoreMatrix[i][j]);
		}
	  
	}

    
    
    printf("Optimal Local Alignments:\n");
    for (i = 0; i < lenseq1; i++){
		for (j = 0; j < lenseq2; j++){
			
			if (scoreMatrix[i][j]== max){
			    Tbseq1 = (char *) malloc( sizeof(char)*lenseq1);
	            Tbseq2 = (char *) malloc( sizeof(char)*lenseq2); 
			
			  c=i, d=j, zeroCounter=0,c1=0,c2=0;
			  
			while(zeroCounter<=1 &&c>=0 && d>=0){ 

				//printf("maxval:%d indises:%d %d\n",max,c,d);
			    //printf("seq1:%c seq2:%c",seq1[c],seq2[d]);
				*(Tbseq1+c1)=seq1[c];    
		        *(Tbseq2+c2)=seq2[d];
	            c1++ , c2++;           
				c--, d--;
				if(scoreMatrix[c][d]==0){
					zeroCounter++;    
				}
			}
         int k,l ;
           printf("sequence 1:");
           for(k=sizeof(Tbseq1);k>=0;k--){
	           printf("%c",*(Tbseq1+k));
           }
           printf("\n");
           printf("sequence 2:");
           for(l=sizeof(Tbseq2);l>=0;l--){
	           printf("%c",*(Tbseq2+l));
           }
			printf("\n\n");
			Tbseq1=NULL;
			Tbseq2=NULL;
   
            }

        }
            
    }
		

	
   


return 0;	}
