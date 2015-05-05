#ifndef TMX_MAP_H_INCLUDED
#define TMX_MAP_H_INCLUDED

#include <string>
#include <vector>
using namespace std;

#include <rapidxml.hpp>
using namespace rapidxml;

struct TMX_Property
{
    string name;
    string value;
};

struct TMX_Properties
{
    vector<TMX_Property> Property;
};

struct TMX_TileOffset
{
    long X;
    long Y;
};

class TMX_Tile
{
public:
    TMX_Tile();
    TMX_Tile(char *data, xml_node<> *node);
    void Load_Tile(char *data, xml_node<> *node);
private:
    unsigned int            ID;
    vector<unsigned int[4]> Terrain;
    string                  Probability;
};

class TMX_Data
{
public:
    TMX_Data();
    TMX_Data(char *data, xml_node<> *node);
    void Load_Data(char *data, xml_node<> *node);
    string getEncoding();
    string getCompression();
    string getData();
    vector<TMX_Tile> getTileData();
private:
    string Encoding;
    string Compression;
    string Value;
    vector<TMX_Tile> Tile;
};

class TMX_Image
{
public:
    TMX_Image();
    TMX_Image(char* data, xml_node<> *node);
    void Load_Image(char* data, xml_node<> *node);
    string getFilename();
    unsigned long getWidth();
    unsigned long getHeight();
    unsigned long getTrans();
private:
    string Format;
    string ID;
    string Source;
    unsigned long Trans;
    unsigned long Width;
    unsigned long Height;
    vector<TMX_Data> Data;
};

struct TMX_Point
{
    long X;
    long Y;
};

struct TMX_Polyline
{
    vector<TMX_Point> Point;
};

struct TMX_Polygon
{
    vector<TMX_Point> Point;
};

struct TMX_Ellipse
{
    long X;
    long Y;
    unsigned long Width;
    unsigned long Height;
};

struct TMX_Object
{

    string name;
    string type;
    long X;
    long Y;
    unsigned long Width;
    unsigned long Height;
    int Rotation;
    unsigned int gid;
    bool Visible;
    vector<TMX_Properties> Properties;
    vector<TMX_Ellipse>    Ellipse;
    vector<TMX_Polygon>    Polygon;
    vector<TMX_Polyline>   Polyline;
    vector<TMX_Image>      Image;
};

struct TMX_ObjectGroup
{
    string name;
    string color;
    unsigned int X;
    unsigned int Y;
    long Width;
    long Height;
    float Opacity;
    bool Visible;
};

struct TMX_Imagelayer
{
   string Name;
   float  Opacity;
   bool   Visible;
   vector<TMX_Properties> Property;
   vector<TMX_Image>      Image;
};

struct TMX_Terrain
{
    string name;
    unsigned int           ID;
    vector<TMX_Properties> Properties;
};

struct TMX_TerrainType
{
    vector<TMX_Terrain> Terrain;
};

class TMX_Tileset
{
public:
    TMX_Tileset();
    TMX_Tileset(char *data, xml_node<> *node);
    void Load_Tileset(char *data, xml_node<> *node);
    string getName();
    TMX_Image getImage(unsigned index);
    unsigned long getTileWidth();
    unsigned long getTileHeight();
    unsigned int getSpacing();
    unsigned int getGID();
    string getSource();
private:
    unsigned int firstgid;
    string source;
    string name;
    unsigned long tilewidth;
    unsigned long tileheight;
    unsigned int spacing;
    unsigned int margin;
    vector<TMX_TileOffset>  Offset;
    vector<TMX_Properties>  Properties;
    vector<TMX_Image>       Image;
    vector<TMX_TerrainType> Terraintype;
    vector<TMX_Tile>        Tile;
};


class TMX_Layer
{
public:
    TMX_Layer();
    TMX_Layer (char *data, xml_node<> *node);
    void Load_Layer(char *data, xml_node<> *node);
    unsigned long getWidth();
    unsigned long getHeight();
    TMX_Data getData();
    bool isVisible();
    float getOpacity();
private:
    string Name;
    unsigned int           X;
    unsigned int           Y;
    unsigned long          Width;
    unsigned long          Height;
    float                  Opacity;
    bool                   Visible;
    vector<TMX_Properties> Properties;
    vector<TMX_Data>       Data;
};

class TMX_Map
{
public:
    TMX_Map();
    TMX_Map(const char* fn);
    void Load_Map(char* data);
    string getMapFile();
    string getVersion();
    string getOrientation();
    unsigned long getWidth();
    unsigned long getHeight();
    unsigned long getTileWidth();
    unsigned long getTileHeight();
    string getBackgroundColor();
    TMX_Tileset getTileset(unsigned index);
    TMX_Layer getLayer(unsigned index);
    unsigned findTileset(unsigned int GID);
    unsigned getNumLayers();
    unsigned getNumTilesets();
private:
    string Filename;
    string Version;
    string Orientation;
    unsigned long Width;
    unsigned long Height;
    unsigned long TileWidth;
    unsigned long TileHeight;
    string BackgroundColor;
    vector<TMX_Properties>  Properties;
    vector<TMX_Tileset>     Tileset;
    vector<TMX_Layer>       Layer;
    vector<TMX_ObjectGroup> ObjGroup;
    vector<TMX_Imagelayer>  ImgLayer;
};



#endif // TMX_MAP_H_INCLUDED
