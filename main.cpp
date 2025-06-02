#include "main_solver.h"


int main(int argc, char *argv[]){
    // 1- custom_values(bool), 2- x0, 3- y0, 4- z0, 5- v_y0, 6- simulation_time, 7- width, 8- length, 9- height, 10- cube_mass, 11- dt
    double x0, y0, z0, v_y0, simulation_time, width, length, height, cube_mass, dt;

    if(argc > 1 && stoi(argv[1]) != 0){
        x0 = stod(argv[2]), y0 = stod(argv[3]), z0 = stod(argv[4]), v_y0 = stod(argv[5]);
        simulation_time = stod(argv[6]); //in seconds
        width = stod(argv[7]), length = stod(argv[8]), height = stod(argv[9]); //m
        cube_mass = stod(argv[10]); //kg
        dt = stod(argv[11]); 
    }else{
        //standard_values
        x0 = -5.0, y0 = 2.0, z0 = 5.0, v_y0 = -5.0;
        simulation_time = 30.0; //in seconds
        width = 10.0, length = 10.0, height = 10.0; //m
        cube_mass = 300*1000; //kg (simulation for coal)
        dt = 1.0/60.0;
    }

    
    floating_solid_solver solver(x0, y0, z0, v_y0, simulation_time, dt, width, length, height, cube_mass);

    solver.solve_numerical();
    solver.solve_analytical();

    return 0;
}

