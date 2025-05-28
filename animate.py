from time import sleep
from vpython import box, vector, color, scene

def parse_header(header):
    data = header.split(";")
    data = [x.split(" = ") for x in data]

    data_dict = {}
    for k, v in data:
        data_dict[str.strip(k)] = float(v)
    return data_dict

def main():
    scene.background = color.white


    with open("./y_positions_calculated/analytical_solution.txt") as file:
        content = file.read().split("\n")

    header = content[0]
    params = parse_header(header)
    y_list = [float(x) for x in content[1:]]



    water = box(pos=vector(0, params.get("h_water") - params.get("cube_height")*5/2, 0), length=50, height=params.get("cube_height")*5, width=50, color=color.blue, opacity=0.4)
    # water height -water_cube_height/2 in order for surface to be on h_water height

    solid = box(pos=vector(params.get("x0"), y_list[0], params.get("z0")), length=params.get("cube_length"),
                height=params.get("cube_height"), width=params.get("cube_width"), color=color.red)

    scene.center = vector(-5, 2, 5)
    scene.forward = vector(-8.61595, -2.73272, 6.87733)
    scene.range = 22.96683
    # TODO melhorar câmera
    # TODO plotar ambos os cálculos e mostrar o tempo que cada um demorou para ser calculado

    dt = params.get("dt")
    for y in y_list:
        sleep(dt)
        solid.pos.y = y

if __name__ == "__main__":
    main()

