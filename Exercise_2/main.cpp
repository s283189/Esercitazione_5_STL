#include "Eigen/Eigen"
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        return 1;
    }

    return 0;
}
