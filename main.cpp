#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>


using namespace std;

void check_arguments(int argc, char* argv[]) {
  string usage_instructions = "Usage instructions: ";
  usage_instructions += argv[0];
  usage_instructions += " path/to/input.txt output.txt";

  bool has_valid_args = false;

  // make sure the user has provided input and output files
  if (argc == 1) {
    cerr << usage_instructions << endl;
  } else if (argc == 2) {
    cerr << "Please include an output file.\n" << usage_instructions << endl;
  } else if (argc == 3) {
    has_valid_args = true;
  } else if (argc > 3) {
    cerr << "Too many arguments.\n" << usage_instructions << endl;
  }

  if (!has_valid_args) {
    exit(EXIT_FAILURE);
  }
}

void check_files(ifstream& in_file, string& in_name,
                 ofstream& out_file, string& out_name) {
  if (!in_file.is_open()) {
    cerr << "Cannot open input file: " << in_name << endl;
    exit(EXIT_FAILURE);
  }

  if (!out_file.is_open()) {
    cerr << "Cannot open output file: " << out_name << endl;
    exit(EXIT_FAILURE);
  }
}


void search(vector<int> init, vector<int> exit, vector<vector<char>> grid){
  //go up, go left, go down, go right
  vector<vector<int>> move = {{-1,0},{0,-1},{1,0},{0,1}}; 

  //create closed list of available cells
  //0 still open, 1 be closed
  vector<vector<int>> closed;
  closed.resize(7);
  for (int m=0; m<7; m++){
    closed[m].resize(7);
  }
  closed[init[0]][init[1]] = 1;

  int x = init[0];
  int y = init[1];
  int g = 0;
  
  vector<int> temp;
  vector<int> t2;
  temp.push_back(g);
  temp.push_back(x);
  temp.push_back(y);
  
  vector<vector<int>> open;  // create open expained cell list
  
  open.push_back(temp);
  //cout<<open.size()<<endl;
  //cout<<"start at: "<<open[0][0]<<",("<<open[0][1]<<","<<open[0][2]<<")"<<endl;
  
  bool found = false; //change it when search completed.
  bool resign = false; // flag it when exit is not exist.
  vector<int> next;

  while (found==false && resign ==false){
    if (open.size()==0){
      resign = true;
      cout << "fail"<<endl;
    }else{
      next = open[0];
      g = next[0];
      x = next[1];
      y = next[2];
      
      open.erase(open.begin());
      cout<<"open cell:("<<g<<","<<x<<","<<y<<")"<<endl;

      if(x==exit[0] && y==exit[1]){
        found = true;
        cout<<"search success"<<endl;
      }else{
        //expain the open list by trying 4 direction moves. 
        for(int n=0; n<move.size(); n++){
	  int x2 = x + move[n][0];
	  int y2 = y + move[n][1];
          //cout<<"x2, "<<x2<< ", y2, "<<y2<<endl;
	    if(0<= x2< 7 && 0<= y2<7){
	      //cout<<"x2, "<<x2<< ", y2, "<<y2<<", ";
	      //cout<<closed[x2][y2]<<", ";
	      //cout<<grid[x2][y2]<<endl;
	      if((closed[x2][y2]==0) && (grid[x2][y2]=='-')){
		  int g2 = g+1;
		  //cout <<"g2 "<< g2<<endl;
		  t2.clear();
		  t2.push_back(g2);
		  t2.push_back(x2);
		  t2.push_back(y2);
 		  open.push_back(t2);
                  //cout<<"open cell:("<<g2<<","<<x2<<","<<y2<<")"<<endl;
		  closed[x2][y2]= 1; //don't touch this cell again
		  grid[x2][y2]= 'x'; //mark the path
	       }
	    }
         }
      }
    } 
  }
  
}


int main(int argc, char* argv[]){

  check_arguments(argc, argv);

  string in_file_name_ = argv[1];
  ifstream in_file_(in_file_name_.c_str(), ifstream::in);

  string out_file_name_ = argv[2];
  ofstream out_file_(out_file_name_.c_str(), ofstream::out);

  check_files(in_file_, in_file_name_, out_file_, out_file_name_);
  
  string line;
  string file_contents;
  int player;
    
  vector<string> size;
  size.resize(2);

  vector<string> cell(7);

  vector<int> exit;  //Exit position, goal position
  exit.resize(2);

  vector<vector<char>> maze;

  vector<int> init;  //Start position
  init.resize(2);

  //int g;  // g-value 
  int count = 0;
  int i;
  // read in the file
  while(getline(in_file_, line)){
  
    istringstream iss(line);
    if (count==0){
      iss >> player;
      //cout <<player<<endl;
    }else if (count==1){
      iss >>size[0]>>size[1];
      //cout<<size[0]<<","<<size[1];
    }else if(1<count && count<9){
      i=count-2;
      iss >>cell[i][0]>>cell[i][1]>>cell[i][2]>>cell[i][3]>>cell[i][4]>>cell[i][5]>>cell[i][6];
    }else if(count ==9){
      iss >>exit[0]>>exit[1];
    }else if(count ==10){
      iss >>init[0]>>init[1];
    }
    count +=1;

  }
  
  cout<<"player id:"<<player<<endl;
  cout<<"maze size:"<<size[0]<<","<<size[1]<<endl;
  cout<<"start position:"<<init[0]<<","<<init[1]<<endl;
  cout<<"exit  position:"<<exit[0]<<","<<exit[1]<<endl;
  vector<char> t3;
  for(int j=0;j<7;j++){
    cout<<cell[j][0]<<cell[j][1]<<cell[j][2]<<cell[j][3]<<cell[j][4]<<cell[j][5]<<cell[j][6]<<endl;
    t3.clear();
    t3.push_back(cell[j][0]);
    t3.push_back(cell[j][1]);
    t3.push_back(cell[j][2]);
    t3.push_back(cell[j][3]);
    t3.push_back(cell[j][4]);
    t3.push_back(cell[j][5]);
    t3.push_back(cell[j][6]);
    maze.push_back(t3);
  }



  search(init, exit, maze);

  return 0;
}
