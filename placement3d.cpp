#include "placement3d.h"

#include <iostream>
using namespace std;

std::vector<Box> Placement3D::LoadBoxesFromFile(const std::string& fileName)
{
    cout << "Hello World" << endl;
    return std::vector<Box>();
}

bool Placement3D::SaveBoxesToFile(const std::string& fileName, const std::vector<Box>& boxes)
{

}

Placement3D::Placement3D(const std::vector<Box> &boxes)
    : boxes(boxes)
{

}

Placement3D::~Placement3D()
{

}
