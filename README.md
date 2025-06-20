# floating_solid_simulation
[floating_solid.webm](https://github.com/user-attachments/assets/6415bb7f-1713-4d7a-ab18-2301a5ddcd78)


## PT - BR
Simulação de um cubo flutuando na água feita utilizando C++ e Python.

Cálculos realizados em C++ usando a classe criada "floating_solid_solver" que engloba os solucionadores analítico e numérico para o problema. O arquivo src/cpp/main.cpp utiliza da classe introduzida em src/cpp/main_solver.h e entra com os parâmetros para rodar a simulação desejada. O cálculo numérico é feito usando o método Runge Kutta de quarta ordem (RK4) enquanto que o método analítico calcula y do sólido a cada instante de tempo a partir da solução analítica encontrada a mão da EDO.

Após os cálculos, os resultados são armazenados na pasta "data" no devido arquivo ("analytical" ou "numerical") juntamente com um cabeçalho com os parâmetros passados anteriormente.

Por fim, os arquivos com a posição vertical do sólido ao longo do tempo são acessados via script Python e plotados em 3D utilizando a biblioteca visual VPython.

Para input de usuário fácil rodar o script src/python/main.py que perguntará por cada informação da simulação, então a calculará e em seguida mostrará o plot 3D.
IMPORTANTE: É necessário ter o compilador c++ "g++" instalado na sua máquina.

### Explicação Matemática

Um sólido dentro da água sofre ação de duas forças: Peso e Empuxo (Empuxo leva o objeto à superfície e Peso o afunda), essas devem somadas ser igual à força resultante na direção y (m - massa do sólido, $a_y$ - aceleração vertical do sólido, $\rho$ - densidade do fluido, g - aceleração da gravidade, V_d - volume do fluido deslocado):

$$F_r = E - P \implies m \cdot a_y = \rho \cdot g \cdot V_d - m \cdot g$$

Assim, é possível isolar a aceleração em y e obter a derivada dupla de y, que representa a derivada da velocidade de y, que já é suficiente para realizar o cálculo numérico do problema:

$$ a_y = \frac{\rho \cdot g \cdot V_d}{m} - g$$

Para resolver analiticamente, é preciso descrever o volume deslocado em função do y do centro do sólido. Sabendo que a altura da base do sólido é igual à altura do centro do sólido menos a metade da altura do sólido ($y_{base} = y - \frac{h}{2}$) e que $V_d = c \cdot l \cdot (h_{water} - y_{base})$:

$$ y'' = \frac{\rho \cdot g \cdot c \cdot l}{m} \cdot (h_{water} + \frac{h}{2}) - \frac{\rho \cdot g \cdot c \cdot l \cdot y}{m} - g$$

A partir disso assumimos que a solução da EDO é a soma da solução homogênea com uma solução particular. Para a homogênea teremos que $$y'' = - \frac{\rho \cdot g \cdot c \cdot l \cdot y}{m} \implies y_h = C_1 \cdot \cos \left(\sqrt{\frac{\rho \cdot g \cdot c \cdot l}{m}}t \right) + C_2 \cdot \sin\left(\sqrt{\frac{\rho \cdot g \cdot c \cdot l}{m}}t \right)$$

A solução particular se dá ao assumir que y é constante, assim: 
$$y_p = h_{water} + \frac{h}{2} - \frac{m}{\rho \cdot c \cdot l}$$

Por fim, são aplicadas as condições iniciais ($y(t=0) = y_0, y'(t=0) = vy_0$) e são encontrados os valores das constantes $C_1$ e $C_2$:

$$C_1 = y_0 + \frac{m}{\rho \cdot c \cdot l} - h_{water} - \frac{h}{2}$$ <br>
$$C_2 = \frac{vy_0}{\omega}$$
Onde: $\omega = \sqrt{\frac{\rho \cdot c \cdot g \cdot l}{m}}$


## EN
Simulation of a cube floating in water using C++ and Python.

Calculations performed in C++ using the class created "floating_solid_solver" which includes the analytical and numerical solvers for the problem. The src/cpp/main.cpp file uses the class introduced in src/cpp/main_solver.h and enters the parameters to run the desired simulation. The numerical calculation is done using the fourth order Runge Kutta method (RK4) while the analytical method calculates y of the solid at each instant of time from the analytical solution found manually from the ODE.

After the calculations, the results are stored in the "data" folder in the appropriate file ("analytical" or "numerical") along with a header with the parameters previously passed.

Finally, the files with the vertical position of the solid over time are accessed via Python script and plotted in 3D using the VPython visual library.

For easy user input run the main.py script which will ask for each simulation data, then calculate it
and then display the 3D plot.

IMPORTANT: You need to have the c++ compiler "g++" installed in your machine.

### Mathematical Explanation

A solid in water is affected by two forces: Weight and Buoyancy (Buoyancy brings the object to the surface and Weight sinks it), these must add up to equal the resultant force in the y direction (m - mass of the solid, $a_y$ - vertical acceleration of the solid, $\rho$ - density of the fluid, g - acceleration due to gravity, V_d - volume of the fluid displaced):

$$F_r = E - P \implies m \cdot a_y = \rho \cdot g \cdot V_d - m \cdot g$$

Thus, it is possible to isolate the acceleration in y and obtain the double derivative of y, which represents the derivative of the velocity of y, which is enough to perform the numerical calculation of the problem:

$$ a_y = \frac{\rho \cdot g \cdot V_d}{m} - g$$

To solve the problem analytically, we need to describe the displaced volume as a function of y from the center of the solid. Knowing that the height of the base of the solid is equal to the height of the center of the solid minus half the height of the solid ($y_{base} = y - \frac{h}{2}$) and that $V_d = w \cdot l \cdot (h_{water} - y_{base})$:

$$ y'' = \frac{\rho \cdot g \cdot w \cdot l}{m} \cdot (h_{water} + \frac{h}{2}) - \frac{\rho \cdot g \cdot w \cdot l \cdot y}{m} - g$$

From this we assume that the solution of the ODE is the sum of the homogeneous solution and a particular solution. For the homogeneous solution, $$y'' = - \frac{\rho \cdot g \cdot w \cdot l \cdot y}{m} \implies y_h = C_1 \cdot \cos \left(\sqrt{\frac{\rho \cdot g \cdot w \cdot l}{m}}t \right) + C_2 \cdot \sin\left(\sqrt{\frac{\rho \cdot g \cdot w \cdot l}{m}}t \right)$$

The particular solution is to assume that y is constant, thus: 
$$y_p = h_{water} + \frac{h}{2} - \frac{m}{\rho \cdot w \cdot l}$$

Finally, the initial conditions are applied ($y(t=0) = y_0, y'(t=0) = vy_0$) and the values of the constants $C_1$ and $C_2$ are found:

$$C_1 = y_0 + \frac{m}{\rho \cdot w \cdot l} - h_{water} - \frac{h}{2}$$ <br>
$$C_2 = \frac{vy_0}{\omega}$$
Where: $\omega = \sqrt{\frac{\rho \cdot w \cdot g \cdot l}{m}}$

## ES

Simulación de un cubo flotando en el agua utilizando C++ y Python.

Cálculos realizados en C++ utilizando la clase creada "floating_solid_solver" que incluye los resolvedores analítico y numérico para el problema. El fichero src/cpp/main.cpp utiliza la clase introducida en src/cpp/main_solver.h e introduce los parámetros para ejecutar la simulación deseada. El cálculo numérico se realiza utilizando el método Runge Kutta de cuarto orden (RK4) mientras que el método analítico calcula el y del sólido en cada instante de tiempo a partir de la solución analítica encontrada a mano de la EDO.

Despues de los cálculos, los resultados se almacenan en la carpeta "data" en el archivo apropiado ("analytical" o "numerical") junto con una cabecera con los parámetros previamente pasados.

Por último, se accede a los archivos con la posición vertical del sólido a lo largo del tiempo mediante un script de Python y se trazan en 3D utilizando la biblioteca visual VPython.

Para una entrada fácil del usuario, ejecute el script main.py, que pedirá cada dato de la simulación, lo calculará y mostrará el gráfico 3D.

IMPORTANTE: Debe tener instalado en su máquina el compilador de c++ "g++".

### Explicacion Matematica 

Un sólido en el agua se ve afectado por dos fuerzas: Peso y Empuje (el Empuje lleva el objeto a la superficie y el Peso lo hunde), estas deben sumarse para igualar la fuerza resultante en la dirección y (m - masa del sólido, $a_y$ - aceleración vertical del sólido, $\rho$ - densidad del fluido, g - aceleración debida a la gravedad, V_d - volumen del fluido desplazado):

$$F_r = E - P \implies m \cdot a_y = \rho \cdot g \cdot V_d - m \cdot g$$

Así, es posible aislar la aceleración en el y y obtener la doble derivada de y, que representa la derivada de la velocidad de y, que es suficiente para realizar el cálculo numérico del problema:

$$ a_y = \frac{\rho \cdot g \cdot V_d}{m} - g$$

Para resolver el problema analíticamente, necesitamos describir el volumen desplazado en función de y desde el centro del sólido. Sabiendo que la altura de la base del sólido es igual a la altura del centro del sólido menos la mitad de la altura del sólido ($y_{base} = y - \frac{h}{2}$) 
y que $V_d = a \cdot l \cdot (h_{agua} - y_{base})$:

$$ y'' = \frac{\rho \cdot g \cdot a \cdot l}{m} \cdot (h_{water} + \frac{h}{2}) - \frac{\rho \cdot g \cdot a \cdot l \cdot y}{m} - g$$

La solución particular es suponer que y es constante, así: 
$$y_p = h_{water} + \frac{h}{2} - \frac{m}{\rho \cdot a \cdot l}$$

Finalmente, se aplican las condiciones iniciales ($y(t=0) = y_0, y'(t=0) = vy_0$) y se hallan los valores de las constantes $C_1$ y $C_2$:

$$C_1 = y_0 + \frac{m}{\rho \cdot a \cdot l} - h_{water} - \frac{h}{2}$$ <br>
$$C_2 = \frac{vy_0}{\omega}$$
Donde: $\omega = \sqrt{\frac{\rho \cdot a \cdot g \cdot l}{m}}$