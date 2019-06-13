/** **************************************************************************************
*                                                                                        *
*    A Ridiculously Simple RSJ Parser for C++ (RSJp-cpp)                                 *
*    Version 2.x                                                                         *
*    ----------------------------------------------------------                          *
*    Copyright (C) 2017  Subhrajit Bhattacharya                                          *
*                                                                                        *
*    This program is free software: you can redistribute it and/or modify                *
*    it under the terms of the GNU General Public License as published by                *
*    the Free Software Foundation, either version 3 of the License, or                   *
*    (at your option) any later version.                                                 *
*                                                                                        *
*    This program is distributed in the hope that it will be useful,                     *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of                      *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                       *
*    GNU General Public License for more details <http://www.gnu.org/licenses/>.         *
*                                                                                        *
*                                                                                        *
*    Contact:  subhrajit@gmail.com                                                       *
*              https://www.lehigh.edu/~sub216/ , http://subhrajit.net/                   *
*                                                                                        *
*                                                                                        *
*************************************************************************************** **/
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

// RSJP header:
#include "RSJparser.tcc"

#define DO_TEST 1
#define PRINT_PARSED 0
#define DO_BENCHMARK 1

using namespace std::chrono;

int main(int argc, char *argv[])
{
    // Load file content
    std::string json_file = "json_files/canada.json";
    if (argc>1)
        json_file = argv[1];
    std::string path(argv[0]);
    path = path.substr(0, path.find_last_of("\\/")+1);
    std::cout << "Loading file " << (path+json_file) << "." << std::endl;
    std::ifstream my_fstream (path+json_file);
    std::string my_json_string ((std::istreambuf_iterator<char>(my_fstream)), std::istreambuf_iterator<char>());
    
    if (DO_TEST) {
        RSJresource json_file_resource (my_json_string);
        json_file_resource.parse_full ();
        // std::cout << "The JSON string is " << my_json_string  << std::endl;
        std::cout << "The JSON string is " << my_json_string.length() << " bytes long." << std::endl;
        std::cout << "Test parse: The root contains " << json_file_resource.size() << " elements." << std::endl;
        if (PRINT_PARSED)
            std::cout << json_file_resource.as_str() << std::endl;
    }
    
    if (DO_BENCHMARK) {
        int parse_count = 10;
        if (argc>2)
            parse_count = atoi (argv[2]);
        
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        for (int a=0; a<parse_count; ++a) {
            //std::cout << "a = " << a << std::endl;
            RSJresource json_file_resource (my_json_string);
            json_file_resource.parse_full (true);
        }
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        
        auto duration = duration_cast<milliseconds>(t2-t1).count();
        std::cout << "Done! Parsed " << parse_count << " times. Time taken = " << duration << " milli-seconds" << std::endl;
    }
    
}

