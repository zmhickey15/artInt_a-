
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>  

using namespace std;
using namespace std::chrono;

class State {
public:
    int state[3][3];
    int nodeDepth;
    int Hvalue;
    State* parent;
    vector<State> child;
    State() {};

    void printState() {
        for (int k = 0; k < 3; k++) {
            for (int i = 0; i < 3; i++)
                cout << state[k][i] << " ";
            cout << endl;
        }
    }
    void add_child(State kid) {
        child.push_back(kid);

    }

    State get_child() {
        // loop for testing to get children 
    /*
          for(State k: child){
            cout <<endl;
            k.printState();
          }
          */
        State k = child.back();
        child.pop_back();
        return k;
        //return child.back();
    };

    bool operator<(const State& r) const
    {
        if (Hvalue != r.Hvalue) {
            return Hvalue < r.Hvalue;
        }

        return Hvalue < r.Hvalue;
    }

    bool operator>(const State& r) const
    {
        if (Hvalue != r.Hvalue) {
            return Hvalue > r.Hvalue;
        }

        return Hvalue > r.Hvalue;
    }
};

//function to assign hvalue for number of displaced tiles
void hValueDisplaced(State& state, State goal) {
    int calcHvalue = 0;

    calcHvalue += state.nodeDepth;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state.state[i][j] == 0) {
                continue;
            }
            if (state.state[i][j] != goal.state[i][j]) {
                calcHvalue++;
            }
        }
    }

    state.Hvalue = calcHvalue;
}
// h value distance to right state
void hValueDistance(State& state, State goal){
	int calcHvalue = 0;
	calcHvalue += state.nodeDepth;
	int value;
	for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
				value = state.state[i][j];
				switch (value){
					case 1:
						calcHvalue += abs( i - 0 + j - 0);
					break;
					case 2:
						calcHvalue += abs ( i - 0 + j-1);
					break;
					case 3:
						calcHvalue += abs( i - 0 + j -2);
					break;
					case 4:
						calcHvalue += abs( i - 1 + j-2 );
					break;
					case 5:
						calcHvalue += abs( i - 2 + j -2);
					break;
					case 6:
						calcHvalue += abs( i -2 + j -1);
					break;
					case 7:
						calcHvalue += abs(i - 2 + j - 0);
					break;
					case 8: 
						calcHvalue += abs( i - 1 + j - 0);				
            break;
					case 0:
            calcHvalue += abs (i -1 + j-1);
					break;					
					
							}
			}
			}
	
	 state.Hvalue = calcHvalue;
	
}

// s value
int sValue(State& state, State goal) {
    int calcHvalue = 0;
    calcHvalue += state.nodeDepth;

    if( !(state.state[0][0] + 1 == state.state[0][1] ||
        state.state[0][0] == 8 && state.state[0][1] == 1))
        calcHvalue+=2;
      if( !(state.state[0][1] + 1 == state.state[0][2] ||
        state.state[0][1] == 8 && state.state[0][2] == 1))
        calcHvalue+=2;
      if( !(state.state[0][2] + 1 == state.state[1][2] ||
        state.state[0][2] == 8 && state.state[1][2] == 1))
        calcHvalue+=2;

      if( !(state.state[1][2] + 1 == state.state[1][2] ||
        state.state[1][2] == 8 && state.state[2][2] == 1))
        calcHvalue+=2;
      if( !(state.state[2][2] + 1 == state.state[2][1] ||
        state.state[2][2] == 8 && state.state[2][1] == 1))
        calcHvalue+=2;
      if( !(state.state[2][1] + 1 == state.state[2][0] ||
        state.state[2][1] == 8 && state.state[2][0] == 1))
        calcHvalue+=2;
      if( !(state.state[2][0] + 1 == state.state[1][0] ||
        state.state[2][0] == 8 && state.state[1][0] == 1))
        calcHvalue+=2;
      if( !(state.state[1][0] + 1 == state.state[0][0] ||
        state.state[1][0] == 8 && state.state[0][0] == 1))
        calcHvalue+=2;
      if( state.state[1][1] !=1 )
         calcHvalue+=2;
  
        return calcHvalue;
    
  }

// hs value 
void hSvalue (State& state, State goal){
  int calcHvalue = 0;
	calcHvalue += state.nodeDepth;
	int value;
	for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
				value = state.state[i][j];
				switch (value){
					case 1:
						calcHvalue += abs( i - 0 + j - 0);
					break;
					case 2:
						calcHvalue += abs ( i - 0 + j-1);
					break;
					case 3:
						calcHvalue += abs( i - 0 + j -2);
					break;
					case 4:
						calcHvalue += abs( i - 1 + j-2 );
					break;
					case 5:
						calcHvalue += abs( i - 2 + j -2);
					break;
					case 6:
						calcHvalue += abs( i -2 + j -1);
					break;
					case 7:
						calcHvalue += abs(i - 2 + j - 0);
					break;
					case 8: 
						calcHvalue += abs( i - 1 + j - 0);				
            break;
					case 0:
            calcHvalue += abs (i -1 + j-1);
					break;					
					
							}
			}
			}
        int svalue = sValue(state, goal);
        svalue = svalue * 3;
	      calcHvalue += svalue;
	 state.Hvalue = calcHvalue;
}


