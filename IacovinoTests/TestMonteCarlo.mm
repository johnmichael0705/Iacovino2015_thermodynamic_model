//
//  TestMonteCarlo.m
//  Iacovino
//
//  Created by Roderick Mann on 5/10/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>

#import <cstdio>

#import "Histogram.h"
#import "MonteCarlo.h"

#import "CharacterizationContext.h"
#import "MeltInclusion.h"
#import "SensitivityContext.h"




@interface TestMonteCarlo : XCTestCase

@end




@implementation TestMonteCarlo

- (void)
testHistogram
{
	Histogram		hist(1081.0, 50.0);
	XCTAssertEqualWithAccuracy(hist.lowValue(), 881.0, 0.00001);
	XCTAssertEqualWithAccuracy(hist.highValue(), 1281.0, 0.00001);
	XCTAssertEqualWithAccuracy(hist.binWidth(), 9.75609, 0.00001);
	XCTAssertEqual(hist.binCount(), 41);
	XCTAssertEqual(hist.maxBinCount(), 0);
	XCTAssertEqual(hist.maxBinIdx(), 0);
	
	XCTAssertEqualWithAccuracy(hist.binLow(0), hist.lowValue(), 0.00001);
	XCTAssertEqualWithAccuracy(hist.binHigh(hist.binCount() - 1), hist.highValue(), 0.00001);
	
	XCTAssertEqualWithAccuracy(hist.binLow(20), 1076.122, 0.001);
	XCTAssertEqualWithAccuracy(hist.binHigh(20), 1085.878, 0.001);
	
	double
	temps[] =
	{
		0, 1, 2, 880,							//	Discarded
		881, 882, 883, 884, 885, 886,			//	6 values (not all in one bin)
		1076, 1077, 1078.530,					//	3 values
		1078.531, 1081, 1081, 1082, 1083.469,	//	5 values
		1085.938, 1084, 1086,					//	3 values
		1280.999,								//	1 value
		1281,									//	Out, because the intervals are half-open [low, high)
	};
	const size_t kNumTemps = sizeof(temps) / sizeof(*temps);
	
	for (size_t i = 0; i < kNumTemps; ++i)
	{
		double v = temps[i];
		hist.add(v);
	}
	
	XCTAssertEqual(hist.valueCount(), 18);
	XCTAssertEqual(hist.maxBinCount(), 8);
	XCTAssertEqual(hist.maxBinIdx(), 20);
	
	XCTAssertEqual(hist.binForValue(1081), 20);
	
	XCTAssertEqual(hist[0], 6);
	XCTAssertEqual(hist[1], 0);
	XCTAssertEqual(hist[20], 8);
	XCTAssertEqual(hist[30], 0);
	XCTAssertEqual(hist[35], 0);
	XCTAssertEqual(hist[40], 1);
}

