/*
 TUIO PureData External
 Copyright (c) 2005-2016 Martin Kaltenbrunner <martin@tuio.org>
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library.
*/

#include <list>
#include <algorithm>
#include <TuioWrapper.h>

extern "C"{
	#include "m_pd.h"
	#include <stdio.h>
	#include <string.h>
	
	static t_class *TuioClient_class;
	std::list<TuioWrapper*> TuioClientList;
	
	typedef struct TuioClientBox
	{
		t_object x_obj;
		int port;
		t_outlet *message_outlet;
		t_outlet *refresh_outlet;
	} t_TuioClientBox;
	
	void *TuioClient_new(t_floatarg f)
	{
		t_TuioClientBox *x = (t_TuioClientBox *)pd_new(TuioClient_class);
		x->message_outlet = outlet_new(&x->x_obj, gensym((char*)"list"));
		x->refresh_outlet = outlet_new(&x->x_obj, gensym((char*)"bang"));		
		
		x->port = (int)f;
		if(x->port<1024) x->port=3333;	
		
		TuioWrapper *wrapper = NULL;
		std::list<TuioWrapper*>::iterator iter;
		for (iter=TuioClientList.begin(); iter != TuioClientList.end(); iter++) {
			if ((*iter)->getPort()==x->port) {
				wrapper = *iter;
				break;
			}
		}
		
		if (wrapper==NULL) wrapper = new TuioWrapper(x->port);
		
		wrapper->addOutlet(x->message_outlet, x->refresh_outlet);
		
		if (!wrapper->isRunning()) {
			wrapper->start();
			if (wrapper->isRunning()) {
				TuioClientList.push_back(wrapper);
				post("TuioClient: started listening to TUIO/UDP port %d",x->port);
			} else {
				delete wrapper;
				post("TuioClient: could not bind to TUIO/UDP port %d",x->port);
			}			

		}
		
		return (void *)x;
	}
	
	static void TuioClient_free(t_TuioClientBox *x)
	{
		TuioWrapper *wrapper = NULL;
		std::list<TuioWrapper*>::iterator iter;
		for (iter=TuioClientList.begin(); iter != TuioClientList.end(); iter++) {
			if ((*iter)->getPort()==x->port) {
				wrapper = *iter;
				wrapper->removeOutlet(x->message_outlet, x->refresh_outlet);
				
				if (wrapper->outletCount()==0) {
					wrapper->stop();
					TuioClientList.erase(iter);
					delete wrapper;
					wrapper = NULL;
					post("TuioClient: stopped listening to TUIO/UDP port %d",x->port);
				}
				break;
			}
		}	
	}
	
	void TuioClient_setup(void)
	{
		TuioClient_class = class_new(gensym((char*)"TuioClient"), (t_newmethod)TuioClient_new,(t_method)TuioClient_free, sizeof(t_TuioClientBox), 0, A_DEFFLOAT, 0);
	}
}
