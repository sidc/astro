/* 

  Krishna_1_Tropical.c	A program to find Krishna's birthdate according to Chart 1 given in the commentary on Bhagavata Purana (10.3.1) by Srila Sanatana Goswami. This programs uses tropical astrology. 

  Output: Date and planetary positions for the birthdate
		
   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
  char serr[AS_MAXCH], snam[AS_MAXCH];  

// jstartyear : starting point of the search interval
// jendyear : ending point of the search interval
  int jstartyear = -10500, jendyear = -1500,pyear= 1,pmonth= 1, pday= 1; 
  double geopos[] = {77.67,27.49}, jut = 0.0, phour=1.0;
  double tjsd,tjed,tjd,moonL, sunL, tithi, x2[6], p;
  int32 iflag, iflgret;

  swe_set_ephe_path("/users/ephe/");

  swe_set_topo(geopos[0], geopos[1], 0); 

  iflag =   SEFLG_SWIEPH |  SEFLG_TOPOCTR ;
  
  
  // Convert Start And End Years Into Julian Dates
  tjsd = swe_julday(jstartyear,1,1,jut,SE_GREG_CAL) - geopos[0]/360;
  tjed = swe_julday(jendyear,1,1,jut,SE_GREG_CAL) - geopos[0]/360;
  

    for(tjd = tjsd; tjd<=tjed; tjd=tjd+1){
    
    // Calculating Julian Date and Hour
    swe_revjul(tjd,SE_GREG_CAL,&pyear,&pmonth,&pday,&phour);
    //printf("%d\t%d\t%d\t%f\n",pyear,pmonth,pday,phour);

    // Calculating The Position Of Moon
    iflgret = swe_calc_ut(tjd, SE_MOON, iflag, x2, serr);
    if (iflgret < 0) 
      printf("Error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("Warning: Iflgret != Iflag. %d\t%d\n", iflag,iflgret);

    //printf("Moon:\t%f\t%f\n",x2[0],x2[1]);
    // If Moon in Rohini Nakshatra 40 - 53.3 with 2 degrees of error
    if((x2[0] < 38) || (x2[0] > 62)) continue;
    moonL = x2[0];

    // Calculating the position of Sun
    iflgret = swe_calc_ut(tjd, SE_SUN, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    //printf("Sun:\t%f\t%f\n",x2[0],x2[1]);
    // If Sun in Leo 120 - 150 with 2 degrees of error
    if((x2[0] < 118) || (x2[0] > 152)) continue;

    sunL = x2[0];

    // If tithi is Krishna Paksa - astami 264 - 276
    tithi = swe_degnorm(moonL - sunL);
    if((tithi < 262) || (tithi > 278)) continue;

    // Calculating the position of Mercury
    iflgret = swe_calc_ut(tjd, SE_MERCURY, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    //printf("Mercury:\t%f\t%f\n",x2[0],x2[1]);
    // If Mercury in Virgo 150 - 180 with 2 degrees of error
    if((x2[0] < 148) || (x2[0] > 182)) continue;

    // Calculating the position of Saturn
    iflgret = swe_calc_ut(tjd, SE_SATURN, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    //printf("Saturn:\t%f\t%f\n",x2[0],x2[1]);
    // If Saturn in Libra 180 - 210 with 2 degrees of error
    if((x2[0] < 178) || (x2[0] > 212)) continue;

    // Calculating the position of Mars
    iflgret = swe_calc_ut(tjd, SE_MARS, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n",iflag,iflgret);

    //printf("Mars:\t%f\t%f\n",x2[0],x2[1]);
    // If Mars in Capricorn 270 - 300 with 2 degrees of error
    if((x2[0] < 268) || (x2[0] > 302)) continue;

    // Calculating the position of Venus
    iflgret = swe_calc_ut(tjd, SE_VENUS, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n",iflag,iflgret);

    //printf("Venus:\t%f\t%f\n",x2[0],x2[1]);
    // If Venus in Libra 180 - 210 with 2 degrees of error
    if((x2[0] < 178) || (x2[0] > 212)) continue;


    // Calculating the position of Jupiter
    iflgret = swe_calc_ut(tjd, SE_JUPITER, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n",iflag,iflgret);

    //printf("Jupiter:\t%f\t%f\n",x2[0],x2[1]);
    // If Jupiter in Pieces 330 - 360 with 2 degrees of error
    if((x2[0] < 328) && (x2[0] > 2)) continue;



    printf("%d\t%d\t%d\t%f\t",pyear,pmonth,pday,phour);
    
    for (p = SE_SUN; p <= SE_CHIRON; p++) {
      if (p == SE_EARTH) continue;
		  /*
		   * do the coordinate calculation for this planet p
		   */
      iflgret = swe_calc_ut(tjd, p, iflag, x2, serr);
	      /*
	       * if there is a problem, a negative value is returned  
         * and an error message is in serr.
	       */
      if (iflgret < 0) 
    	  printf("error: %s\n", serr);
      else if (iflgret != iflag)
      	printf("warning: iflgret != iflag. %s\n", serr);
	      /*
	       * get the name of the planet p
	       */
      swe_get_planet_name(p, snam);
	      /*
	       * print the coordinates
	       */
      printf("%10s\t%11.7f\t%10.7f\n", snam, x2[0], x2[1]);
    }

    // Incase there is match jump 20 days ahead
    tjd = tjd + 20;
  }
  
  return OK;
}
