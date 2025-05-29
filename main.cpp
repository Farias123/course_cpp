#include "main_solver.h"


int main(){
    double x0 = -5.0, y0 = 2.0, z0 = 5.0, v_y0 = -5.0;
    double simulation_time = 30.0; //in seconds
    double width = 10.0, length = 10.0, height = 10.0, h_water = 0.0; //m
    double cube_mass = 300*1000; //kg (simulation for coal)
    double dt = 1.0/60.0;
    
    floating_solid_solver solver(x0, y0, z0, v_y0, simulation_time, dt, width, length, height, h_water, cube_mass);

    solver.solve_numerical();
    solver.solve_analytical();

    return 0;
}

