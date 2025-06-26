#include <string>
#include "text.h"

Text::Text() : Entity(0, 0, 0, 0, 0){}

Text::Text(std::string text, double xPos, double yPos, double width, double height, int layerMask) :
Entity(xPos, yPos, width, height, layerMask)
{

}