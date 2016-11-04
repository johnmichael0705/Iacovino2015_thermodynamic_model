//
//  MeltInclusion.cpp
//  Iacovino
//
//  Created by Roderick Mann on 4/25/15.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#include "MeltInclusion.h"


#include <cmath>
#include <cstdio>

#import "EquilibriumConstantOfFormation.h"

#include "MonteCarlo.h"





double	//	 A	               B              C             D                  E              G             H
fS2(double inGammaS2, double inKSO2, double inFO2, double inGammaSO2, double inKH2S, double inFH2, double inGammaH2S, double inP);



#pragma mark -
#pragma mark • MeltInclusion

MeltInclusion::MeltInclusion()
	:
	mTemperature(0.0),
	mPressure(0.0),
	mLogFugacityH2O(0.0),
	mLogFugacityO2(0.0),
	mLogFugacityS2(0.0),

	mGammaCO(0.0),
	mGammaCO2(0.0),
	mGammaH2(0.0),
	mGammaH2O(0.0),
	mGammaH2S(0.0),
	mGammaO2(0.0),
	mGammaS2(0.0),
	mGammaSO2(0.0),
	mKFCO2(0.0),
	mKFH2O(0.0),
	mKFH2S(0.0),
	mKFSO2(0.0),
	mPCO(0.0),
	mPCO2(0.0),
	mFCO(0.0),
	mFCO2(0.0),
	mFH2O(0.0),
	mFO2(0.0),
	mFS2(0.0),
	mXH2(0.0),
	mXO2(0.0),
	mXS2(0.0),
	mXCO(0.0),
	mXCO2(0.0),
	mXH2O(0.0),
	mXH2S(0.0),
	mXSO2(0.0)
{
}

MeltInclusion::MeltInclusion(double inTemperature,
								double inPressure,
								double inLogFH2O,
								double inLogFO2,
								double inLogFS2)
	:
	mTemperature(inTemperature),
	mPressure(inPressure),
	mLogFugacityH2O(inLogFH2O),
	mLogFugacityO2(inLogFO2),
	mLogFugacityS2(inLogFS2),

	mGammaCO(0.0),
	mGammaCO2(0.0),
	mGammaH2(0.0),
	mGammaH2O(0.0),
	mGammaH2S(0.0),
	mGammaO2(0.0),
	mGammaS2(0.0),
	mGammaSO2(0.0),
	mKFCO2(0.0),
	mKFH2O(0.0),
	mKFH2S(0.0),
	mKFSO2(0.0),
	mPCO(0.0),
	mPCO2(0.0),
	mFCO(0.0),
	mFCO2(0.0),
	mFH2O(0.0),
	mFO2(0.0),
	mFS2(0.0),
	mXH2(0.0),
	mXO2(0.0),
	mXS2(0.0),
	mXCO(0.0),
	mXCO2(0.0),
	mXH2O(0.0),
	mXH2S(0.0),
	mXSO2(0.0)
{
}

MeltInclusion::MeltInclusion(const MonteCarlo::ValueListT& inInputs)
	:
	WeightPercents(inInputs[5], inInputs[6], inInputs[7]),
	mTemperature(inInputs[0]),
	mPressure(inInputs[1]),
	mLogFugacityH2O(inInputs[2]),
	mLogFugacityO2(inInputs[3]),
	mLogFugacityS2(inInputs[4]),

	mGammaCO(0.0),
	mGammaCO2(0.0),
	mGammaH2(0.0),
	mGammaH2O(0.0),
	mGammaH2S(0.0),
	mGammaO2(0.0),
	mGammaS2(0.0),
	mGammaSO2(0.0),
	mKFCO2(0.0),
	mKFH2O(0.0),
	mKFH2S(0.0),
	mKFSO2(0.0),
	mPCO(0.0),
	mPCO2(0.0),
	mFCO(0.0),
	mFCO2(0.0),
	mFH2O(0.0),
	mFO2(0.0),
	mFS2(0.0),
	mXH2(0.0),
	mXO2(0.0),
	mXS2(0.0),
	mXCO(0.0),
	mXCO2(0.0),
	mXH2O(0.0),
	mXH2S(0.0),
	mXSO2(0.0)
{
}


MeltInclusion::MeltInclusion(const MeltInclusion& inRHS)
{
	*this = inRHS;
}

