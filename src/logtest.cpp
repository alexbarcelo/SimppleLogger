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
	pplelog::SimppleLogger &logA = pplelog::getLogger("main");
	pplelog::SimppleLogger &logB = pplelog::getLogger("mainB", "main");
	pplelog::SimppleLogger &logC = pplelog::getLogger("mainC");
	pplelog::setParent("mainC", "main");
	logA.setLogLevel(pplelog::DEBUG);
	pplelog::SimppleLogger &logD = pplelog::getLogger("mainD");
	logD.setParent(logA);
	pplelog::SimppleLogger &logE = pplelog::getLogger("mainE");
	logE.setParent("main");

	logE.setLogLevel(pplelog::TRACE);
	logD.setLogLevel(pplelog::DEBUG);
	logC.setLogLevel(pplelog::INFO);

	STDLOG_INFO(logA, "Hello! " << 1234 << 'c' << " this is " << &logA);
	STDLOG_INFO(logB, "Hello!");
	STDLOG_INFO(logC, "Hello without fooling!");
	STDLOG_INFO(logD, "Hello from n_th logger!");
	STDLOG_INFO(logE, "Hello from E logger!");


	STDLOG_DEBUG(logA, "Hello! " << 1234 << 'c' << " this is " << &logA);
	STDLOG_DEBUG(logB, "Hello!");
	STDLOG_DEBUG(logC, "Hello without fooling!");
	STDLOG_DEBUG(logD, "Hello from n_th logger!");
	STDLOG_DEBUG(logE, "Hello from E logger!");

	STDLOG_TRACE(logA, "Hello! " << 1234 << 'c' << " this is " << &logA);
	STDLOG_TRACE(logB, "Hello!");
	STDLOG_TRACE(logC, "Hello without fooling!");
	STDLOG_TRACE(logD, "Hello from n_th logger!");
	STDLOG_TRACE(logE, "Hello from E logger!");


	return 0;
}
