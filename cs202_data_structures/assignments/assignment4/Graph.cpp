#ifndef GRAPH_CPP
#define GRAPH_CPP
#include "Graph.h"



Graph::Graph(char* filename)
{
	ifstream in_file;
	in_file.open(filename);
	
	if (in_file.fail())
	{
		cout << "Error reading file!\n";
		exit(1);
	}
	
	string crap, temp;
	in_file >> crap;
	in_file >> temp;
	
	while (temp != "ARCS")
	{
		float temp_x, temp_y;
		in_file >> temp_x;
		in_file >> temp_y;
		
		node *temp_node = new node(temp, temp_x, temp_y);
	
		cities.push_back(temp_node);
		
		in_file >> temp;
	}
	
	while (!in_file.eof())
	{
		string temp_origin, temp_dest;
		float temp_weight;
		
		in_file >> temp_origin;
		in_file >> temp_dest;
		in_file >> temp_weight;
		
		node* node_origin = getCity(temp_origin);
		node* node_dest = getCity(temp_dest);
		
		edge temp_edge_ori(node_origin, node_dest, temp_weight);
		
		node_origin->edges.push_back(temp_edge_ori);
		
		arcs.push_back(temp_edge_ori);
		
		edge temp_edge_dst(node_dest, node_origin, temp_weight);
		node_dest->edges.push_back(temp_edge_dst);
	}

}

node* Graph::getCity(string s)
{
	for (int i = 0; i < cities.size(); i++)
	{
		if (cities[i]->name == s)
		{
			return cities[i];
		}
	}
	
	return NULL;
}

vector<node*> Graph::Kruskal()
{
	
	pqueue<edge> p_edges(arcs);
	
	vector<edge> edges_mst;
	
	tree nodes;
	
	vector<set<node*> >cloud;
	for (int i = 0; i < cities.size(); i++)
	{
		set<node*> temp;
		temp.insert(cities[i]);
		cloud.push_back(temp);
	}
	
	while (p_edges.numE > 0)
	{
		edge min_edge = p_edges.ExtractMin();
		
		int origin_index = find_node(cloud, min_edge.Origin);
		int dest_index = find_node(cloud, min_edge.Dest);
		
		if (origin_index != dest_index)
		{
			edges_mst.push_back(min_edge);
			
			cloud[origin_index].insert(cloud[dest_index].begin(), cloud[dest_index].end());
			cloud.erase(cloud.begin() + dest_index);
		}
	}
	
	for (int i = 0; i < edges_mst.size(); i++)
	{	
		cout << edges_mst[i].Origin->name << " " << edges_mst[i].Dest->name << " " << edges_mst[i].weight << endl;
	}
	
	vector<node*> result;
	return result;
}

int Graph::find_node(vector<set<node*> >cloud, node* temp)
{
	for (int i = 0; i < cloud.size(); i++)
	{
		if (cloud[i].find(temp) != cloud[i].end())
		{
			return i;	
		}	
	}	
	
	return -1;
}

void Graph::display(node* temp)
{	
	dfs(temp);	
}

void Graph::dfs(node* temp)
{	
	for (int i = 0; i < temp->edges.size(); i++)
	{
		if (temp->edges[i].Dest->visit != 1)
		{
			temp->edges[i].Dest->visit = 1;
			dfs(temp->edges[i].Dest);
			cout << temp->name << endl;
		}
	}
}

vector<string> Graph::Dijkstra(string u, string v, float &)
{
	// initializing all the distances to infinity
	for (int i = 0; i < cities.size(); i++)
	{
		cities[i]->dist = 10000;
	}
	
	node *source = getCity(u);
	node *dest = getCity(v);
	source->dist = 0;
	
	//pqueue<node*> p_nodes(cities);
	vector<node*> nodes;
	for (int i = 0; i < cities.size(); i++)
	{
		nodes.push_back(cities[i]);
	}
	
	while (nodes.size() > 0)
	{
		//node* temp = p_nodes.ExtractMin();
		int min_index = find_min(nodes);
		node *temp = nodes[min_index];
		
		nodes.erase(nodes.begin()+min_index);
		
		temp->visit = 1;
		for (int i = 0; i < temp->edges.size(); i++)
		{
			if (!temp->edges[i].Dest->visit)
			{
				float new_dist = temp->dist + temp->edges[i].weight;
				
				if (new_dist < temp->edges[i].Dest->dist)
				{
					temp->edges[i].Dest->dist = new_dist;
					temp->edges[i].Dest->prev = temp;
					//p_nodes.DecreaseKey(temp->edges[i].Dest);
				}
			}	
		}
		
	}
	
	vector<string> result;
	node *ptr = dest;
	while (ptr != source)
	{
		result.push_back(ptr->name);
		ptr = ptr->prev;
	}
	result.push_back(source->name);
	
	
	reverse(result.begin(), result.end());
	
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i] << " ";	
	}
	
	return result;
	
}

int Graph::find_min(vector <node*> temp)
{
	float min = temp[0]->dist;
	int min_index = 0;
	
	for (int i = 1; i < temp.size(); i++)
	{
		if (temp[i]->dist < min)
		{
			min = temp[i]->dist;
			min_index = i; 
		}
	}
	
	return min_index;
}

vector< set<string> > Graph::connectedComponents()
{
	
}

		
bool operator < (edge a, edge b)
{
	if (a.weight < b.weight)
	{
		return true;
	}
	
	return false;
}

bool operator == (edge a, edge b)
{
	if (a.weight == b.weight)
	{
		return true;
	}
	
	return false;
}

bool operator > (edge a, edge b)
{
	if (a.weight > b.weight)
	{
		return true;
	}
	
	return false;
}

bool operator < (node a, node b)
{
	if (a.dist < b.dist)
	{
		return true;
	}
	
	return false;
}

bool operator == (node a, node b)
{
	if (a.dist == b.dist)
	{
		return true;
	}
	
	return false;
}

bool operator > (node a, node b)
{
	if (a.dist > b.dist)
	{
		return true;
	}
	
	return false;
}



#endif