MeltInclusion&
MeltInclusion::operator=(const MeltInclusion& inRHS)
{
	WeightPercents::operator=(inRHS);
	
	mTemperature = inRHS.mTemperature;
	mPressure = inRHS.mPressure;
	mLogFugacityH2O = inRHS.mLogFugacityH2O;
	mLogFugacityO2 = inRHS.mLogFugacityO2;
	mLogFugacityS2 = inRHS.mLogFugacityS2;

	mGammaCO = inRHS.mGammaCO;
	mGammaCO2 = inRHS.mGammaCO2;
	mGammaH2 = inRHS.mGammaH2;
	mGammaH2O = inRHS.mGammaH2O;
	mGammaH2S = inRHS.mGammaH2S;
	mGammaO2 = inRHS.mGammaO2;
	mGammaS2 = inRHS.mGammaS2;
	mGammaSO2 = inRHS.mGammaSO2;
	mKFCO2 = inRHS.mKFCO2;
	mKFH2O = inRHS.mKFH2O;
	mKFH2S = inRHS.mKFH2S;
	mKFSO2 = inRHS.mKFSO2;
	mPCO = inRHS.mPCO;
	mPCO2 = inRHS.mPCO2;
	mFCO = inRHS.mFCO;
	mFCO2 = inRHS.mFCO2;
	mFH2O = inRHS.mFH2O;
	mFO2 = inRHS.mFO2;
	mFS2 = inRHS.mFS2;
	mXH2 = inRHS.mXH2;
	mXO2 = inRHS.mXO2;
	mXS2 = inRHS.mXS2;
	mXCO = inRHS.mXCO;
	mXCO2 = inRHS.mXCO2;
	mXH2O = inRHS.mXH2O;
	mXH2S = inRHS.mXH2S;
	mXSO2 = inRHS.mXSO2;
	
	return *this;
}

#pragma mark -
#pragma mark • Model


void
MeltInclusion::calcComposition()
{
	//	Common calculations on inputs…
	
	mGammaCO = gammaCO(mPressure);
	mGammaCO2 = gammaCO2(mPressure);
	mGammaH2 = gammaH2(mPressure);
	mGammaH2O = gammaH2O(mPressure);
	mGammaH2S = gammaH2S(mPressure);
	mGammaO2 = gammaO2(mPressure);
	mGammaS2 = gammaS2(mPressure);
	mGammaSO2 = gammaSO2(mPressure);
	
	mFH2O = std::pow(10, mLogFugacityH2O);
	mFO2 = std::pow(10, mLogFugacityO2);
	
	mKFCO2 = std::pow(10, logKFCO2(tK()));
	mKFH2O = std::pow(10, logKFH2O(tK()));
	mKFH2S = std::pow(10, logKFH2S(tK()));
	mKFSO2 = std::pow(10, logKFSO2(tK()));
	
	//	MeltInclusion calculations on inputs…
	
	mFS2 = std::pow(10, mLogFugacityS2);
	
	//	MeltInclusion high-pressure model…
	
	//	Hydrogen & Oxygen…
	
	double fO2Sqrt = std::sqrt(mFO2);
	double fH2 = mFH2O / (mKFH2O * fO2Sqrt);
	double pH2 = fH2 / mGammaH2;
	mXH2 = fH2 / (mGammaH2 * mPressure);
	
	double pH2O = mFH2O / mGammaH2O;
	mXH2O = mFH2O / (mGammaH2O * mPressure);
	
	double pO2 = mFO2 / mGammaO2;
	mXO2 = mFO2 / (mGammaO2 * mPressure);
	
	//	Sulfur…
	
	double pS2 = mFS2 / mGammaS2;
	mXS2 = mFS2 / (mGammaS2 * mPressure);
	
	double fS2Sqrt = std::sqrt(mFS2);
	double fH2S = mKFH2S * fH2 * fS2Sqrt;
	double pH2S = fH2S / mGammaH2S;
	mXH2S = fH2S / (mGammaH2S * mPressure);
	
	double fSO2 = mKFSO2 * mFO2 * fS2Sqrt;
	double pSO2 = fSO2 / mGammaSO2;
	mXSO2 = fSO2 / (mGammaSO2 * mPressure);
	
	//	Carbon…
	
	const double partialPTot = mPressure - pH2 - pH2O - pH2S - pO2 - pS2 - pSO2;
	mPCO = mGammaCO2 * partialPTot / (mGammaCO2 + mGammaCO * mKFCO2 * fO2Sqrt);
	mPCO2 = mPressure - mPCO - pH2 - pH2S - pO2 - pS2 - pSO2;
	mFCO2 = mPCO2 * mGammaCO2;
	mFCO = mFCO2 / (mKFCO2 * fO2Sqrt);
	mXCO = mFCO / (mGammaCO * mPressure);
	mXCO2 = mFCO2 / (mGammaCO2 * mPressure);
}

