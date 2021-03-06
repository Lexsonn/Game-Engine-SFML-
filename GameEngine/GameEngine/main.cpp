/**************************************************************************************\
 **								 													 ** 
 **	GAME ENGINE																		 **
 **																					 ** 
 **	Created by Daimen "Lexsonn" Estevez												 **
 ** (u no dis gon b gud)															 ** 
 **																					 **
\**************************************************************************************/

#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

int main() {
	Event event;
	RenderWindow window(VideoMode(1280, 960), "GAME ENGINE v0.07");

	// BAD DEVELOPER BAD! Change this shit to not be tied to framerate you filthy casual
	window.setFramerateLimit(60); // REEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

	Game game(&window);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::Resized)
				game.setLetterBoxView();
		}
		// Run the game loop
		game.runLoop();
	}

	return 0;
}
