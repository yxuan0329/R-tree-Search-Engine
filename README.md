# R-tree: A Library for Spatial Search Engine
A project that implement R-tree libary for spatial searching.

GitHub Repository: https://github.com/yxuan0329/R-tree-Search-Engine

## Table of Contents
- [Basic Information](#basic-information)
  - [Problem to Solve](#problem-to-solve)
  - [Prospective Users](#prospective-users)
- [System Architecture](#system-architecture)
  - [Feature Overview](#feature-overview)
  - [Architecture](#architecture)

- [API Description](#api-description)
  - [Get Started](#get-started)
  - [For C++ Users](#for-c-users)
  - [For Python Users](#for-python-users)
- [Engineering Infrastructure](#engineering-infrastructure)
- [Reference](#references)

## Basic Information
R-tree is a tree structure designed for efficient spatial data access. It has 
been widely used in real-world geographic searching because of its exceptional 
searching performance. In this project, we aim to serve a R-tree library to 
provide an efficient search for end-users. 


### Problem to Solve
In geographic searching application, the users would expect to swiftly receive 
a set of searching results upon entering the query. In real-world application, 
rapid access to geospatial information is crucial for the users, as delays can 
result in inconveniences and increased costs.  

The fundamental concept behind the R-tree is to encapsulate nearby objects 
related to the searching target within a minimum bounding rectangle. Our goal 
is to develop an efficient R-tree library for spatial data retrieval that can 
address large-scale spatial data searches. 


### Prospective Users
This project aims to provide to users who seek to build an efficient 
multi-dimensional searching service.


## System Architecture
### Feature Overview
The library includes:

- ``Rtree()``: Initialize a r-tree
- ``insert()``: Insert a reactangle area in r-tree
- ``remove()``: Delete a rectangle area in r-tree
- ``search()``: Search for all the available results in r-tree

### Architecture


## API Description
This library provides to C++ and python users. The users can include the library by linking in their program. 
### Get Started
1. Clone this GitHub repository.
  ``` bash
   $ git clone https://github.com/yxuan0329/R-tree-Search-Engine.git 
   ```
2. Build. You should see ``_Rtree.so`` in your directory if it built successfully.
  ``` bash
  $ make
  ```
### For C++ users
1. Include the following scripts in your main function.
``` c++
// add this at the head of your code
#include “.includes/Rtree.h”
```
2. Compile your program with linking the library.
The C++ users can include when compiling. See [main.cpp](./main.cpp) for more details.

  ```bash
  $ g++ main.cpp -o -l_Rtree
  ```

### For python users
The Python users can import the library by adding the script.
See [main.py](./main.py) for more details.

  ```python
  import r-tree-lib
  ```


## Engineering Infrastructure
1. Automatic build system: Makefile
2. Version control: git
3. Testing framework: Pytest
4. Documentation: README.md

  Testing data source: random-generated testing datasets including location and the 
  name of the place. 

  The testing mesurement includes correctness and time performance.


## References
- https://en.wikipedia.org/wiki/R-tree
- https://timecenter.cs.aau.dk/wp-content/uploads/2022/12/TR-45.pdf
- https://link.springer.com/referenceworkentry/10.1007/978-3-319-23519-6_1151-2
- https://blog.mapbox.com/a-dive-into-spatial-search-algorithms-ebd0c5e39d2a
- https://www.youtube.com/watch?v=hUIHtPLL940

