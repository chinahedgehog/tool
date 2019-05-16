#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main( int argv, char *args[]) {
	char names [9][9] = {
		"000000000",
		"00000000",
		"0000000",
		"000000",
		"00000",
		"0000",
		"000",
		"00",
		"0"
	}; 
	char fileName[4096];
	char fileNewName[4096];
	char filePath[4096]; 
	
	int count = 3;
	if (argv == 3) {
		 count = atoi(args[1]);
	} 
	if (argv < 2) {
		printf("where is file ?\n");
	} 
	strcpy(fileName, args[2]);
	FILE *f = fopen(fileName, "r");
	if (!f) {
		fclose(f);
		printf("%s file not find",fileName);
	}	
	
	fseek(f , 0, SEEK_END);
	double fsize = ftell(f);
	fclose(f);
	 
	for (int i=0;i<count;i++) {
		f = fopen(fileName, "w");
		if (!f) {
		fclose(f);
		printf("%s file not find",fileName);
	}	
	
		printf("%d/%d\n", i, count);
		for (double j=0; j<fsize;j++) {
			fputc( (char)(rand() % 128),f);
			if ( (int)(j/fsize*100) % 10 == 1) {
				//printf("%d,%d %%\n", rand() % 128, (int)(j/fsize*100));
			}
		}
		fclose(f);
	} 
	
	
	strcpy(filePath,args[2]);  
	int i = strlen(filePath);
	for (;i > 0 ;i--) {
		if (filePath[i] == '/' || filePath[i] == '\\') {
			filePath[i+1] = 0x0;
			break;
		}
	}
 	for (int i = 0; i<9; i++) {
		sprintf(fileNewName, "%s%s", filePath, names[i]);
		fileNewName[strlen(filePath)+strlen(names[i])] = 0x0;
		rename(fileName, fileNewName);
		strcpy(fileName, fileNewName);   
		printf("%s\n", fileName); 
	} 
	remove(fileNewName);
	printf("over!\n");
	return 1;
}


//gcc ./shred.c -o /usr/local/bin/shred
//shred 7 ./1.txt ./2.txt  或是find . | xargs shred 7 批量清除当前目录所有信息
