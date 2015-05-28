//
//  FugacityCalculator.m
//  Iacovino
//
//  Created by Roderick Mann on 5/9/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import "FugacityCalculator.h"



#import "RedlichKwong.h"


@interface FugacityCalculator ()

@property (nonatomic, assign)	double			criticalTemp;
@property (nonatomic, assign)	double			criticalPressure;
@property (nonatomic, assign)	double			acentricFactor;

@property (nonatomic, assign)	double			temperature;
@property (nonatomic, assign)	double			pressure;

@property (nonatomic, assign, readonly)	double	fugacityCoeff;

@end




@implementation FugacityCalculator

- (void)
viewDidLoad
{
	[super viewDidLoad];
	
	self.criticalTemp = 647.3;
	self.criticalPressure = 221.2;
	self.acentricFactor = 0.344;
	
	self.temperature = 1273.15;
	self.pressure = 2500;
}

- (double)
fugacityCoeff
{
	CriticalParameters cp;
	cp.mTc = self.criticalTemp;
	cp.mPc = self.criticalPressure;
	cp.mW = self.acentricFactor;
	
	double fc;
	redlichKwong(cp, self.temperature, self.pressure, NULL, NULL, &fc, NULL, NULL);
	return fc;
}

+ (NSSet*)
keyPathsForValuesAffectingFugacityCoeff
{
	return [NSSet setWithObjects: @"criticalTemp", @"criticalPressure", @"acentricFactor", @"temperature", @"pressure", nil];
}


@end
