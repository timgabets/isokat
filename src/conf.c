#include <libconfig.h>
#include <zf_log.h>

#include "conf.h"
#include "retcodes.h"

isokat_rc_t parse_config(isokat_ctx_t *ctx, const char* filename)
{
	if(ctx == NULL || filename == NULL)
		return VALUE_ERROR;

	config_t conf;

	config_init(&conf);
	config_set_include_dir(&conf, "../tests");
	ZF_LOGI("Parsing configuration file %s", filename);

	if(config_read_file(&conf, filename) == CONFIG_FALSE) {
		ZF_LOGE("Error parsing configuration file %s:%d (%s)", 
			config_error_file(&conf), config_error_line(&conf), config_error_text(&conf));
			config_destroy(&conf);
			return VALUE_ERROR;
		return PARSE_ERROR;
	}

	config_destroy(&conf);
	return OK;
}
