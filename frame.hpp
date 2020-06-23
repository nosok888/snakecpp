#ifndef frame_class
	#define frame_class
	
	#incoude <vector>

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

Frame::Frame(const Map* _map, const Apple* _apple, const Snake* _snake){
	/*get Map coordinates*/
	std::vector<Map::Matrix::Point> map = _map->getMatrixOfPoint();
	for(int _iter = 0; _iter < map.size(); ++_iter){
		Frame::frame.push_back(DrawPoint(map[_iter].getCoordinatesOfPoint()[0], map[_iter].getCoordinatesOfPoint()[1], "."));
	}
	
	/*get Apple coordinates*/
	
	
	/*get Snake cordinates/
}

#endif
