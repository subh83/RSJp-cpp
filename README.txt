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

JavaScript Object Notation (JSON) is an open-standard format that uses human-readable text
    to transmit data objects consisting of attribute–value pairs.
    More info: https://en.wikipedia.org/wiki/JSON 

RSJP-cpp is a template-based JSON parser for C++ that is contained in a single header file.
*   RSJP-cpp uses STL.
*   RSJP-cpp does not depend on any external library.
*   RSJP-cpp is template-based and there is nothing to build/install. The entire library is 
    contained in a single header file that you simply need to unclude in your code.
*   RSJP-cpp implements a relaxed parser that works with standard JSON syntax while
    allowing some relaxation (e.g., omitting quotes around object field names).
*   Efficiency considerations:
    - Parses the JSON text on an on-demand basis.
    - Internally stores parsed data for quick future reference.
    - TODO: Will use 'istream' for reading JSON text instead of 'string'.


Basic usage:
------------

* Include header file in your code:

    #include "JSONparser.h"
    
* Create an instance of 'JSONcontainer' using a string or file stream:

    - std::string str = "{'animal':cat, coordinates: [2, 5, 8], is_vicious: false, "
                        "\ncomment:'It\\'s in fact quite...\\t adorable.' }";
      JSONcontainer my_container (str);
    
    - std::ifstream my_fstream ("envfiles/problems.env");
      JSONcontainer json_file_container (my_fstream);
    
* Access structured JSON data:

    - std::cout << my_container["coordinates"][1].as<int>();
      std::cout << my_container["comment"].as<std::string>() << std::endl;
    
    - JSONarray the_array = json_file_container.as<JSONarray>();
      std::cout << the_array[a]["goal"][0].as<double>();
    
    
-----------------------------
Compile & run 'json_test.cpp':
    g++ -std=gnu++11 -O3 -g  -w -I. -o json_test json_test.cpp -lm
    ./json_test

