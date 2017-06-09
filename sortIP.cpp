/*
 * Sorts IP adresses, given by file.
 *   
 * Copyright (C) 2017 Yakup Ates <Yakup.Ates@rub.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sortIP.h"

using namespace std;

sortIP::sortIP(){
	cout << "[#] Note: No file to sort given. Exit." << endl;
}

sortIP::sortIP(const string& path){
	set_file(path);
	sortIPs();
}

sortIP::~sortIP(){
	vector_from_file.clear();
}

/**
 * See if file exists. Very fast.
 */
inline bool sortIP::file_exists(const string& file_path) const{
	struct stat buffer;
	
	return (stat (file_path.c_str(), &buffer) == 0); 
}

/**
 * Validate given path to file and set if valid.
 */
inline bool sortIP::set_file(const std::string& path){
	if(file_exists(path)){
		file_path = path;
		return true;
	} else {
		cout << "[-] Error: Given file does not exist." << endl;
		return false;;
	}
}

/**
 * Extract all lines of file and save them in a vector.
 * TODO: Check if line is an IP.
 */
bool sortIP::file_to_vector(){
	ifstream file_stream(file_path.c_str());
	if(!file_stream.is_open()){
		cout << "[-] Error: Could not open file." << endl;
		return false;
	}
	
	istream_iterator<string> start(file_stream), end;
	vector<string> result(start, end);
	vector_from_file = result;
	result.clear();

	return true;
}

/**
 * After sorting is done the vector can be written back into a file again.
 * TODO: Check what could go wrong.
 */
bool sortIP::vector_to_file(){
	char dot = '.';
	
	vector<string> tmp = splitString(file_path, dot);
	output_filename = tmp[0] + PREFIX + dot + tmp[1];
	tmp.clear();
	
	ofstream output_file_stream(output_filename.c_str());
	ostream_iterator<string> output_iterator(output_file_stream, "\n");
	copy(vector_from_file.begin(), vector_from_file.end(), output_iterator);

	return true;
}

/**
 * Split a string by a given character.
 */
vector<string> sortIP::splitString(const string& input, const char& split_character) const{
	string cut_string;
	vector<string> result;
	stringstream input_stream;
	input_stream << input;

	while(getline(input_stream, cut_string, split_character))
		result.push_back(cut_string);

	return result;
}

/**
 * Sort a vecor of IP addresses (ascending).
 */
bool sortIP::sortIPs() {
	cout << "[#] Input file: " << file_path << endl;
	if(file_to_vector()){
		cout << "[+] Note: Converted file to vector..." << endl;
		// https://stackoverflow.com/questions/41156952/convert-ip-address-to-a-single-number
		struct CompareSockAddr_in{
			bool operator ()(struct sockaddr_in ip1, struct sockaddr_in ip2){
				return ip1.sin_addr.s_addr < ip2.sin_addr.s_addr;
			}
		};
		
		int vector_length = vector_from_file.size();
		struct sockaddr_in ip_structs[vector_length];

		// http://www.manpagez.com/man/3/inet/
		for(int i=0; i<vector_length; ++i)
			inet_pton(AF_INET, vector_from_file[i].c_str(), &(ip_structs[i].sin_addr));

		// sort ip structs by uint32_t s_addr
		// https://linux.die.net/man/7/ip
		sort(ip_structs, ip_structs+vector_length, CompareSockAddr_in());
		cout << "[+] Note: Sorted ip adresses..." << endl;

		// http://www.manpagez.com/man/3/inet/
		for(int i=0; i<vector_length; ++i)
			vector_from_file[i] = inet_ntoa(ip_structs[i].sin_addr);

		if(vector_to_file()){
			cout << "[+] Note: Converted vector to file..." << endl;
			cout << "[#] Output file: " << output_filename << endl;
			cout << "[>] Done." << endl;
			return true;
		}
	}

	return false;
}
