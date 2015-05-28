//
//  SearchMix.h
//  Iacovino
//
//  Created by Roderick Mann on 5/5/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#ifndef __Iacovino__SearchMix__
#define __Iacovino__SearchMix__

#include <vector>

class BasaniteDissolvedVolatiles;
class DissolvedVolatiles;
class MeltInclusion;



class
SearchMix
{
public:
	typedef	double			MixValT;

	void					add(const MeltInclusion& inMelt, double inPressure);
	void					add(double inCO, double inCO2, double inH2O, double inH2S, double inSO2);
	
	void					search();
	
	void					dump() const;

//protected:
	double
	getVals(int a, int b, int c, int d, int e, int f, int g, const std::vector<MixValT>& inV) const
	{
		return		a * inV[0]
				+	b * inV[1]
				+	c * inV[2]
				+	d * inV[3]
				+	e * inV[4]
				+	f * inV[5]
				+	g * inV[6];
	}
	
	void					dumpLine(const std::vector<MixValT>& inV) const;
	
//private:
	std::vector<MixValT>	mCOVals;
	std::vector<MixValT>	mCO2Vals;
	std::vector<MixValT>	mH2OVals;
	std::vector<MixValT>	mH2SVals;
	std::vector<MixValT>	mSO2Vals;
};

#endif /* defined(__Iacovino__SearchMix__) */
