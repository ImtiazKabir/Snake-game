#include <SFML/Graphics.hpp>

// define necessary constants
#define width 500
#define height 500
#define rows 20
#define cols 20
#define step 10000

const float cellx  = static_cast<float>(width)/cols;
const float celly = static_cast<float>(height)/rows;

struct vec {
	int i;
	int j;
};

vec food;
std::vector<vec> snake;
vec vel;

bool over = false;

int count = 0;

int main() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Snake Game");

	// prepare randomness
	srand(time(0));

	// init food, snake and vel
	// food
	food.i = rand() % rows;
	food.j = rand() % cols;
	// snake
	vec head;
	head.i = rows/2;
	head.j = cols/2;
	snake.push_back(head);
	// vel
	vel.i = 0;
	vel.j = 1;

	// prepare the background
	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setPosition(0, 0);
	background.setFillColor(sf::Color(255, 255, 255));


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::Up:
						if (snake.size() == 0 or snake[0].i - 1 != snake[1].i) {
							vel.i = -1;
							vel.j = 0;
						}
						break;
					case sf::Keyboard::Left:
						if (snake.size() == 0 or snake[0].j - 1 != snake[1].j) {
							vel.i = 0;
							vel.j = -1;
						}
						break;
					case sf::Keyboard::Down:
						if (snake.size() == 0 or snake[0].i + 1 != snake[1].i) {
							vel.i = 1;
							vel.j = 0;
						}
						break;
					case sf::Keyboard::Right:
						if (snake.size() == 0 or snake[0].j + 1 != snake[1].j) {
							vel.i = 0;
							vel.j = 1;
						}
						break;
					case sf::Keyboard::Escape:
						window.close();
						break;
					default:
						break;

				}
			}
		}


		if (count % step == 0 and not over) {
			window.clear();
			// draw stuff
			window.draw(background);
			// draw food and snake
			sf::RectangleShape rect(sf::Vector2f(cellx, celly));
			// food
			rect.setFillColor(sf::Color(255, 0, 0));
			rect.setPosition(food.j * cellx, food.i * celly);
			window.draw(rect);
			// snake
			rect.setFillColor(sf::Color(51, 51, 51));
			for (unsigned k = 0; k < snake.size(); ++k) {
				rect.setPosition(snake[k].j * cellx, snake[k].i * celly);
				window.draw(rect);
			}


			// check over
			if (snake[0].i < 0 or snake[0].i >= rows or snake[0].j < 0 or snake[0].j >= cols) over = true;
			else {
				for (unsigned k = 1; k < snake.size(); ++k) {
					if (snake[k].i == snake[0].i and snake[k].j == snake[0].j) {
						over = true;
						break;
					}
				}
			}

			// check hit
			if (snake[0].i == food.i and snake[0].j == food.j) {
				food.i = rand() % rows;
				food.j = rand() % cols;

				// add tail
				int index = snake.size() - 1;
				vec tail;
				tail.i = snake[index].i + vel.i;
				tail.j = snake[index].j + vel.j;
				snake.push_back(tail);
			}


			// update stats
			for (int k = snake.size() - 1; k > 0; --k) {
				snake[k].i = snake[k-1].i;
				snake[k].j = snake[k-1].j;
			}
			snake[0].i += vel.i;
			snake[0].j += vel.j;

			count = 0;
			window.display();
		}
		count ++;
	}

}






