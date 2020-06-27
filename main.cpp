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
#define part_of_snake 1

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77


static int gameover;
static int is_lose = 1;
static bool __key__[256];
static bool up;

#include "logic.hpp"
#include "moving.hpp"

int main(int argc, char** argv) {
	
	Snake snake(part_of_snake, Direction::__right__, (max_x*max_y)-1);
	Map   map  (max_x, max_y);
	Apple apple(min_x, max_x, min_y, max_y);
	Frame frame(&map, &apple, &snake);
	
	/*Start of moving function in other thread of this game*/
	std::thread thread(moving, &snake);

	do{
		/*Reset of created matrix of all coordinates of all objects such as Map, Snake and Apple*/
		frame.resetMatrix();
		
		/*Draw ascii by coordinates of matrix*/
		frame.draw();
		
		/*Start moving of snake*/
		snake.start();
		
		/*Start logic function which will check the all coordinates*/
		logic(&map, &apple, &snake);
		
		/*Frame per milliseconds*/
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		/*Show count of eaten apples*/
		gotoXY(0, max_y+1);
		std::cout << "Count: " << snake.getNumberOfEatenApples() << std::endl;
	}while(!::gameover);
	
	gotoXY(0, max_y+1);
	/*Gameover message ;)*/
	if(is_lose){
		std::cout << "Hahahahha You are loser xD" << std::endl;
	}else{
		std::cout << "Oh shit! you are winner :O" << std::endl;
	}

	
	thread.join();
	
	return 0;
}
