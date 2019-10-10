#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <locale.h>
#include <aclib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/************************ konstanty **************************************/
#define TEST TRUE



/*********************** deklarace struktur *******************************/



/************************ definice struktur ******************************/




/************************ deklarace funkcí **********************************/



#if TEST == TRUE
uint32_t UTRuntime();

#endif



/*************************** modul main ***********************************/

void mainThread(int argv, char ** argc)
{
	gtk_init(&argv, &argc);



	gtk_main();

}


int main(int argv, char ** argc)
{
	#if TEST == TRUE
		if(UTRuntime() == 0)
		{
			mainThread(argv, argc);	
			return 0;
		}
		else
		{
			return 1;
		}
	#else
		mainThread(argv, argc);
		return 0;
	#endif
}


/********************* definice unit testů *********************************/

#if TEST == TRUE

uint32_t UTRuntime()
{
	uint32_t UTResult = 0;

	return UTResult;
}

#endif

