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

    ComplexPlane screen(height/width);
	Font font;
	Text basicText;
	
	VertexArray vArray;
	vArray.setPrimitiveType(Points);
	vArray.resize(width*height);
	enum class GameState { CALCULATING, DISPLAYING };
	GameState curr = GameState::CALCULATING;

	while(window.isOpen())
	{
		/*HANDLE INPUT*/
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{
				window.close();
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{
				// get the current mouse position in the window
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

                // convert it to world coordinates
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, screen);
                if(event.mouseButton.button == sf::Mouse::Right)
				{
					screen.zoomOut();
					screen.setCenter(worldPos);
				}
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					screen.zoomIn();
					screen.setCenter(worldPos);
				}
				curr = GameState::CALCULATING;                           
			}
			if(event.type == sf::Event::MouseMoved)
			{
				// get the current mouse position in the window
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

                // convert it to world coordinates
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, screen);
                screen.setMouseLocation(worldPos);
			}
		}
		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*UPDATE SCENE*/
		if(curr == GameState::CALCULATING)
		{
			for(int j = 0; j < screen.getSize().x; j++)
			{
				for(int i = 0; i < screen.getSize().y; i++)
				{
					vArray[j + i * width].position = { (float)j,(float)i };
					
                	sf::Vector2i pixelPos = { j, i };

                	// convert it to world coordinates
                	sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, screen);
					size_t count = screen.countIterations(worldPos);
					Uint8 r, g, b;
					screen.iterationsToRGB(count, r, g, b);
					vArray[j + i * width].color = { r,g,b };
				}
			}
			curr = GameState::DISPLAYING;
			screen.loadText(basicText);
		}
		/*DRAW SCENE SEGMENT*/
		window.clear();
		CircleShape r(1);
		for(int i = 0; i < vArray.getVertexCount(); i++)
		{
			r.setFillColor(vArray[i].color);
			r.setPosition(vArray[i].position);
			window.draw(r);
		}
		window.draw(basicText);
		window.display();
	}
}