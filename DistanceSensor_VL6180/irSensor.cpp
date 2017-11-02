#include "stdio.h"
#include "RangeFinder.h"
#include "unistd.h"

int main(int argc, char *argv[]) {
 //   FILE * pFile = fopen ("distances.txt","w");
    RangeFinder irSens;
    int value;
    for( int i=0; i<1000; i++) {
        value = irSens.getRange();
        printf("value: %d\n", value);
//	fprintf(pFile,"%d\n",value);
        sleep(0.1);
    }
    irSens.closeFile();
//    fclose (pFile);
}

