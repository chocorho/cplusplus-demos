/*
 *
 * This is a long-overdue set of tests to make sure that I really unerstand,
 * at a deep level, the use of the keyword `virtual`.
 *
 * I was always trained to use `virtual` whenever a subclass has an overridden
 * function, but the truth is, I didn't know why. What happens if I keep a
 * pointer to the base class and run its overridden member function? How does the
 * omission of `virtual` change this? And how does it work when there is a
 * third-generation subclass? What about the other possible combinations.
 *
 */

#include <iostream>
#include <memory>

class ParentNoVirt {

  public:
    ParentNoVirt() {
      
    }
    ~ParentNoVirt() {
      
    }
    
    void printStatusc() {
      std::cout << "Take a look! We're running inside the parent class, "
                << "unabashedly." << std::endl;
    }

};

class ChildNoVirt : public ParentNoVirt {

  public:
    ChildNoVirt() : ParentNoVirt() {

    }
    ~ChildNoVirt() {

    }

    void printStatusc() {
      std::cout << "Take a look! We're running inside the child class... "
                << "That's pretty cool." << std::endl;
    }

};

class ParentVirt {
  public:
    ParentVirt() {
      
    }

    /* Note: this destructor should be virtual; otherwise the compiler prints a
     *       warning! Evidently this is BECAUSE the other method is declared
     *       virtual. */
    virtual ~ParentVirt() {
      
    }
    
    virtual void printStatusc() {
      std::cout << "Take a look! We're running inside the parent class, "
                << "despite being marked as virtual. I bet you didn't "
                << "instantiate it using a child class this time, did you!"
                << std::endl;
    }

};

class ChildVirt : public ParentVirt {
  public:
    ChildVirt() : ParentVirt() {
      
    }
    ~ChildVirt() {
      
    }
    
    virtual void printStatusc() {
      std::cout << "Take a look! We're running inside the child class, "
                << "because the function was marked as virtual." << std::endl;
    }
};

int main() {
  std::cout << "Trying with type (ParentNoVirt *)..." << std::endl;
  ParentNoVirt *testNoVirt = new ChildNoVirt();
  testNoVirt->printStatusc();

  std::cout << std::endl;
  std::cout << "Trying with type (ParentVirt *)..." << std::endl;
  ParentVirt *testWithVirt = new ChildVirt();
  testWithVirt->printStatusc();

  std::cout << std::endl;
  delete testNoVirt;
  delete testWithVirt;

  /* Now I want to test using smart pointers to check if it's any different */

  std::cout << std::endl;
  std::cout << "Trying with type (std::unique_ptr<ParentNoVirt>)..." << std::endl;
  std::unique_ptr<ParentNoVirt> wrapperNoVirt(new ChildNoVirt());
  wrapperNoVirt->printStatusc();

  std::cout << std::endl;
  std::cout << "Trying with type (std::unique_ptr<ParentVirt>)..." << std::endl;
  std::unique_ptr<ParentVirt> wrapper(new ChildVirt());
  wrapper->printStatusc();

  return 0;
}
