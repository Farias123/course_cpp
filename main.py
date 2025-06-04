import subprocess
import animate


def full_process():
    # TODO capture output
    subprocess.run(["g++", "./main.cpp", "-o",  "main"], capture_output=True, text=True)

    while True:
        execute_cpp_calculations()

        file = choose_data_file()
        animate.main(file)

        print("Do you want to do another simulation (y or n):")
        user_input = input(">")

        if str.lower(user_input) == 'y':
            continue
        else:
            break


def execute_cpp_calculations():
    print("Would you like to choose custom values for the simulation (y or n):")
    user_input = input('>')

    if str.lower(user_input) == 'y':
        param_names = ["initial y", "initial y speed", "simulation time (in seconds)", "solid width",
                       "solid length", "solid height", "cube mass", "dt"]
        params = ["./main", "1"]

        for param_name in param_names:
            print(f"Enter {param_name}:")
            param_entered = input()
            params.append(param_entered)

        output = subprocess.run(params, capture_output=True, text=True)
    else:
        output = subprocess.run(["./main"], capture_output=True, text=True)

    return output


def choose_data_file():
    print("""The analytical method has a perfect solution but should only be used for simple cases (when the solid is 
never completely under or out of the water), whereas the numerical method is an approximation of the solution that 
works for more complex cases but diverges if the interval dt is not small enough.""")

    while True:
        print("You want to watch the numerical(1) or analytical(2) solution?")
        user_input = int(input('>'))

        if user_input == 1:
            return "./y_positions_calculated/numerical_solution.txt"

        elif user_input == 2:
            return "./y_positions_calculated/analytical_solution.txt"

        print("Not a valid choice")


if __name__ == "__main__":
    full_process()
