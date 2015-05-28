//
//  HistogramView.h
//  Iacovino
//
//  Created by Roderick Mann on 5/15/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import <CorePlot/CorePlot.h>


#import "Histogram.h"


@interface HistogramView : NSView

@property (nonatomic, assign)		Histogram					histogram;
@property (nonatomic, copy)			NSString*					title;

@end
