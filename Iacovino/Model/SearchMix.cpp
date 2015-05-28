//
//  SearchMix.cpp
//  Iacovino
//
//  Created by Roderick Mann on 5/5/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#include "SearchMix.h"

#include <cstdio>
#include <dispatch/dispatch.h>

#include "MeltInclusion.h"



const double kMultiplier = 100.0;


void
SearchMix::add(const MeltInclusion& inMelt, double inPressure)
{
	double co, co2, h2o, h2s, so2;
	inMelt.depressurize(inPressure, co, co2, h2o, h2s, so2);
	add(co, co2, h2o, h2s, so2);
}

void
SearchMix::add(double inCO, double inCO2, double inH2O, double inH2S, double inSO2)
{
	mCOVals.push_back(inCO);
	mCO2Vals.push_back(inCO2);
	mH2OVals.push_back(inH2O);
	mH2SVals.push_back(inH2S);
	mSO2Vals.push_back(inSO2);
}


#if 1
double surfaceCO[3] = {0.0238, 0.0, 0.0};
double surfaceCO2[3] = {0.3713, 0.0, 0.0};
double surfaceH2O[3] = {0.5903, 0.0, 0.0};
double surfaceH2S[3] = {0.0003, 0.0, 0.0};
double surfaceSO2[3] = {0.0143, 0.0, 0.0};
#else
double surfaceCO2[3] = {38.04, 0.0, 0.0};
double surfaceH2O[3] = {60.47, 0.0, 0.0};
double surfaceH2S[3] = {0.03, 0.0, 0.0};
double surfaceSO2[3] = {1.46, 0.0, 0.0};
#endif

void
SearchMix::search()
{
	const double error = 0.2;
	
	surfaceCO[0] *= kMultiplier;
	surfaceCO2[0] *= kMultiplier;
	surfaceH2O[0] *= kMultiplier;
	surfaceH2S[0] *= kMultiplier;
	surfaceSO2[0] *= kMultiplier;
	
	surfaceCO[1] =  std::max(0.0, surfaceCO[0] - error);	surfaceCO[2] = surfaceCO[0] + error;
	surfaceCO2[1] = std::max(0.0, surfaceCO2[0] - error);	surfaceCO2[2] = surfaceCO2[0] + error;
	surfaceH2O[1] = std::max(0.0, surfaceH2O[0] - error);	surfaceH2O[2] = surfaceH2O[0] + error;
	surfaceH2S[1] = std::max(0.0, surfaceH2S[0] - error);	surfaceH2S[2] = surfaceH2S[0] + error;
	surfaceSO2[1] = std::max(0.0, surfaceSO2[0] - error);	surfaceSO2[2] = surfaceSO2[0] + error;
	
	std::printf("Surface gasses:\n");
	double* p;
	p = surfaceCO;  std::printf("CO:     %6.2f     %6.2f     %6.2f\n", p[0], p[1], p[2]);
	p = surfaceCO2; std::printf("CO2:    %6.2f     %6.2f     %6.2f\n", p[0], p[1], p[2]);
	p = surfaceH2O; std::printf("H2O:    %6.2f     %6.2f     %6.2f\n", p[0], p[1], p[2]);
	p = surfaceH2S; std::printf("H2S:    %6.2f     %6.2f     %6.2f\n", p[0], p[1], p[2]);
	p = surfaceSO2; std::printf("SO2:    %6.2f     %6.2f     %6.2f\n", p[0], p[1], p[2]);
	
	FILE *ofp = stdout;
	
	fprintf(ofp,"\n\nBas   Teph  Phon    LL  B->T  T->P  P->L           %10.10s    %10.10s    %10.10s    %10.10s    %10.10s\n",
													"CO", "CO2", "H2O", "H2S", "SO2");
	fprintf(ofp,"----  ----  ----  ----  ----  ----  ----           %10.10s    %10.10s    %10.10s    %10.10s    %10.10s\n",
													"--", "---", "---", "---", "---");
	//Generates a list of one-dimensional arrays, each array 7 values long, where the sum of each array is 100
	//for (int a=0;a<100;a++)
	::dispatch_apply(100, ::dispatch_get_global_queue(QOS_CLASS_USER_INTERACTIVE, 0),
	^(size_t inA)
	{
		int a = (int) inA;
		//printf("a: %d\n", a);
		for (int b=100-a; b>-1; b--)
		{
			for (int c=100-a-b; c>-1; c--)
			{
				for (int d=100-a-b-c; d>-1; d--)
				{
					for (int e=100-a-b-c-d; e>-1; e--)
					{
						for (int f=100-a-b-c-d-e; f>-1; f--)
						{
							for (int g=100-a-b-c-d-e-f; g>-1; g--)
							{
								int sum = a+b+c+d+e+f+g;
								if (sum != 100)
								{
									continue;
								}
								
								//If G - 1 >= the sum of the proportioned fluid contributions >= G+1, exclude that array from the final list. G = measured surface gas value of each species.
								
#if 1
								double co = getVals(a,b,c,d,e,f,g, mCOVals);
								if ((co < surfaceCO[1]) || (co >surfaceCO[2]))
								{
									continue;
								}
#endif
								double co2 = getVals(a,b,c,d,e,f,g, mCO2Vals);
								if ((co2 < surfaceCO2[1]) || (co2 >surfaceCO2[2]))
								{
									continue;
								}

								double h2o = getVals(a,b,c,d,e,f,g, mH2OVals);
								if ((h2o < surfaceH2O[1]) || (h2o >surfaceH2O[2]))
								{
									continue;
								}

								double h2s = getVals(a,b,c,d,e,f,g, mH2SVals);
								if ((h2s < surfaceH2S[1]) || (h2s >surfaceH2S[2]))
								{
									continue;
								}

								double so2 = getVals(a,b,c,d,e,f,g, mSO2Vals);
								if ((so2 < surfaceSO2[1]) || (so2 >surfaceSO2[2]))
								{
									continue;
								}
								//Prints all arrays where G - 1 <= sum of the proportioned fluid contributions <= G + 1 is true for all gas species. Output is saved to four files: one file for each forked process.
								fprintf(ofp,"%4d  %4d  %4d  %4d  %4d  %4d  %4d  = %4d - %10.7f    %10.7f    %10.7f    %10.7f    %10.7f\n",a,b,c,d,e,f,g, sum, co, co2, h2o, h2s, so2);
							}
						}
					}
				}
			}
		}
	});
	
}


