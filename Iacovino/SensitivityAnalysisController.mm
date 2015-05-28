//
//  SensitivityAnalysisController.m
//  Iacovino
//
//  Created by Roderick Mann on 5/24/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import "SensitivityAnalysisController.h"




#import "Model.h"
#import "Region.h"









@interface SensitivityAnalysisController()

@property (nonatomic, strong)	NSArray*					regions;
@property (nonatomic, strong)	Region*						selectedRegion;

@end

@implementation SensitivityAnalysisController

- (void)
viewDidLoad
{
	[super viewDidLoad];
	
	//	Set up the regions…
	
	NSMutableArray* regions = [NSMutableArray new];
	Region* r = nil;
	
	r = [Region regionWithMeltInclusion: &LL_Phon_8 name: @"Lave Lake"];
	[regions addObject: r];
	self.selectedRegion = r;
	
	r = [Region regionWithMeltInclusion: &deltaPhonToLL name: @"Phon to Lava Lake"];
	[regions addObject: r];
	
	r = [Region regionWithMeltInclusion: &EA1_avg name: @"EA1"];
	[regions addObject: r];
	
	r = [Region regionWithMeltInclusion: &deltaTephToPhon name: @"Teph to Phon"];
	[regions addObject: r];
	
	r = [Region regionWithMeltInclusion: &Intermediate_avg name: @"Intermediate"];
	[regions addObject: r];
	
	r = [Region regionWithMeltInclusion: &deltaBasToTeph name: @"Basanite to Teph"];
	[regions addObject: r];
	
	r = [Region regionWithMeltInclusion: &DVDP3_295_average name: @"Basanite DVDP3 295"];
	[regions addObject: r];
	
	self.regions = [regions copy];
}

@end
