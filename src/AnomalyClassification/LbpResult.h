#ifndef LbpResult_H
#define LbpResult_H

class LbpResult
{
private:
	int lbp;
	int uniformity;

public:
	LbpResult(int lbp, int uniformity)
	{
		this->lbp = lbp;
		this->uniformity = uniformity;
	}

	int getLbp(){ return this->lbp; }
	int getUniformity() { return this->uniformity; }
};

#endif