#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXSIZE 9
#define BUFFERMAX 10000
#define ROWLENGTH 80
#define ALPHABET 26

void usage(){
	
	printf("USAGE: [PATH to KeyFile][PATH to inputFile]" );
	return;
}

int main(int argc, char *argv[]){
	
	//*****DECLARATION OF VARIABLES*****//
	FILE *fp, *keyFile;
	int numRowAndColumns, alphaBit, padding = 0;
	char fileBuffer[BUFFERMAX];
	int encryptMatrix[MAXSIZE][MAXSIZE], cipherTextMatrix[MAXSIZE][1], messageMatrix[BUFFERMAX];
	int i,j,k;
	
	//*****ZERO INITIALIZERS*****//
	int n = 0;
	int charCount = 0;
	int counter = 0;
	int total = 0;
	int sum = 0;
	
	
	if(argc != 3){
		usage();
		return 0;	
	}
	
	
	//*****OPEN AND READ FILES [KeyFile]*****//
	keyFile = fopen(argv[1],"r");
	if(keyFile == NULL){
		printf("Key File Not Found!\n");
		return 0;
		
	}
	
	//*****OPEN AND READ FILES [inputFile]*****//
	fp = fopen(argv[2],"r");
	if(fp == NULL){
		printf("Input File not found!\n");
		return 0;
	}
	
	
	//******** READ KEYFILE **********///
	fscanf(keyFile,"%d", &numRowAndColumns);
	while(!feof(keyFile)){
		for(i=0; i<numRowAndColumns; i++){
			for(j=0; j<numRowAndColumns; j++){
				fscanf(keyFile, "%d ",&encryptMatrix[i][j]);
				
			}
						
		}
				
	}
	
	//********READ INPUT FILE*****//	
	do
	{
		alphaBit = fgetc(fp);
		//padding 
		if(feof(fp)){
			if(charCount % numRowAndColumns != 0){
				padding = (numRowAndColumns - ((charCount % numRowAndColumns)));
				for(i=charCount; i<(charCount + padding); ++i){
					fileBuffer[i] = 120;
				}
				
				break;
			}
			else 
				break;
		}
			
				
		if(isalpha(alphaBit)){
			if(isupper(alphaBit)){
				alphaBit = tolower(alphaBit);
				fileBuffer[charCount]= alphaBit;
				charCount++;
				
			}
			else if(!isspace(alphaBit)){
				fileBuffer[charCount]= alphaBit;
				charCount++;
			}
			
		}
		else
			continue;
	
	}while(1);
		

	//*****PRINT MATRIX*****//
	printf("\n");
	printf("Key Matrix:\n");
	printf("\n");
	for(i=0; i<numRowAndColumns; i++){
		for(j=0; j<numRowAndColumns; j++){
			printf("%d ", encryptMatrix[i][j]);
			
		}
		printf("\n");	
	}
	 
	 
	//print newline
	printf("\n");

	// ***** PRINT CONTENTS OF FILEBUFFER 
	printf("Plaintext:\n");
	for(i=0; i<(charCount + padding); i++){
		if(i%80 == 0)
			printf("\n");
		printf("%c", fileBuffer[i]);
		
	}
	
	
	//print newline
	printf("\n");
	
	//******BEGIN MATRIX MULTIPLICATION******//
	while(counter < (charCount+padding)){
		
		//read in characters at a time from buffer
		for(i=0; i<numRowAndColumns;i++){
			cipherTextMatrix[i][0] = fileBuffer[n] % 97;
			n++;
		}
		
		for(j=0; j<numRowAndColumns; j++){
			for(k=0; k<numRowAndColumns; k++){
				total = cipherTextMatrix[k][0] * encryptMatrix[j][k];
				sum +=total;
			}	
			sum %= 26;	//mod it by 26 
			messageMatrix[counter] = sum + 97; //add 97 to the sum for LC letters
			counter++;
			sum = 0;
		}
		
	}
	
	//***** PRINT CIPHERTEXT*****//
	printf("CipherText:\n");
	for(i=0; i<(charCount+padding); i++){
		if(i%80 == 0)
			printf("\n");
		printf("%c", messageMatrix[i]);
		
	}
	
	printf("\n");	
	fclose(fp);
	fclose(keyFile);
	return 0;
	
}