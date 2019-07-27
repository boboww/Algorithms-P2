#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector> 

using namespace std;

// Function to print vector
void print(vector<int> const &num){                    
    for (unsigned int i = 0; i < num.size(); i++){     	// 0(n)
        cout << num.at(i) << ' ';                       // 0(1)
    }													// total complexity 0(n)
}

int minMaxVec(vector<int> vec, int flag){              	// function for both min and max of vectors output depends on flag
    int min = vec[0];                                   // 0(1)    
    int max = vec[0];                                   // 0(1)
    vector<int>::iterator it;                           // 0(1)

    for(unsigned int i = 1; i < vec.size(); i++){    	// 0(n)
        if (vec[i] < min) {								// total complexity 0(n)
            min = vec[i];
        }if (vec[i] > max) {
            max = vec[i];
        }
    }if(flag == 1){                                     // 1 for min
        return min;
    }else{                                              // anything else for max
        return max;
    }
}

// Function to find both min and max of int
int minMax(int a, int b, int flag) {                    
    int min;                                            // output (min/max) depends on flag
    int max;

    if(a > b){
        max = a;										// save both max and min
        min = b;
    }else{
        max = b;
        min = a;
    }if(flag == 1){                                     // 1 for min
        return min;
    }else{
        return max;                                     // anything else for max
    }
}

// Calculate min height
int vectorMax(vector<int> A, vector<int> B){             
    int maxA = minMaxVec(A, 0);							// get max of vector A
    int maxB = minMaxVec(B, 0);							// get max of vector B
    int minA = minMaxVec(A, 1);							// get min of vector A
    int minB = minMaxVec(B, 1);							// get min of vector B

    int maxSum = maxA + maxB;							// sum of maxes of A and B
    int maxAB = maxA + minB;
    int maxBA = minA + maxB;
    int maxFin = minMax(maxAB, maxBA, 0);

    int beginA = A.front();
    int beginB = B.front();
    int beginSum = beginA + beginB;
    int endA = A.back();
    int endB = B.back();
    int endSum = endA + endB;

    if (beginSum == maxSum || endSum == maxSum) { 		// select which max to use as minimum height
        return maxSum;
    }if (beginSum > maxFin) {
        return beginSum;
    }if (endSum > maxFin) {
        return endSum;
    }else{
        return maxFin;
    }
}

// Returns the next move to make, favoring the center 
pair<int, int> nextMove(vector<vector<int>> &jaw, pair<int, int> &position, int &max) {
    pair<int, int> p1;															// initialize current pair

	int rightMove = 0;
	int downMove = 0;
	int centerMove = 0;	
	
	int pos1 = (position.first)+1;
	int pos2 = (position.second)+1;
	
	if(pos1 != 0){																// stop when reaching right sentinel values
		rightMove = max - jaw[position.first][position.second + 1];
    }if(pos2 != 0){																// same as above but for down sentinels
		downMove = max - jaw[position.first + 1][position.second];
	}if(pos1 != 0 && pos2 != 0){												// same as above but for diagonal sentinels
		centerMove = max - jaw[position.first + 1][position.second + 1];		
	}
	
	if(pos1 != 0){																// conditional for right movement
		if (rightMove >= 0) {
			if (rightMove < centerMove || centerMove < 0) {
				if (rightMove <= downMove || downMove < 0) {
					p1.first = position.first;
					p1.second = position.second + 1;
				}
			}
		}
	}if(pos2 != 0){																// conditional for down movement
		if (downMove >= 0) {
			if ((downMove <= centerMove) || (centerMove < 0) ) {
				if ( (downMove <= rightMove) || (rightMove < 0) ) {
					p1.first = position.first + 1;
					p1.second = position.second;
				}
			}
		}
	}if(pos1 != 0 && pos2 != 0){												// conditional for right+down movement (diagonal)
		if (centerMove >= 0) {
			if (centerMove < rightMove || rightMove < 0) {
				if (centerMove <= downMove || downMove < 0) {
					p1.first = position.first + 1;
					p1.second = position.second + 1;
				}
			}
		}
	}
    return p1;
}

