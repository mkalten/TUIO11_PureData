TUIO PureData Client 1.1.5
Copyright (c) 2005-2015 Martin Kaltenbrunner <martin@tuio.org>

Demo Patch:
-----------
This package contains a simple patch that receives and decodes
TUIO messages reveived from any TUIO enabled tracker or a TUIO simulator.

The TuioClient object takes an alternative port number as 
an optional argument. The default TUIO port is 3333.

There are two outputs, the first one is sending all relevant
TUIO events such as addObject, updateObject and removeObject
as well as addCursor, updateCursor and removeCursor and
addBlob, updateBlob and removeBlob.

The second output sends simple bangs for each fully received
frame, and every second while no new messages are received, 
in order to indicate that the connection is still alive.

The list format of the messages received at the first output
are in analogy to the TUIO message format:

addObject session_id symbol_id xpos ypos angle
updateObject session_id symbol_id xpos ypos angle xspeed yspeed rspeed maccel raccel
removeObject session_id symbol_id

addCursor session_id cursor_id xpos ypos
updateCursor session_id cursor_id xpos ypos xspeed yspeed maccel
removeCursor session_id cursor_id

addBlob session_id symbol_id xpos ypos angle
updateBlob session_id symbol_id xpos ypos angle width height area xspeed yspeed rspeed maccel raccel
removeBlob session_id symbol_id

Each object, cursor or blob is identified with a unique session ID, that is only maintained
over its lifetime. Additionally each object carries a symbol ID that corresponds
to its attached fiducial marker number. The cursor ID of the cursor object is always
a number in the range of all currently detected cursor blobs.

Binaries:
---------
This package includes binaries for Windows NT or later.
and Mac OS X 10.5 or later as Universal binary.

Source Code:
------------
The TuioClient external comes with its full source code which can be
built under Windows, Mac OS X as well as all Linux or Unix flavors.
In order to compile the external for your platform, type "make"
folloed by "pd_linux", "pd_darwin" or "pd_nt" depending on your platform.
For convenience the Windows and Mac OS X binaries are included.

License:
--------
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.
 
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

