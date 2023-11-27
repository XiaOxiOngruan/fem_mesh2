// ConsoleApplication3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "myread.h"
using namespace std;
pair<point, point> getpoint(int n,element e) {
    point p1;
    point p2;
    int ne = n + 1;
    switch (ne)
    {
    case 1:
        p1 = e.point1;
        p2 = e.point2;
        break;
    case 2:
        p1 = e.point1;
        p2 = e.point3;
        break;
    case 3:
        p1 = e.point1;
        p2 = e.point4;
        break;
    case 4:
        p1 = e.point2;
        p2 = e.point3;
        break;
    case 5:
        p1 = e.point2;
        p2 = e.point4;
        break;
    case 6:
        p1 = e.point3;
        p2 = e.point4;
        break;
    default:
        cout << "越界" <<ne<< endl;
        break;
    }
    return std::make_pair(p1, p2);
}

 point point_mesh(point p1 ,point p2){

     point p3{};
     for (int i = 1; i <= 3; i++) {
         p3.xyz[i-1] = 0.5 * (p1.xyz[i-1] + p2.xyz[i-1]);
     }
     return p3;
}
 element element_mesh(element& e,std::vector<Edgemesh>& edgemesh, vector<point>& point_vet){//单个单元依次遍历所有边
     int np = 6;
     point newp;
     size_t edge = 0;
     element newelement{};
     int qnsize = edgemesh.size();
     int size = 0;
     for (int i = 0; i < np; i++) {
         int i2 = i + 1;
         edge = e.edgeGlobalId[i]-1;//局部编号到全局编号
         if (edge >= edgemesh.size())
         {
             cout << "数组越界了" << endl;
             throw runtime_error("This is a manually thrown exception.");
         }
         if (edgemesh[edge].ifmesh==1)//加密
         {
             pair < point ,point >result = getpoint(i,e);
             newp = point_mesh(result.first, result.second);
             point_vet.push_back(newp);//创建中点
             size = point_vet.size();
             edgemesh[edge].ifmesh = 2;
             edgemesh[edge].pmeshed = newp;
             edgemesh[edge].gpmeshed = size;
             
             switch (i2) {           //生成新的单元
             case 1:
                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = newp;
                 newelement.pointGlobalId[1] = size;
                 newelement.point3 = e.point3;
                 newelement.pointGlobalId[2] = e.pointGlobalId[2];
                 newelement.point4 = e.point4;
                 newelement.pointGlobalId[3] = e.pointGlobalId[3];
                 newelement.edgeGlobalId[0] = qnsize;
                 newelement.edgeGlobalId[1] = e.edgeGlobalId[1];
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = qnsize;
                 newelement.edgeGlobalId[5] = e.edgeGlobalId[5];
                 e.edgeGlobalId[0] = qnsize;
                 e.edgeGlobalId[1] = qnsize;
                 e.edgeGlobalId[2] = qnsize;
                 e.point1 = newp;
                 e.pointGlobalId[0] = size;
                 break;
             case 2:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = e.point2;
                 newelement.pointGlobalId[1] = e.pointGlobalId[1];
                 newelement.point3 = newp;
                 newelement.pointGlobalId[2] = size;
                 newelement.point4 = e.point4;
                 newelement.pointGlobalId[3] = e.pointGlobalId[3];
                 newelement.edgeGlobalId[0] = e.edgeGlobalId[0];
                 newelement.edgeGlobalId[1] = qnsize;
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = e.edgeGlobalId[4];
                 newelement.edgeGlobalId[5] = qnsize;
                 e.edgeGlobalId[0] = qnsize;
                 e.edgeGlobalId[1] = qnsize;
                 e.edgeGlobalId[2] = qnsize;
                 e.point1 = newp;
                 e.pointGlobalId[0] = size;
                 break;
             case 3:
                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = e.point2;
                 newelement.pointGlobalId[1] = e.pointGlobalId[1];
                 newelement.point3 = e.point3;
                 newelement.pointGlobalId[2] = e.pointGlobalId[2];
                 newelement.point4 = newp;////////////////////////////////////
                 newelement.edgeGlobalId[0] = e.edgeGlobalId[0];
                 newelement.edgeGlobalId[1] = e.edgeGlobalId[1];
                 newelement.edgeGlobalId[3] = e.edgeGlobalId[3];
                 newelement.edgeGlobalId[5] = qnsize;
                 newelement.edgeGlobalId[2] = qnsize;
                 newelement.edgeGlobalId[4] = qnsize;
                 e.edgeGlobalId[0] = qnsize;
                 e.edgeGlobalId[1] = qnsize;
                 e.edgeGlobalId[2] = qnsize;
                 e.point1 = newp;
                 e.pointGlobalId[0] = size;
                 break;
             case 6:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = e.point2;
                 newelement.pointGlobalId[1] = e.pointGlobalId[1];
                 newelement.point3 = newp;
                 newelement.pointGlobalId[2] = size;
                 newelement.point4 = e.point4;
                 newelement.edgeGlobalId[0] = e.edgeGlobalId[0];
                 newelement.edgeGlobalId[1] = qnsize;
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = e.edgeGlobalId[4];
                 newelement.edgeGlobalId[5] = qnsize;
                 e.edgeGlobalId[2] = qnsize;
                 e.edgeGlobalId[4] = qnsize;
                 e.edgeGlobalId[5] = qnsize;
                 e.point4 = newp;
                 e.pointGlobalId[3] = size;
                 break;
             case 4:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = newp;
                 newelement.pointGlobalId[1] = size;
                 newelement.point3 = e.point3;
                 newelement.pointGlobalId[2] = e.pointGlobalId[2];
                 newelement.point4 = e.point4;
                 newelement.edgeGlobalId[0] = qnsize;
                 newelement.edgeGlobalId[1] = e.edgeGlobalId[1];
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = qnsize;
                 newelement.edgeGlobalId[5] = e.edgeGlobalId[5];
                 e.edgeGlobalId[1] = qnsize;
                 e.edgeGlobalId[3] = qnsize;
                 e.edgeGlobalId[5] = qnsize;
                 e.point3 = newp;
                 e.pointGlobalId[2] = size;
                 break;
             case 5:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = newp;
                 newelement.pointGlobalId[1] = size;
                 newelement.point3 = e.point3;
                 newelement.pointGlobalId[2] = e.pointGlobalId[2];
                 newelement.point4 = e.point4;
                 newelement.edgeGlobalId[0] = qnsize;
                 newelement.edgeGlobalId[1] = e.edgeGlobalId[1];
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = qnsize;
                 newelement.edgeGlobalId[5] = e.edgeGlobalId[5];                
                 e.edgeGlobalId[2] = qnsize;
                 e.edgeGlobalId[4] = qnsize;
                 e.edgeGlobalId[5] = qnsize;
                 e.point4 = newp;
                 e.pointGlobalId[3] = size;
                 break;
             }
             
         }
         else if (edgemesh[edge].ifmesh == 2) {
             size = edgemesh[edge].gpmeshed;
             newp= edgemesh[edge].pmeshed;
             switch (i2) {           //生成新的单元
             case 1:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = newp;
                 newelement.pointGlobalId[1] = size;
                 newelement.point3 = e.point3;
                 newelement.pointGlobalId[2] = e.pointGlobalId[2];
                 newelement.point4 = e.point4;
                 newelement.edgeGlobalId[0] = qnsize;
                 newelement.edgeGlobalId[1] = e.edgeGlobalId[1];
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = qnsize;
                 newelement.edgeGlobalId[5] = e.edgeGlobalId[5];
                 e.edgeGlobalId[0] = qnsize;
                 e.edgeGlobalId[1] = qnsize;
                 e.edgeGlobalId[2] = qnsize;
                     e.point1 = edgemesh[edge].pmeshed;
                 e.pointGlobalId[0] = size;
                 break;
             case 2:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = e.point2;
                 newelement.pointGlobalId[1] = e.pointGlobalId[1];
                 newelement.point3 = newp;
                 newelement.pointGlobalId[2] = size;
                 newelement.point4 = e.point4;
                 newelement.edgeGlobalId[0] = e.edgeGlobalId[0];
                 newelement.edgeGlobalId[1] = qnsize;
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = e.edgeGlobalId[4];
                 newelement.edgeGlobalId[5] = qnsize;
                 e.edgeGlobalId[0] = qnsize;
                 e.edgeGlobalId[1] = qnsize;
                 e.edgeGlobalId[2] = qnsize;
                 e.point1 = edgemesh[edge].pmeshed;
                 e.pointGlobalId[0] = size;
                 break;
             case 3:

                 newelement.point1 = e.point1;
                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = e.point2;
                 newelement.pointGlobalId[1] = e.pointGlobalId[1];
                 newelement.point3 = e.point3;
                 newelement.pointGlobalId[2] = e.pointGlobalId[2];
                 newelement.point4 = newp;
                 newelement.edgeGlobalId[0] = e.edgeGlobalId[0];
                 newelement.edgeGlobalId[1] = e.edgeGlobalId[1];
                 newelement.edgeGlobalId[3] = e.edgeGlobalId[3];
                 newelement.edgeGlobalId[5] = qnsize;
                 newelement.edgeGlobalId[2] = qnsize;
                 newelement.edgeGlobalId[4] = qnsize;
                 e.edgeGlobalId[0] = qnsize;
                 e.edgeGlobalId[1] = qnsize;
                 e.edgeGlobalId[2] = qnsize;
                 e.point1 = edgemesh[edge].pmeshed;
                 e.pointGlobalId[0] = size;
                 break;
             case 6:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = e.point2;
                 newelement.pointGlobalId[1] = e.pointGlobalId[1];
                 newelement.point3 = newp;
                 newelement.pointGlobalId[2] = size;
                 newelement.point4 = e.point4;
                 newelement.edgeGlobalId[0] = e.edgeGlobalId[0];
                 newelement.edgeGlobalId[1] = qnsize;
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = e.edgeGlobalId[4];
                 newelement.edgeGlobalId[5] = qnsize;
                 e.edgeGlobalId[2] = qnsize;
                 e.edgeGlobalId[4] = qnsize;
                 e.edgeGlobalId[5] = qnsize;
                 e.point4 = edgemesh[edge].pmeshed;
                 e.pointGlobalId[3] = size;
                 break;
             case 4:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = newp;
                 newelement.pointGlobalId[1] = size;
                 newelement.point3 = e.point3;
                 newelement.pointGlobalId[2] = e.pointGlobalId[2];
                 newelement.point4 = e.point4;
                 newelement.edgeGlobalId[0] = qnsize;
                 newelement.edgeGlobalId[1] = e.edgeGlobalId[1];
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = qnsize;
                 newelement.edgeGlobalId[5] = e.edgeGlobalId[5];
                 e.edgeGlobalId[1] = qnsize;
                 e.edgeGlobalId[3] = qnsize;
                 e.edgeGlobalId[5] = qnsize;
                 e.point3 = edgemesh[edge].pmeshed;
                 e.pointGlobalId[2] = size;
                 break;
             case 5:

                 newelement.point1 = e.point1;
                 newelement.pointGlobalId[0] = e.pointGlobalId[0];
                 newelement.point2 = newp;
                 newelement.pointGlobalId[1] = size;
                 newelement.point3 = e.point3;
                 newelement.pointGlobalId[2] = e.pointGlobalId[2];
                 newelement.point4 = e.point4;
                 newelement.edgeGlobalId[0] = qnsize;
                 newelement.edgeGlobalId[1] = e.edgeGlobalId[1];
                 newelement.edgeGlobalId[2] = e.edgeGlobalId[2];
                 newelement.edgeGlobalId[3] = qnsize;
                 newelement.edgeGlobalId[4] = qnsize;
                 newelement.edgeGlobalId[5] = e.edgeGlobalId[5];
                 e.edgeGlobalId[2] = qnsize;
                 e.edgeGlobalId[4] = qnsize;
                 e.edgeGlobalId[5] = qnsize;
                 e.point4 = edgemesh[edge].pmeshed;
                 e.pointGlobalId[3] = size;
                 break;
             }

         
         }
     }
     return newelement;
 }//对单个单元加密
