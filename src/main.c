#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <locale.h>
#include <aclib.h>
#include <assert.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/************************ konstanty **************************************/
#define TEST TRUE

#define CONF_CYCLIC_INTERUPT_FREQ 1000
#define CONF_WINDOW_TITLE "Stock manager"


/*********************** deklarace struktur *******************************/

struct _Controler_;
typedef struct _Controler_ Controler;

struct _Geometry_;
typedef struct _Geometry_ Geometry;

struct _View_;
typedef struct _View_ View;

struct _ViewBase_;
typedef struct _ViewBase_ ViewBase;

struct _ViewWindowStructure_;
typedef struct _ViewWindowStructure_ ViewWindowStructure;

struct _ViewBaseScreen_;
typedef struct _ViewBaseScreen_ ViewBaseScreen;

/************************ definice struktur ******************************/

struct _Controler_
{
	
};

struct _Geometry_
{
	double x;
	double y;
};	

struct _View_
{
	ViewWindowStructure * viewWindowStructure;
	Controler * controler;
};

struct _ViewBase_
{
	Geometry windowBaseGeometry;
	Geometry windowGeometry;
	double horizontalRatio;
	double verticalRatio;
};

struct _ViewWindowStructure_
{
	ViewBase * viewBase;
	GtkWidget * mainContainer;
	GtkWidget * screenStack;
	GtkWidget * programWindow;
};

struct _ViewBaseScreen_
{
	GtkWidget * fixedContainer;
	ViewBase * viewBase;
};





/************************ deklarace funkcí **********************************/
Controler * controlerNew();
void controlerFinalize(Controler *);

ViewBase * viewBaseNew(Geometry);
double viewBaseGetVerticalRatio(ViewBase *);
double viewBaseGetHorizontalRatio(ViewBase *);
Geometry viewBaseGetWindowGeometry(ViewBase *);
Geometry viewBaseGetBaseWindowGeometry(ViewBase *);
GdkPixbuf * viewBaseLoadImage(char *);
GdkPixbuf * viewBaseScaleImage(GdkPixbuf *, bool, double);
void viewBaseFinalize(ViewBase *);
void viewBaseLoadWindowGeometry(ViewBase *);
static void viewBaseCountSideRatio(ViewBase *);

View * viewNew(Controler *);
static void viewSignals(View *);
void veiwRealize(View *);
static void viewDestroyCallback(GtkWidget *, gpointer);
static void viewCloseCallback(GtkWidget *, gpointer);
static gboolean viewCyclicInterupt(gpointer);
void ViewFinalize(View *);

ViewWindowStructure * viewWindowStructureNew();
void viewWindowStructureFinalize(ViewWindowStructure *);
static void viewWindowStructureBuildScreens(ViewWindowStructure *);
static void viewWindowStructureBuildProgramWindow(ViewWindowStructure *);

ViewBaseScreen * viewBaseScreenNew(ViewBase *);
void viewBaseScreenFinalize(ViewBaseScreen *);
void viewBaseScreenPutWidget(ViewBaseScreen *, GtkWidget *, double, double);
GtkWidget * viewBaseScreenGetInstance(ViewBaseScreen *);




#if TEST == TRUE
uint32_t UTRuntime();

uint32_t viewBaseTC();
uint32_t viewBaseGetVerzticalRatioTest();
uint32_t viewBaseGetHorizontalRatioTest();

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

/********************** definice funkcí ************************************/

/********************** modul Controler ************************************/
Controler * controlerNew()
{
	Controler * this = (Controler *) malloc(sizeof(Controler));

	return this;
}

void controlerFinalize(Controler * this)
{
	free(this);
}


/************************* modul ViewBase *********************************/
ViewBase * viewBaseNew(Geometry windowBaseGeometry)
{
	ViewBase * this = (ViewBase*) malloc(sizeof(ViewBase));

	this->windowBaseGeometry = windowBaseGeometry;
	
	viewBaseLoadWindowGeometry(this);

	return this;
}

void viewBaseLoadWindowGeometry(ViewBase * this)
{
	viewBaseCountSideRatio(this);
}

static void viewBaseCountSideRatio(ViewBase * this)
{
	this->verticalRatio = this->windowGeometry.y/this->windowBaseGeometry.y;
	this->horizontalRatio = this->windowGeometry.x/this->windowBaseGeometry.x;
}

double viewBaseGetVerticalRatio(ViewBase * this)
{
	return this->verticalRatio;
}

