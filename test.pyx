import cppyy
cppyy.cppdef(
"""
    class MyClass
{
public:
    MyClass(){

    }
    ~MyClass(){

    }

    int add(int a, int b){
        return a + b;
    }
};
"""
)

from cppyy.gbl import MyClass

class MyClassEdited(MyClass):
    def add(a, b):
        # sub
        return a - b

cdef public object createMyClass():
    return MyClassEdited()