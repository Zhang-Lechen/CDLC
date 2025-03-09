#ifndef PERIODIC_H
#define PERIODIC_H

#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "cdl.h"

void periodic_joinThread(FILE *fp, int period, int flagNum);
void periodic_sendMegs(FILE *fp, const char *portName, const char *type, int flagNum);
void periodic_freeComp(FILE *fp, const char* comp, int flagNum);
void periodic_activateComp(FILE *fp, const char* comp, int flagNum);
void periodic_unactivateComp(FILE *fp, const char* comp, int flagNum);
void periodic_sendMegs(FILE *fp, const char* comp, const vector<string> publish_names);
void set_on_data_available(FILE *fp, ComponentPortDesc *pPort, int recvType);
void set_receive_Megs(FILE *fp, ComponentPortDesc *pPort, int recvType);

#endif
