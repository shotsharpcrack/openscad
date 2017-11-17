#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <deque>
#include <queue>

using namespace std;

//#define PI 3.1415926;

class Point{
public:
    double x = 0;
    double y = 0;
    double z = 0;
    Point(double x, double y, double z):x(x),y(y),z(z){
    }

    friend ostream& operator <<(ostream& s, Point p){
        s <<"vertex"<<' '<<p.x<<' '<<p.y<<' '<<p.z <<endl;
    }
};

class Triangle{
public:
    Point a,b,c;
    Triangle(Point a,Point b,Point c):a(a),b(b),c(c){
        /*vector<Point> points;
        points.push_back(Point(a));
        points.push_back(Point(b));
        points.push_back(Point(c));*/
    }

    friend ostream& operator <<(ostream& s, Triangle t){
        s << "facet normal 0 0 0"<<endl;
        s << " " << "outer loop" <<endl;
        s << "  " << t.a;
        s << "  " << t.b;
        s << "  " << t.c;
        s << "  " << "endloop" <<endl;
        s << " " << "endfacet" << endl;

    }

};


class Polygon{
public:
    int n;
    double r;
    //Point origin = Point(0,0,0);
    deque<Point> points;

    Polygon(int n):n(n){
        //vector<Point> points;

        double sita = (2*M_PI)/n;
        for (int i = 0; i < n; i++) {
            points.push_back(Point(r*cos(sita),r*sin(sita),0));
        }
    }

    queue<Point> findTriangle(){
        queue<Point> triangles;

        triangles.push(Point(points.front()));
        points.pop_front();
        triangles.push(Point(points.back()));
        points.pop_back();
        triangles.push(Point(points.front()));
        points.pop_front();

/*        while(!points.empty()){
 *
        }*/
    }

};
class Shape {
public:
    virtual string print() = 0;
};
class Cylinder : public Shape{
private:
    double r, h;
    int facets;
    double vectorarray[3];
public:
    Cylinder(double x, double y, double z, double r, double h, int facets):r(r),h(h),facets(facets) {
        vectorarray[0]=x;
        vectorarray[1]=y;
        vectorarray[2]=z;
    }
    string vector_print(double x1,double y1,double z1){    //format the vector location(x,y,z) to string
        ostringstream output_result;
        output_result<<" "<< vectorarray[0]+x1<<" "<<vectorarray[1]+y1<<" "<<vectorarray[2]+z1<<"\n";
        return output_result.str();
    }
    string vector_print2(double x1,double y1,double z1){    //format the vector location(x,y,z) to string
        ostringstream output_result;
        output_result<<" "<< vectorarray[0]+x1<<" "<<vectorarray[1]+y1<<" "<<vectorarray[2]+z1<<"\n";
        return output_result.str();
    }
    string angle_print(double n){             //print 4 triangles for X angle
        double angle1=(n*360*M_PI)/(180*facets);
        double angle2=((n+1)*360*M_PI)/(180*facets);
        string output_result="";
        output_result="  facet normal"+output_result+vector_print(cos(angle1+360/facets),sin(angle1+360/facets),0)+"    outer loop\n"+
                      "      vertex" +vector_print(r*cos(angle2),r*sin(angle2),h)+
                      "      vertex" +vector_print(r*cos(angle1),r*sin(angle1),h)+
                      "      vertex" +vector_print(r*cos(angle1),r*sin(angle1),0)+
                      "    endloop\n  endfacet\n"+
                      "  facet normal"+vector_print2(cos(angle1+360/facets),sin(angle1+360/facets),0)+"    outer loop\n"+
                      "      vertex" +vector_print(r*cos(angle2),r*sin(angle2),h)+
                      "      vertex" +vector_print(r*cos(angle1),r*sin(angle1),0)+
                      "      vertex" +vector_print(r*cos(angle2),r*sin(angle2),0)+
                      "    endloop\n  endfacet\n"+
                      "  facet normal"+vector_print(0,0,1)+"    outer loop\n"+
                      "      vertex" +vector_print(0,0,h)+
                      "      vertex" +vector_print(r*cos(angle1),r*sin(angle1),h)+
                      "      vertex" +vector_print(r*cos(angle2),r*sin(angle2),h)+
                      "    endloop\n  endfacet\n"+
                      "  facet normal"+vector_print(0,0,-1)+"    outer loop\n"+
                      "      vertex" +vector_print(0,0,0)+
                      "      vertex" +vector_print(r*cos(angle2),r*sin(angle2),0)+
                      "      vertex" +vector_print(r*cos(angle1),r*sin(angle1),0)+
                      "    endloop\n  endfacet\n";
        return output_result;
    };
    string print(){                         //print the whole Cylinder
        string output_result="";
        if (facets<3)
            cout<<"Face is less than 3, Can not print";
        else
            for (int indexofvector=0;indexofvector<facets;indexofvector++)
                output_result=output_result+angle_print(indexofvector);
        return output_result;
    }
};

