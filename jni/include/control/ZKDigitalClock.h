/*
 * ZKDigitalClock.h
 *
 *  Created on: Sep 19, 2017
 *      Author: guoxs
 */

#ifndef _CONTROL_ZKDIGITALCLOCK_H_
#define _CONTROL_ZKDIGITALCLOCK_H_

#include "ZKTextView.h"

class ZKDigitalClock : public ZKTextView {
public:
	ZKDigitalClock(HWND hParentWnd);
	virtual ~ZKDigitalClock();

protected:
	virtual void onBeforeCreateWindow(const Json::Value &json);
	virtual void onAfterCreateWindow(const Json::Value &json);
	virtual const char* getClassName() const { return ZK_DIGITALCLOCK; }

	virtual void onDraw(HDC hdc);
	virtual void onTimer(int id);

	void _section_(zk) drawClock(HDC hdc);

private:
	void _section_(zk) parseDigitalClockAttributeFromJson(const Json::Value &json);
	bool checkTimeUpdate();

private:
	bool mIsBeated;		// 冒号跳动
	bool mShowColon;	// 显示冒号
	bool mIs24HourFormat;
	bool mHasWithSec;
	int mClockColor;
};

#endif /* _CONTROL_ZKDIGITALCLOCK_H_ */
