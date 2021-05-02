/*
 * Copyright (c) 2021
 *
 * (No memory leaks! -- verified by valgrind)
 *
 * An attempt to REALLY understand how copy constructors
 * work and how they differ from assignment operator
 * overloading.
 *
 * This program helps me codify WHY I was so darn confused
 * about copy constructors and the Rule of Three.
 * It is because, when `=` is used for an object variable
 * in the same statement as its declaration, it calls the
 * COPY Constructor and not the assignment operator,
 * despite using the `=` syntax.
 *
 * This probably makes sense, because an object needs to be
 * fully constructed before its member functions can be
 * called; but it's still very important to understand when
 * syntax (the same exact syntactical key) can be
 * overloaded to do different things in different contexts.
 *
 * In the future, try them with smart pointers to see what
 * difference that makes. Also try compiling with different
 * C++ STANDARDS to see if that makes any difference to the final
 * executable.
 */

#include <iostream>

class ModernTest {
  public:
    ModernTest() {
      my_size = 0;
    }
    ModernTest(size_t _initSize) {
      my_size = _initSize;
    }

    ModernTest(const ModernTest &m) {
      std::cout << "[     ]    Now in the copy constructor!" << std::endl;
      my_size = m.my_size;
    }
    
    void operator =(const ModernTest &m) {
      std::cout << "[     ]    Now in the overridden assignment operator!" << std::endl;
      my_size = m.my_size;
    }

    size_t getSize() {
      return my_size;
    }

    void setSize(size_t _size) {
      my_size = _size;
    }

  protected:
    size_t my_size;
};

int main() {
/*  ModernTest objA(); */ // this declares a wrong type!! A ptr to a function?
  ModernTest objA();
  ModernTest objZ(127);
  objA.setSize(17);
  std::cout << "[DEBUG]    Just set size to 17" << std::endl;
  ModernTest objB = objA;
  std::cout << "[DEBUG]    Just ran objB = objA. ObjB size is " << objB.getSize() << std::endl;
  ModernTest objC(objA);
  std::cout << "[DEBUG]    Just ran objC(objA). ObjC size is " << objC.getSize() << std::endl;
  objC.setSize(19);
  std::cout << "[DEBUG]    Just set objC size to 19" << std::endl;
  objB = objC;
  std::cout << "[DEBUG]    Just ran objB = objC." << std::endl;
  std::cout << "objA size: " << objA.getSize() << std::endl;
  std::cout << "objB size: " << objB.getSize() << std::endl;
  std::cout << "objC size: " << objC.getSize() << std::endl;
  std::cout << "objZ size: " << objZ.getSize() << std::endl;
  return 0;
}
