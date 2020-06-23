#include <iostream>
#include <vector>
#include <thread>

#include "snake.hpp"
#include "map.hpp"
#include "apple.hpp"
#include "frame.hpp"

static int gameover = 0;

int main(int argc, char** argv) {
	
	Snake snake(3, Direction::__up__);
	Map   map  (10, 10);
	Apple apple(0, 10, 0, 10);
	Frame frame(&map, &apple, &snake);
	
	std::cout << (char)42 << std::endl;
	
	//std::thread thread(moving, &snake, &map, &apple);
	
	//while(!::gameover){
		/*Reset of created matrix of all coordinates of all objects such as Map, Snake and Apple*/		
		//frame.resetMatrix();
		
		/*Draw ascii by coordinates of matrix*/
		//draw_frame(&frame);
		
		/*Start logic function which will check the all coordinates*/
		//logic();
	//}
	
	//thread.join();
	
	return 0;
}