- (void)
testDynamicHistogram
{
	DynamicHistogram		hist;
	
	double
	temps[] =
	{
		0, 1, 2, 880,							//	4 values
		881, 882, 883, 884, 885, 886,			//	6 values (not all in one bin)
		1076, 1077, 1078.530,					//	3 values
		1078.531, 1081, 1081, 1082, 1083.469,	//	5 values
		1085.938, 1084, 1086,					//	3 values
		1280.999,								//	1 value
		1281,									//	1 value
	};											//	23 values
	const size_t kNumTemps = sizeof(temps) / sizeof(*temps);
	
	for (size_t i = 0; i < kNumTemps; ++i)
	{
		double v = temps[i];
		hist.add(v);
	}
	
	hist.sort();
	XCTAssertEqual(hist.binCount(), 20);
	XCTAssertEqual(hist.valueCount(), kNumTemps);
	
	XCTAssertEqualWithAccuracy(hist.mean(), 897.36813, 0.00001);
	XCTAssertEqualWithAccuracy(hist.stdDev(), 374.05645, 0.00001);
	XCTAssertEqualWithAccuracy(hist.lowValue(),0, 0.00001);
	XCTAssertEqualWithAccuracy(hist.highValue(), 1281, 0.00001);
	
	XCTAssertEqual(hist[0], 3);
	XCTAssertEqual(hist[1], 0);
	XCTAssertEqual(hist[2], 0);
	XCTAssertEqual(hist[3], 0);
	XCTAssertEqual(hist[4], 0);
	XCTAssertEqual(hist[5], 0);
	XCTAssertEqual(hist[6], 0);
	XCTAssertEqual(hist[7], 0);
	XCTAssertEqual(hist[8], 0);
	XCTAssertEqual(hist[9], 0);
	XCTAssertEqual(hist[10], 0);
	XCTAssertEqual(hist[11], 0);
	XCTAssertEqual(hist[12], 0);
	XCTAssertEqual(hist[13], 7);
	XCTAssertEqual(hist[14], 0);
	XCTAssertEqual(hist[15], 4);
	XCTAssertEqual(hist[16], 7);
	XCTAssertEqual(hist[17], 0);
	XCTAssertEqual(hist[18], 1);
	XCTAssertEqual(hist[19], 1);
}

- (void)
testDynamicHistogramBounds
{
	DynamicHistogram		hist;
	hist.add(1.0);
	hist.add(2.0);
	hist.sort();
	XCTAssertEqualWithAccuracy(hist.lowValue(), 1.0, 0.00001);
	XCTAssertEqualWithAccuracy(hist.highValue(), 2.0, 0.00001);
	
	hist.reset();
	hist.add(-1.0);
	hist.add(-2.0);
	hist.sort();
	XCTAssertEqualWithAccuracy(hist.lowValue(), -2.0, 0.00001);
	XCTAssertEqualWithAccuracy(hist.highValue(), -1.0, 0.00001);
}

class
MeltInclusionSweepContext : public MonteCarlo::SweepContext
{
public:
	
	virtual	void			sweepCollectionBegan();
	virtual	void			sweepBegan();
	virtual	bool			run(const MonteCarlo::ValueListT& inInputs, MonteCarlo::ValueListT& outOutputs);
	virtual	void			sweepComplete();
	virtual	void			sweepCollectionComplete(MonteCarlo::ValueListT& outMeans, MonteCarlo::ValueListT& outStdDevs);

private:
	VarianceAccumulator		mVarianceCO;
	std::vector<double>		mCOValues;
};

void
MeltInclusionSweepContext::sweepCollectionBegan()
{
}

void
MeltInclusionSweepContext::sweepBegan()
{
	mVarianceCO.reset();
}

bool
MeltInclusionSweepContext::run(const MonteCarlo::ValueListT& inInputs, MonteCarlo::ValueListT& outOutputs)
{
	MeltInclusion	mi(inInputs[0], inInputs[1], inInputs[2], inInputs[3], inInputs[4]);
	mi.calcComposition();
	
	double	co, co2, h2o, h2s, so2;
	mi.depressurize(1.0, co, co2, h2o, h2s, so2);
	
	mVarianceCO.add(co);
	mCOValues.push_back(co);
	//std::printf("%20.10f\n", co);
	//std::printf("%20.5e, %20.5e, %20.5e, %20.5e, %20.5e\n", co, co2, h2o, h2s, so2);
	
	return true;
}

void
MeltInclusionSweepContext::sweepComplete()
{
	std::printf("%3zd  %10.5f  %10.5f\n", variableIdx(), mVarianceCO.mean(), mVarianceCO.stdDev());
}

void
MeltInclusionSweepContext::sweepCollectionComplete(MonteCarlo::ValueListT& outMeans, MonteCarlo::ValueListT& outStdDevs)
{
	std::printf("----------\n");
}


