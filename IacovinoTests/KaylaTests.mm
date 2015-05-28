//
//  KaylaTests.m
//  KaylaTests
//
//  Created by Roderick Mann on 4/25/15.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>

#import <cmath>
#import <cstdio>

#import "RedlichKwong.h"
#import "EquilibriumConstantOfFormation.h"
#import "MeltInclusion.h"
#import "Model.h"
#import "SearchMix.h"

@interface KaylaTests : XCTestCase

@end



extern
double
fS2(double inA, double inB, double inC, double inD, double inE, double inG, double inH, double inP);


@implementation KaylaTests


- (void)
testModel
{
	initModel();
	model();
}

- (void)
testAverageHighAndLowPressure
{
	initModel();
	
#if 0
	DVDP3_295_average.calcComposition();
	Intermediate_avg.calcComposition();
	EA1_avg.calcComposition();
	LL_Phon_8.calcComposition();
	
	WeightPercents bas(0.5537, 1.498, 0.21662);
    WeightPercents teph(0.1594, 0.34, 0.0662); //comp(CO2, H2O, S) values in wt%
	WeightPercents phon(0.0691, 0.167, 0.03805);
	WeightPercents ll(0.03, 0.11, 0.0);
	
	BasaniteMeltInclusion		deltaBasToTeph(DVDP3_295_average);
	deltaBasToTeph.calcDeltaComposition(bas, kBasFrac, teph);
	
	MeltInclusion				deltaTephToPhon(Intermediate_avg);
	deltaTephToPhon.calcDeltaComposition(teph, kTephFrac, phon);
	
	MeltInclusion				deltaPhonToLL(EA1_avg);
	deltaPhonToLL.calcDeltaComposition(phon, kPhonFrac, ll);
#endif

	//	High pressure…
	
	std::printf("\n\n%-20.20s  %13.13s  %13.13s  %13.13s  %13.13s  %13.13s\n", "Region (high press)", "CO", "CO2", "H2O", "H2S", "SO2");
	std::printf("%20.20s  %13.13s  %13.13s  %13.13s  %13.13s  %13.13s\n", "--------------------", "--------", "--------", "--------", "--------", "--------");
	
	outputMeltData(DVDP3_295a, "DVDP3_295a");
	outputMeltData(DVDP3_295b, "DVDP3_295b");
	outputMeltData(DVDP3_295c, "DVDP3_295c");
	outputMeltData(DVDP3_295d, "DVDP3_295d");
	outputMeltData(DVDP3_295g, "DVDP3_295g");
	outputMeltData(DVDP3_295i, "DVDP3_295i");
	outputMeltData(DVDP3_295j, "DVDP3_295j");
	outputMeltData(DVDP3_295l, "DVDP3_295l");
	outputMeltData(DVDP3_295q, "DVDP3_295q");
	outputMeltData(DVDP3_295r, "DVDP3_295r");
	outputMeltData(DVDP3_295_average, "DVDP3_295_average");
	
	outputMeltData(tp97009b, "tp97009b");
	outputMeltData(tp97009d, "tp97009d");
	outputMeltData(tp97009e, "tp97009e");
	outputMeltData(tp97009g, "tp97009g");
	outputMeltData(tp97010b, "tp97010b");
	outputMeltData(tp97010d, "tp97010d");
	outputMeltData(tp97011a, "tp97011a");
	outputMeltData(aw82033c, "aw82033c");
	outputMeltData(aw82033e, "aw82033e");
	outputMeltData(aw82033i, "aw82033i");
	outputMeltData(Intermediate_avg, "Intermediate_avg");
	
	outputMeltData(EA1_a, "EA1_a");
	outputMeltData(EA1_b, "EA1_b");
	outputMeltData(EA1_d, "EA1_d");
	outputMeltData(EA1_e, "EA1_e");
	outputMeltData(EA1_f, "EA1_f");
	outputMeltData(EA1_g, "EA1_g");
	outputMeltData(EA1_h, "EA1_h");
	outputMeltData(EA1_i, "EA1_i");
	outputMeltData(EA1_j, "EA1_j");
	outputMeltData(EA1_k, "EA1_k");
	outputMeltData(EA1_avg, "EA1_avg");
	
	outputMeltData(LL_Phon_8, "LL_Phon_8");
	
	outputMeltData(deltaBasToTeph, "deltaBasToTeph");
	outputMeltData(deltaTephToPhon, "deltaTephToPhon");
	outputMeltData(deltaPhonToLL, "deltaPhonToLL");
	
	//	Low pressure…
	
	std::printf("\n\n%-20.20s  %13.13s  %13.13s  %13.13s  %13.13s  %13.13s\n", "Region (low press)", "CO", "CO2", "H2O", "H2S", "SO2");
	std::printf("%20.20s  %13.13s  %13.13s  %13.13s  %13.13s  %13.13s\n", "--------------------", "--------", "--------", "--------", "--------", "--------");
	
	double pressure = 1.0;
	
	outputLowMeltData(pressure, LL_Phon_8, "LL_Phon_8");
	outputLowMeltData(pressure, EA1_avg, "EA1_avg");
	outputLowMeltData(pressure, Intermediate_avg, "Intermediate_avg");
	outputLowMeltData(pressure, DVDP3_295_average, "DVDP3_295_average");
	outputLowMeltData(pressure, deltaPhonToLL, "deltaPhonToLL");
	outputLowMeltData(pressure, deltaTephToPhon, "deltaTephToPhon");
	outputLowMeltData(pressure, deltaBasToTeph, "deltaBasToTeph");
	
	
	std::printf("\n\n");
}





