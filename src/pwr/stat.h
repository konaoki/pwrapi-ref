/* 
 * Copyright 2014-2015 Sandia Corporation. Under the terms of Contract
 * DE-AC04-94AL85000, there is a non-exclusive license for use of this work 
 * by or on behalf of the U.S. Government. Export of this program may require
 * a license from the United States Government.
 *
 * This file is part of the Power API Prototype software package. For license
 * information, see the LICENSE file in the top level directory of the
 * distribution.
*/

#ifndef _PWR_STAT_H
#define _PWR_STAT_H

#include <assert.h>

#include "pwr.h"
#include "group.h"
#include "object.h"

namespace PowerAPI {

class Grp;
class Object;
class Cntxt;

class Stat {
	typedef double (*OpFuncPtr)(std::vector<double>&);
  public:
	Stat( Cntxt* ctx, Object* obj, PWR_AttrName name, OpFuncPtr ptr,
															double hz ) 
	  : m_ctx( ctx), m_obj(obj), m_grp(NULL), m_attrName( name ), 
	    opPtr( ptr ), m_period( 1 / hz ),
		m_startTime(PWR_TIME_NOT_SET), m_stopTime(PWR_TIME_NOT_SET) { }

	Stat( Cntxt* ctx, Grp* grp, PWR_AttrName name, OpFuncPtr ptr, double hz ) 
	  : m_ctx( ctx), m_obj(NULL), m_grp(grp), m_attrName( name ),
	    opPtr( ptr ), m_period( 1/ hz), 
		m_startTime(PWR_TIME_NOT_SET), m_stopTime(PWR_TIME_NOT_SET) { }
	virtual ~Stat() {}

	virtual int start() = 0;
	virtual int stop() = 0; 
	virtual int clear() = 0;
	virtual int getValue( double* value, PWR_StatTimes* statTimes ) = 0;
	virtual int getValues( double value[], PWR_StatTimes statTimes[] ) = 0;

	Cntxt* getCtx() {
		return m_ctx;
	}


  protected:
	Cntxt*			m_ctx;
	Object*			m_obj;
	Grp*			m_grp;
	PWR_AttrName	m_attrName;
	OpFuncPtr		opPtr;
    double 			m_period;
    double 			m_startTime;
    double 			m_stopTime;
};

}

#endif