void
SearchMix::dump() const
{
	std::printf("      %15.15s  %15.15s  %15.15s  %15.15s  %15.15s  %15.15s  %15.15s\n",
						"Bas", "Teph", "Phon", "LL", "Bas->Teph", "Teph->Phon", "Phon->LL");
	std::printf("      %15.15s  %15.15s  %15.15s  %15.15s  %15.15s  %15.15s  %15.15s\n",
						"---------------", "---------------", "---------------", "---------------", "---------------", "---------------", "---------------");
	std::printf("CO:   ");	dumpLine(mCOVals);		std::printf("\n");
	std::printf("CO2:  ");	dumpLine(mCO2Vals);		std::printf("\n");
	std::printf("H2O:  ");	dumpLine(mH2OVals);		std::printf("\n");
	std::printf("H2S:  ");	dumpLine(mH2SVals);		std::printf("\n");
	std::printf("SO2:  ");	dumpLine(mSO2Vals);		std::printf("\n");
	
	std::printf("      %15.15s  %15.15s  %15.15s  %15.15s  %15.15s  %15.15s  %15.15s\n",
						"---------------", "---------------", "---------------", "---------------", "---------------", "---------------", "---------------");
	
	std::vector<MixValT>	sums;
	for (int i = 0; i < mCOVals.size(); ++i)
	{
		MixValT sum = mCOVals[i] + mCO2Vals[i] + mH2OVals[i] + mH2SVals[i] + mSO2Vals[i];
		sums.push_back(sum);
	}
	std::printf("Sum:  ");	dumpLine(sums);		std::printf("\n");
	std::printf("\n\n");
}

void
SearchMix::dumpLine(const std::vector<MixValT>& inV) const
{
	for (int i = 0; i < inV.size(); ++i)
	{
		std::printf("%15.5g  ", inV[i]);
	}
}
