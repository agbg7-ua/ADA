//ANDREA GÓMEZ BOBES 48679841L
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
double pasos = 0;
//Coste: T(n)
unsigned long pow2_1(unsigned n){
    long pow2 = 2;
    pasos++;
    if(n==0){
        return 1;
    }
    for(unsigned int i = 1;i<n;i++){
        pow2 = pow2 * 2;
        pasos++;
    }

    return pow2;
}
//Coste: T(log n)
unsigned long pow2_2(unsigned n){
    
    pasos++;
    if(n==0){
        return 1;
    }

    if(n%2 == 0){

        return (pow2_2(n/2))*(pow2_2(n/2));
    }else{

        return 2*(pow2_2(n/2))*(pow2_2(n/2));
    }

}
//Coste: T(2^n)
unsigned long pow2_3(unsigned n){
    pasos++;
    if(n==0){
        return 1;
    }
    return pow2_3(n-1) + pow2_3(n-1);
}
int main(){
        int n =4;
        cout << "n   " << "pow2_1_pasos   " << "pow2_2_pasos   " <<"pow2_3_pasos"<< endl;
        cout << "--------------------------------------------------------------------------------" <<endl;
    while(n>=0){
        
        pasos = 0;
        pow2_1(n);
        cout<< n << "\t" <<pasos << "\t";
        pasos = 0;
        pow2_2(n);
        cout << pasos << "\t";
        pasos = 0;
        pow2_3(n);
        cout<<pasos <<endl;
        n--;
    }


    

}
