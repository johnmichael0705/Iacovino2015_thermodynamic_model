//
//  CharacterizationContext.h
//  Iacovino
//
//  Created by Roderick Mann on 5/14/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#ifndef __Iacovino__CharacterizationContext__
#define __Iacovino__CharacterizationContext__


#include <vector>

#import "Histogram.h"
#import "MonteCarlo.h"





class
CharacterizationContext : public MonteCarlo::SweepContext
{
public:
							CharacterizationContext();
	
	virtual	void			sweepCollectionBegan();
	virtual	void			sweepBegan();
	virtual	bool			run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues);
	virtual	void			sweepComplete();
	virtual	void			sweepCollectionComplete(MonteCarlo::ValueListT& outMeans, MonteCarlo::ValueListT& outStdDevs);
	
	DynamicHistogram		mTemp;
	DynamicHistogram		mPressure;
	DynamicHistogram		mLogFH2O;
	DynamicHistogram		mLogFO2;
	DynamicHistogram		mLogFS2;
	
	DynamicHistogram		mCO;
	DynamicHistogram		mCO2;
	DynamicHistogram		mH2O;
	DynamicHistogram		mH2S;
	DynamicHistogram		mSO2;

private:
};





#endif /* defined(__Iacovino__CharacterizationContext__) */
