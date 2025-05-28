# floating_solid_simulation
[floating_solid.webm](https://github.com/user-attachments/assets/6415bb7f-1713-4d7a-ab18-2301a5ddcd78)


## PT - BR
Simulação de um cubo flutuando na água feita utilizando C++ e Python.

Cálculos realizados em C++ usando a classe criada "floating_solid_solver" que engloba os solucionadores analítico e 
numérico para o problema. O arquivo main.cpp utiliza da classe introduzida em main_solver.h e entra com os parâmetros
para rodar a simulação desejada. O cálculo numérico é feito usando o método Runge Kutta de quarta ordem (RK4) enquanto
que o método analítico calcula y do sólido a cada instante de tempo a partir da solução analítica encontrada a mão da EDO.

Após os cálculos, os resultados são armazenados na pasta "y_positions_calculated" no devido arquivo ("analytical" ou 
"numerical") juntamente com um cabeçalho com os parâmetros passados anteriormente.

Por fim, os arquivos com a posição vertical do sólido ao longo do tempo são acessados via script Python e plotados em 3D
utilizando a biblioteca visual VPython.

### Explicação Matemática

Um sólido dentro da água sofre ação de duas forças: Peso e Empuxo (Empuxo leva o objeto à superfície e Peso o afunda), 
essas devem somadas ser igual à força resultante na direção y (m - massa do sólido, $a_y$ - aceleração vertical do sólido, 
$\rho$ - densidade do fluido, g - aceleração da gravidade, V_d - volume do fluido deslocado):

$$F_r = E - P \implies m \cdot a_y = \rho \cdot g \cdot V_d - m \cdot g$$

Assim, é possível isolar a aceleração em y e obter a derivada dupla de y, que representa a derivada da velocidade de y,
que já é suficiente para realizar o cálculo numérico do problema:

$$ a_y = \frac{\rho \cdot g \cdot V_d}{m} - g$$

Para resolver analiticamente, é preciso descrever o volume deslocado em função do y do centro do sólido. Sabendo que a 
altura da base do sólido é igual à altura do centro do sólido menos a metade da altura do sólido ($y_{base} = y - \frac{h}{2}$) 
e que $V_d = c \cdot l \cdot (h_{water} - y_{base})$:

$$ y'' = \frac{\rho \cdot g \cdot c \cdot l}{m} \cdot (h_{water} + \frac{h}{2}) - \frac{\rho \cdot g \cdot c \cdot l \cdot y}{m} - g$$

A partir disso assumimos que a solução da EDO é a soma da solução homogênea com uma solução particular. Para a homogênea
teremos que $$y'' = - \frac{\rho \cdot g \cdot c \cdot l \cdot y}{m} \implies y_h = 
C_1 \cdot \cos \left(\sqrt{\frac{\rho \cdot g \cdot c \cdot l}{m}}t \right) + C_2 \cdot \sin\left(\sqrt{\frac{\rho \cdot g \cdot c \cdot l}{m}}t \right)$$

A solução particular se dá ao assumir que y é constante, assim: 
$$y_p = h_{water} + \frac{h}{2} - \frac{m}{\rho \cdot c \cdot l}$$

Por fim, são aplicadas as condições iniciais ($y(t=0) = y_0, y'(t=0) = vy_0$) e são encontrados os valores das constantes 
$C_1$ e $C_2$:

$$C_1 = y_0 + \frac{m}{\rho \cdot c \cdot l} - h_{water} - \frac{h}{2}$$ <br>
$$C_2 = \frac{vy_0}{\omega}$$
Onde: $\omega = \sqrt{\frac{\rho \cdot c \cdot g \cdot l}{m}}$
