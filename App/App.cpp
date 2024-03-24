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
	std::string input = "a^3";

	ArithmeticTree math(input);
	math.setValue('a', 3);
	math.setValue('b', 2);
	math.setValue('c', 3);
	math.setValue('x', 4);
	ArithmeticTree diff = math.differentiation('a');
	math.setValue('a', 3);

	printf("%s = %f\n", math.toString().c_str(), math.calculate());
	printf("%s = %f\n", diff.toString().c_str(), diff.calculate());


	
	//graphicEngine
	Rect r = Window::getInnerSize();
	int* image = new int[r.width * r.height];
	for (int i = 0; i < r.width * r.height; i++)
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