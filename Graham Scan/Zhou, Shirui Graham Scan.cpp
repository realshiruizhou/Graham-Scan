// Shirui Zhou P5
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <list>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <limits>
#include <unordered_map>
#include <stack>

typedef std::numeric_limits< double > dbl;

using namespace std;
using namespace std::chrono;

const int width = 800, height = 800;
int arr[width][height];

void linecalculations(int x1, int y1, int x2, int y2, int color){
    int dx = x2 - x1;
    int dy = y2 - y1;
    int driving;
    if(abs(dx) > abs(dy)){
        driving = 0;
    }
    else{
        driving = 1;
    }
    if(dy < 0 && dx < 0){
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        dx = abs(dx);
        dy = abs(dy);
    }
    if(driving == 0){
        if(dx >= 0){
            int t = 0;
            if (dy < 0){
                dy = abs(dy);
                t = 1;
            }
            int j = y1;
            int e = dy - dx;
            for (int i = x1; i < x2; i++){
                if(i >= 0 && i < width && j >= 0 && j < height){
                    arr[i][j] = color;
                }
                if (e >= 0){
                    if(t == 1){
                        j -= 1;
                    }
                    else{
                        j += 1;
                    }
                    e -= dx;
                }
                e += dy;
            }
        }
        else{
            dx = abs(dx);
            int j = y1;
            int e = dy - dx;
            for (int i = x1; i > x2; i--){
                if(i >= 0 && i < width && j >= 0 && j < height){
                    arr[i][j] = color;
                }
                if (e >= 0){
                    j += 1;
                    e -= dx;
                }
                e += dy;
            }
        }
    }
    else{
        if(dy >= 0){
            int t = 0;
            if (dx < 0){
                dx = abs(dx);
                t = 1;
            }
            int j = x1;
            int e = dx - dy;
            for (int i = y1; i < y2; i++){
                if(i >= 0 && i < height && j >= 0 && j < width){
                    arr[j][i] = color;
                }
                if (e >= 0){
                    if(t == 1){
                        j -= 1;
                    }
                    else{
                        j += 1;
                    }
                    e -= dy;
                }
                e += dx;
            }
        }
        else{
            dy = abs(dy);
            int j = x1;
            int e = dx - dy;
            for (int i = y1; i > y2; i--){
                if(i >= 0 && i < height && j >= 0 && j < width){
                    arr[j][i] = color;
                }
                if (e >= 0){
                    j += 1;
                    e -= dy;
                }
                e += dx;
            }
        }
    }
    arr[x1][y1] = color;
    arr[x2][y2] = color;
}

void drawCircleHelper(int xc, int yc, int x, int y, int color){
    if(xc + x < width && yc + y < height){
        arr[xc+x][yc+y] = color;
    }
    if(xc - x >= 0 && yc + y < height){
        arr[xc-x][yc+y] = color;
    }
    if(xc + x < width && yc - y >= 0){
        arr[xc + x][yc - y] = color;
    }
    if(xc - x >= 0 && yc - y >= 0){
        arr[xc - x][yc - y] = color;
    }
    if(xc + y < width && yc + x < height){
        arr[xc + y][yc + x] = color;
    }
    if(xc - y >= 0 && yc + x < height){
        arr[xc - y][yc + x] = color;
    }
    if(xc + y < width && yc - x >= 0){
        arr[xc + y][yc - x] = color;
    }
    if(xc - y >= 0 && yc - x >= 0){
        arr[xc - y][yc - x] = color;
    }
}

void drawCircle(int xc, int yc, int r, int color){
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircleHelper(xc, yc, x, y, color);
    while (y >= x){
        x++;
        if (d > 0){
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircleHelper(xc, yc, x, y, color);
    }
}


void draw(){
    int r, g, b;
    ofstream img("cv.ppm");
    img << "P3" << endl;
    img << width << " " << height << endl;
    img << "255" << endl;

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if(arr[x][y] == 1){
                r = 0;
                g = 0;
                b = 0;
            }
            else if(arr[x][y] == 2){
                r = 255;
                b = 0;
                g = 0;
            }
            else{
                r = 255;
                g = 255;
                b = 255;
            }
            img << r << " " << g << " " << b << endl;
        }
    }
}

class Point{
private:
    double x, y;
public:
    Point(double a, double b){
        x = a;
        y = b;
    }
    Point(){
        x = 0;
        y = 0;
    }
    double getX(){
        return x;
    }
    double getY(){
        return y;
    }
    void setX(double c){
        x = c;
    }
    void setY(double d){
        y = d;
    }
    void display(){
        cout<<"("<<x<<","<<y<<")"<<endl;
    }
};

double distance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void generatePoints(vector<Point> &p, int n){
    srand(time(0));
    ofstream myfile;
    myfile.open("points.txt");
    for(int a = 0; a < n; a++){
        Point p1(rand()/(RAND_MAX + 1.), rand()/(RAND_MAX + 1.));
//        while(pow(p1.getX() - .5, 2) + pow(p1.getY() - .5, 2) >= .25){
//            Point p2(rand()/(RAND_MAX + 1.), rand()/(RAND_MAX + 1.));
//            p1 = p2;
//        }
        myfile.precision(dbl::max_digits10);
        myfile<<p1.getX()<<" "<<p1.getY()<<endl;
        p.push_back(p1);
        arr[(int)(p1.getX() * width + .5)][(int)(p1.getY() * height + .5)] = 1;
        drawCircle((int)(p1.getX() * width + .5),(int)(p1.getY() * height + .5), 5, 1);
    }
}

