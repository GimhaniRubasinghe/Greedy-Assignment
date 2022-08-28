#include <iostream>
#include <vector>
#include <algorithm>
#include <stdbool.h>

using namespace std;

int findSmallest(int *teamSizes, int n, int k){           //Function which finds the smallest teamsize from the existing teams
    int low = *min_element(teamSizes, teamSizes + n);
    int high = *max_element(teamSizes, teamSizes + n);
 
    while (low <= high){
        int mid = low + (high - low) / 2;
        int countless = 0, countequal = 0;
        
        for (int i = 0; i < n; ++i){
            if (teamSizes[i] < mid){
            	++countless;
			}
            else if (teamSizes[i] == mid){
            	++countequal;
			}
        }
 
        if (countless < k && (countless + countequal) >= k){
            return mid;
        }
 
        else if (countless >= k){
            high = mid - 1;
        }
 
        else if (countless < k && countless + countequal < k){
            low = mid + 1;
        }
    }
}

int pickSmallest(int *teamSizes, int n, int k){			  //Function which finds the index of the smallest team from the 2d vector
	int index = 0;
	int smallestValue = findSmallest(teamSizes, n, k);
	for(int i = 0; i< n; i++){
		if(teamSizes[i] == smallestValue){
			index = i;
			break;
		}
	}
	return index;
}

void initialize(int *teamSizes, int n){					  //Initializing the team sizes to INT_MAX and the first team's size to 0
	teamSizes[0] = 0;
	for(int i=1;i<n;i++){
		teamSizes[i] = INT_MAX;
	}
}

bool checkExists(int value, vector<int> vec){			  //Checking the uniqueness of a skill within a team
	if (std::find(vec.begin(), vec.end(), value) != vec.end()){
		return true;
	}
	else return false;
}

int largestSmallerTeam(int *skills, int n){				 //Function which returns the largest smallest team
	int *teamSizes = new int[n]();
	
	initialize(teamSizes, n);     //Initializing teamSizes array
	
	int smallestTeam;
	bool inserted;
	int size;
	
	vector<vector<int> > teams;      //vector of vectors to store the teams
	vector<int> v;					//Initializing the first team
	v.push_back(INT_MAX);
	teams.push_back(v);
	int teamCount = 1;
	
	for(int i=0;i<n;i++){
		inserted = false;
		smallestTeam = pickSmallest(teamSizes, n, 1);			//Picking the smallest team   GREEDY CHOICE
		        
		if(checkExists(skills[i], teams[smallestTeam])){    //Checking if the skill is unique within the team
			int k = 2;
			while(k < teamCount+1){										//If the skill is not unique, 
				smallestTeam = pickSmallest(teamSizes, n, k);         //Picking the kth smallest team   GREEDY CHOICE
				if(!checkExists(skills[i], teams[smallestTeam])){
					vector<int> v;
					v.push_back(skills[i]);
					teams.push_back(v);
					teamSizes[smallestTeam]++;
					inserted = true;
					break;
				}
				k++;	
			}
			if(!inserted){							//If the skill is not unique within all existing teams, create a new team
				vector<int> vec;
				vec.push_back(skills[i]);        
				teams.push_back(vec);
				size = teams.size();
				teamSizes[size-1] = 1;
				teamCount++;
			}	
		}
		else{
			teams[smallestTeam].push_back(skills[i]);      //If the skill is unique within the current team then insert it
			teamSizes[smallestTeam]++;
		}
	}
	
	return findSmallest(teamSizes, n, 1);               //return the size of the smallest team
}

int main(){
	
	int testcases = 0;
	int n;
	
	cin >> testcases;
	
	for(int i=0;i<testcases;i++){
		cin >> n;
		int *skills = new int[n]();
		
		for(int j=0;j<n;j++){
			cin >> skills[j];
		}
		
		cout << largestSmallerTeam(skills,n);
	}
	return 0;
}