double viewBaseGetHorizontalRatio(ViewBase * this)
{
	return this->horizontalRatio;
}

Geometry viewBaseGetWindowGeometry(ViewBase * this)
{
	return this->windowGeometry;
}

Geometry viewBaseGetBaseWindowGeometry(ViewBase * this)
{
	return this->windowBaseGeometry;
}

GdkPixbuf * viewBaseLoadImage(char * imageAddress)
{
	GError * error;

	GdkPixbuf * image = gdk_pixbuf_new_from_file(imageAddress, &error);

	return image;
}

GdkPixbuf * viewBaseScaleImage(GdkPixbuf * image, bool dimension, double newSize)
{
	return image;
}

void viewBaseFinalize(ViewBase * this)
{
	free(this);
}



/*************************** modul View *************************************/
View * viewNew(Controler * controler)
{
	View * this = (View*) malloc(sizeof(View));

	this->controler = controler;
	this->viewWindowStructure = viewWindowStructureNew();

	g_timeout_add(CONF_CYCLIC_INTERUPT_FREQ, viewCyclicInterupt, this);

	return this;
}

static void viewSignals(View * this)
{
	
}

void veiwRealize(View * this)
{
	viewSignals(this);
}

static void viewDestroyCallback(GtkWidget * widget, gpointer param)
{

}

static void viewCloseCallback(GtkWidget * widget, gpointer param)
{

}

static gboolean viewCyclicInterupt(gpointer param)
{
	return false;
}

void ViewFinalize(View * this)
{
	free(this);
}



/***************************** modul ViewWindowStructure **********************/
ViewWindowStructure * viewWindowStructureNew()
{
	ViewWindowStructure * this = (ViewWindowStructure *) malloc(sizeof(ViewWindowStructure));

	viewWindowStructureBuildProgramWindow(this);
	viewWindowStructureBuildScreens(this);

	return this;
}

void viewWindowStructureFinalize(ViewWindowStructure * this)
{
	free(this);
}

static void viewWindowStructureBuildScreens(ViewWindowStructure * this)
{

}

static void viewWindowStructureBuildProgramWindow(ViewWindowStructure * this)
{
	this->programWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(this->programWindow), CONF_WINDOW_TITLE);
}


/******************************* modul ViewBaseScreen *************************/
ViewBaseScreen * viewBaseScreenNew(ViewBase * viewBase)
{
	ViewBaseScreen * this = (ViewBaseScreen *) malloc(sizeof(ViewBaseScreen));

	this->viewBase = viewBase;
	this->fixedContainer = gtk_fixed_new();

	return this;
}

void viewBaseScreenFinalize(ViewBaseScreen * this)
{	
	free(this);
}

void viewBaseScreenPutWidget(ViewBaseScreen * this, GtkWidget * widget, double x, double y)
{
	gtk_fixed_put(GTK_FIXED(this->fixedContainer), widget, viewBaseGetHorizontalRatio(this->viewBase) * x, viewBaseGetVerticalRatio(this->viewBase) * y);
}

GtkWidget * viewBaseScreenGetInstance(ViewBaseScreen * this)
{
	return this->fixedContainer;
}


/********************* definice unit testů *********************************/

#if TEST == TRUE

uint32_t UTRuntime()
{
	uint32_t UTResult = 0;

	return UTResult;
}



uint32_t viewBaseTC()
{
	uint32_t TCResult = 0;

	TCResult += viewBaseGetVerzticalRatioTest();
	TCResult += viewBaseGetHorizontalRatioTest();

	return TCResult;
}

uint32_t viewBaseGetVerzticalRatioTest()
{
	Geometry baseWindowGeometry = {800, 600};
	ViewBase * this = viewBaseNew(baseWindowGeometry);
	
	Geometry windowGeometry = viewBaseGetWindowGeometry(this);

	if(round(viewBaseGetHorizontalRatio(this)) != round(windowGeometry.x/baseWindowGeometry.x))
	{
		assert(false);
		return 1;
	}
	else
	{
		return 0;
	}
}

uint32_t viewBaseGetHorizontalRatioTest()
{
	Geometry baseWindowGeometry = {800, 600};
	ViewBase * this = viewBaseNew(baseWindowGeometry);
	
	Geometry windowGeometry = viewBaseGetWindowGeometry(this);

	if(round(viewBaseGetVerticalRatio(this)) != round(windowGeometry.y/baseWindowGeometry.y))
	{
		assert(false);
		return 1;
	}
	else
	{
		return 0;
	}
}




#endif

