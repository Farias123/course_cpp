#include <iostream>
#include <cmath>
#include <string>
#include <array>

using namespace std;

const double gravity_acceleration = 9.81;
double fluid_density = 997.0474; // kg/m^3 (water)

int main(){
    double x0, y0, z0, v_y0;
    double simulation_time = 10; //in seconds
    double width = 1, length = 1, height = 1, h_water = 0, cube_mass = 1;
    double dt = 1.0/60.0;

    floating_solid_solver solver(x0, y0, z0, v_y0, simulation_time, dt, width, length, height, h_water, cube_mass);

    return 0;
}

class floating_solid_solver{
    public:
        double x0, y0, z0, v_y0;
        double simulation_time, dt;
        double width, length, height, h_water, cube_mass;

        floating_solid_solver(double x0, double y0, double z0, double v_y0, double simulation_time, double dt, 
                              double width, double length, double height, double h_water, double cube_mass)
                              : y0(y0), v_y0(v_y0), simulation_time(simulation_time), dt(dt),
                                width(width), length(length), height(height), h_water(h_water), cube_mass(cube_mass){
                                    string header = "dt = " + to_string(dt) + "; x0 = " + to_string(x0) + "; z0 = " + 
                                    to_string(z0) + "; h_water = " + to_string(h_water) + "; cube_width = " + 
                                    to_string(width) + "; cube_length = " + to_string(length) + "; cube_height = " + 
                                    to_string(height) + ";";
                                }

        void solve_analytical(){
            int steps = simulation_time*60; //60 fps
            double t, y; //time in seconds, y coordinates in meters

            double omega = sqrt(fluid_density*gravity_acceleration*length*width/cube_mass);
            double c1 = y0 + cube_mass/(fluid_density*length*width) - h_water - height/2.0;
            double c2 = v_y0/omega;

            for(int i = 0; i < steps; i += 1){
                t = i/60.0;
                y = c1*cos(omega*t) + c2*sin(omega*t) + h_water + height/2.0 - cube_mass/(fluid_density*length*width);
                cout << y << endl;
            }

        }

        void solve_numerical(){
            int steps = simulation_time*60; //60 fps
            double r[steps][2];
            array<double, 2> k1, k2, k3, k4, temp_derivative;
            r[0][0] = y0;
            r[0][1] = v_y0;
            cout << r[0][0] << endl;

            for(int i = 1; i < steps; i += 1){
                temp_derivative = f_y(r[i-1]);
                k1 = {dt*temp_derivative[0], dt*temp_derivative[1]};

                temp_derivative = f_y({r[i-1][0] + k1[0]/2.0, r[i-1][1] + k1[1]/2.0});
                k2 = {dt*temp_derivative[0], dt*temp_derivative[1]};

                temp_derivative = f_y({r[i-1][0] + k2[0]/2.0, r[i-1][1] + k2[1]/2.0});
                k3 = {dt*temp_derivative[0], dt*temp_derivative[1]};
                
                temp_derivative = f_y({r[i-1][0] + k3[0], r[i-1][1] + k3[1]});
                k4 = {dt*temp_derivative[0], dt*temp_derivative[1]};

                r[i][0] = r[i-1][0] + 1.0/6.0*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0]);
                r[i][1] = r[i-1][1] + 1.0/6.0*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1]);
                cout << r[i][0] << endl;
            }

        }

        array<double, 2> f_y(double ri[2]){
            // returns derivative of input
            double y = ri[0], vy = ri[1];
            double ay = fluid_density*gravity_acceleration*length*width/cube_mass*(h_water + height/2.0 - y) - gravity_acceleration;
            
            return {vy, ay};
        }


};
