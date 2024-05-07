#include <iostream>
#include <fstream>
#include <sstream>
#include "Eigen/Eigen"
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;

inline void fixstr(string& line)
{
    for(unsigned int i = 0; i < line.length(); i++)
    {
        if(line[i] == ';')
            line.replace(i, 1, " ");
    }
    return;
}

bool ImportMesh(PolygonalMesh& mesh)
{
    if(!ImportCell0Ds(mesh))
        return false;
    else
    {
        cout<<"Cell0D Number of cells: "<<mesh.numberCell0D<<endl;
        cout<<"Cell0Ds: markers" <<endl;
        for(auto it=mesh.Cell0DMarkers.begin(); it!=mesh.Cell0DMarkers.end(); it++)
        {
            cout<<"Marker: "<<it->first<<"  Values: ";
            for(unsigned int value: it->second)
                cout<<"\t"<<value;
            cout<<endl;
        }
    }
    cout<<endl;

    if(!ImportCell1Ds(mesh))
        return false;
    else
    {
        cout<<"Cell1D Number of cells: "<<mesh.numberCell1D<<endl;
        cout<<"Cell1Ds: markers" <<endl;
        for(auto it=mesh.Cell1DMarkers.begin(); it!=mesh.Cell1DMarkers.end(); it++)
        {
            cout<<"Marker: "<<it->first<<"  Values: ";
            for(unsigned int value: it->second)
                cout<<"\t"<<value;
            cout<<endl;
        }
    }
    cout<<endl;

    if(!ImportCell2Ds(mesh))
        return false;
    else
    {
        cout<<"Cell2D Number of cells: "<<mesh.numberCell2D<<endl;
        //test
        for(unsigned int i = 0; i < mesh.numberCell2D; i++)
        {
            if(mesh.Cell2DNumVertices[i] != mesh.Cell2DNumEdges[i])
            {
                cerr<<"Number of vertices and edges in a cell must be the same."<<endl;
                return false;
            }
        }

    }

    return true;
}

bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file("./PolygonalMesh/Cell0Ds.csv");
    if(file.fail())
        return false;

    string line;
    unsigned int id;
    unsigned int marker;
    Vector2d coordinates;

    mesh.numberCell0D = 0;
    getline(file,line);
    while(getline(file,line))
    {
        fixstr(line);
        istringstream convert(line);
        convert >> id >> marker >> coordinates(0) >> coordinates(1);

        mesh.numberCell0D++;
        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coordinates);

        if(marker != 0)
        {
            if(mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
                mesh.Cell0DMarkers.insert({marker, {id}});
            else
                mesh.Cell0DMarkers[marker].push_back(id);
        }
    }

    file.close();
    return true;
}

bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file("./PolygonalMesh/Cell1Ds.csv");
    if(file.fail())
        return false;

    string line;
    unsigned int id;
    unsigned int marker;
    Vector2i vertices;

    mesh.numberCell1D = 0;
    getline(file,line);
    while(getline(file,line))
    {
        fixstr(line);
        istringstream convert(line);
        convert >> id >> marker >> vertices(0) >> vertices(1);

        mesh.numberCell1D++;
        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vertices);

        if(marker != 0)
        {
            if(mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
                mesh.Cell1DMarkers.insert({marker, {id}});
            else
                mesh.Cell1DMarkers[marker].push_back(id);
        }
    }

    file.close();
    return true;
}

bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file("./PolygonalMesh/Cell2Ds.csv");
    if(file.fail())
        return false;

    string line;
    unsigned int id;
    unsigned int marker;
    unsigned int numVertices;
    unsigned int numEdges;
    unsigned int vertex;
    unsigned int edge;
    vector<unsigned int> vertices;
    vector<unsigned int> edges;

    mesh.numberCell2D = 0;
    getline(file,line);
    while(getline(file,line))
    {
        fixstr(line);
        istringstream convert(line);

        convert >> id >> marker >> numVertices;
        vertices.resize(numVertices);
        for(unsigned int i=0; i < numVertices; i++)
        {
            convert >> vertex;
            vertices.push_back(vertex);
        }
        edges.resize(numEdges);
        convert >> numEdges;
        for(unsigned int i=0; i < numEdges; i++)
        {
            convert >> edge;
            edges.push_back(edge);
        }

        mesh.numberCell2D++;
        mesh.Cell2DId.push_back(id);
        mesh.Cell2DNumVertices.push_back(numVertices);
        mesh.Cell2DNumEdges.push_back(numEdges);
        mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DEdges.push_back(edges);
    }

    file.close();
    return true;
}
