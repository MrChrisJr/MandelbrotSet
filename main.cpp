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
	//View mainView(FloatRect(0.0f,0.0f,width, height));
	float aspectRatio = height/width;
	//width = 800; height = 600;
	// Create a video mode object
	VideoMode vm(width, height);
	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot Set!", Style::Default);
	
    ComplexPlane screen(aspectRatio);
	Font f;
	if (!f.loadFromFile("./fonts/Roboto-Black.ttf")) cout << "failed to load font..." << endl;
	Text basicText;
	basicText.setFont(f);
	basicText.setCharacterSize(24);
	basicText.setFillColor(Color::White);
	
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
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, screen.getView());
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
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, screen.getView());
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
			for(int j = 0; j < width; j++)
			{
				for(int i = 0; i < height; i++)
				{
					vArray[j + i * width].position = { (float)j,(float)i };
					
                	//sf::Vector2i pixelPos = { j, i };

                	// convert it to world coordinates
					Vector2i pixelLocation = { j, i };
                    Vector2f viewCoord;
                    viewCoord = window.mapPixelToCoords(pixelLocation, screen.getView());
                	/*sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, screen.getView());*/
					size_t count = screen.countIterations(viewCoord);
					Uint8 r, g, b;
					screen.iterationsToRGB(count, r, g, b);
					vArray[j + i * width].color = { r,g,b };
				}
			}
			curr = GameState::DISPLAYING;
			//screen.loadText(basicText);
		}
		screen.loadText(basicText);
		/*DRAW SCENE SEGMENT*/
		window.clear();
		//window.setView(screen.getView());
		window.draw(vArray);
		window.draw(basicText);
		window.display();
	}
	return 0;
}