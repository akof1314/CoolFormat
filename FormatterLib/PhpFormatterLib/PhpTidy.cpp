#include "PhpTidy.h"
#include "common.h"

#include "exception.h"
#include "settings.h"
#include "formatter.h"
#include "scanner.h"
#include "parser.h"

/* globals */
CSettings  *settings  = NULL;
CFormatter *formatter = NULL;
CScanner   *scanner   = NULL;
CParser    *parser    = NULL;
namespace PhpFormatter{
PhpTidy::PhpTidy(void)
{
}

PhpTidy::~PhpTidy(void)
{
}

bool PhpFormatter::PhpTidy::PhpTidyMain( const char* pSourceIn, const char *pOptions, string &strOut, string &strErr)
{
	try {
		/* create settings class */
		settings = new CSettings();
		if (settings == NULL) {
			throw new CException(E_MEMORY);
		}

		/* create formatter class */
		formatter = new CFormatter();
		if (formatter == NULL) {
			throw new CException(E_MEMORY);
		}

		/* create scanner class */
		scanner = new CScanner();
		if (scanner == NULL) {
			throw new CException(E_MEMORY);
		}

		/* create parser class */
		parser = new CParser();
		if (parser == NULL) {
			throw new CException(E_MEMORY);
		}

		/* init settings */
		settings->InitFromOptions(pOptions);
		

		/* init formatter */
		formatter->Init();

		/* init scanner */
		scanner->Init(pSourceIn);

		/* init parser */
		//CParser->Init();

		/* start formatting */
		formatter->Run(strOut);
	}

	/* catch exceptions */
	catch (CException *exception) {

		/* show message */
		if (!settings->quiet)
		{
			strErr = exception->message;
		}

		/* delete classes */
		if (settings != NULL) {
			delete settings;
		}

		if (formatter != NULL) {
			delete formatter;
		}

		if (scanner != NULL) {
			delete scanner;
		}

		if (parser != NULL) {
			delete parser;
		}

		return false;
	}

	

	/* delete classes */
	delete settings;
	delete formatter;
	delete scanner;
	delete parser;

	return true;
}
}