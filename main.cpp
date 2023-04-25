#include "ComplexPlane.h"
/*#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
using namespace sf;
using namespace std; ****All in ComplexPlane.h*******/

int main()
{
    //Constructs and constrains window
    float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	View mainView(FloatRect(0.0f,0.0f,width, height));
	//width = 800; height = 600;
	// Create a video mode object
	VideoMode vm(width, height);
	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot Set!", Style::Default);

    //ComplexPlane comPlane(height/width);
	Font font;
	Text basicText;
}