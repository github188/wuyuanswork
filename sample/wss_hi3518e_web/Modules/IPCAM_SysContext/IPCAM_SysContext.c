
#include "IPCAM_Export.h"
#include <sys/prctl.h>

int IPCAM_setTskName(char * name)
{
	return prctl(PR_SET_NAME, name);
}

