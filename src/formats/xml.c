#include <zf_log.h>

#include "formats/xml.h"

/**
 Examples:

 <RequestInput>
 	<Header>
 		<MessageID>430173293629234065</MessageID>
 		<SystemID>IDDQD</SystemID>
 	</Header>
	<ISO8583-87>
	 	<i000>0100</i000>
	 	<i002>4444000011112222</i002>
	 	<i003>300000</i003>
	 	<i004>000000000000</i004>
	 	<i007>2101165825</i007>
	 	<i011>430173</i011>
	 	<i012>165825</i012>
	 	<i013>0121</i013>
	 	<i014>2402</i014>
	 	<i018>6011</i018>
	 	<i022>0100</i022>
	 	<i023>000</i023>
	 	<i025>02</i025>
	 	<i026>04</i026>
	 	<i032>437783</i032>
	 	<i037>293629234065</i037>
	 	<i041>TERMID01</i041>
	 	<i042>IDDQD MERCH ID</i042>
	 	<i043>IDDQD AM. 341215574     341215574 MSKRU</i043>
	 	<i049>643</i049>
	 	<i053>9801100001000000</i053>
	 	<i120>UD009TF0040431</i120>
	 </ISO8583-87>
 </RequestInput>
 */

isokat_rc_t xml_serialize_request(msg_common_t *msg, char **buf, int32_t *n_bytes)
{
	isokat_rc_t rc = OK;

	if(msg == NULL || buf == NULL || n_bytes == NULL)
		return VALUE_ERROR;

	*n_bytes = -1;
	xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
	xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "RequestInput");
	xmlDocSetRootElement(doc, root_node);

	for(size_t i = 0; i < MAX_DE_INDEX; i++){
		if(msg->elements[i] != NULL) {
			char node_name[8] = {0};
			snprintf(node_name, 8, "i%03lu", i);
			xmlNewChild(root_node, NULL, BAD_CAST node_name, BAD_CAST msg->elements[i]);
		} 
	}

	xmlDocDumpMemory(doc, (xmlChar**) buf, n_bytes);
	//ZF_LOGD("%d bytes serialized: %s", *n_bytes, *buf);

	xmlFreeDoc(doc);
	return rc;
}