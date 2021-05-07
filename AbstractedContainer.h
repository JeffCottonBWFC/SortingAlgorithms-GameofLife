#ifndef AbstractedContainer_h
#define AbstractedContainer_h

#include <vector>

//Container as a base class for sorting operations
class SortableContainer{
public:
	virtual int size() const = 0;
	virtual void swap(int i, int j) = 0;
	virtual bool cmp(int i, int j) = 0;
};



// Derived class that represents a mathematical vector
class MVector : public SortableContainer{
public:
	// constructors
	MVector() {}
	explicit MVector(int n) : v(n) {}
	MVector(int n, double x) : v(n, x) {}
	MVector(std::initializer_list<double> l) : v(l) {}
	
	// access element (lvalue)
	double &operator[](int index){
		if(index+1 > v.size() || index < 0){
			std::cout << "Error: Index outside range" << std::endl;
			exit(-1);
		}
		else{
			return v[index];
		}
	}
	
	// access element (rvalue)
	double operator[](int index) const{
		if(index+1 > v.size() || index < 0){
			std::cout << "Error: Index outside range" << std::endl;
			exit(-1);
		}
		else{
			return v[index];
		}
	}
	
	// access size of vector
	int size() const { return v.size(); } // number of elements
	
	//Swap two values in a vector
	void swap(int i, int j){
		double Temp = 0;
		Temp = v[i];
		v[i] = v[j];
		v[j] = Temp;
	}
	
	//Compares 2 values in a vector, if first input element is less than second, return true. Change comparison operator here to alter ascending/descending values
	bool cmp(int i, int j){
		if(v[i] < v[j]){
			return true;
		}
		else{
			return false;
		}
	}
	
	//create vector of random numbers between min and max
	void initialise_random(double xmin, double xmax){
		size_t s = v.size();
		for (size_t i=0; i<s; i++)
			v[i] = xmin + (xmax-xmin)*rand()/static_cast<double>(RAND_MAX);
	}
	
private:
	std::vector<double> v;
};






// Overload the << operator to output MVectors to screen or file
std::ostream& operator<<(std::ostream& os, const MVector& v)
{
	int VectorSize = v.size();
	os << "(";
	for (int i=0; i < VectorSize-1; i++){
		os << v[i] << ", ";
	}
	os << v[VectorSize-1] << ")";
	return os;
}






#endif /* AbstractedContainer_h */
