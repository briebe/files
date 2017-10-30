#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main() {
	ifstream data;
	data.open("dat2.txt",ios_base::in);
	
	string line;
	int counter = 0;
	
	// Jumping over the node names til #
	
	while(getline(data,line)){
		
		cout << line << "\n";
		
		if(line != "#"){
					
		counter++;
		}
		
		if(line == "#"){
			break;
		}
	}
	
		float datamatrix[counter][counter] = {0};

	//putting node numbers and values into a matrix

		while(getline(data,line)){
			
			
			string space = " ";
			
			int found = line.find(space);
			int found2 = line.find(space, found+1);
			
			int node1 = stoi(line.substr(0, found));
			int node2 = stoi(line.substr(found+1, found2-found-1));
			float weight = stof(line.substr(found2+1));
		
			
			cout << node1 << " " << node2 << endl;
			cout << weight << endl;
			
			
			datamatrix[node1][node2] = weight;
			
		};
	
	// Matrix to file(so i could open it with excel and see it)		
		ofstream output("output.txt");
		for (int i=0;i<counter;i++){
			for(int j=0;j<counter;j++){
				output << datamatrix[i][j] << " ";
			}
			output << "\n";
		}
		


return 0;
 }