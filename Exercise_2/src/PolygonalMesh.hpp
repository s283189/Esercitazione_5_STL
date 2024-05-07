#pragma once

#include "Eigen/Eigen"
#include "map"

using namespace Eigen;
using namespace std;

struct PolygonalMesh
{
    unsigned int numberCell0D;
    unsigned int numberCell1D;
    unsigned int numberCell2D;

    //Cell0D
    vector<unsigned int> Cell0DId;
    vector<Vector2d> Cell0DCoordinates;
    map<unsigned int, list<unsigned int>> Cell0DMarkers;

    //Cell1D
    vector<unsigned int> Cell1DId;
    vector<Vector2i> Cell1DVertices;
    map<unsigned int, list<unsigned int>> Cell1DMarkers;

    //Cell2D
    vector<unsigned int> Cell2DId;
    vector<unsigned int> Cell2DNumVertices;
    vector<unsigned int> Cell2DNumEdges;
    vector<vector<unsigned int>> Cell2DVertices;
    vector<vector<unsigned int>> Cell2DEdges;
    map<unsigned int, list<unsigned int>> Cell2DMarkers;
};

bool ImportMesh(PolygonalMesh& mesh);

bool ImportCell0Ds(PolygonalMesh& mesh);

bool ImportCell1Ds(PolygonalMesh& mesh);

bool ImportCell2Ds(PolygonalMesh& mesh);

