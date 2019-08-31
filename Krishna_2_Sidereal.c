/* 

  Krishna_2_Sidereal.c	A program to find Krishna's birthdate according to chart 2 given by Sanatana Goswami in their commentary on Bhagavata Purana (10.3.1) in the book Vaisnava Tosani. This program used Tropical astrology with topocentric corrections. 

   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
  char serr[AS_MAXCH], snam[AS_MAXCH];  
  int jstartyear = -10999, jendyear = -500,pyear= 1,pmonth= 1, pday= 1; 
  double geopos[] = {77.67,27.49}, jut = 0.01, phour=1.0;
  double tjsd,tjed,tjd,moonL, sunL, tithi, x2[6], p;
  int32 iflag, iflgret;
  int gregflag = SE_JUL_CAL;

  swe_set_ephe_path("/users/ephe/");
  swe_set_sid_mode(1, 0, 0);
  swe_set_topo(geopos[0], geopos[1], 0); 

  iflag =  SEFLG_SWIEPH |  SEFLG_TOPOCTR | SEFLG_SIDEREAL |  SEFLG_NONUT ;
  
  
  // Convert Start And End Years Into Julian Dates
  tjsd = swe_julday(jstartyear,1,1,jut,gregflag) - geopos[0]/360;
  tjed = swe_julday(jendyear,1,1,jut,gregflag) - geopos[0]/360;


  for(tjd = tjsd; tjd<=tjed; tjd=tjd+1){
    
    

    // Calculating The Position Of Moon
    iflgret = swe_calc_ut(tjd, SE_MOON, iflag, x2, serr);
    if (iflgret < 0) 
      printf("Error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("Warning: Iflgret != Iflag. %d\t%d\n", iflag,iflgret);

    // If Moon in Rohini Nakshatra 40 - 53.3 with 2 degrees of error. Rohini constellation is a subset of Taurus. 
    if((x2[0] < 38) | (x2[0] > 55.3)) continue;
    moonL = x2[0];

    
    // Calculating the position of Sun
    iflgret = swe_calc_ut(tjd, SE_SUN, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    sunL = x2[0];

    // If tithi is Krishna Paksa - astami   264 - 276
    tithi = swe_degnorm(moonL - sunL);
    if((tithi < 262) | (tithi > 278)) continue;

    // Calculating the position of Mercury
    iflgret = swe_calc_ut(tjd, SE_MERCURY, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    //printf("Mercury:\t%f\t%f\n",x2[0],x2[1]);
    // If Mercury in Virgo 150 - 180 with 2 degrees of error
    if((x2[0] < 148) | (x2[0] > 182)) continue;

    // Calculating the position of Saturn
    iflgret = swe_calc_ut(tjd, SE_SATURN, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

    // If Saturn in Libra 180 - 210 with 2 degrees of error
    if((x2[0] < 178) | (x2[0] > 212)) continue;

    // Calculating the position of Mars
    iflgret = swe_calc_ut(tjd, SE_MARS, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n",iflag,iflgret);

    // If Mars in Pisces 330 - 360 with 2 degrees of error
    if((x2[0] < 328) && (x2[0] > 2)) continue;

     // Calculating the position of Jupiter
    iflgret = swe_calc_ut(tjd, SE_JUPITER, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n",iflag,iflgret);

    // If Jupiter in Cancer (Domicile) 90-120 or Gemini 60 - 90 with 2 degrees of error
    if((x2[0] < 58) || (x2[0] > 122)) continue;


    // Calculating Julian Date and Hour
    swe_revjul(tjd + geopos[0]/360,gregflag,&pyear,&pmonth,&pday,&phour);
    printf("%d\t%d\t%d\t%f\n",pyear,pmonth,pday,phour);
    
    for (p = SE_SUN; p <= SE_MEAN_NODE; p++) {
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
