
#include <iostream>
#include <vector>
using namespace std;

class State{
  public:
    int state [3][3];
    State *parent;
    vector<State*> child;
  State(){};

  void printState(){
    for ( int k=0; k<3; k++ ){
      for (int i= 0; i<3;i++ )
        cout <<state[k][i] <<" ";
      cout << endl;
    }
  }
  void add_child(State *kid){
    child.push_back(kid);
    
  }
  State* get_child(){     
      return child.back();
  };
};


/////////
void generatekids( State *start){
      
      /// find the 0 pos k + i
      int blankRow;
      int blankCol;
      for ( int k=0; k<3; k++ )
        for (int i= 0; i<3;i++ )
          if( start->state[k][i] == 0 ){
            blankRow = k;
            blankCol = i;
          }
      //if +1 or -1 works swap 
      cout <<endl <<"row: "<<blankRow << endl <<"col: "<<blankCol;
      if( blankCol + 1 < 3){
        cout<<"1";

        State *child = new State();
        child->state[0][0] = start->state[0][0];
        child->state[0][1] = start->state[0][1];
        child->state[0][2] = start->state[0][2];
        child->state[1][0] = start->state[1][0];
        child->state[1][1] = start->state[1][1];
        child->state[1][2] = start->state[1][2];
        child->state[2][0] = start->state[2][0];
        child->state[2][1] = start->state[2][1];
        child->state[2][2] = start->state[2][2];
        
        child->state[blankRow][blankCol] = start->state[blankRow][blankCol+1];
        child->state[blankRow][blankCol+1] = 0;
        start->add_child(child);
      }
      if( blankCol - 1 > -1){
        State *child = new State();
         cout<<"2";
        child->state[0][0] = start->state[0][0];
        child->state[0][1] = start->state[0][1];
        child->state[0][2] = start->state[0][2];
        child->state[1][0] = start->state[1][0];
        child->state[1][1] = start->state[1][1];
        child->state[1][2] = start->state[1][2];
        child->state[2][0] = start->state[2][0];
        child->state[2][1] = start->state[2][1];
        child->state[2][2] = start->state[2][2];
        
        child->state[blankRow][blankCol] = start->state[blankRow][blankCol-1];
        child->state[blankRow][blankCol-1] = 0;
        start->add_child(child);

      }
      if( blankRow + 1 < 3){
        State *child = new State();
         cout<<"3";
        child->state[0][0] = start->state[0][0];
        child->state[0][1] = start->state[0][1];
        child->state[0][2] = start->state[0][2];
        child->state[1][0] = start->state[1][0];
        child->state[1][1] = start->state[1][1];
        child->state[1][2] = start->state[1][2];
        child->state[2][0] = start->state[2][0];
        child->state[2][1] = start->state[2][1];
        child->state[2][2] = start->state[2][2];
        
        child->state[blankRow][blankCol] = start->state[blankRow+1][blankCol];
        child->state[blankRow][blankCol+1] = 0;
        start->add_child(child);
        

      }
      if( blankRow - 1 > -1){
        State *child = new State();
         cout<<"4";
        child->state[0][0] = start->state[0][0];
        child->state[0][1] = start->state[0][1];
        child->state[0][2] = start->state[0][2];
        child->state[1][0] = start->state[1][0];
        child->state[1][1] = start->state[1][1];
        child->state[1][2] = start->state[1][2];
        child->state[2][0] = start->state[2][0];
        child->state[2][1] = start->state[2][1];
        child->state[2][2] = start->state[2][2];
        
        child->state[blankRow][blankCol] = start->state[blankRow][blankCol+1];
        child->state[blankRow][blankCol+1] = 0;
        start->add_child(child);

      }


      
     // start->add_child(child);
}



int main(){
      State test;
      State child;
      State *root;
      test.state[0][0] = 2;
      test.state[0][1] = 8;
      test.state[0][2] = 3;
      test.state[1][0] = 1;
      test.state[1][1] = 6;
      test.state[1][2] = 4;
      test.state[2][0] = 0;
      test.state[2][1] = 7;
      test.state[2][2] = 5;
      test.printState();
      //test.newStates();
      generatekids(&test);
     
     // test.add_child(&child);

      //test.get_child().printState();
      root =test.get_child();
      cout<<endl;
      root->printState();
      
      root =test.get_child();
      cout<<endl;
      root->printState();
      



      

}



