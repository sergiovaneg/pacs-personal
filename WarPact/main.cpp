#include "Network.hpp"
#include <iostream>

#define N_I 5000
#define N_F 2500

unsigned Node::current_id = 0;

int main(int argc, char** argv){
    unsigned n_i = (argc == 3) ? std::stoul(argv[1]) : N_I;
    unsigned n_f = (argc == 3) ? std::stoul(argv[2]) : N_F;

    Network reference{n_i};
    reference.print("initial");
    
    {
        Network war_pact{reference};
        std::cout << "Running RR...\r";
        std::cout.flush();
        war_pact.run<Method::RR>(n_f);
        std::cout << "Printing RR...\r";
        std::cout.flush();
        war_pact.print("RR");
        std::cout << "Done with RR." << std::endl;
    }

    {
        Network war_pact{reference};
        std::cout << "Running KK...\r";
        std::cout.flush();
        war_pact.run<Method::KK>(n_f);
        std::cout << "Printing KK...\r";
        std::cout.flush();
        war_pact.print("KK");
        std::cout << "Done with KK." << std::endl;
    }

    {
        Network war_pact{reference};
        std::cout << "Running KR...\r";
        std::cout.flush();
        war_pact.run<Method::KR>(n_f);
        std::cout << "Printing KR...\r";
        std::cout.flush();
        war_pact.print("KR");
        std::cout << "Done with KR." << std::endl;
    }

    {
        Network war_pact{reference};
        std::cout << "Running KI...\r";
        std::cout.flush();
        war_pact.run<Method::KI>(n_f);
        std::cout << "Printing KI...\r";
        std::cout.flush();
        war_pact.print("KI");
        std::cout << "Done with KI." << std::endl;
    }
}