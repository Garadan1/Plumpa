#pragma once

class Plumpa {
// Structs

	enum Plumpas{ NIL, Lawson, Nick, Peter, Dan, Ethan, Nathan, Conor, Conor2, Noah, Karl, Matt, Teddy, Brad, Evan, David, Carson, Alex, Charlie, Maverick, Lucas };
	enum nonPlumpas{ Dani }; // Add 5 unknown numbers 
	std::vector<std::string> chatNames = { "NULL", "Lawson W", "Nick Remelius", "Peter Hummer", "Daniel G", "Ethan Aiuto", "Nathan R", "Conor Garvey", "Conor G", "Noah Word", "Karl Krieger", "Fik", "Teddy", "Brad Geist", "Evan Nguyen", "David Swegles", "Carson Dara", "‪+1 (313) 300‑1397‬", "charlie calc", "Maverick Taavola", "Lucas Biernat" };

	struct Member { // Aligned!
		Plumpas name = NIL;
		size_t numMessages = 0;
	};

	struct Message { // Aligned!
		tm time; // (tm struct from ctime)
		Member sender;
		std::string message; // This is probably not efficient
	};

// Member variables
	size_t totalMessages = 0; // Default 0
	size_t totalNonMessages = 0;
	size_t totalPhotos = 0;
	std::vector<Message> messages;
	std::vector<Member> members;
	std::vector<Message> nonMessages;
	std::vector<Message> photos;
	std::vector<Message> specialMessages;

	std::vector<std::string> tempMembers;

// Member functions

	// Gets date and timestamp from message
	tm getMessageTime(std::string& raw);

	// Reads in chat history from cin, sanitizes it, and stores for analysis
	// TODO: Create an overloaded version with string parameter
	void readInput();

	// TODO: Implement
	void readInput(std::string filename);
	
	// This is kind of lazy, and not meant to be permanent
	// More of a debugging tool
	void analyzeTime();

	// Prints all lines from chat.txt matching "Photo/Video omitted"
	void printPhotos();

	// Prints all lines from chat.txt deemed as "not a message"
	void printNonMessages();

	// Prints all members
	// TODO: Change to actual member struct and print more info
	void printMembers();

public:
	// Constructor
	Plumpa(); 
};