void
outputMeltData(const MeltInclusion& inMelt, const char* inName)
{
	double co, co2, h2o, h2s, so2;
	inMelt.molFractions(co, co2, h2o, h2s, so2);
	std::printf("%-20.20s  %13.2f  %13.2f  %13.2f  %13.2f  %13.2f\n", inName, co*100, co2*100, h2o*100, h2s*100, so2*100);
}

void
outputLowMeltData(double inPressure, const MeltInclusion& inMelt, const char* inName)
{
	double co, co2, h2o, h2s, so2;
	inMelt.depressurize(inPressure, co, co2, h2o, h2s, so2);
	std::printf("%-20.20s  %13.2f  %13.2f  %13.2f  %13.8f  %13.5f\n", inName, co*100, co2*100, h2o*100, h2s*100, so2*100);
}
















- (void)
testMixer
{
	SearchMix		sm;
	
	sm.add(0.0, 99.83/100.0, 0.17/100.0, 0.0, 0.0);
	sm.add(0.0, 98.41/100.0, 1.59/100.0, 0.1/100.0, 0.0);
	sm.add(0.0, 87.43/100.0, 4.81/100.0, 0.54/100.0, 7.22/100.0);
	sm.add(0.0, 60.02/100.0, 37.82/100.0, 2.12/100.0, 0.03/100.0);
	sm.add(0.0, 12.50/100.0, 85.58/100.0, 0.04/100.0, 1.88/100.0);
	sm.add(0.0, 15.45/100.0, 80.04/100.0, 2.22/100.0, 2.29/100.0);
	sm.add(0.0, 16.95/100.0, 60.38/100.0, 10.61/100.0, 12.06/100.0);
	
	sm.search();
}

