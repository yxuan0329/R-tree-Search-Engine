# R-tree-Search-Engine
A project that implement R-tree libary for spatial searching.
- GitHub Repository: https://github.com/yxuan0329/R-tree-Search-Engine


## Basic Information
R-tree is a tree structure designed for efficient spatial data access. It has 
been widely used in real-world geographic searching because of its exceptional 
searching performance. In this project, we aim to serve a R-tree library to 
provide an efficient search for end-users. 


## Problem to Solve
In geographic searching application, the users would expect to swiftly receive 
a set of searching results upon entering the query. In real-world application, 
rapid access to geospatial information is crucial for the users, as delays can 
result in inconveniences and increased costs.  

The fundamental concept behind the R-tree is to encapsulate nearby objects 
related to the searching target within a minimum bounding rectangle. Our goal 
is to develop an efficient R-tree library for spatial data retrieval that can 
address large-scale spatial data searches. 


## Prospective Users
This project aims to provide to users who seek to build an efficient 
multi-dimensional searching service.


## System Architecture
### Architecture
The library would include:

- ``build_tree``: build a r-tree
- ``insert``: insert a node in r-tree
- ``delete``: delete a node in r-tree
- ``search``: search for the available results in r-tree

### Datasets
Randomly generate about 50-100 map data entry by Python for validating the 
R-tree algorithm can works correctly. 
For the initial testing, the dimension of each data is 3 (latitude, longitude, 
altitude). After that, I intend to expand the dimensionality of the generated 
data to 4 or 5 dimensions, or maybe n-dimension if the users create their own 
datasets in the future. 


## API Description
The users can include the library by linking in their project. 
The C++ users can include when compiling.

``g++ main.cpp -o -lr-tree-library``

The Python users can import the library by adding the script.

``import r-tree-library``


## Engineering Infrastructure
1. Automatic build system: CMake
2. Version control: git
3. Testing framework: Pytest
4. Documentation: README.rst

  Testing data source: random-generated testing datasets including location and the 
  name of the place. 

  The testing mesurement includes correctness and time performance.

## Schedule

* Planning phase (6 weeks from mm/dd to mm/dd):

### Week 0 (10/03-10/29)
- Planning the project proposal

### Week 1 (10/30-11/05)
- Survey some reference about the data structure and implementation
- Survey some existing R-tree paper
- Create a few testing dataset for testing the existing libraries

### Week 2 (11/06-11/12)
- Create about 50-100 testing datasets for future use
- Design the C++ classes architecture

### Week 3 (11/13-11/19)
- Implement R-tree with C++: ``build_tree``, ``insert``, ``delete``

### Week 4 (11/20-11/28)
- Implement R-tree with C++: ``search``

### Week 5 (11/27/12/03)
- Implement R-tree with C++: allow to search in user-defined dimension
- Refactor the code if needed 

### Week 6 (12/04-12/10)
- Testing the features with pytest

### Week 7 (12/11-12/17)
- Finish up the project and the documentation
- Prepare for the slides
  
### Week 8 (12/18-12/24)
- Prepare for the presentation

## References
- https://en.wikipedia.org/wiki/R-tree
- https://timecenter.cs.aau.dk/wp-content/uploads/2022/12/TR-45.pdf
- https://link.springer.com/referenceworkentry/10.1007/978-3-319-23519-6_1151-2
- https://blog.mapbox.com/a-dive-into-spatial-search-algorithms-ebd0c5e39d2a
