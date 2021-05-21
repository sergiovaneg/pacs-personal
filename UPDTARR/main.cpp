#include <iostream>
#include <vector>

int main(){
    size_t T, N, Q, a, b;
    size_t n = 0;
    std::cin >> T;

    for(size_t i = 0; i < T; ++i){
        std::cin >> N >> Q;
        std::vector<short> r(N);
        short* p = r.data();

        for(size_t j = 0; j < Q; ++j){
            std::cin >> a >> b;
            if(a > N)
                continue;

            short *p1, *p2;
            p1 = p2 = p + a - 1;
            *p1 = true;

            unsigned k;
            bool entered = false;

            if(a > N/2){
                for(k = a-1+b; k < N; k+=b){
                    entered = true;
                    p1+=b;
                    p2-=b;
                    *p1 = *p2 = true;
                }

                k += (entered) ? b : 0;
                
                for(;k < 2 * a; k+=b){
                    p2 -= b;
                    *p2 = true;
                }
            }
            else{
                for(k = a-1+b; k < 2*a; k+=b){
                    entered = true;
                    p1+=b;
                    p2-=b;
                    *p1 = *p2 = true;
                }

                k += (entered) ? b : 0;

                for(;k < N; k+=b){
                    p1 += b;
                    *p1 = true;
                }
            }

        }

        std::cout << "Case " << ++n << ":";
        for(const auto & aux : r)
            std::cout << " " << aux;
        std::cout << std::endl;
    }

    return 0;
}