#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <cstdlib>

#define INF 0x3f3f3f3f

using namespace std;

typedef pair<int, int> iPair;

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
		

	 //Creates a Min heap
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;


	 //Initiate start parameters

	 //Creates an vector for all distances and fill it with infinite
    vector<int> distances(counter, INF);

	int src = atoi(argv[2]);

	int target = atoi(argv[3]);

	 //Push startVertex into priority queue and set it's distance to 0
    pq.push(make_pair(0, src));
    distances[src] = 0;

    /* Looping till all vertices was selected */
    while (!pq.empty())
    {
	      int selectedVertex = pq.top().second;
		  pq.pop();

		  for(int i = 0; i < counter; ++i)
		  {
			  if(datamatrix[selectedVertex][i] != 0 ){
			  int weightOfVertexToCheck = datamatrix[selectedVertex][i];
			  int labelOfVertexToCheck = i;
			   printf("selectedVertex: %d , labelOfVertexToCheck: %d\n",selectedVertex, labelOfVertexToCheck);
			   printf("distances[labelOfVertexToCheck]: %d > distances[selectedVertex]: %d + weightOfVertexToCheck: %d\n",distances[labelOfVertexToCheck], distances[selectedVertex], weightOfVertexToCheck);
			if (distances[labelOfVertexToCheck] > distances[selectedVertex] + weightOfVertexToCheck)
            {
				printf("\nUpdate\n\n");
                 //Updating distance
                distances[labelOfVertexToCheck] = distances[selectedVertex] + weightOfVertexToCheck;
                pq.push(make_pair(distances[labelOfVertexToCheck], labelOfVertexToCheck));
            }
			}
		  }

    }
 
     //Print shortest distances
    /*printf("Vertex || Distance from source\n");
    for (int i = 0; i < counter; ++i)
        printf("%d || %d\n", i, distances[i]);
        */
        
        printf("\n Distance from source to target: %d\n",distances[target]);

return 0;
}