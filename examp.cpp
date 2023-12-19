#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;
int main()
{
	RenderWindow win(VideoMode(800, 800), "Tennis");
	RectangleShape line(Vector2f(1, 800));
	line.setFillColor(Color::White);
	line.setPosition(400, 0);

	Texture tplayer, tball;
	tplayer.loadFromFile("C:/Users/Владимир/OneDrive/Рабочий стол/C++/Project3/Project3/Image/player.png");
	tball.loadFromFile("C:/Users/Владимир/OneDrive/Рабочий стол/C++/Project3/Project3/Image/balls.png");
	bool play = true, winer = false;
	int scr_x = 1, scr_y = 1;
	int red_ch = 0, blue_ch = 0;

	Font font;
	if (!font.loadFromFile("C:/Users/Владимир/OneDrive/Рабочий стол/C++/Project3/Project3/Fonts/timesnewromanpsmt.ttf"))
	{
		return 0;
	}
	Text text, text2, text3;
	text.setFont(font); 
	text.setCharacterSize(50);
	text.setFillColor(Color::White);
	text.setStyle(Text::Bold);

	text2.setFont(font);
	text2.setCharacterSize(50);
	text2.setFillColor(Color::White);
	text2.setStyle(Text::Bold);

	text3.setFont(font);
	text3.setCharacterSize(100);
	text3.setFillColor(Color::Red);
	text3.setStyle(Text::Bold);
	text3.setString("Win Friend");
	text3.setPosition(230, 300);

	Sprite player[2], ball(tball);
	for (int i = 0; i < 2; i++) {
		player[i].setTexture(tplayer);
		player[i].setTextureRect(IntRect(40*i, 0, 36, 208));
		player[i].setPosition(765 * i, 250);
	}
	ball.setScale(2, 2); // размер шарика
	ball.setPosition(40, 320);

	while (win.isOpen()) {
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				win.close();
			}
		}

		ball.move(0.5 * scr_x, 0.5 * scr_y);
		Vector2f b = ball.getPosition();
		if (b.y < 0 || b.y > 730) {
			scr_y *= -1;
		}
		
		Vector2f p[2];
		for (int i = 0; i < 2; i++) {
			p[i] = player[i].getPosition();
			p[0] = player[0].getPosition();
			p[1] = player[1].getPosition();
			if (p[0].y < 0) {
				player[0].setPosition(0, 0);
			}
			else if (p[0].y > 600) {
				player[0].setPosition(0, 600);
			}
			if (p[1].y < 0) {
				player[1].setPosition(765, 0);
			}
			else if (p[1].y > 600) {
				player[1].setPosition(765, 600);
			}
			if (ball.getGlobalBounds().intersects(player[i].getGlobalBounds())) {
				scr_x *= -1;
				if (scr_x < 0) {
					ball.move(-10, 0);
				}
			}
		}

		if (play) {
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				player[1].move(0, -0.75);
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				player[1].move(0, 0.75);
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				player[0].move(0, -0.75);
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) {
				player[0].move(0, 0.75);
			}
			if (b.x < -100) {
				blue_ch += 1;
				ball.setPosition(700, 320);
			}
			if (b.x > 800) {
				red_ch += 1;
				ball.setPosition(40, 320);
			}
			if (red_ch == 3 || blue_ch == 3) {
				play = false;
				winer = true;
			}
		}
		if (play) {
			string blue_st = to_string(blue_ch);
			string red_st = to_string(red_ch);

			win.clear();
			win.draw(line);
			text2.setString(blue_st);
			text2.setPosition(500, 0);
			text.setString(red_st);
			text.setPosition(250, 0);
			win.draw(text);
			win.draw(text2);
			for (int i = 0; i < 2; i++) {
				win.draw(player[i]);
			}
			win.draw(ball);
			win.display();
		}
		if (winer) {
			win.clear();
			win.draw(line);

			for (int i = 0; i < 2; i++) {
				win.draw(player[i]);
			}
			win.draw(text3);
			win.display();
		}
	}
}