- (void)
testSMMix
{
	SearchMix		sm;
	
	sm.add(0.0, 99.83/100.0, 0.17/100.0, 0.0, 0.0);
	sm.add(0.0, 98.41/100.0, 1.59/100.0, 0.1/100.0, 0.0);
	sm.add(0.0, 87.43/100.0, 4.81/100.0, 0.54/100.0, 7.22/100.0);
	sm.add(0.0, 60.02/100.0, 37.82/100.0, 2.12/100.0, 0.03/100.0);
	sm.add(0.0, 12.50/100.0, 85.58/100.0, 0.04/100.0, 1.88/100.0);
	sm.add(0.0, 15.45/100.0, 80.04/100.0, 2.22/100.0, 2.29/100.0);
	sm.add(0.0, 16.95/100.0, 60.38/100.0, 10.61/100.0, 12.06/100.0);
	
	double co2 = sm.getVals(0, 100, 0, 0, 0, 0, 0, sm.mCO2Vals);
	XCTAssertEqualWithAccuracy(co2, 98.409996, 0.00001);
	co2 = sm.getVals(0, 99, 1, 0, 0, 0, 0, sm.mCO2Vals);
	XCTAssertEqualWithAccuracy(co2, 98.3001937, 0.00001);
	
	double h2o = sm.getVals(0, 29, 0, 1, 67, 2, 1, sm.mH2OVals);
	XCTAssertEqualWithAccuracy(h2o, 60.3824959, 0.00001);
	h2o = sm.getVals(25, 4, 0, 0, 66, 0, 5, sm.mH2OVals);
	XCTAssertEqualWithAccuracy(h2o, 59.6078987, 0.00001);
	
	double h2s = sm.getVals(26, 1, 2, 1, 70, 0, 0, sm.mH2SVals);
	XCTAssertEqualWithAccuracy(h2s, 0.060999997, 0.00001);
	h2s = sm.getVals(0, 28, 2, 0, 70, 0, 0, sm.mH2SVals);
	XCTAssertEqualWithAccuracy(h2s, 0.0667999983, 0.00001);
	
	double so2 = sm.getVals(25, 4, 0, 0, 63, 8, 0, sm.mSO2Vals);
	XCTAssertEqualWithAccuracy(so2, 1.36759996, 0.00001);
	so2 = sm.getVals(0, 28, 2, 0, 70, 0, 0, sm.mSO2Vals);
	XCTAssertEqualWithAccuracy(so2, 1.46039999, 0.00001);
}

extern "C" int mix();

- (void)
testOldMixer
{
	mix();
}

#if 0
- (void)
testAltMolFractionsDV
{
	BasaniteDissolvedVolatiles	DVDP3_295_avg_DV(1100, 5000, 2.52356903, -7.63, 0.9299, 0.5537, 1.498, 0.21662);
	
	DVDP3_295_avg_DV.molPercentToTeph()
	
	double co, co2, h2o, h2s, so2;
	DVDP3_295_avg_DV.molFractions(1.0, co, co2, h2o, h2s, so2);
	
	XCTAssertEqualWithAccuracy(co, 0.00498793412675, 0.00001);
	XCTAssertEqualWithAccuracy(co2, 0.92384810807, 0.0001);
	XCTAssertEqualWithAccuracy(h2o, 0.0608696545967, 0.00001);
	XCTAssertEqualWithAccuracy(h2s, 6.54620467794e-08, 0.001e-8);
	XCTAssertEqualWithAccuracy(so2, 0.00977660298284, 0.0001);
}
#endif

- (void)
testAltMolFractions
{
	BasaniteMeltInclusion		DVDP3_295a(1100, 5000, 2.60, -7.63, 0.925);
	DVDP3_295a.calcComposition();
	
	double co, co2, h2o, h2s, so2;
	DVDP3_295a.depressurize(1.0, co, co2, h2o, h2s, so2);
	
	XCTAssertEqualWithAccuracy(co, 0.00498793412675, 0.00001);
	XCTAssertEqualWithAccuracy(co2, 0.92384810807, 0.0001);
	XCTAssertEqualWithAccuracy(h2o, 0.0608696545967, 0.00001);
	XCTAssertEqualWithAccuracy(h2s, 6.54620467794e-08, 0.001e-8);
	XCTAssertEqualWithAccuracy(so2, 0.00977660298284, 0.0001);
}

- (void)
testLowPhonolite
{
	MeltInclusion	EA1_a(1000, 2534, std::log10(3.65685507), -11.26, -2.7);
	EA1_a.calcComposition();
	
	double co, co2, h2o, h2s, so2;
	EA1_a.depressurize(1.0, co, co2, h2o, h2s, so2);
	XCTAssertEqualWithAccuracy(co, 0.0392225980442, 0.00001);
	XCTAssertEqualWithAccuracy(co2, 0.960785260391, 0.0001);
	XCTAssertEqualWithAccuracy(h2o, 0.00150074694977, 0.00001);
	XCTAssertEqualWithAccuracy(h2s, 2.77152751933e-08, 0.001e-8);
	XCTAssertEqualWithAccuracy(so2, 2.13639184163e-05, 0.0001);
}

