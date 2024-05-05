#ifndef ColorLib_H
#define ColorLib_H

class ColorLib
{
public:
	double l;
	double a;
	double b;

	ColorLib() 
	{	
		this->l = 0;
		this->a = 0;
		this->b = 0;
	}

	ColorLib(double l, double a, double b)
	{
		this->l = l;
		this->a = a;
		this->b = b;
	}
};

#endif