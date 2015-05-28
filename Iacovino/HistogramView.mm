//
//  HistogramView.m
//  Iacovino
//
//  Created by Roderick Mann on 5/15/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import "HistogramView.h"

//
//	Library Imports
//

#import <CorePlot/CorePlot.h>


//
//	Project Imports
//

#import "Histogram.h"



@interface ScrollLockPlotSpace : CPTXYPlotSpace
{
}

@end

@implementation ScrollLockPlotSpace

@end



@interface HistogramView()<CPTPlotDataSource, CPTPlotSpaceDelegate>

@property (nonatomic, weak)		IBOutlet CPTGraphHostingView*	graphView;

@property (nonatomic, strong)	CPTXYGraph*						graph;
@property (nonatomic, weak)		CPTTextLayer*					params;

@end





@implementation HistogramView

- (void)
awakeFromNib
{
	[super awakeFromNib];
	
	//	If there’s no graph hosting view provided by IB, make one…
	
	if (self.graphView == nil)
	{
		CPTGraphHostingView* gv = [[CPTGraphHostingView alloc] initWithFrame: self.bounds];
		[self addSubview: gv positioned: NSWindowAbove relativeTo: nil];
		self.graphView = gv;
		
		//	Constraints to fill this view…
		
		NSDictionary* views = @{ @"gv" : gv };
		[self addConstraints: [NSLayoutConstraint constraintsWithVisualFormat: @"H:|[gv]|" options: 0 metrics: nil views: views]];
		[self addConstraints: [NSLayoutConstraint constraintsWithVisualFormat: @"V:|[gv]|" options: 0 metrics: nil views: views]];
	}
	
	CPTXYGraph* graph = [[CPTXYGraph alloc] initWithFrame: self.bounds];
	graph.fill                = [CPTFill fillWithColor: [CPTColor colorWithGenericGray: 0.95]];
	graph.cornerRadius        = 4.0;
	self.graphView.hostedGraph = graph;
	
	self.graph = graph;
	
	//self.mean.stringValue = @"Mean";
	//self.stdDev.stringValue = @"sigma";
	
	// Plot area
	
	graph.plotAreaFrame.fill          = [CPTFill fillWithColor: [CPTColor clearColor]];
	graph.plotAreaFrame.paddingTop    = 4.0;
	graph.plotAreaFrame.paddingBottom = 30.0;
	graph.plotAreaFrame.paddingLeft   = 50.0;
	graph.plotAreaFrame.paddingRight  = 4.0;
	graph.plotAreaFrame.cornerRadius  = 4.0;
	graph.plotAreaFrame.masksToBorder = NO;

	graph.plotAreaFrame.axisSet.borderLineStyle = [CPTLineStyle lineStyle];

	graph.plotAreaFrame.plotArea.fill = [CPTFill fillWithColor:[CPTColor whiteColor]];

	// Setup plot space
	CPTXYPlotSpace *plotSpace = (CPTXYPlotSpace *)graph.defaultPlotSpace;
	plotSpace.delegate = self;
	plotSpace.allowsUserInteraction = true;
	
	plotSpace.xRange     = [CPTPlotRange plotRangeWithLocation: @(0.0) length: @(100.0)];
	plotSpace.yRange     = [CPTPlotRange plotRangeWithLocation: @(0.0) length: @(100)];

	// Line styles
	CPTMutableLineStyle *axisLineStyle = [CPTMutableLineStyle lineStyle];
	axisLineStyle.lineWidth = 1.0;

	CPTMutableLineStyle *majorGridLineStyle = [CPTMutableLineStyle lineStyle];
	majorGridLineStyle.lineWidth = 0.75;
	majorGridLineStyle.lineColor = [CPTColor redColor];

	CPTMutableLineStyle *minorGridLineStyle = [CPTMutableLineStyle lineStyle];
	minorGridLineStyle.lineWidth = 0.25;
	minorGridLineStyle.lineColor = [CPTColor blueColor];

	// Text styles
	CPTMutableTextStyle *axisTitleTextStyle = [CPTMutableTextStyle textStyle];
	axisTitleTextStyle.fontName = @"Helvetica Neue Bold";
	axisTitleTextStyle.fontSize = 14.0;

	//	Axes
	
	CPTXYAxisSet *axisSet = (CPTXYAxisSet *)graph.axisSet;
	CPTXYAxis *x          = axisSet.xAxis;
	x.separateLayers				= NO;
	x.orthogonalPosition			= @(0.0);
	x.majorIntervalLength			= @(0.5);
	x.minorTicksPerInterval			= 4;
	x.tickDirection					= CPTSignNegative;
	x.axisLineStyle					= axisLineStyle;
	x.majorTickLength				= 12.0;
	x.majorTickLineStyle			= axisLineStyle;
	x.minorTickLength				= 8.0;
	x.title							= self.title;
	x.titleTextStyle				= axisTitleTextStyle;
	x.titleOffset					= 25.0;
	//x.alternatingBandFills        = @[[[CPTColor redColor] colorWithAlphaComponent:0.1], [[CPTColor greenColor] colorWithAlphaComponent:0.1]];
	x.labelingPolicy				= CPTAxisLabelingPolicyAutomatic;

	NSNumberFormatter* nf = [[NSNumberFormatter alloc] init];
	nf.numberStyle = NSNumberFormatterScientificStyle;
	nf.usesSignificantDigits = true;
	nf.minimumSignificantDigits = 2;
	nf.maximumSignificantDigits = 2;
	x.labelFormatter = nf;
	
	//	Label y with an automatic label policy…

	CPTXYAxis *y = axisSet.yAxis;
	y.separateLayers        = YES;
	y.orthogonalPosition	= plotSpace.xRange.location;
	y.minorTicksPerInterval = 1;
	y.tickDirection         = CPTSignNegative;
	y.axisLineStyle         = axisLineStyle;
	y.majorTickLength       = 12.0;
	y.majorTickLineStyle    = axisLineStyle;
	y.minorTickLength       = 8.0;
	//y.title                 = @"Number of Samples";
	y.titleTextStyle        = axisTitleTextStyle;
	y.titleOffset           = 40.0;
	//y.alternatingBandFills  = @[[[CPTColor blueColor] colorWithAlphaComponent:0.1], [NSNull null]];
	y.labelingPolicy        = CPTAxisLabelingPolicyAutomatic;
	
	nf = [[NSNumberFormatter alloc] init];
	nf.numberStyle = NSNumberFormatterDecimalStyle;
	nf.minimumFractionDigits = 0;
	nf.maximumFractionDigits = 0;
	y.labelFormatter = nf;

	//CPTFill *bandFill = [CPTFill fillWithColor:[[CPTColor darkGrayColor] colorWithAlphaComponent:0.5]];
	//[y addBackgroundLimitBand:[CPTLimitBand limitBandWithRange:[CPTPlotRange plotRangeWithLocation:CPTDecimalFromDouble(7.0) length:CPTDecimalFromDouble(1.5)] fill:bandFill]];
	//[y addBackgroundLimitBand:[CPTLimitBand limitBandWithRange:[CPTPlotRange plotRangeWithLocation:CPTDecimalFromDouble(1.5) length:CPTDecimalFromDouble(3.0)] fill:bandFill]];
	
	
	//	Set up the bar plot…
	
    CPTBarPlot *barPlot               = [[CPTBarPlot alloc] init];
	
	CPTMutableLineStyle *barLineStyle = [[CPTMutableLineStyle alloc] init];
    barLineStyle.lineWidth = CPTFloat(1.0);
    barLineStyle.lineColor = [CPTColor blackColor];
    //barPlot.lineStyle         = barLineStyle;
	
	barPlot.dataSource		=	self;
	
	barPlot.barsAreHorizontal = false;
	barPlot.barWidth		=	@(10);
	barPlot.barWidthsAreInViewCoordinates = false;
	barPlot.barBasesVary	=	false;
	barPlot.baseValue		=	@(0.0);
	barPlot.barOffset		=	@(0.0);
	barPlot.identifier		=	@"Bar Plot";
	//barPlot.plotRange		=	[CPTPlotRange plotRangeWithLocation:CPTDecimalFromDouble(0.0) length:CPTDecimalFromDouble(7.0)];
	
	[self.graph addPlot: barPlot];
	
	//	Mean and StdDev labels…
	
	CPTMutableTextStyle* paramsLabelStyle = [CPTMutableTextStyle textStyle];
	paramsLabelStyle.color = [CPTColor blackColor];
	paramsLabelStyle.textAlignment = CPTTextAlignmentLeft;
	
	CPTLayerAnnotation* mean = [[CPTLayerAnnotation alloc] initWithAnchorLayer: self.graphView.hostedGraph.plotAreaFrame];
	mean.rectAnchor = CPTRectAnchorTopLeft; //to make it the top centre of the plotFrame
	mean.displacement = CGPointMake(graph.plotAreaFrame.paddingLeft + 0, 15.0); //To move it down, below the title
	mean.contentAnchorPoint = CGPointMake(0.0, 1.0);
	CPTTextLayer* textLayer = [[CPTTextLayer alloc] initWithText: nil style: paramsLabelStyle];
	mean.contentLayer = textLayer;
	
	[self.graphView.hostedGraph.plotAreaFrame addAnnotation: mean];
	self.params = textLayer;
}

