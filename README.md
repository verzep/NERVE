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
 

and are used by the function `step` to handle the evolution on the membrane potential over time according to an Ornstein-Uhlenbeck process, that reads:

(<a href="http://www.codecogs.com/eqnedit.php?latex=dX(t)&space;=&space;-(\frac{X(t)}{\tau}&space;&plus;&space;\mu)&space;dt&space;&plus;&space;\sigma&space;dW_t" target="_blank"><img src="http://latex.codecogs.com/gif.latex?dX(t)&space;=&space;-(\frac{X(t)}{\tau}&space;&plus;&space;\mu)&space;dt&space;&plus;&space;\sigma&space;dW_t" title="dX(t) = -(\frac{X(t)}{\tau} + \mu) dt + \sigma dW_t" /></a>)

where *X(t)* is the mp *W* is a standard Wiener process.

### Methods
To handle the evolution in time of the `mp` the class uses various methods, namely:

* `step( double noise)`: makes a single step forward in time, according to 
```
mp += (-(mp/theta) + mu) * dt  + noise*sigma * sqrt(dt)
```

* `jump(double he)`: makes the 'mp' jump of the amount `he`, i.e. 
```
mp += he 
``` 
* `reset()`: resets all the variables of the neuron (also the log)
* `spike()`: registers the spike time in `spikeTimes` and set the `mp` to 0. Moreover, it notifies the network that the neuron has spiked, using `NeuralNetwork.activity`


## Class_Neural_Network

Neurons are linked to each others.


## First Passage Times (FPTs)


## Spike Trains (STs)


## Essential bibliography

* [1] Sacerdote, L., & Giraudo, M. T. (2013). *Stochastic integrate and fire models: a review on mathematical methods and their applications*. In Stochastic biomathematical models (pp. 99-148). Springer, Berlin, Heidelberg.

