#pragma once

#include <cJSON.h>

typedef struct msg_common {
	char channel[4];
	char* element[192];
} msg_common_t;

msg_common_t* common_msg_new();
void common_msg_free(msg_common_t*);

msg_common_t* json_to_common(cJSON* json);
