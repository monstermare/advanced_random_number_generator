# The Advanced Random Number Generator with Intel Edison

## Overview
For any programming, when we need to use a random number, we use 'rand' function that is commonly provided by default. We often _do believe_ that a number generated by random functions is a true random number (at least I did until I faced the truth). Sadly, that is not true.

## Background
A random number generator is essentially under the category of _Deterministic Finite Automaton_ (or simply say DFA). You could learn more about DFA or further stuff on the [Wikipedia](https://en.wikipedia.org/wiki/Deterministic_finite_automaton), but it is out of the scope of this work. The only thing we need to know is the most random functions generate _pseudoramdon number_ and the numbers generated can be predictable if we know what type of generator and input used! However, in reality, computer scientists invented awesome algorithms that makes pseudorandom numbers are almost impossible to predict in practice. Here is some algorithms for pseudorandom numbers has pretty good performance.

### Linear Congruential Generator
This is one of the common pseudorandom number generator. This is fast and lightweight. It requires minimal memory, but it also has some weakness like cryptographic issue. For more information, here is [Wikipedia link](https://en.wikipedia.org/wiki/Linear_congruential_generator) might be helpful.

In this project, we are going to use this method because it is pretty intuitive and easy to implement.
However, there are many pseudorandom number generator has better performance and secure (like cryptographic pseudorandom number generator!), and of course, you can try different method whatever you want.

The method can be described as a closed-form expression like:

![equation](https://latex.codecogs.com/gif.latex?\fn_cm&space;X_{n&plus;1}=(aX_n&plus;c)\mod{m})

where a, c, and m are constant number satisfies the following conditions
>m > 0\
>0 < a < m\
>0 <= c < m


the seed number ![equation](https://latex.codecogs.com/gif.latex?\fn_phv&space;X_0) should be a non-zero natural number and smaller than m

In LCG, it is really important to pick a good number for those constants to have a maximum period length. As your gerenator gets larger period length, it would be harder to predict the numbers generated. You can calculate the best combinations for practice, but I will just pick one of the combinations listed on the wikipedia for convenience.
>m = 281,474,976,710,656\
>a = 25,214,903,917\
>c = 11


So now we get everything we need for developing the LCG, and here is the sample code that outputs random numbers to check if it is working nicely.
```python
import time

class LCG():
    m = 281474976710656
    a = 25214903917
    c = 11

    def __init__(self, seed):
        self.prev = seed
        
    def rand(self):
        self.prev = (self.a*self.prev+self.c)%self.m
        return self.prev 

testing = LCG(24)
while(1):
    print testing.rand()
    time.sleep(1)
```

If you run this code, you will see it nicely outputs random numbers.

## The Advanced Random Number Generator
As we discussed above, the LCG has limitation that the numbers can be predictable. Technically, if you have a good computer (like supercomputer!), sequence of the generated numbers, and an appropriate algorithm, you can find the seed number. This is not only LCG's limitation but all of pseudorandom number generators. Some might be harder to predict (or almost impossible with the current technology), but theoretically, every pseudorandom numbers can be predictable.\
Then is it really impossible to make a true random number? Well, if we define the randomness is the one that cannot be predictable, it is actually possible to generate a true random number!\

### Noise
The noise is pretty common stuff. When you're listening music, changing radio station, or speaking over the phone, you could hear the noise. Noise is somewhat unpredictable. The idea starts from here; if we can use those noise for the random numbers, the numbers generated will be unpredictable, too.\
As long as you are able to get those noise, you can make true random numbers by your own, and that is why we're going to use Intel Edison.

### Intel Edison
The Intel Edison is a single board computer (SBC) announced in 2014. With the breakout board, you can use various modules and sensors with powerful cpu for a SBC.
I will use this to measure a noise with sensors. However, if you don't have Edison but other SBCs like raspberry pi or Alduino, it is welcome to use it.
I believe using raspberry pi would be easier and more intuitive, but I use Edison because I don't have micro-sd card on my raspberry pi right now :D

#### Preperation

