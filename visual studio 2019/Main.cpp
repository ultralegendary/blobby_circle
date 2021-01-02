#include"perlin.h"
#include<SFML/Graphics.hpp>


#include<cmath>
#include<vector>
#include<iostream>

const float PI =  3.14;

class looping_noise :public sf::Drawable,public sf::Transformable
{
	sf::VertexArray circle;
	float radius,z,size,speed,noise_y,delta_r;
	int waves,width;
	
	bool run_update,switch_t;
	
	virtual void draw(sf::RenderTarget& t, sf::RenderStates s)const
	{
		s.transform *= getTransform();
		
		t.draw(circle, s);

	}
public:
	looping_noise() : size(10.f), circle(sf::TriangleFan, 65), radius(250), waves(10), speed(0.01f), width(10),switch_t(false),run_update(true)
	{
		// circle no. of points available variation: 630 and 65
		int index = 0;
		z = 0;
		delta_r = 0.0f;
		
		circle[index++].position = sf::Vector2f(425, 425);
		for (float i = 0.f; i < ( 2.0* PI)+0.1f; index++, i += 0.1f)
		{
			circle[index].position = sf::Vector2f(425+radius * cos(i),425+ radius * sin(i));
			
		}
		
	}
	void pauseupdate()
	{
		run_update = !run_update;
	}
	void update_speed(float f)
	{
		speed+=f;
	}
	void update_wave_count(int w)
	{
		waves += w;
	}
	void update_width(int w)
	{
		width += w;
	}
	void switch_too ()
	{
		switch_t = !switch_t;
	}
	void update_1()
	{
		
		if (!run_update)return;
		int index = 1;
		
		z +=0.009f;
		
		delta_r += 0.0047f;
		if (delta_r > 0.05f)
		{
			delta_r = 0.f;
		}
		
		
		for (float i = 0.f-delta_r; i < (2 * PI) + 0.1f-delta_r; index++, i += 0.1f)
		{

			float offset = static_cast<float>(Noise(((i-delta_r)*10)+z*10 , 0, 0) * width);
			float rdius = radius + offset;
			circle[index].position = sf::Vector2f(425 + rdius * cos(i-delta_r), 425 + rdius * sin(i-delta_r));
		}
	}
	
	void update_2()
	{
		
		if (!run_update)return;
		int index=1;
		
		z +=speed;
		
		for (float i = 0.f; i < (2 * PI)+0.1f; index++, i += 0.1f)
		{
			float offset= std::sin(i*waves+z)*width;
			
			float rdius = radius +offset;
			circle[index].position = sf::Vector2f(425 + rdius * cos(i), 425 + rdius* sin(i));
		}
	}
};

int main()
{
	std::cout << "\n\tKEY CODES:\n'SpaceBar' - pause and resume\n'z' - increase speex\n'x' - decrease speed\n'q' - increase no. of waves\n'w' - decrease no. of waves\
\n'a' - increase width\n's' - decrease width\n'1' - switch update";
	bool update = false;
	srand(time(0));
	looping_noise objects;
	sf::Clock timer;
	sf::RenderWindow w(sf::VideoMode(850, 850), "Pixels");
	
	w.setFramerateLimit(60);
	timer.restart();
	while (w.isOpen())
	{
		sf::Event e;
		while (w.pollEvent(e))
		{
			switch (e.type)
			{
			case 0:
				w.close();
			case sf::Event::KeyPressed:
				switch (e.key.code)
				{
				case sf::Keyboard::Space:
					objects.pauseupdate();
					break;
				case sf::Keyboard::Z:
					objects.update_speed(0.001f);
					break;
				case sf::Keyboard::X:
					objects.update_speed(-0.001f);
					break;
				case sf::Keyboard::Q:
					objects.update_wave_count(1);
					break;
				case sf::Keyboard::W:
					objects.update_wave_count(-1);
					break;
				case sf::Keyboard::A:
					objects.update_width(1);
					break;
				case sf::Keyboard::S:
					objects.update_width(-1);
					break;
				case sf::Keyboard::Num1:
					update = !update;
				}
				break;
			}
		}
		if (update)
			objects.update_1();
		else
			objects.update_2();
		
		w.clear();
		w.draw(objects);

		w.display();
	}
	

	return 0;
}