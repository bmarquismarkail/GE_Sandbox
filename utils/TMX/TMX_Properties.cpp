#include <cstring>
using namespace std;

#include "TMX_Map.h"

TMX_Properties::TMX_Properties()
{

}


TMX_Properties::TMX_Properties(char *data, xml_node<> *node)
{
    Load_Properties(data, node);
}

void TMX_Properties::Load_Properties(char *data, xml_node<> *node)
{
	for(xml_node<> *iNode = node->first_node() ; iNode; iNode = iNode->next_sibling() )
	{
		if(!strcmp(iNode->name(), "property"))
		{
			TMX_Property tmp_Property(data, iNode);
			Property.push_back(tmp_Property);
		}
	}
}


TMX_Property TMX_Properties::getProperty(unsigned index)
{
    return Property.at(index);
}

TMX_Property TMX_Properties::getProperty(const char *name)
{
    for(vector<TMX_Property>::iterator it = Property.begin() ; it != Property.end() ; ++it )
        if (std::strcmp(it->getName().c_str(), name))
            return *it;
    return *Property.end();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
TMX_Property::TMX_Property()
{
    name = "";
    value = "";
}

TMX_Property::TMX_Property(char *data, xml_node<> *node)
{
    Load_Property(data, node);
}

void TMX_Property::Load_Property(char* data, xml_node<> *node)
{
    if(xml_attribute<> *iattr = node->first_attribute("name"))	name	= iattr->value();
    if(xml_attribute<> *iattr = node->first_attribute("value"))	value	= iattr->value();
}


string TMX_Property::getName() {return name;}
string TMX_Property::getValue() {return value;}
