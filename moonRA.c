#include "swephexp.h" 

int main()
{
  char serr[AS_MAXCH];  
  int jStartYear = 2018,pyear= 1,pmonth= 1, pday= 1; 
  double geopos[] = {82.2,26.8},  phour=1.0 , jut = 0.0;
  double tjsd, x2[6];
  int32 iflag, iflgret;

  swe_set_ephe_path("/users/ephe/");
//  swe_set_sid_mode(SE_SIDM_LAHIRI, 0, 0);
  swe_set_topo(geopos[0], geopos[1], 0); 

  iflag =  SEFLG_SWIEPH | SEFLG_EQUATORIAL | SEFLG_TOPOCTR ;
  // 

  // Convert Start and End years into julian dates
  tjsd = swe_julday(jStartYear,1,1,0,0)- geopos[0]/360;


    // Printing Gregorian year based on Julian dates    
    swe_revjul(tjsd,0,&pyear,&pmonth,&pday,&phour);
    printf("%f\t%d\t%d\t%d\t%f\n",tjsd,pyear,pmonth,pday,phour);

    // Calculating the position of Moon
    iflgret = swe_calc_ut(tjsd, SE_MOON, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    printf("Moon:\t%f\t%f\n",x2[0],x2[1]);

}
