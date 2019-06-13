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
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

// RSJP header:
#include "RSJparser.tcc"

int main(int argc, char *argv[])
{
    std::ifstream my_fstream (argv[1]);
    RSJresource my_json (my_fstream);
    //std::cout << std::string ( (std::istreambuf_iterator<char>(my_fstream)), (std::istreambuf_iterator<char>()) ) << std::endl;
    std::cout << my_json.as_str() << std::endl;
}

