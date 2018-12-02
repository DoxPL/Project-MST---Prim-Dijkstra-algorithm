#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;

class Bird
{
	private:
		string name;
		int wingspan, height;
	public:
		void set(string name, int wingspan, int height)
		{
			this->name = name;
			this->wingspan = wingspan;
			this->height = height;
		}
		string get_name()
		{
			return this->name;
		}
		int get_ws()
		{
			return this->wingspan;
		}
		int get_height()
		{
			return this->height;
		}
		void show() 
		{ 
			cout << this->name << "\n" << this->wingspan << "\n" << this->height << "\n\n";
		}
};
const int birds_num = 30;
Bird bird[birds_num];
vector <bool> visited;
vector<int> weight, tree;
vector < vector< pair<int,int> > > edges;
int getWeight(Bird bird[], int from, int to);
void initEdges();
void Prim(int first_vert);
struct s
{
	bool operator() (const int &a, const int &b)
	{
		if (weight[a] < weight[b]) return true;
		if (weight[a] > weight[b]) return false;
		return a<b;
	}
};
set <int, s> heap;

int main()
{
	srand(time(NULL));
	bird[0].set("Perkoz grubodzioby", 62, 34);
	bird[1].set("Alczyk", 48, 19);
	bird[2].set("Ges zbozowa", 160, 75);
	bird[3].set("Ges krotkodzioba", 171, 76);
	bird[4].set("Bernikla rdzawoszyja", 135, 36);
	bird[5].set("Kazarka rdzawa", 145, 67);
	bird[6].set("Swistun zwyczajny", 82, 51);
	bird[7].set("Mandarynka", 75, 49);
	bird[8].set("Krakwa", 95, 58);
	bird[9].set("Helmiatka zwyczajna", 82, 57);
	bird[10].set("Edredon turkan", 105, 63);
	bird[11].set("Birginiak", 75, 50);
	bird[12].set("Perkoz rdzawoszyi", 70, 43);
	bird[13].set("Trzmielojad zwyczajny", 160, 60);
	bird[14].set("Kania czarna", 155, 59);
	bird[15].set("Kobuz", 85, 36);
	bird[16].set("Sokol skalny", 105, 42);
	bird[17].set("Drzemlik", 69, 34);
	bird[18].set("Bielik zwyczajny", 220, 95);
	bird[19].set("Sieweczka mongolska", 60, 20);
	bird[20].set("Sieweczka morska", 45, 20);
	bird[21].set("Mewa cienkodzioba", 115, 45);
	bird[22].set("Mewa siwa", 120, 56);
	bird[23].set("Alka zwyczajna", 67, 48);
	bird[24].set("Nurnik zwyczajny", 58, 38);
	bird[25].set("Syczek zwyczajny", 54, 22);
	bird[26].set("Puchacz zwyczajny", 180, 78);
	bird[27].set("Sowa uszatka", 100, 37);
	bird[28].set("Zimorodek zwyczajny", 26, 16);
	bird[29].set("Dudek", 46, 29);	 
	edges.resize(birds_num);
	cout << "Czy wygenerowac krawedzie: (t/n)";
	char res;
	cin >> res;
	if(res != 't' and res != 'T')
	{
		cout << "Podaj ilosc krawedzi: ";
		int vert_num; 
		cin >> vert_num;
		for(int i=0; i<vert_num; i++)
		{
			int from, to;
			cout << "\n\nKrawedz nr " << i + 1 << ": ";
			cout << "\nWierzcholek pocz¹tkowy: ";
			cin >> from;
			cout << "Wierzcholek koncowy: ";
			cin >> to;
			from--;
			to--;
			int tmp_len = getWeight(bird, from, to);
			edges[from].push_back(make_pair(to, tmp_len));
			edges[to].push_back(make_pair(from, tmp_len));
		}
	}
	else
	{
		initEdges();
	}
	
	Prim(0); 
	int sum = 0; 
	for (int i=1; i<birds_num; i++) 
		sum += weight[i];
	cout << "Suma MST: " << sum << endl;
	for(int i=1; i<birds_num; i++)
	{
		int tmpWeight = getWeight(bird, i, tree[i]);
		cout << bird[i].get_name() << " -- " << bird[tree[i]].get_name() << " (Waga: " << tmpWeight << ")" << endl;
		cout << i + 1 << " -- " << tree[i] + 1 << endl << endl;
	}
	int maxEdge = 0;
	int maxWeight = 0;
	int treeSize = tree.size();
	for(int i=0; i < treeSize; i++)
	{
		int tmpWeight = getWeight(bird, i, tree[i]);
		if(tmpWeight > maxWeight)
		{
			maxWeight = tmpWeight;
			maxEdge = tree[i];
		}
	}
	//grupowanie obiektow przez pominiecie najdluzszej krawedzi
	if(treeSize > 0)
	{
		cout << "Pogrupowane obiekty: " << endl << endl;
		for(int i=1; i < maxEdge; i++)
			cout << bird[i].get_name() << " -- " << bird[tree[i]].get_name() << endl;
		cout << endl << endl;
		for(int i=maxEdge + 1; i < birds_num; i++)
			cout << bird[i].get_name() << " -- " << bird[tree[i]].get_name() << endl;
	}
	return 0;
}

int getWeight(Bird bird[], int from, int to)
{
	int w = 30 * abs(bird[from].get_ws() - bird[to].get_ws()) + 
		abs(bird[from].get_height() - bird[to].get_height());
	return w; 
}

void Prim(int first_vert)
{
	int vertex, vertex2, edgeWeight;
	weight.clear(); 
	weight.resize(birds_num, 9999999); 
	visited.clear(); 
	visited.resize(birds_num,false);
	tree.resize(birds_num);
 
	weight[first_vert] = 0; 
	tree[first_vert]=first_vert; 
	heap.clear(); 
	for (int i=0; i<birds_num; i++) 
		heap.insert(i);
 
 	//usuwanie elementow kopca i doklejanie do drzewa
	while(!heap.empty())
	{
		vertex2 = *(heap.begin()); 
		heap.erase(heap.begin());
		visited[vertex2]=true; 
 
 		//sprawdzamy krawedzie, ktore wychodza z wierzcholka vertex2
		for(int i=0; i<edges[vertex2].size(); i++)
		{
			vertex = edges[vertex2][i].first;
			if (!visited[vertex])
			{
				edgeWeight = edges[vertex2][i].second;
				if (edgeWeight < weight[vertex]) 
				{
					heap.erase(heap.find(vertex));
					weight[vertex] = edgeWeight; 
					heap.insert(vertex);
					tree[vertex] = vertex2;
				}
			}
		}
	}
}

void initEdges()
{
	for(int i=0; i<29; i++)
	{
		int w = getWeight(bird, i, i+1); 
		edges[i].push_back(make_pair(i+1, w)); 
		edges[i+1].push_back(make_pair(i, w));
	}
	for(int i=0; i < birds_num; i++)
	{
		int w = getWeight(bird, i, i+1);
		int destination = rand()%30;
		if(bird[i].get_name() != bird[destination].get_name())
		{
			edges[i].push_back(make_pair(destination, w));
			edges[destination].push_back(make_pair(i, w));
		}
	} 
}
