//
//  MonteCarlo.cpp
//  Iacovino
//
//  Created by Roderick Mann on 5/10/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#include "MonteCarlo.h"


#include <dispatch/dispatch.h>








InputVariable::InputVariable(const std::string& inName, double inMean, double inStdDev)
	:
	mName(inName),
	mMean(inMean),
	mStdDev(inStdDev),
	mDistribution(inMean, inStdDev)
{
}

InputVariable::InputVariable(double inMean, double inStdDev)
	:
	mMean(inMean),
	mStdDev(inStdDev),
	mDistribution(inMean, inStdDev)
{
}

InputVariable::InputVariable(const InputVariable& inVar)
{
	*this = inVar;
}








#pragma mark - • MonteCarlo

MonteCarlo::MonteCarlo()
	:
	mRunCTX(nullptr),
	mCreateSweepContextBlock(nullptr),
	mRunBlock(nullptr),
	mSweepCompleteBlock(nullptr)
{
}

MonteCarlo::MonteCarlo(RunContext* inCTX)
	:
	mRunCTX(inCTX),
	mCreateSweepContextBlock(nullptr),
	mRunBlock(nullptr),
	mSweepCompleteBlock(nullptr)
{
}


void
MonteCarlo::addInputVariable(const InputVariable& inVar)
{
	mInputVariables.push_back(inVar);
}

void
MonteCarlo::setInputs(const InputVariablesListT& inVars)
{
	mInputVariables = inVars;
	//	TODO: reset anything else?
}

/**
	Run the model inNumIterations times, varying all the input parameters
*/

void
MonteCarlo::runCharacterization(size_t inNumIterations, RunCompletedBlockT inCompletedBlock)
{
	//	Get the context…
	
	SweepContext* ctx = mCreateSweepContextBlock(0);
	
	ctx->sweepCollectionBegan();
	
	for (size_t i = 0; i < inNumIterations; ++i)
	{
		//	Assign random values to each of the input values…
		
		ValueListT		inputValues;
		for (size_t i = 0; i < mInputVariables.size(); ++i)
		{
			double v = mInputVariables[i].randomValue();
			inputValues.push_back(v);
		}
		
		ValueListT outputs;
		bool goodRun = ctx->run(inputValues, outputs);
		if (goodRun)
		{
			mRunCTX->mGoodRuns++;
		}
		mRunCTX->mTotalRuns++;
	}
	
	//	Call the completion callbacks…
	
	ValueListT		means;
	ValueListT		stdDevs;
	ctx->sweepCollectionComplete(means, stdDevs);
	if (inCompletedBlock != NULL)
	{
		inCompletedBlock(this, ctx);
	}
	
	//	Clean up…
	
	delete ctx;
}

/**
	For each input:
		Assign random values to remaining inputs
		Sweep the input to get a distribution of outputs
		Get mean and stddev of each of the output distributions
 
 
*/

#define qAsync	1

void
MonteCarlo::runSensitivityAnalysis(size_t inInputIdx, size_t inNumIterationsPerInput, size_t inNumIterationsPerSweep)
{
	size_t inputIdx = inInputIdx;
	
	if (mRunCTX != NULL)
	{
		mRunCTX->runBegan(inputIdx);
	}
	
	mRunCTX->mGoodRuns = 0;
	mRunCTX->mTotalRuns = 0;
	
	//	For each input, sweep it multiple times…
	
	//for (size_t inputIdx = 0; inputIdx < mInputVariables.size(); ++inputIdx)
	{
	#if qAsync
		::dispatch_apply(inNumIterationsPerInput, ::dispatch_get_global_queue(QOS_CLASS_USER_INTERACTIVE, 0),
		^(size_t inIter)
	#else
		for (size_t i = 0; i < inNumIterationsPerInput; ++i)
	#endif
		{
			//	Get the context…
			
			SweepContext* ctx = mCreateSweepContextBlock(inputIdx);
			ctx->setVariableIdx(inputIdx);
			
			ctx->sweepCollectionBegan();
		
			sweepInput(ctx, inputIdx, inNumIterationsPerSweep);
			
			//	Clean up…
			
			ValueListT		means;
			ValueListT		stdDevs;
			ctx->sweepCollectionComplete(means, stdDevs);
			
			if (mRunCTX != NULL)
			{
				mRunCTX->sweepCompleted(inputIdx, ctx);
			}
			
			delete ctx;
	#if qAsync
		});
	#else
		}
	#endif
	}
	
	if (mRunCTX != NULL)
	{
		mRunCTX->runComplete(inputIdx);
	}
}

void
MonteCarlo::sweepInput(SweepContext* inCTX, size_t inVariableIdx, size_t inIterations) const
{
	//	Assign random values to each of the input values…
	
	ValueListT		inputValues;
	for (size_t i = 0; i < mInputVariables.size(); ++i)
	{
		double v = mInputVariables[i].randomValue();
		inputValues.push_back(v);
	}
	
	inCTX->sweepBegan();
	
	//	Run the model inIterations times…
	
	for (size_t i = 0; i < inIterations; ++i)
	{
		//	Assign a new value to the input variable in question…
		
		double v = mInputVariables[inVariableIdx].randomValue();
		inputValues[inVariableIdx] = v;
		
		ValueListT outputs;
		bool goodRun = inCTX->run(inputValues, outputs);
		if (goodRun)
		{
			mRunCTX->mGoodRuns++;
		}
		mRunCTX->mTotalRuns++;
		//runWithInputs(inputValues);
	}
	
	inCTX->sweepComplete();
	//mSweepCompleteBlock(inVariableIdx);
}
