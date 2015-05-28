//
//  Region.m
//  Iacovino
//
//  Created by Roderick Mann on 5/24/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import "Region.h"


#import "MeltInclusion.h"





@interface Region()

@property (nonatomic, copy)		NSString*						name;
@property (nonatomic, assign)	double							temperature;
@property (nonatomic, assign)	double							sigmaTemperature;
@property (nonatomic, assign)	double							pressure;
@property (nonatomic, assign)	double							sigmaPressure;
@property (nonatomic, assign)	double							fH2O;
@property (nonatomic, assign)	double							sigmaFH2O;
@property (nonatomic, assign)	double							fO2;
@property (nonatomic, assign)	double							sigmaFO2;
@property (nonatomic, assign)	double							fS2OrXCO2;
@property (nonatomic, assign)	double							sigmaFS2OrXCO2;
@property (nonatomic, copy)		NSString*						fS2OrXCO2Label;

@end





@implementation Region

+ (instancetype)
regionWithMeltInclusion: (MeltInclusion*) inMelt
	name: (NSString*) inName;
{
	Region* r = [Region new];
	
	r.name = inName;
	r.temperature = inMelt->tC();
	r.pressure = inMelt->p();
	r.fH2O = inMelt->logFH2O();
	r.fO2 = inMelt->logFO2();
	r.fS2OrXCO2 = inMelt->logFS2OrXCO2();
	
	//	This is a bit hacky, but whatever…
	
	BasaniteMeltInclusion* b = dynamic_cast<BasaniteMeltInclusion*> (inMelt);
	if (b != nullptr)
	{
		r.fS2OrXCO2Label = @"XCO2";
	}
	else
	{
		r.fS2OrXCO2Label = @"S2";
	}
	
	return r;
}


@end
