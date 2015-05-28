//
//  SensitivityContext.h
//  Iacovino
//
//  Created by Roderick Mann on 5/20/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#ifndef __Iacovino__SensitivityContext__
#define __Iacovino__SensitivityContext__

#include <string>
#include <vector>

#import "Histogram.h"
#import "MonteCarlo.h"




class
SensitivityRunContext : public MonteCarlo::RunContext
{
public:
							SensitivityRunContext();
	
	virtual	void			sweepCompleted(size_t inInputVariable, MonteCarlo::SweepContext* inCTX);
	virtual	void			runComplete(size_t inInputVariable);
	
	std::string				csvPopulationsForSpecies(size_t inIdx) const;
	
	std::vector<std::string>				mInputNames;
	std::vector<std::string>				mSpecies;
	std::vector<VarianceAccumulator>		mMeans;		//	One for each gas species (CO, CO2, H2O, H2S, SO2)
	std::vector<VarianceAccumulator>		mStdDevs;	//	One for each gas species (CO, CO2, H2O, H2S, SO2)
};

class
SensitivityContext : public MonteCarlo::SweepContext
{
public:
							SensitivityContext();
	
	virtual	void			sweepCollectionBegan();
	virtual	void			sweepBegan();
	virtual	bool			run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues);
	virtual	void			sweepComplete();
	virtual	void			sweepCollectionComplete(MonteCarlo::ValueListT& outMeans, MonteCarlo::ValueListT& outStdDevs);
	
	typedef	std::vector<double>				ValueListT;
	
	std::vector<VarianceAccumulator>		mOutputs;	//	One for each gas species (CO, CO2, H2O, H2S, SO2)
	
	std::vector<ValueListT>					mMeans;		//	List of output values, one for each species
	std::vector<ValueListT>					mStdDevs;	//	same

private:
};








#pragma mark -

class
BasaniteSensitivityContext : public SensitivityContext
{
public:
	virtual	bool			run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues);
};







#pragma mark -

class
DeltaSensitivityContext : public SensitivityContext
{
public:
	DeltaSensitivityContext(double inFrac)
		:
		mFrac(inFrac)
	{
	}
	
	virtual	bool			run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues);

protected:
	double					mFrac;
};







#pragma mark -

class
DeltaBasaniteSensitivityContext : public DeltaSensitivityContext
{
public:
	DeltaBasaniteSensitivityContext(double inFrac)
		:
		DeltaSensitivityContext(inFrac)
	{
	}
	
	virtual	bool			run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues);
};

#endif /* defined(__Iacovino__SensitivityContext__) */
