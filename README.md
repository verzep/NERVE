# Neural Environment for Random Variable Estimation (NERVE)

### By Pietro Verzelli


This is is a C++ code implementing two classes (`NeuralNetwork` and `Neuron`) to simulate the activity of a small neural network, generating Spike Trains (STs). Neurons' activity is simulated evolving their membrane potentials (MPs), modeled as a stochastic process. Connections among neurons may be introduced, creating a (small) neural network (NN) which allows neurons to communicate via spikes. The theory behind the stochastic modeling of neuronal activity can be found in [1]:


**NOTE: this script is for C++11**

## Introduction

The programs consists of the following parts

- `class_Neuron` : is used to implement istances of `Neuron` (`.h` is the header file while `.cpp` is the implementation)
- `class_NeuralNetwork` : is used to implement istances of `NeuralNetwork` (`.h` is the header file while `.cpp` is the implementation)
- `class_statistic`: contains some useful functions, used in the earlier versions of the code (`.h` is the header file while `.cpp` is the implementation)

## Class_Neuron

The most basic element of a neural network is the `Neuron`. We study the evolution of its membrane potential `mp` over `time`. Each neuron behavior is regulated by the influence of other neurons (that is going to be described in the next section) and by some parameters that characterize it. Those are:

* `sigma`: is the noise intensity;
* `theta`: is the time constant ;
* `mu`: is the drift;
* `C`: is the threshold;
 

and are used by the function `step` to handle the evolution on the membrane potential over time according to an Ornstein-Uhlenbeck (it's spelled right, I googled it) process, that reads:

<a href="http://www.codecogs.com/eqnedit.php?latex=dX(t)&space;=&space;-(\frac{X(t)}{\tau}&space;&plus;&space;\mu)&space;dt&space;&plus;&space;\sigma&space;dW_t" target="_blank"><img src="http://latex.codecogs.com/gif.latex?dX(t)&space;=&space;-(\frac{X(t)}{\tau}&space;&plus;&space;\mu)&space;dt&space;&plus;&space;\sigma&space;dW_t" title="dX(t) = -(\frac{X(t)}{\tau} + \mu) dt + \sigma dW_t" /></a>

where *X(t)* is the mp *W* is a standard Wiener process.

### Methods
To handle the evolution in time of the `mp` the class uses various methods, namely:

* `step( double noise)`: makes a single step forward in time, according to 
```C++
mp += (-(mp/theta) + mu) * dt  + noise*sigma * sqrt(dt)
```

* `jump(double he)`: makes the `mp` jump of the amount `he`, i.e. `mp += he` 

* `reset()`: resets all the variables of the neuron (also the log)
* `spike()`: registers the spike time in `spikeTimes` and set the `mp` to 0. Moreover, it notifies the network that the neuron has spiked, using `NeuralNetwork.activity`


## Class_Neural_Network

`Neural_Network` is the class that manages the network interactions. It creates its neurons (as described in `Class_Neuron`) and simulates the synaptic interactions among them, generating a correlated activity of the mps. 

The constructor `NeuralNetwork(int numNeur, double mu, double sigma, double theta, double C);` will require the number of neurons in the network (`numNeur`) and all the parameters needed to construct a single neuron, described in the section above. Note that in this way *all* the neurons will have the same parameters. To change any parameter of a single neuron, you can use specific setters implemented in the class `Neuron`).

This correlation among neurons can be introduced in two (non mutually esclusive) ways:

* __Correlated noise__ : The Wiener processes driving the neurons are correlated. This correlation is introduced through a covariance matrix `R` whose element `r_ij` represent the correlation coefficient of the noise between the i-th and the j-th neuron. The diagonal elements should always be set to one, since the variance of the the noise is controlled by the parameter `sigma`. Moreove `R` must be diagonal.

* __Jump diffusion__ : Every times a neurons _fires_ (i.e. it reaches the threshold), other neurons in the networks may get excited or inhibited by its activity. This is econded in a matrix `H` whose element `h_ij` represent the variation in the activity that the j-th neuron undergoes whenever the i-th neuron fires. So h_ij > 0 means an exitatory linkage, while h_ij < 0 will result in an inibition. A null value simply signifies that the neurons are not connected. Since excitations and inhibitation are (in general) non-mutual, the matrix 'H' do not have to be symmetrical. Its diagonal elements represent self excitations ( or inhibitions), but are usually set to zero.

## First Passage Times (FPTs)

The method `FPT( int NData)` is used to generate First passage times. It will generate `NData` samples. 
After that, you need to use the method `writeSpikeTimes_FPT()` to print them on a file, on which each column will contain all the FPTs of a neuron. The method can take the name of the file as argument and if not present, it will ask for that tame. 


## Spike Trains (STs)
The method `spikeTrain(double Tmax, bool save)` is used to generate spike trains. Note that the argument is the time `Tmax` that the system will have to evolve, so that in this case you cannot know in advance how many samples the system will generate. Note also that it is not guranteed (and, in almost every case, won't be) that each neuron will have the same number of samples. The parameter `save`, if set true, will make the network save every step of the evolution: this is really memory consuming and should be used only for debugging porpouses (or if you want to plot the time evolution).
To save the data on a file you have to use `writeSpikeTimes_ST()`, which works exactly the same way as the FPT one.

## Code Example
In the file `main.cpp` you can find an example of the code I used for the simulation. It will produce an FPT experiment by default, but you should be able to modify it almost effortless.
To run run, I suggest that you first compile the libraries by tiping on your terminal:

```
g++ -std=c++11 -c Class_Neuron.cpp Class_NeuralNetwork.cpp statistic.cpp
```
So that you don't have to recompile it every time. If you want to run an experiment, you can compile the main file (after modifying it, if needed)

```
g++ -std=c++11 Class_Neuron.o Class_NeuralNetwork.o statistic.o main.cpp -o EXP.out
```
and then run the experiment

```
./EXP.out
```

## Essential bibliography

* [1] Sacerdote, L., & Giraudo, M. T. (2013). *Stochastic integrate and fire models: a review on mathematical methods and their applications*. In Stochastic biomathematical models (pp. 99-148). Springer, Berlin, Heidelberg.