void
MeltInclusion::depressurize(double inPressure,
							double& outCO,
							double& outCO2,
							double& outH2O,
							double& outH2S,
							double& outSO2) const
{
	double
	mLowGammaCO = gammaCO(inPressure),
	mLowGammaCO2 = gammaCO2(inPressure),
	mLowGammaH2 = gammaH2(inPressure),
	mLowGammaH2O = gammaH2O(inPressure),
	mLowGammaH2S = gammaH2S(inPressure),
	//mLowGammaO2 = gammaO2(inPressure),
	mLowGammaS2 = gammaS2(inPressure),
	mLowGammaSO2 = gammaSO2(inPressure);
	
	//	Low O2…
	
	double logFO2NNOHighP = -24930.0 / tK() + 9.36 + 0.046 * (p() - 1.0) / tK();
	double dNNO = mLogFugacityO2 - logFO2NNOHighP;
	
	double logFO2NNOLowP = -24930.0 / tK() + 9.36 + 0.046 * (inPressure - 1.0) / tK();
	double logFO2LowP = dNNO + logFO2NNOLowP;
	
	double lowFO2 = std::pow(10, logFO2LowP);
	
	//	Low CO…
	
	double molFractionCTotal = mXCO2 * 1.0 / 3.0 + mXCO * 1.0 / 3.0;
	double n = 6.0 * molFractionCTotal * mLowGammaCO2 * inPressure * mLowGammaCO;
	double d = 2.0 * mKFCO2 * std::sqrt(lowFO2) * mLowGammaCO + 2.0 * mLowGammaCO2;
	double lowFCO = n / d;
	
	double mLowCO = lowFCO / (mLowGammaCO * inPressure);
	
	//	Low CO2…
	
	double lowFCO2 = mKFCO2 * lowFCO * std::sqrt(lowFO2);
	double mLowCO2 = lowFCO2 / (mLowGammaCO2 * inPressure);
	
	//	Low H2…
	
	double molFractionHTotal = mXH2 + mXH2O * 2.0 / 3.0 + mXH2S * 2.0 / 3.0;
	
	double a = 3.0 * molFractionHTotal * mLowGammaH2 * inPressure * mLowGammaH2O * mLowGammaH2S;
	double b = 2.0 * mLowGammaH2 * mKFH2O * std::sqrt(lowFO2) * mLowGammaH2S;
	double c = 2.0 * mLowGammaH2 * mLowGammaH2O * mKFH2S * std::sqrt(mFS2);
			d = 3.0 * mLowGammaH2O * mLowGammaH2S;
	
	double lowFH2 = a / (b + c + d);
	
	//	Low H2O…
	
	double lowFH2O = mKFH2O * lowFH2 * std::sqrt(lowFO2);
	double mLowH2O = lowFH2O / (mLowGammaH2O * inPressure);
	
	//	Low fS2…
	
	double lowFS2 = 0.0;
	{
		double molFractionSTotal = mXS2 + mXH2S * 1.0 / 3.0 + mXSO2 * 1.0 / 3.0;
		
		double gH2SSqr = mLowGammaH2S;		gH2SSqr *= gH2SSqr;
		double gS2Sqr = mLowGammaS2;		gS2Sqr *= gS2Sqr;
		double gSO2Sqr = mLowGammaSO2;		gSO2Sqr *= gSO2Sqr;
		
		double fO2Sqr = lowFO2;				fO2Sqr *= fO2Sqr;
		double fH2Sqr = lowFH2;				fH2Sqr *= fH2Sqr;
		
		double KFH2SSqr = mKFH2S;			KFH2SSqr *= KFH2SSqr;
		double KFSO2Sqr = mKFSO2;			KFSO2Sqr *= KFSO2Sqr;
		
		double H = gH2SSqr * gSO2Sqr;
		double A = mKFH2S * mLowGammaSO2 * lowFH2 + mLowGammaH2S * mKFSO2 * lowFO2;
		double B = 36.0 * inPressure * molFractionSTotal * H;
		double C = KFH2SSqr * gSO2Sqr * mLowGammaS2 * fH2Sqr;
		double D = 2.0 * mKFH2S * mLowGammaH2S * mLowGammaS2 * mKFSO2 * mLowGammaSO2 * lowFO2 * lowFH2;
		double E = gH2SSqr * mLowGammaS2 * KFSO2Sqr * fO2Sqr;
		double F = 18.0 * inPressure * gH2SSqr * molFractionSTotal * mLowGammaS2 * gSO2Sqr;
		double G = KFH2SSqr * gS2Sqr * gSO2Sqr * fH2Sqr;
		double L = 2.0 * mKFH2S * mLowGammaH2S * gS2Sqr * mKFSO2 * mLowGammaSO2 * lowFO2 * lowFH2;
		double J = gH2SSqr * gS2Sqr * KFSO2Sqr * fO2Sqr;
		
		lowFS2 = (1.0 / (18.0 * H)) * (-std::pow(mLowGammaS2, 1.5) * A * std::sqrt(B+C+D+E) + F+G+L+J);
	}
	
	//	Low H2S…
	
	double lowFH2S = mKFH2S * lowFH2 * std::sqrt(lowFS2);
	double mLowH2S = lowFH2S / (mLowGammaH2S * inPressure);
	
	//	Low SO2…
	
	double lowFSO2 = mKFSO2 * std::sqrt(lowFS2) * lowFO2;
	double mLowSO2 = lowFSO2 / (mLowGammaSO2 * inPressure);
	
	//	Normalize…
	
	double total = mLowCO + mLowCO2 + mLowH2O + mLowH2S + mLowSO2;
	mLowCO /= total;
	mLowCO2 /= total;
	mLowH2O /= total;
	mLowH2S /= total;
	mLowSO2 /= total;
	
	//	Outputs…
	
	outCO = mLowCO;
	outCO2 = mLowCO2;
	outH2O = mLowH2O;
	outH2S = mLowH2S;
	outSO2 = mLowSO2;
}


