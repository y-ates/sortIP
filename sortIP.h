#ifndef SORT_IP_H
#define SORT_IP_H

#define sortIP_VERSION_MAJOR 
#define sortIP_VERSION_MINOR 
#define PREFIX "_sorted"

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

class sortIP {
 private:
	std::string file_path;
	std::vector<std::string> vector_from_file;
 public:
	sortIP();
	sortIP(const std::string path);
	~sortIP();

	std::vector<std::string> splitString(std::string input, char split_character);
	inline bool set_file(const std::string path);
	inline bool file_exists(const std::string file_path);
	bool file_to_vector();
	bool vector_to_file();
	bool sortIPs();

};

#endif
