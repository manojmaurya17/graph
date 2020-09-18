#include<iostream>
using namespace std;

void fun(){
     int arr1[20];
     for(int i=0;i<20l;i++){
         cin>>arr1[i];
     }
     int *arr = new int[20];
     for(int i=0;i<30;i++){
         cout<<i<<" "<<arr[i]<<","<<arr1[i]<<endl;
     }
}

int main(){
    fun();
    return 0;
}