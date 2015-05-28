//
//  SensitivityContext.cpp
//  Iacovino
//
//  Created by Roderick Mann on 5/20/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#include "SensitivityContext.h"






#include "MeltInclusion.h"








void spfa(std::string &s, const std::string fmt, ...)
{
    std::string ss;
    int n, size=100;
    bool b=false;
    va_list marker;

    while (!b)
    {
        ss.resize(size);
        va_start(marker, fmt);
        n = vsnprintf((char*)ss.c_str(), size, fmt.c_str(), marker);
        va_end(marker);
        if ((n>0) && ((b=(n<size))==true)) ss.resize(n); else size*=2;
    }
    s += ss;
}






#pragma mark - • SensitivityRunContext

SensitivityRunContext::SensitivityRunContext()
	:
	mMeans(5),
	mStdDevs(5)
{
	mInputNames.push_back("Temperature");
	mInputNames.push_back("Pressure");
	mInputNames.push_back("LogFH2O");
	mInputNames.push_back("LogFO2");
	mInputNames.push_back("LogFS2");
	
	mSpecies.push_back("CO");
	mSpecies.push_back("CO2");
	mSpecies.push_back("H2O");
	mSpecies.push_back("H2S");
	mSpecies.push_back("SO2");
}

void
SensitivityRunContext::sweepCompleted(size_t inInputVariable, MonteCarlo::SweepContext* inCTX)
{
	//std::printf("SensitivityRunContext::sweepCompleted\n");
	
	const SensitivityContext* ctx = static_cast<const SensitivityContext*> (inCTX);
	
	for (size_t i = 0; i < ctx->mMeans.size(); ++i)
	{
		mMeans[i].syncAdd(ctx->mMeans[i]);
		mStdDevs[i].syncAdd(ctx->mStdDevs[i]);
	}
}


void
SensitivityRunContext::runComplete(size_t inInputVariable)
{
#if 0
	std::printf("runComplete\n\n");
	
	std::printf("%s\n", mInputNames[inInputVariable].c_str());
	std::printf("      Means                       Std Deviations\n");
	std::printf("      Mean          StdDev        Mean          StdDev     \n");
	std::printf("      -----------   -----------   -----------   -----------\n");
	for (size_t i = 0; i < mMeans.size(); ++i)
	{
		std::printf("%3.3s:  %-11.5g   %-11.5g   %-11.5g   %-11.5g\n",
					mSpecies[i].c_str(),
					mMeans[i].mean(), mMeans[i].stdDev(), mStdDevs[i].mean(), mStdDevs[i].stdDev());
	}
	
	std::printf("\n\n");
#else
	
#endif
}

/**
	Builds a comma-separated string of all of the output values.
	
	e.g. CO mean mean, CO mean sigma, CO sigma mean, CO sigma sigma, CO2 mean mean, etc.
*/

std::string
SensitivityRunContext::csvPopulationsForSpecies(size_t inIdx) const
{
	std::string s;
	spfa(s, "%g,%g,%g,%g",
		mMeans[inIdx].mean(),
		mMeans[inIdx].stdDev(),
		mStdDevs[inIdx].mean(),
		mStdDevs[inIdx].stdDev());
		
	return s;
}




#pragma mark - • SensitivityContext

SensitivityContext::SensitivityContext()
	:
	mOutputs(5),
	mMeans(5),
	mStdDevs(5)
{
#if 0
	mCO.setName("CO");
	mCO2.setName("CO");
	mH2O.setName("CO");
	mH2S.setName("CO");
	mSO2.setName("CO");
#endif
}





void
SensitivityContext::sweepCollectionBegan()
{
}

void
SensitivityContext::sweepBegan()
{
}

bool
SensitivityContext::run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues)
{
	MeltInclusion	mi(inValues);
	mi.calcComposition();
	
	double	co, co2, h2o, h2s, so2;
	mi.depressurize(1.0, co, co2, h2o, h2s, so2);
	
	if (std::isnan(co))
	{
		return false;
	}
	
	mOutputs[0].add(co);
	mOutputs[1].add(co2);
	mOutputs[2].add(h2o);
	mOutputs[3].add(h2s);
	mOutputs[4].add(so2);
	
	return true;
}

void
SensitivityContext::sweepComplete()
{
#if o
	std::printf("SweepComplete\n");
	
	std::printf("      Mean          Sigma\n");
	std::printf("      -----------   -----------\n");
	std::printf("CO:   %-11.5g   %-11.5g\n", mOutputs[0].mean(), mOutputs[0].stdDev());
	std::printf("CO2:  %-11.5g   %-11.5g\n", mOutputs[1].mean(), mOutputs[1].stdDev());
	std::printf("H2O:  %-11.5g   %-11.5g\n", mOutputs[2].mean(), mOutputs[2].stdDev());
	std::printf("H2S:  %-11.5g   %-11.5g\n", mOutputs[3].mean(), mOutputs[3].stdDev());
	std::printf("SO2:  %-11.5g   %-11.5g\n", mOutputs[4].mean(), mOutputs[4].stdDev());
#endif
	
	for (size_t i = 0; i < mOutputs.size(); ++i)
	{
		mMeans[i].push_back(mOutputs[i].mean());
		mStdDevs[i].push_back(mOutputs[i].stdDev());
	}
}

void
SensitivityContext::sweepCollectionComplete(MonteCarlo::ValueListT& outMeans, MonteCarlo::ValueListT& outStdDevs)
{
}

#pragma mark - • BasaniteSensitivityContext

bool
BasaniteSensitivityContext::run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues)
{
	BasaniteMeltInclusion	mi(inValues);
	mi.calcComposition();
	
	double	co, co2, h2o, h2s, so2;
	mi.depressurize(1.0, co, co2, h2o, h2s, so2);
	
	if (std::isnan(co))
	{
		return false;
	}
	
	mOutputs[0].add(co);
	mOutputs[1].add(co2);
	mOutputs[2].add(h2o);
	mOutputs[3].add(h2s);
	mOutputs[4].add(so2);
	
	return true;
}





#pragma mark - • DeltaSensitivityContext

bool
DeltaSensitivityContext::run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues)
{
	MeltInclusion	mi(inValues);
	
	WeightPercents to(inValues[8], inValues[9], inValues[10]);
	mi.calcDeltaComposition(to, mFrac);
	
	double	co, co2, h2o, h2s, so2;
	mi.depressurize(1.0, co, co2, h2o, h2s, so2);
	
	if (std::isnan(co))
	{
		return false;
	}
	
	mOutputs[0].add(co);
	mOutputs[1].add(co2);
	mOutputs[2].add(h2o);
	mOutputs[3].add(h2s);
	mOutputs[4].add(so2);
	
	return true;
}




#pragma mark - • DeltaBasaniteSensitivityContext

bool
DeltaBasaniteSensitivityContext::run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues)
{
	BasaniteMeltInclusion	mi(inValues);
	
	WeightPercents to(inValues[8], inValues[9], inValues[10]);
	mi.calcDeltaComposition(to, mFrac);
	
	double	co, co2, h2o, h2s, so2;
	mi.depressurize(1.0, co, co2, h2o, h2s, so2);
	
	if (std::isnan(co))
	{
		return false;
	}
	
	mOutputs[0].add(co);
	mOutputs[1].add(co2);
	mOutputs[2].add(h2o);
	mOutputs[3].add(h2s);
	mOutputs[4].add(so2);
	
	return true;
}