/////////
int generatekids(State* start) {

    /// find the 0 pos k + i
    int numNodes = 0;
    int blankRow;
    int blankCol;
    for (int k = 0; k < 3; k++)
        for (int i = 0; i < 3; i++)
            if (start->state[k][i] == 0) {
                blankRow = k;
                blankCol = i;
            }
    //if +1 or -1 works swap 
    if (blankCol + 1 < 3) {
        //cout << "1";

        State child;// = new State();
        child.state[0][0] = start->state[0][0];
        child.state[0][1] = start->state[0][1];
        child.state[0][2] = start->state[0][2];
        child.state[1][0] = start->state[1][0];
        child.state[1][1] = start->state[1][1];
        child.state[1][2] = start->state[1][2];
        child.state[2][0] = start->state[2][0];
        child.state[2][1] = start->state[2][1];
        child.state[2][2] = start->state[2][2];
        child.nodeDepth = start->nodeDepth + 1;

        child.state[blankRow][blankCol] = start->state[blankRow][blankCol + 1];
        child.state[blankRow][blankCol + 1] = 0;
        start->add_child(child);
        numNodes++;
    }
    if (blankCol - 1 > -1) {
        State child; //= new State();
        //cout << "2";
        child.state[0][0] = start->state[0][0];
        child.state[0][1] = start->state[0][1];
        child.state[0][2] = start->state[0][2];
        child.state[1][0] = start->state[1][0];
        child.state[1][1] = start->state[1][1];
        child.state[1][2] = start->state[1][2];
        child.state[2][0] = start->state[2][0];
        child.state[2][1] = start->state[2][1];
        child.state[2][2] = start->state[2][2];
        child.nodeDepth = start->nodeDepth + 1;

        child.state[blankRow][blankCol] = start->state[blankRow][blankCol - 1];
        child.state[blankRow][blankCol - 1] = 0;
        start->add_child(child);
        numNodes++;

    }

    if (blankRow + 1 < 3) {
        State child;// = new State();
        //cout << "3";
        child.state[0][0] = start->state[0][0];
        child.state[0][1] = start->state[0][1];
        child.state[0][2] = start->state[0][2];
        child.state[1][0] = start->state[1][0];
        child.state[1][1] = start->state[1][1];
        child.state[1][2] = start->state[1][2];
        child.state[2][0] = start->state[2][0];
        child.state[2][1] = start->state[2][1];
        child.state[2][2] = start->state[2][2];
        child.nodeDepth = start->nodeDepth + 1;

        child.state[blankRow][blankCol] = start->state[blankRow + 1][blankCol];
        child.state[blankRow + 1][blankCol] = 0;
        start->add_child(child);
        numNodes++;



    }
    if (blankRow - 1 > -1) {
        State child;// = new State();
        //cout << "4";
        child.state[0][0] = start->state[0][0];
        child.state[0][1] = start->state[0][1];
        child.state[0][2] = start->state[0][2];
        child.state[1][0] = start->state[1][0];
        child.state[1][1] = start->state[1][1];
        child.state[1][2] = start->state[1][2];
        child.state[2][0] = start->state[2][0];
        child.state[2][1] = start->state[2][1];
        child.state[2][2] = start->state[2][2];
        child.nodeDepth = start->nodeDepth + 1;

        child.state[blankRow][blankCol] = start->state[blankRow - 1][blankCol];
        child.state[blankRow - 1][blankCol] = 0;
        start->add_child(child);
        numNodes++;
    }

    return numNodes;

    // start->add_child(child);
}

