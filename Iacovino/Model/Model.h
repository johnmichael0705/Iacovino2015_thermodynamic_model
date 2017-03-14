//
//  Model.h
//  Iacovino
//
//  Created by Roderick Mann on 4/25/15.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#ifndef __Iacovino__Model__
#define __Iacovino__Model__

#include "MeltInclusion.h"

void		initModel();
void		model();



extern BasaniteMeltInclusion	CN_deep_average;
extern BasaniteMeltInclusion	CN1_99c_MI1;
extern BasaniteMeltInclusion	CN1_99G_MI1;
extern BasaniteMeltInclusion	CN2_MI99J;
extern BasaniteMeltInclusion	CN2_MI99J2;
extern BasaniteMeltInclusion	CN2_MI99N;

extern MeltInclusion			CN_shallow_avg;
extern MeltInclusion			LP30_MI;
extern MeltInclusion			LP34_MI;
extern MeltInclusion			LP51_MI;
extern MeltInclusion			LP51_MI1B;
extern MeltInclusion			LP52_MI1;
extern MeltInclusion			LP53_MI1;
extern MeltInclusion			LP54_MI1;
extern MeltInclusion			LP55_MI2;
extern MeltInclusion			LP55_MI1;
extern MeltInclusion			LP56_MI1;

extern BasaniteMeltInclusion	deltaDeepToShallow;

#endif /* defined(__Iacovino__Model__) */
