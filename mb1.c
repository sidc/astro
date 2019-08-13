/* 

  MB1.c	A program to find Mahabharata's date

  Input: 
  Output:
		
   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
  char serr[AS_MAXCH];  
  int jstartyear = -7621, jendyear = -7615,pyear= 1,pmonth= 11, pday= 1; 
  double geopos[] = {76.87,29.96}, jut = 0.01, phour=1.0;
  double tjsd,tjed,tjd,x2[6];
  int32 iflag, iflgret, isflag;
  int gregflag = SE_JUL_CAL;

  swe_set_ephe_path("/users/ephe/");
  swe_set_sid_mode(1, 0, 0);
  swe_set_topo(geopos[0], geopos[1], 0); 

  iflag =  SEFLG_SWIEPH |  SEFLG_TOPOCTR | SEFLG_SIDEREAL |  SEFLG_NONUT ;
  isflag = iflag | SEFLG_SPEED;
  
  // Convert Start And End Years Into Julian Dates
  tjsd = swe_julday(jstartyear,1,1,jut,gregflag) - geopos[0]/360;
  tjed = swe_julday(jendyear,1,1,jut,gregflag) - geopos[0]/360;


  for(tjd = tjsd; tjd<=tjed; tjd=tjd+1){
    
    

    // Calculating The Position Of Saturn
    iflgret = swe_calc_ut(tjd, SE_SATURN, iflag, x2, serr);
    if (iflgret < 0) 
      printf("Error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("Warning: Iflgret != Iflag. %d\t%d\n", iflag,iflgret);

    //printf("Saturn:\t%f\t%f\n",x2[0],x2[1]);
    //If Saturn in Rohini Nakshatra 40 - 53.3 with 2 degrees of error
    //If Saturn is in or near Vishaka Nakshatra 200 - 213.3 with 10 degrees of error
    //if((x2[0] < 190) | (x2[0] > 223.3)) continue;

    
    // Calculating the position and speed of Mars
    iflgret = swe_calc_ut(tjd, SE_MARS, isflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != isflag)
    	printf("warning: iflgret != isflag. %d\t%d\n", iflag,iflgret);

    //printf("Mars:\t%f\t%f\n",x2[0],x2[1]);
    // If Mars in Jyestha 226.66 - 240 and going backwards with 2 degrees of error
    // If Mars in Anuradha 213.33 - 226.66 and going backwards with 2 degrees of error
    if((x2[0] < 211.33) | (x2[0] > 242) ) continue;

    // Calculating Julian Date and Hour
    swe_revjul(tjd + geopos[0]/360,gregflag,&pyear,&pmonth,&pday,&phour);
    printf("%d\t%d\t%d\t%f\n",pyear,pmonth,pday,phour);
   
/*
    for (p = SE_SUN; p < SE_CHIRON; p++) {
      if (p == SE_EARTH) continue;
		  // do the coordinate calculation for this planet p
	
      iflgret = swe_calc_ut(tjd, p, isflag, x2, serr);
	      // if there is a problem, a negative value is returned and an error message is in serr.
	
      if (iflgret < 0) 
    	  printf("error: %s\n", serr);
      else if (iflgret != isflag)
      	printf("warning: iflgret != isflag. %s\n", serr);
	      // get the name of the planet p
	
      swe_get_planet_name(p, snam);
	      // print the coordinates
	
      printf("%10s\t%11.7f\t%10.7f\t%10.7f\n", snam, x2[0], x2[1], x2[3]);
    }
*/
    // Incase there is match jump 20 days ahead
    tjd = tjd + 10;
  }
  return OK;
}