- (void)
testMonteCarlo
{
	MonteCarlo				mc;
	
	InputVariable			temp(1081.0, 50.0);
	InputVariable			pressure(3000.0, 50.0);
	InputVariable			logFH2O(1.7706, 0.01);
	InputVariable			logFO2(-9.99, 0.01);
	InputVariable			logFS2(-3.01, 0.01);
	mc.addInputVariable(temp);
	mc.addInputVariable(pressure);
	mc.addInputVariable(logFH2O);
	mc.addInputVariable(logFO2);
	mc.addInputVariable(logFS2);
	
#if 0
	Histogram				histCO(3.19904e-02, 0.001, 0.01);
	Histogram				histCO2(9.52939e-01, pressure.stdDev(), 50.0;
	Histogram				histH2O(logFH2O.mean(), logFH2O.stdDev(), 5.0;
	Histogram				histH2S(logFO2.mean(), temp.stdDev(), 5.0;
	Histogram				histSO2(temp.mean(), temp.stdDev(), 5.0;
#endif
	
	__block VarianceAccumulator		coVariance;
	
	mc.setCreateSweepContextBlock(
	^MonteCarlo::SweepContext* (size_t inVariableIdx)
	{
		MeltInclusionSweepContext* ctx = new MeltInclusionSweepContext();
		return ctx;
	});
	
	mc.runSensitivityAnalysis(0, 100, 100);
	
}


#pragma mark - • Test MC Characterization

- (void)
testCharacterization
{
	MonteCarlo				mc;
	
	InputVariable			temp(1081.0, 50.0);
	InputVariable			pressure(3000.0, 50.0);
	InputVariable			logFH2O(1.7706, 0.01);
	InputVariable			logFO2(-9.99, 0.01);
	InputVariable			logFS2(-3.01, 0.01);
	mc.addInputVariable(temp);
	mc.addInputVariable(pressure);
	mc.addInputVariable(logFH2O);
	mc.addInputVariable(logFO2);
	mc.addInputVariable(logFS2);
	
#if 0
	Histogram				histCO(3.19904e-02, 0.001, 0.01);
	Histogram				histCO2(9.52939e-01, pressure.stdDev(), 50.0;
	Histogram				histH2O(logFH2O.mean(), logFH2O.stdDev(), 5.0;
	Histogram				histH2S(logFO2.mean(), temp.stdDev(), 5.0;
	Histogram				histSO2(temp.mean(), temp.stdDev(), 5.0;
#endif
	
	/**
		TODO:	Set up run to break up iterations into multiple parallel ops.
				Create serial queue to enqueue histogram accumulation of outputs.
	*/
	 
	
	mc.setCreateSweepContextBlock(
	^MonteCarlo::SweepContext* (size_t inVariableIdx)
	{
		CharacterizationContext* ctx = new CharacterizationContext();
		return ctx;
	});
	
	mc.runCharacterization(100, ^(MonteCarlo *inMC, MonteCarlo::SweepContext *inCTX) {
		std::printf("Done\n");
	});
	
}

- (void)
testSweepInput
{
	MonteCarlo				mc;
	
	InputVariable			temp("temp", 1081.0, 25.0);
	InputVariable			pressure("pressure", 3582.0, 1.0);
	InputVariable			logFH2O("logFH2O", 1.25, 0.06);
	InputVariable			logFO2("logFO2", -9.99, 0.5);
	InputVariable			logFS2("logFS2", -3.01, 0.35);
	mc.addInputVariable(temp);
	mc.addInputVariable(pressure);
	mc.addInputVariable(logFH2O);
	mc.addInputVariable(logFO2);
	mc.addInputVariable(logFS2);
	
	
	SensitivityContext* ctx = new SensitivityContext();
	mc.sweepInput(ctx, 0, 1000);
	
	
}

- (void)
testRunMC
{
	SensitivityRunContext	rc;
	
	MonteCarlo				mc(&rc);
	
	InputVariable			temp("temp", 1081.0, 25.0);
	InputVariable			pressure("pressure", 3582.0, 1.0);
	InputVariable			logFH2O("logFH2O", 1.25, 0.06);
	InputVariable			logFO2("logFO2", -9.99, 0.5);
	InputVariable			logFS2("logFS2", -3.01, 0.35);
	mc.addInputVariable(temp);
	mc.addInputVariable(pressure);
	mc.addInputVariable(logFH2O);
	mc.addInputVariable(logFO2);
	mc.addInputVariable(logFS2);
	
	
	mc.setCreateSweepContextBlock(
		^MonteCarlo::SweepContext* (size_t inVariableIdx)
		{
			SensitivityContext* ctx = new SensitivityContext();
			return ctx;
		});
	
	size_t iterationsPerInput = 1000;
	size_t iterationsPerSweep = 1000;
	mc.runSensitivityAnalysis(0, iterationsPerInput, iterationsPerSweep);
	mc.runSensitivityAnalysis(1, iterationsPerInput, iterationsPerSweep);
}

- (void)
testRunFullSensitivity
{
	MonteCarlo::InputVariablesListT basanite =		//	DVDP3_295
	{
		InputVariable("temp",		1100,		25.0),
		InputVariable("pressure",	4445.0,		100.0),
		InputVariable("logFH2O",	2.52356903,	0.06),
		InputVariable("logFO2",		-7.63,		0.5),
		InputVariable("XCO2",		0.9299,		0.1),
		InputVariable("wt%CO2",		0.5537,		0.08),		//15% error
		InputVariable("wt%H2O",		1.498,		0.17976),	//12% error
		InputVariable("wt%Stot",	0.067,		0.02),		//±200 ppm error
	};
	
	MonteCarlo::InputVariablesListT teph =
	{
		InputVariable("temp",		1081.0,		12.0),
		InputVariable("pressure",	3582.0,		100.0),
		InputVariable("logFH2O",	1.25,		0.06),
		InputVariable("logFO2",		-9.99,		0.5),
		InputVariable("logFS2",		-3.01,		0.35),
		InputVariable("wt%CO2",		0.1513,		0.02),		//15% error
		InputVariable("wt%H2O",		0.2575,		0.0309),	//12% error
		InputVariable("wt%Stot",	0.0998,		0.02),		//±200 ppm
	};
	
	MonteCarlo::InputVariablesListT phon =
	{
		InputVariable("temp",		1000,		25.0),
		InputVariable("pressure",	2671.3,		1.0),
		InputVariable("logFH2O",	0.60650829,	0.06),
		InputVariable("logFO2",		-11.26,		0.5),
		InputVariable("logFS2",		-2.7,		0.35),
		InputVariable("wt%CO2",		0.0691,		0.015475),	//25% error
		InputVariable("wt%H2O",		0.167,		0.02004),	//12% error
		InputVariable("wt%Stot",	0.03805,	0.02),		//±200 ppm
	};
	
	MonteCarlo::InputVariablesListT ll =
	{
		InputVariable("temp",		1000,		25.0),
		InputVariable("pressure",	4.321,		1.0),
		InputVariable("logFH2O",	0.21255783,	0.06),
		InputVariable("logFO2",		-12.2,		0.5),
		InputVariable("logFS2",		-2.7,		0.35),
		InputVariable("wt%CO2",		0.03,		0.015),		//50% error
		InputVariable("wt%H2O",		0.11,		0.0132),	//12% error
		InputVariable("wt%Stot",	0.0,		0.0),
	};
	
	std::printf("\n\n");
	
	//	Print a header…
	
	SensitivityRunContext	rc;
	std::string s = "Region,Input Variable,Good Runs,Total Runs,";
	for (size_t speciesIdx = 0; speciesIdx < rc.mSpecies.size(); ++speciesIdx)
	{
		std::string sn = rc.mSpecies[speciesIdx];
		s += sn + " mm," + sn + " mσ," + sn + " σm," + sn + " σσ,";
	}
	s.pop_back();
	std::printf("%s\n", s.c_str());
	
	//	Run the analyses…
	
	runSensitivity("bas", basanite, 5, ^MonteCarlo::SweepContext* (size_t inVariableIdx) { return new BasaniteSensitivityContext(); });
	runSensitivity("teph", teph, 5, ^MonteCarlo::SweepContext* (size_t inVariableIdx) { return new SensitivityContext(); });
	runSensitivity("phon", phon, 5, ^MonteCarlo::SweepContext* (size_t inVariableIdx) { return new SensitivityContext(); });
	runSensitivity("ll", ll, 5, ^MonteCarlo::SweepContext* (size_t inVariableIdx) { return new SensitivityContext(); });
	
	runSensitivity("basToTeph", basanite, teph, ^MonteCarlo::SweepContext* (size_t inVariableIdx) { return new DeltaBasaniteSensitivityContext(kBasFrac); });
	runSensitivity("tephToPhon", teph, phon, ^MonteCarlo::SweepContext* (size_t inVariableIdx) { return new DeltaSensitivityContext(kTephFrac); });
	runSensitivity("phonToLL", phon, ll, ^MonteCarlo::SweepContext* (size_t inVariableIdx) { return new DeltaSensitivityContext(kPhonFrac); });
	
	std::printf("\n\n");
}

void
runSensitivity(const std::string& inName,
				const MonteCarlo::InputVariablesListT& inRegionIVs,
				size_t inNumToVary,
				MonteCarlo::CreateSweepContextBlockT inCSCB)
{
	SensitivityRunContext	rc;
	MonteCarlo				mc(&rc);
	mc.setCreateSweepContextBlock(inCSCB);
	
	mc.setInputs(inRegionIVs);
	
	size_t iterationsPerInput = 1000;
	size_t iterationsPerSweep = 1000;
	for (size_t inputVarIdx = 0; inputVarIdx < inNumToVary; ++inputVarIdx)
	{
		mc.runSensitivityAnalysis(inputVarIdx, iterationsPerInput, iterationsPerSweep);
		
		std::string s;
		for (size_t speciesIdx = 0; speciesIdx < rc.mSpecies.size(); ++speciesIdx)
		{
			s += rc.csvPopulationsForSpecies(speciesIdx) + ",";
		}
		s.pop_back();
		std::printf("%s,%s,%zd,%zd,%s\n", inName.c_str(), inRegionIVs[inputVarIdx].name().c_str(), (size_t) rc.mGoodRuns, (size_t) rc.mTotalRuns, s.c_str());
	}
	
}

void
runSensitivity(const std::string& inName,
				const MonteCarlo::InputVariablesListT& inRegionIVs,
				const MonteCarlo::InputVariablesListT& inTargetRegionIVs,
				MonteCarlo::CreateSweepContextBlockT inCSCB)
{
	SensitivityRunContext	rc;
	MonteCarlo				mc(&rc);
	mc.setCreateSweepContextBlock(inCSCB);
	
	MonteCarlo::InputVariablesListT		inputs(inRegionIVs);
	inputs.push_back(inTargetRegionIVs[5]);
	inputs.push_back(inTargetRegionIVs[6]);
	inputs.push_back(inTargetRegionIVs[7]);
	mc.setInputs(inputs);
	
	size_t iterationsPerInput = 1000;
	size_t iterationsPerSweep = 1000;
	for (size_t inputVarIdx = 0; inputVarIdx < inputs.size(); ++inputVarIdx)
	{
		mc.runSensitivityAnalysis(inputVarIdx, iterationsPerInput, iterationsPerSweep);
		
		std::string s;
		for (size_t speciesIdx = 0; speciesIdx < rc.mSpecies.size(); ++speciesIdx)
		{
			s += rc.csvPopulationsForSpecies(speciesIdx) + ",";
		}
		s.pop_back();
		std::printf("%s,%s,%zd,%zd,%s\n", inName.c_str(), inputs[inputVarIdx].name().c_str(), (size_t) rc.mGoodRuns, (size_t) rc.mTotalRuns, s.c_str());
	}
	
}

@end
