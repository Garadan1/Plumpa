#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime> // For message timestamps
#include "plumpa.h"

#define DEBUG // For extensive debugging
#define NUM_MESSAGES 350000 // Actual current num_messages = 304,791

using namespace std;

tm Plumpa::getMessageTime(std::string& raw) {

	// Month/Day/Year

	// Combine these lines once data is formatted properly (safe)
	// This has to be int because of ctime, kinda stupid imo
	int month = stoi(raw.substr(1, raw.find_first_of('/')));

#ifdef DEBUG
	if (month < 1 || month > 12) {
		std::cerr << "Invalid month " << month
			<< " from (raw) message: \n" << raw << "\n";
		exit(1);
	}
#endif

	// Cut out month
	raw = raw.substr(raw.find_first_of('/') + 1, raw.size());

	int day = stoi(raw.substr(0, raw.find_first_of('/')));

#ifdef DEBUG
	if (day < 1 || day > 31) {
		std::cerr << "Invalid day " << day
			<< " from (raw) message: \n" << raw << "\n";
		exit(1);
	}
#endif

	// Cut out day
	raw = raw.substr(raw.find_first_of('/') + 1, raw.size());

	int year = stoi(raw.substr(0, raw.find_first_of(',')));

#ifdef DEBUG
	if (year < 17 || year > 22) { // Will have to change in 2023!
		std::cerr << "Invalid year " << year
			<< " from (raw) message: \n" << raw << "\n";
		exit(1);
	}
#endif

	// Hour/Min/Sec

	int hour = stoi(raw.substr(raw.find_first_of(',') + 2, raw.find_first_of(':')));
#ifdef DEBUG
	if (hour < 1 || hour > 12) {
		std::cerr << "Invalid hour " << year
			<< " from (raw) message: \n" << raw << "\n";
		exit(1);
	}
#endif

	// Trim out hour
	raw = raw.substr(raw.find_first_of(':') + 1, raw.size());

	// Since min and sec are 0 padded, this part is easier
	int min = stoi(raw.substr(0, 2));
#ifdef DEBUG
	if (min < 0 || min > 59) {
		std::cerr << "Invalid minute " << year
			<< " from (raw) message: \n" << raw << "\n";
		exit(1);
	}
#endif

	int sec = stoi(raw.substr(3, 5));
#ifdef DEBUG
	if (sec < 0 || sec > 59) {
		std::cerr << "Invalid second " << year
			<< " from (raw) message: \n" << raw << "\n";
		exit(1);
	}
#endif

	// Trim out min, sec, trailing space
	raw = raw.substr(6, raw.size());

	// Convert to 24-hour time
	// Can remove the second check once confident
	if (raw[0] == 'P' && raw[1] == 'M') {
		hour += 12;
		if (hour == 24) hour = 0; // 12 AM to 0
	}
	else if (raw[0] == 'A' && raw[1] == 'M')
		; // Do nothing
	else {
		std::cerr << "AM or PM not matched in raw message:\n" <<
			raw << "\n";
		exit(1);
	}

	// Trim everything up to sender name
	raw = raw.substr(4, raw.size());

	// Assign values to time struct
	// Note that the "year" does not follow the C++ standard
	// It's fine for our purposes.
	tm temp;
	temp.tm_mday = day;
	temp.tm_mon = month;
	temp.tm_year = year;
	temp.tm_sec = sec;
	temp.tm_min = min;
	temp.tm_hour = hour;
	return temp;
}

void Plumpa::readInput() {
	messages.reserve(NUM_MESSAGES); // Find a better way to do this
	photos.reserve(NUM_MESSAGES / 10); // Approximations...
	nonMessages.reserve(NUM_MESSAGES / 100);
	specialMessages.reserve(NUM_MESSAGES / 1000);
	std::string raw;
	// Ignore messages not starting with [ for now
	// TODO: Add lines not starting with [ to previous message
	while (getline(std::cin, raw)) {
		// This is not a safe check!! TODO: Fix the isdigit part!
		if (raw[0] == '[' && isdigit(raw[1])) {
			Message temp;

			temp.time = getMessageTime(raw);

			// Raw trimmed down by getMessageTime(), should now be able to grab sender and message
			// All messages should be in the form <sender>: <message>, so look up until first :
			std::string tempName = raw.substr(0, raw.find_first_of(':'));
			if (std::find(chatNames.begin(), chatNames.end(), tempName) == tempMembers.end()) {
				std::cout << "Member " << tempName << " not found yet, pushing to tempMembers\n";
			}

			// TODO: Finish implementing - Sender (Member), message


			messages.push_back(temp);
			++totalMessages;
		}				// This inefficiency is intentional to avoid segfault
		else if (raw[0] == 'â' && raw[1] == '€' && raw[2] == 'Ž') { // Capture images and videos
			++totalPhotos;
			Message temp;

			// Get time, sender
			// Grab photo/video boolean

			temp.message = raw;
			photos.push_back(temp);
		}
		else {
			++totalNonMessages;
			Message temp;

			// Find out how to assign to last line

			temp.message = raw;
			nonMessages.push_back(temp);
		}
	} // while()
}

void Plumpa::readInput(std::string filename) {
	std::cout << "Need to implement this\n";
}

