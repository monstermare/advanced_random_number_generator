#!/usr/bin/env python

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
