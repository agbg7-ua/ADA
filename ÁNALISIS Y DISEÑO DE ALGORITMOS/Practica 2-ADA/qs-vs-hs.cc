/*
ANDREA GOMEZ BOBES
ADA. 2022-23
Práctica 2:"Empirical analysis by means of program-steps account of two sorting algorithms: Middle-Quicksort and Heapsort."
*/
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <iomanip>


using namespace std;
double pasos = 0;

//--------------------------------------------------------------
// Middle Quick Sort
void middle_QuickSort(int * v, long left, long right){
	if (left<right){
	    long i=left; 
        long j=right;
		int pivot=v[(i+j)/2];
		do {
            while (v[i]<pivot) {i++; pasos++;}
            while (v[j]>pivot) {j--; pasos++;}
            if (i<=j){ 
                swap(v[i], v[j]);
                i++; j--;
            }
        } while (i<=j);
        if (left < j)  middle_QuickSort(v,left,j);
        if (i < right) middle_QuickSort(v,i,right);
    }
    pasos++;
}

//--------------------------------------------------------------                
//HEAPSORT
// Procedure sink used by Heapsort algorith
// Sink an element (indexed by i) in a tree to keep the heap property. n is the size of the heap. 

void sink(int *v, size_t n, size_t i) {
    pasos++;
    do {
        size_t largest = i;  // Initialize largest as root
        size_t l = 2*i + 1;  // left = 2*i + 1
        size_t r = 2*i + 2;  // right = 2*i + 2
 
    // Is left child larger than root?
        if (l < n && v[l] > v[largest])
            largest = l;
 
    // Is right child larger than largest so far
        if (r < n && v[r] > v[largest])
            largest = r;
 
    // If largest is still root then the process is done
        if (largest == i) break;
    
	// If not, swap new largest with current node i and repeat the process with childs. 
        swap(v[i], v[largest]);
        i=largest;  
        pasos++;
     } while (true);
}
 
//--------------------------------------------------------------                
// Heapsort algorithm (ascending sorting)
void heapSort(int *v, size_t n) {
    pasos++;
    if( n < 2 ) // nothing to do
        return;

    // Build a MAX-HEAP with the input array
    for (size_t i = n / 2 - 1; true; i--) {
        pasos++;
        sink(v, n, i);
        if (i==0) break; //as size_t is unsigned type
	}	

  	// A this point we have a HEAP on the input array, let's take advantage of this to sort the array:
    // One by swap the first element, which is the largest (max-heap), with the last element of the vector and rebuild heap by sinking the new placed element on the begin of vector.  
    for (size_t i=n-1; i>0; i--) {
        pasos++;
		// Move current root to the end.
        swap(v[0], v[i]);
 		// Now largest element is at the end but do not know if the element just moved to the beginning is well placed, so a sink process is required.
		// Note that, at the same time, the HEAP size is reduced one element by one.
        sink(v, i, 0);
		// The procedure ends when HEAP has only one element, the lower of the input array
    }
}

int main(void){
    cout<<"#QUICKSORT VERSUS HEAPSORT" <<endl;
    cout<<"#Average processing Msteps (millions os programs steps)" <<endl;
    cout<<"#Number of samples (arrays of integer): 30" <<endl;
    cout <<"#\t\t RANDOM ARRAYS" << "\t SORTES ARRAYS" << "\t REVERSE SORTED ARRAYS"<< endl;
    cout<<"#\t      -----------------" <<" ----------------" <<" ---------------------" <<endl;
    cout << "#\tSize" <<"\tQuickSort" <<" HeapSort" <<" QuickSort" <<" HeapSort"<<" QuickSort" <<" HeapSort" << endl;
    cout << "#========================================================================================================" <<endl;
    srand(0);

    for (int exp = 15; exp <= 20; exp++){
        size_t size = size_t( pow(2,exp) );
        int* vAl = new int [size];
        int* vOrd = new int[size];
        int* vInv = new int[size];
        if (!vAl){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }
        if (!vOrd){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }
        if (!vInv){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }
        cout << "\t";
        cout << size << "\t  " << std::flush;
        for(unsigned int i = 0;i < 30; i++){
            for (size_t j = 0; j < size; j++) 
                vAl[j] = rand(); 

            middle_QuickSort(vAl, 0, size - 1);
        }
        cout << std::setprecision(3) << std::fixed << (pasos/30)/1000000;
	    cout << "     ";
	    pasos = 0;
        for(unsigned int i = 0;i < 30; i++){
            for (size_t j = 0; j < size; j++) 
                vAl[j] = rand(); 

            heapSort(vAl,size);
        }
        cout << std::setprecision(3) << std::fixed << (pasos/30)/1000000;
	    cout << "     ";
	    pasos = 0;

        for(size_t  j = 0; j < size;j++){
            vOrd[j] = j;
        }
        middle_QuickSort(vOrd, 0, size - 1);
        cout << std::setprecision(3) << std::fixed << (pasos/30)/1000000 ;
	    cout << "     ";
	    pasos = 0;

        heapSort(vOrd,size);
        cout << std::setprecision(3) << std::fixed << (pasos/30)/1000000;
	    cout << "     ";
	    pasos = 0;
        for(size_t  j = 0; j < size;j++){
            vInv[j] = (size-1) - j;
        }
        middle_QuickSort(vInv, 0, size - 1);
        cout << std::setprecision(3) << std::fixed << (pasos/30)/1000000;
	    cout << "     ";
	    pasos = 0;

        heapSort(vInv,size);
        cout << std::setprecision(3) << std::fixed << (pasos/30)/1000000;
	    cout << endl;
	    pasos = 0;
        for (size_t i = 1; i < size; i++)
			if (vAl[i] < vAl[i-1]){ 
				cerr << "Panic, array not sorted! " << i << endl; 
				exit(EXIT_FAILURE);            
			}

        delete[] vAl; 
    for (size_t i = 1; i < size; i++)
			if (vOrd[i] < vOrd[i-1]){ 
				cerr << "Panic, array not sorted! " << i << endl; 
				exit(EXIT_FAILURE);            
			}

        delete[] vOrd; 
    for (size_t i = 1; i < size; i++)
			if (vInv[i] < vInv[i-1]){ 
				cerr << "Panic, array not sorted! " << i << endl; 
				exit(EXIT_FAILURE);            
			}

        delete[] vInv; 
    }

    

}