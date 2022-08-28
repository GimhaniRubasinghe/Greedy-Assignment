#include <iostream>
using namespace std;


int main() {  
  
    int N,M,temp;
    
    cin>>N>>M;
    
	int S[M];
	int V[M];
	
	for(int i=0; i<M; i++){		//get the number of 7 KG sacks of paddy in each container
		cin>>S[i];
	}
    
    for(int i=0; i<M; i++){		//get the price of each paddy container
		cin>>V[i];
	}
    
    for(int i=0; i<M; i++)		//set S & V  such that V[i]/S[i] < V[j]/S[j] for i<j
	{		
		for(int j=i+1; j<M; j++)
		{
			if( (V[i]/S[i])  >  (V[j]/S[j]) )
			{
				temp =V[i];
				V[i]=V[j];
				V[j]=temp;
				
				temp =S[i];
				S[i]=S[j];
				S[j]=temp;
				
			}
		}
	}
     
	int R[M], Nt=0;
	
	for(int i=0; i<M; i++){		//Initial Results Set array
		R[i]=0;
	}
	int i=0;
	
	while (Nt < N){		//greedy choice        		       
		
		if( (Nt + S[i]) <= N){					  
			R[i]= S[i];                                   
			Nt = Nt + S[i];                        
		}
		
		else {												
			
			R[i] = (N - Nt);	
			Nt = N;															
			
		}
		
		i++;
	}
	
	int result=0;
	
	
	for(int i=0; i<M; i++){		//Calculate the value of the container corresponding to each greedy choice
	
		result =  result + ( R[i] * V[i] / S[i] );
	}
	
	cout << result;		//output
	
    return 0;
}
