#ifndef SortingAlgorithms_h
#define SortingAlgorithms_h

//BUBBLESORT FUNCTIONS
//Sorts a vector using the bubble sort algorithm. Compares pairs of consecutive elements and swaps them if the ith element is larger than the (i+1)th.
void bubble(SortableContainer &v){
	
	int VectorLength = v.size();
	
	for (int j=0; j<VectorLength-1; j++){
		for (int i=0; i<VectorLength-j-1; i++){
			if (v.cmp(i+1,i)){
				v.swap(i,i+1);
			}
		}
	}
}






//QUICKSORT FUNCTIONS
//Choose random pivot, move to end of vector, move all elements smaller than pivot to left and all larger to right.
int SetPartition(SortableContainer &v, int start, int end){
	int pivotIndex = start + rand() % (end - start);
	v.swap(end, pivotIndex);
	
	int i = start - 1;
	
	for(int j = start; j <= end-1; j++){
		if(v.cmp(j,end)){
			i++;
			v.swap(i,j);
		}
	}
	
	v.swap(i+1,end);
	
	return(i+1);
}


//While the sublist is larger than one, quicksort the remaining sublists.
void quick_recursive(SortableContainer &v, int start, int end){
	if(start < end){
		int PartIndex = SetPartition(v, start, end);
		quick_recursive(v, start, PartIndex - 1);
		quick_recursive(v, PartIndex + 1, end);
	}
}

//Wrapper function
void quick(SortableContainer &v) {quick_recursive(v,0,v.size()-1);}






//HEAPSORT FUNCTIONS
//Sorts a vector using the heapsort algorithm. Creates a heap from the initial array, create a max heap, then swap root and last item of heap and reduce heap size by 1. Repeat until only one element remains in heap.
void heap_from_root(SortableContainer &v, int i, int n){
	
	//Declares
	int biggest = i;
	int left = 2*i+1;
	int right = 2*i+2;
	
	//Checks if left child is larger than root node
	if(left < n && v.cmp(biggest,left)){
		biggest = left;
	}
	
	//Checks if right child is larger than current largest
	if(right < n && v.cmp(biggest,right)){
		biggest = right;
	}
	
	//Checks if largest is not the root(i.e. if only one element in heap) and heapsorts remaining heap.
	if(biggest != i){
		v.swap(i, biggest);
		heap_from_root(v, biggest, n);
	}
}

void heap(SortableContainer &v){
	//Declares
	int n = v.size();
	
	//Build the heap
	for(int i = n/2 - 1; i>=0; i--){
		heap_from_root(v, i, n);
	}
	
	//Take elements from heap one at a time, move root to end and heapsort the reduced heap
	for(int i = n - 1; i>=0; i--){
		v.swap(0, i);
		heap_from_root(v, 0, i);
	}
}




#endif /* SortingAlgorithms_h */
