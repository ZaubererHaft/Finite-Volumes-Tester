#include "Domain.h"

Domain::Domain(double xStart, double xEnd) : xStart{xStart}, xEnd{xEnd}, size{xEnd - xStart} {

}

double Domain::getXStart() const {
    return xStart;
}

double Domain::getXEnd() const {
    return xEnd;
}

double Domain::getSize() const {
    return size;
}
