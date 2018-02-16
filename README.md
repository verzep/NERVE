# Neural Environment for Random Variable Estimation (NERVE)

### By Pietro Verzelli


This is is a C++ code implementing two classes (`NeuralNetwork` and `Neuron`) to simulate the activity of a small neural network, generating Spike Trains (STs). Neurons' activity is simulated evolving their membrane potentials (MPs), modeled as a stochastic process. Connections among neurons may be introduced, creating a (small) neural network (NN) which allows neurons to communicate via spikes. The theory behind the stochastic modeling of neuronal activity can be found in [1]:


**NOTE: this script is for C++11**

## Introduction

The programs consists of the following parts

- `class_Neuron` : is used to implement istances of `Neuron` (`.h` is the header file while `.cpp` is the implementation)
- `class_NeuralNetwork` : is used to implement istances of `NeuralNetwork` (`.h` is the header file while `.cpp` is the implementation)
- `class_statistic`: contains some useful functions, used in the earlier versions of the code (`.h` is the header file while `.cpp` is the implementation)

##Class_Neron






The most basic element of a neural network is the `Neuron`. We study the evolution of its membrane potential `mp` over `time`. Each neuron behavior is regulated by the influence of other neurons (that is going to be described in the next section) and by some parameters that characterize it. Those are:

* `sigma`: is the noise intensity;
* `theta`: is the time constant ;
* `mu`: is the drift;
* `C`: is the threshold;
 
and are used by the function `step()` to handle the evolution on the membrane potential over time according to an Ornstein-Uhlenbeck process.



## Essential bibliography

* [1] Sacerdote, L., & Giraudo, M. T. (2013). *Stochastic integrate and fire models: a review on mathematical methods and their applications*. In Stochastic biomathematical models (pp. 99-148). Springer, Berlin, Heidelberg.