#pragma mark -
#pragma mark • Melt Inclusion Evolution

/**
	Delta			inFrac
	--------------	--------------
	Bas -> Teph		kBasFrac
	Teph -> Phon	kTephFrac
	Phon -> LL		kPhonFrac
*/

void
MeltInclusion::calcDeltaComposition(const WeightPercents& inFrom, double inFrac, const WeightPercents& inTo)
{
	calcComposition();
	
	double deltaCO2 = inFrom.WPCO2() / inFrac - inTo.WPCO2();
	double deltaH2O = inFrom.WPH2O() / inFrac - inTo.WPH2O();
	double deltaSTotal = inFrom.WPSTotal() / inFrac - inTo.WPSTotal();
	
	double mpoCO2 = deltaCO2 / kMolWtCO2;
	double mpoH2O = deltaH2O / kMolWtH2O;
	double mpoSTotal = deltaSTotal / kMolWtS;
	
	double totMPO = mpoCO2 + mpoH2O + mpoSTotal;
	double MPCO2 = mpoCO2 / totMPO;
	double MPH2O = mpoH2O / totMPO;
	double MPSTotal = mpoSTotal / totMPO;
	
	molFractions(MPCO2, MPH2O, MPSTotal,
					mXCO,
					mXCO2,
					mXH2O,
					mXH2S,
					mXSO2);
	
	
}

void
MeltInclusion::calcDeltaComposition(const WeightPercents& inTo, double inFrac)
{
	calcDeltaComposition(*this, inFrac, inTo);
}


