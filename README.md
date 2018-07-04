# The Advanced Pseudorandom Number Generator with Intel Edison

## Overview
For any programming, when we need to use a random number, we use 'rand' function that is commonly provided by default. We often _do believe_ that a number generated by random functions is a true random number (at least I did until I faced the truth). Sadly, that is not true.

## Background
A random number generator is essentially under the category of _Deterministic Finite Automaton_ (or simply say DFA). You could learn more about DFA or further stuff on the [Wikipedia](https://en.wikipedia.org/wiki/Deterministic_finite_automaton), but it is out of the scope of this work. The only thing we need to know is the most random functions generate _pseudoramdon number_ and the numbers generated can be predictable if we know what type of generator and input used! However, in reality, computer scientists invented awesome algorithms that makes pseudorandom numbers are almost impossible to predict in practice. Here is some algorithms for pseudorandom numbers has pretty good performance.

### Linear Congruential Generator
This is one of the common pseudorandom number generator. This is fast and lightweight. It requires minimal memory, but it also has some weakness like it is comparatively easier to predict. For more information, here is [Wikipedia link](https://en.wikipedia.org/wiki/Linear_congruential_generator) might be helpful.

In this project, we are going to use this method because it is pretty intuitive and easy to implement.
Note that there are many pseudorandom number generator has better performance and secure (like cryptographic pseudorandom number generator!), and of course, you can try different method whatever you want. Anyway, I think LCG is a good enough method for this project.

The method can be described as a closed-form expression like:

![equation](https://latex.codecogs.com/gif.latex?\fn_cm&space;X_{n&plus;1}=(aX_n&plus;c)\mod{m})

where a, c, and m are constant number satisfies the following conditions
	m > 0
	0 < a < m
	0 <= c < m

the seed number ![equation](https://latex.codecogs.com/gif.latex?\fn_phv&space;X_0) should be a non-zero natural number is smaller than m

In LCG, it is really important to pick a good number for those constants to have a maximum period length. As your gerenator gets larger period length, it would be harder to predict the numbers generated. You can calculate the best combinations for practice, but I will just pick one of the combinations listed on the wikipedia for convenience.
	m = 281,474,976,710,656
	a = 25,214,903,917
	c = 11

So now we get everything we need to implement the LCG. Let's see if it is working nicely by using Python.
```python
s = "python syntax highlighting"
print s
```
