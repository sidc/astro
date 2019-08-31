/* 

  Mbh.c	A program to find pair of lunar and solar eclipses with few other planetary positions as mentioned in the Mahabharata 

	Output: Pair of lunar and solar eclipses with their types.    
	
   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
double tret[10], phour=0.1;

char serr[255],snam[255];

int jstartyear, jendyear,  gregflag = SE_JUL_CAL, pyear= 1,pmonth= 1, pday= 1;

int32 whicheph = SEFLG_SWIEPH; /* default ephemeris */

double tjd_start,p; /* Julian day number for 1 Jan 2000 */

int32 ifltype, eclflag; 

jstartyear = -7796; // -9564; //-7796
jendyear = -7546; //-9314; //-7546

pyear = jstartyear;


printf("Lunar Eclipses \n");



int32 iflgret, moonFlag, sunFlag, iflag =  SEFLG_SWIEPH |  SEFLG_TOPOCTR | SEFLG_SIDEREAL |  SEFLG_NONUT ;
int32 isflag = iflag | SEFLG_SPEED;
double geopos[] = {76.87,29.96}, x2[6],moonEcl,sunEcl;
swe_set_topo(geopos[0], geopos[1], 0); 
swe_set_sid_mode(1, 0, 0);

while (pyear <= jendyear ) {
  ifltype = SE_ECL_TOTAL | SE_ECL_PARTIAL; //SE_ECL_TOTAL | SE_ECL_PARTIAL | SE_ECL_PENUMBRAL; 
  tjd_start = swe_julday(pyear,pmonth,pday+2,phour,gregflag);

  /* find next Lunar eclipse anywhere on earth */
  
  eclflag = swe_lun_eclipse_when(tjd_start, whicheph,  ifltype, tret, 0, serr);

  if (eclflag == ERR)
    return ERR;
  
   swe_revjul(tret[0],gregflag,&pyear,&pmonth,&pday,&phour);
  /* the time of the greatest eclipse has been returned in tret[0]; */

   // Calculating the position and speed of Mars
    iflgret = swe_calc_ut(tret[0], SE_MARS, isflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != isflag)
    	printf("warning: iflgret != isflag. %d\t%d\n", iflag,iflgret);

    //printf("Mars:\t%f\t%f\n",x2[0],x2[1]);
    // If Mars in Jyestha 226.66 - 240 and going backwards with 2 degrees of error
    // If Mars in Anuradha 213.33 - 226.66 and going backwards with 2 degrees of error
    if((x2[0] < 211.33) | (x2[0] > 242) ) continue;


     // Calculating The Position Of Saturn
    iflgret = swe_calc_ut(tret[0], SE_SATURN, iflag, x2, serr);
    if (iflgret < 0) 
      printf("Error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("Warning: Iflgret != Iflag. %d\t%d\n", iflag,iflgret);

    //printf("Saturn:\t%f\t%f\n",x2[0],x2[1]);
    //If Saturn in Rohini Nakshatra 40 - 53.3 with 2 degrees of error
    //If Saturn is in or near Vishaka Nakshatra 200 - 213.3 with 20 degrees of error
    if((x2[0] < 180) | (x2[0] > 233.3)) continue;


    moonEcl = tret[0];
    moonFlag=eclflag;
    ifltype = 0; //SE_ECL_TOTAL ¦ SE_ECL_CENTRAL ¦ SE_ECL_NONCENTRAL;
    eclflag = swe_sol_eclipse_when_glob(moonEcl, whicheph,  ifltype, tret, 0, serr);

    if (eclflag == ERR)
      return ERR;
    sunEcl = tret[0];

    if((sunEcl - moonEcl) > 20) continue;
  
    swe_revjul(moonEcl,gregflag,&pyear,&pmonth,&pday,&phour);
    printf("Lunar: %d/%d/%d\t%f\t%d ",pyear,pmonth,pday,phour,moonFlag);

    swe_revjul(sunEcl,gregflag,&pyear,&pmonth,&pday,&phour);
    printf("Solar: %d/%d/%d\t%f\t%d\n",pyear,pmonth,pday,phour,eclflag);
  
  /*
   for (p = SE_SUN; p < SE_CHIRON; p++) {
      if (p == SE_EARTH) continue;
		  // do the coordinate calculation for this planet p
	
      iflgret = swe_calc_ut(moonEcl, p, isflag, x2, serr);
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
}



 return OK;
}
