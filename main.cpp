#include <iostream>
#include <math.h>
#include <fstream>
#include <ctime>

//#include "mvector.h"
#include "AbstractedContainer.h"
#include "SortingAlgorithms.h"
#include "CoordinateArray.h"
#include "Timing.h"

//TO DO LIST
//o Look at optimising runtime for larger patterns and higher generation counts
//o STABLE CONFIGURATIONS: Check if the previous set of living cells is the same as the current and end the program with a STABLE OUTCOME output.
//o Move GoL functions to separate header file?


//Function which takes the cells to be tested TestCells, a cell index j and the current living cells LiveCells and returns whether the selected test cell is in the current living cells
bool inLiveCells(CoordinateArray &TestCells, CoordinateArray &LiveCells, int j){
	bool inLiveCells = false;
	for(int i = 0; i < LiveCells.size(); i++){
		if(LiveCells.getX(i) == TestCells.getX(j) && LiveCells.getY(i) == TestCells.getY(j)){
			inLiveCells = true; break;
		}
	}
	return inLiveCells;
}


//Function which takes all possible next gen cells NeighbouringCells, a cell index j and the cells to be tested and returns how many occurences in NeighbouringCells the current test cell has
int HowManyNeighbours(CoordinateArray &TestCells, CoordinateArray &NeighbouringCells, int j){
	int count = 0;
	for(int i = 0; i < NeighbouringCells.size(); i++){
		if(NeighbouringCells.getX(i) == TestCells.getX(j) && NeighbouringCells.getY(i) == TestCells.getY(j)){
			count += 1;
		}
	}
	return count;
}

//Function which removes all duplicate tuples from the CoordinateArray inputted
CoordinateArray RemoveDuplicates(CoordinateArray &CoordArr){
	CoordinateArray Temp(0);
	for(int i = 0; i < CoordArr.size()-1; i++){
		if((CoordArr.getX(i) != CoordArr.getX(i+1)) || (CoordArr.getY(i) != CoordArr.getY(i+1))){
			Temp.resize(Temp.size()+1);
			Temp.setX(Temp.size()-1, CoordArr.getX(i));
			Temp.setY(Temp.size()-1, CoordArr.getY(i));
		}
	}
	
	Temp.resize(Temp.size()+1);
	Temp.setX(Temp.size()-1, CoordArr.getX(CoordArr.size()-1));
	Temp.setY(Temp.size()-1, CoordArr.getY(CoordArr.size()-1));
	return Temp;
}

//Working Game of Life code
CoordinateArray PlayGOL(CoordinateArray &LiveCells, int MaxIterations){
	for(int i = 0; i < MaxIterations+1; i++){
		
		//Outputs current generation number if MaxIterations not reached
		//Outputs final generation number, number of current living cells and the coordinates of said living cells
		
		if(i != MaxIterations){
			std::cout << "Generation " << i << "\n";
		}else{
			std::cout << "Generation " << i << ": Amount living " << LiveCells.size() << ", Living Cells: " << LiveCells << "\n";
		}
			
		//Reset storage CoordinateArrays
		CoordinateArray NextGenLivingCells(0);
		CoordinateArray NeighbouringCells(0);
		
		//Generates CoordinateArray of NeighbouringCells for all currently living cells
		for(int counter = 0; counter < LiveCells.size(); counter++){
			for (int dx = -1; dx <= 1; dx++) {
				for (int dy = -1; dy <= 1; dy++) {
					if (dx != 0 || dy != 0) {
						NeighbouringCells.resize(NeighbouringCells.size()+1);
						NeighbouringCells.setX(NeighbouringCells.size() - 1, LiveCells.getX(counter) + dx);
						NeighbouringCells.setY(NeighbouringCells.size() - 1, LiveCells.getY(counter) + dy);
					}
				}
			}
		}
		
		//Go through each NeighbouringCells entry, test whether it is in live cells, count how many times in NeighbouringCells and add to NextGenLiving according to the rules of GOL
		for(int i = 0; i < NeighbouringCells.size(); i++){
			int NeighbourCount = HowManyNeighbours(NeighbouringCells, NeighbouringCells, i);
			bool LiveCellBoolean = inLiveCells(NeighbouringCells, LiveCells, i);
			if(LiveCellBoolean == true && (NeighbourCount == 2 || NeighbourCount == 3)){
				
				NextGenLivingCells.resize(NextGenLivingCells.size()+1);
				NextGenLivingCells.setX(NextGenLivingCells.size() - 1, NeighbouringCells.getX(i));
				NextGenLivingCells.setY(NextGenLivingCells.size() - 1, NeighbouringCells.getY(i));
				
			} else if (LiveCellBoolean == false && (NeighbourCount == 3)){
				
				NextGenLivingCells.resize(NextGenLivingCells.size()+1);
				NextGenLivingCells.setX(NextGenLivingCells.size() - 1, NeighbouringCells.getX(i));
				NextGenLivingCells.setY(NextGenLivingCells.size() - 1, NeighbouringCells.getY(i));
				
			}
		}
		
		//Check to see if all living cells have died, end game if so
		if(NextGenLivingCells.size() == 0){
			std::cout << "All cells have died: GAME OVER \n";
			break;
		}
		
		//Run heapsort and removes duplicate cells found in NextGenLiving to save memory
		quick(NextGenLivingCells);
		NextGenLivingCells = RemoveDuplicates(NextGenLivingCells);
		
		//Set NextGenLivingCells as LiveCells
		LiveCells.resize(NextGenLivingCells.size());
		for(int i = 0; i < NextGenLivingCells.size(); i++){
			LiveCells.setX(i, NextGenLivingCells.getX(i));
			LiveCells.setY(i, NextGenLivingCells.getY(i));
		}
	}
	
	return LiveCells;
}