bool compareState(State state, State goal) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state.state[i][j] != goal.state[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool compareHValue(State i1, State i2) {
    return (i1.Hvalue > i2.Hvalue);
}

void propagateOld(State state) {
    if (state.child.size() == 0)
        return;
    for (State k : state.child) {
        k.nodeDepth = state.nodeDepth + 1;
        propagateOld(k);
    }
}

void removeChild(State parent, State child) {
    int i = 0;
    for (State k : parent.child) {
        if(compareState(child, k))
            parent.child.erase(parent.child.begin() + i);
    }
    cout << "unsuccessful remove\n";
}

void viewOPEN(vector<State> open) {
    cout << endl;
    for (State k : open) {
        cout << k.Hvalue << " ";
    }
    cout << endl;
}



void aStar( State initial, State goal, void (*hVal) (State&, State) ){

    auto start = high_resolution_clock::now();
  
    vector<State> OPEN, CLOSED;
    State BESTNODE, SUCCESSOR, OLD;
    bool putOnOpen = true;

    int numNodes = 0;
    int nodesExpanded = 0;

    hVal(initial, goal);
    OPEN.push_back(initial);

    while (OPEN.size() != 0) {
        BESTNODE = OPEN.back();
        OPEN.pop_back();
        CLOSED.push_back(BESTNODE);
        if (compareState(BESTNODE, goal)) {
            //PRINT TABLE
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);


            cout << "FOUND GOAL\n";
            cout << "DEPTH (D): " << BESTNODE.nodeDepth;
            cout << "\nNUMBER OF NODES (NG): " << numNodes;
            cout << "\nNodes expanded (NE): " << nodesExpanded;
            cout << "\nb* (NG/D): " << numNodes / BESTNODE.nodeDepth;
            cout << "\nrun time: " << duration.count() <<" microseconds";
            return;
        }
        else {
            numNodes += generatekids(&BESTNODE); // number of nodes
            nodesExpanded++;// nodes expanded
            for (State k : BESTNODE.child) {
                SUCCESSOR = k;
                hVal(SUCCESSOR, goal);
                BESTNODE = SUCCESSOR;
                for (State m : OPEN) {
                    if (compareState(m, SUCCESSOR)) {
                        putOnOpen = false;
                        OLD = m;
                        //BESTNODE.child.erase(std::remove(BESTNODE.child.begin(), BESTNODE.child.end(), SUCCESSOR), BESTNODE.child.end());
                        //removeChild(BESTNODE, OLD);
                        BESTNODE.add_child(OLD);
                        if (OLD.nodeDepth > SUCCESSOR.nodeDepth) {
                            OLD.parent = &BESTNODE;
                            OLD.nodeDepth = BESTNODE.nodeDepth + 1;
                            hVal(OLD, goal);
                            OPEN.push_back(SUCCESSOR);
                            sort(OPEN.begin(), OPEN.end(), greater<State>());
                        }
                    }
                }

                for (State m : CLOSED) {
                    if (compareState(m, SUCCESSOR)) {
                        putOnOpen = false;
                        OLD = m;
                        BESTNODE.add_child(OLD);
                        if (OLD.nodeDepth > SUCCESSOR.nodeDepth) {
                            OLD.parent = &BESTNODE;
                            OLD.nodeDepth = BESTNODE.nodeDepth + 1;
                            hVal(OLD, goal);
                            OPEN.push_back(SUCCESSOR);
                            sort(OPEN.begin(), OPEN.end(), greater<State>());
                            propagateOld(OLD);
                        }
                    }
                }

                if (putOnOpen) {
                    BESTNODE = SUCCESSOR;
                    OPEN.push_back(BESTNODE);
                    sort(OPEN.begin(), OPEN.end(), greater<State>());
                    viewOPEN(OPEN);
                    //BESTNODE.printState();
                    //cin.ignore();
                }
                putOnOpen = true;
            }
        }

    }

    cout << "FAILURE: no solution found\n";
    return;

}
int main() {
    State initial;
    State initalTwo;
    State child;
    State root;
    State goal;
    initial.state[0][0] = 2;
    initial.state[0][1] = 1;
    initial.state[0][2] = 6;
    initial.state[1][0] = 4;
    initial.state[1][1] = 0;
    initial.state[1][2] = 8;
    initial.state[2][0] = 7;
    initial.state[2][1] = 5;
    initial.state[2][2] = 3;
    initial.nodeDepth = 0;
    initial.printState();

    //
    initalTwo.state[0][0] = 2;
    initalTwo.state[0][1] = 8;
    initalTwo.state[0][2] = 3;
    initalTwo.state[1][0] = 1;
    initalTwo.state[1][1] = 6;
    initalTwo.state[1][2] = 4;
    initalTwo.state[2][0] = 0;
    initalTwo.state[2][1] = 7;
    initalTwo.state[2][2] = 5;
    initalTwo.nodeDepth = 0;
    initalTwo.printState();

    

    goal.state[0][0] = 1;
    goal.state[0][1] = 2;
    goal.state[0][2] = 3;
    goal.state[1][0] = 8;
    goal.state[1][1] = 0;
    goal.state[1][2] = 4;
    goal.state[2][0] = 7;
    goal.state[2][1] = 6;
    goal.state[2][2] = 5;

 
    //aStar2(initalTwo, goal, & hValueDistance);
  aStar(initial, goal, & hValueDisplaced);
  aStar(initial, goal, & hValueDistance);
  aStar( initial, goal, &hSvalue);
	aStar( initalTwo, goal, &hSvalue);

}
