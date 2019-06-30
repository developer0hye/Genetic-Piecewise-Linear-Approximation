# Genetic Piecewise Linear Approximation

**GPLA**(Genetic Piecewise Linear Approximation) is the method to search automatically optimal linear pieces using **GA**(genetic algorithm), when applying **PLA**(Piecewise Linear Approximation) algorithm for our applications.

To understand **GPLA**, you should know **PLA**.

## Piecewise Linear Approximation

**PLA** is one method to approximate a single valude function of one variable in terms of a sequence of linear segments.

![figure1_example_of_pla](https://user-images.githubusercontent.com/35001605/60398737-c1c7b080-9b96-11e9-9f17-d90016a6ab61.png)

Figure 1. **A function (blue) and a piecewise linear approximation to it (red).**


### Limitations

Creating a PLA creates its own optimization problem. 

Obviously the best PLA would use an infinite number of linear pieces to fit the curve.