int main() {
    int np;
    int lv;
    vector<Edgemesh> edgemesh;// 0不要加密 1需要加密且未加密 2加密过了
    vector<element> Element_vet;
    vector<point> point_vet;
    readFileData_xyz("cub1.xyz", point_vet, &np); ///点的坐标信息
    readFileData_lv("cub1.lv",Element_vet,point_vet,&lv);// 四面体单元信息
    readFileData_le("cub1.le", Element_vet);         //
    readFileData_mesh("cub1.re",edgemesh,0.03);   // 加密信息 加密百分比
    Edgemesh qnedge{};
    qnedge.ifmesh = 0;
    edgemesh.push_back(qnedge); //添加新的全局编号
    size_t i = 0;
    //读取加密文件
    element newe{};
    for (size_t it = 0; it < Element_vet.size(); ++it) {
        
        newe=element_mesh(Element_vet[it], edgemesh, point_vet);//执行加密
        if (newe.edgeGlobalId[0] > 0) {
            Element_vet.push_back(newe);
        }
        i++;
       // cout << Element_vet.size() << endl;
    }
    cout << "加密完成,新单元网格数量为：" << endl;
    //
    //cout << i << endl;
    cout << Element_vet.size() << endl;
    wxyz("newcub1.xyz", point_vet);
    wlv("newcub1.lv", Element_vet);
    return 0;
}



