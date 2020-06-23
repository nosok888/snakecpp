#include <iostream>
#include <vector>
#include <thread>

#include "snake.hpp"
#include "map.hpp"
#include "apple.hpp"

std::vector<int> compose(Map &map, Snake &snake, Apple &apple){
	
	
	
	return matrix;
}

static int gameover = 0;

int main(int argc, char** argv) {
	
	Snake snake(3, Direction::__up__);
	Map   map  (10, 10);
	Apple apple(0, 10, 0, 10);
	
	std::thread thread(moving, &snake, &map, &apple);
	
	while(!::gameover){
		/*Compose all objects coordinates in one vector of coordinates*/
		std::vector<int> matrix = compose(&map, &snake, &apple);
		
		/*Draw ascii by coordinates of matrix*/
		draw_frame(&matrix);
		
		/*Start moving function in thread*/
		thread.join();
		
		/*Start login function which will check the all coordinates*/
		logic();
	}
	
	return 0;
}
