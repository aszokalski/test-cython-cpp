import numpy as np
class MyClass:
    def add(self, a, b):
        return np.add(a, b)
    def sub(self, a, b):
        return a - b

cdef public object createMyClass():
    return MyClass()