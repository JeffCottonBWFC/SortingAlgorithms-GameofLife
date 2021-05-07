#ifndef GameOfLife_h
#define GameOfLife_h


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

#endif /* GameOfLife_h */
