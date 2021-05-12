#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <set>
#include <algorithm>
#include <ostream>

class Node{
    unsigned id;
    std::set<unsigned> neighbours;
    unsigned size;

public:
    static unsigned current_id;

    Node(){
        id = current_id++;
        size = 1;
    }

    unsigned get_id() const {return id;}

    const std::set<unsigned>& get_neighbours() const {return neighbours;}
    void add_neighbour(unsigned neighbour) {neighbours.insert(neighbour);}
    bool remove_neighbour(unsigned neighbour) {return neighbours.erase(neighbour);}

    unsigned get_size() const {return size;}

    void merge(Node& other)
    {
        size += other.size;
        neighbours.insert(other.neighbours.cbegin(), other.neighbours.cend());
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& node);
};

std::ostream& operator<<(std::ostream& os, const Node& node)
{
    for(const unsigned& n : node.neighbours)
        os << node.id << "," << n << ",\"undirected\"" << std::endl;
    return os;
}

#endif