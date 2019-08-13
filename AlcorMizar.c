/* 

  AlcorVasistha.c	A program to find the difference between Arundhati(Alcor) and Vasistha(Mizar) measured in Right Ascension coordinates.

  Input: Two years
  Output: RA values (degrees) for Alcor and Mizar and their difference. 
  RA-Alcor - RA-Mizar. Negative values imply that Arundhati rose earlier than Vasistha. 
		
   
  Author: Sidharth Chhabra

*/

#include "swephexp.h" 	/* this includes  "sweodef.h" */

int main()
{
  char sdate[AS_MAXCH], serr[AS_MAXCH], serr2[AS_MAXCH], alcor[AS_MAXCH] = "Alcor",mizar[AS_MAXCH] = "Mizar";  
  int jStartYear = 1, jEndYear = 1,pyear= 1,pmonth= 1, pday= 1; 
  double jut = 0.0, phour=1.0;
  double tjsd,tjed,p,alcorL, mizarL, x2[6], x3[6];
  int32 iflag, iflgret;
  swe_set_ephe_path("/users/ephe/");
  iflag =  SEFLG_SWIEPH | SEFLG_EQUATORIAL | SEFLG_NONUT | SEFLG_TRUEPOS | SEFLG_NOABERR | SEFLG_NOGDEFL;
  printf("\nStart-year  End-year ?");
  if( !fgets(sdate, sizeof(sdate)-1, stdin) ) return OK;
  if (sscanf (sdate, "%d%*c%d", &jStartYear,&jEndYear) < 1) exit(1);
  
  // Convert Start and End years into julian dates
  tjsd = swe_julday(jStartYear,1,1,jut,SE_GREG_CAL);
  tjed = swe_julday(jEndYear,1,1,jut,SE_GREG_CAL);

  printf("Year\tAlcor RA\tMizar RA\tDifference (arc secs)\t%d\n",iflag);
  for(p = tjsd; p<=tjed; p=p+73050){
    
    // Printing Gregorian year based on Julian dates    
    swe_revjul(p,SE_GREG_CAL,&pyear,&pmonth,&pday,&phour);
    printf("%d\t",pyear);

    // Calculating the position of Alcor
    iflgret = swe_fixstar2_ut(alcor, p, iflag, x2, serr);
    if (iflgret < 0) 
      printf("error: %s\n", serr);
    else if (iflgret != iflag)
    	printf("warning: iflgret != iflag. %d\t%d\n", iflag,iflgret);

	  // print Alcor's Right Ascension value
    alcorL = x2[0];
    printf("%11.7f\t",alcorL);
    
    // Calculating the position of Mizar
    iflgret = swe_fixstar2_ut(mizar, p, iflag, x3, serr2);
    if (iflgret < 0) 
	    printf("error: %s\n", serr);
    else if (iflgret != iflag)
	    printf("warning: iflgret != iflag. %s\n", serr);

	  // print Mizar's Right Ascension value and the difference (in arc secs)
    mizarL = x3[0];
    printf("%f\t%11.7f\n", mizarL, (alcorL-mizarL)*3600);
      
  }
  return OK;
}
