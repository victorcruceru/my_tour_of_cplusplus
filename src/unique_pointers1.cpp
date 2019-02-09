/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Victor Cruceru wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
 * Description: Mainly std::unique_ptr execise.
 * It also covers some basic inheritance items like:
 * virtual destructor call sequence,  constructors in dervied class
 */ 
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <vector>

using namespace std::string_literals;

class BaseShape {

  public:
    virtual ~BaseShape(void){
       std::cout << "DEBUG: *Destructor* for "<< get_name() <<" called" 
                 << std::endl;
    }

    virtual double get_area(void) = 0; // pure virtual function

    virtual const std::string get_name(void){
      return  ("BaseShape"s);
    }
};


class Triangle: public BaseShape{  
  private:
    double side_a_ = 0;
    double side_b_ = 0;
    double side_c_ = 0;
 
  public:
    Triangle(double side_a, double side_b, double side_c): 
      side_a_ {side_a}, 
      side_b_ {side_b}, 
      side_c_ {side_c}{
       std::cout << "DEBUG: *Constructor* for "<< get_name() <<" called" 
                 << std::endl;
    }
    
    virtual 
    double get_area(void) override {
      double half_perimeter = (side_a_ + side_b_ + side_c_)/2;
      return (sqrt(half_perimeter * 
                  (half_perimeter - side_a_) * 
                  (half_perimeter - side_b_) * 
                  (half_perimeter - side_c_)));
    }

    virtual const std::string get_name(void) override{
      return ("Triangle"s);
    }    

    virtual ~Triangle(void){
       std::cout << "DEBUG: *Destructor* for "<< get_name() <<" called" 
                 << std::endl;      
    } 
};

class Rectangle: public BaseShape{  
  private:
    double w_ = 0;
    double h_ = 0;

  
  public:
    Rectangle(double h, double w): 
      w_ {w}, 
      h_ {h}{
       std::cout << "DEBUG: *Constructor* for "<< get_name() <<" called" 
                 << std::endl;
    }
    
    virtual 
    double get_area(void) override {
      return (w_ * h_);
    }

    virtual const std::string get_name(void) override{
      return  ("Rectangle"s);
    }    

    virtual ~Rectangle(void){
       std::cout << "DEBUG: *Destructor* for "<< get_name() <<" called" 
                 << std::endl;      
    } 
};

class Square: public Rectangle{

  public:
    Square(double side): Rectangle{side, side}{
      std::cout << "DEBUG: *Constructor* for "<< get_name() <<" called" 
                << std::endl;     
    }
    virtual const std::string get_name(void) override{
      return  ("Square"s);
    }    

    virtual ~Square(void){
       std::cout << "DEBUG: *Destructor* for "<< get_name() <<" called" 
                 << std::endl;      
    } 
};

class Circle: public BaseShape{  
  private:
    double radius_ = 0;

  public:
    Circle(double radius): radius_ {radius}{
       std::cout << "DEBUG: *Constructor* for "<< get_name() <<" called" 
                 << std::endl;
    }  
    virtual 
    double get_area(void) override {
      return (M_PI * radius_ * radius_);
    }

    virtual const std::string get_name(void) override{
      return  ("Circle"s);
    }   

    virtual ~Circle(void){
       std::cout << "DEBUG: *Destructor* for "<< get_name() <<" called" 
                 << std::endl;      
    } 
};      



int main(){
  std::unique_ptr<BaseShape> triangle = std::unique_ptr<BaseShape>(
                                    new Triangle {10.0, 10.0, 1.0}
                                  );
  std::cout << triangle->get_name() << " area is: " << triangle->get_area() 
            << std::endl;
  
  /*
  std::unique_ptr<BaseShape> tp2 = triangle;
  std::cout << triangle->get_name() << ":" << triangle->get_area() <<std::endl;
  */

  std::unique_ptr<BaseShape> square = std::unique_ptr<BaseShape>(
                                    new Square {9.0});

  std::cout << square->get_name() << " area is: " << square->get_area() 
            << std::endl;

  std::vector<std::unique_ptr<BaseShape>> vec {};
  vec.push_back(std::unique_ptr<BaseShape>(new Triangle {7.0, 7.0, 7.0}));
  vec.push_back(std::unique_ptr<BaseShape>(new Circle {7}));
  vec.push_back(std::unique_ptr<BaseShape>(new Rectangle {7, 17}));
  vec.push_back(std::unique_ptr<BaseShape>(new Square {90}));
  // Next two C++ lines do not work - can't copy a unique_ptr (triangle is  
  // by passed value)
  // vec.push_back(triangle);
  // vec.push_back(square)

  // Next two lines work - triangle or/ and square are moved into temp variables
  // of type unique_ptr which in tun are saved into the container
  vec.push_back(std::move(triangle));
  //vec.push_back(std::move(square));

  std::cout << "DEBUG: triangle is valid: " << std::boolalpha << bool(triangle) 
            << std::endl;

  std::cout << "DEBUG: square is valid: " << std::boolalpha << bool(square) 
            << std::endl;  

  for (const auto& v: vec){
    std::cout << v->get_name() << " area is: " << v->get_area() 
            << std::endl;    
  }
   
  return (EXIT_SUCCESS);
}