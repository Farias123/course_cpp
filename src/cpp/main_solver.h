#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <array>
#include <chrono>

using namespace std;
using namespace std::chrono;

const double gravity_acceleration = 9.81;
double fluid_density = 997.0474; // kg/m^3 (water)

class floating_solid_solver{
    public:
        double x0, y0, z0, v_y0;
        double simulation_time, dt;
        double width, length, height, cube_mass;
        string header;

        floating_solid_solver(double x0, double y0, double z0, double v_y0, double simulation_time, double dt, 
                              double width, double length, double height, double cube_mass)
                              : y0(y0), v_y0(v_y0), simulation_time(simulation_time), dt(dt),
                                width(width), length(length), height(height), cube_mass(cube_mass){
                                    header = "dt = " + to_string(dt) + "; x0 = " + to_string(x0) + "; z0 = " + 
                                    to_string(z0) + "; cube_width = " + to_string(width) + "; cube_length = " +  
                                    to_string(length) + "; cube_height = " + to_string(height) + "; cube_mass = " 
                                    + to_string(cube_mass);
                                }

        void solve_analytical(){
            auto start = high_resolution_clock::now();

            int steps = simulation_time/dt;
            double t, y; //time in seconds, y coordinates in meters
            string y_points_string = "";

            double omega = sqrt(fluid_density*gravity_acceleration*length*width/cube_mass);
            double c1 = y0 + cube_mass/(fluid_density*length*width) - height/2.0;
            double c2 = v_y0/omega;

            ofstream analytical_solution_file("../../data/analytical_solution.txt");

            for(int i = 0; i < steps; i += 1){
                t = i*dt;
                y = c1*cos(omega*t) + c2*sin(omega*t) + height/2.0 - cube_mass/(fluid_density*length*width);
                y_points_string += to_string(y);
                if( i != steps - 1){
                    y_points_string += "\n";
                }
            }

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            
            analytical_solution_file << "calculation_time(ms) = " + to_string(duration.count()) + "; ";
            analytical_solution_file << header << endl << y_points_string;
            analytical_solution_file.close();

        }

        void solve_numerical(){
            auto start = high_resolution_clock::now();

            int steps = simulation_time/dt;
            double y_list[steps], vy_list[steps];
            array<double, 2> k1, k2, k3, k4, temp_derivative;

            y_list[0] = y0;
            vy_list[0] = v_y0;
            string y_points_string = "";

            ofstream numerical_solution_file("../../data/numerical_solution.txt");

            for(int i = 1; i < steps; i += 1){
                temp_derivative = f_y(y_list[i-1], vy_list[i-1]);
                k1 = {dt*temp_derivative[0], dt*temp_derivative[1]};

                temp_derivative = f_y(y_list[i-1] + k1[0]/2.0, vy_list[i-1] + k1[1]/2.0);
                k2 = {dt*temp_derivative[0], dt*temp_derivative[1]};

                temp_derivative = f_y(y_list[i-1] + k2[0]/2.0, vy_list[i-1] + k2[1]/2.0);
                k3 = {dt*temp_derivative[0], dt*temp_derivative[1]};
                
                temp_derivative = f_y(y_list[i-1] + k3[0], vy_list[i-1] + k3[1]);
                k4 = {dt*temp_derivative[0], dt*temp_derivative[1]};

                y_list[i] = y_list[i-1] + 1.0/6.0*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0]);
                vy_list[i] = vy_list[i-1] + 1.0/6.0*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1]);
                y_points_string += to_string(y_list[i]);

                if( i != steps - 1){
                    y_points_string += "\n";
                }
            }

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            
            numerical_solution_file << "calculation_time(ms) = " + to_string(duration.count()) + "; " 
                                    << header << endl << to_string(y0) << endl << y_points_string;
            numerical_solution_file.close();

        }

        array<double, 2> f_y(double y, double vy){
            // returns derivative of input
            
            double fluid_volume_displaced = length*width*(height/2.0 - y);
            fluid_volume_displaced = fix_volume_displaced(fluid_volume_displaced);
            double ay = fluid_density*gravity_acceleration*fluid_volume_displaced/cube_mass - gravity_acceleration;
            // ma = E - P -> a = d*g*V/m - g
            
            return {vy, ay};
        }

        double fix_volume_displaced(double volume_displaced){
            //correction for two cases(1- solid completely under the water, 2- solid completely out of water)
            if(volume_displaced > width*length*height){
                volume_displaced = width*length*height;
            }
            if(volume_displaced < 0){
                volume_displaced = 0;
            }
            return volume_displaced;
        }
};

