from time import sleep
from vpython import box, vector, color, scene, canvas


def parse_header(header):
    data = header.split(";")
    data = [x.split(" = ") for x in data]

    data_dict = {}
    for k, v in data:
        data_dict[str.strip(k)] = float(v)
    return data_dict

def main(y_data_file):
    mycanvas = canvas()
    mycanvas.select()
    mycanvas.background = color.white

    with open(y_data_file) as file:
        content = file.read().split("\n")

    header = content[0]
    params = parse_header(header)
    y_list = [float(x) for x in content[1:]]


    water = box(pos=vector(0, - params.get("cube_height")*10000/2, 0), length=params.get("cube_length")*10000, height=params.get("cube_height")*10000, width=params.get("cube_width")*10000, color=color.blue, opacity=0.4)
    # water height -water_cube_height/2 in order for surface to be on h_water height

    solid = box(pos=vector(params.get("x0"), y_list[0], params.get("z0")), length=params.get("cube_length"),
                height=params.get("cube_height"), width=params.get("cube_width"), color=color.red)

    mycanvas.center = vector(-5, 2, 5)
    mycanvas.forward = vector(-8.61595, -2.73272, 6.87733)
    mycanvas.range = 22.96683
    # TODO melhorar câmera

    dt = params.get("dt")
    for y in y_list:
        solid.pos.y = y
        sleep(dt)

    mycanvas.visible = False

if __name__ == "__main__":
    main("./y_positions_calculated/numerical_solution.txt")

