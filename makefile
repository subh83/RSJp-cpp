# A Ridiculously Simple JSON Parser for C++ (RSJp-cpp)
# Makefile for compiling examples

# Change these if needed or pass as input parameter
PREFIX = /usr/local

# ================================

# INCLUDE FOLDER
# --------------

INC_FOLDER = $(PREFIX)/include

# --------------------------------------------
# Install

.PHONY: install
install:
	cp RSJparser.tcc $(INC_FOLDER)
	find $(INC_FOLDER)/RSJparser.tcc -type d -exec chmod 755 {} \;
	find $(INC_FOLDER)/RSJparser.tcc -type f -exec chmod 644 {} \;

.PHONY: uninstall
uninstall:
	rm -rf $(INC_FOLDER)/RSJparser.tcc

# --------------------------------------------
# Examples

.PHONY: tests
tests:
	cd tests && \
	g++ -std=gnu++11 -I.. -Og -o json_example json_example.cpp && \
	g++ -std=gnu++11 -I.. -Og -o benchmark benchmark.cpp && \
	g++ -std=gnu++11 -I.. -Og -c utils.cpp && \
	g++ -std=gnu++11 -I.. -Og -o parse_file_test utils.o parse_file_test.cpp

