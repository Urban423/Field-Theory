#include "App.h"

int main()
{
	App app;
	app.onCreate();
	while (app.isRunning())
	{
		app.onUpdate();
	}
	return 0;
}