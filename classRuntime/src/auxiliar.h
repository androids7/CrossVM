#ifndef AUXILIAR_H_
#define AUXILIAR_H_


/******************* CONSTANTES *********************/
#define FILE_ERROR		-1
#define INVALID_FILE_FORMAT 	-2
#define NOT_ENOUGH_PARAMS	-3
#define MEMORY_ERROR            -4
#define ERROR                   -5
#define OK			 0
#define TRUE		         0
#define FALSE			 1
#define FILENAMEMAX		30
/*********************************************************/

#ifdef DEBUG
#define PRINT printf
#define STOP if ( opcao_stop == 1 ) getchar();
#else
#define PRINT
#define STOP
#endif

#endif
