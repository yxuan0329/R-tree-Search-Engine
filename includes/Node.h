#ifndef NODE_H
#define NODE_H

template<typename DataType>
class Node {
public:
    Node();
    ~Node();

    Node(int, DataType, DataType);
    Node(int, DataType, DataType, DataType);

    bool operator==(const Node&) const;
    bool operator!=(const Node&) const;

    const DataType& getLong() const { return longtitude; }
    const DataType& getLat() const { return latitude; }
    const DataType& getAlt() const { return altitude; }
    const bool isLeaf() const { return isLeaf; }    

private:
    int id; // id of the node(location), for referencing the location name
    DataType longtitude = 0.0;
    DataType latitude = 0.0;
    DataType altitude = 0.0;
    bool isLeaf = true;
};

#endif
