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

`Neural_Network` is the class that manages the network interactions. It creates its neurons (as described in `Class_Neuron`) and simulates the synaptic interactions among them, generating a correlated activity of the mps. This correlation can be introduced in two (non mutually esclusive) ways:

* __Correlated noise__ : The Wiener processes driving the neurons are correlated. This correlation is introduced through a covariance matrix `R` whose element `r_ij` represent the correlation coefficient of the noise between the i-th and the j-th neuron. The diagonal elements should always be set to one, since the variance of the the noise is controlled by the parameter `sigma`. Moreove `R` must be diagonal.

* __Jump diffusion__ : Every times a neurons _fires_ (i.e. it reaches the threshold), other neurons in the networks may get excited or inhibited by its activity. This is econded in a matrix `H` whose element `h_ij` represent the variation in the activity that the j-th neuron undergoes whenever the i-th neuron fires. So h_ij > 0 means an exitatory linkage, while h_ij < 0 will result in an inibition. A null value simply signifies that the neurons are not connected. Since excitations and inhibitation are (in general) non-mutual, the matrix 'H' do not have to be symmetrical. Its diagonal elements represent self excitations ( or inhibitions), but are usually set to zero.

## First Passage Times (FPTs)


## Spike Trains (STs)


## Essential bibliography

* [1] Sacerdote, L., & Giraudo, M. T. (2013). *Stochastic integrate and fire models: a review on mathematical methods and their applications*. In Stochastic biomathematical models (pp. 99-148). Springer, Berlin, Heidelberg.

