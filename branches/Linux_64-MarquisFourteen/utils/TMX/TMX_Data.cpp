#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TMX_Map.h"

TMX_Data::TMX_Data()
{

}

TMX_Data::TMX_Data(char *data, xml_node<> *node)
{
	Load_Data(data, node);
}

void TMX_Data::Load_Data(char *data, xml_node<> *node)
{
	if(xml_attribute<> *iattr = node->first_attribute("encoding"))		Encoding   = iattr->value();
    if(xml_attribute<> *iattr = node->first_attribute("compression"))	Compression	  = iattr->value();
	else Compression = "";
																		Value	= node->value();
	Value.erase(remove_if(Value.begin(), Value.end(), ::isspace), Value.end());

	for(xml_node<> *iNode = node->first_node() ; iNode; iNode = iNode->next_sibling() )
	{
		if(!strcmp(iNode->name(), "tile"))
		{
			TMX_Tile tmp_Tile(data, node);
			Tile.push_back(tmp_Tile);
		}
	}
}


string TMX_Data::getEncoding()
{
	return Encoding;
}

string TMX_Data::getCompression()
{
	return Compression;
}

string TMX_Data::getData()
{
	return Value;
}

vector<TMX_Tile> TMX_Data::getTileData()
{
	return Tile;
}
