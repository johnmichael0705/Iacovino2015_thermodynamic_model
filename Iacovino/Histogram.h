//
//  Histogram.h
//  Iacovino
//
//  Created by Roderick Mann on 5/10/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#ifndef __Iacovino__Histogram__
#define __Iacovino__Histogram__

#include <cassert>
#include <cmath>
#include <mutex>
#include <string>
#include <vector>













#pragma mark -
#pragma mark • VarianceAccumulator


class
VarianceAccumulator
{
public:
	VarianceAccumulator()
	{
		reset();
	}
	
	VarianceAccumulator(const VarianceAccumulator& inVal)
	{
		*this = inVal;
	}
	
	VarianceAccumulator&
	operator=(const VarianceAccumulator& inVal)
	{
		mCount = inVal.mCount;
		mMean = inVal.mMean;
		mM2 = inVal.mM2;
		mVariance = inVal.mVariance;
		
		return *this;
	}
	
	void
	reset()
	{
		mCount = 0;
		mMean = 0.0;
		mM2 = 0.0;
		mVariance = 0.0;
	}
	
	void			add(const double inVal);
	void			syncAdd(const std::vector<double>& inValues);
	
	double			stdDev()				const	{ return std::sqrt(mVariance); }
	double			mean()					const	{ return mMean; }
	
private:
	size_t			mCount;
	double			mMean;
	double			mM2;
	double			mVariance;
	
	std::mutex		mMutex;
};






#pragma mark -
#pragma mark • Histogram

/**
	Simple data structure for accumulating a histogram. Note that this class
	does not actuall graph the histogram, it only creates the bins and
	accumulates the values added.
*/

class
Histogram
{
public:
	typedef	std::vector<size_t>						BinArrayT;
	typedef	std::vector<size_t>::size_type			SizeT;

					Histogram();
					Histogram(double inMean, double inStdDev);
	
	void			reset();
	
	Histogram&		operator=(const Histogram& inHistogram);
	
	void			setName(const std::string& inVal)						{ mName = inVal; }
	const std::string&
					name()									const			{ return mName; }
	
	double			mean()									const			{ return mMean; }
	double			stdDev()								const			{ return mStdDev; }
	
	/**
		Add a value to the histogram. Values outside the expected
		range are discarded.
		
		TODO: Implement a version that automatically expands the histogram bins.
	*/
	
	void			add(double inVal);
	
	double			lowValue()								const			{ return mLowValue; }
	double			highValue()								const			{ return mHighValue; }
	
	double			binWidth()								const			{ return mBinWidth; }
	SizeT			binCount()								const			{ return mBins.size(); }
	SizeT			binForValue(double inVal)				const;
	size_t			operator[](SizeT inIdx)					const			{ return mBins[inIdx]; }
	SizeT			valueCount()							const			{ return mNumValues; }
	
	double			binLow(SizeT inIdx)						const;
	double			binMid(SizeT inIdx)						const;
	double			binHigh(SizeT inIdx)					const;
	
	double			histogramLow()							const			{ return mHistogramLow; }
	double			histogramHigh()							const			{ return mHistogramHigh; }
	double			histogramRange()						const			{ return mHistogramRange; }
	
	size_t			maxBinCount()							const			{ return mMaxBinCount; }
	SizeT			maxBinIdx()								const			{ return mMaxBinIdx; }

protected:
	void			setupHistogram(double inMean, double inStdDev);
	
protected:
	std::string		mName;
	
	double			mMean;
	double			mStdDev;
	double			mBinWidth;
	
	double			mLowValue;
	double			mHighValue;
	
	double			mHistogramLow;
	double			mHistogramHigh;
	double			mHistogramRange;
	
	BinArrayT		mBins;
	SizeT			mNumValues;
	
	size_t			mMaxBinCount;
	SizeT			mMaxBinIdx;
};



inline
Histogram::SizeT
Histogram::binForValue(double inVal) const
{
	double x = inVal - mHistogramLow;
	BinArrayT::size_type idx = x / mBinWidth;
	assert(idx < mBins.size());
	return idx;
}

inline
double
Histogram::binLow(SizeT inIdx) const
{
	return mHistogramLow + inIdx * mBinWidth;
}

inline
double
Histogram::binMid(SizeT inIdx) const
{
	return mHistogramLow + mBinWidth / 2.0 + inIdx * mBinWidth;
}

inline
double
Histogram::binHigh(SizeT inIdx) const
{
	return mLowValue + (inIdx + 1) * mBinWidth;
}








#pragma mark -
#pragma mark • Dynamic Histogram

class
DynamicHistogram : public Histogram
{
public:
	typedef	std::vector<double>				ValuesArrayT;
	
	DynamicHistogram();
	
	void			reset();
	
	void			add(double inVal);
	void			sort(SizeT inNumBins = 20);		//	Seems like a nice number
	
private:
	ValuesArrayT			mValues;
	VarianceAccumulator		mVariance;
};

#endif /* defined(__Iacovino__Histogram__) */
