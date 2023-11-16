#include <iostream>
#include "Node.h"

using namespace std;

template<typename DataType>
Node<DataType>::Node() {
    this->id = 0;
    this->longtitude = 0.0;
    this->latitude = 0.0;
    this->altitude = 0.0;
}

template<typename DataType>
Node<DataType>::Node(int id, DataType lon, DataType lat){
    this->id = id;
    this->longtitude = lon;
    this->latitude = lat;
    this->altitude = 0.0;
}

template<typename DataType>
Node<DataType>::Node(int id, DataType lon, DataType lat, DataType alt){
    this->id = id;
    this->longtitude = lon;
    this->latitude = lat;
    this->altitude = alt;
}

template<typename DataType>
Node<DataType>::~Node() {
    delete this;
}

template<typename DataType>
bool Node<DataType>::operator==(const Node& other) const {
    return (longtitude == other.longtitude && latitude == other.latitude && altitude == other.altitude);
}

template<typename DataType>
bool Node<DataType>::operator!=(const Node& other) const {
    return !(*this == other);
}

