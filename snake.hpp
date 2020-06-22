#ifndef snake_class
	#define snake_class
	
	#include <vector>
	
	#define START_POSITION_X 4
	#define START_POSITION_Y 4

/*Direction of head moving enum with some kind of direction number*/
enum Direction{
	__up__    = 1,
	__right__ = 2,
	__down__  = 3,
	__left__  = 4
};
/*---------------------------------------------------------------*/


/*Main class Snake*/
class Snake{
	public:
		Snake() = delete;
		/*Create a body of snake*/
		Snake(const int count_of_snake_part, const int _direction);
		~Snake();
		
		
		/*For getting some kind of info about parts of snake*/
		const int* getPositionOfSnakeParts  (const int _id) const;
		int        getNumberOfSnakeParts	() 			    const;
		int  	   getDirection		        () 			    const;
		int        getNumberOfEatenApples   () 			    const;
				
		void      setNewSnakePart           (const Snake* _new_part);
		void 	  setNewNumberOfEatenApples (const int _number);
	
	private:
		int apples_eaten;
		
		
		/*|||||||||||||||||||||||||||||||||||||||||*/
		/*This class needs for create snake parts*/
		class SnakePart{
			public:
				SnakePart() = delete;
				SnakePart(const int _id, const int _direction);
				~SnakePart();
		
				/*Getting some position value of head, this needs for body-parts*/
				const int*  getNextPositionOfPart    () const;
				const int*  getCurrentPositionOfPart () const;
				const int*  getPrevPositionOfPart	 () const;
				int 		getDirectionOfPart   	 () const;
				int 		getIdOfPart				 () const;
				
				/*For moving the head*/
				void  setNextPositionOfPart	   (const int _x_pos, const int _y_pos);
				void  setNewPositionOfPart     ();
			
			private:
				/*Some position and direction value*/
				int* next_position;
				int* curr_position;
				int* prev_position;
				
				int _direction;
				/*This is id of part if this id equ 0 if meens that is the head of snake*/
				const int _id;
		};
		/*|||||||||||||||||||||||||||||||||||||||||*/

	/*Some methods which needs for getting access to SnakePart class*/
	public:
		static std::vector<SnakePart> body;
		/*This is a body of snake known as vector array*/
		SnakePart* getSnakePart	(const int _id) const;
		
};

/*Create the Snake*/
Snake::Snake(const int count_of_snake_part, const int _direction){
	
	/*Create a head know as the first element of vector*/
	Snake::body.push_back(Snake::SnakePart(Snake::body.size(), _direction));
	
	/*Create other parts of snake body know as other index of vector*/
	for(int _iter=1; _iter<count_of_snake_part; ++_iter){
		int _id = static_cast<int>(Snake::body.size());
		Snake::body.push_back(Snake::SnakePart(_id, this->getDirection()));
	}

	this->apples_eaten = 0;
}

/*For getting posotion of every part of body snake*/
const int* Snake::getPositionOfSnakeParts(const int _id = 0) const{
	return (Snake::body.at(_id)).getCurrentPositionOfPart();
}

/*For getting count of eaten apples during playing*/
int Snake::getNumberOfEatenApples() const{
	return this->apples_eaten;
}

/*For getting direction of the head*/
int Snake::getDirection() const{
	return (Snake::body.at(0)).getDirectionOfPart();
}

/*For getting count parts of snake*/
int Snake::getNumberOfSnakeParts() const{
	return Snake::body.size();
}

/*For getting each part of snake*/
Snake::SnakePart* Snake::getSnakePart(const int _id = 0) const{
	return &(Snake::body.at(_id));
}



/*Create head or some part of snake and set position and other needed value*/
Snake::SnakePart::SnakePart(const int _id, const int _direction) : _id(_id), 
																   next_position(new int[2]),
													   			   curr_position(new int[2]),
													   			   prev_position(new int[2]){
	this->_direction = _direction;
	if(_id == 0){
		this->curr_position[0] = START_POSITION_X;
		this->curr_position[1] = START_POSITION_Y;
	}
	else{
		if(this->_direction == Direction::__up__){
			this->curr_position[0] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[0];
			this->curr_position[1] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[1]-1;
		}
		else if(this->_direction == Direction::__down__){
			this->curr_position[0] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[0];
			this->curr_position[1] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[1]+1;
		}
		else if(this->_direction == Direction::__left__){
			this->curr_position[0] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[0]+1;
			this->curr_position[1] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[1];
		}
		else if(this->_direction == Direction::__right__){
			this->curr_position[0] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[0]-1;
			this->curr_position[1] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[1];
		}
		else{
			this->curr_position[0] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[0];
			this->curr_position[1] = ( Snake::body.at(_id-1) ).getCurrentPositionOfPart()[1]-1;
		}
	}
}

/*For getting next position of the current SnakePart*/
const int* Snake::SnakePart::getNextPositionOfPart() const{
	return this->next_position;
}

/*For getting current position of the current SnakePart*/
const int* Snake::SnakePart::getCurrentPositionOfPart() const{
	return this->curr_position;
}

/*For getting prev position of the current SnakePart*/
const int* Snake::SnakePart::getPrevPositionOfPart() const{
	return this->prev_position;
}

/*For getting direction value of the current SnakePart*/
int Snake::SnakePart::getDirectionOfPart() const{
	return this->_direction;
}

/*For getting ID value of the current SnakePart
If ID == 0 it meens that is the head of snake*/
int Snake::SnakePart::getIdOfPart() const{
	return this->_id;
}


/*Set new position for snake part*/
void Snake::SnakePart::setNextPositionOfPart(const int _x_pos = 0, const int _y_pos = 0){
	(this->next_position[0])+=_x_pos;
	(this->next_position[1])+=_y_pos;
}

void Snake::SnakePart::setNewPositionOfPart(){
	this->prev_position[0] = this->curr_position[0];
	this->prev_position[1] = this->curr_position[1];
	
	this->curr_position[0] = this->next_position[0];
	this->curr_position[1] = this->next_position[1];
}



/*Destructors*/
Snake::SnakePart::~SnakePart(){
	//delete[] this->next_position;
	//delete[] this->curr_position;
	//delete[] this->prev_position;
}
Snake::~Snake(){}
/*For fix the undefined reference error ;)*/
std::vector<Snake::SnakePart> Snake::body;

#endif
