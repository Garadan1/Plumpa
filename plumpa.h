#pragma once

#define DEBUG // For extensive debugging

class Plumpa {
// Structs

	struct Member { // Aligned!
		std::string name;
		size_t numMessages = 0;
	};

	struct Message { // Aligned!
		tm time; // (tm struct from ctime)
		Member sender;
		std::string message; // This is probably not efficient
	};

// Member variables
	size_t totalMessages = 0; // Default 0
	size_t nonMessages = 0;
	std::vector<Message> messages;
	std::vector<Member> members;

// Member functions

	// Reads in chat history from cin, sanitizes it, and stores for analysis
	// TODO: Create an overloaded version with string parameter
	void readInput() {
		messages.reserve(350000); // Find a better way to do this
		std::string raw;
		// Ignore messages not starting with [ for now
		// TODO: Add lines not starting with [ to previous message
		while (getline(std::cin, raw)) {
			// This is not a safe check!! TODO: Fix the isdigit part!
			if (raw[0] == '[' && isdigit(raw[1])) {
				Message temp;

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

				temp.time.tm_mon = month;

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
				raw = raw.substr(6 ,raw.size());

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

				// TODO: Finish implementing - Sender (Member), message

				// Assign values to time struct
				// Note that the "year" does not follow the C++ standard
				// It's fine for our purposes.
				temp.time.tm_mday = day;
				temp.time.tm_mon = month;
				temp.time.tm_year = year;
				temp.time.tm_sec = sec;
				temp.time.tm_min = min;
				temp.time.tm_hour = hour;
				
				messages.push_back(temp);
				++totalMessages;
			}
			else {
				++nonMessages;
			}
		} // while()
	} // readInput()

	// TODO: Implement
	void readInput(std::string filename) {
		std::cout << "Need to implement this\n";
	}
	
	// This is kind of lazy, and not meant to be permanent
	// More of a debugging tool
	void analyzeTime() {

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


		std::cout << "\n\nTotal number of non-messages: " << nonMessages << "\n";
		std::cout << "Total number of messages: " << totalMessages << "\n";

		std::cout << "\nThe following totals should equal the above"
			"Total number of messages\n";
		std::cout << "Day total: " << dyTotal << "\n";
		std::cout << "Month total: " << mnTotal << "\n";
		std::cout << "Year total: " << yrTotal << "\n";
		std::cout << "Hour total: " << hrTotal << "\n";
		std::cout << "Minute total: " << minTotal << "\n";
		std::cout << "Second total: " << secTotal << "\n";
	}

public:

	// Constructor
	Plumpa() {
		readInput();
		analyzeTime();
	}
};