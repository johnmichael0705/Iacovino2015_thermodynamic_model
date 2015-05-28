#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#include <dispatch/dispatch.h>

typedef double			DataTypeT;

//All compositions are given in mol%
//The below values are given in the order: EA-1 equilibrium fluid; 97009 equilibrium fluid; DVDP 3-295 equilibrium fluid; Lava Lake euqilibrium fluid; Bas-to-Teph MIs; Tehp-to-Phon MIs; Phon-to-LL MIs
DataTypeT co2_vals[] = {99.83/100.0,	98.41/100.0,	87.43/100.0,	60.02/100.0,	12.50/100.0,	15.45/100.0,	16.95/100.0};
DataTypeT h2o_vals[] = {0.17/100.0,		1.59/100.0,		4.81/100.0,		37.82/100.0,	85.58/100.0,	80.04/100.0,	60.38/100.0};
DataTypeT h2s_vals[] = {0.0,			0.1/100.0,		0.54/100.0,		2.12/100.0,		0.04/100.0,		2.22/100.0,		10.61/100.0};
DataTypeT so2_vals[] = {0.0,			0.0,			7.22/100.0,		0.03/100.0,		1.88/100.0,		2.29/100.0,		12.06/100.0};
DataTypeT total_s_vals[] = {0.0,		0.1/100.0,		7.72/100.0,		2.15/100.0,		1.92/100.0,		4.51/100.0,		22.67/100.0};

//The below values are all for the surface gas, given in the order: x; x-1; x+1, where x = measured value
DataTypeT surface_gas_co2[] = {38.04, 37.99, 38.09};
DataTypeT surface_gas_h2o[] = {60.47, 60.42, 60.52};
DataTypeT surface_gas_h2s[] = {0.03, 0.0, 0.08};
DataTypeT surface_gas_so2[] = {1.46, 1.41, 1.51};
DataTypeT surface_gas_total_s[] = {1.49, 1.44, 1.54};

//Defines an inline function that multiplies the possible percentage values a,b,c,d,e,f, and g by the concentration of some species (CO2, H2O, or Stot) in each contributing fluid
DataTypeT getVals(int a, int b, int c, int d, int e, int f, int g, DataTypeT *ptr){
  return (a*ptr[0])+(b*ptr[1])+(c*ptr[2])+(d*ptr[3])+(e*ptr[4])+(f*ptr[5])+(g*ptr[6]);
}

//Define the variables to be used
int mix(void)
{
  FILE *ofp = stdout;
  
	//Generates a list of one-dimensional arrays, each array 7 values long, where the sum of each array is 100
	dispatch_apply(4, dispatch_get_global_queue(QOS_CLASS_USER_INTERACTIVE, 0),
	^(size_t inI)
//  for (i = 0; i < 4; i++){
    {
		int i = (int) inI;
		
  register int a,b,c,d,e,f,g;
  //DataTypeT val;
  int start_val, end_val;
  //char s[200];
		
	  //sprintf(s,"iter_out_%d",i);
      start_val = i*25;
      end_val = start_val + 26;
      for (a=start_val;a<end_val;a++){
        //printf("proc%d: i = %d\n",i,a);
        for (b=100-a; b>-1; b--){
          for (c=100-a-b; c>-1; c--){
            for (d=100-a-b-c; d>-1; d--){
              for (e=100-a-b-c-d; e>-1; e--){
                for (f=100-a-b-c-d-e; f>-1; f--){
                  for (g=100-a-b-c-d-e-f; g>-1; g--){
					int sum = a+b+c+d+e+f+g;
					if (sum != 100)
					{
						continue;
					}
					  
#if 1
					  //If G - 1 >= the sum of the proportioned fluid contributions >= G+1, exclude that array from the final list. G = measured surface gas value of each species.
                    DataTypeT co2 = getVals(a,b,c,d,e,f,g,co2_vals);
                    if ((co2 < surface_gas_co2[1]) || (co2 >surface_gas_co2[2])){
                      continue;
                    }
                    
                    DataTypeT h2o = getVals(a,b,c,d,e,f,g,h2o_vals);
                    if ((h2o < surface_gas_h2o[1]) || (h2o >surface_gas_h2o[2])){
                      continue;
                    }
                    
                    DataTypeT h2s = getVals(a,b,c,d,e,f,g,h2s_vals);
                    if ((h2s < surface_gas_h2s[1]) || (h2s >surface_gas_h2s[2])){
                      continue;
                    }
					  
                    DataTypeT so2 = getVals(a,b,c,d,e,f,g,so2_vals);
                    if ((so2 < surface_gas_so2[1]) || (so2 >surface_gas_so2[2])){
                      continue;
                    }
#endif
                    //Prints all arrays where G - 1 <= sum of the proportioned fluid contributions <= G + 1 is true for all gas species. Output is saved to four files: one file for each forked process.
                    fprintf(ofp,"%d %d %d %d %d %d %d - %10.7f    %10.7f    %10.7f    %10.7f\n",a,b,c,d,e,f,g, co2, h2o, h2s, so2);
                        
                  }
                }
              }
            }
          }
        }
      }
      
    });
	printf("Complete\n");
  return 0;
 }
      
    
  
