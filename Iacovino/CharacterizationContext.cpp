//
//  CharacterizationContext.cpp
//  Iacovino
//
//  Created by Roderick Mann on 5/14/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#include "CharacterizationContext.h"




#include "MeltInclusion.h"

















CharacterizationContext::CharacterizationContext()
{
	mLogFO2.setName("log FO2");
}





void
CharacterizationContext::sweepCollectionBegan()
{
}

void
CharacterizationContext::sweepBegan()
{
}

bool
CharacterizationContext::run(const MonteCarlo::ValueListT& inValues, MonteCarlo::ValueListT& outValues)
{
	mTemp.add(inValues[0]);
	mPressure.add(inValues[1]);
	mLogFH2O.add(inValues[2]);
	mLogFO2.add(inValues[3]);
	mLogFS2.add(inValues[4]);
	
	MeltInclusion	mi(inValues[0], inValues[1], inValues[2], inValues[3], inValues[4]);
	mi.calcComposition();
	
	double	co, co2, h2o, h2s, so2;
	mi.depressurize(1.0, co, co2, h2o, h2s, so2);
	
	mCO.add(co);
	mCO2.add(co2);
	mH2O.add(h2o);
	mH2S.add(h2s);
	mSO2.add(so2);
	
	return true;
}

void
CharacterizationContext::sweepComplete()
{
}

void
CharacterizationContext::sweepCollectionComplete(MonteCarlo::ValueListT& outMeans, MonteCarlo::ValueListT& outStdDevs)
{
	Histogram::SizeT numBins = 100;
	
	mTemp.sort(numBins);
	mPressure.sort(numBins);
	mLogFH2O.sort(numBins);
	mLogFO2.sort(numBins);
	mLogFS2.sort(numBins);
	
	mCO.sort(numBins);
	mCO2.sort(numBins);
	mH2O.sort(numBins);
	mH2S.sort(numBins);
	mSO2.sort(numBins);
}


