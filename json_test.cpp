/** **************************************************************************************
*                                                                                        *
*    A Ridiculously Simple JSON Parser for C++ (RSJP-cpp)                                *
*    Version 1.0a                                                                        *
*    ----------------------------------------------------------                          *
*    Copyright (C) 2016  Subhrajit Bhattacharya                                          *
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

// RSJP header:
#include "JSONparser.h"

int main(int argc, char *argv[])
{
    // Example 1:
    std::string    str = "{'animal':cat, coordinates: [2, 5, 8], is_vicious: false, "
                         "\ncomment:'It\\'s in fact quite...\\t adorable.' }";
    JSONcontainer  my_container (str); // JSON parser:
    
    std::cout << "\n---------\nEXAMPLE 1: The string:\n" << str << "\n" << std::endl;
    
    std::cout << "Iterating over the object fields:" << std::endl;
    JSONobject obj_map = my_container.as<JSONobject>(); // JSONobject = std::map <std::string,JSONcontainer>
    for (auto it=obj_map.begin(); it!=obj_map.end(); ++it)
        std::cout << "\t" << it->first << " => " << it->second.data << std::endl;
    std::cout << std::endl;
    
    std::cout << "Some specific queries:" << std::endl;
    std::cout << "\tThe animal is: " << my_container["animal"].as<std::string>() << std::endl;
    std::cout << "\tIts Y coordinate is: " << my_container["coordinates"][1].as<int>() << std::endl;
    std::cout << "\tIts Z coordinate is: " << my_container["coordinates"][2].as<double>() << std::endl;
    std::cout << "\tIs it vicious? " << my_container["is_vicious"].as<bool>() << std::endl;
    std::cout << "\tComment: " << my_container["comment"].as<std::string>() << std::endl;
    
    // ===============================================================================
    // Example 2:
    std::ifstream my_fstream ("envfiles/problems.env");
    JSONcontainer json_file_container (my_fstream);
    
    std::cout << "\n---------\nEXAMPLE 2: The string:\n" << json_file_container.data << "\n" << std::endl;
    
    JSONarray the_array = json_file_container.as<JSONarray>(); // JSONarray = std::vector <JSONcontainer>
    std::cout << "Number of experiments = " << the_array.size() << ".\nList the goals: " << std::endl;
    for (int a=0; a<the_array.size(); ++a)
        printf ("The %d-th goal is (%f, %f) in map %s.\n", a, 
                        the_array[a]["goal"][0].as<double>(), the_array[a]["goal"][1].as<double>(), 
                        the_array[a]["map_name"].as<std::string>().c_str());
    std::cout << std::endl;
}

