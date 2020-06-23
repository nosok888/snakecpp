#include <iostream>
#include <vector>
#include <thread>

#include "snake.hpp"
#include "map.hpp"
#include "apple.hpp"

class Frame{
	private:
		class DrawPoint{
			public:
				DrawPoint() = delete;
				DrawPoint(const int _x, const int _y, const int _ascii);
				
				int* getCoordinates() const;
				void setCoordinates(const int _x, const int _y);
				void setAsciiSymbol(const int _ascii);
				
			private:
				int* cooridnates;
				int symbol;
				
		};
	public:
		Frame();
		Frame(const Map* _map, const Apple* _apple, const Snake* _snake);
				
		std::vector<DrawPoint> getMatrix() const;
		void resetMatrix();
		
		static std::vector<DrawPoint> frame;
};






std::vector<Frame::DrawPoint> Frame::frame;
static int gameover = 0;

int main(int argc, char** argv) {
	
	Snake snake(3, Direction::__up__);
	Map   map  (10, 10);
	Apple apple(0, 10, 0, 10);
	Frame frame(&map, &apple, &snake);
	
	std::thread thread(moving, &snake, &map, &apple);
	
	while(!::gameover){
		/*Reset of created matrix of all coordinates of all objects such as Map, Snake and Apple*/		
		frame.resetMatrix();
		
		/*Draw ascii by coordinates of matrix*/
		draw_frame(&frame);
		
		/*Start logic function which will check the all coordinates*/
		logic();
	}
	
	thread.join();
	
	return 0;
}
