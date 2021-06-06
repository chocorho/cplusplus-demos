/* 
 * This is a series of tests designed to let myself explore the backwards-compatibility of C++ with C.
 * I do not often see people using structs in C++, since they're rather old-school. But that just raises the question, to what extent **can** you use them in C++?
 * I learned C in uni, but not C++.
 * 
 * So this suite of tests will push the limits of visibility, constructors, and so forth.
 * You may compile with something like:
 * 
 *  $(CC) -o test_structs struct-testing.cpp $(CXXFLAGS) 
 */

#include <iostream>

struct c_style_struct {
  
 int weight;
 const char *label;
  
};

struct struct_plus_visibility {
  public:
    struct_plus_visibility(const char *first_name) {
      name = first_name;
    }
  
  private:
    const char *name;
  
};

struct struct_plus_string {
  public:
    struct_plus_string(std::string *_name) {
      name = _name;
    }
  
  private:
    std::string *name;
  
};

struct struct_plus_string_obj {

  public:
    struct_plus_string_obj(std::string &_name) {
      name = _name;
    }
  
  private:
    std::string name;
  
};

int main() {
  const char *question = "which is better, c or c++?";
  
  struct c_style_struct test1 = { 17, question };
  std::cout << "sizeof() on the C-style struct: " << sizeof(test1) << std::endl;
  
  struct struct_plus_visibility test2(question);

  /* The following line is a compilation error!!!
   * So `private` visibility IS in fact valid for C++ structs! */
  //test2.name = question;
  std::cout << "sizeof() on the private-visibility struct: " << sizeof(test2) << std::endl;

  std::string auto_alloc_string = "Exactly thirty-six characters long";
  std::string *heap_alloc_string = new std::string("Exactly thirty-six characters long");
  
  struct struct_plus_string test3(heap_alloc_string); //  = { /*23,*/ heap_alloc_string };
/*  test3.name = heap_alloc_string;*/
  std::cout << "sizeof() on the C-style struct: " << sizeof(test3) << std::endl;
  
  struct struct_plus_string_obj test4(auto_alloc_string); // = { /*29,*/ auto_alloc_string };
/*  test4.name = auto_alloc_string;*/
  std::cout << "sizeof() on the C-style struct: " << sizeof(test4) << std::endl;
  
  delete heap_alloc_string;
  return 0;
}

