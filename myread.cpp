#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "myread.h"
void readFileData_xyz(const std::string& filename, std::vector<point>& point_vet, int* np) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        int lineNumber = 0;
        point pointtol{};
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (lineNumber == 0) {
                int number;
                iss >> number;
                *np = number;
            }
            else {
                iss >> pointtol.xyz[0] >> pointtol.xyz[1] >> pointtol.xyz[2];
                point_vet.push_back(pointtol);
            }

            lineNumber++;
        }
        std::cout << "读取xyz完成" << std::endl;
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
}
void readFileData_le(const string& filename, vector<element>& Element_vet) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        int i = 0;
        int number = 0;
        while (std::getline(file, line)) {
            // 使用 std::istringstream 分割每一行的整数
            std::istringstream iss(line);
            int np = 0;
            // 逐个读取整数并处理
            while (iss >> number) {
                Element_vet[i].edgeGlobalId[np] = number;
                np++;
            }
            i++;
        }

        std::cout << "读取le完成" << std::endl;
        // 关闭文件
        file.close();
    }

}

void readFileData_lv(const std::string& filename, std::vector<element>& Element_vet, std::vector<point>& point_vet, int* lv) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        int lineNumber = 0;
        int val = 0;
        element ele{};
        std::vector<point> p;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            if (lineNumber == 0) {
                int number;
                iss >> number;
                *lv = number;
            }
            else {
                int pointGlobalId, edgeGlobalId;
                bool edge;
                iss >> ele.pointGlobalId[0] >> ele.pointGlobalId[1] >> ele.pointGlobalId[2] >> ele.pointGlobalId[3];
                val = ele.pointGlobalId[0];
                ele.point1 = point_vet[val - 1];
                ele.point2 = point_vet[ele.pointGlobalId[1] - 1];
                ele.point3 = point_vet[ele.pointGlobalId[2] - 1];
                ele.point4 = point_vet[ele.pointGlobalId[3] - 1];
                Element_vet.push_back(ele);
            }
            lineNumber++;
        }
        std::cout << "读取lv完成" << std::endl;
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

void readFileData_mesh(const string& filename, vector<Edgemesh>& edgemesh, double m) {
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        vector <int> nle;
        while (std::getline(file, line)) {
            // 使用 std::istringstream 分割每一行的整数
            std::istringstream iss(line);
            int number;
            // 逐个读取整数并处理
            iss >> number;
            nle.push_back(number);
            // 换行
        }
        double size0 = nle.size() * m;
        int size = static_cast<int>(size0);
        Edgemesh e{};
        edgemesh.resize(nle.size());
        for (int i = 0; i < nle.size(); i++) {
            if (i < size) {
                e.ifmesh = 1;
            }
            else
            {
                e.ifmesh = 0;
            }
            int  number = nle[i] - 1;
            //cout << number << endl;
            edgemesh[number] = e;
        }
        std::cout << "读取mesh完成" << size << std::endl;
        // 关闭文件
        file.close();
    }
    else
    {
        std::cout << "读取mesh失败，未能打开文件" << std::endl;
    }
}
void wle(const string& filename, vector<point>& point_vet) {}
void wlv(const string& filename, vector<element>& Element_vet) {
    ofstream outputFile(filename, ios::trunc);

    if (!outputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    outputFile << Element_vet.size() << endl;
    for (const auto& e : Element_vet) {
        // 写入xyz数组的三个值，每一行储存一个point的数据
        outputFile << e.pointGlobalId[0] << " " << e.pointGlobalId[1] << " "
            << e.pointGlobalId[2] << " " << e.pointGlobalId[3] << " " << "1"
            << " " << "0" << " " << "0" << " " << "0" << " " << "0" << endl;
    }
    cout << "写入lv文件成功" << endl;
    outputFile.close();
}
void wxyz(const string& filename, vector<point>& point_vet) {
    ofstream outputFile(filename, ios::trunc);

    if (!outputFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    outputFile << point_vet.size() << endl;
    for (const auto& p : point_vet) {
        // 写入xyz数组的三个值，每一行储存一个point的数据
        outputFile << p.xyz[0] << " " << p.xyz[1] << " " << p.xyz[2] << endl;
    }
    cout << "写入xyz文件成功" << endl;
    outputFile.close();
}