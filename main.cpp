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
#include "cxxopts.hpp"

int main(int argc, char* argv[]){
    try{
        cxxopts::Options options(argv[0], "Sorts IP adresses, given by file.");
        options.add_options()
            ("f,file", "File name", cxxopts::value<std::string>());

        options.add_options()
            ("h,help", "Help; not really :D");

        options.parse(argc, argv);

        if(options.count("f")){
            std::string file_path_argv = options["f"].as<std::string>();
            sortIP ip_sorter(file_path_argv);
            return 0;
        }

        if(options.count("h")){
            std::cout << "You should point me to a file containing ip adresses: "
                  << argv[0] << " -f [file-with-ip_adresses]"
                  << std::endl;
            return 0;
        }
    } catch (const cxxopts::OptionException& e){
        std::cout << "[-] Error: Parsing options: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
