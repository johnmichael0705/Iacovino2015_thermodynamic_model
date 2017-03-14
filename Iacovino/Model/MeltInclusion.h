/**
	MeltInclusion.h
	Iacovino

	Created by Roderick Mann on 4/25/15.
	
	
	NOTES
	=============
	Performance can be improved by only recomputing values when inputs change (e.g. gamma values).
*/

#ifndef __MeltInclusion__
#define __MeltInclusion__

#include <cmath>

#include "EquilibriumConstantOfFormation.h"
#include "RedlichKwong.h"

#include "MonteCarlo.h"



#pragma mark -
#pragma mark • WeightPercents

class
WeightPercents
{
public:
	WeightPercents()
		:
		mWPCO2(0.0),
		mWPH2O(0.0),
		mWPSTotal(0.0)
	{
	}
	
	WeightPercents(double inWPCO2,
					double inWPH2O,
					double inWPSTotal);

	WeightPercents&
	operator=(const WeightPercents& inRHS)
	{
		mWPCO2 = inRHS.mWPCO2;
		mWPH2O = inRHS.mWPH2O;
		mWPSTotal = inRHS.mWPSTotal;
		
		return *this;
	}
	
	double				WPCO2()						const			{ return mWPCO2; }
	double				WPH2O()						const			{ return mWPH2O; }
	double				WPSTotal()					const			{ return mWPSTotal; }
	
private:
	double				mWPCO2;					//	wt% dissolved CO2
	double				mWPH2O;					//	wt% dissolved H2O
	double				mWPSTotal;
};

//  Fractionation factors (user can edit these -- they should eventually be changed to not be constants, as these values will depend on user data)
const double	kBasFrac				=	0.46;
const double	kTephFrac				=	0.46;
const double	kPhonFrac				=	0.46;

//  Molecular weights of species of interest. Do not change.
const double	kMolWtCO				=	28.0101;
const double	kMolWtCO2				=	44.0095;
const double	kMolWtH2O				=	18.01528;
const double	kMolWtH2S				=	34.08088;
const double	kMolWtS					=	32.065;
const double	kMolWtSO2				=	64.0638;

#pragma mark -


