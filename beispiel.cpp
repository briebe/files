#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

template<typename T> void print_queue(T q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

struct Compare {
    	vector<double> d;
    	// constructor
    	Compare(vector<double> &dist){ 
    	d = dist; 
    	}
    	bool operator() (unsigned a, unsigned b) {
        	return (d[a] > d[b]) ;
    	}
};

vector<string> split(string str, string delim){
	string vertex;
	vector<string> verteces;
	size_t pos = 0;
	while((pos = str.find(delim))!= string::npos){
		vertex = str.substr(0, pos);
		verteces.push_back(vertex);
		str.erase(0, pos + delim.length());
	}
	verteces.push_back(str);
	
	return verteces;
}

int dijkstra(vector<unsigned> &verteces, vector<vector<double>> &edges, unsigned &s, unsigned &t){
	
	vector<double> d(verteces.size(),numeric_limits<double>::max());
	d[s] = 0;
	vector<double> pi(verteces.size(),numeric_limits<double>::max());
	pi[s] = 0;
	vector<unsigned> S;
	
	Compare cmp(d);
	priority_queue<unsigned, vector<unsigned>, decltype(cmp)> q(cmp);
	
	for (unsigned vertex: verteces){
		q.push(vertex);
	}
	
	while (!q.empty()){
		unsigned u = q.top();
		q.pop();
		S.push_back(u);
		for (unsigned j = 0; j<verteces.size();j++){
			if(edges[u][j]>0){	
					if((d[u]+edges[u][j])<d[j]){
						d[j] = d[u]+edges[u][j];
						pi[j] = u;
						q.push(j);
						}
				}
		}	
	}
	
	unsigned count = t;
	cout << d[t] << endl;
	while(count!=s){
		cout << count << " ";
		count = pi[count];
	}
	cout << s << endl;
	
	return 0;
	}

int main(int argc, char** argv)
{
		
	if(argc<4 or argc>4){
		return 2;
	}
		
	string filename = argv[1];
	unsigned s = strtol(argv[2], NULL, 10);
	unsigned t = strtol(argv[3], NULL, 10);

	/*cout << filename << '\n' << s << '\n' << t << endl;*/


	ifstream file(filename);
	if(!file){return 1;}
	string str;
	
	vector<unsigned> verteces;
	vector<string> vertex;
	string delim = " ";

	while (getline(file, str)){
		
		if(str != "#"){
			vertex = split(str, delim);
			verteces.push_back(stoi(vertex[0]));
		}
		else {					
			break;
		}
	}
	
	if(find(verteces.begin(),verteces.end(),s)==verteces.end() or find(verteces.begin(),verteces.end(),t)==verteces.end()){
		return 2;}
	unsigned nVort = verteces.size();
	vector<vector<double>> edges(nVort, vector<double>(nVort, -1));
	while (getline(file, str)){
		vertex = split(str, delim);
		unsigned i = stoi(vertex[0]);
		unsigned j = stoi(vertex[1]);
		double weight = stod(vertex[2]);
		edges[i][j] = weight;
		
	}
	
	dijkstra(verteces, edges, s, t);

return 0;
}