void
MeltInclusion::molFractions(double inMPCO2, double inMPH2O, double inMPSTotal,
					double& outCO,
					double& outCO2,
					double& outH2O,
					double& outH2S,
					double& outSO2) const
{
	double fCOPure = p() * mGammaCO;
	double fCO2Pure = p() * mGammaCO2;
	
	double fCRatio = mFCO / mFCO2;
	double fCPureRatio = fCOPure / fCO2Pure;
	double molFractionCRatio = fCRatio / fCPureRatio;
	double dCO2 = 1.0 / (1.0 + molFractionCRatio);
	
	double fH2SPure = p() * mGammaH2S;
	double fSO2Pure = p() * mGammaSO2;
	
	double fSRatio = fH2S() / fSO2();
	double fSPureRatio = fH2SPure / fSO2Pure;
	double molFractionSRatio = fSRatio / fSPureRatio;
	double dSO2 = 1.0 / (1.0 + molFractionSRatio);
	
	double SInSO2 = dSO2 * inMPSTotal;
	double SInH2S = inMPSTotal - SInSO2;
	double mpCO2InCO2 = dCO2 * inMPCO2;
	double CO2InCO = inMPCO2 - mpCO2InCO2;
	
	double mpSO2 = SInSO2 * kMolWtSO2 / kMolWtS;
	double mpH2S = SInH2S * kMolWtH2S / kMolWtS;
	double mpCO = CO2InCO * kMolWtCO / kMolWtCO2;
	
	double mpTotal = mpCO + mpCO2InCO2 + inMPH2O + mpH2S + mpSO2;
	
	outCO = mpCO / mpTotal;
	outCO2 = inMPCO2 / mpTotal;
	outH2O = inMPH2O / mpTotal;
	outH2S = mpH2S / mpTotal;
	outSO2 = mpSO2 / mpTotal;
}


#pragma mark -


#if 0
double
MeltInclusion::fCO() const
{
	double fCO2Val = fCO2();
	double r = fCO2Val / (KFCO2() * std::sqrt(fO2()));
	return r;
}
#endif

double
MeltInclusion::fH2() const
{
	double r = fH2O() / (KFH2O() * std::sqrt(fO2()));
	return r;
}

double
MeltInclusion::fH2S() const
{
	double r = KFH2S() * fH2() * std::sqrt(fS2());
	return r;
}

double
MeltInclusion::fSO2() const
{
	double r = KFSO2() * std::sqrt(fS2()) * fO2();
	return r;
}

double
MeltInclusion::PSpeciesS() const
{
	return mPressure - PCO() - PCO2() - PH2O() - PH2() - PO2();
}


#if 0
double
MeltInclusion::PCO() const
{
	const double partialPTot = mPressure - PH2() - PH2O() - PH2S() - PO2() - PS2() - PSO2();
	
	double PCO = gammaCO2() * partialPTot / (gammaCO2() + gammaCO() * KFCO2() * std::sqrt(fO2()));
	return PCO;
}
#endif

#pragma mark -
#pragma mark • Alternate Pressure Calculations

double
MeltInclusion::fCO(double inP)
const
{
	double molFractionCTotal = molFractionCO2() * 1.0 / 3.0 + molFractionCO() * 1.0 / 3.0;
	
	double n = 6.0 * molFractionCTotal * gammaCO2(inP) * inP * gammaCO(inP);
	double d = 2.0 * KFCO2() * std::sqrt(fO2(inP)) * gammaCO(inP) + 2.0 * gammaCO2(inP);
	
	return n / d;
}

double
MeltInclusion::fCO2(double inP) const
{
	return KFCO2() * fCO(inP) * std::sqrt(fO2(inP));
}

double
MeltInclusion::fH2(double inP) const
{
	double molFractionHTotal = molFractionH2() + molFractionH2O() * 2.0 / 3.0 + molFractionH2S() * 2.0 / 3.0;
	
	double a = 3.0 * molFractionHTotal * gammaH2(inP) * inP * gammaH2O(inP) * gammaH2S(inP);
	double fO2Low = fO2(inP);
	double b = 2.0 * gammaH2(inP) * KFH2O() * std::sqrt(fO2Low) * gammaH2S(inP);
	double c = 2.0 * gammaH2(inP) * gammaH2O(inP) * KFH2S() * std::sqrt(fS2());
	double d = 3.0 * gammaH2O(inP) * gammaH2S(inP);
	
	double fH2 = a / (b + c + d);
	return fH2;
}

double
MeltInclusion::fH2O(double inP) const
{
	return KFH2O() * fH2(inP) * std::sqrt(fO2(inP));
}

double
MeltInclusion::fH2S(double inP) const
{
	return KFH2S() * fH2(inP) * std::sqrt(fS2(inP));
}

