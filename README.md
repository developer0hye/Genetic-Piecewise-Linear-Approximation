# Genetic Piecewise Linear Approximation

**GPLA**(Genetic Piecewise Linear Approximation) is the method to search automatically optimal linear pieces using **GA**(Genetic Algorithm), when using **PLA**(Piecewise Linear Approximation) algorithm to approximate a function.

To understand **GPLA**, you should know **PLA**.

## Piecewise Linear Approximation

**PLA** is one method to approximate a single valued function of one variable in terms of a sequence of linear pieces.

<p align="center"><img src="./figures/fig1_example_of_pla.png" width="40%"></p>

<p align="center">Figure 1. A function (blue) and a piecewise linear approximation to it (red).</p>


### Limitations of PLA

Obviously, a function can be approximated almost perfectly using PLA, if we use an infinite number of linear pieces to fit the curve with an infinite memory. However, the memory is finite.

So, it is important to decide **the proper number of linear pieces** and **the boundary of each piece** to approximate accurately a function.

In this project, I propose the method to search the boundary of each piece automatically using GA when the number of linear pieces is set manually.
