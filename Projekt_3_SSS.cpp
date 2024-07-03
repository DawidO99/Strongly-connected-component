#include <iostream>
#include <vector>
#include <fstream>
const size_t SIZE = 10000;

std::vector<int> graph[SIZE];
std::vector<int> transposed_graph[SIZE];
std::vector<int> SSS[SIZE];

int dfs_visited[SIZE];
int SSS_visited[SIZE];
int post_order[SIZE];

int nr = 1;
int ile_SSS = 0;

void dfs(int vertex)
{
	dfs_visited[vertex] = 1;
	while (!graph[vertex].empty())
	{
		int z = graph[vertex].back();
		graph[vertex].pop_back();
		if (!dfs_visited[z])
		{
			dfs_visited[z] = 1;
			dfs(z);
		}
	}
	post_order[nr]=vertex;
	nr++;
}

void transposed_dfs(int vertex)
{
	SSS_visited[vertex] = 1;
	while (!transposed_graph[vertex].empty())
	{
		int z = transposed_graph[vertex].back();
		transposed_graph[vertex].pop_back();
		if (!SSS_visited[z])
		{
			SSS[ile_SSS].push_back(z);
			SSS_visited[z] = 1;
			transposed_dfs(z);
		}
	}
}

inline void menu()
{
	std::cout << "1. Wczytaj dane z pliku" << std::endl;
	std::cout << "2. Podaj wlasne dane" << std::endl;
}


int main()
{
	std::cout << "Algorytm wyznaczania silnie spojnych skladowych w grafie skierowanym" << std::endl;
	std::cout << "Autor : Dawid Ochman" << std::endl;
	std::cout << "Informatyka, I Rok, II Semestr" << std::endl;
	menu();
	std::ofstream outfile("result.txt");
	int n, vertex, edge;
	std::cin >> n;
	switch (n)
	{
		case 1:
		{
			std::ifstream infile("test.txt");
			infile >> vertex >> edge;
			outfile << vertex << " " << edge << std::endl;
			for (int i = 0; i < edge; i++)
			{
				int a, b; //dwa wierzcholki miedzy ktorymi mamy krawedz
				infile >> a >> b;
				graph[a].push_back(b); //graf
				transposed_graph[b].push_back(a); //odwrocony graf
				outfile << a << " " << b << std::endl;
			}
			infile.close();
			break;
		}
		case 2:
		{
			std::cout << "Podaj liczbe wierzcholkow i krawedzi grafu : " << std::endl;
			std::cin >> vertex >> edge;
			outfile << vertex << " " << edge << std::endl;
			for (int i = 0; i < edge; i++)
			{
				int a, b; //dwa wierzcholki miedzy ktorymi mamy krawedz
				std::cin >> a >> b;
				graph[a].push_back(b); //graf
				transposed_graph[b].push_back(a); //odwrocony graf
				outfile << a << " " << b << std::endl;
			}
			break;
		}
		default:
		{
			std::cout << "Podano bledna opcje. Koncze dzialanie programu..." << std::endl;
			exit(0);
		}
	}
	
	for (int i = 1; i <= vertex; i++)
		if (!dfs_visited[i]) dfs(i);

	for (int i = vertex; i >= 1; i--)
		if (!SSS_visited[post_order[i]])
		{
			transposed_dfs(post_order[i]);
			SSS[ile_SSS].push_back(post_order[i]);
			ile_SSS++;
		}

	outfile << ile_SSS << std::endl;
	for (int i = 0; i < ile_SSS; i++)
	{
		for (int v : SSS[i])
			outfile << v << " ";
		outfile << std::endl;
	}
	outfile.close();

	std::cout << "Liczba silnie spojnych skladowych : " << ile_SSS << std::endl;
	for (int i = 0; i < ile_SSS; i++)
	{
		std::cout << i+1 << ". ";
		while (!SSS[i].empty())
		{
			std::cout << SSS[i].back() << " ";
			SSS[i].pop_back();
		}
		std::cout << std::endl;
	}
}