// Memoized Function
int MemoizeFunc(vector<vector<int>> &jaw, vector<int> &top, vector<int> &bot, pair<int, int> &position) {
	jaw[position.first][position.second] = top[position.first] + bot[position.second];
	
	int top1 = (top.size())-1;
	int bot1 = (bot.size())-1;
	int pos1 = (position.first)+1;
	int pos2 = (position.second)+1;
		
	if (pos1 < top1) {
        jaw[position.first + 1][position.second] = top[position.first + 1] + bot[position.second];
        if (position.second + 1 < (int) bot.size()) {
            jaw[position.first + 1][position.second + 1] = top[position.first + 1] + bot[position.second + 1];
        }
    }if (pos2 < bot1) {
        jaw[position.first][position.second + 1] = top[position.first] + bot[position.second + 1];
    }
	return 0;
}

int main() {
    int topCount = 0;                                       	//number of elements in top
    int botCount = 0;                                       	//number of elements in bot
    int temp1 = 0;
	int temp2 = 0;
	int i = 0;	
 
    ifstream input("input.txt");                         		//File IO
    ofstream output("output.txt");								//open files

    if (!input.is_open()) {                               		//check for valid input file                
        cout << "Can't open input.txt" << endl;             	//throw if file error
        return 0;
    }if (!output.is_open()) {                              		//check for valid output file               
        cout << "Can't open output.txt" << endl;            	//throw if file error
        return 0;
    }

    input >> topCount;                                      	//put first number into ar1
    input >> botCount;                                      	//put second number into ar2

    vector<int> top;                                        	//create vector for top
    vector<int> bot;                                        	//create vector for bot
 
    for (i = 0; i < topCount; i++) {                			//Filling vectors from Input      	
        input >> temp1;
        top.push_back(temp1);									//push input to top
    }
    for (i = 0; i < botCount; i++) {                     	
        input >> temp2;
        bot.push_back(temp2);									//push input to bot
    }		
    int max = vectorMax(bot, top);  							//determine max (min height) of two vectors
	
	top.push_back(temp1);
	bot.push_back(temp2);
	
    vector <vector<int>> jaw;                               	//create 2d jaw vector
    jaw.resize(botCount+2, vector<int>(topCount+2, 0));    		//resize jaw to be of ar1xar2

	for(int i = 0; i < topCount; i++){
		for(int j = 0; j < botCount; j++){
			jaw[i][j] = -1;
		}
	}
    vector<pair<int, int>> path;								//initialize path vector

    cout << endl << "Min Height: " << max << endl;          	//display minimum height
    output << max;                                          	//print max to output
    cout << endl;
    output << endl;
	
    print(top);                                             	//print out arrays
    cout << endl;                                           	//for debugging
    print(bot);
    cout << endl << endl;
	
    cout << "Top elements:" << topCount << endl;        		//print out # of array elements
    cout << "Bot elements:" << botCount << endl << endl;   		//for debugging

    pair<int, int> position;
    jaw[0][0] = top[0] + bot[0];
	
	int top1 = top.size();
	int bot1 = bot.size();
	int pos1 = position.first;
	int pos2 = position.second;	
	
    while(pos1 < top1 && pos2 <= bot1){        					//loop to execute main algorithms          		

        output << top.at(position.first) << " ";				//print to output
		output << bot.at(position.second) << endl; 	
        MemoizeFunc(jaw, top, bot, position);           		//Set start position and moves to needed values
        position = nextMove(jaw, position, max);   				//Position is calculated through nextMove.  
		
		top1 = (top.size())-1;
		bot1 = (bot.size())-1;
		pos1 = (position.first);
		pos2 = (position.second);
    }		
	
	for(i = 0; i < (int) bot.size(); i++){
        for (int j = 0; j < (int) top.size(); j++) {
            cout << jaw[j][i] << " | ";                      	//print jaw to terminal 
        }
        cout << endl;
    }    
    input.close();                                          	//close files
    output.close();
}