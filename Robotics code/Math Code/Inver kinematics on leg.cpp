#include <iostream>
#include <vector>
#include <math.h>
#include <cmath>
using namespace std;

double PI = acos(-1);

// Carteasian Coordinates
double x = 5;
double y = 21;

// Arm Lengths
double l1 = 10;
double l2 = 20;

// Functions
double Sum(double a, double b);
void print(vector<double> rec);
vector<double> Normal();
vector<double> Polar();


int main(){
    /*
    cout << "Enter Lengths: " << endl;
    cin >> l1;
    cin >> l2;

    cout << "Enter X and Y coordinates: " << endl;
    cin >> x;
    cin >> y;
    */

    cout << "Normal: " << endl;
    print(Normal());

    cout << "Polar" << endl;
    print(Polar());

    return 0;
}

vector<double> Normal(){
    double diff = 0;
    double  num = 0, denom1 = 0, denom2 = 0;
    double a1 = 0, a2 = 0;

    diff = Sum(x,y) - Sum(l1, l2);
    denom1 = 2*(l1*l2);
    a2 = acos(diff/denom1);

    num = l2 * sin(a2);
    denom2 = l1 + l2 * cos(a2);
    a1 = atan(y/x) - atan(num/denom2);

    vector<double> angles = {a1,a2};
    return angles;
}

vector<double> Polar(){
    double r = 0, theta = 0;
    double ABC = 0, BAC = 0;
    double a1 = 0, a2 = 0;
    double num = 0, denom;

    r = sqrt(pow(x, 2) + pow(y,2));
    theta = atan(y/x);

    num = Sum(l1, l2) - pow(r,2);
    denom = (2*l1*l2);
    ABC = PI - acos(num/denom);

    num  = Sum(l1, r) - pow(l2, 2);
    denom = 2 * l1 * r;
    BAC = -acos(num/denom);

    a1 = BAC + theta;
    a2 = ABC - (PI - a2) + PI;

    vector<double> angles = {a1,a2};
    return angles;
}

double Sum(double a, double b){
    return pow(a,2) + pow(b,2);
}

void print(vector<double> rec){
    for (double i:rec){
        cout << i*180/PI << endl;
    }
}