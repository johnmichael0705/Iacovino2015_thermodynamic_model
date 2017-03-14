//
//  Model.cpp
//  Iacovino
//
//  Created by Roderick Mann on 4/25/15.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#include "Model.h"

//
//	Standard Includes
//

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <vector>

//
//	Project Includes
//


#include "MeltInclusion.h"
#include "SearchMix.h"


//  John's Cerro Negro MI, "deep" region
//	Based on: Basanite
//  Takes inputs: T,P,fH2O,logfO2,XCO2

BasaniteMeltInclusion	CN1_99c_MI1(1170,2400,std::log10(1286.5372),-6.82,0.498);
BasaniteMeltInclusion	CN1_99G_MI1(1170,2400,std::log10(1820.2660),-7.92,0.375);
BasaniteMeltInclusion	CN2_MI99J(1170,2400,std::log10(803.2587),-7.92,0.478);
BasaniteMeltInclusion	CN2_MI99J2(1170,2400,std::log10(1543.1178),-7.92,0.286);
BasaniteMeltInclusion	CN2_MI99N(1170,2400,std::log10(1723.7608),-7.92,0.216);


BasaniteMeltInclusion   CN_deep_average(1170, 2400, 3.139857745, -7.70, 0.371);

MeltInclusion*
sBasaniteInclusions[] =
{
	&CN1_99c_MI1,
	&CN1_99G_MI1,
	&CN2_MI99J,
	&CN2_MI99J2,
	&CN2_MI99N,

};


//  John's Cerro Negro MI, "shallow" region
//  Based on: New "Intermediate Region" Melt inclusions
//  Takes inputs: T,P,fH2O,logfO2,logfS2

MeltInclusion   LP30_MI(1130, 1300, std::log10(477.9442), -6.69, -3.01);
MeltInclusion   LP34_MI(1130, 1300, std::log10(29.4906), -8.17, -3.01);
MeltInclusion   LP51_MI(1130, 1300, std::log10(342.2188), -8.41, -3.01);
MeltInclusion   LP51_MI1B(1130, 1300, std::log10(354.3629), -8.41, -3.01);
MeltInclusion   LP52_MI1(1130, 1300, std::log10(464.2169), -8.41, -3.01);
MeltInclusion   LP53_MI1(1130, 1300, std::log10(396.3056), -8.41, -3.01);
MeltInclusion   LP54_MI1(1130, 1300, std::log10(13.3801), -8.41, -3.01);
MeltInclusion	LP55_MI2(1130, 1300, std::log10(383.8208), -8.41, -3.01);
MeltInclusion	LP55_MI1(1130, 1300, std::log10(180.2752), -8.41, -3.01);
MeltInclusion	LP56_MI1(1130, 1300, std::log10(333.8420), -8.41, -3.01);

MeltInclusion   CN_shallow_avg(1130, 1300, std::log10(297.5857), -8.21, -3.01);


//Values for new "intermediate" region

MeltInclusion*
sTephriphonoliteInclusions[] =
{
	&LP30_MI,
	&LP34_MI,
	&LP51_MI,
	&LP51_MI1B,
	&LP52_MI1,
	&LP53_MI1,
	&LP54_MI1,
	&LP55_MI2,
	&LP55_MI1,
	&LP56_MI1,
};


//  Melt degassing. Subtracting values of melt inclusions to get at gas being released between regions.
BasaniteMeltInclusion		deltaDeepToShallow(CN_deep_average);

void
initModel()
{
	CN_deep_average.calcComposition();
	CN1_99c_MI1.calcComposition();
	CN1_99G_MI1.calcComposition();
	CN2_MI99J.calcComposition();
	CN2_MI99J2.calcComposition();
	CN2_MI99N.calcComposition();
	
	CN_shallow_avg.calcComposition();
	LP30_MI.calcComposition();
	LP34_MI.calcComposition();
	LP51_MI.calcComposition();
	LP51_MI1B.calcComposition();
	LP52_MI1.calcComposition();
	LP53_MI1.calcComposition();
	LP54_MI1.calcComposition();
	LP55_MI2.calcComposition();
	LP55_MI1.calcComposition();
	LP56_MI1.calcComposition();

//  WeightPercents takes three arguments, in wt%: CO2, H2O, S total. These are from the average MI.
	WeightPercents deep(0.079, 3.62, 0.12868);
	WeightPercents shallow(0.068, 1.45, 0.05057);
	
	deltaDeepToShallow.calcDeltaComposition(deep, kBasFrac, shallow);
}

void
model()
{
	double pressure = 1.0;
	
	SearchMix		sm;
	sm.add(CN_deep_average, pressure);
	sm.add(CN_shallow_avg, pressure);
	
	sm.add(deltaDeepToShallow, pressure);
	
	sm.dump();			//	Display values prior to searching for mixing weights
	sm.search();		//	Will dump resulting weights
}