- (void)
testLowBasanite
{
	BasaniteMeltInclusion		DVDP3_295a(1100, 5000, 2.60, -7.63, 0.925);
	DVDP3_295a.calcComposition();
	
	double co, co2, h2o, h2s, so2;
	DVDP3_295a.depressurize(1.0, co, co2, h2o, h2s, so2);
	XCTAssertEqualWithAccuracy(co, 0.00498793412675, 0.00001);
	XCTAssertEqualWithAccuracy(co2, 0.92384810807, 0.0001);
	XCTAssertEqualWithAccuracy(h2o, 0.0608696545967, 0.00001);
	XCTAssertEqualWithAccuracy(h2s, 6.54620467794e-08, 0.001e-8);
	XCTAssertEqualWithAccuracy(so2, 0.00977660298284, 0.0001);
}

- (void)
testAltFS2
{
	BasaniteMeltInclusion		DVDP3_295a(1100, 5000, 2.60, -7.63, 0.925);
	DVDP3_295a.calcComposition();
	
	
	double fLow = DVDP3_295a.fS2(1.0);
	
	XCTAssertEqualWithAccuracy(fLow, 4.64353282791e-09, 0.0001e-9);
	
	double fHigh = DVDP3_295a.fS2();
	double fHighAlt = DVDP3_295a.fS2(DVDP3_295a.p());
	XCTAssertEqualWithAccuracy(fHigh, fHighAlt, 0.0000001);
}

- (void)
testAltFH2
{
	BasaniteMeltInclusion		DVDP3_295a(1100, 5000, 2.60, -7.63, 0.925);
	DVDP3_295a.calcComposition();
	
	double fLow = DVDP3_295a.fH2(1.0);
	
	XCTAssertEqualWithAccuracy(fLow, 0.000138178467699, 0.00001);
	
	double fHigh = DVDP3_295a.fH2();
	double fHighAlt = DVDP3_295a.fH2(DVDP3_295a.p());
	XCTAssertEqualWithAccuracy(fHigh, fHighAlt, 0.0000000000001);
}

- (void)
testAltFO2
{
	BasaniteMeltInclusion		DVDP3_295a(1100, 5000, 2.60, -7.63, 0.925);
	DVDP3_295a.calcComposition();
	
	double fLow = DVDP3_295a.fO2(1.0);
	XCTAssertEqualWithAccuracy(fLow, 0.000000015941728602617667, 0.0000000001);
	
	double fHigh = DVDP3_295a.fO2();
	double fHighAlt = DVDP3_295a.fO2(DVDP3_295a.p());
	XCTAssertEqualWithAccuracy(fHigh, fHighAlt, 0.0000000000001);
}

