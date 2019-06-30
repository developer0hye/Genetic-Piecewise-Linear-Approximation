# Genetic Piecewise Linear Approximation

**GPLA**(Genetic Piecewise Linear Approximation) is the method to search automatically optimal linear pieces using **GA**(genetic algorithm), when applying **PLA**(Piecewise Linear Approximation) algorithm for our applications.

To understand **GPLA**, you should know **PLA**.

## Piecewise Linear Approximation

**PLA** is one method to approximate a single valued function of one variable in terms of a sequence of linear pieces.

<p align="center"><img src="./figures/fig1_example_of_pla.png" width="40%"></p>

<p align="center">Figure 1. A function (blue) and a piecewise linear approximation to it (red).</p>


### Limitations of PLA

A function can be approximated perfectly using PLA, if we segment a function with an infinite number of linear pieces to fit the curve.

