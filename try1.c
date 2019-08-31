/* 

  try1.c	A program to print planet's coordinates

  Input: 
  Output:
		
   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
char serr[255],snam[255];

int gregflag = SE_JUL_CAL, pyear= -7650 ,pmonth= 9, pday= 17;

double tjd,p, phour=5.0, geopos[] = {76.87,29.96}, x2[6];

int32 iflgret, iflag =  SEFLG_SWIEPH |  SEFLG_TOPOCTR | SEFLG_SIDEREAL |  SEFLG_NONUT ;

swe_set_topo(geopos[0], geopos[1], 0); 

swe_set_sid_mode(1, 0, 0);

tjd = swe_julday(pyear,pmonth,pday,phour,gregflag);
printf("Date: %d/%d/%d\t%f\n ",pyear,pmonth,pday,phour);
for (p = SE_SUN; p < SE_CHIRON; p++) {
      if (p == SE_EARTH) continue;
		  // do the coordinate calculation for this planet p
	
      iflgret = swe_calc_ut(tjd, p, iflag, x2, serr);
	      // if there is a problem, a negative value is returned and an error message is in serr.
	
      if (iflgret < 0) 
    	  printf("error: %s\n", serr);
      else if (iflgret != iflag)
      	printf("warning: iflgret != iflag. %s\n", serr);
	      // get the name of the planet p
	
      swe_get_planet_name(p, snam);
	      // print the coordinates
	
      printf("%10s\t%11.7f\t%10.7f\t%10.7f\n", snam, x2[0], x2[1], x2[3]);

}

return OK;
}
