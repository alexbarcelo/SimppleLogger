//============================================================================
// Name        : logtest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SimppleLogger.hpp"

int main() {
	pplelog::SimppleLogger &logger = pplelog::getLogger("main");

	pplelog::setLogLevel("secondLogger", pplelog::FATAL);

	pplelog::SimppleLogger &log2 = pplelog::getLogger("secondLogger");

	pplelog::SimppleLogger &log2bis = pplelog::getLogger("secondLogger");

	pplelog::SimppleLogger &logn = pplelog::getLogger("a_logger");

	pplelog::SimppleLogger &logA = pplelog::getLogger("loggerA");
	pplelog::setDefaultLevel(pplelog::INFO);
	logA.setLogLevel(pplelog::TRACE);
	pplelog::SimppleLogger &logB = pplelog::getLogger("loggerB");


	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
	logger.log("This is a string and there is no magic");

	STDLOG_DEBUG(logger, "Hello! " << 1234 << 'c' << " this is " << &logger);
	STDLOG_DEBUG(log2, "Hello!");
	STDLOG_DEBUG(log2bis, "Hello without fooling!");
	STDLOG_DEBUG(logn, "Hello from n_th logger!");

	STDLOG_TRACE(logA, "AaA");
	STDLOG_DEBUG(logB, "BbB");


	return 0;
}
