#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <cstdlib>

#define INF 0x3f3f3f3f

using namespace std;

typedef pair<float, int> iPair;

int main(int argc, char* argv[]) {

if(argc==0 || argc<4 || argc>4) 
	{
		cout << "Usage: ./program_name tgf_file source target" << endl;
		return 0;
}


	ifstream data;	
	data.open(argv[1],ios_base::in);
	
	string line;
	int counter = 0;
	
	// Jumping over the node names til #
	
	while(getline(data,line)){
		
		//cout << line << "\n";
		
		if(line != "#"){
					
		counter++;
		}
		
		if(line == "#"){
			break;
		}
	}
	
		float** datamatrix= new float*[counter];
		for (int i = 0; i < counter; ++i)
		datamatrix[i] = new float[counter];

	//putting node numbers and values into a matrix

		while(getline(data,line)){
			
			
			string space = " ";
			
			int found = line.find(space);
			int found2 = line.find(space, found+1);
			
			int node1 = stoi(line.substr(0, found));
			int node2 = stoi(line.substr(found+1, found2-found-1));
			float weight = stof(line.substr(found2+1));
		
			
			//cout << node1 << " " << node2 << endl;
			//cout << weight << endl;
			
			
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
		

	// Creates a Min heap
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;


	// Initiate start parameters

	// Creates an vector for distance and previous vertex and fill it with infinite
    vector<iPair> distances(counter, make_pair(INF, INF));

	int src = atoi(argv[2]);

	int target = atoi(argv[3]);

	// Push startVertex into priority queue and set it's distance to 0
    pq.push(make_pair(0, src));
    distances[src].first = 0;

    // Looping till all vertices was selected
    while (!pq.empty())
    {
	      int selectedVertex = pq.top().second;
		  pq.pop();

		  for(int i = 0; i < counter; ++i)
		  {
			  if(datamatrix[selectedVertex][i] != 0 ){
			  float weightOfVertexToCheck = datamatrix[selectedVertex][i];
			  int labelOfVertexToCheck = i;
			if (distances[labelOfVertexToCheck].first > distances[selectedVertex].first + weightOfVertexToCheck)
            {
                // Updating distance
                distances[labelOfVertexToCheck].first = distances[selectedVertex].first + weightOfVertexToCheck;
				// save the previous vertex
				distances[labelOfVertexToCheck].second = selectedVertex;
                pq.push(make_pair(distances[labelOfVertexToCheck].first, labelOfVertexToCheck));
            }
			}
		  }

    }

	// Print length of shortest path
	cout << distances[target].first << endl;

	// Print path
	vector<int> path;
	path.push_back(target);
	// Go throw the chain of previous vertices and add them to the path vector
	while(distances[target].second != INF)
	{
		path.push_back(distances[target].second);
		target = distances[target].second;
	}

	// Print path from source to target
	for (vector<int>::reverse_iterator i = path.rbegin(); i != path.rend(); ++i)
	{
		cout << *i << ' ';
	}

return 0;
}
