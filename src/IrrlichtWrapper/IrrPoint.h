#ifndef IrrPoint_h
#define IrrPoint_h

class IrrPoint
{
public:
	virtual bool operator== (IrrPoint& a) = 0;
	virtual bool operator== (IrrPoint* a) = 0;
	virtual bool operator== (const IrrPoint& a) = 0;
	virtual bool operator== (const IrrPoint* a) = 0;

	virtual bool operator<(const IrrPoint& a) const = 0;

	virtual double getX() const = 0;
	virtual double getY() const = 0;
};

#endif