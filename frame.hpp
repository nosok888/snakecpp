#ifndef frame_class
	#define frame_class
	
	#include <vector>


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoXY(int x, int y, char text){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	std::cout << text;
}

void gotoXY(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Frame{
	private:
		void inline setFrameMatrix();
		const Map* _map;
		const Apple* _apple;
		const Snake* _snake;
		
	public:
		class DrawPoint{
			public:
				DrawPoint() = delete;
				DrawPoint(const int _x, const int _y, const int _ascii);
				
				int* getCoordinates() const;
				int  getAsciiSymbol() const;
				void setCoordinates(const int _x, const int _y);
				void setAsciiSymbol(const int _ascii);
				
			private:
				int* coordinates;
				int symbol;
		};
		
		Frame();
		Frame(const Map* _map, const Apple* _apple, const Snake* _snake);
				
		std::vector<DrawPoint> getMatrix() const;
		void resetMatrix();
		void draw();
		
		static std::vector<DrawPoint> frame;
};


/*----------------------------------------------------------------------------*/
void inline Frame::setFrameMatrix(){
	/*get Map coordinates*/
	std::vector<Map::Matrix::Point> map = this->_map->getMatrixOfPoint();
	for(int _iter = 0; _iter < map.size(); ++_iter){
		Frame::frame.push_back(DrawPoint(map[_iter].getCoordinatesOfPoint()[0], map[_iter].getCoordinatesOfPoint()[1], '.'));
	}
	
	/*get Apple coordinates*/
	Frame::frame.push_back(DrawPoint(this->_apple->getAppleCoordinations()[0], this->_apple->getAppleCoordinations()[1], '@'));
	
	/*get Snake cordinates*/
	for(int _iter=0; _iter<this->_snake->getNumberOfSnakeParts(); ++_iter){
		if(this->_snake->getSnakePart(_iter)->getIdOfPart() == 0){
			Frame::frame.push_back(DrawPoint(this->_snake->getPositionOfSnakeParts(_iter)[0], this->_snake->getPositionOfSnakeParts(_iter)[1], 'O'));
		}else{
			Frame::frame.push_back(DrawPoint(this->_snake->getPositionOfSnakeParts(_iter)[0], this->_snake->getPositionOfSnakeParts(_iter)[1], 'o'));
		}
	}
}

Frame::Frame(const Map* _map, const Apple* _apple, const Snake* _snake) : _map(_map), _apple(_apple), _snake(_snake){
	this->setFrameMatrix();
}

void Frame::resetMatrix(){
	Frame::frame.clear();
	this->setFrameMatrix();
}

std::vector<Frame::DrawPoint> Frame::getMatrix() const{
	return this->frame;
}

void Frame::draw(){
	for(int _iter=0; _iter < this->getMatrix().size(); ++_iter){
		gotoXY(this->getMatrix().at(_iter).getCoordinates()[0], this->getMatrix().at(_iter).getCoordinates()[1], (char)(this->getMatrix().at(_iter).getAsciiSymbol()));
	}
}
/*----------------------------------------------------------------------------*/




Frame::DrawPoint::DrawPoint(const int _x, const int _y, const int _ascii) : coordinates(new int[2]){
	this->coordinates[0] = _x;
	this->coordinates[1] = _y;
	this->symbol = _ascii;
}

int* Frame::DrawPoint::getCoordinates() const{
	return this->coordinates;
}

void Frame::DrawPoint::setCoordinates(const int _x, const int _y){
	this->coordinates[0] = _x;
	this->coordinates[1] = _y;
}

void Frame::DrawPoint::setAsciiSymbol(const int _ascii){
	this->symbol = _ascii;
}

int Frame::DrawPoint::getAsciiSymbol() const{
	return (int)(this->symbol);
}

std::vector<Frame::DrawPoint> Frame::frame;

#endif
