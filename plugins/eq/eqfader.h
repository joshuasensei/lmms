/* eqfader.h - defination of EqFader class.
*
* Copyright (c) 2014 David French <dave/dot/french3/at/googlemail/dot/com>
*
* This file is part of LMMS - http://lmms.io
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

#ifndef EQFADER_H
#define EQFADER_H
#include "Fader.h"
#include "EffectControls.h"
#include "MainWindow.h"
#include "qwidget.h"
#include "TextFloat.h"
#include "qlist.h"



class EqFader : public Fader
{

public:
	Q_OBJECT
public:
	EqFader( FloatModel * model, const QString & name, QWidget * parent, float* lPeak, float* rPeak ) :
		Fader( model, name, parent)
	{
		setMinimumSize( 23, 116 );
		setMaximumSize( 23, 116 );
		resize( 23, 116 );
		m_lPeak = lPeak;
		m_rPeak = rPeak;
		connect( Engine::mainWindow(), SIGNAL( periodicUpdate() ), this, SLOT( updateVuMeters() ) );
		m_text = 0;
		QList<TextFloat*> tfs = Engine::mainWindow()->findChildren<TextFloat*>();
		m_text = tfs.last();
		if(m_text)
		{
			printf("found text float\n");
		}
		connect(model , SIGNAL (dataChanged()) , this, SLOT (updateText () ));
		m_model = model;
	}




	~EqFader()
	{
	}


private slots:

	void updateVuMeters()
	{
		const float opl = getPeak_L();
		const float opr = getPeak_R();
		const float fall_off = 1.2;
		if( *m_lPeak > opl )
		{
			setPeak_L( *m_lPeak );
			*m_lPeak = 0;
		}
		else
		{
			setPeak_L( opl/fall_off );
		}

		if( *m_rPeak > opr )
		{
			setPeak_R( *m_rPeak );
			*m_rPeak = 0;
		}
		else
		{
			setPeak_R( opr/fall_off );
		}
		update();
	}

	void updateText()
	{
		m_text->setText(QString()+m_model->value());
	}


private:
	float* m_lPeak;
	float* m_rPeak;
	TextFloat* m_text;
	FloatModel* m_model;

};
#endif // EQFADER_H
