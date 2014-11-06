/*
 TUIO PureData External
 Copyright (c) 2005-2014 Martin Kaltenbrunner <martin@tuio.org>
 
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

#include "TuioWrapper.h"
	
TuioWrapper::TuioWrapper(int p) {

	udp_port = p;
	running = false;
}

void TuioWrapper::addOutlet(t_outlet *m,  t_outlet *r) {
	message_outlet.push_back(m);
	refresh_outlet.push_back(r);	
}

void TuioWrapper::removeOutlet(t_outlet *m,  t_outlet *r) {
	std::list<t_outlet*>::iterator m_outlet = find(message_outlet.begin(), message_outlet.end(), m);
	if (m_outlet!=message_outlet.end()) message_outlet.remove(m);

	std::list<t_outlet*>::iterator r_outlet = find(refresh_outlet.begin(), refresh_outlet.end(), r);
	if (r_outlet!=refresh_outlet.end()) refresh_outlet.remove(r);
}

bool TuioWrapper::outletCount() {
	return message_outlet.size();
}

void TuioWrapper::addTuioObject(TuioObject *tobj) {
	
	t_atom message[5];
	SETFLOAT(&message[0],(float)tobj->getSessionID());
	SETFLOAT(&message[1],(float)tobj->getSymbolID());
	SETFLOAT(&message[2],tobj->getX());
	SETFLOAT(&message[3],tobj->getY());
	SETFLOAT(&message[4],tobj->getAngle());
	
	if (sys_trylock()==0) {
		for(std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"addObject"), 5, message);
		} sys_unlock();
	} //else post("oops");
}

void TuioWrapper::updateTuioObject(TuioObject *tobj) {

	t_atom message[10];
	SETFLOAT(&message[0],(float)tobj->getSessionID());
	SETFLOAT(&message[1],(float)tobj->getSymbolID());
	SETFLOAT(&message[2],tobj->getX());
	SETFLOAT(&message[3],tobj->getY());
	SETFLOAT(&message[4],tobj->getAngle());
	SETFLOAT(&message[5],tobj->getXSpeed());
	SETFLOAT(&message[6],tobj->getYSpeed());
	SETFLOAT(&message[7],tobj->getRotationSpeed());
	SETFLOAT(&message[8],tobj->getMotionAccel());
	SETFLOAT(&message[9],tobj->getRotationAccel());
	
	if (sys_trylock()==0) {
		for (std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"updateObject"), 10, message);
		}
		sys_unlock();
	} //else post("oops");
}

void TuioWrapper::removeTuioObject(TuioObject *tobj) {

	t_atom message[2];
	SETFLOAT(&message[0],(float)tobj->getSessionID());
	SETFLOAT(&message[1],(float)tobj->getSymbolID());
	if (sys_trylock()==0) {
		for(std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"removeObject"), 2, message);
		} sys_unlock();
	} //else post("oops");
}

void TuioWrapper::addTuioCursor(TuioCursor *tcur) {

	t_atom message[4];
	SETFLOAT(&message[0],(float)tcur->getSessionID());
	SETFLOAT(&message[1],(float)tcur->getCursorID());
	SETFLOAT(&message[2],tcur->getX());
	SETFLOAT(&message[3],tcur->getY());
	
	if (sys_trylock()==0) {
		for(std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"addCursor"), 4, message);
		}
		sys_unlock();	
	} //else post("oops");
}

void TuioWrapper::updateTuioCursor(TuioCursor *tcur) {

	t_atom message[7];
	SETFLOAT(&message[0],(float)tcur->getSessionID());
	SETFLOAT(&message[1],(float)tcur->getCursorID());
	SETFLOAT(&message[2],tcur->getX());
	SETFLOAT(&message[3],tcur->getY());
	SETFLOAT(&message[4],tcur->getXSpeed());
	SETFLOAT(&message[5],tcur->getYSpeed());
	SETFLOAT(&message[6],tcur->getMotionAccel());
	
	if (sys_trylock()==0) {
		for(std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"updateCursor"), 7, message);
		}
		sys_unlock();
	} //else post("oops");
}

void TuioWrapper::removeTuioCursor(TuioCursor *tcur) {
	
	t_atom message[2];
	SETFLOAT(&message[0],(float)tcur->getSessionID());
	SETFLOAT(&message[1],(float)tcur->getCursorID());
	if (sys_trylock()==0) {
		for(std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"removeCursor"), 2, message);
		} sys_unlock();
	} //else post("oops");
}

void TuioWrapper::addTuioBlob(TuioBlob *tblb) {
	
	t_atom message[8];
	SETFLOAT(&message[0],(float)tblb->getSessionID());
	SETFLOAT(&message[1],(float)tblb->getBlobID());
	SETFLOAT(&message[2],tblb->getX());
	SETFLOAT(&message[3],tblb->getY());
	SETFLOAT(&message[4],tblb->getAngle());
	SETFLOAT(&message[5],tblb->getWidth());
	SETFLOAT(&message[6],tblb->getHeight());
	SETFLOAT(&message[7],tblb->getArea());
	
	if (sys_trylock()==0) {
		for(std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"addBlob"), 8, message);
		} sys_unlock();
	} //else post("oops");
}

void TuioWrapper::updateTuioBlob(TuioBlob *tblb) {
	
	t_atom message[13];
	SETFLOAT(&message[0],(float)tblb->getSessionID());
	SETFLOAT(&message[1],(float)tblb->getBlobID());
	SETFLOAT(&message[2],tblb->getX());
	SETFLOAT(&message[3],tblb->getY());
	SETFLOAT(&message[4],tblb->getAngle());
	SETFLOAT(&message[5],tblb->getWidth());
	SETFLOAT(&message[6],tblb->getHeight());
	SETFLOAT(&message[7],tblb->getArea());
	SETFLOAT(&message[8],tblb->getXSpeed());
	SETFLOAT(&message[9],tblb->getYSpeed());
	SETFLOAT(&message[10],tblb->getRotationSpeed());
	SETFLOAT(&message[11],tblb->getMotionAccel());
	SETFLOAT(&message[12],tblb->getRotationAccel());
	
	if (sys_trylock()==0) {
		for (std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"updateBlob"), 13, message);
		} sys_unlock();
	} //else post("oops");
}

void TuioWrapper::removeTuioBlob(TuioBlob *tblb) {
	
	t_atom message[2];
	SETFLOAT(&message[0],(float)tblb->getSessionID());
	SETFLOAT(&message[1],(float)tblb->getBlobID());
	
	if (sys_trylock()==0) {
		for(std::list<t_outlet*>::iterator outlet = message_outlet.begin(); outlet!=message_outlet.end(); outlet++) {
			outlet_anything(*outlet, gensym((char*)"removeBlob"), 2, message);
		} sys_unlock();
	} //else post("oops");
}

void TuioWrapper::refresh(TuioTime frameTime) {

	if (sys_trylock()==0) {
		for(std::list<t_outlet*>::iterator outlet = refresh_outlet.begin(); outlet!=refresh_outlet.end(); outlet++) {
			outlet_bang(*outlet);
		} sys_unlock();
	} //else post("oops");
}

void TuioWrapper::start() {

	if (!running) {
		client = new TuioClient(udp_port);
		client->addTuioListener(this);
		client->connect();
		if (client->isConnected()) running = true;
	}
}

void TuioWrapper::stop() {
	
	if (running) {
		client->removeTuioListener(this);
		client->disconnect();
		delete client;
		running = false;
	}
}



