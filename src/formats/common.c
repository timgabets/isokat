#include <string.h>
#include <stdlib.h>

#include "formats/common.h"

msg_common_t* common_msg_new()
{
	msg_common_t* msg = malloc(sizeof(msg_common_t));
	memset(msg, 0, sizeof(msg_common_t));
	return msg;
}

void common_msg_free(msg_common_t* msg)
{
	free(msg);
}

msg_common_t* json_to_common(cJSON* json)
{
	if(json == NULL)
		return NULL;
	msg_common_t* msg = common_msg_new();
	return msg;
}