- (void)
testDissolvedVolatiles
{
	MeltInclusion	EA1_avg(1000, 2671.3, 0.60650829, -11.26, -2.7);//, 0.0691, 0.167, 0.03805);
	EA1_avg.calcComposition();
	
	XCTAssertEqualWithAccuracy(EA1_avg.KFCO2(), 11609339.6907, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.KFH2O(), 17151809.4747, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.KFH2S(), 13.7246296563, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.KFSO2(), 98548280692.608109, 0.0001);
	
	XCTAssertEqualWithAccuracy(EA1_avg.gammaCO(), 1.88658690409, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.gammaCO2(), 1.71293605864, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.gammaH2O(), 0.948049278037, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.gammaH2S(), 1.59056956512, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.gammaS2(), 1.52394254014, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.gammaSO2(), 1.80117893877, 0.0001);
	
#if 0
	XCTAssertEqualWithAccuracy(EA1_avg.fCOPure(), 5039.63959691, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.fCO2Pure(), 4575.76609344, 0.0001);
	
	XCTAssertEqualWithAccuracy(EA1_avg.fCRatio(), 0.0367445117611, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.fCPureRatio(), 1.10137613986, 0.0001);
	
	XCTAssertEqualWithAccuracy(EA1_avg.molFractionCRatio(), 0.0333623640745, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.molFractionSRatio(), 2.88439092592, 0.0001);
	
	XCTAssertEqualWithAccuracy(EA1_avg.DCO2(), 0.967714748249, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.DSO2(), 0.257440617865, 0.0001);
#endif
	
	BasaniteMeltInclusion		DVDP3_295_avg(1100, 5000, 2.52356903, -7.63, 0.9299);
	DVDP3_295_avg.calcComposition();
	MeltInclusion				T97009_avg(1081, 3000, 1.685047, -9.99, -3.01);
	T97009_avg.calcComposition();
	
#if 0
	XCTAssertEqualWithAccuracy(DVDP3_295_avg.WPH2O(), 1.498, 0.0001);
	XCTAssertEqualWithAccuracy(T97009_avg.WPH2O(), 0.527, 0.0001);
	
	XCTAssertEqualWithAccuracy(DVDP3_295_avg.deltaToTephH2O(&T97009_avg), 3.753, 0.0001);
	XCTAssertEqualWithAccuracy(DVDP3_295_avg.deltaToTephCO2(&T97009_avg), 1.3398, 0.0001);
	XCTAssertEqualWithAccuracy(DVDP3_295_avg.deltaToTephSTotal(&T97009_avg), 0.551914285714, 0.0001);
	
	XCTAssertEqualWithAccuracy(T97009_avg.WPCO2(), 0.2422, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.WPCO2(), 0.0691, 0.0001);
	XCTAssertEqualWithAccuracy(T97009_avg.deltaToPhonoliteCO2(&EA1_avg), 0.961538297872, 0.0001);
	XCTAssertEqualWithAccuracy(T97009_avg.deltaToPhonoliteH2O(&EA1_avg), 2.07555319149, 0.0001);
	XCTAssertEqualWithAccuracy(T97009_avg.deltaToPhonoliteSTotal(&EA1_avg), 0.247056382979, 0.0001);
#endif
	
	MeltInclusion				ll(0.0, 0.0, 0.0, 0.0, 0.0);//, 0.03, 0.11, 0.0);
#if 0
	XCTAssertEqualWithAccuracy(EA1_avg.deltaToLLCO2(&ll), 0.0391, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.deltaToLLH2O(&ll), 0.057, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_avg.deltaToLLSTotal(&ll), 0.03805, 0.0001);
#endif
	
	//	Bas -> Teph
	
	WeightPercents bas(0.5537, 1.498, 0.21662);
	WeightPercents teph(0.2422, 0.527, 0.067);
	DVDP3_295_avg.calcDeltaComposition(bas, kBasFrac, teph);
	
	double co, co2, h2o, h2s, so2;
	DVDP3_295_avg.molFractions(co, co2, h2o, h2s, so2);
	XCTAssertEqualWithAccuracy(co, 0.000293471067079, 0.0001);
	XCTAssertEqualWithAccuracy(co2, 0.111648463276, 0.0001);
	XCTAssertEqualWithAccuracy(h2o, 0.764005981645, 0.0001);
	XCTAssertEqualWithAccuracy(h2s, 0.00182546749279, 0.0001);
	XCTAssertEqualWithAccuracy(so2, 0.122687718583, 0.0001);
	
	double sum = co + co2 + h2o + h2s + so2;
	XCTAssertEqualWithAccuracy(sum, 1.0, 0.001);
	
#if 0
	T97009_avg.molPercentToPhonolite(&EA1_avg, mpCO2, mpH2O, mpSTotal);
	T97009_avg.molFractions(mpCO2, mpH2O, mpSTotal, co, co2, h2o, h2s, so2);
	
	EA1_avg.molPercentToLL(&ll, mpCO2, mpH2O, mpSTotal);
	EA1_avg.molFractions(mpCO2, mpH2O, mpSTotal, co, co2, h2o, h2s, so2);
#endif
	
	
}

