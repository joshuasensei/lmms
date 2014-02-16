/*
 * dynamics_processor.h - dynamics_processor effect-plugin
 *
 * Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
 * Copyright (c) 2006-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 *
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef _DYNPROC_H
#define _DYNPROC_H

#include "Effect.h"
#include "effect_lib.h"
#include "dynamics_processor_controls.h"



class dynProcEffect : public Effect
{
public:
	dynProcEffect( Model * _parent,
			const Descriptor::SubPluginFeatures::Key * _key );
	virtual ~dynProcEffect();
	virtual bool processAudioBuffer( sampleFrame * _buf,
							const fpp_t _frames );

	virtual EffectControls * controls()
	{
		return( &m_dpControls );
	}


private:

	dynProcControls m_dpControls;

// this member array is needed for peak detection 
	float currentPeak[2];

	friend class dynProcControls;

} ;





#endif
