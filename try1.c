#include "swephexp.h"
#include "swephlib.h"
#include "sweph.h"
#include "swepcalc.h"
#include "sweodef.h"
#include "swemptab.h"
#include "swejpl.h"
#include "swedll.h"


int main()
{
double tret[10], attr[20], geopos[10];

char serr[255];

int32 whicheph = 0; /* default ephemeris */

double tjd_start = 2451545; /* Julian day number for 1 Jan 2000 */

int32 ifltype = SE_ECL_TOTAL|SE_ECL_CENTRAL|SE_ECL_NONCENTRAL;

/* find next eclipse anywhere on earth */

int eclflag = swe_sol_eclipse_when_glob(tjd_start, whicheph,  ifltype, tret, 0, serr);

if (eclflag == ERR)

  return ERR;

/* the time of the greatest eclipse has been returned in tret[0];

 * now we can find geographical position of the eclipse maximum */

tjd_start = tret[0];

eclflag = swe_sol_eclipse_where(tjd_start, whicheph, geopos, attr, serr);

if (eclflag == ERR)

  return ERR;

/* the geographical position of the eclipse maximum is in geopos[0] and geopos[1];

 * now we can calculate the four contacts for this place. The start time is chosen

 * a day before the maximum eclipse: */

tjd_start = tret[0] - 1;

eclflag = swe_sol_eclipse_when_loc(tjd_start, whicheph, geopos, tret, attr, 0, serr);

if (eclflag == ERR)

  return ERR;

/* now tret[] contains the following values:

 * tret[0] = time of greatest eclipse (Julian day number)

 * tret[1] = first contact

 * tret[2] = second contact

 * tret[3] = third contact

 * tret[4] = fourth contact */

}
