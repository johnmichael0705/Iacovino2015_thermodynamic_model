//
//  Region.h
//  Iacovino
//
//  Created by Roderick Mann on 5/24/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import <Foundation/Foundation.h>


class MeltInclusion;


@interface Region : NSObject

+ (instancetype)			regionWithMeltInclusion: (MeltInclusion*) inMelt
								name: (NSString*) inName;

@end


