/**************************************************************************************\
 **								 													 ** 
 **	MIT License																		 ** 
 **																					 ** 
 ** Copyright (c) 2016 Daimen "Lexsonn" Estevez										 ** 
 **																					 ** 
 ** Permission is hereby granted, free of charge, to any person obtaining a copy	 ** 
 ** of this software and associated documentation files (the "Software"), to deal	 ** 
 ** in the Software without restriction, including without limitation the rights	 ** 
 ** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell		 ** 
 ** copies of the Software, and to permit persons to whom the Software is			 ** 
 ** furnished to do so, subject to the following conditions:						 ** 
 **																					 ** 
 ** The above copyright notice and this permission notice shall be included in all	 **	
 ** copies or substantial portions of the Software.									 ** 
 **																					 ** 
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR		 ** 
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,		 ** 
 ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE		 ** 
 ** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER			 ** 
 ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	 ** 
 ** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE	 ** 
 ** SOFTWARE.																		 **
 **																					 **
\**************************************************************************************/

#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
	sf::Event event;
	sf::RenderWindow window(sf::VideoMode(1280, 960), "GAME ENGINE v0.02");

	window.setFramerateLimit(60);

	Game game(&window);

	while (window.isOpen()) {
		// Open window for rendering.
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Run the game loop
		game.runLoop();
	}

	return 0;
}
