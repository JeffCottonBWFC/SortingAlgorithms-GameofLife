#include <iostream>
#include <math.h>
#include <fstream>
#include <ctime>

//#include "mvector.h"
#include "AbstractedContainer.h"
#include "SortingAlgorithms.h"
#include "CoordinateArray.h"
#include "Timing.h"
#include "GameOfLife.h"

//TO DO LIST
//o Look at optimising runtime for larger patterns and higher generation counts
//o STABLE CONFIGURATIONS: Check if the previous set of living cells is the same as the current and end the program with a STABLE OUTCOME output.


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

