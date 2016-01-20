#include <cstring>
using namespace std;

#include "TMX_Map.h"

TMX_Image::TMX_Image()
{

}

TMX_Image::TMX_Image(char *data, xml_node<> *node)
{
	Load_Image(data, node);
}

void TMX_Image::Load_Image(char *data, xml_node<> *node)
{
	if(xml_attribute<> *iattr = node->first_attribute("format"))	Format	= iattr->value();
	if(xml_attribute<> *iattr = node->first_attribute("id"))		ID		= iattr->value();
	if(xml_attribute<> *iattr = node->first_attribute("source"))	Source	= iattr->value();
	if(xml_attribute<> *iattr = node->first_attribute("trans"))		Trans	= strtoul( iattr->value(), NULL, 16);
	if(xml_attribute<> *iattr = node->first_attribute("width"))		Width	= strtoul( iattr->value(), NULL, 10 );
	if(xml_attribute<> *iattr = node->first_attribute("height"))	Height	= strtoul( iattr->value(), NULL, 10 );
	for(xml_node<> *iNode = node->first_node() ; iNode; iNode = iNode->next_sibling() )
	{
		if(!strcmp(iNode->name(), "image"))
		{
			TMX_Data tmp_Data(data, node);
			Data.push_back(tmp_Data);
		}
	}
}


string TMX_Image::getFilename()
{
	return Source;
}
unsigned long TMX_Image::getWidth()
{
	return Width;
}
unsigned long TMX_Image::getHeight()
{
	return Height;
}

unsigned long TMX_Image::getTrans()
{
	return Trans;
}