void Plumpa::analyzeTime() {
	std::cout << "\n\nTotal number of messages: " << totalMessages << "\n";
	std::cout << "Total number of non-messages: " << totalNonMessages << "\n";
	std::cout << "Total number of photos: " << totalPhotos << "\n";

	// +1 because 1-indexed
	std::vector<int> day(32, 0), month(13, 0), year(23, 0);
	// Not +1, 0-indexed
	std::vector<int> hour(24, 0), minute(60, 0), second(60, 0);

	for (size_t i = 0; i < messages.size(); ++i) {
		++day[messages[i].time.tm_mday];
		++month[messages[i].time.tm_mon];
		++year[messages[i].time.tm_year];
		++hour[messages[i].time.tm_hour];
		++minute[messages[i].time.tm_min];
		++second[messages[i].time.tm_sec];
	}

	// Print days, should be even distribution
	int dyTotal = 0;
	std::cout << "Number of messages in:\n";
	std::cout << "\nDay of month:\n";
	for (size_t i = 1; i < day.size(); ++i)
		std::cout << i << "\t"; // One indexed!
	std::cout << "\n";
	for (size_t i = 1; i < day.size(); ++i) {
		std::cout << day[i] << "\t";
		dyTotal += day[i];
	}

	// Print months, should be even distribution
	int mnTotal = 0;
	std::cout << "\n\nMonth of year:\n";
	for (size_t i = 1; i < month.size(); ++i)
		std::cout << i << "\t"; // One indexed!
	std::cout << "\n";
	for (size_t i = 1; i < month.size(); ++i) {
		std::cout << month[i] << "\t";
		mnTotal += month[i];
	}

	// Print years, should only see values in 17-22
	int yrTotal = 0;
	std::cout << "\n\nYear (from 2000):\n";
	for (size_t i = 1; i < year.size(); ++i)
		std::cout << i << "\t"; // One indexed!
	std::cout << "\n";
	for (size_t i = 1; i < year.size(); ++i) {
		std::cout << year[i] << "\t";
		yrTotal += year[i];
	}

	// Print hours, should see more during the day
	int hrTotal = 0;
	std::cout << "\n\n\nHour:\n";
	for (size_t i = 0; i < hour.size(); ++i)
		std::cout << i << "\t";
	std::cout << "\n";
	for (size_t i = 0; i < hour.size(); ++i) {
		std::cout << hour[i] << "\t";
		hrTotal += hour[i];
	}

	// Print minutes, should see even distribution
	int minTotal = 0;
	std::cout << "\n\nMinute:\n";
	for (size_t i = 0; i < 30; ++i)
		std::cout << i << "\t";
	std::cout << "\n";
	for (size_t i = 0; i < 30; ++i) {
		std::cout << minute[i] << "\t";
		minTotal += minute[i];
	}
	std::cout << "\n\n";
	for (size_t i = 30; i < 60; ++i)
		std::cout << i << "\t";
	std::cout << "\n";
	for (size_t i = 30; i < 60; ++i) {
		std::cout << minute[i] << "\t";
		minTotal += minute[i];
	}

	// Print seconds, should see totally even distribution
	int secTotal = 0;
	std::cout << "\n\nSecond:\n";
	for (size_t i = 0; i < 30; ++i)
		std::cout << i << "\t";
	std::cout << "\n";
	for (size_t i = 0; i < 30; ++i) {
		std::cout << second[i] << "\t";
		secTotal += second[i];
	}
	std::cout << "\n\n";
	for (size_t i = 30; i < 60; ++i)
		std::cout << i << "\t";
	std::cout << "\n";
	for (size_t i = 30; i < 60; ++i) {
		std::cout << second[i] << "\t";
		secTotal += second[i];
	}

	std::cout << "\nThe following totals should equal the above"
		"Total number of messages\n";
	std::cout << "Day total: " << dyTotal << "\n";
	std::cout << "Month total: " << mnTotal << "\n";
	std::cout << "Year total: " << yrTotal << "\n";
	std::cout << "Hour total: " << hrTotal << "\n";
	std::cout << "Minute total: " << minTotal << "\n";
	std::cout << "Second total: " << secTotal << "\n";
}

void Plumpa::printPhotos() {
	std::cout << "\n\nPhotos and Videos (total " << totalPhotos << "):\n";
	for (size_t i = 0; i < photos.size(); ++i) {
		std::cout << i << ":\t" << photos[i].message << "\n";
	}
}

void Plumpa::printNonMessages() {
	std::cout << "\n\nNon-messages (total " << totalNonMessages <<"):\n";
	for (size_t i = 0; i < nonMessages.size(); ++i) {
		std::cout << i << ":\t" << nonMessages[i].message << "\n";
	}
}

void Plumpa::printMembers() {
	std::cout << "\n\Members (total " << tempMembers.size() << "):\n";
	for (size_t i = 0; i < tempMembers.size(); ++i) {
		std::cout << i << ":\t" << tempMembers[i] << "\n";
	}
}

	 Plumpa::Plumpa() {
	readInput();
	analyzeTime();
	//printPhotos();
	//printNonMessages();
	printMembers();
}

int main(int argc, char* argv[]) {
	Plumpa p;
	return 0;
}