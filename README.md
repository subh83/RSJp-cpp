```
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
```

JavaScript Object Notation (JSON) is an open-standard format that uses human-readable text
    to transmit data objects consisting of attribute–value pairs.
    More info: https://en.wikipedia.org/wiki/JSON 

RSJP-cpp is a template-based JSON parser for C++ that is contained in a single header file.
*   RSJP-cpp uses STL.
*   RSJP-cpp does not depend on any external library.
*   RSJP-cpp is template-based and there is nothing to build/install. The entire library is 
    contained in a single header file that you simply include in your code.
*   RSJP-cpp implements a relaxed parser that works with standard JSON syntax while
    allowing some relaxation (e.g., omitting quotes around object key names).
*   It is possible to extend the parsers to non-fundamental or user-defined types.
*   Efficiency considerations:
    - Parses parts of the JSON text at an on-demand basis.
    - Internally stores parsed data for quick future reference.
    - TODO: Will use 'istream' for reading JSON text instead of 'string'.

### Use:
The header provides the 'JSONcontainer' class that can be initialized using a 'std::string':
```C++
    JSONcontainer::JSONcontainer (std::string json_text);          // constructor
```
The structured data is then accessed using the following members:
```C++
    JSONcontainer& JSONcontainer::operator[] (std::string key);    // for JSON object
    JSONcontainer& JSONcontainer::operator[] (int indx);           // for JSON array
    template <class dataType> dataType JSONcontainer::as (void);   // for JSON data
```

### Example:
```C++
    std::string str = "{'JSON': string_data, keyName: [2,3,5,7]}";
    std::cout  <<  JSONcontainer(str)["keyName"][2].as<int>();     // prints 5
```

### User-defined Types:
It is possible to extend the parsers to non-fundamental or user-defined types by
specializing the template member function 'as' in your own code:
```C++
    template<>
    user_defined_type  JSONcontainer::as<user_defined_type> (void)
    { /* ... */ }
```

Basic usage:
------------

* Include header file in your code:
```C++
    #include "JSONparser.h"
```

* Create an instance of 'JSONcontainer' using a string or file stream:
```C++
      std::string str = "{'animal':cat, coordinates: [2, 5, 8], is_vicious: false, \n comment:'It\\'s in fact quite...\\t adorable.' }";
      JSONcontainer my_container (str);

// or...

      std::ifstream my_fstream ("envfiles/problems.env");
      JSONcontainer json_file_container (my_fstream);
```

* Access structured JSON data:
```C++
      std::cout << my_container["coordinates"][1].as<int>();
      std::cout << my_container["is_vicious"].as<bool>();
      std::cout << my_container["comment"].as<std::string>() << std::endl;
    
      JSONarray the_array = json_file_container.as<JSONarray>();
      std::cout << the_array[1]["goal"][0].as<double>();
 ```
    
-----------------------------
Compile & run 'json_test.cpp':
```
    g++ -std=gnu++11 -O3 -g  -w -I. -o json_test json_test.cpp -lm
    ./json_test
```
