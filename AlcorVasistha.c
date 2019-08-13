
/* 

  AlcorVasistha.c	A program to show a strange behavior of Swiss Ephemeris's fixed star function

  Input: any year
  Output: Longitude Values of Alcor and Mizar
		
   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
  char sdate[AS_MAXCH], serr[AS_MAXCH], alcor[41] = "Alcor",mizar[41] = "Mizar";  
  int jYear = 1; 
  double jut = 0.0;
  double tjd, x2[6];
  int32 iflag, iflgret;
  swe_set_ephe_path("../ephe/");
  iflag =  SEFLG_EQUATORIAL | SEFLG_BARYCTR | SEFLG_NONUT | SEFLG_TRUEPOS ;
  printf("\nYear?");
  if( !fgets(sdate, sizeof(sdate)-1, stdin) ) return OK;
  if (sscanf (sdate, "%d", &jYear) < 1) exit(1);

  tjd = swe_julday(jYear,1,1,jut,SE_GREG_CAL);

  iflgret = swe_fixstar2_ut(mizar, tjd, iflag, x2, serr);
  printf("Mizar\t%11.7f\t%11.7f\n",x2[0],x2[1]);


  iflgret = swe_fixstar2_ut(mizar, tjd, iflag, x2, serr);
  printf("Mizar\t%11.7f\t%11.7f\n",x2[0],x2[1]); 

  iflgret = swe_fixstar2_ut(alcor, tjd, iflag, x2, serr);
  printf("Alcor\t%11.7f\t%11.7f\n",x2[0],x2[1]);

  iflgret = swe_fixstar2_ut(alcor, tjd, iflag, x2, serr);
  printf("Alcor\t%11.7f\t%11.7f\n",x2[0],x2[1]);

  iflgret = swe_fixstar2_ut(mizar, tjd, iflag, x2, serr);
  printf("Mizar\t%11.7f\t%11.7f\n",x2[0],x2[1]); 


  iflgret = swe_fixstar2_ut(mizar, tjd, iflag, x2, serr);
  printf("Mizar\t%11.7f\t%11.7f\n",x2[0],x2[1]); 
 
  return OK;
}
