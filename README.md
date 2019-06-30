# Genetic Piecewise Linear Approximation

**GPLA**(Genetic Piecewise Linear Approximation) is the method to search automatically optimal linear pieces using **GA**(genetic algorithm), when applying **PLA**(Piecewise Linear Approximation) algorithm for our applications.

To understand **GPLA**, you should know **PLA**.

## Piecewise Linear Approximation

**PLA** is one method to approximate a single valued function of one variable in terms of a sequence of linear pieces.

![figure1_example_of_pla](https://user-images.githubusercontent.com/35001605/60399341-14f13180-9b9e-11e9-8ddd-e79f65e61476.png)

Figure 1. **A function (blue) and a piecewise linear approximation to it (red).**

### Limitations

PLA creates its own optimization problem. 

Obviously the best PLA would use an infinite number of linear pieces to fit the curve. 


