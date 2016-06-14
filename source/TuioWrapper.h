/*
	TUIO Pure Data External - part of the reacTIVision project
	http://reactivision.sourceforge.net/

	Copyright (c) 2005-2016 Martin Kaltenbrunner <martin@tuio.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef INCLUDED_TuioWrapper_H
#define INCLUDED_TuioWrapper_H

#include "TuioListener.h"
#include "TuioClient.h"
#include "m_pd.h"

using namespace TUIO;

class TuioWrapper : public TuioListener { 
	
	public:
		TuioWrapper(int p);
		~TuioWrapper() {};

		void addOutlet(t_outlet *m,  t_outlet *r);
		void removeOutlet(t_outlet *m,  t_outlet *r);
		bool outletCount();
	
		void start();
		void stop();
		bool isRunning() { return running; };

		int getPort() { return udp_port; };
	
		void addTuioObject(TuioObject *tuioObject);
		void updateTuioObject(TuioObject *tuioObject);
		void removeTuioObject(TuioObject *tuioObject);
	
		void addTuioCursor(TuioCursor *tuioCursor);
		void updateTuioCursor(TuioCursor *tuioCursor);
		void removeTuioCursor(TuioCursor *tuioCursor);

		void addTuioBlob(TuioBlob *tuioBlob);
		void updateTuioBlob(TuioBlob *tuioBlob);
		void removeTuioBlob(TuioBlob *tuioBlob);
	
		void refresh(TuioTime frameTime);

	private:

  		TuioClient *client;
		std::list<t_outlet*> message_outlet;
		std::list<t_outlet*> refresh_outlet;
		int udp_port;
		bool running;
};

#endif /* INCLUDED_TuioWrapper_H */
