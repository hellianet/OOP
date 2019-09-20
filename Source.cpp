#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

bool pairCompare(pair<int, string> a, pair<int, string> b)
{
	return a.first > b.first;
}

class WordCount
{
public:
	WordCount(vector<string> arr)
	{
		int count = arr.size();

		for (int i = 0; i < count; i++)
		{
			string str = arr[i];
			int count_in_str = str.size();
			string word = "";
			for (int k = 0; k < count_in_str; k++)
			{
				if (isalnum((char)str[k]))
				{
					word += str[k];
				}
				else
				{
					if (word != "")
					{
						words[word]++;
						word = "";
						count_el_file_++;
					}
				}
			}
			if (word != "")
			{
				words[word]++;
				count_el_file_++;
			}


		}
	}

	~WordCount() {}

	vector<pair<int, string> > return_sort_vector()
	{
		map<string, int>::iterator cur;
		vector<pair<int, string> > pairs;
		for (cur = words.begin(); cur != words.end(); cur++)
		{
			pair<int, string> p;
			p.first = cur->second;
			p.second = cur->first;
			pairs.push_back(p);
		}
		sort(pairs.begin(), pairs.end(), pairCompare);
		return pairs;
	}

	int get_all_el()
	{
		return count_el_file_;
	}

private:
	map<string,int> words;
	int count_el_file_;
	
};

class Reader
{
public:
	Reader(string name)
	{
		path = name;		
	    file.open(name);
	}
	
	~Reader()
	{
		file.close();
	}

	string read()
	{
		string str = "";
		if (file.is_open() & !file.eof())
		{
			getline(file, str);
		}
		return str;
	}

private:
	string path;
	ifstream file;
};

class Writer
{
public:
	Writer(string name)
	{
		path = name;
		outfile.open(name);
	}

	~Writer()
	{
		outfile.close();
	}

	void write(vector<pair<int,string> > arr, int count)
	{
		if (outfile.is_open())
		{ 
			outfile << "Words, Count, Frequency" << endl; 
			for(int i = 0; i < arr.size(); i++)
			{
				outfile << arr[i].second<<", "<< arr[i].first <<", " << (arr[i].first / float(count)) *100 << "%" << endl;

			}
		}
		
	}

private:
	string path;
	ofstream outfile;	
};

int main()
{
	Reader a("doc.txt");
	string x = a.read();
	vector<string> strings;
	while (x != "")
	{
		strings.push_back(x);
		x = a.read();
	}
	WordCount wc(strings);
	int count = wc.get_all_el();
	vector<pair<int, string> > pairs = wc.return_sort_vector();
	Writer wr("out.csv");
	wr.write(pairs, count);
    return 0;
}