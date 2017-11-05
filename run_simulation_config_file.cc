#include "simulation.h"
#include <iostream>
#include "lattice_io.h"
#include "simulation_utility.h"
#include <sstream>
#include <sys/stat.h>

template <typename T> void value_save_config_string(std::ifstream& file, T& val) {
        std::string line;
        if(getline(file, line)){
                std::istringstream is{line};
                getline(is, val, '=');
                getline(is, val);
                return;
        };
};

template <typename T> void value_save_config(std::ifstream& file, T& val) {
        std::string line;
        if(getline(file, line)){
                std::istringstream is{line};
                std::string param;

                getline(is, param, '=');
                getline(is, param);
                std::istringstream iss{param};
                if((iss >> val) && !(iss >> param)){
                        return;
                };
                std::cerr << param << " is invalid input. Please edit file." << std::endl;
                exit(1);
        };
};

template <typename T> void check_sign_config(T& val) {
        if(val <= 0) {
                std::cerr << std::to_string(val) << " has the wrong sign. Please edit file" << std::endl;
                exit(1);
        };
        return;
};

int main() {
        std::cout << "Welcome to the KPZ simulation. Please type in the configuration file name:" << std::endl;
        std::string config_file;
        getline(std::cin, config_file);
        std::ifstream file(config_file);
        if(!file) {
                std::cerr << "File does not exist. Error." << std::endl;
                exit(1);
        };
        double Dx;
        value_save_config(file, Dx);
        double Dy;
        value_save_config(file, Dy);
        double Lx;
        value_save_config(file, Lx);
        double Ly;
        value_save_config(file, Ly);
        double cL;
        value_save_config(file ,cL);
        double dt;
        value_save_config(file, dt);
        check_sign_config(dt);
        int lat_size = 0;
        value_save_config(file, lat_size);
        std::cout << lat_size;
        check_sign_config(lat_size);
        int num_iter = 0;
        value_save_config(file, num_iter);
        check_sign_config(num_iter);
        int num_sim;
        value_save_config(file, num_sim);
        check_sign_config(num_sim);
        int num_save;
        value_save_config(file, num_save);
        check_sign_config(num_save);

        std::string cond_input;
        std::string init_cond = {"ordered"};
        
        
        value_save_config_string(file, cond_input);
        if(cond_input == "y") {
                init_cond = "disordered";
        };

        std::cout << "Please type the directory in which to save the simulation:" << std::endl;
        std::string directory;
        getline(std::cin, directory);
        check_dir(directory);

        parameters param(Dx, Dy, Lx, Ly, cL);
        sim_parameters sim_param(dt, num_iter, num_sim, num_save, init_cond);

        std::cout << "This is a simulation with parameters: Dx = " << Dx << ", Dy = " << Dy
                << ", Lx = " << Lx << ", Ly = " << Ly << ", cL = " << cL << std::endl;
        std::cout << "The simulation parameters are: timestep is " << dt << ", number of iterations is "
                << num_iter << ", the number of simulations is " << num_sim
                << ", and the number of iterations per save is " << num_save << std::endl;
        std::cout << "The initial condition is " << init_cond << " and the directory the files will be save in is "
        << directory << std::endl;

        multiple_simulate(lat_size, param, sim_param, directory);
};        
