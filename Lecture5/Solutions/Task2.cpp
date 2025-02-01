#include <iostream>
#include <cmath>
using namespace std;
class Complex{
    public :
    float imaginary,real;
    Complex(float re,float im){
        real = re;
        imaginary = im;
    }
    Complex operator+(Complex &other){
        float im = imaginary + other.imaginary;
        float re = real + other.real;
        Complex result(re, im);
        return result;
    }
    Complex operator-(Complex &other){
        float im = imaginary - other.imaginary;
        float re = real - other.real;
        Complex result(re, im);
        return result;
    }
    Complex operator*(Complex &other){
        float im = imaginary * other.real + real * other.imaginary;
        float re = real * other.real - imaginary * other.imaginary;
        Complex result(re, im);
        return result;
    }
    Complex operator/(Complex &other){
        float im = (imaginary * other.real - real * other.imaginary)/(other.real * other.real + other.imaginary * other.imaginary);
        float re = (real * other.real + imaginary * other.imaginary)/(other.real * other.real + other.imaginary * other.imaginary);
        Complex result(re, im);
        return result;
    }
    bool operator==(Complex &other){
        return imaginary == other.imaginary && real == other.real;
    }
    float modulus(){
        return sqrt(imaginary * imaginary + real * real);
    }
    void display(){
        if (imaginary > 0){
            cout << real << " + " << imaginary << "i" << endl;
        }else{
            cout << real << " " << imaginary << "i" << endl;
        }
        
    }
};
int main(){
    Complex c1(3,4);
    Complex c2(-7,3);
    Complex c3(0,0);
    c1.display();
    cout << "c1 modulus = "<< c1.modulus() << endl;
    c3 = c1 / c2;
    c3.display();
    return 0;
}