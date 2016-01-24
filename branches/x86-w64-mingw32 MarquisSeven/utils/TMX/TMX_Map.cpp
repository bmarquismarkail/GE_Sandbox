#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

#include <rapidxml/rapidxml.hpp>

#include "TMX_Map.h"


TMX_Map::TMX_Map(const char* fn)
{
	Filename.assign(fn);
	ifstream in_xml(Filename.c_str(), ifstream::in);
	if (!in_xml.is_open())
		exit(-1);
	stringstream *ss_xml = new stringstream;
	*ss_xml << in_xml.rdbuf();
	char *xml_data = new char[ss_xml->str().length()+1]();
	strcpy(xml_data, ss_xml->str().c_str());
	in_xml.close();
	delete ss_xml;
	Load_Map(xml_data);

}

TMX_Map::TMX_Map()
{
	Filename		= "";
	Orientation		= "";
	Width			= 0;
	Height			= 0;
	TileWidth		= 0;
	TileHeight		= 0;
	BackgroundColor = "";

}

void TMX_Map::Load_Map(char *data)
{
	rapidxml::xml_document<> *doc = new rapidxml::xml_document<>;
	doc->parse<0>(data);
	rapidxml::xml_node<> *pRoot = doc->first_node();

	if(pRoot->first_attribute("version"))			Version.assign(pRoot->first_attribute("version")->value());
	if(pRoot->first_attribute("orientation"))		Orientation.assign(pRoot->first_attribute("orientation")->value());
	if(pRoot->first_attribute("width"))				Width = strtoul(pRoot->first_attribute("width")->value(), NULL, 0);
	if(pRoot->first_attribute("height"))			Height = strtoul(pRoot->first_attribute("height")->value(), NULL, 0);
	if(pRoot->first_attribute("tilewidth"))			TileWidth = strtoul(pRoot->first_attribute("tilewidth")->value(), NULL, 0);
	if(pRoot->first_attribute("tileheight"))		TileHeight = strtoul(pRoot->first_attribute("tileheight")->value(), NULL, 0);
	if(pRoot->first_attribute("backgroundcolor"))	BackgroundColor.assign (pRoot->first_attribute("backgroundcolor")->value());
	for (rapidxml::xml_node<> *iNode = pRoot->first_node() ; iNode ; iNode = iNode->next_sibling())
	{
		if (!strcmp(iNode->name(), "properties"))
		{
			TMX_Properties tmp_Properties(data, iNode);
			Properties.push_back(tmp_Properties);
		}
		if (!strcmp(iNode->name(), "tileset"))
		{
			TMX_Tileset tmp_Tileset(data, iNode);
			Tileset.push_back(tmp_Tileset);
		}
		if (!strcmp(iNode->name(), "layer"))
		{
			TMX_Layer tmp_Layer(data, iNode);
			Layer.push_back(tmp_Layer);
		}

	}
}

string TMX_Map::getMapFile()
{
	return Filename;
}

string TMX_Map::getVersion()
{
	return Version;
}

string TMX_Map::getOrientation()
{
	return Orientation;
}

unsigned long TMX_Map::getWidth()
{
	return Width;
}

unsigned long TMX_Map::getHeight()
{
	return Height;
}

unsigned long TMX_Map::getTileWidth()
{
	return TileWidth;
}

unsigned long TMX_Map::getTileHeight()
{
	return TileHeight;
}

string TMX_Map::getBackgroundColor()
{
	return BackgroundColor;
}

TMX_Properties TMX_Map::getProperties(unsigned index)
{
    return Properties.at(index);
}

TMX_Tileset TMX_Map::getTileset(unsigned index)
{
	return Tileset.at(index);
}

TMX_Layer TMX_Map::getLayer(unsigned index)
{
	return Layer.at(index);
}

unsigned TMX_Map::findTileset(unsigned int GID)
{
	for( int i = Tileset.size()-1; i > -1; --i)
	{
		if (GID >= Tileset[i].getGID())
			return i;
	}
	return -1;
}

unsigned TMX_Map::getNumLayers()
{
	return Layer.size();
}

unsigned TMX_Map::getNumTilesets()
{
	return Tileset.size();
}
