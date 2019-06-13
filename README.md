JavaScript Object Notation (JSON) is a text-based presentation of structured data consisting of objects (attribute–value pairs) and arrays. More info: https://en.wikipedia.org/wiki/JSON .

RSJp-cpp (a Ridiculously Simple JSON Parser for C++) is a template-based C++ parser (and emitter) for JSON texts. RSJp-cpp is easy to use and parses the JSON text at an on-demand basis.

### Simple Example:
```C++
    std::string str = "{'RSJ': 'string data', 'keyName': [2,3,5,7]}";
    RSJresource my_json(str);
    std::cout  <<  my_json["keyName"][2].as<int>() << std::endl;     // prints 5
    std::cout  <<  my_json["RSJ"].as<std::string>("default string") << std::endl; // prints "string data"
    std::cout  <<  my_json["JSON"].as<std::string>("default string") << std::endl; // prints "default string"
```

RSJp-cpp is a template-based JSON parser for C++ that is contained in a single header file.
*   RSJp-cpp uses STL and does not depend on any external library.
*   RSJp-cpp is template-based and there is nothing to build/install. The entire library is contained in a single header file (`RSJparser.tcc`) that you simply include in your code. However, you can optionally copy the header to system folder by executing `sudo make install`.
*   RSJp-cpp implements a relaxed parser that works with standard JSON syntax while allowing some relaxation (e.g., omitting quotes around object key names).
*   It is possible to extend the parsers to non-fundamental or user-defined types.
*   Efficiency considerations:
    - Parses parts of the JSON text at an on-demand basis as queries are made (i.e., does not require an entire JSON text/file to be parsed for accessing only a part of it).
    - Internally stores parsed data for quick future reference.
    - Current version of RSJp-cpp is however not very efficient at parsing an entire large JSON file in one go. In future versions a `fast_parse` method will be included for such parsing tasks.
*   **Security warning:** RSJp-cpp skips most syntax and sanity checks on the JSON text itself. If the JSON text has invalid JSON syntax, most of the time RSJp-cpp will still parse it without complaining, although its behavior may be unexpected / undefined. So, if the JSON text is a potential source of infiltration (e.g., user input in a web-based application), RSJp-cpp should not be used. Future version of RSJp-cpp will have added security features that can be optionally turned on for performing syntax checks on the JSON text.


### Use:
The header, `RSJparser.tcc`, provides the 'RSJresource' class that can be initialized using a 'std::string':
```C++
    RSJresource::RSJresource (std::string json_text);          // constructor
```
The structured data is then accessed using the following members:
```C++
    RSJresource& RSJresource::operator[] (std::string key);    // for JSON object
    RSJresource& RSJresource::operator[] (int indx);    // for JSON array
    template <class dataType> dataType RSJresource::as (const dataType& def = dataType());    // for JSON leaf data (with value defaulting to 'def' if field does not exist)
```

**Specializations of the `RSJresource::as()` template provided with the library:**

```C++
    std::string  RSJresource::as<std::string> (const std::string& def);
    int  RSJresource::as<int> (const int& def);
    double  RSJresource::as<double> (const double& def);
    bool  RSJresource::as<bool> (const bool& def);
    // RSJ-specific types:
    RSJobject RSJresource::as<RSJobject> (const RSJobject& def);
    RSJarray  RSJresource::as<RSJarray> (const RSJarray& def);
```

### Other useful declarations and member functions:
```C++
    // typedefs and enums
    typedef std::unordered_map <std::string,RSJresource>    RSJobject;
    typedef std::vector <RSJresource>                       RSJarray;
    enum RSJresourceType { RSJ_UNINITIATED, RSJ_UNKNOWN, RSJ_OBJECT, RSJ_ARRAY, RSJ_LEAF };
    
    // function to query properties
    int RSJresource::size (void);
    bool RSJresource::exists (void);
    RSJresourceType RSJresource::type (void);
    
    // single-level parsing functions
    RSJobject& RSJresource::as_object(); // get reference to object as 'std::unordered_map<std::string,RSJresource>'.
    RSJarray& RSJresource::as_array(); // get reference to array as 'std::vector<RSJresource>'.
    
    // printing/emitting functions
    std::string RSJresource::as_str (bool print_comments=false); // outputs as string. Note: 'as_str()' parses the entire JSON if it's not already parsed.
    void RSJresource::print (bool print_comments=false); // prints to terminal. Note: 'print()' parses the entire JSON if it's not already parsed.
    
    // object/array with fields converted to a specified type
    template <class dataType> 
        std::unordered_map<std::string,dataType> RSJresource::as_map (); // get copy of object as 'std::unordered_map<std::string,dataType>'
    template <class dataType> 
        std::vector<dataType> RSJresource::as_vector (); // get copy of array as 'std::vector<dataType>'
```

### User-defined Types:
It is possible to extend the parsers to non-fundamental or user-defined types by specializing the template member function 'as' in your own code:
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
    std::cout << my_resource["coordinates"][1].as<int>() << std::endl; // prints 5
    std::cout << my_resource["is_vicious"].as<bool>() << std::endl; // prints 0
    std::cout << my_resource["comment"].as<std::string>() << std::endl; // prints "It's in fact quite...	 adorable."
    std::cout << my_resource["height"].as<int>(-1) << std::endl; // prints 1
    std::cout << my_resource["width"].as<int>(-1) << std::endl; // prints -1
 ```
 
* Iterate over an array or object:
```C++
    std::cout << "This animal lives in a " << my_resource["coordinates"].size() << " dimensional space." << std::endl;
    // Output: This animal lives in a 3 dimensional space.
    
    for (auto it=my_resource["coordinates"].as_array().begin(); it!=my_resource["coordinates"].as_array().end(); ++it)
        std::cout << " | " << it->as<int>();
    std::cout << " | " << std::endl;
    // Output: | 2 | 5 | 8 |
```

* Change / insert contents and print:
```C++
    my_resource["coordinates"][1] = -5; // change Y-coordinate
    my_resource["color"] = "black";
    std::cout << "changed contents:\n" << my_resource.as_str() << std::endl;
    /* Output:
        changed contents:
        {
            'comment': 'It\'s in fact quite...\t adorable.',
            'is_vicious': false,
            'height': 1,
            'coordinates': [
                2,
                -5,
                8
            ],
            'color': black,
            'animal': cat
        }
    */
```
    
-----------------------------
Compile & run 'json_example.cpp':
```
    cd tests
    g++ -std=gnu++11 -I.. -Og -o json_example json_example.cpp
    ./json_example
```

Compile & run 'benchmark.cpp':
```
    cd tests
    g++ -std=gnu++11 -I.. -Og -o benchmark benchmark.cpp
    ./benchmark
```

Copy 'RSJparser.tcc' to system folder:
```
    sudo make install
```


License:
--------

```
/** **************************************************************************************
*                                                                                        *
*    A Ridiculously Simple JSON Parser for C++ (RSJp-cpp)                                *
*    Version 2.x                                                                         *
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

`tests/json_files/canada.json` is included from https://github.com/serde-rs/json-benchmark/blob/master/data/canada.json under the terms of Apache License.
