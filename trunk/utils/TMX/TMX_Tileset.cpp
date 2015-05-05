#include <cstring>
using namespace std;

#include "TMX_Map.h"


TMX_Tileset::TMX_Tileset()
{
    firstgid   = 0;
    source     = "";
    name       = "";
    tilewidth  = 0;
    tileheight = 0;
    spacing    = 0;
    margin     = 0;
}

TMX_Tileset::TMX_Tileset(char *data, xml_node<> *node)
{
    Load_Tileset(data, node);
}

void TMX_Tileset::Load_Tileset(char *data, xml_node<> *node)
{
    if(xml_attribute<> *iattr = node->first_attribute("firstgid"))   firstgid   = atoi(iattr->value());
    if(xml_attribute<> *iattr = node->first_attribute("source"))     source     = iattr->value();
    if(xml_attribute<> *iattr = node->first_attribute("name"))       name       = iattr->value();
    if(xml_attribute<> *iattr = node->first_attribute("tilewidth"))  tilewidth  = strtoul(iattr->value(), NULL, 0);
    if(xml_attribute<> *iattr = node->first_attribute("tileheight")) tileheight = strtoul(iattr->value(), NULL, 0);
    if(xml_attribute<> *iattr = node->first_attribute("spacing"))    spacing    = atoi(iattr->value()); else spacing = 0;
    if(xml_attribute<> *iattr = node->first_attribute("margin"))     margin     = atoi(iattr->value()); else margin = 0;
    for(xml_node<> *iNode = node->first_node() ; iNode; iNode = iNode->next_sibling() )
    {
        //if(!strcmp(iNode->name(), "tileoffset"))
        //if(!strcmp(iNode->name(), "properties"))
        if(!strcmp(iNode->name(), "image"))
        {
            TMX_Image tmp_Image(data, iNode);
            Image.push_back(tmp_Image);
        }
        //if(!strcmp(iNode->name(), "terraintypes"))
        //if(!strcmp(iNode->name(), "tile"))
    }
}

string TMX_Tileset::getName()
{
    return name;
}

TMX_Image TMX_Tileset::getImage(unsigned index)
{
    return Image.at(index);
}

unsigned long TMX_Tileset::getTileWidth()
{
    return tilewidth;
}

unsigned long TMX_Tileset::getTileHeight()
{
    return tileheight;
}

unsigned int TMX_Tileset::getSpacing()
{
    return spacing;
}

unsigned int TMX_Tileset::getGID()
{
    return firstgid;
}

string TMX_Tileset::getSource()
{
    return source;
}
