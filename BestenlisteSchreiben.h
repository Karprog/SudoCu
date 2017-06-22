#ifndef BESTENLISTESCHREIBEN_H_
#define BESTENLISTESCHREIBEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

int schreibeErgebnisInDb(int nutzerId, char *schwierigkeitsgrad,
                         int punktzahl, int zeit);
						 
float berechnePunkteProMinute(int iPunktzahl, int iZeit);

#endif /* BESTENLISTESCHREIBEN_H_ */