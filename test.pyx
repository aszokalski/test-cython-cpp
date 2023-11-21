import cppyy
cppyy.cppdef(
"""
    class MyClass
{
public:
    MyClass(){

    }
    virtual ~MyClass(){

    }

    virtual int add(int a, int b){
        return a + b;
    }
};
"""
)

from cppyy.gbl import MyClass

class MyClassAltered(MyClass):
    def add(self, a, b):
        return a + b + 1

cdef public object createMyClass():
    return MyClassAltered()