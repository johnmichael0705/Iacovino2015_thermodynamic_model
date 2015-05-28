/**
	EquilibriumConstantOfFormation.cpp

	Created by Roderick Mann on 4/25/15.
*/

#include "EquilibriumConstantOfFormation.h"

#include <cmath>

/**
	From Robie and Hemingway (1995). Text table
	was fit with sixth-order polynomial to arrive
	at the following coefficients.
	
	H2 + 1/2O2 = H2O
*/

double
logKFH2O(double inT)
{
	double t2 = inT * inT;
	double t3 = inT * inT * inT;
	double t4 = inT * inT * inT * inT;
	double t5 = inT * inT * inT * inT * inT;
	double t6 = inT * inT * inT * inT * inT * inT;
	double logK =		 3.34263E-17 * t6
					+	-2.40813E-13 * t5
					+	 7.10612E-10 * t4
					+	-1.10671E-06 * t3
					+	 9.76038E-04 * t2
					+	-4.84445E-01 * inT
					+	 1.21953E+02;
	
	return logK;
}

/**
	From Robie and Hemingway (1995). Text table
	was fit with sixth-order polynomial to arrive
	at the following coefficients.
	
	H2 + 1/2S2 = H2S
*/

double
logKFH2S(double inT)
{
	double t2 = inT * inT;
	double t3 = inT * inT * inT;
	double t4 = inT * inT * inT * inT;
	double t5 = inT * inT * inT * inT * inT;
	double t6 = inT * inT * inT * inT * inT * inT;
	double logK =		 1.882737E-18 * t6
					+	-1.779266E-14 * t5
					+	 6.319209E-11 * t4
					+	-1.092048E-07 * t3
					+	 9.824774E-05 * t2
					+	-4.805344E-02 * inT
					+	 1.389857E+01;
	
	return logK;
}

/**
	From Robie and Hemingway (1995). Text table
	was fit with sixth-order polynomial to arrive
	at the following coefficients.
	
	S2 + 1/2O2 = SO2
*/

double
logKFSO2(double inT)
{
	double t2 = inT * inT;
	double t3 = inT * inT * inT;
	double t4 = inT * inT * inT * inT;
	double t5 = inT * inT * inT * inT * inT;
	double t6 = inT * inT * inT * inT * inT * inT;
	double logK =		 4.01465E-17 * t6
					+	-2.93845E-13 * t5
					+	 8.78818E-10 * t4
					+	-1.38066E-06 * t3
					+	 1.21978E-03 * t2
					+	-6.03476E-01 * inT
					+	 1.54350E+02;
	
	return logK;
}

/**
	From Wagman et al (1945). Text table
	was fit with sixth-order polynomial to arrive
	at the following coefficients.
	
	CO + 1/2O2 = CO2
*/

double
logKFCO2(double inT)
{
	double t2 = inT * inT;
	double t3 = inT * inT * inT;
	double t4 = inT * inT * inT * inT;
	double t5 = inT * inT * inT * inT * inT;
	double t6 = inT * inT * inT * inT * inT * inT;
	double logK =		 9.11899E-17 * t6
					+	-5.65762E-13 * t5
					+	 1.44706E-09 * t4
					+	-1.96925E-06 * t3
					+	 1.53277E-03 * t2
					+	-6.79138E-01 * inT
					+	 1.53288E+02;
	
	return logK;
}


