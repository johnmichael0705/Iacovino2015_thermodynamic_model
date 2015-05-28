/**
	RedlichKwong.h

	Created by Roderick Mann on 4/25/15.
	
	Derived from:	http://people.ds.cam.ac.uk/pjb10/thermo/pure.html
					Patrick J. Barrie 30 October 2003
	
	C++11
*/

#ifndef __RedlichKwong__
#define __RedlichKwong__



struct
CriticalParameters
{
	double mTc;		//	Critical temperature (K)
	double mPc;		//	Critical pressure (bar)
	double mW;		//	Acentric factor
};

void
redlichKwong(	const CriticalParameters& inCP,

				double inT,			//	Temperature (K)
				double inP,			//	Pressure (bar)

				double* outZ,		//	Compressibility Factor
				//double* outState,
				double* outVol,		//	Molar volume (m^3/mol)
				double* outPhi,		//	Fugacity coefficient
				double* outHdep,	//	Enthalpy departure function
				double* outSdep);	//	Entropy departure function






#endif /* defined(__RedlichKwong__) */
