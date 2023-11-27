#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>pragma once
#ifndef myread
#define myread
using namespace std;
struct point {
    double xyz[3];
};
struct element {
    int pointGlobalId[4];
    int edgeGlobalId[6];
    point point1;
    point point2;
    point point3;
    point point4;
};
struct Edgemesh {
    int ifmesh;
    point pmeshed;
    int gpmeshed;//新点的全局编号
};
void readFileData_xyz(const std::string& filename, std::vector<point>& point_vet, int* np);
void readFileData_le(const string& filename, vector<element>& Element_vet);
void readFileData_lv(const std::string& filename, std::vector<element>& Element_vet, std::vector<point>& point_vet, int* lv);
void readFileData_mesh(const string& filename, vector<Edgemesh>& edgemesh, double m);
void wle(const string& filename, vector<point>& point_vet);
void wlv(const string& filename, vector<element>& Element_vet);
void wxyz(const string& filename, vector<point>& point_vet);
#endif
