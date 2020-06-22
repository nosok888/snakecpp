#include <iostream>
#include <vector>

#include "snake.hpp"
#include "map.hpp"

int main(int argc, char** argv) {
	Snake new_snake(5, 2);
	
	/*Getting for positions of each part of snake*/
	for(int _iter=0; _iter<new_snake.getNumberOfSnakeParts(); ++_iter){
		if(new_snake.getSnakePart(_iter)->getIdOfPart() == 0){
			std::cout << "Head {" << new_snake.getPositionOfSnakeParts(_iter)[0] << ", " << new_snake.getPositionOfSnakeParts(_iter)[1] << "}" << std::endl;
		}
		else{
			std::cout << "Part {" << new_snake.getPositionOfSnakeParts(_iter)[0] << ", " << new_snake.getPositionOfSnakeParts(_iter)[1] << "}" << std::endl;
		}
	}
	
	Map new_map(10, 20);
	
	std::cout << std::endl;
	
	std::vector<Map::Matrix::Point> map = new_map.getMatrixOfPoint();
	
	int _row = map[0].getCoordinatesOfPoint()[1];
	for(int _iter=0; _iter<map.size(); ++_iter){
		if(map[_iter].getCoordinatesOfPoint()[1] > _row){
			_row = map[_iter].getCoordinatesOfPoint()[1];
			std::cout << std::endl;
		}
		std::cout << "[" << map[_iter].getCoordinatesOfPoint()[0] << ", " << map[_iter].getCoordinatesOfPoint()[1] << "]";
	}
	
	return 0;
}