- (NSUInteger)
numberOfRecordsForPlot: (CPTPlot*) inPlot
{
	return self.histogram.binCount();
}

- (double)
doubleForPlot: (CPTPlot*) inPlot
	field: (NSUInteger) inField
	recordIndex: (NSUInteger) inIdx
{
	if (inField == CPTBarPlotFieldBarLocation)
	{
		double v = self.histogram.binMid(inIdx);
		//std::printf("xpos: %f\n", v);
		return v;
	}
	else if (inField == CPTBarPlotFieldBarTip)
	{
		double v = self.histogram[inIdx];
		//std::printf("tip: %f\n", v);
		return v;
	}
	
	return 0.0;
}

#pragma mark - • PlotSpace Delegate Methods

- (BOOL)
plotSpace: (CPTPlotSpace*) inSpace
	shouldHandleScrollWheelEvent: (NSEvent*) inEvent
	fromPoint: (CGPoint) inFromPoint
	toPoint: (CGPoint) inToPoint
{
	return false;
}

- (CGPoint)
plotSpace: (CPTPlotSpace*) inSpace
	willDisplaceBy: (CGPoint) inProposedDisplacementVector
{
	inProposedDisplacementVector.y = 0;
	return inProposedDisplacementVector;
}

- (void)
plotSpace: (CPTPlotSpace*) inSpace
	didChangePlotRangeForCoordinate: (CPTCoordinate) inCoordinate
{
	if (inCoordinate == CPTCoordinateX)
	{
		CPTXYPlotSpace* plotSpace = (CPTXYPlotSpace*) inSpace;
		CPTPlotRange* xr = plotSpace.xRange;
		//NSLog(@"%@ %@", xr.location, xr.length);
		CPTXYAxisSet* axisSet = (CPTXYAxisSet*) plotSpace.graph.axisSet;
		CPTXYAxis* y = axisSet.yAxis;
		y.orthogonalPosition	= xr.location;
	}
}

