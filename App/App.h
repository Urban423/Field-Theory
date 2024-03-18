#pragma once
#include "Window.h"

class App: Window
{
public:
	App();
	~App();
	
	void onCreate();
	void onUpdate();
	
	bool isRunning();


	void setSize(unsigned int width, unsigned int height);
	void onDestroy();
	void onFocus();
	void onKillFocus();
private:
	//system paramerts
	bool focus = true;
	bool fulscreen = false;
	bool _running = false;
};