JavaScript Object Notation (JSON) is an open-standard format that uses human-readable text
    to transmit data objects consisting of attribute–value pairs.
    More info: https://en.wikipedia.org/wiki/JSON 

Example of JSON text:
```
{
    'animals': [
        {
            'name': "cat",
            'coordinates': [2, 5, 8],
            'height': 1,
            'is_vicious': false,
            'comment': "It's in fact quite... adorable."
        },
        {
            'name': "tiger",
            'coordinates': [-2, -5, -8],
            'height': -1,
            'is_vicious': true,
            'comment': "It's a parity-inverted cat."
        }
    ]
}
```
In the above example, if you want to access, say, the x-ccordinate of the tiger, you would want to do something simple like `my_json_resource["animals"][1]["coordinates"][0]`. This is precisely what RSJp-cpp lets you do.

RSJp-cpp is a template-based JSON parser for C++ that is contained in a single header file.
*   RSJp-cpp uses STL.
*   RSJp-cpp does not depend on any external library.
*   RSJp-cpp is template-based and there is nothing to build/install. The entire library is 
    contained in a single header file (`RSJparser.tcc`) that you simply include in your code.
*   RSJp-cpp implements a relaxed parser that works with standard JSON syntax while
    allowing some relaxation (e.g., omitting quotes around object key names).
*   It is possible to extend the parsers to non-fundamental or user-defined types.
*   Efficiency considerations:
    - Parses parts of the JSON text at an on-demand basis.
    - Internally stores parsed data for quick future reference.
    - TODO: Will use 'istream' for reading JSON text instead of 'string'.

### Use:
The header, `RSJparser.tcc`, provides the 'RSJresource' class that can be initialized using a 'std::string':
```C++
    RSJresource::RSJresource (std::string json_text);          // constructor
```
The structured data is then accessed using the following members:
```C++
    RSJresource& RSJresource::operator[] (std::string key);    // for JSON object
    RSJresource& RSJresource::operator[] (int indx);    // for JSON array
    template <class dataType> dataType RSJresource::as (const dataType& def = dataType());    // for JSON data (with value defaulting to 'def' if field does not exist)
```

### Example:
```C++
    std::string str = "{'RSJ': string data, keyName: [2,3,5,7]}";
    RSJresource my_json(str);
    std::cout  <<  my_json["keyName"][2].as<int>();     // prints 5
    std::cout  <<  my_json["RSJ"].as<std::string>("default string"); // prints "string data"
    std::cout  <<  my_json["JSON"].as<std::string>("default string"); // prints "default string"
```

### User-defined Types:
It is possible to extend the parsers to non-fundamental or user-defined types by
specializing the template member function 'as' in your own code:
```C++
    template<>
    user_defined_type  RSJresource::as<user_defined_type> (const user_defined_type& def)
    { /* ... */ }
```

Basic usage:
------------

* Include header file in your code:
```C++
    #include "RSJparser.tcc"
```

* Create an instance of 'RSJresource' using a string or file stream:
```C++
      std::string str = "{'animal':cat, coordinates: [2, 5, 8], height: 1, \nis_vicious: false, comment:'It\\'s in fact quite...\\t adorable.' }";
      RSJresource my_resource (str);

// or...

      std::ifstream my_fstream ("file_name.txt");
      RSJresource json_file_resource (my_fstream);
```

* Access structured JSON data:
```C++
      std::cout << my_resource["coordinates"][1].as<int>(); // prints 5
      std::cout << my_resource["is_vicious"].as<bool>(); // prints 0
      std::cout << my_resource["comment"].as<std::string>() << std::endl; // prints "It's in fact quite...	 adorable."
      std::cout << my_resource["height"].as<int>(-1) << std::endl; // prints 1
      std::cout << my_resource["width"].as<int>(-1) << std::endl; // prints -1
 ```
    
-----------------------------
Compile & run 'json_example.cpp':
```
    g++ -std=gnu++11 -Og -o json_example json_example.cpp
    ./json_example
```

-----------------------------
License:
```
/** **************************************************************************************
*                                                                                        *
*    A Ridiculously Simple RSJ Parser for C++ (RSJp-cpp)                                 *
*    Version 2.0                                                                         *
*    ----------------------------------------------------------                          *
*    Copyright (C) 2018  Subhrajit Bhattacharya                                          *
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
