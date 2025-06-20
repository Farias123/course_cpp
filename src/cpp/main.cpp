#include "main_solver.h"


int main(int argc, char *argv[]){
    // 1- custom_values(bool), 2- y0, 3- v_y0, 4- simulation_time, 5- width, 6- length, 7- height, 8- cube_mass, 9- dt
    double x0, y0, z0, v_y0, simulation_time, width, length, height, cube_mass, dt;

    x0 = -5.0; 
    z0 = 5.0;
    //no difference in calculations

    if(argc > 1 && stoi(argv[1]) != 0){
        y0 = stod(argv[2]), v_y0 = stod(argv[3]);
        simulation_time = stod(argv[4]); //in seconds
        width = stod(argv[5]), length = stod(argv[6]), height = stod(argv[7]); //m
        cube_mass = stod(argv[8]); //kg
        dt = stod(argv[9]); 
    }else{
        //standard_values
        y0 = 2.0, v_y0 = -5.0;
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