#pragma mark - • Properties

- (void)
setHistogram: (Histogram) inHistogram
{
	mHistogram = inHistogram;
	
	if (self.histogram.binCount() == 0)
	{
		self.params.text = nil;
		return;
	}
	
	CPTXYPlotSpace* plotSpace = (CPTXYPlotSpace*) self.graph.defaultPlotSpace;
	plotSpace.xRange = [CPTPlotRange plotRangeWithLocation: @(self.histogram.histogramLow()) length: @(self.histogram.histogramRange())];
	plotSpace.yRange = [CPTPlotRange plotRangeWithLocation: @(0) length: @(self.histogram.maxBinCount())];
	
	CPTXYAxisSet* axisSet = (CPTXYAxisSet*) self.graph.axisSet;
	CPTXYAxis* y = axisSet.yAxis;
	y.orthogonalPosition = plotSpace.xRange.location;
	
	CPTBarPlot* bp = self.graph.allPlots[0];
	bp.barWidth = @(self.histogram.binWidth() * 0.95);
	
	//	Set the meam and sigma…
	
	self.params.text = [NSString stringWithFormat: @"mean: %.4g       σ: %.4g", self.histogram.mean(), self.histogram.stdDev()];
	
	//	Set the min/max value band…
	
	[y removeBackgroundLimitBand: nil];
	CPTPlotRange* r = [CPTPlotRange plotRangeWithLocation: @(self.histogram.lowValue()) length: @(self.histogram.highValue() - self.histogram.lowValue())];
	CPTFill* fill = [CPTFill fillWithColor: [CPTColor colorWithGenericGray: 0.9]];
	CPTXYAxis* x = axisSet.xAxis;
	[x addBackgroundLimitBand: [CPTLimitBand limitBandWithRange: r fill: fill]];
	
	//	Reload the data…
	
	[self.graph reloadData];
}

@synthesize histogram				=	mHistogram;

- (void)
setTitle: (NSString*) inTitle
{
	if ([inTitle isEqual: mTitle])
	{
		return;
	}
	
	mTitle = [inTitle copy];
	
	CPTXYAxisSet* axisSet = (CPTXYAxisSet*) self.graph.axisSet;
	CPTXYAxis* x = axisSet.xAxis;
	x.title = self.title;
}

@synthesize title			=	mTitle;

@end
