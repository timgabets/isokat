#pragma once

#include <libxml/parser.h>
#include <libxml/tree.h>

#include "formats/common.h"
#include "retcodes.h"

isokat_rc_t xml_serialize_request(msg_common_t *msg, char **buf, int32_t *n_bytes);

