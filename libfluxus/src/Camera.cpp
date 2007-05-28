// Copyright (C) 2005 Dave Griffiths
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include "Camera.h"

using namespace fluxus;
	
Camera::Camera() :
m_Initialised(false),
m_Ortho(false),
m_CameraAttached(NULL),
m_CameraLag(0),
m_Up(-1),
m_Down(1),
m_Left(-0.75),
m_Right(0.75),
m_Front(1),
m_Back(10000),
m_OrthZoom(1.0f)
{
	// default camera position
	m_Transform.translate(0,0,-10);
}

Camera::~Camera()
{
}

void Camera::DoProjection()
{
	if (m_Ortho) glOrtho(m_Down*m_OrthZoom,m_Up*m_OrthZoom,m_Right*m_OrthZoom,m_Left*m_OrthZoom,m_Front,m_Back);
  	else glFrustum(m_Up,m_Down,m_Left,m_Right,m_Front,m_Back);
}

void Camera::DoCamera()
{
	glMultMatrixf(m_Transform.arr());

	if (m_CameraAttached)
	{
		if (m_CameraLag!=0)
		{
			m_LockedMatrix.blend(m_CameraAttached->GetState()->Transform.inverse(),m_CameraLag);
		}
		else
		{
			m_LockedMatrix=m_CameraAttached->GetState()->Transform.inverse();
		}

		glMultMatrixf(m_LockedMatrix.arr());		
	}
}

void Camera::LockCamera(Primitive *p)
{
     m_CameraAttached=p;
}

dMatrix Camera::GetProjection()
{
	dMatrix Projection;
	glGetFloatv(GL_PROJECTION_MATRIX,Projection.arr());
	return Projection;
}