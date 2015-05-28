//
//  MonteCarlo.h
//  Iacovino
//
//  Created by Roderick Mann on 5/10/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#ifndef __Iacovino__MonteCarlo__
#define __Iacovino__MonteCarlo__

#include <atomic>
#include <random>
#include <vector>




class
InputVariable
{
public:
	InputVariable(const std::string& inName, double inMean, double inStdDev);
	InputVariable(double inMean, double inStdDev);
	InputVariable(const InputVariable& inVar);
	
	InputVariable&
	operator=(const InputVariable& inVar)
	{
		mName = inVar.mName;
		mMean = inVar.mMean;
		mStdDev = inVar.mStdDev;
		mDistribution = inVar.mDistribution;
		//mGenerator = inVar.mGenerator;
		
		return *this;
	}
	
	const std::string&	name()				const			{ return mName; }
	
	double				mean()				const			{ return mMean; }
	double				stdDev()			const			{ return mStdDev; }
	
	double
	randomValue() const
	{
		double v = mDistribution(mGenerator);
		return v;
	}
	
private:
	std::string										mName;
	double											mMean;
	double											mStdDev;
	mutable std::normal_distribution<double>		mDistribution;
	mutable std::random_device						mGenerator;
};









class
MonteCarlo
{
public:
	class RunContext;
	class SweepContext;
	
	typedef std::vector<InputVariable>			InputVariablesListT;
	typedef std::vector<double>					ValueListT;
	typedef	SweepContext*						(^CreateSweepContextBlockT)(size_t inVariableIdx);
	typedef	void								(^RunBlockT)(const ValueListT& inValues);
	typedef	void								(^SweepCompleteBlockT)(size_t inVariableIdx);
	typedef	void								(^RunCompletedBlockT)(MonteCarlo* inMC, SweepContext* inCTX);
	
					MonteCarlo();
					MonteCarlo(RunContext* inCTX);
	
	void			setCreateSweepContextBlock(CreateSweepContextBlockT inBlock)			{ mCreateSweepContextBlock = inBlock; }
	void			setRunBlock(RunBlockT inBlock)											{ mRunBlock = inBlock; }
	void			setSweepCompleteBlock(SweepCompleteBlockT inBlock)						{ mSweepCompleteBlock = inBlock; }
	
	void			addInputVariable(const InputVariable& inVar);
	void			setInputs(const InputVariablesListT& inVars);
	
	void			runCharacterization(size_t inNumIterations, RunCompletedBlockT inCompletedBlock);
	void			runSensitivityAnalysis(size_t inInputIdx, size_t inNumIterationsPerInput, size_t inNumIterationsPerSweep);
	
	/**
		SweetContext class maintains state for a given parcel of
		Monte Carlo work.
	*/
	
	class
	SweepContext
	{
	public:
		virtual					~SweepContext() {}
		
		virtual	void			sweepCollectionBegan()														=	0;
		virtual	void			sweepBegan()																=	0;
		virtual	bool			run(const ValueListT& inValues, ValueListT& outValues)						=	0;
		virtual	void			sweepComplete()																=	0;
		virtual	void			sweepCollectionComplete(ValueListT& outMeans, ValueListT& outStdDevs)		=	0;
		
		void					setVariableIdx(size_t inVal)			{ mVariableIdx = inVal; }
		size_t					variableIdx()					const	{ return mVariableIdx; }
		
	private:
		size_t					mVariableIdx;
	};

	/**
		RunContext must synchronize access to its members.
	*/
	
	class
	RunContext
	{
	public:
		RunContext()
			:
			mTotalRuns(0),
			mGoodRuns(0)
		{
		}

		virtual					~RunContext() {}
		
		virtual	void			runBegan(size_t inInputVariable) {}
		virtual	void			sweepCompleted(size_t inInputVariable, SweepContext* inCTX) {}
		virtual void			runComplete(size_t inInputVariable) {}
		
		std::atomic<size_t>		mTotalRuns;
		std::atomic<size_t>		mGoodRuns;
	};
	
//protected:
	/**
		Run the model inIteration times. Vary the value of inVariableIdx,
		holding the remaining variables to a constant random vector.
	*/
	
	void			sweepInput(SweepContext* inCTX, size_t inVariableIdx, size_t inIterations) const;
	void			runWithInputs(const ValueListT& inValues) const;
	
private:
	RunContext*					mRunCTX;
	CreateSweepContextBlockT	mCreateSweepContextBlock;
	RunBlockT					mRunBlock;
	SweepCompleteBlockT			mSweepCompleteBlock;
	
	InputVariablesListT			mInputVariables;
};

inline
void
MonteCarlo::runWithInputs(const ValueListT& inValues) const
{
	mRunBlock(inValues);
}


#endif /* defined(__Iacovino__MonteCarlo__) */