class Cube: public Shape {
private:
    double size;
    double vectorarray[3];
public:
    Cube(double x, double y, double z, double size) : size(size){
        vectorarray[0]=x;
        vectorarray[1]=y;
        vectorarray[2]=z;
    };

    string facet_vector(double vector_direction, uint8_t vector_location){
        ostringstream output_result;
        for (uint8_t temp=0;temp<3;temp++)
            if (temp==vector_location)
                output_result<<" "<<vector_direction;
            else
                output_result<<" 0";
        output_result<<"\n";
        return output_result.str();
    }


    string vertex_base(double vector_direction, uint8_t vector_location,double else_value){
        ostringstream output_result;
        for (uint8_t temp=0;temp<3;temp++)
            if (temp==vector_location)
                output_result<<" "<< ((vector_direction+1)/2)*size+vectorarray[temp];
            else
                output_result<<" "<<else_value*size+vectorarray[temp];
        output_result<<"\n";
        return output_result.str();
    }

    string vertex_third_point(double vector_direction, uint8_t vector_location,double else_value){
        ostringstream output_result;
        for (uint8_t temp=0;temp<3;temp++)
            if (temp==vector_location)
                output_result<<" "<< ((vector_direction+1)/2)*size+vectorarray[temp];
            else{
                output_result<<" "<<abs(else_value)*size+vectorarray[temp];
                else_value++;
            }
        output_result<<"\n";
        return output_result.str();
    }

    string triangle_print(double vector_direction, uint8_t vector_location) {
        string output_result = "";
        output_result = "  facet normal" + output_result + facet_vector(vector_direction, vector_location) +
                        "    outer loop\n" +
                        "      vertex" + vertex_base(vector_direction, vector_location, 0) +
                        "      vertex" + vertex_base(vector_direction, vector_location, 1) +
                        "      vertex" + vertex_third_point(vector_direction, vector_location, 0) +
                        "    endloop\n  endfacet\n" +
                        "  facet normal" + facet_vector(vector_direction, vector_location) + "    outer loop\n" +
                        "      vertex" + vertex_base(vector_direction, vector_location, 1) +
                        "      vertex" + vertex_base(vector_direction, vector_location, 0) +
                        "      vertex" + vertex_third_point(vector_direction, vector_location, -1) +
                        "    endloop\n  endfacet\n";
        return output_result;
    }

    string triangle_print_reverse(double vector_direction, uint8_t vector_location){
        string output_result = "";
        output_result = "  facet normal"+output_result+facet_vector(vector_direction,vector_location)+"    outer loop\n"+
                        "      vertex" +vertex_base(vector_direction,vector_location,1)+
                        "      vertex" +vertex_base(vector_direction,vector_location,0)+
                        "      vertex" +vertex_third_point(vector_direction,vector_location,0)+
                        "    endloop\n  endfacet\n"+
                        "  facet normal"+facet_vector(vector_direction,vector_location)+"    outer loop\n"+
                        "      vertex" +vertex_base(vector_direction,vector_location,0)+
                        "      vertex" +vertex_base(vector_direction,vector_location,1)+
                        "      vertex" +vertex_third_point(vector_direction,vector_location,-1)+
                        "    endloop\n  endfacet\n";
        return output_result;
    }
    string print(){
        string output_result="";
        output_result=triangle_print(1, 0)+triangle_print_reverse(-1, 0)+
                      triangle_print_reverse(1, 1)+triangle_print(-1, 1)+
                      triangle_print(1, 2)+triangle_print_reverse(-1, 2);
        return output_result;
    }
};



class CAD {
private:
    vector<Shape*> shapes;
public:
    void add(Shape *p){
        shapes.push_back(p);
    }
    void write(string filename){
        fstream fin(filename, fstream::out);
        fin<< "solid OpenSCAD_Model\n";
        for(int indexofvector=0;indexofvector<shapes.size();indexofvector++)
            fin << shapes[indexofvector]->print();
        fin<<"endsolid OpenSCAD_Model\n";
    }
};

int main() {
    CAD c;
    c.add(new Cube(0,0,0,   5));
    c.add(new Cylinder(100,0,0,    3, 10, 10));
    c.write("test.stl");
}