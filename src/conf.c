#include <libconfig.h>
#include <stdlib.h>
#include <string.h>
#include <zf_log.h>

#include "conf.h"
#include "retcodes.h"

isokat_rc_t parse_config(isokat_ctx_t *ctx, const char* filename)
{
	if(ctx == NULL || filename == NULL)
		return VALUE_ERROR;

	config_t conf;

	config_init(&conf);
	ZF_LOGI("Parsing configuration file %s", filename);

	if(config_read_file(&conf, filename) == CONFIG_FALSE) {
		ZF_LOGE("Error parsing configuration file %s:%d (%s)", 
			config_error_file(&conf), config_error_line(&conf), config_error_text(&conf));
			config_destroy(&conf);
			return VALUE_ERROR;
		return PARSE_ERROR;
	}

	config_setting_t *s = config_lookup(&conf, "channels");
	if(s != NULL && config_setting_is_list(s) == CONFIG_TRUE) {
		size_t n_channels = config_setting_length(s);
		for(size_t i = 0; i < n_channels; i++) {
			config_setting_t *chan_setting = config_setting_get_elem(s, i);
			if(chan_setting == NULL) {
				ZF_LOGE("Error getting channel #%lu", i);
				continue;
			}

			channel_t *ch = channel_new();
			if(ch == NULL)
				return ALLOC_ERROR;

			/* Channel type */
			const char *type_str;
			if(config_setting_lookup_string(chan_setting, "type", &type_str) != CONFIG_TRUE) {
				ZF_LOGE("Missing mandatory channel type setting for channel #%lu", i);
				channel_free(ch);
				continue;
			}

			if(strcmp(type_str, "XML") == 0)
				ch->type = XML;
			else if(strcmp(type_str, "VISA") == 0)
				ch->type = VISA;
			else if(strcmp(type_str, "MASTERCARD") == 0)
				ch->type = MASTERCARD;
			else {
				ZF_LOGE("Unsupported channel type %s for channel #%lu", type_str, i);
				channel_free(ch);
				continue;
			}

			/* Channel name */
			const char *name_str;
			if(config_setting_lookup_string(chan_setting, "name", &name_str) != CONFIG_TRUE) {
				ZF_LOGE("Missing mandatory name setting for channel #%lu", i);
				channel_free(ch);
				continue;
			} 
			ch->name = strdup(name_str);
			if(ch->name == NULL) {
				channel_free(ch);
				return ALLOC_ERROR;
			}

			/* Server/Client */
			const char *conn_type_str;
			if(config_setting_lookup_string(chan_setting, "conn_type", &conn_type_str) != CONFIG_TRUE) {
				/* Using server by default */
				ch->remote_host_is = SERVER;
			} else {
				if(strcmp(conn_type_str, "server") == 0)
					ch->remote_host_is = SERVER;
				else if(strcmp(conn_type_str, "client") == 0)
					ch->remote_host_is = CLIENT;
				else {
					ZF_LOGW("Unsupported connection type for channel #%lu", i);
					channel_free(ch);
					ch->remote_host_is = SERVER;
				}
			}	

			/* Channel host */
			const char *host_str;
			if(config_setting_lookup_string(chan_setting, "host", &host_str) != CONFIG_TRUE) {
				ZF_LOGE("Missing mandatory host setting for channel #%lu", i);
				channel_free(ch);
				continue;
			} 
			ch->host = strdup(host_str);
			if(ch->host == NULL) {
				channel_free(ch);
				return ALLOC_ERROR;
			}	

			/* Channel port */
			if(config_setting_lookup_int(chan_setting, "port", &(ch->port)) != CONFIG_TRUE) {
				ZF_LOGE("Missing mandatory TCP port setting for channel #%lu", i);
				channel_free(ch);
				continue;
			}

			/* Synchronous / Asynchronous */
			int async = false;
			if(config_setting_lookup_bool(chan_setting, "async", &async) != CONFIG_TRUE)
				ch->asynchronous = false; /* Synchronous by default */
			else 
				ch->asynchronous = async;

			/* Timeout */
			double timeout = 0;
			int timeout_int = 0;
			if(config_setting_lookup_float(chan_setting, "timeout", &timeout) != CONFIG_TRUE &&
			   config_setting_lookup_int(chan_setting, "timeout", &timeout_int) != CONFIG_TRUE) {
				ch->timeout = 0;
			} else {
				ch->timeout = (timeout > 0) ? timeout : timeout_int;
			}

			if(ctx_add_channel(ctx, ch) != OK){ 
				ZF_LOGE("Error adding channel #%lu", i);
				channel_free(ch);
				continue;
			}
		}
	}

	config_destroy(&conf);
	return OK;
}
