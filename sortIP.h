#ifndef SORT_IP_H
#define SORT_IP_H

#define sortIP_VERSION_MAJOR 1
#define sortIP_VERSION_MINOR 0
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

	std::vector<std::string> splitString(std::string input, char split_character) const;
	inline bool set_file(const std::string path);
	inline bool file_exists(const std::string file_path) const;
	bool file_to_vector();
	bool vector_to_file() const;
	bool sortIPs();

};

#endif
