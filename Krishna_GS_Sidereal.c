/* 

  Krishna_GS.c	A program to find Krishna's birthday according to the description given in the Garga Samhita. 

  Input: 
  Output:
		
   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
  char serr[AS_MAXCH];  
  int jstartyear = -9000, jendyear = -1000,pyear= 1,pmonth= 1, pday= 1; 
  double geopos[] = {82.2,26.8}, jut = 0.0, phour=1.0;
  double tjsd,tjed,tjd,moonL, sunL, tithi, x2[6];
  int32 iflag, iflgret;

  swe_set_ephe_path("/users/ephe/");
  Swe_Set_Sid_Mode(Se_Sidm_Lahiri, 0, 0);
  swe_set_topo(geopos[0], geopos[1], 0); 

  iflag =  SEFLG_SWIEPH |  SEFLG_TOPOCTR ;
  
  
  // Convert Start And End Years Into Julian Dates
  tjsd = swe_julday(jstartyear,1,1,jut,0) - geopos[0]/360;
  tjed = swe_julday(jendyear,1,1,jut,0) - geopos[0]/360;


  for(tjd = tjsd; tjd<=tjed; tjd=tjd+1){
    
    // Calculating Julian Date and Hour
    swe_revjul(tjd,0,&pyear,&pmonth,&pday,&phour);
    //printf("%d\t%d\t%d\t%f\n",pyear,pmonth,pday,phour);

    // Calculating The Position Of Moon
    iflgret = swe_calc_ut(tjd, SE_MOON, iflag, x2, serr);
    if (iflgret < 0) 
      printf("Error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("Warning: Iflgret != Iflag. %d\t%d\n", iflag,iflgret);

    //printf("Moon:\t%f\t%f\n",x2[0],x2[1]);
    // If Moon in Rohini Nakshatra 40 - 53.3 with 2 degrees of error
    // If Moon in Taurus
    if((x2[0] < 28) | (x2[0] > 62)) continue;
    moonL = x2[0];

    // Calculating the position of Sun
    iflgret = swe_calc_ut(tjd, SE_SUN, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    //printf("Sun:\t%f\t%f\n",x2[0],x2[1]);
    // If Sun in Leo 120 - 150 with 2 degrees of error
    if((x2[0] < 118) | (x2[0] > 152)) continue;

    sunL = x2[0];

    // If tithi is Krishna Paksa - astami or navmi  264 - 288
    tithi = swe_degnorm(moonL - sunL);
    if((tithi < 262) | (tithi > 290)) continue;

    // Calculating the position of Mercury
    iflgret = swe_calc_ut(tjd, SE_MERCURY, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    //printf("Mercury:\t%f\t%f\n",x2[0],x2[1]);
    // If Mercury in Taurus 30 - 60 with 2 degrees of error
    if((x2[0] < 28) | (x2[0] > 62)) continue;

    // Calculating the position of Venus
    iflgret = swe_calc_ut(tjd, SE_VENUS, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    //printf("Venus:\t%f\t%f\n",x2[0],x2[1]);
    // If Venus in Libra 180 - 210 with 2 degrees of error
    if((x2[0] < 178) | (x2[0] > 212)) continue;

    printf("%d\t%d\t%d\t%f",pyear,pmonth,pday,phour);
    
    // Incase there is match jump 20 days ahead
    tjd = tjd + 20;
  }
  return OK;
}