void readfile(list<Point> &p){
    double a, b;
    ifstream infile("points.txt");
    int length;
    while(infile >> a >> b){
        Point temp(a, b);
        p.push_back(temp);
    }
    infile.close();
}

double pDistance(Point a, Point b){
    return distance(a.getX(), a.getY(), b.getX(), b.getY());
}

int findSide(Point p1, Point p2, Point p){
    double value = (p.getY() - p1.getY()) * (p2.getX() - p1.getX()) - (p2.getY() - p1.getY()) * (p.getX() - p1.getX());
    if(value > 0){
        return 1;
    }
    else if(value < 0){
        return -1;
    }
    else{
        return 0;
    }
}

double distanceFromLine(Point p1, Point p2, Point p){
    return abs((p.getY() - p1.getY()) * (p2.getX() - p1.getX()) - (p2.getY() - p1.getY()) * (p.getX() - p1.getX()));
}

void quickHelper(vector<Point> p, int n, Point p1, Point p2, int side){
    int farthest = -1;
    double maxDistance = 0;
    for(int i = 0; i < n; i++){
        double dist = distanceFromLine(p1, p2, p[i]);
        if(dist > maxDistance && findSide(p1, p2, p[i]) == side){
            farthest = i;
            maxDistance = dist;
        }
    }

    if(farthest == -1){
        linecalculations((int)(width * p1.getX() + .5), (int)(height * p1.getY() + .5), (int)(width * p2.getX() + .5), (int)(height * p2.getY() + .5), 1);
        return;
    }

    quickHelper(p, n, p[farthest], p1, -findSide(p[farthest], p1, p2));
    quickHelper(p, n, p[farthest], p2, -findSide(p[farthest], p2, p1));
}

void quickHull(vector<Point> p, int size){
    int minX = 0, maxX = 0;
    for(int k = 1; k < size; k++){
        if(p[k].getX() < p[minX].getX()){
            minX = k;
        }
        if(p[k].getX() > p[maxX].getX()){
            maxX = k;
        }
    }

    quickHelper(p, size, p[minX], p[maxX], 1);
    quickHelper(p, size, p[minX], p[maxX], -1);
}

Point p_init;

Point nextToTop(stack<Point> &S){
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

void swap(Point &p1, Point &p2){
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int orientation(Point p, Point q, Point r){
    double val = (q.getY() - p.getY()) * (r.getX() - q.getX()) - (q.getX() - p.getX()) * (r.getY() - q.getY());
    if(val == 0){
        return 0;
    }
    else if(val > 0){
        return 1;
    }
    else{
        return 2;
    }
}

int compare(const void *vp1, const void *vp2){
    auto *p1 = (Point *)vp1;
    auto *p2 = (Point *)vp2;

    int o = orientation(p_init, *p1, *p2);
    if(o == 0){
        if(pDistance(p_init, *p2) >= pDistance(p_init, *p1)){
            return -1;
        }
        else{
            return 1;
        }
    }
    else if(o == 2){
        return -1;
    }
    else{
        return 1;
    }
}

void grahamScan(vector<Point> points, int n){
    double ymin = points[0].getY();
    int min = 0;
    for(int i = 1; i < n; i++){
        double y = points[i].getY();
        if ((y < ymin) || (ymin == y && points[i].getX() < points[min].getX())){
            ymin = points[i].getY(), min = i;
        }
    }

    swap(points[0], points[min]);

    p_init = points[0];
    Point temp[n - 1];
    int count = 0;
    for(int k = 1; k < n; k++){
        temp[count] = points[k];
        count++;
    }
    qsort(&temp[0], n-1, sizeof(Point), compare);
    count = 1;
    for(auto z: temp){
        points[count] = z;
        count++;
    }

    int m = 1;
    for(int i=1; i<n; i++){
        while(i < n-1 && orientation(p_init, points[i],points[i+1]) == 0){
            i++;
        }
        points[m] = points[i];
        m++;
    }

    stack<Point> s;
    s.push(points[0]);
    s.push(points[1]);
    s.push(points[2]);

    for(int i = 3; i < m; i++){
        while(orientation(nextToTop(s), s.top(), points[i]) != 2){
            s.pop();
        }
        s.push(points[i]);
    }

    Point last = s.top();
    Point previous = s.top();
    s.pop();
    while(!s.empty()){
        Point p = s.top();
        linecalculations((int)(width * previous.getX() + .5), (int)(height * previous.getY() + .5), (int)(width * p.getX() + .5), (int)(width * p.getY() + .5), 1);
        previous = p;
        s.pop();
    }
    linecalculations((int)(width * previous.getX() + .5), (int)(height * previous.getY() + .5), (int)(width * last.getX() + .5), (int)(width * last.getY() + .5), 1);
}

int main()
{
    srand(time(0));
    int size = 50;
    vector<Point> points;
    for(int a = 0; a < size; a++){
        Point t(rand()/(RAND_MAX + 1.), rand()/(RAND_MAX + 1.));
        points.push_back(t);
    }
    for(auto s: points){
        drawCircle((int)(width * s.getX() + .5), (int)(height * s.getY() + .5), 3, 1);
    }
    grahamScan(points, points.size());
    draw();
    return 0;
}