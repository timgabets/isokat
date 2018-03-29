#include <stdio.h>
#include <libxml/xmlreader.h>
#include "xmlparser.hh"

static void processNode(xmlTextReaderPtr reader)
{
	const xmlChar* name = xmlTextReaderConstName(reader);
	if (name == NULL)
		name = BAD_CAST "--";

	const xmlChar* value = xmlTextReaderConstValue(reader);

	printf("%d %d %s %d %d",
	       xmlTextReaderDepth(reader),
	       xmlTextReaderNodeType(reader),
	       name,
	       xmlTextReaderIsEmptyElement(reader),
	       xmlTextReaderHasValue(reader));
	if (value == NULL)
		printf("\n");
	else {
		if (xmlStrlen(value) > 40)
			printf(" %.40s...\n", value);
		else
			printf(" %s\n", value);
	}
}

static void streamFile(const char *filename)
{
	xmlTextReaderPtr reader = xmlReaderForFile(filename, NULL, 0);
	if (reader != NULL) {
		int ret = xmlTextReaderRead(reader);
		while (ret == 1) {
			processNode(reader);
			ret = xmlTextReaderRead(reader);
		}
		xmlFreeTextReader(reader);
		if (ret != 0) {
			fprintf(stderr, "%s : failed to parse\n", filename);
		}
	} else {
		fprintf(stderr, "Unable to open %s\n", filename);
	}
}

void parseXmlFile(const char* filename)
{
	LIBXML_TEST_VERSION

	streamFile(filename);
	xmlCleanupParser();
	xmlMemoryDump();
}