double
MeltInclusion::fO2(double inP) const
{
	double logFO2NNOHighP = -24930.0 / tK() + 9.36 + 0.046 * (mPressure - 1.0) / tK();
	double dNNO = mLogFugacityO2 - logFO2NNOHighP;
	
	double logFO2NNOLowP = -24930.0 / tK() + 9.36 + 0.046 * (inP - 1.0) / tK();
	double logFO2LowP = dNNO + logFO2NNOLowP;
	
	return std::pow(10, logFO2LowP);
}

double
MeltInclusion::fS2(double inP) const
{
	double molFractionSTotal = mXS2 + mXH2S * 1.0 / 3.0 + mXSO2 * 1.0 / 3.0;
	
	double gH2SSqr = gammaH2S(inP);		gH2SSqr *= gH2SSqr;
	double gS2Sqr = gammaS2(inP);		gS2Sqr *= gS2Sqr;
	double gSO2Sqr = gammaSO2(inP);		gSO2Sqr *= gSO2Sqr;
	
	double fO2Sqr = fO2(inP);			fO2Sqr *= fO2Sqr;
	double fH2Sqr = fH2(inP);			fH2Sqr *= fH2Sqr;
	
	double KFH2SSqr = KFH2S();			KFH2SSqr *= KFH2SSqr;
	double KFSO2Sqr = KFSO2();			KFSO2Sqr *= KFSO2Sqr;
	
	double H = gH2SSqr * gSO2Sqr;
	double A = KFH2S() * gammaSO2(inP) * fH2(inP) + gammaH2S(inP) * KFSO2() * fO2(inP);
	double B = 36.0 * inP * molFractionSTotal * H;
	double C = KFH2SSqr * gSO2Sqr * gammaS2(inP) * fH2Sqr;
	double D = 2.0 * KFH2S() * gammaH2S(inP) * gammaS2(inP) * KFSO2() * gammaSO2(inP) * fO2(inP) * fH2(inP);
	double E = gH2SSqr * gammaS2(inP) * KFSO2Sqr * fO2Sqr;
	double F = 18.0 * inP * gH2SSqr * molFractionSTotal * gammaS2(inP) * gSO2Sqr;
	double G = KFH2SSqr * gS2Sqr * gSO2Sqr * fH2Sqr;
	double L = 2.0 * KFH2S() * gammaH2S(inP) * gS2Sqr * KFSO2() * gammaSO2(inP) * fO2(inP) * fH2(inP);
	double J = gH2SSqr * gS2Sqr * KFSO2Sqr * fO2Sqr;
	
	double fS2 = (1.0 / (18.0 * H)) * (-std::pow(gammaS2(inP), 1.5) * A * std::sqrt(B+C+D+E) + F+G+L+J);
	return fS2;
}

double
MeltInclusion::fSO2(double inP) const
{
	return KFSO2() * std::sqrt(fS2(inP)) * fO2(inP);
}

#pragma mark -
#pragma mark • Fugacity Coefficients (Gamma)

CriticalParameters			MeltInclusion::sCPCO	=	{ 133.15,  34.9571,	 0.049 };
CriticalParameters			MeltInclusion::sCPCO2	=	{ 304.15,  73.8659,	 0.225 };
CriticalParameters			MeltInclusion::sCPH2	=	{  33.25,  12.9696,	-0.218 };
CriticalParameters			MeltInclusion::sCPO2	=	{ 154.75,  50.7638,	 0.021 };		//	Need omega for S2
CriticalParameters			MeltInclusion::sCPS2	=	{ 208.15,  72.954,	 0.0 };			//	Need omega for S2
CriticalParameters			MeltInclusion::sCPSO2	=	{ 430.95,  78.7295,	 0.0256 };
CriticalParameters			MeltInclusion::sCPH2S	=	{ 373.55,  90.0779,	 0.081 };
CriticalParameters			MeltInclusion::sCPH2O	=	{ 647.25, 221.1925,	 0.334 };

double
MeltInclusion::gammaCO(double inP) const
{
	double gamma;
	redlichKwong(sCPCO, tK(), inP, NULL, NULL, &gamma, NULL, NULL);
	return gamma;
}

