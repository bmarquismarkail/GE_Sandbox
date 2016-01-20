#include <cstring>
#include <iostream>
using namespace std;

#include "TMX_Map.h"

TMX_Layer::TMX_Layer()
{
	Opacity = 1;
	Visible = true;
}

TMX_Layer::TMX_Layer(char *data, xml_node<> *node)
{
	Load_Layer(data, node);
}

void TMX_Layer::Load_Layer(char *data, xml_node<> *node)
{
	if(xml_attribute<> *iattr = node->first_attribute("name"))		Name		= iattr->value();
	if(xml_attribute<> *iattr = node->first_attribute("opacity"))	Opacity		= atof(iattr->value()); else Opacity = 1.0;
	if(xml_attribute<> *iattr = node->first_attribute("visible"))	Visible		= atoi(iattr->value()); else Visible = 1;
	for(xml_node<> *iNode = node->first_node() ; iNode; iNode = iNode->next_sibling() )
	{
		if(!strcmp(iNode->name(), "data"))
		{
			TMX_Data tmp_Data(data, iNode);
			Data.push_back(tmp_Data);
		}
	}
}

TMX_Data TMX_Layer::getData()
{
	return Data.at(0);
}

bool TMX_Layer::isVisible()
{
	return Visible;
}

float TMX_Layer::getOpacity()
{
	return Opacity;
}