class
MeltInclusion : public WeightPercents
{
public:
	MeltInclusion();
	
	MeltInclusion(double inTemperature,
					double inPressure,
					double inLogFH2O,
					double inLogFO2,
					double inLogFS2);
	MeltInclusion(const MonteCarlo::ValueListT& inInputs);
	MeltInclusion(const MeltInclusion& inRHS);
	
	
	MeltInclusion&			operator=(const MeltInclusion& inRHS);
	
	void
	setInputs(double inTemperature,
				double inPressure,
				double inLogFH2O,
				double inLogFO2,
				double inLogFS2)
	{
		mTemperature = inTemperature;
		mPressure = inPressure;
		mLogFugacityH2O = inLogFH2O;
		mLogFugacityO2 = inLogFO2;
		mLogFugacityS2 = inLogFS2;
	}
	
	/**
		Calculates the high-pressure mol fractions.
	*/
	
	virtual	void			calcComposition();
	
	/**
		Depressurize calculated composition to specified pressure.
	*/
	
	void					depressurize(double inPressure,
											double& outCO,
											double& outCO2,
											double& outH2O,
											double& outH2S,
											double& outSO2) const;
	
	/**
		Return this inclusion’s temperature in K.
	*/
	
	double			tK()				const			{ return mTemperature + 273.15; }
	double			tC()				const			{ return mTemperature; }
	double			p()					const			{ return mPressure; }
	double			logFH2O()			const			{ return mLogFugacityH2O; }
	double			logFO2()			const			{ return mLogFugacityO2; }
	double			logFS2()			const			{ return mLogFugacityS2; }
	
	virtual double	logFS2OrXCO2()		const			{ return logFS2(); }
	
	double			KFCO2()				const			{ return mKFCO2; }
	double			KFH2O()				const			{ return mKFH2O; }
	double			KFH2S()				const			{ return mKFH2S; }
	double			KFSO2()				const			{ return mKFSO2; }
	
	double			gammaCO()			const			{ return mGammaCO; }
	double			gammaCO2()			const			{ return mGammaCO2; }
	double			gammaH2()			const			{ return mGammaH2; }
	double			gammaH2O()			const			{ return mGammaH2O; }
	double			gammaH2S()			const			{ return mGammaH2S; }
	double			gammaO2()			const			{ return mGammaO2; }
	double			gammaS2()			const			{ return mGammaS2; };
	double			gammaSO2()			const			{ return mGammaSO2; };
	
	double			molFractionH2()		const			{ return mXH2; }
	double			molFractionO2()		const			{ return mXO2; }
	double			molFractionS2()		const			{ return mXS2; }
	
	//	The things we actually care about…
	
	double			molFractionCO()		const			{ return mXCO; }
	double			molFractionCO2()	const			{ return mXCO2; }
	double			molFractionH2O()	const			{ return mXH2O; }
	double			molFractionH2S()	const			{ return mXH2S; }
	double			molFractionSO2()	const			{ return mXSO2; }
	
	
	
	
	
	
	virtual	double			PCO()				const			{ return mPCO; }
	virtual	double			PCO2()				const			{ return mPCO2; }
	
	virtual	double			PH2()				const			{ return fH2()	/ gammaH2(); }
	virtual	double			PH2O()				const			{ return fH2O()	/ gammaH2O(); }
	virtual	double			PH2S()				const			{ return fH2S()	/ gammaH2S(); }
	virtual	double			PO2()				const			{ return fO2()	/ gammaO2(); }
	virtual	double			PS2()				const			{ return fS2()	/ gammaS2(); }
	virtual	double			PSO2()				const			{ return fSO2() / gammaSO2(); }
	
	virtual	double			fCO()				const			{ return mFCO; }
	virtual	double			fCO2()				const			{ return mFCO2; }
	virtual double			fH2()				const;
	virtual	double			fH2O()				const			{ return mFH2O; }
	virtual double			fH2S()				const;
	virtual	double			fO2()				const			{ return mFO2; }
	virtual	double			fS2()				const			{ return mFS2; }
	virtual	double			fSO2()				const;
	
	virtual	double			fCO(double inP)		const;
	virtual	double			fCO2(double inP)	const;
	virtual	double			fH2(double inP)		const;
	virtual	double			fH2O(double inP)	const;
	virtual double			fH2S(double inP)	const;
	virtual	double			fO2(double inP)		const;
	virtual	double			fS2(double inP)		const;
	virtual	double			fSO2(double inP)	const;
	
	virtual	double			PSpeciesS()			const;
	
	
	virtual
	void
	molFractions(	double& outCO,
					double& outCO2,
					double& outH2O,
					double& outH2S,
					double& outSO2) const
	{
		outCO = molFractionCO();
		outCO2 = molFractionCO2();
		outH2O = molFractionH2O();
		outH2S = molFractionH2S();
		outSO2 = molFractionSO2();
	}
	
#if 0
	virtual
	void
	molFractions( double inP,
					double& outCO,
					double& outCO2,
					double& outH2O,
					double& outH2S,
					double& outSO2) const
	{
		outCO = fCO(inP) / (gammaCO(inP) * inP);
		outCO2 = fCO2(inP) / (gammaCO2(inP) * inP);
		outH2O = fH2O(inP) / (gammaH2O(inP) * inP);
		outH2S = fH2S(inP) / (gammaH2S(inP) * inP);
		outSO2 = fSO2(inP) / (gammaSO2(inP) * inP);
	}
#endif
	
	virtual	void		calcDeltaComposition(const WeightPercents& inFrom, double inFrac, const WeightPercents& inTo);
	virtual	void		calcDeltaComposition(const WeightPercents& inTo, double inFrac);

protected:
	virtual	double			gammaCO(double inP)				const;
	virtual	double			gammaCO2(double inP)			const;
	virtual	double			gammaH2(double inP)				const;
	virtual	double			gammaH2O(double inP)			const;
	virtual	double			gammaH2S(double inP)			const;
	virtual	double			gammaO2(double inP)				const;
	virtual	double			gammaS2(double inP)				const;
	virtual	double			gammaSO2(double inP)			const;
	
	void					molFractions(double inMPCO2, double inMPH2O, double inMPSTotal,
											double& outCO,
											double& outCO2,
											double& outH2O,
											double& outH2S,
											double& outSO2) const;

protected:
	double					mTemperature;			//	(°C)
	double					mPressure;				//	(bar)
	double					mLogFugacityH2O;		//	(log) (bar)
	double					mLogFugacityO2;			//	(log) (bar)
	double					mLogFugacityS2;			//	(log) (bar) (Ignored by Basanite)
	
	double					mGammaCO;
	double					mGammaCO2;
	double					mGammaH2;
	double					mGammaH2O;
	double					mGammaH2S;
	double					mGammaO2;
	double					mGammaS2;
	double					mGammaSO2;
	
	double					mKFCO2;
	double					mKFH2O;
	double					mKFH2S;
	double					mKFSO2;
	
	double					mPCO;
	double					mPCO2;
	
	double					mFCO;
	double					mFCO2;
	double					mFH2O;
	double					mFO2;
	double					mFS2;
	
	double					mXH2;
	double					mXO2;
	double					mXS2;
	
	double					mXCO;
	double					mXCO2;
	double					mXH2O;
	double					mXH2S;
	double					mXSO2;
	
private:
	static	CriticalParameters			sCPCO;
	static	CriticalParameters			sCPCO2;
	static	CriticalParameters			sCPH2;
	static	CriticalParameters			sCPH2S;
	static	CriticalParameters			sCPH2O;
	static	CriticalParameters			sCPO2;
	static	CriticalParameters			sCPS2;
	static	CriticalParameters			sCPSO2;
};



class
BasaniteMeltInclusion : public virtual MeltInclusion
{
public:
	BasaniteMeltInclusion(double inTemperature,
							double inPressure,
							double inLogFH2O,
							double inLogFO2,
							double inXFCO2);
	BasaniteMeltInclusion(const MonteCarlo::ValueListT& inInputs);
	
	virtual double	logFS2OrXCO2()		const			{ return mFS2; }
	
	/**
		Calculates the high-pressure mol fractions.
	*/
	
	virtual	void			calcComposition();
	
	
	
	//virtual	double			PCO()					const;
	//virtual	double			PCO2()					const			{ return fCO2()	/ gammaCO2(); }
	//virtual	double			fCO2()					const;
	//virtual	double			fS2()					const;

	using MeltInclusion::fS2;
};


#endif /* defined(__MeltInclusion__) */
