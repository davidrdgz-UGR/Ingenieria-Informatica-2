#ifndef __PGM__
#define __PGM__

//V0: Jose Manuel Garcia Salmeron (Universidad de Almeria) => Libreria original
//	Nicolas Calvo Cruz (Universidad de Granada) => Optimizacion del uso de memoria contigua

void ** GetMem2D(int rows, int columns, int sizeofTipo);
void Free2D(void ** h);

unsigned char** pgmread(char* filename, int* rows, int* columns);

// Ver https://netpbm.sourceforge.net/doc/pgm.html para mas detalles del formato

#endif /*__PGM__*/