- (void)
testEvolution
{
	BasaniteMeltInclusion		DVDP3_295_avg(1100, 5000, 2.52356903, -7.63, 0.9299);
	BasaniteMeltInclusion		DVDP3_295_evolved(DVDP3_295_avg);
	
	WeightPercents bas(0.5537, 1.498, 0.21662);
	WeightPercents teph(0.2422, 0.527, 0.067);
	DVDP3_295_evolved.calcDeltaComposition(bas, kBasFrac, teph);
	
	
	double co, co2, h2o, h2s, so2;
	DVDP3_295_evolved.molFractions(co, co2, h2o, h2s, so2);
	XCTAssertEqualWithAccuracy(co, 0.000293471067079, 0.0001);
	XCTAssertEqualWithAccuracy(co2, 0.111648463276, 0.0001);
	XCTAssertEqualWithAccuracy(h2o, 0.764005981645, 0.0001);
	XCTAssertEqualWithAccuracy(h2s, 0.00182546749279, 0.0001);
	XCTAssertEqualWithAccuracy(so2, 0.122687718583, 0.0001);
	
	double sum = co + co2 + h2o + h2s + so2;
	XCTAssertEqualWithAccuracy(sum, 1.0, 0.0005);
	
	//	Depressurize…
	//	TODO: Verify these values!
	
	DVDP3_295_evolved.depressurize(1.0, co, co2, h2o, h2s, so2);
	XCTAssertEqualWithAccuracy(co, 0.000601138380897, 0.0001);
	XCTAssertEqualWithAccuracy(co2, 0.111340795962, 0.0001);
	XCTAssertEqualWithAccuracy(h2o, 0.74893022884, 0.0001);
	XCTAssertEqualWithAccuracy(h2s, 1.02904425178e-05, 0.0001);
	XCTAssertEqualWithAccuracy(so2, 0.124908481113, 0.0001);
	
	sum = co + co2 + h2o + h2s + so2;
	XCTAssertEqualWithAccuracy(sum, 1.0, 0.1);
}

- (void)
testMolFractions
{
	BasaniteMeltInclusion		DVDP3_295a(1100, 5000, 2.60, -7.63, 0.925);
	DVDP3_295a.calcComposition();
	
	double XH2 = DVDP3_295a.molFractionH2();
	double XH2O = DVDP3_295a.molFractionH2O();
	double XO2 = DVDP3_295a.molFractionO2();
	double XS2 = DVDP3_295a.molFractionS2();
	double XSO2 = DVDP3_295a.molFractionSO2();
	double XH2S = DVDP3_295a.molFractionH2S();
	double XCO = DVDP3_295a.molFractionCO();
	double XCO2 = DVDP3_295a.molFractionCO2();
	
	double sum = XH2 + XH2O + XO2 + XS2 + XSO2 + XH2S + XCO + XCO2;
	XCTAssertEqualWithAccuracy(sum, 1.0, 0.001);
}

- (void)
testFS2
{
	double t = 1100;
	double p = 5000;
	double fO2 = std::pow(10, -7.63);
	double fH2O = std::pow(10, 2.601099);
	
	double tK = t + 273.15;
	
	double logKSO2 = logKFSO2(tK);
	double logKH2S = logKFH2S(tK);
	double logKH2O = logKFH2O(tK);
	
	double KSO2 = std::pow(10, logKSO2);
	double KH2S = std::pow(10, logKH2S);
	double KH2O = std::pow(10, logKH2O);
	
	double fH2 = fH2O / (KH2O * std::sqrt(fO2));
	
	//	Gammas…
	
	CriticalParameters		s2;
	s2.mTc = 208.15;
	s2.mPc = 72.954;
	
	double gammaS2;
	redlichKwong(s2, tK, p, NULL, NULL, &gammaS2, NULL, NULL);
	
	CriticalParameters		so2;
	so2.mTc = 430.95;
	so2.mPc = 78.7295;
	
	double gammaSO2;
	redlichKwong(so2, tK, p, NULL, NULL, &gammaSO2, NULL, NULL);

	CriticalParameters		h2s;
	h2s.mTc = 373.55;
	h2s.mPc = 90.0779;
	
	double gammaH2S;
	redlichKwong(h2s, tK, p, NULL, NULL, &gammaH2S, NULL, NULL);
	
	//	Partial Pressure…
	
	double pS2Total = 64.67754225;
	
	//	Test FS2…
	
	double fs2 = fS2(gammaS2, KSO2, fO2, gammaSO2, KH2S, fH2, gammaH2S, pS2Total);
	//double fs2 = fS2(2.195, 4786300923, std::pow(10, -7.63), 3.647, 6.309573445, 1.164392283, 2.671, 64.67754225);
	XCTAssertEqualWithAccuracy(fs2, 1.1511, 0.0001);
}

