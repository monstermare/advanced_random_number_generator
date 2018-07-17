#!/usr/bin/env python

import time

class LCG():
    m = 55
    a = 7
    c = 3

    def __init__(self, seed):
        self.prev = seed
        
    def rand(self):
        self.prev = (self.a*self.prev+self.c)%self.m
        return self.prev 

testing = LCG(2)
while(1):
    print testing.rand()
    time.sleep(1)
