#include <cstring>
using namespace std;

#include "TMX_Map.h"

TMX_Tile::TMX_Tile()
{

}

TMX_Tile::TMX_Tile(char *data, xml_node<> *node)
{
    Load_Tile(data, node);
}

void TMX_Tile::Load_Tile(char *data, xml_node<> *node)
{
    if(xml_attribute<> *iattr = node->first_attribute("gid"))         ID = atoi(iattr->value());
    if(xml_attribute<> *iattr = node->first_attribute("id"))          ID = atoi(iattr->value());
    //if(xml_attribute<> *iattr = node->first_attribute("terrain")) Terrain
    if(xml_attribute<> *iattr = node->first_attribute("probability")) Probability = iattr->value();
}
