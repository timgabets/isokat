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

<RequestResponse>
  <Header>
    <MessageID>430173293629234065</MessageID>
    <CorrelationID>430173293629234065</CorrelationID>
    <SystemID>IDDQD</SystemID>
  </Header>
  <Result>
    <Code>0</Code>
    <Description>OK</Description>
  </Result>
  <ISO8583-87>
    <i000>0110</i000>
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
    <i026>4</i026>
    <i032>437783</i032>
    <i037>293629234065</i037>
    <i039>91</i039>
    <i041>TERMID01</i041>
    <i042>IDDQD MERCH ID</i042>
    <i043>IDDQD AM. 341215574     341215574 MSKRU</i043>
    <i049>643</i049>
    <i053>9801100001000000</i053>
    <i096>0000293629234065</i096>
  </ISO8583-87>
</RequestResponse>
 */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "formats/xml.h"

Test(xml, xml_serialize_request_nullptr)
{
    msg_common_t *msg = common_msg_new();
    char *buf = NULL;
    int32_t n_bytes = -1; 

    cr_assert(eq(int, xml_serialize_request(NULL, &buf, &n_bytes), VALUE_ERROR));
    cr_assert(eq(int, xml_serialize_request(msg, NULL, &n_bytes), VALUE_ERROR));
    cr_assert(eq(int, xml_serialize_request(msg, &buf, NULL), VALUE_ERROR));

    common_msg_free(msg);
}

Test(xml, xml_serialize_request_dummy)
{   
    msg_common_t* msg = common_msg_new();
    msg->elements[0] = strdup("0120");
    msg->elements[2] = strdup("4444000011112222");

    char *buf = NULL;
    int32_t n_bytes = 0; 

    cr_assert(eq(int, xml_serialize_request(msg, &buf, &n_bytes), OK));
    cr_expect(ne(ptr, buf, NULL));
    cr_expect(ne(int, n_bytes, 0));
    cr_expect(eq(str, buf, (char*)"<?xml version=\"1.0\"?>\n<RequestInput><i000>0120</i000><i002>4444000011112222</i002></RequestInput>\n"));

    common_msg_free(msg);
    free(buf);
}
