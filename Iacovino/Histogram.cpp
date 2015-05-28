//
//  Histogram.cpp
//  Iacovino
//
//  Created by Roderick Mann on 5/10/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#include "Histogram.h"

#include <cmath>
#include <cstdio>
#include <limits>



Histogram::Histogram()
	:
	mMean(0.0),
	mStdDev(0.0),
	mBinWidth(0.0),
	mNumValues(0),
	mLowValue(std::numeric_limits<double>::max()),
	mHighValue(std::numeric_limits<double>::lowest()),
	mHistogramLow(std::numeric_limits<double>::max()),
	mHistogramHigh(std::numeric_limits<double>::lowest()),
	mHistogramRange(0),
	mMaxBinCount(0),
	mMaxBinIdx(0)
{
}


Histogram::Histogram(double inMean, double inStdDev)
	:
	mMean(inMean),
	mStdDev(inStdDev),
	mBinWidth(0),
	mLowValue(std::numeric_limits<double>::max()),
	mHighValue(std::numeric_limits<double>::lowest()),
	mHistogramLow(std::numeric_limits<double>::max()),
	mHistogramHigh(std::numeric_limits<double>::lowest()),
	mHistogramRange(0),
	mNumValues(0),
	mMaxBinCount(0),
	mMaxBinIdx(0)
{
	setupHistogram(inMean, inStdDev);
}

void
Histogram::reset()
{
	mBinWidth = 0.0;
	mNumValues = 0;
	mLowValue = std::numeric_limits<double>::max();
	mHighValue = std::numeric_limits<double>::lowest();
	mHistogramLow = std::numeric_limits<double>::max();
	mHistogramHigh = std::numeric_limits<double>::lowest();
	mHistogramRange = 0;
	mMaxBinCount = 0;
	mMaxBinIdx = 0;
}

Histogram&
Histogram::operator=(const Histogram& inHistogram)
{
	mName = inHistogram.mName;
	
	mMean = inHistogram.mMean;
	mStdDev = inHistogram.mStdDev;
	mBinWidth = inHistogram.mBinWidth;
	
	mLowValue = inHistogram.mLowValue;
	mHighValue = inHistogram.mHighValue;
	
	mHistogramLow = inHistogram.mHistogramLow;
	mHistogramHigh = inHistogram.mHistogramHigh;
	mHistogramRange = inHistogram.mHistogramRange;
	
	mBins = inHistogram.mBins;
	mNumValues = inHistogram.mNumValues;
	
	mMaxBinCount = inHistogram.mMaxBinCount;
	mMaxBinIdx = inHistogram.mMaxBinIdx;
	
	return *this;
}

void
Histogram::setupHistogram(double inMean, double inStdDev)
{
	mMean = inMean;
	mStdDev = inStdDev;
	mBinWidth = mStdDev / 5;
	
	//	We use a 4-sigma range…
	
	double range = 2 * 4 * inStdDev;
	
	//	Compute the number of bins, adding one if
	//	needed to make the number odd…
	
	SizeT numBins = std::ceil(range / mBinWidth);
	numBins /= 2;
	numBins = 2 * numBins + 1;
	
	mBinWidth = range / numBins;
	
	//	Initialize the bins to 0…
	
	mBins.clear();
	mBins.assign(numBins, 0);
	
	//	Center the middle bin on the mean.
	//
	//	This math is more convoluted than necessary, but
	//	I *think* it produces more accurate results. Haven’t
	//	checked to be sure, though…
	
	numBins /= 2;													//	Integer divide truncates
	mHistogramLow = inMean - numBins * mBinWidth - mBinWidth / 2;		//	Subtract half a bin
	mHistogramHigh = inMean + numBins * mBinWidth + mBinWidth / 2;		//	Add half a bin
	
	mMaxBinCount = 0;
	mMaxBinIdx = 0;
}

void
Histogram::add(double inVal)
{
	//	If inVal is outside our range, discard it…
	
	if (inVal < mHistogramLow || mHistogramHigh <= inVal)
	{
		return;
	}
	
	mNumValues += 1;
	
	BinArrayT::size_type idx = binForValue(inVal);
	size_t count = mBins[idx];
	count += 1;
	mBins[idx] = count;
	
	if (count >= mMaxBinCount)		//	>= so most recent bin is always max, even if same as previous max
	{
		mMaxBinCount = count;
		mMaxBinIdx = idx;
	}
}

#pragma mark -
#pragma mark • DynamicHistogram

DynamicHistogram::DynamicHistogram()
{
}

void
DynamicHistogram::reset()
{
	Histogram::reset();
	
	mValues.clear();
	mVariance.reset();
}


void
DynamicHistogram::add(double inVal)
{
	if (inVal < mLowValue)
	{
		mLowValue = inVal;
		//std::printf("New low: %g\n", inVal);
	}
	
	if (inVal > mHighValue)
	{
		mHighValue = inVal;
		//std::printf("%s new high: %g\n", name().c_str(), inVal);
	}
	
	mValues.push_back(inVal);
	mVariance.add(inVal);
}

/**
	Set appropriate parameters and sort the values into buckets.
*/

void
DynamicHistogram::sort(SizeT inNumBins)
{
	
	mMean = mVariance.mean();
	mStdDev = mVariance.stdDev();
	
	//std::printf("%.12f, %.12f | %.12f, %.12f\n", mLowValue, mHighValue, mMean, mStdDev);
	//std::printf("%e, %e | %e, %e\n", mLowValue, mHighValue, mMean, mStdDev);
	
	//	The histogram should span the values. The bins are half-open
	//	intervals of the bin width, so the highest value should be the
	//	the lowest value of the highest bin…
	
	mBinWidth = mHighValue - mLowValue;
	mBinWidth /= inNumBins - 1;
	
	//	Initialize the bins to 0…
	
	mBins.clear();
	mBins.assign(inNumBins, 0);
	
	//	Set the histogram range…
	
	mHistogramLow = mLowValue;
	mHistogramHigh = binHigh(binCount() - 1);
	mHistogramRange	= mHistogramHigh - mHistogramLow;
	
	for (size_t i = 0; i < mValues.size(); ++i)
	{
		const double v = mValues[i];
		Histogram::add(v);
		//std::printf("Hist val %f max bin count: %zd (%zd)\n", v, maxBinCount(), maxBinIdx());
	}
}

#pragma mark -
#pragma mark • VarianceAccumulator

void
VarianceAccumulator::add(const double inVal)
{
	mCount += 1;
	double delta = inVal - mMean;
	mMean += delta / mCount;
	mM2 += delta * (inVal - mMean);
	
	if (mCount >= 2)
	{
		mVariance = mM2 / (mCount - 1);
	}
}

void
VarianceAccumulator::syncAdd(const std::vector<double>& inValues)
{
	std::lock_guard<std::mutex>	lock(mMutex);
	
	for (const auto val : inValues)
	{
		add(val);
	}
}
