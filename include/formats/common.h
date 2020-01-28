#pragma once

#include <stdint.h>

#include "cJSON.h"

#define MAX_DE_INDEX 192

typedef struct msg_common {
	uint32_t id;
	char channel[4];
	char* elements[MAX_DE_INDEX];
} msg_common_t;

int32_t get_de_index_from_string(const char* de_index);

msg_common_t* common_msg_new();
void common_msg_free(msg_common_t*);

msg_common_t* json_to_common(cJSON* json);