int main() {
	//GAME OF LIFE INSTRUCTIONS
	//o Set the number of iterations you wish to be evolved
	//o Enter the amount of initially living cells in the InitialCellCount variable
	//o Set the X and Y coordinates of each intial living cell, remembering to change the coordinate index for each living cell
	//		i.e. The first living cell (5,4) is set with index 0 as:
	//			LiveCells.setX(0,5);
	//			LiveCells.setY(0,4);
	// 		then the next living cell (5,5) is set with index 1 as:
	//			LiveCells.setX(1,5);
	//			LiveCells.setY(1,5);
	
	//Number of iterations
	int MaxIterations = 5206;
	
	//EXAMPLE INITIAL PATTERNS
	//2x2 Block Pattern//
//	int InitialCellCount = 4;
//	CoordinateArray LiveCells(InitialCellCount);
//	LiveCells.setX(0,1);
//	LiveCells.setY(0,1);
//	LiveCells.setX(1,1);
//	LiveCells.setY(1,2);
//	LiveCells.setX(2,2);
//	LiveCells.setY(2,1);
//	LiveCells.setX(3,2);
//	LiveCells.setY(3,2);
	
	//Blinker Pattern//
//	int InitialCellCount = 3;
//	CoordinateArray LiveCells(InitialCellCount);
//	LiveCells.setX(0,5);
//	LiveCells.setY(0,4);
//	LiveCells.setX(1,5);
//	LiveCells.setY(1,5);
//	LiveCells.setX(2,5);
//	LiveCells.setY(2,6);


	//Acorn Pattern//
	int InitialCellCount = 7;
	CoordinateArray LiveCells(InitialCellCount);
	LiveCells.setX(0,10001);
	LiveCells.setY(0,10001);
	LiveCells.setX(1,10002);
	LiveCells.setY(1,10001);
	LiveCells.setX(2,10002);
	LiveCells.setY(2,10003);
	LiveCells.setX(3,10004);
	LiveCells.setY(3,10002);
	LiveCells.setX(4,10005);
	LiveCells.setY(4,10001);
	LiveCells.setX(5,10006);
	LiveCells.setY(5,10001);
	LiveCells.setX(6,10007);
	LiveCells.setY(6,10001);

	//Play the game of life with Initial chosen cells and number of iterations selected
	LiveCells = PlayGOL(LiveCells, MaxIterations);
	
	
	
	//Ensuring RNG is different on each call (non-fixed seed)
	//std::srand(std::time(NULL));
	
	//Code sorting tuples of coordinates of length 100 to 5000
//
//	int MaxArrayLength = 5000;
//	double HeapTime = 0.0;
//
//	//Bubblesort Coordinates execute code
//	 std::ofstream FileStream;
//	FileStream.open("HeapCoordAlg.txt");
//	 if (!FileStream) return 1;
//
//	 for(int i = 100; i <= MaxArrayLength; i+=100){
//		 CoordinateArray coordArr(i);
//
//		 double HeapTotalTime = 0.0;
//		 double HeapAverageTime = 0.0;
//
//		 //Create 100 instances of a vector of length i
//		 for(int j = 0; j < 100; j++){
//
//			 //Create random coordinate array of length i
//			 for(int k = 0; k < i; k++){
//				 coordArr.setRandX(k);
//				 coordArr.setRandY(k);
//			 }
//
//			 double HeapStartTime = Timer();
//			 heap(coordArr);
//			 double HeapEndTime = Timer();
//			 HeapTime = (HeapEndTime - HeapStartTime);
//			 HeapTotalTime = HeapTotalTime + HeapTime;
//		 }
//
//		 HeapAverageTime = HeapTotalTime / 100;
//		 FileStream.width(15); FileStream << i;
//		 FileStream.width(15); FileStream << HeapAverageTime << std::endl;
//		 std::cout << "Arrays of size " << i << " sorted \n";
//	 }
//
//	FileStream.close();
//
	
	
	
	
	//Code sorting 1D vectors of length 100 to 5000
//	//Initialise as random for each random vector call
//	std::srand(std::time(NULL));
//
//	int MaxArrayLength = 5000;
//
//	double BubbleTime = 0.0;
//
//	 //Bubblesort execute code
//	std::ofstream FileStream;
//	FileStream.open("BubbleAlg.txt");
//	if (!FileStream) return 1;
//
//	 for(int i = 100; i <= MaxArrayLength; i+=100){
//		 MVector BubbleVect(i);
//
//		 double BubbleTotalTime = 0.0;
//		 double BubbleAverageTime = 0.0;
//
//		 //Create 50 instances of a vector of length i
//		 for(int j = 0; j < 100; j++){
//			 BubbleVect.initialise_random(0, 1);
//
//			 double BubbleStartTime = Timer();
//			 bubble(BubbleVect);
//			 double BubbleEndTime = Timer();
//			 BubbleTime = (BubbleEndTime - BubbleStartTime);
//			 BubbleTotalTime = BubbleTotalTime + BubbleTime;
//		 }
//
//		 BubbleAverageTime = BubbleTotalTime / 100;
//		 FileStream.width(15); FileStream << i;
//		 FileStream.width(15); FileStream << BubbleAverageTime << std::endl;
//		 std::cout << "Arrays of size " << i << " sorted \n";
//	 }
//	FileStream.close();
	
	
}