double
MeltInclusion::gammaCO2(double inP) const
{
	double gamma;
	redlichKwong(sCPCO2, tK(), inP, NULL, NULL, &gamma, NULL, NULL);
	return gamma;
}

double
MeltInclusion::gammaH2(double inP) const
{
	double gamma;
	redlichKwong(sCPH2, tK(), inP, NULL, NULL, &gamma, NULL, NULL);
	return gamma;
}

double
MeltInclusion::gammaH2O(double inP) const
{
	double gamma;
	redlichKwong(sCPH2O, tK(), inP, NULL, NULL, &gamma, NULL, NULL);
	return gamma;
}

double
MeltInclusion::gammaH2S(double inP) const
{
	double gamma;
	redlichKwong(sCPH2S, tK(), inP, NULL, NULL, &gamma, NULL, NULL);
	return gamma;
}

double
MeltInclusion::gammaO2(double inP) const
{
	double gamma;
	redlichKwong(sCPO2, tK(), inP, NULL, NULL, &gamma, NULL, NULL);
	return gamma;
}

double
MeltInclusion::gammaS2(double inP) const
{
	double gamma;
	redlichKwong(sCPS2, tK(), inP, NULL, NULL, &gamma, NULL, NULL);
	return gamma;
}

double
MeltInclusion::gammaSO2(double inP) const
{
	double gamma;
	redlichKwong(sCPSO2, tK(), inP, NULL, NULL, &gamma, NULL, NULL);
	return gamma;
}


#pragma mark -
#pragma mark • Basanite

BasaniteMeltInclusion::BasaniteMeltInclusion(double inTemperature,
												double inPressure,
												double inLogFH2O,
												double inLogFO2,
												double inXFCO2)
	:
	MeltInclusion(inTemperature, inPressure, inLogFH2O, inLogFO2, 0)
{
	mXCO2 = inXFCO2;
}

BasaniteMeltInclusion::BasaniteMeltInclusion(const MonteCarlo::ValueListT& inInputs)
	:
	MeltInclusion(inInputs)
{
	mLogFugacityS2 = 0.0;
	mXCO2 = inInputs[4];
}




void
BasaniteMeltInclusion::calcComposition()
{
	//	This will compute a value for mXCO2 that
	//	is a user input to the Basanite model, so
	//	save that off first, then restore it when
	//	we’re done computing the base class compositions…
	
	double saveXCO2 = mXCO2;
	MeltInclusion::calcComposition();
	mXCO2 = saveXCO2;
	
	//	Common calculations on inputs…
	
	mGammaCO = gammaCO(mPressure);
	mGammaCO2 = gammaCO2(mPressure);
	mGammaH2 = gammaH2(mPressure);
	mGammaH2O = gammaH2O(mPressure);
	mGammaH2S = gammaH2S(mPressure);
	mGammaO2 = gammaO2(mPressure);
	mGammaS2 = gammaS2(mPressure);
	mGammaSO2 = gammaSO2(mPressure);
	
	mFH2O = std::pow(10, mLogFugacityH2O);
	mFO2 = std::pow(10, mLogFugacityO2);
	
	mKFCO2 = std::pow(10, logKFCO2(tK()));
	mKFH2O = std::pow(10, logKFH2O(tK()));
	mKFH2S = std::pow(10, logKFH2S(tK()));
	mKFSO2 = std::pow(10, logKFSO2(tK()));
	
	//	BasaniteMeltInclusion calculations on inputs…
	
	//	MeltInclusion high-pressure model…
	
	//	Hydrogen & Oxygen…
	
	double fO2Sqrt = std::sqrt(mFO2);
	double fH2 = mFH2O / (mKFH2O * fO2Sqrt);
	double pH2 = fH2 / mGammaH2;
	mXH2 = fH2 / (mGammaH2 * mPressure);
	
	double pH2O = mFH2O / mGammaH2O;
	mXH2O = mFH2O / (mGammaH2O * mPressure);
	
	double pO2 = mFO2 / mGammaO2;
	mXO2 = mFO2 / (mGammaO2 * mPressure);
	
	//	Carbon…
	
	
	mFCO2 = p() * mGammaCO2 * mXCO2;
	mPCO2 = mFCO2 / mGammaCO2;
	mFCO = mFCO2 / (mKFCO2 * fO2Sqrt);
	mPCO = mFCO / mGammaCO;
	mXCO = mFCO / (mGammaCO * mPressure);
	
	//	S2…
	
	double pSpeciesS = mPressure - mPCO - mPCO2 - pH2O - pH2 - pO2;
	if (pSpeciesS < 0.0)
	{
		pSpeciesS = 0.0;
	}
	mFS2 = ::fS2(mGammaS2, mKFSO2, mFO2, mGammaSO2, mKFH2S, fH2, mGammaH2S, pSpeciesS);
	
	mXS2 = mFS2 / (mGammaS2 * mPressure);
	
	//	Sulfur…
	
	double fS2Sqrt = std::sqrt(mFS2);
	double fH2S = mKFH2S * fH2 * fS2Sqrt;
	mXH2S = fH2S / (mGammaH2S * mPressure);
	
	double fSO2 = mKFSO2 * mFO2 * fS2Sqrt;
	mXSO2 = fSO2 / (mGammaSO2 * mPressure);
	
}


