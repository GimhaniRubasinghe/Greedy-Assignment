 #include<iostream>
#include<stdlib.h>
using namespace std;

int Count(int n,int a[]){ //Count the cities which are suitable to build a water treatment plant 
 	int count=0;
 	for(int j=0;j<n;j++){
 		if(a[j]==1){
 			count++;
		 }
	 }
	 return count;
 }
 
int FirstPlant(int k,int a[]){ //Find the first suitable city to build a water plant 
	//To find the optimal solution, first check if the (k-1)th city is suitable to build a water plant	(Greedy choice 1)
	//If it is not check the previous city and if its not, keep checking previous city until it comes first city.
	//When it comes first city, if it is also not suitable to build a water plant then returns -1
	for(int j=k-1;j>=0;j--){
		if(a[j]==1){
			return j;
		}
	}
	return -1;
}

void PrintArray(int n,int a[]){ //To print the indexes of cities where the water treatment plants should be built.
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
int main(){
	int n,k;
	cin >> n >> k ; //Get number of cities(n) in WonderLand and the plant range constant[k].
	
	if(n<1 || k<1 || 100000<n || 100000<k){ // 1<k,n<100000(constraint 1)
		cout<<"The number of cities in WonderLand(n) and the plant range constant(k) should be between 1 and 100000."<<endl;
		exit(0);
	}
	
	int MD[n];
	for(int i=0;i<n;i++){ 
		cin >> MD[i]; //Get whether it is suitable to build a water treatment plant in that city(input 1) or not(input 0).
		if(MD[i]!=0 && MD[i]!=1){
			cout<<endl<<"Ministry Data should be 0 or 1"<<endl;//Each MD[i] = 0 or MD[i] = 1.(constraint 2)
			exit(0);
		}
	}
	
	int count = Count(n,MD);//call the Count function and store in count 
	int Plant[count] , x ,min;
	Plant[0] = FirstPlant(k,MD);//call the FirstPlant function and store in Plant[0]
	if(Plant[0]!= -1){//check whether Plant[0] is not equel to -1, if it is print -1(it means that the given task can't be done)
	
		x = Plant[0]+(2*(k-1))+1; // Greedy Choice 2
		min = 1;
		while((x-k+1) < n){ //check whether x-(k-1) is less than number of cities
			if(Plant[min-1]!=x && MD[x]==1){ 
				Plant[min]=x;				
				x +=  (2*(k-1))+1; // Greedy Choice 2
				min++;
			}
			
			else if(Plant[min-1]!=x){
				x--;
			}
			
			else{
				cout<< -1 << endl;
				exit(0);
			}
		}

		if(n<=(Plant[min-1]+k)){ // check whether there are less than k cities after the last city which builds a water plant 
			cout<<min<<endl;
			PrintArray(min,Plant);
		}
		else{
			cout<< -1 << endl;
		}
	}
	else{
		cout<< -1 << endl;
	}
	
 }
 

