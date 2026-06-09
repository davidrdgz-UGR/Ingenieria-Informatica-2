#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm.h"

// Nicolas Calvo Cruz - UGR (Ceuta): Un conversor simple <SLOW version> de imagenes PGM a ASCII con submuestreo

void toASCII(unsigned char** Original, unsigned char** Salida, int outRows, int outCols, int subSample) {
  char conversion[] = {'#', '@', '%', '+', '*', '=', ':', '-', '.', ' '};
  int windowSize = subSample*subSample;
  int focusRow = 0, focusCol = 0, accum = 0;
  int i, j;

  for(int j = 0; j<outCols; j++){
    for(int i = 0; i<outRows; i++){
      focusRow = i*subSample;
      focusCol = j*subSample;
      accum = 0;
      for(int l = 0; l<subSample; l++){
        for(int k = 0; k<subSample; k++){
          accum += (Original[focusRow + k][focusCol + l]);
        }
      }
      Salida[i][j] = conversion[ (accum / windowSize)*(10)/256];
    }
  }
}

void toDisk(const char* name, unsigned char** Salida, int rows, int cols){
  FILE* output = fopen(name, "w");
  for(int i = 0; i<rows; i++){
    for(int j= 0; j < cols; j++){
      fputc(Salida[i][j], output);//fprintf(output, "%c", Salida[i][j]);
    }
    fprintf(output, "\n");
  }
  fclose(output);
}

int main(int argc, char *argv[]){
  if(argc!=4){
    printf("Uso: ./prog nombreImagenPGM subsample outName\n");
    return 1;
  }

  int rows, cols;
  unsigned char** Original = pgmread(argv[1], &rows, &cols);
  int subSample = atoi(argv[2]);

  int outRows = rows/subSample;
  int outCols = cols/subSample;
  unsigned char** Salida = (unsigned char**) GetMem2D(outRows, outCols, sizeof(unsigned char));

  toASCII(Original, Salida, outRows, outCols, subSample);
  toDisk(argv[3], Salida, outRows, outCols);

  Free2D((void**) Original);
  Free2D((void**) Salida);
  return 0;
}
