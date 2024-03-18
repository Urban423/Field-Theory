#include "App.h"

#include <ArithmeticTree.h>
#include <stdio.h>

App::App()
{	
	fulscreen 	= false;
	focus 		= true;
	_running 	= true;
}

App::~App(){}

void App::onCreate()
{
	//system
	_running 	= true;
	

	//logic
	std::string input = "-(a + b) + (-(a)^2)";

	ArithmeticTree math(input);
	math.setValue('a', 3);
	math.setValue('b', 2);
	math.setValue('c', 3);
	math.setValue('x', 4);
	double ans = math.calculate();

	printf("%s = %f\n", input.c_str(), ans);


	
	//graphicEngine
	int* image = new int[640 * 320];
	for (int i = 0; i < 640 * 320; i++)
	{
		//           AA RR GG BB
		image[i] = 0x00'00'FF'00;
	}
	
	//window
	Window::init("Window", 640, 320, false);
	Window::setBuffer(image);
}

void App::onUpdate()
{
	Window::broadcast();
}



bool App::isRunning()
{
	return _running;
}



void App::setSize(unsigned int width, unsigned int height)
{

}

void App::onDestroy()
{
	_running = false;
}

void App::onFocus()
{

}

void App::onKillFocus()
{

}