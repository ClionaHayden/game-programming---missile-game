#include <iostream>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct Position
{
	int x;
	int y;

	void print()
	{
		std::cout << x << " " << y << std::endl;
	}
}Coordinates;

enum WarHead { EXPLOSIVE, NUCLEAR };

typedef struct Enemy
{
	Coordinates coordinates;
}Target;

struct Missile
{
	WarHead payload;
	Coordinates coordinates;
	Target target;

	bool armed;

	void arm()
	{
		if (armed)
			armed = false;
		else
			armed = true;
	}

	void update()
	{
		coordinates.x += 1;
		coordinates.y += 2;

	}
};


int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	bool isActive = true;
	int score = 0;
	bool enemyHit = false;
	int input;
	Enemy enemy;
	Missile missile;

	//for launch code
	int launchCode;
	enemy.coordinates.x = rand() % 10 + 1;
	enemy.coordinates.y = rand() % 10 + 2;

	std::cout << "-----------------Missile command terminal--------------------" << std::endl;
	
	while (isActive) // while game is active
	{
		// initialise variables 
		launchCode = rand() % 9998 + 1;
		enemyHit = false;

		std::cout << "Enter type of warhead to fire: \n 1:Nuclear\n 2:Explosive" << std::endl;
		std::cin >> input;
		// Choose currect warhead based on input
		if (input == 1)
		{
			std::cout << "Current warhead: Nuclear" << std::endl;
			missile.payload = NUCLEAR;
		}
		else if (input == 2)
		{
			std::cout << "Current warhead: Explosive" << std::endl;
			missile.payload = EXPLOSIVE;
		}
		else
		{
			std::cout << "Ivalid input, default warhead chosen \nCurrent Warhead: Explosive" << std::endl;
			missile.payload = EXPLOSIVE;
		}

		// enter launch coordinates
		std::cout << "----------Enter launch coordinates---------- \n(all values between 1 - 10) \nx: ";
		std::cin >> missile.coordinates.x;
		std::cout << "y: ";
		std::cin >> missile.coordinates.y;

		// enter launch code to fire
		std::cout << "Enter launch code [" << launchCode << "] to fire:";
		std::cin >> input;
		if (launchCode == input)
		{
			std::cout << "--------------Missile Armed-------------" << std::endl;
			std::cout << "Press 1 to fire" << std::endl;
			std::cin >> input;
			if(input == 1)
			std::cout << "Missile launched at coordinates [" << missile.coordinates.x << " , " << missile.coordinates.y << "]\n";
			else
			{
				std::cout << "--------------Invalid code. Aborting launch--------------\n\n" << std::endl;
				continue;
			}
		}
		else
		{
			std::cout << "--------------Invalid code. Aborting launch--------------\n\n" << std::endl;
			continue;
		}

		// test collision with enemy
		while (missile.coordinates.y < 20)
		{
			missile.update();
			if ((missile.coordinates.x >= enemy.coordinates.x - 1 && missile.coordinates.x <= enemy.coordinates.x + 1) &&
				(missile.coordinates.y >= enemy.coordinates.y - 1 && missile.coordinates.y <= enemy.coordinates.y + 1))
			{
				score++;
				enemyHit = true;
				enemy.coordinates.x = rand() % 10 + 1;
				enemy.coordinates.y = rand() % 10 + 2;
				std::cout << "-------- Enemy Hit! ---------\nCurrent score: " << score << std::endl;
				break;
			}
			else
				std::cout << "Firing...." << std::endl;
		}
		if (!enemyHit)
			std::cout << "------- Enemy missed ---------\nCurrent score: " << score << std::endl;

		// Ask to try again
		std::cout << "\nTry again?\n1.Yes\n2.No" << std::endl;
		std::cin >> input;
		if (input == 2)
			isActive = false;
		else
		{
			std::cout << "-----------------------------------------------" << std::endl;
			std::cout << std::endl << std::endl << std::endl;
		}
		
	}

	std::system("pause");
	return 0;
}

