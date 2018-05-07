#include <stdio.h>



FILE* openFile(char selectType){
	FILE *fp;

	switch(selectType){
		case 'x':
			fp = fopen("position.dat","w");
			break;
		case 'u':
			fp = fopen("input.dat","w");
			break;

		default:
			break;
	}
	return fp;
}

void closeFiles(FILE *fp){
	fclose(fp);

}