- (void)
testPhonolite
{
	MeltInclusion				EA1_a(1000, 2534, std::log10(3.65685507), -11.26, -2.7);
	EA1_a.calcComposition();
	
	XCTAssertEqualWithAccuracy(EA1_a.KFCO2(), 11609339.6907, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.KFH2O(), 17151809.4747, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.KFH2S(), 13.7246296563, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.KFSO2(), 98548280692.608109, 0.0001);
	
	XCTAssertEqualWithAccuracy(EA1_a.gammaCO(), 1.82337817643, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.gammaCO2(), 1.65686765952, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.gammaH2(), 1.54730663533, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.gammaH2O(), 0.937525993842, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.gammaH2S(), 1.54093239348, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.gammaO2(), 1.58907339097, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.gammaS2(), 1.48815859028, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.gammaSO2(), 1.72565453346, 0.0001);

	XCTAssertEqualWithAccuracy(EA1_a.PCO(), 81.7444672809, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.PCO2(), 2448.24467365, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.PH2(), 0.0587788949176, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.PH2O(), 3.90053725872, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.PH2S(), 0.0361838566384, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.PO2(), 0.0000000000034582472841224929, 0.000000000000001);
	XCTAssertEqualWithAccuracy(EA1_a.PS2(), 0.00134075919596, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.PSO2(), 0.0140182950035, 0.0001);
	
	XCTAssertEqualWithAccuracy(EA1_a.fCO(), 149.051077684, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.fCO2(), 4056.41742237, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.fH2(), 0.0909489741236, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.fH2S(), 0.0557568768153, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.fO2(), 0, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.fS2(), 0.00199526231497, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.fSO2(), 0.0241907343242, 0.0001);
	
	XCTAssertEqualWithAccuracy(EA1_a.molFractionCO(), 0.0322590636468, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.molFractionCO2(), 0.966158119043, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.molFractionH2(), 2.31960911277e-5, 0.0000001);
	XCTAssertEqualWithAccuracy(EA1_a.molFractionH2O(), 0.00153928068616, 0.0001);
	XCTAssertEqualWithAccuracy(EA1_a.molFractionH2S(), 1.42793435826e-05, 0.0000001);
	XCTAssertEqualWithAccuracy(EA1_a.molFractionO2(), 1.36473847045e-15, 0.000000000000001);
	XCTAssertEqualWithAccuracy(EA1_a.molFractionS2(), 5.29107812139e-7, 0.0000001);
	XCTAssertEqualWithAccuracy(EA1_a.molFractionSO2(), 5.53208169041e-6, 0.0000001);
}

- (void)
testBasanite
{
	BasaniteMeltInclusion		DVDP3_295a(1100, 5000, 2.60, -7.63, 0.925);
	DVDP3_295a.calcComposition();
	
	double PCO = DVDP3_295a.PCO();
	XCTAssertEqualWithAccuracy(PCO, 19.1802109823, 0.0001);
	
	double fCO2 = DVDP3_295a.fCO2();
	XCTAssertEqualWithAccuracy(fCO2, 13421.3162733, 0.0001);
	
	double XCO2 = DVDP3_295a.molFractionCO2();
	XCTAssertEqualWithAccuracy(XCO2, 0.925, 0.0001);
	
	double fS2 = DVDP3_295a.fS2();
	XCTAssertEqualWithAccuracy(fS2, 0.644581489263, 0.0001);
}

