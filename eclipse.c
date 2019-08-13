/* 

  MB1.c	A program to find Mahabharata's date

  Input: 
  Output:
		
   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
double tret[10], phour=0.0;

char serr[255];

int jstartyear = -7624, jendyear = -7623,  gregflag = SE_JUL_CAL, pyear= 1,pmonth= 1, pday= 1;

int32 whicheph = SEFLG_SWIEPH; /* default ephemeris */

double tjd_start; /* Julian day number for 1 Jan 2000 */

int32 ifltype = 0, eclflag; //SE_ECL_TOTAL ¦ SE_ECL_CENTRAL ¦ SE_ECL_NONCENTRAL;

pyear = jstartyear;

printf("Solar Eclipses \n");

while (pyear <= jendyear ) {
  tjd_start = swe_julday(pyear,pmonth,pday+2,phour,gregflag);

  /* find next eclipse anywhere on earth */

  eclflag = swe_sol_eclipse_when_glob(tjd_start, whicheph,  ifltype, tret, 0, serr);

  if (eclflag == ERR)
    return ERR;

  /* the time of the greatest eclipse has been returned in tret[0]; */

  swe_revjul(tret[0],gregflag,&pyear,&pmonth,&pday,&phour);
  printf("%d\t%d\t%d\t%f\t%d\n",pyear,pmonth,pday,phour,eclflag);
  
}

printf("Lunar Eclipses \n");

pyear = jstartyear;
pmonth=1;
pday=1;
phour=0.0;
ifltype = SE_ECL_TOTAL | SE_ECL_PARTIAL | SE_ECL_PENUMBRAL; 

while (pyear <= jendyear ) {
  tjd_start = swe_julday(pyear,pmonth,pday+2,phour,gregflag);

  /* find next Lunar eclipse anywhere on earth */

  eclflag = swe_lun_eclipse_when(tjd_start, whicheph,  ifltype, tret, 0, serr);

  if (eclflag == ERR)
    return ERR;

  /* the time of the greatest eclipse has been returned in tret[0]; */

  swe_revjul(tret[0],gregflag,&pyear,&pmonth,&pday,&phour);
  printf("%d\t%d\t%d\t%f\t%d\n",pyear,pmonth,pday,phour,eclflag);
  
}



 return OK;
}
