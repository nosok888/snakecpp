#include <iostream>
#include <vector>
#include <thread>
#include <windows.h>
#include <conio.h>

#include <chrono>
#include <thread>

#include "snake.hpp"
#include "map.hpp"
#include "apple.hpp"
#include "frame.hpp"

#define min_x 0
#define min_y 0
#define max_x 20
#define max_y 20
#define part_of_snake 2

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


static int gameover;
static bool __key__[256];
static bool up;

void logic(Map* _map, Apple* _apple, Snake* _snake){
	
	/*For checking board collision*/
	if(_snake->getPositionOfSnakeParts(0)[0] == max_x && _snake->getDirection() == Direction::__right__){
		int _y = _snake->getPositionOfSnakeParts(0)[1];
		_snake->setNewHeadPositionOfSnake(-1, _y);
		
	}else if(_snake->getPositionOfSnakeParts(0)[0] == min_x-1 && _snake->getDirection() == Direction::__left__){
		int _y = _snake->getPositionOfSnakeParts(0)[1];
		_snake->setNewHeadPositionOfSnake(max_x-1, _y);
		
	}else if(_snake->getPositionOfSnakeParts(0)[1] == max_y && _snake->getDirection() == Direction::__down__){
		int _x = _snake->getPositionOfSnakeParts(0)[0];
		_snake->setNewHeadPositionOfSnake(_x, -1);
		
	}else if(_snake->getPositionOfSnakeParts(0)[1] == min_y-1 && _snake->getDirection() == Direction::__up__){
		int _x = _snake->getPositionOfSnakeParts(0)[0];
		_snake->setNewHeadPositionOfSnake(_x, max_y-1);
	}
	
	if(_snake->getPositionOfSnakeParts(0)[0] == _apple->getAppleCoordinations()[0] &&
	   _snake->getPositionOfSnakeParts(0)[1] == _apple->getAppleCoordinations()[1]){
	   	_snake->setNewSnakePart();
	   	_apple->setNewAppleCoordinations();
	   	_snake->setNewNumberOfEatenApples(1);
	}
	
	for(int _iter_of_snake_part = 1; _iter_of_snake_part < _snake->body.size(); ++_iter_of_snake_part){
		if(_snake->body.at(0).getCurrentPositionOfPart()[0] == _snake->body.at(_iter_of_snake_part).getCurrentPositionOfPart()[0] &&
		   _snake->body.at(0).getCurrentPositionOfPart()[1] == _snake->body.at(_iter_of_snake_part).getCurrentPositionOfPart()[1]){
		    gameover = 1;
		}
	}
}

void moving(Snake* _snake){
	int c = 0;
    while(!::gameover)
    {
        c = 0;
		c = getch();
		
        if(c == KEY_UP && _snake->getDirection() != Direction::__down__){
			_snake->setNewHeadDirectionOfSnake(Direction::__up__);
		}else if(c == KEY_DOWN && _snake->getDirection() != Direction::__up__){
			_snake->setNewHeadDirectionOfSnake(Direction::__down__);
		}else if(c == KEY_LEFT && _snake->getDirection() != Direction::__right__){
			_snake->setNewHeadDirectionOfSnake(Direction::__left__);
		}else if(c == KEY_RIGHT && _snake->getDirection() != Direction::__left__){
			_snake->setNewHeadDirectionOfSnake(Direction::__right__);
		}
    }
}

int main(int argc, char** argv) {
	
	Snake snake(part_of_snake, Direction::__right__);
	Map   map  (max_x, max_y);
	Apple apple(min_x, max_x, min_y, max_y);
	Frame frame(&map, &apple, &snake);
	
	std::thread thread(moving, &snake);

	while(!::gameover){
		/*Clear console*/		
		//system("cls");
		
		/*Reset of created matrix of all coordinates of all objects such as Map, Snake and Apple*/
		frame.resetMatrix();
		
		/*Draw ascii by coordinates of matrix*/
		frame.draw();
		
		//moving(&snake);
		/*Start logic function which will check the all coordinates*/
	//	logic(&map, &apple, &snake);
		
		/*Start moving of snake*/
		snake.start();
		
		logic(&map, &apple, &snake);
		
		/*Frame per milliseconds*/
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		gotoXY(0, max_y+1);
		std::cout << "Count: " << snake.getNumberOfEatenApples() << std::endl;
	}	
	gotoXY(0, max_y+1);
	
	std::cout << "Game over ;)" << std::endl;
	
	thread.join();
	
	return 0;
}
