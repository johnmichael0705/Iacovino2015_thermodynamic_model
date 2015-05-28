//
//  CharacterizeMeltInclusion.m
//  Iacovino
//
//  Created by Roderick Mann on 5/9/2015.
//  Copyright (c) 2015 Latency: Zero. All rights reserved.
//

#import "CharacterizeMeltInclusion.h"


#import <CorePlot/CorePlot.h>


#import "CharacterizationContext.h"
#import "HistogramView.h"


@interface CharacterizeMeltInclusion()
{
	MonteCarlo			mMC;
}

@property (weak) IBOutlet HistogramView *tempChart;
@property (weak) IBOutlet HistogramView *pressureChart;
@property (weak) IBOutlet HistogramView *logFH2OChart;
@property (weak) IBOutlet HistogramView *logFO2Chart;
@property (weak) IBOutlet HistogramView *logFS2Chart;

@property (weak) IBOutlet HistogramView *coChart;
@property (weak) IBOutlet HistogramView *co2Chart;
@property (weak) IBOutlet HistogramView *h2oChart;
@property (weak) IBOutlet HistogramView *h2sChart;
@property (weak) IBOutlet HistogramView *so2Chart;

@end




@implementation CharacterizeMeltInclusion

- (void)
viewDidLoad
{
	[super viewDidLoad];
	
	self.tempChart.title = @"Temp (°C)";
	self.pressureChart.title = @"Pressure (bar)";
	self.logFH2OChart.title = @"log FH2O";
	self.logFO2Chart.title = @"log FO2";
	self.logFS2Chart.title = @"log FS2";
	
	self.coChart.title = @"CO";
	self.co2Chart.title = @"CO2";
	self.h2oChart.title = @"H2O";
	self.h2sChart.title = @"H2S";
	self.so2Chart.title = @"SO2";
}


- (IBAction)
runCharacterization: (id) inSender
{
	//	Intermediate region…
	
	InputVariable			temp(1081.0, 25.0);
	InputVariable			pressure(3582.0, 1.0);
	InputVariable			logFH2O(1.25, 0.06);
	InputVariable			logFO2(-9.99, 0.5);
	InputVariable			logFS2(-3.01, 0.35);
	
	mMC.addInputVariable(temp);
	mMC.addInputVariable(pressure);
	mMC.addInputVariable(logFH2O);
	mMC.addInputVariable(logFO2);
	mMC.addInputVariable(logFS2);
	
#if 0
	Histogram				histCO(3.19904e-02, 0.001, 0.01);
	Histogram				histCO2(9.52939e-01, pressure.stdDev(), 50.0;
	Histogram				histH2O(logFH2O.mean(), logFH2O.stdDev(), 5.0;
	Histogram				histH2S(logFO2.mean(), temp.stdDev(), 5.0;
	Histogram				histSO2(temp.mean(), temp.stdDev(), 5.0;
#endif
	
	/**
		TODO:	Set up run to break up iterations into multiple parallel ops.
				Create serial queue to enqueue histogram accumulation of outputs.
	*/
	 
	
	__block VarianceAccumulator		coVariance;
	
	mMC.setCreateSweepContextBlock(
	^MonteCarlo::SweepContext* (size_t inVariableIdx)
	{
		CharacterizationContext* ctx = new CharacterizationContext();
		return ctx;
	});
	
	mMC.runCharacterization(10000,
		^(MonteCarlo* inMC, MonteCarlo::SweepContext* inCTX)
		{
			//	Update the histograms…
			
			const CharacterizationContext* ctx = static_cast<CharacterizationContext*>(inCTX);
			
			self.tempChart.histogram = ctx->mTemp;
			self.pressureChart.histogram = ctx-> mPressure;
			self.logFH2OChart.histogram = ctx->mLogFH2O;
			self.logFO2Chart.histogram = ctx->mLogFO2;
			self.logFS2Chart.histogram = ctx->mLogFS2;
			
			self.coChart.histogram = ctx->mCO;
			self.co2Chart.histogram = ctx->mCO2;
			self.h2oChart.histogram = ctx->mH2O;
			self.h2sChart.histogram = ctx->mH2S;
			self.so2Chart.histogram = ctx->mSO2;
		});
}

@end


