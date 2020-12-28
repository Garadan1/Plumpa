#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<ostream>
#include<vector>
#include<algorithm>
#include<iomanip>

struct Member
{
	std::string name;
	size_t msgcount;
	size_t nwordcount;

};
bool comparebynum(const Member& a, const Member& b)
{
	return a.msgcount < b.msgcount;

};
bool comparebynword(const Member& a, const Member& b)
{
	return a.nwordcount < b.nwordcount;
}
class Plumpa
{
public:


	
	std::ifstream inFile;
	std::vector<Member>MemberData; //can't call a method on a member variable inside your class declaration, eg size
	std::ofstream DataFile;
	

	Plumpa();
	
	
	void msgCount();
	void nWordCount();
	void printData();
	void outData();
	void Sort();
	void nWordSort();
};
Plumpa::Plumpa()
{
	MemberData.resize(18);	//have to do this here
	
	MemberData[0].name = "Carson:";	//this is really long but the only way I could think of. F
	MemberData[1].name = "Karl:";
	MemberData[2].name = "Nick Remelius:";
	MemberData[3].name = "Noah:";
	MemberData[4].name = "Arob:";
	MemberData[4].name = "Brad:";
	MemberData[5].name = "Charles:";
	MemberData[6].name = "Conor:";
	MemberData[7].name = "Daniel Garan:";
	MemberData[8].name = "David:";
	MemberData[9].name = "E:";
	MemberData[10].name = "Evan:";
	MemberData[11].name = "Lawson:";
	MemberData[12].name = "Lucas:";
	MemberData[13].name = "Mathieu Fikany:";
	MemberData[14].name = "Maverick:";
	MemberData[15].name = "Nathan:";
	MemberData[16].name = "Peter:";
	MemberData[17].name = "Teddy:";

	for (int i = 0; i < MemberData.size(); i++)
	{
		MemberData[i].msgcount = 0;		
		MemberData[i].nwordcount = 0;   //just being really careful here

	}

	inFile.open("fuckyeah.txt"); //whatever the filename is. 
	

	DataFile.open("Plumpa Data.txt");
}

void Plumpa::msgCount()
{
	std::string line;

	if (inFile.fail())
		std::cout << "File not found" << std::endl; //idk what best place for this is
	
	while (inFile.good())
	{
		for (int i = 0; i < MemberData.size(); i++)
		{
			getline(inFile, line);
			for (int j = 0; j < MemberData.size(); j++)
			{
				if (line.find(MemberData[j].name) != std::string::npos)//who the fuck knows if this works
					MemberData[j].msgcount++;


			}
		}
	}
	inFile.clear();
	inFile.seekg(0, std::ios::beg); //reset to beginning of file
	
	Sort();
}

void Plumpa::nWordCount()
{
	std::string line;

	while (inFile.good())
	{
		for (int i = 0; i < MemberData.size(); i++)
		{
			getline(inFile, line);
			for (int j = 0; j < MemberData.size(); j++)
			{
				if (line.find(MemberData[j].name) != std::string::npos)
				{
					if (line.find("nword") != std::string::npos || line.find("nword") != std::string::npos || line.find("nword") != std::string::npos || line.find("nword") != std::string::npos)
						MemberData[j].nwordcount++;
				}
			}
		}
	}
	inFile.clear();
	inFile.seekg(0, std::ios::beg); //reset to beginning of file
	
}
void Plumpa::Sort()
{
	std::sort(MemberData.begin(), MemberData.end(), comparebynum); //sorts by msg count, overload for n word
}
void Plumpa::nWordSort()
{
	std::sort(MemberData.begin(), MemberData.end(), comparebynword);
}
void Plumpa::printData()
{
	
	std::cout << std::left << std::setw(20) <<"Name"<<"Messages Sent"<<std::setw(20)<< std::right <<"N words used" << std::endl;
	
	for (int i = 0; i < MemberData.size(); i++)
	{
		std::cout << std::left << std::setw(20) <<MemberData[i].name  << MemberData[i].msgcount << std::setw(20)<<std::right<<MemberData[i].nwordcount<< std::endl;
	}
}
void Plumpa::outData()//text file
{

	DataFile << std::left << std::setw(20) << "Name" << "Messages Sent" << std::setw(20) << std::right << "N words used" << std::endl;

	for (int i = 0; i < MemberData.size(); i++)
	{
		DataFile << std::left << std::setw(20) << MemberData[i].name << MemberData[i].msgcount << std::setw(20) << std::right << MemberData[i].nwordcount << std::endl;
	}
}