- (void)
testBasaniteNaN
{
	MonteCarlo::ValueListT	vals =
	{
		1082.9885458293031,
		4390.1389168458663,
		2.5749396073971589,
		-7.3696249156708955,
		1.0870757520331997,
		0.62954224970918204,
		1.7169669029397017,
		0.084761953361175895,
	};
	
	BasaniteMeltInclusion	mi(vals);
	mi.calcComposition();
	
	double	co, co2, h2o, h2s, so2;
	mi.depressurize(1.0, co, co2, h2o, h2s, so2);
	
	XCTAssertEqualWithAccuracy(co, 1.0, 0.001);
}

- (void)
testXH2
{
	MeltInclusion				EA1_a(1000, 2534, std::log10(3.65685507), -11.26, -2.7);
	EA1_a.calcComposition();
	XCTAssertEqualWithAccuracy(EA1_a.molFractionH2(), 2.31960911277e-05, 0.0001e-5);
}

- (void)
testRedlichKwong1
{
	CriticalParameters		h2o;
	h2o.mTc = 647.25;
	h2o.mPc = 221.1925;
	
	double gamma;
	redlichKwong(h2o, 1273.15, 2500, NULL, NULL, &gamma, NULL, NULL);
}

- (void)
testRedlichKwongFugacity
{
	CriticalParameters		h2o;
	h2o.mTc = 647.25;
	h2o.mPc = 221.1925;
	
	double gamma;
	redlichKwong(h2o, 1273.15, 2500, NULL, NULL, &gamma, NULL, NULL);
	XCTAssertEqualWithAccuracy(gamma, 0.9350, 0.0001);
	
	redlichKwong(h2o, 2273.15, 2500, NULL, NULL, &gamma, NULL, NULL);
	XCTAssertEqualWithAccuracy(gamma, 1.1331, 0.0001);
	
	redlichKwong(h2o, 1273.15, 1000, NULL, NULL, &gamma, NULL, NULL);
	XCTAssertEqualWithAccuracy(gamma, 0.9013, 0.0001);
	
	redlichKwong(h2o, 1273.15, 8000, NULL, NULL, &gamma, NULL, NULL);
	XCTAssertEqualWithAccuracy(gamma, 2.0193, 0.0001);
}

- (void)
disableTestRedlichKwongPerformance
{
	[self measureBlock:
	^{
		CriticalParameters		h2o;
		h2o.mTc = 647.25;
		h2o.mPc = 221.1925;
	
		for (uint64_t i = 0; i < 1000000; ++i)
		{
			double gamma;
			redlichKwong(h2o, 1273.15, 2500, NULL, NULL, &gamma, NULL, NULL);
		}
	}];
}

- (void)
testECOF
{
	double k;
	k = logKFH2O(300);		XCTAssertEqualWithAccuracy(k, 39.776, 0.001);
	k = logKFH2O(1000);		XCTAssertEqualWithAccuracy(k, 10.061, 0.001);
	k = logKFH2O(1800);		XCTAssertEqualWithAccuracy(k,  4.280, 0.001);
	
	k = logKFH2S(300);		XCTAssertEqualWithAccuracy(k,  5.846, 0.001);
	k = logKFH2S(1000);		XCTAssertEqualWithAccuracy(k,  2.170, 0.001);
	k = logKFH2S(1800);		XCTAssertEqualWithAccuracy(k,  0.039, 0.001);
	
	k = logKFSO2(300);		XCTAssertEqualWithAccuracy(k, 52.243, 0.001);
	k = logKFSO2(1000);		XCTAssertEqualWithAccuracy(k, 15.113, 0.001);
	k = logKFSO2(1800);		XCTAssertEqualWithAccuracy(k,  6.721, 0.001);
	
	
	k = logKFCO2(300);		XCTAssertEqualWithAccuracy(k, 44.7390, 0.001);
	k = logKFCO2(1000);		XCTAssertEqualWithAccuracy(k, 10.1579, 0.001);
	k = logKFCO2(1800);		XCTAssertEqualWithAccuracy(k, 14.1190, 0.001);
}

@end
