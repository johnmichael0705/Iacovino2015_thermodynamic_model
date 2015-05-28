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


//	Basanite,T,P,fH2O,logfO2,XCO2
//  Using Papel modeled pressure esimates

BasaniteMeltInclusion	DVDP3_295a(1100,4879,std::log10(399.1161657),-7.63,0.95);
BasaniteMeltInclusion	DVDP3_295b(1100,4141,std::log10(403.5717232),-7.63,0.89);
BasaniteMeltInclusion	DVDP3_295c(1100,5235,std::log10(314.8036358),-7.63,0.937);
BasaniteMeltInclusion	DVDP3_295d(1100,4453,std::log10(403.5717232),-7.63,0.915);
BasaniteMeltInclusion	DVDP3_295g(1100,5151,std::log10(440.0314516),-7.63,0.925);
BasaniteMeltInclusion	DVDP3_295i(1100,4510,std::log10(254.0161678),-7.63,0.95);
BasaniteMeltInclusion	DVDP3_295j(1100,4273,std::log10(239.7579362),-7.63,0.94);
BasaniteMeltInclusion	DVDP3_295l(1100,4379,std::log10(360.040825),-7.63,0.917);
BasaniteMeltInclusion	DVDP3_295q(1100,4665,std::log10(236.2525171),-7.63,0.95);
BasaniteMeltInclusion	DVDP3_295r(1100,5125,std::log10(287.4735304),-7.63,0.95);

BasaniteMeltInclusion   DVDP3_295_average(1100, 4445, 2.52356903, -7.63, 0.9299);

MeltInclusion*
sBasaniteInclusions[] =
{
	&DVDP3_295a,
	&DVDP3_295b,
	&DVDP3_295c,
	&DVDP3_295d,
	&DVDP3_295g,
	&DVDP3_295i,
	&DVDP3_295j,
	&DVDP3_295l,
	&DVDP3_295q,
	&DVDP3_295r,
};


//  New "Intermediate Region" Melt inclusions (T,P,fH2O,logfO2,logfS2)

MeltInclusion   tp97009b(1081, 4460, std::log10(50.46), -9.99, -3.01);
MeltInclusion   tp97009d(1081, 3938, std::log10(29.81), -9.99, -3.01);
MeltInclusion   tp97009e(1081, 4005, std::log10(30.08), -9.99, -3.01);
MeltInclusion   tp97009g(1081, 4271, std::log10(40.56), -9.99, -3.01);
MeltInclusion   tp97010b(1081, 4757, std::log10(3.12), -9.99, -3.01);
MeltInclusion   tp97010d(1081, 3115, std::log10(3.30), -9.99, -3.01);
MeltInclusion   tp97011a(1081, 3521, std::log10(3.25), -9.99, -3.01);
MeltInclusion	aw82033c(1081, 2485, std::log10(2.84), -9.99, -3.01);
MeltInclusion	aw82033e(1081, 2532, std::log10(7.46), -9.99, -3.01);
MeltInclusion	aw82033i(1081, 2739, std::log10(3.02), -9.99, -3.01);

MeltInclusion   Intermediate_avg(1081, 3582, std::log10(17.39), -9.99, -3.01);


#if 0
//	Original Tephriphonolite 97009 values,T,P,fH2O,logfO2,logfS2

MeltInclusion	tp97009a(1081,3000,std::log10(58.97683095),-9.99,-3.01);
MeltInclusion	tp97009b(1081,3000,std::log10(57.14242454),-9.99,-3.01);
MeltInclusion	tp97009c(1081,3000,std::log10(53.55359992),-9.99,-3.01);
MeltInclusion	tp97009d(1081,3000,std::log10(35.74647257),-9.99,-3.01);
MeltInclusion	tp97009e(1081,3000,std::log10(38.73837574),-9.99,-3.01);
MeltInclusion	tp97009f(1081,3000,std::log10(46.69792389),-9.99,-3.01);
MeltInclusion	tp97009g(1081,3000,std::log10(46.69792389),-9.99,-3.01);
MeltInclusion	tp97009h(1081,3000,std::log10(34.29200101),-9.99,-3.01);
MeltInclusion	tp97009i(1081,3000,std::log10(41.84028969),-9.99,-3.01);
MeltInclusion	tp97009j(1081,3000,std::log10(70.53892478),-9.99,-3.01);

MeltInclusion	Teph_avg(1081, 3000, std::log(48.6133333), -9.99, -3.01);

//Original values for Tephriphonolite 97009 values

MeltInclusion*
sTephriphonoliteInclusions[] =
{
	&tp97009a,
	&tp97009b,
	&tp97009c,
	&tp97009d,
	&tp97009e,
	&tp97009f,
	&tp97009g,
	&tp97009h,
	&tp97009i,
	&tp97009j,
};

