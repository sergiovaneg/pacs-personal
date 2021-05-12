#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <vector>
#include <fstream>
#include <random>
#include <utility>
#include <algorithm>

#include "Node.hpp"

enum class Method{
    RR,
    KK,
    KR,
    KI
};

class Network{
    std::vector<Node> nodes;
    std::random_device r;
    std::default_random_engine engine{r()};

    template <Method m>
    std::pair<size_t, size_t> pick(){
        std::pair<size_t, size_t> result = std::make_pair(0,0);

        if constexpr(m == Method::RR){
            std::uniform_int_distribution<size_t> distribution(0, nodes.size()-1);
            result.first = distribution(engine);
            result.second = distribution(engine);
        }
        if constexpr(m == Method::KK){
            std::vector<double> weights;
            weights.reserve(nodes.size());
            for(const Node& aux : nodes)
                weights.push_back(aux.get_neighbours().size());

            std::discrete_distribution<size_t> distribution(weights.cbegin(), weights.cend());
            result.first = distribution(engine);
            result.second = distribution(engine);
        }
        if constexpr(m == Method::KR){
            std::vector<double> weights;
            weights.reserve(nodes.size());
            for(const Node& aux : nodes)
                weights.push_back(aux.get_neighbours().size());

            std::discrete_distribution<size_t> distribution1(weights.cbegin(), weights.cend());
            std::uniform_int_distribution<size_t> distribution2(0, nodes.size()-1);
            result.first = distribution1(engine);
            result.second = distribution2(engine);
        }
        if constexpr(m == Method::KI){
            std::vector<double> weights, inv_weights;
            weights.reserve(nodes.size());
            inv_weights.reserve(nodes.size());
            for(const Node& aux : nodes){
                weights.push_back(aux.get_neighbours().size());
                inv_weights.push_back(1./weights.back());
            }

            std::discrete_distribution<size_t> distribution1(weights.cbegin(), weights.cend());
            std::discrete_distribution<size_t> distribution2(inv_weights.cbegin(), inv_weights.cend());
            result.first = distribution1(engine);
            result.second = distribution2(engine);
        }

        return result;
    }

    bool check(std::pair<size_t, size_t> p)
    {
        if (p.first == p.second)
            return false;

        if(std::find(nodes[p.first].get_neighbours().cbegin(),
                        nodes[p.first].get_neighbours().cend(),
                        nodes[p.second].get_id())
            != nodes[p.first].get_neighbours().cend())
            return false;

        return true;
    }

    void merge(std::pair<size_t, size_t> p)
    {
        size_t a, b;
        if(nodes[p.first].get_size() > nodes[p.second].get_size()){
            a = p.first;
            b = p.second;
        }
        
        else{
            a = p.second;
            b = p.first;
        }

        nodes[a].merge(nodes[b]);
            for(Node& aux : nodes){
                if(aux.get_id() == nodes[b].get_id())
                    continue;
                if(aux.remove_neighbour(nodes[b].get_id()))
                    aux.add_neighbour(nodes[a].get_id());
            }
            nodes.erase(nodes.begin() + b);
    }

public:
    Network(size_t size)
    {
        for(size_t i = 0; i < size; ++i){
            nodes.emplace_back();
            if(i%2){
                nodes[i].add_neighbour(i-1);
                nodes[i-1].add_neighbour(i);
            }
        }
    }

    Network(const Network& net) : nodes{net.nodes.cbegin(), net.nodes.cend()}
    {}

    template <Method m>
    void run(size_t target)
    {
        while(nodes.size() > target){
            auto picked = pick<m>();
            if(check(picked))
                merge(picked);
        }
    }

    void print(const std::string& filename) const{
        std::ofstream ofs_nodes, ofs_edges;

        ofs_nodes.open(filename + "_nodes.csv", std::ofstream::out | std::ofstream::trunc);
        ofs_nodes << "Id,Label,Size" << std::endl;

        ofs_edges.open(filename + "_edges.csv", std::ofstream::out | std::ofstream::trunc);
        ofs_edges << "Source,Target,Type" << std::endl;

        for(const Node& aux : nodes){
            ofs_nodes << aux.get_id() << "," << aux.get_id() << "," << aux.get_size() << std::endl;
            ofs_edges << aux;
        }
        
        ofs_nodes.close();
        ofs_edges.close();
    }
};

#endif