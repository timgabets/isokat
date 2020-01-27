#include <stdlib.h>
#include <string.h>

#include "formats/common.h"
#include "zf_log.h"

msg_common_t* common_msg_new()
{
	msg_common_t* msg = malloc(sizeof(msg_common_t));
	memset(msg, 0, sizeof(msg_common_t));
	return msg;
}

void common_msg_free(msg_common_t* msg)
{
	for(size_t i = 0; i < MAX_DE_INDEX; i++)
		if(msg->elements[i] != NULL)
			free(msg->elements[i]);
	free(msg);
}


int32_t get_de_index_from_string(const char* de_index)
{
	if(de_index == NULL || de_index[0] != 'i' || strlen(de_index) < 2)
		return -1;

	char *endp;
	int32_t index = (int32_t) strtol(&de_index[1], &endp, 10);
	if(endp == NULL || *endp != '\0')
			return -1;

	return index;
}

msg_common_t* json_to_common(cJSON* json)
{
	if(json == NULL || json->child == NULL)
		return NULL;
	msg_common_t* msg = common_msg_new();

	cJSON *root = json->child;
	for(cJSON *i = root; i != NULL; i = i->next) {
		int32_t index = get_de_index_from_string(i->string);
		if(index == -1) {
			ZF_LOGE("Error getting Data Element index from '%s'", i->string);
			continue;
		} else if(index > MAX_DE_INDEX) {
			ZF_LOGE("Data Element index '%s' is too large: must be less than %d", i->string, MAX_DE_INDEX);
			continue;
		}

		if(i->valuestring == NULL) {
			ZF_LOGE("NULL value on Data Element %s", i->string);
			continue;
		}

		msg->elements[index] = strdup(i->valuestring);
		if(msg->elements[index] == NULL)
			ZF_LOGE("strdup() error");

	}
	return msg;
}