#if 0
double
BasaniteMeltInclusion::PCO() const
{
	return mFCO / gammaCO();
}

double
BasaniteMeltInclusion::fCO2() const
{
	double fCO2 = p() * gammaCO2() * molFractionCO2();
	return fCO2;
}

double
BasaniteMeltInclusion::fS2() const
{
	double pSpeciesS = PSpeciesS();
	
	double fs2 = ::fS2(gammaS2(), KFSO2(), fO2(), gammaSO2(), KFH2S(), fH2(), gammaH2S(), pSpeciesS);
	return fs2;
}
#endif



#pragma mark - •

WeightPercents::WeightPercents(double inWPCO2,
								double inWPH2O,
								double inWPSTotal)
	:
	mWPCO2(inWPCO2),
	mWPH2O(inWPH2O),
	mWPSTotal(inWPSTotal)
{
}


double	//	 A	               B              C             D                  E              G             H
fS2(double inGammaS2, double inKSO2, double inFO2, double inGammaSO2, double inKH2S, double inFH2, double inGammaH2S, double inP)
{
	double a2 = inGammaS2 * inGammaS2;
	double b2 = inKSO2 * inKSO2;
	double c2 = inFO2 * inFO2;
	double d2 = inGammaSO2 * inGammaSO2;
	double e2 = inKH2S * inKH2S;
	double g2 = inFH2 * inFH2;
	double h2 = inGammaH2S * inGammaH2S;
	
	double v1 = 1.0 / (2 * d2 * h2);
	double v2 = -std::pow(inGammaS2, 1.5) * (inKSO2 * inFO2 * inGammaH2S + inGammaSO2 * inKH2S * inFH2);
	
	double s1 = inGammaS2 * b2 * c2 * h2;
	double s2 = 2 * inGammaS2 * inKSO2 * inFO2 * inGammaSO2 * inKH2S * inFH2 * inGammaH2S;
	double s3 = inGammaS2 * d2 * e2 * g2 + 4 * d2 * h2 * inP;
	double sq = std::sqrt(s1 + s2 + s3);
	
	double v31 = a2 * b2 * c2 * h2;
	double v32 = 2 * a2 * inKSO2 * inFO2 * inGammaSO2 * inKH2S * inFH2 * inGammaH2S;
	double v33 = a2 * d2 * e2 * g2;
	double v34 = 2 * inGammaS2 * d2 * h2 * inP;
	double v3 = v31 + v32 + v33 + v34;
	
	double r = v1 * (v2 * sq + v3);
	
#if 0 && qLogging > 1
	std::fprintf(stderr, "gammaS2:  %30.16f\n", inGammaS2);
	std::fprintf(stderr, "KSO2:     %30.16f\n", inKSO2);
	std::fprintf(stderr, "FO2:      %30.16f\n", inFO2);
	std::fprintf(stderr, "gammaSO2: %30.16f\n", inGammaSO2);
	std::fprintf(stderr, "KH2S:     %30.16f\n", inKH2S);
	std::fprintf(stderr, "FH2:      %30.16f\n", inFH2);
	std::fprintf(stderr, "gammaH2S: %30.16f\n", inGammaH2S);
	std::fprintf(stderr, "PSTotal:  %30.16f\n", inP);
	std::fprintf(stderr, "FS2:      %30.16f\n", r);
#endif
	
	return r;
}

