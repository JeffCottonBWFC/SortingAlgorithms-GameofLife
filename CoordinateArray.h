#ifndef CoordinateArray_h
#define CoordinateArray_h

//Integer Coordinates
class IntegerCoordinate{
public:
	unsigned X, Y;
};


//CoordinateArray class, deriving from SortableContainer
class CoordinateArray : public SortableContainer{
	std::vector<IntegerCoordinate> v;
public:
	CoordinateArray() {}
	CoordinateArray(int n):v(n){}
	
	//Random number boundaries
	int MinRand = 0;
	int MaxRand = 100;
	
	//Set X-coord of vector to chosen integer
	void setX(int i, int x){
		if (i+1 > v.size() || i < 0){
			std::cout << "Error: Index outside range" << std::endl;
			exit(-1);
		}
		else{
			v[i].X = x;
		}
	}
	
	//Set X-coord of vector to random value between MinRand and MaxRand
	void setRandX(int i){
		if (i + 1 > v.size() || i < 0){
			std::cout << "Error: Index outside range" << std::endl;
			exit(-1);
		}
		else{
			v[i].X = rand() % (MaxRand - MinRand + 1) + MinRand;
		}
	}
	
	//Set Y-coord of vector to chosen integer
	void setY(int i, int y){
		if (i + 1 > v.size() || i < 0){
			std::cout << "Error: Index outside range" << std::endl;
			exit(-1);
		}
		else{
			v[i].Y = y;
		}
	}
	
	//Set Y-coord of vector to random value between MinRand and MaxRand
	void setRandY(int i){
		if (i + 1 > v.size() || i < 0){
			std::cout << "Error: Index outside range" << std::endl;
			exit(-1);
		}
		else{
			v[i].Y = rand() % (MaxRand - MinRand + 1) + MinRand;
		}
	}
	
	//Returns X value of selected vector
	double getX(int i){
		if (i + 1 > v.size() || i < 0){
			std::cout << "Error: Index outside range" << std::endl;
			exit(-1);
		}
		else{
			return v[i].X;
		}
	}
	
	//Returns Y value of selected vector
	double getY(int i){
		if (i + 1 > v.size() || i < 0){
			std::cout << "Error: Index outside range" << std::endl;
			exit(-1);
		}
		else{
			return v[i].Y;
		}
	}
	
	//Comparison operator
	bool cmp(int i, int j){
		if((getX(i) < getX(j)) || ((getX(i) == getX(j)) && (getY(i) < getY(j)))){
			return true;
		} else {
			return false;
		}
	}
	
	//Swap two values in a vector
	void swap(int i, int j){
		double TempX = 0;
		double TempY = 0;
		
		TempX = getX(i);
		TempY = getY(i);
		setX(i, getX(j));
		setY(i, getY(j));
		setX(j, TempX);
		setY(j, TempY);
	}
	
	//Resizing chosen vector
	void resize(int n){
		v.resize(n);
	}
	
	//Returns size of vector
	int size() const { return v.size(); }
};


// Overload the << operator to output CoordinateArrays to screen or file
std::ostream& operator<<(std::ostream& os, CoordinateArray& v){
	int n = v.size();
	if (n > 0){
		os << "(";
		for(int i = 0; i < n-1; i++){
			os << "(" << v.getX(i) << "," << v.getY(i) << ")" << ", ";
		}
		os << "(" << v.getX(n-1) << "," << v.getY(n-1) << ")";
		os << ")";
		return os;
	}
	else{
		os << "( )";
		return os;
	}
}


#endif /* CoordinateArray_h */
