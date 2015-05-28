/**
	RedlichKwong.cpp

	Created by Roderick Mann on 4/25/15.
	
	Derived from:	http://people.ds.cam.ac.uk/pjb10/thermo/pure.html
					Patrick J. Barrie 30 October 2003
	
	C++11
*/


#include "RedlichKwong.h"


#include <cmath>

void		solveCubic(double inC0, double inC1, double inC2,
						double* outZ0, double* outZ1, double* outZ2, double* outD);
void		calcDepartureFunctions(double inT,
						double inA, double inB, double inKappa, double inZ,
						double* outPhi, double* outHdep, double* outSdep);



const double kR			=	8.3145;

void
redlichKwong(	const CriticalParameters& inCP,

				double inT,			//	Temperature (K)
				double inP,			//	Pressure (bar)

				double* outZ,		//	Compressibility Factor
				//double* outState,
				double* outVol,		//	Molar volume (m^3/mol)
				double* outPhi,		//	Fugacity coefficient
				double* outHdep,	//	Enthalpy departure function
				double* outSdep)	//	Entropy departure function
{
	//	Calculate a and b parameters (depend only on critical parameters)…
	
	double a = 0.42748 * kR * kR * std::pow(inCP.mTc, 2.5) / (inCP.mPc * 1.0e5);
	double b = 0.08664 * kR * inCP.mTc / (inCP.mPc * 1.0e5);
	double kappa = 0.0;
	
	//	Calculate coefficients in the cubic equation of state…
	//
	//	coeffs: (C0,C1,C2,A,B);
	
	double A = a * inP * 1.0e5/ (std::sqrt(inT) * std::pow(kR * inT, 2));
	double B = b * inP * 1e5 / (kR * inT);
	double C2 = -1.0;
	double C1 = A - B - B * B;
	double C0 = -A * B;
	
	//	Solve the cubic equation for Z0 - Z2, D…
	
	double Z0;
	double Z1;
	double Z2;
	double D;
	solveCubic(C0, C1, C2, &Z0, &Z1, &Z2, &D);
	
	//	Determine the fugacity coefficient of first root and departure functions…
	//
	//	calcdepfns(coeffs[3],	coeffs[4],	paramsab[0],	Z[0]);
	//	calcdepfns(A,			B,			kappa,			Z)
	
	calcDepartureFunctions(inT, A, B, kappa, Z0, outPhi, outHdep, outSdep);
}

void
calcDepartureFunctions(double inT,
						double inA, double inB, double inKappa, double inZ,
						double* outPhi, double* outHdep, double* outSdep)
{
	if (outPhi != NULL)
	{
		double phi = std::exp(inZ - 1 - std::log(inZ - inB) - inA * std::log(1 + inB / inZ) / inB);
		*outPhi = phi;
	}
	
	if (outHdep != NULL)
	{
		double Hdep = kR * inT * (inZ - 1 - 1.5 * inA * std::log(1 + inB / inZ) / inB);
		*outHdep = Hdep;
	}
	
	if (outSdep != NULL)
	{
		double Sdep = kR * (std::log(inZ - inB) - 0.5 * inA * std::log(1 + inB / inZ) / inB);
		*outSdep = Sdep;
	}
}

void
solveCubic(double inC0, double inC1, double inC2,
			double* outZ0, double* outZ1, double* outZ2, double* outD)
{
	double Q1 = inC2 * inC1 / 6 - inC0 / 2 - inC2 * inC2 * inC2 / 27;
	double P1 = inC2 * inC2 / 9 - inC1 / 3;
	double D = Q1 * Q1 - P1 * P1 * P1;
	if (outD != NULL) *outD = D;
	
	if (D >= 0)
	{
		if (outZ0 != NULL)		//	Skip all this work if the caller doesn't want it
		{
			const double kOneThird = 1.0 / 3.0;
			
			const double sqrtD = std::sqrt(D);
			
			const double absQ1PSqrtD = std::abs(Q1 + sqrtD);
			double temp1 = std::pow(absQ1PSqrtD, kOneThird);
			temp1 *= (Q1 + sqrtD) / absQ1PSqrtD;
			
			const double absQ1MSqrtD = std::abs(Q1 - sqrtD);
			double temp2 = std::pow(absQ1MSqrtD, kOneThird);
			temp2 *= (Q1 - sqrtD) / absQ1MSqrtD;
			
			double Z0 = temp1 + temp2 - inC2 / 3;
			*outZ0 = Z0;
		}
	}
	else
	{
		double temp1 = Q1 * Q1 /(P1 * P1 * P1);
		double temp2 = std::sqrt(1.0 - temp1) / std::sqrt(temp1);
		temp2 *= Q1 / std::abs(Q1);
		
		double phi = std::atan(temp2);
		if (phi < 0)
		{
			phi = phi + M_PI;
		}
		
		const double sqrtP1 = std::sqrt(P1);
		double Z0 = 2 * sqrtP1 * std::cos(phi / 3) - inC2 / 3;
		double Z1 = 2 * sqrtP1 * std::cos((phi + 2 * M_PI) / 3) - inC2 / 3;
		double Z2 = 2 * sqrtP1 * std::cos((phi + 4 * M_PI) / 3) - inC2 / 3;
		
		double temp;
		if (Z0 < Z1)
		{
			temp = Z0; Z0 = Z1; Z1 = temp;
		}
		
		if (Z1 < Z2)
		{
			temp = Z1; Z1 = Z2; Z2 = temp;
		}
		
		if (Z0 < Z1)
		{
			temp = Z0; Z0 = Z1; Z1 = temp;
		}
		
		if (outZ0 != NULL)	*outZ0 = Z0;
		if (outZ1 != NULL)	*outZ1 = Z1;
		if (outZ2 != NULL)	*outZ2 = Z2;
	}
}