#endif


//Values for new "intermediate" region

MeltInclusion*
sTephriphonoliteInclusions[] =
{
	&tp97009b,
	&tp97009d,
	&tp97009e,
	&tp97009g,
	&tp97010b,
	&tp97010d,
	&tp97011a,
	&aw82033c,
	&aw82033e,
	&aw82033i,
};

//	Phonolite,T,P,fH2O,logfO2,logfS2

MeltInclusion	EA1_a(1000,2534,std::log10(3.65685507),-11.26,-2.7);
MeltInclusion	EA1_b(1000,2793,std::log10(4.222179382),-11.26,-2.7);
MeltInclusion	EA1_d(1000,2686,std::log10(3.839505618),-11.26,-2.7);
MeltInclusion	EA1_e(1000,2062,std::log10(4.442576661),-11.26,-2.7);
MeltInclusion	EA1_f(1000,2626,std::log10(5.347242686),-11.26,-2.7);
MeltInclusion	EA1_g(1000,2775,std::log10(3.363264424),-11.26,-2.7);
MeltInclusion	EA1_h(1000,2938,std::log10(4.610652035),-11.26,-2.7);
MeltInclusion	EA1_i(1000,2851,std::log10(3.415961461),-11.26,-2.7);
MeltInclusion	EA1_j(1000,2998,std::log10(3.03449156),-11.26,-2.7);
MeltInclusion	EA1_k(1000,2450,std::log10(4.479080008),-11.26,-2.7);

MeltInclusion   EA1_avg(1000, 2671.3, 0.60650829, -11.26, -2.7);

MeltInclusion*
sPhonoliteInclusions[] =
{
	&EA1_a,
	&EA1_b,
	&EA1_d,
	&EA1_e,
	&EA1_f,
	&EA1_g,
	&EA1_h,
	&EA1_i,
	&EA1_j,
	&EA1_k,
};

MeltInclusion	LL_Phon_8(1000, 4.321, std::log10(1.631390134), -12.2, -2.7);

BasaniteMeltInclusion		deltaBasToTeph(DVDP3_295_average);
MeltInclusion				deltaTephToPhon(Intermediate_avg);
MeltInclusion				deltaPhonToLL(EA1_avg);

void
initModel()
{
	DVDP3_295_average.calcComposition();
	DVDP3_295a.calcComposition();
	DVDP3_295b.calcComposition();
	DVDP3_295c.calcComposition();
	DVDP3_295d.calcComposition();
	DVDP3_295g.calcComposition();
	DVDP3_295i.calcComposition();
	DVDP3_295j.calcComposition();
	DVDP3_295l.calcComposition();
	DVDP3_295q.calcComposition();
	DVDP3_295r.calcComposition();
	
	Intermediate_avg.calcComposition();
	tp97009b.calcComposition();
	tp97009d.calcComposition();
	tp97009e.calcComposition();
	tp97009g.calcComposition();
	tp97010b.calcComposition();
	tp97010d.calcComposition();
	tp97011a.calcComposition();
	aw82033c.calcComposition();
	aw82033e.calcComposition();
	aw82033i.calcComposition();

	EA1_avg.calcComposition();
	EA1_a.calcComposition();
	EA1_b.calcComposition();
	EA1_d.calcComposition();
	EA1_e.calcComposition();
	EA1_f.calcComposition();
	EA1_g.calcComposition();
	EA1_h.calcComposition();
	EA1_i.calcComposition();
	EA1_j.calcComposition();
	EA1_k.calcComposition();

	LL_Phon_8.calcComposition();
	
	WeightPercents bas(0.5537, 1.498, 0.067);
    //WeightPercents teph(0.2242, 0.527, 0.0662); //comp(CO2, H2O, S) values in wt% - Original 97009 values
	WeightPercents teph(0.1513,0.2575,0.0998);
	WeightPercents phon(0.0691, 0.167, 0.03805);
	WeightPercents ll(0.03, 0.11, 0.0);
	
	deltaBasToTeph.calcDeltaComposition(bas, kBasFrac, teph);
	deltaTephToPhon.calcDeltaComposition(teph, kTephFrac, phon);
	deltaPhonToLL.calcDeltaComposition(phon, kPhonFrac, ll);
}

void
model()
{
	double pressure = 1.0;
	
	SearchMix		sm;
	sm.add(DVDP3_295_average, pressure);
	sm.add(Intermediate_avg, pressure);
	sm.add(EA1_avg, pressure);
	sm.add(LL_Phon_8, pressure);
	
	sm.add(deltaBasToTeph, pressure);
	sm.add(deltaTephToPhon, pressure);
	sm.add(deltaPhonToLL, pressure);
	
	sm.dump();			//	Display values prior to searching for mixing weights
	sm.search();		//	Will dump resulting weights
}
