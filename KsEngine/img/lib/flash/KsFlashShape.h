/*
    Ming, an SWF output library
    Copyright (C) 2001  Opaque Industries - http://www.opaque.net/

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* shape.h
 * 
 * $Id: KsFlashShape.h,v 1.1.1.1 2005/10/05 17:33:26 TSUKASA Exp $
 *
 * Notice: This header file contains declarations of functions and types that
 * are just used internally. All library functions and types that are supposed
 * to be publicly accessable are defined in ./src/ming.h.
 */

#ifndef SWF_SHAPE_H_INCLUDED
#define SWF_SHAPE_H_INCLUDED

#include "ming.h"
#include "output.h"


#define SWF_SHAPE_NEWSTYLEFLAG	 (1<<4)
#define SWF_SHAPE_LINESTYLEFLAG	 (1<<3)
#define SWF_SHAPE_FILLSTYLE1FLAG (1<<2)
#define SWF_SHAPE_FILLSTYLE0FLAG (1<<1)
#define SWF_SHAPE_MOVETOFLAG	 (1<<0)

#define NOFILL NULL


/* returns a shape containing the bitmap in a filled rect */
SWFShape newSWFShapeFromBitmap(SWFBitmap bitmap);

void SWFShape_addStyleHeader(SWFShape shape);

int SWFShape_getScaledPenX(SWFShape shape);

int SWFShape_getScaledPenY(SWFShape shape);

void SWFShape_moveScaledPenTo(SWFShape shape, int x, int y);

void SWFShape_moveScaledPen(SWFShape shape, int x, int y);

void SWFShape_drawScaledLineTo(SWFShape shape, int x, int y);

void SWFShape_drawScaledLine(SWFShape shape, int dx, int dy);

void SWFShape_drawScaledCurveTo(SWFShape shape,
			        int controlx, int controly,
			        int anchorx, int anchory);

void SWFShape_drawScaledCurve(SWFShape shape,
			      int controldx, int controldy,
			      int anchordx, int anchordy);

void SWFShape_drawScaledGlyph(SWFShape shape,
	    		      SWFFont font, unsigned short c, int size);

SWFOutput
SWFShape_getOutput(SWFShape shape);

void
SWFShape_getFills(SWFShape shape, SWFFillStyle** outFills, int* outNFills);

void
SWFShape_getLines(SWFShape shape, SWFLineStyle** outLines, int* outNLines);

void
SWFShape_setMorphFlag(SWFShape shape);

#endif /* SWF_SHAPE_H_INCLUDED */
