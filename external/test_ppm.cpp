



#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>

#include "json.hpp"
#include "simpleppm.h"

#include <sstream>

using namespace std;
using namespace nlohmann;


int test_save_ppm(){
    int dimx = 800;
    int dimy = 600;
    
    int w = 100;
    
    std::vector<double> buffer(3*dimx*dimy);
    for(int j=0;j<dimy;++j){
        for(int i=0;i<dimx;++i){
            double value = (double)j / dimy;

            buffer[3*j*dimx+3*i+0]= value;
            buffer[3*j*dimx+3*i+1]= value;
            buffer[3*j*dimx+3*i+2]= value;
        }
    }
               
             
    save_ppm("test.ppm", buffer, dimx, dimy);
    
    return 0;
}
