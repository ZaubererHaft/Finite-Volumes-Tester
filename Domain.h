/**
 * \file
 * \{
 * \defgroup 
 * \{
 * \ingroup  
 * \brief    
 * \details  
 *
 * \author   l.kratzl
 */


#ifndef FVM_DOMAIN_H
#define FVM_DOMAIN_H


class Domain {
public:
    Domain(double xStart, double xEnd);

    double getXStart() const;

    double getXEnd() const;

    double getSize() const;

private:
    double xStart;
    double xEnd;
    double size;
};


#endif //FVM_DOMAIN_H

/**
* \}
* \}
*/