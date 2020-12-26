#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
#include<algorithm>
#include<iomanip>
#include<vector>
using namespace std;

struct member {
	string name;
	int count;

	void print() {
		cout << left << setw(20) << this->name << this->count << endl;
	}
};
bool comparebynum(const member &a, const member &b)
{
	return a.count < b.count;

}
int main()
{
	vector<string> members = { "Carson:","‎‪no data‬","Karl:","Nick Remelius:","Noah:","Arob:","Brad:","Charles:",
		"Conor:","Daniel Garan:","David:","E:","Evan:","Lawson:","Lucas:","Mathieu Fikany:","Maverick:","Nathan:","Peter:","Teddy:" };

	vector<int> memberCount;
	memberCount.resize(20);
	for (int i = 0; i < 20; i++)
		memberCount[i] = 0;

	ifstream inFile;
	string line;

	inFile.open("fuckyeah.txt");
	//HUNDERED THOUSANDS 
	while (inFile.good())
	{
		

		for (int i = 0; i < 20; i++)
		{
			getline(inFile, line);
			for (int j = 0; j < 20; j++)
			{
				if (line.find(members[j]) != string::npos)//who the fuck knows if this works
					memberCount[j]++;
				
			}
		}
	}

	
	vector<member>chatmembers;
	chatmembers.resize(20);

	for (int i = 0; i < 20; i++)
	{
		chatmembers[i].count = memberCount[i];
		chatmembers[i].name = members[i];
	}
	

	std::sort(chatmembers.begin(), chatmembers.end(),comparebynum);


	for (int i = 0; i < 20; i++)
	{
		chatmembers[i].print();
	}
	
	
	



}

