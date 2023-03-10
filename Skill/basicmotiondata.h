#ifndef BASICMOTIONDATA_H
#define BASICMOTIONDATA_H
#include "../Stdafx.h"
Angle aStartWalk[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ //-0.01,0.21
		JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(90, 0),
				JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						38.95, 0), JointInfo(-81.79, 0), JointInfo(46.82, 0),
				JointInfo(-0, 0), JointInfo(-45, 0), JointInfo(-90, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-30, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(38.95, 0),
				JointInfo(-81.79, 0), JointInfo(46.82, 0), JointInfo(-0, 0) },
		{ //0.175 for short cycle walk
		JointInfo(0, 0), JointInfo(-70, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						25.84, 0), JointInfo(-66.05, 0), JointInfo(40.21, 0),
				JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-70, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-30, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(25.84, 0), JointInfo(
						-66.05, 0), JointInfo(40.21, 0), JointInfo(-0, 0) },
		{ //0.190 for long cycle walk
		JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-20, 0), JointInfo(90, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						25.31, 0), JointInfo(-80.09, 0), JointInfo(54.78, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(
						20, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(25.31, 0), JointInfo(
						-80.09, 0), JointInfo(54.78, 0), JointInfo(0, 0) },
		{ ///2fall to forward
		JointInfo(0, 0), JointInfo(-105, 0), JointInfo(0, 0), JointInfo(90, 0),
				JointInfo(45, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(75, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-105, 0), JointInfo(0, 0), JointInfo(
						-90, 0), JointInfo(-45, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(75,
						0), JointInfo(0, 0) },
		{ ///3fall to back
		JointInfo(0, 0), JointInfo(-105, 0), JointInfo(0, 0), JointInfo(90, 0),
				JointInfo(45, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-45, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-105, 0), JointInfo(0, 0), JointInfo(
						-90, 0), JointInfo(-45, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-45,
						0), JointInfo(0, 0) },
		{ ///4
		JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
				JointInfo(45, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						-90, 0), JointInfo(-45, 0), JointInfo(-5, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0) } };
Angle splits[] =
{
{ JointInfo(0, 0), JointInfo(60, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-100, 0), JointInfo(-90, 0), JointInfo(45,
				0), JointInfo(0, 0), JointInfo(-40, 0), JointInfo(0, 0),
		JointInfo(70, 0), JointInfo(60, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-100, 0), JointInfo(90, 0), JointInfo(45, 0),
		JointInfo(0, 0), JointInfo(-40, 0), JointInfo(0, 0), },
{ JointInfo(0, 0), JointInfo(60, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-100, 0), JointInfo(-90, 0), JointInfo(45,
				0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(20, 0),
		JointInfo(70, 0), JointInfo(60, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-100, 0), JointInfo(90, 0), JointInfo(45, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(-20, 0), },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(
		30, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(30, 0), JointInfo(-30,
		0), JointInfo(0, 0) },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
		-30, 0), JointInfo(1, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(1, 0),
		JointInfo(0, 0) },
{ JointInfo(0, 0), JointInfo(60, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-50, 0), JointInfo(-90, 0), JointInfo(45, 0),
		JointInfo(-150, 0), JointInfo(60, 0), JointInfo(0, 0), JointInfo(70, 0),
		JointInfo(60, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(-50, 0), JointInfo(90, 0), JointInfo(45, 0), JointInfo(-150,
				0), JointInfo(60, 0), JointInfo(0, 0), },
{ JointInfo(0, 0), JointInfo(60, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-100, 0), JointInfo(-90, 0), JointInfo(180,
				0), JointInfo(-180, 0), JointInfo(45, 0), JointInfo(25, 0),
		JointInfo(70, 0), JointInfo(60, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-100, 0), JointInfo(90, 0), JointInfo(180,
				0), JointInfo(-180, 0), JointInfo(45, 0), JointInfo(-25, 0), } };

Angle preventFallDown_FORWARD[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ ///////////0
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(90, 0),
				JointInfo(90, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-90, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0) },
		{ //////////////////1
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
						70, 0), JointInfo(-70, 0), JointInfo(70, 0), JointInfo(
						20, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-30,
						0), JointInfo(0, 0), JointInfo(70, 0), JointInfo(-70,
						0), JointInfo(70, 0), JointInfo(-20, 0) },
		{ //////////////////2
		JointInfo(0, 0), JointInfo(-1, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-2, 0), JointInfo(0, 0), JointInfo(6,
						0), JointInfo(-4, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-1, 0), JointInfo(0, 0), JointInfo(
						-0, 0), JointInfo(-0, 0), JointInfo(-2, 0), JointInfo(0,
						0), JointInfo(6, 0), JointInfo(-4, 0), JointInfo(0, 0),
				JointInfo(0, 0) },
		{ //////////////////3
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(2, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-90,
						0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130,
						0), JointInfo(2, 0), JointInfo(0, 0) },
		{ //////////////////4
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(-40, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) },
		{ //////////////////5
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(40, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) },
		{ //////////////////6
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) }

};
Angle preventFallDown_FORWARD1[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ ///////////0
				JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(90, 0),JointInfo(90, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-90, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,0), JointInfo(0, 0) },
				{ //////////////////1
				JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),JointInfo(0, 0),
				JointInfo(-30, 0), JointInfo(0, 0), JointInfo(70, 0), JointInfo(-70, 0), JointInfo(70, 0), JointInfo(20, 0),
				JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0,	0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(-30,0), JointInfo(0, 0),JointInfo(70, 0), JointInfo(-70,0), JointInfo(70, 0), JointInfo(-20, 0) },
				{ //////////////////2
				JointInfo(0, 0),
				JointInfo(-1, 0), JointInfo(0, 0), JointInfo(0, 0),JointInfo(0, 0),
				JointInfo(-2, 0), JointInfo(0, 0), JointInfo(6,0), JointInfo(-4, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0),
				JointInfo(-1, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(-2, 0), JointInfo(0,0), JointInfo(6, 0), JointInfo(-4, 0), JointInfo(0, 0),JointInfo(0, 0) },
				{ //////////////////3
				JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-20, 0), JointInfo(0, 0),JointInfo(0, 0),
				JointInfo(-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(2, 0), JointInfo(0, 0),
				JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(20,0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(-90,0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130,0), JointInfo(2, 0), JointInfo(0, 0) },

		{ //////////////////4
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(-40, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) },
		{ //////////////////5
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(40, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) },
		{ //////////////////6
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) }

};
Angle preventFallDown_FORWARD3[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ ///////////0
		JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(90, 0),JointInfo(90, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-90, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,0), JointInfo(0, 0) },
		{ //////////////////1
		JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),JointInfo(0, 0),
		JointInfo(-30, 0), JointInfo(0, 0), JointInfo(70, 0), JointInfo(-70, 0), JointInfo(70, 0), JointInfo(20, 0),
		JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0,	0), JointInfo(-0, 0), JointInfo(-0, 0),
		JointInfo(-30,0), JointInfo(0, 0),JointInfo(70, 0), JointInfo(-70,0), JointInfo(70, 0), JointInfo(-20, 0) },
		{ //////////////////2
		JointInfo(0, 0),
		JointInfo(-1, 0), JointInfo(0, 0), JointInfo(0, 0),JointInfo(0, 0),
		JointInfo(-2, 0), JointInfo(0, 0), JointInfo(6,0), JointInfo(-4, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0),
		JointInfo(-1, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0),
		JointInfo(-2, 0), JointInfo(0,0), JointInfo(6, 0), JointInfo(-4, 0), JointInfo(0, 0),JointInfo(0, 0) },
		{ //////////////////3
		JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-20, 0), JointInfo(0, 0),JointInfo(0, 0),
		JointInfo(-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(2, 0), JointInfo(0, 0),
		JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(20,0), JointInfo(-0, 0), JointInfo(-0, 0),
		JointInfo(-90,0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130,0), JointInfo(2, 0), JointInfo(0, 0) },
		{ //////////////////4
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(-40, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) },
		{ //////////////////5
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(40, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) },
		{ //////////////////6
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) }

};
Angle preventFallDown_BACK[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
////////一些值是大于最大植的，就用的最大值
		{ ///////////0
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						110, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(110, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) },
		{ ///////////1
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-20, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-20, 0), JointInfo(
						0, 0), JointInfo(100, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0) },
		{ //////////////////2
		JointInfo(0, 0), JointInfo(14.56, 0), JointInfo(0, 0), JointInfo(-5.34,
				0), JointInfo(0, 0), JointInfo(-87.72, 0), JointInfo(0, 0),
				JointInfo(92.25, 0), JointInfo(-99.05, 0), JointInfo(-25.06, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(14.56, 0),
				JointInfo(0, 0), JointInfo(-5.34, 0), JointInfo(-0, 0),
				JointInfo(-87.72, 0), JointInfo(0, 0), JointInfo(92.25, 0),
				JointInfo(-99.05, 0), JointInfo(-25.06, 0), JointInfo(0, 0) },
		{ //////////////////3
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) },
		{ ///////////4
		JointInfo(0, 0), JointInfo(-120, 0), JointInfo(0, 0), JointInfo(-90, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-120, 0), JointInfo(0,
						0), JointInfo(90, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0) },
		{ ///////////5
		JointInfo(0, 0), JointInfo(-135, 0), JointInfo(0, 0), JointInfo(-90, 0),
				JointInfo(90, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-135, 0), JointInfo(0,
						0), JointInfo(90, 0), JointInfo(-90, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0) },
		{ ///////////6
		JointInfo(0, 0), JointInfo(-120, 0), JointInfo(0, 0), JointInfo(-90, 0),
				JointInfo(90, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						20, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-120, 0), JointInfo(0,
						0), JointInfo(90, 0), JointInfo(-90, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(20, 0), JointInfo(0, 0),
				JointInfo(-30, 0), JointInfo(0, 0) }, };

Angle aStandUpForward[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-20, 0), JointInfo(0,
				0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0) },
		{ ///1
		JointInfo(0, 0), JointInfo(-120, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-120, 0), JointInfo(20, 0),
				JointInfo(-0, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0) },
		{ ///2
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20, 0), JointInfo(
						-0, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0) },
		{ ///3
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-25, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20, 0),
				JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(-25, 0), JointInfo(-0, 0), JointInfo(0,
						0), JointInfo(0, 0) },
		{ ///4
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-45, 0), JointInfo(50, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(100, 0), JointInfo(-45, 0),
				JointInfo(50, 0), JointInfo(0, 0) },
		{ ///5
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-45, 0), JointInfo(50, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(100, 0), JointInfo(-45, 0),
				JointInfo(50, 0), JointInfo(0, 0) },
		{ ///6
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-90,
						0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130,
						0), JointInfo(0, 0), JointInfo(0, 0) },
		{ ///7
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(55, 0),
				JointInfo(25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(
						-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ ///8
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(55, 0),
				JointInfo(25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(
						-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ ///9
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						80, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(
						25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-60,
						0), JointInfo(0, 0), JointInfo(80, 0), JointInfo(-130,
						0), JointInfo(55, 0), JointInfo(-25, 0) } };

Angle aStandUpBackward[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						-90, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) },
		{ ///1
		JointInfo(0, 0), JointInfo(-120, 0), JointInfo(-0, 0), JointInfo(-90,
				0), JointInfo(45, 0), JointInfo(-90, 0), JointInfo(0, 0),
				JointInfo(10, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-120, 0), JointInfo(0,
						0), JointInfo(90, 0), JointInfo(-45, 0), JointInfo(-90,
						0), JointInfo(0, 0), JointInfo(10, 0), JointInfo(-0, 0),
				JointInfo(-0, 0), JointInfo(0, 0) },
		{ ///2
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-90, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(-30, 0),
				JointInfo(-10, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(90, 0), JointInfo(-0, 0), JointInfo(
						-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(
						-130, 0), JointInfo(-30, 0), JointInfo(10, 0) },
		{ ///3
		JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0,
						0), JointInfo(0, 0) },
		{ ///4
		JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-90, 0), JointInfo(
						-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0,
						0), JointInfo(0, 0) },
		{ ///5
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-45, 0), JointInfo(50, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(100, 0), JointInfo(-45, 0),
				JointInfo(50, 0), JointInfo(0, 0) },
		{ ///6
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-90,
						0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130,
						0), JointInfo(0, 0), JointInfo(0, 0) },
		{ ///7
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(55, 0),
				JointInfo(25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(
						-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ ///8
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(55, 0),
				JointInfo(25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(
						-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ ///9
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						80, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(
						25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-60,
						0), JointInfo(0, 0), JointInfo(80, 0), JointInfo(-130,
						0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(90,
				0), JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(44.95, 0), JointInfo(-81.79, 0), JointInfo(46.82, 0),
				JointInfo(-0, 0), JointInfo(-42, 0), JointInfo(-90, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-30, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(44.95, 0),
				JointInfo(-81.79, 0), JointInfo(46.82, 0), JointInfo(-0, 0) } };

string standBackUp[] = /// stand up data form seuredSun 
		{ //0
				"(he1 0)(he2 0)(rae1 5.23599)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23599)(lae2 0)(lae3 0)(lae4 0)(rle1 0)(rle2 0)(rle3 5.81781)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.81776)(lle4 0)(lle5 0)(lle6 0)",
//1
				"(he1 0)(he2 0)(rae1 5.236)(rae2 0)(rae3 0)(rae4 0)(lae1 5.236)(lae2 0)(lae3 0)(lae4 0)(rle1 0)(rle2 0)(rle3 5.81777)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.81777)(lle4 0)(lle5 0)(lle6 0)",
//2
				"(he1 0)(he2 0)(rae1 5.23601)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23601)(lae2 0)(lae3 0)(lae4 0)(rle1 0.000671283)(rle2 0.000671283)(rle3 5.81823)(rle4 0)(rle5 0)(rle6 0)(lle1 -0.000671083)(lle2 0)(lle3 5.81823)(lle4 0)(lle5 0)(lle6 0)",
//3
				"(he1 0)(he2 0)(rae1 5.23602)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23602)(lae2 0)(lae3 0)(lae4 0)(1 0.000671284)(rle2 0.000671284)(rle3 5.818)(rle4 0)(rle5 0)(rle6 0)(lle1 -0.000671301)(lle2 0.000727225)(lle3 5.818)(lle4 0)(lle5 0)(lle6 0)",
//4
				"(he1 0)(he2 0)(rae1 5.23682)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23603)(lae2 0)(lae3 0)(lae4 0)(rle1 0.000732312)(rle2 0.000732312)(rle3 5.81858)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0.000727226)(lle3 5.81779)(lle4 0)(lle5 0)(lle6 0)",
//5
				"(he1 0)(he2 0)(rae1 5.23684)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23692)(lae2 0)(lae3 0)(lae4 0)(rle1 0.000799443)(rle2 0.000799443)(rle3 5.81833)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.81841)(lle4 0)(lle5 0)(lle6 0)",
//6
				"(he1 0)(he2 0)(rae1 5.23683)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23682)(lae2 0)(lae3 0)(lae4 0)(rle1 0.000880795)(rle2 0)(rle3 5.81896)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.81895)(lle4 0)(lle5 0)(lle6 0)",
//7
				"(he1 0)(he2 0)(rae1 5.23695)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23695)(lae2 0)(lae3 0)(lae4 0)(rle1 0.000980727)(rle2 -0.00107972)(rle3 5.81868)(rle4 0)(rle5 0)(rle6 0)(lle1 -0.00109091)(lle2 0.00108982)(lle3 5.81868)(lle4 0)(lle5 0)(lle6 0)",
//8
				"(he1 0)(he2 0)(rae1 5.23709)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23709)(lae2 0)(lae3 0)(lae4 0)(rle1 0.00110656)(rle2 -0.00109242)(rle3 5.81846)(rle4 0)(rle5 0)(rle6 0)(lle1 0.000155844)(lle2 -0.000155688)(lle3 5.81846)(lle4 0)(lle5 0)(lle6 0)",
//9
				"(he1 0)(he2 0)(rae1 5.23727)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23727)(lae2 0)(lae3 0)(lae4 0)(rle1 -0.000184427)(rle2 0.00018207)(rle3 5.81815)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.8196)(lle4 0)(lle5 0)(lle6 0)",
//10
				"(he1 0)(he2 0)(rae1 5.23752)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23752)(lae2 0)(lae3 0)(lae4 0)(rle1 0)(rle2 0)(rle3 5.81948)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.81919)(lle4 0)(lle5 0)(lle6 0)",
//11
				"(he1 0)(he2 0)(rae1 5.23787)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23787)(lae2 0)(lae3 0)(lae4 0)(rle1 0)(rle2 0)(rle3 5.82106)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.82113)(lle4 0)(lle5 0)(lle6 0)",
//12
				"(he1 0)(he2 0)(rae1 5.23842)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23842)(lae2 0)(lae3 0)(lae4 0)(rle1 0)(rle2 0)(rle3 5.82071)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.82068)(lle4 0)(lle5 0)(lle6 0)",
//13
				"(he1 0)(he2 0)(rae1 5.23914)(rae2 0)(rae3 0)(rae4 0)(lae1 5.23914)(lae2 0)(lae3 0)(lae4 0)(rle1 0)(rle2 0)(rle3 5.82066)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 5.82067)(lle4 0)(lle5 0)(lle6 0)",
//14
				"(he1 0)(he2 0)(rae1 2.62078)(rae2 0)(rae3 0)(rae4 0)(lae1 2.62078)(lae2 0)(lae3 0)(lae4 0)(rle1 0)(rle2 0)(rle3 2.91034)(rle4 0)(rle5 0)(rle6 0)(lle1 0)(lle2 0)(lle3 2.91034)(lle4 0)(lle5 0)(lle6 0)",
//15
				"(he1 0)(he2 0)(rae1 0.262393)(rae2 0)(rae3 0)(rae4 0)(lae1 0.262393)(lae2 0)(lae3 0)(lae4 0)(rle1 -7.85398)(rle2 0.872665)(rle3 0.291906)(rle4 -11.3446)(rle5 -1.74533)(rle6 -2.18166)(lle1 -7.85398)(lle2 0.872665)(lle3 0.291034)(lle4 -11.3446)(lle5 -1.74533)(lle6 1.309)",
//16
				"(he1 0)(he2 0)(rae1 0.262704)(rae2 0)(rae3 0)(rae4 0)(lae1 0.262704)(lae2 0)(lae3 0)(lae4 0)(rle1 -7.854)(rle2 0.872667)(rle3 0.291422)(rle4 -11.3447)(rle5 -1.74533)(rle6 -2.18167)(lle1 -7.854)(lle2 0.872667)(lle3 0.291519)(lle4 -11.3447)(lle5 -1.74533)(lle6 1.309)",
//17
				"(he1 0)(he2 0)(rae1 0.262779)(rae2 0)(rae3 0)(rae4 0)(lae1 0.262779)(lae2 0)(lae3 0)(lae4 0)(rle1 -8.06892)(rle2 0.872669)(rle3 0.291914)(rle4 -11.9959)(rle5 -1.74643)(rle6 -2.18276)(lle1 -8.06892)(lle2 0.872669)(lle3 0.291902)(lle4 -11.9959)(lle5 -1.74643)(lle6 1.309)",
//18
				"(he1 0)(he2 0)(rae1 0.262909)(rae2 0)(rae3 0)(rae4 0)(lae1 0.261662)(lae2 0)(lae3 0)(lae4 0)(rle1 -8.31454)(rle2 0.872672)(rle3 0.29116)(rle4 -12.7415)(rle5 -1.74644)(rle6 -2.18402)(lle1 -8.31454)(lle2 0.873919)(lle3 0.291162)(lle4 -12.7415)(lle5 -1.74644)(lle6 1.31026)",
//19
				"(he1 0)(he2 0)(rae1 0.261618)(rae2 0)(rae3 0)(rae4 0)(lae1 0.261826)(lae2 0)(lae3 0)(lae4 0)(rle1 -8.63693)(rle2 0.874131)(rle3 0.291817)(rle4 -13.7184)(rle5 -1.74808)(rle6 -2.18567)(lle1 -8.63693)(lle2 0.873923)(lle3 0.291816)(lle4 -13.7184)(lle5 -1.74808)(lle6 1.31172)",
//20
				"(he1 0)(he2 0)(rae1 0.261842)(rae2 0)(rae3 0)(rae4 0)(lae1 0.2618)(lae2 0)(lae3 0)(lae4 0)(rle1 -9.07292)(rle2 0.874137)(rle3 0.292455)(rle4 -15.0398)(rle5 -1.74831)(rle6 -2.18615)(lle1 -9.07292)(lle2 0.874178)(lle3 0.292455)(lle4 -15.0398)(lle5 -1.74831)(lle6 1.31197)",
//21
				"(he1 0)(he2 0)(rae1 0.261798)(rae2 0)(rae3 0)(rae4 0)(lae1 0.261808)(lae2 0)(lae3 0)(lae4 0)(rle1 -9.69852)(rle2 0.874508)(rle3 0.291233)(rle4 -16.9359)(rle5 -1.74901)(rle6 -2.18934)(lle1 -9.69633)(lle2 0.872316)(lle3 0.291233)(lle4 -16.938)(lle5 -1.74901)(lle6 1.31266)",
//22
				"(he1 0)(he2 0)(rae1 0.261797)(rae2 0)(rae3 0)(rae4 0)(lae1 0.261794)(lae2 0)(lae3 0)(lae4 0)(rle1 -10.6773)(rle2 0.87495)(rle3 0.292707)(rle4 -19.9032)(rle5 -1.7499)(rle6 -2.19071)(lle1 -10.6751)(lle2 0.872772)(lle3 0.292707)(lle4 -19.9054)(lle5 -1.75281)(lle6 1.31358)",
//23
				"(he1 0)(he2 0)(rae1 0.261799)(rae2 0)(rae3 0)(rae4 0)(lae1 0.261801)(lae2 0)(lae3 0)(lae4 0)(rle1 -12.4593)(rle2 0.871519)(rle3 0.294341)(rle4 -25.3083)(rle5 -1.75176)(rle6 -2.19458)(lle1 -12.456)(lle2 0.876971)(lle3 0.294341)(lle4 -25.3072)(lle5 -1.75467)(lle6 1.31979)",
//24
				"(he1 0)(he2 0)(rae1 0.1309)(rae2 0)(rae3 0)(rae4 0)(lae1 0.130899)(lae2 0)(lae3 0)(lae4 0)(rle1 -8.50094)(rle2 0.436905)(rle3 0.145172)(rle4 -19.5341)(rle5 -0.878175)(rle6 -1.10183)(lle1 -8.49821)(lle2 0.438543)(lle3 0.145172)(lle4 -19.539)(lle5 -0.881084)(lle6 0.657829)",
//25
				"(he1 0)(he2 0)(rae1 0.01309)(rae2 0)(rae3 0)(rae4 0)(lae1 0.0130901)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.48254)(rle2 0.043576)(rle3 0.0142812)(rle4 -3.87076)(rle5 -0.0884607)(rle6 -0.110602)(lle1 -1.48194)(lle2 0.0434122)(lle3 0.0142812)(lle4 -3.87114)(lle5 -0.0890426)(lle6 0.0668622)",
//26
				"(he1 0)(he2 0)(rae1 0.01309)(rae2 0)(rae3 0)(rae4 0)(lae1 0.01309)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.74544)(rle2 0.0436397)(rle3 0.0148967)(rle4 -5.35957)(rle5 -0.0881037)(rle6 -0.110854)(lle1 -1.74357)(lle2 0.0436579)(lle3 0.0148967)(lle4 -5.3605)(lle5 -0.0890086)(lle6 0.0662628)",
//27
				"(he1 0)(he2 0)(rae1 0.0136355)(rae2 0)(rae3 0)(rae4 0)(lae1 0.0136355)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.74533)(rle2 0.0436326)(rle3 0.014501)(rle4 -5.3602)(rle5 -0.0882531)(rle6 -0.110499)(lle1 -1.74338)(lle2 0.0436304)(lle3 0.014501)(lle4 -5.36117)(lle5 -0.089231)(lle6 0.0658941)",
//28
				"(he1 0)(he2 0)(rae1 0.0130122)(rae2 0)(rae3 0)(rae4 0)(lae1 0.0142588)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.74535)(rle2 0.0436337)(rle3 0.0141349)(rle4 -5.36166)(rle5 -0.0883729)(rle6 -0.110129)(lle1 -1.74313)(lle2 0.0436341)(lle3 0.0141349)(lle4 -5.36277)(lle5 -0.0882333)(lle6 0.0666337)",
//29
				"(he1 0)(he2 0)(rae1 0.0138304)(rae2 0)(rae3 0)(rae4 0)(lae1 0.0136226)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.74535)(rle2 0.0436339)(rle3 0.0150981)(rle4 -5.36202)(rle5 -0.0885376)(rle6 -0.109638)(lle1 -1.74427)(lle2 0.0436338)(lle3 0.0150981)(lle4 -5.36475)(lle5 -0.0885609)(lle6 0.0659807)",
//30
				"(he1 0)(he2 0)(rae1 0.0129422)(rae2 0)(rae3 0)(rae4 0)(lae1 0.0129837)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.74537)(rle2 0.0436341)(rle3 0.0144333)(rle4 -5.36449)(rle5 -0.0887599)(rle6 -0.108975)(lle1 -1.74384)(lle2 0.0436342)(lle3 0.0144333)(lle4 -5.36569)(lle5 -0.0887552)(lle6 0.0653451)",
//31
				"(he1 0)(he2 0)(rae1 0.0142176)(rae2 0)(rae3 0)(rae4 0)(lae1 0.0142072)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.7453)(rle2 0.0436324)(rle3 0.0138449)(rle4 -5.36523)(rle5 -0.0890736)(rle6 -0.108018)(lle1 -1.7435)(lle2 0.0436324)(lle3 0.0138449)(lle4 -5.87762)(lle5 -0.0890749)(lle6 0.0643844)",
//32//
				"(he1 0)(he2 0)(rae1 0.012714)(rae2 0)(rae3 0)(rae4 0)(lae1 0.0127174)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.74532)(rle2 0.0465419)(rle3 0.015748)(rle4 -5.36738)(rle5 -0.0895717)(rle6 -0.109437)(lle1 -1.74301)(lle2 0.043633)(lle3 0.0128385)(lle4 -6.23796)(lle5 -0.0866628)(lle6 0.0658044)",
//33///
				"(he1 0)(he2 0)(rae1 0.0154596)(rae2 0)(rae3 0)(rae4 0)(lae1 0.0154578)(lae2 0)(lae3 0)(lae4 0)(rle1 -1.74533)(rle2 0.0465419)(rle3 0.0139449)(rle4 -6.62761)(rle5 -0.086113)(rle6 -0.106724)(lle1 -1.74212)(lle2 0.0479966)(lle3 0.0153997)(lle4 -7.38787)(lle5 -0.0875677)(lle6 0.0630909)",
//34
				"(he1 0)(he2 0)(rae1 0.00536019)(rae2 0)(rae3 0)(rae4 0)(lae1 0.00536105)(lae2 0)(lae3 0)(lae4 0)(rle1 -0.872668)(rle2 0.0247254)(rle3 0.00611861)(rle4 -4.418)(rle5 -0.0442101)(rle6 -0.0557208)(lle1 -0.869908)(lle2 0.023998)(lle3 0.00975383)(lle4 -4.87126)(lle5 -0.0434828)(lle6 0.0339041)",
//35
				"(he1 0)(he2 0)(rae1 -5.4708)(rae2 0)(rae3 0)(rae4 5.23599)(lae1 -5.4716)(lae2 0)(lae3 0)(lae4 -5.23599)(rle1 7.76672)(rle2 -0.869956)(rle3 -5.61667)(rle4 3.32712)(rle5 4.70808)(rle6 2.17589)(lle1 7.76644)(lle2 -0.870603)(lle3 -5.61766)(lle4 3.24927)(lle5 4.74846)(lle6 -1.30553)",
//36
				"(he1 0)(he2 0)(rae1 -5.4712)(rae2 0)(rae3 0)(rae4 5.236)(lae1 -5.4711)(lae2 0)(lae3 0)(lae4 -5.236)(rle1 7.76673)(rle2 -0.87012)(rle3 -2.61697)(rle4 3.17076)(rle5 5.70803)(rle6 2.17649)(lle1 7.76677)(lle2 -0.870848)(lle3 -3.61767)(lle4 3.06582)(lle5 5.74849)(lle6 -1.30661)",
//37
				"(he1 0)(he2 0)(rae1 -7.0165)(rae2 0)(rae3 0)(rae4 5.23929)(lae1 -7.0165)(lae2 0)(lae3 0)(lae4 -5.23929)(rle1 7.97402)(rle2 -0.870874)(rle3 -2.6264)(rle4 3.17999)(rle5 5.71187)(rle6 2.17687)(lle1 7.97292)(lle2 -0.872775)(lle3 -2.62613)(lle4 3.07404)(lle5 5.75301)(lle6 -1.30618)",
//38
				"(he1 0)(he2 0)(rae1 -7.6385)(rae2 0)(rae3 0)(rae4 5.24305)(lae1 -7.6385)(lae2 0)(lae3 0)(lae4 -5.24305)(rle1 8.20842)(rle2 -0.87176)(rle3 -3.63472)(rle4 3.18814)(rle5 5.71625)(rle6 2.17738)(lle1 8.20858)(lle2 -0.873765)(lle3 -3.63454)(lle4 3.08091)(lle5 5.75818)(lle6 -1.30709)",
//39
				"(he1 0)(he2 0)(rae1 -7.4532)(rae2 0)(rae3 0)(rae4 5.24491)(lae1 -7.4532)(lae2 0)(lae3 0)(lae4 -5.24491)(rle1 8.68488)(rle2 -0.871437)(rle3 -1.64145)(rle4 3.19466)(rle5 8.7233)(rle6 2.17798)(lle1 8.5176)(lle2 -0.873759)(lle3 -1.64269)(lle4 3.08869)(lle5 8.77355)(lle6 -1.30804)",
//40
				"(he1 0)(he2 0)(rae1 -8.5557)(rae2 0)(rae3 0)(rae4 5.24809)(lae1 -8.5557)(lae2 0)(lae3 0)(lae4 -5.24809)(rle1 9.41553)(rle2 -0.873006)(rle3 -2.64966)(rle4 3.19908)(rle5 4.69268)(rle6 2.17713)(lle1 8.93413)(lle2 -0.875728)(lle3 -2.65261)(lle4 3.09609)(lle5 4.70244)(lle6 -1.30941)",
//41
				"(he1 0)(he2 0)(rae1 -8.1375)(rae2 0)(rae3 0)(rae4 5.25035)(lae1 -8.1375)(lae2 0)(lae3 0)(lae4 -5.25035)(rle1 10.6858)(rle2 -0.872704)(rle3 -2.65507)(rle3 5.20623)(rle5 4.71507)(rle6 2.1784)(lle1 10.4418)(lle2 -1.32979)(lle3 -2.65614)(lle4 3.10075)(lle5 4.75485)(lle6 -1.30918)",
//42
				"(he1 0)(he2 0)(rae1 -8.6142)(rae2 0)(rae3 0)(rae4 5.25442)(lae1 -8.6142)(lae2 0)(lae3 0)(lae4 -5.25442)(rle1 13.2658)(rle2 -0.773924)(rle3 -5.65919)(rle4 3.21141)(rle5 4.72017)(rle6 2.17982)(lle1 11.3808)(lle2 -1.32791)(lle3 -5.66998)(lle4 3.10942)(lle5 4.76611)(lle6 -1.31224)",
//43
				"(he1 0)(he2 0)(rae1 -22.1157)(rae2 0)(rae3 0)(rae4 5.25729)(lae1 -22.1157)(lae2 0)(lae3 0)(lae4 -5.25729)(rle1 15.5371)(rle2 -0.778315)(rle3 -6.40985)(rle4 3.21841)(rle5 4.72157)(rle6 2.17821)(lle1 13.5387)(lle2 -2.5775)(lle3 -3.68813)(lle4 5.12476)(lle5 4.7743)(lle6 -1.31671)",
//44
				"(he1 0)(he2 0)(rae1 -16.7976)(rae2 0)(rae3 0)(rae4 2.62916)(lae1 -16.7976)(lae2 0)(lae3 0)(lae4 -2.62916)(rle1 11.3297)(rle2 -0.39215)(rle3 -3.20711)(rle4 2.61876)(rle5 2.36033)(rle6 1.08819)(lle1 9.39675)(lle2 -3.26171)(lle3 -2.86037)(lle4 2.57329)(lle5 2.39221)(lle6 -0.664347)",
//45
				"(he1 0)(he2 0)(rae1 -3.27785)(rae2 0)(rae3 0)(rae4 0.263301)(lae1 -3.27785)(lae2 0)(lae3 0)(lae4 -0.263301)(rle1 2.0732)(rle2 -0.0402521)(rle3 -0.349958)(rle4 0.263608)(rle5 0.236951)(rle6 0.11022)(lle1 1.68094)(lle2 -0.864046)(lle3 -0.28849)(lle4 0.259297)(lle5 0.240177)(lle6 -0.0698243)",
//46
				"(he1 0)(he2 0)(rae1 -4.46164)(rae2 0)(rae3 0)(rae4 0.263573)(lae1 -4.46261)(lae2 0)(lae3 0)(lae4 -0.263573)(rle1 2.65041)(rle2 -0.0401912)(rle3 -0.350451)(rle4 0.263694)(rle5 0.236442)(rle6 0.109927)(lle1 2.04435)(lle2 -1.46402)(lle3 -0.287303)(lle4 0.259179)(lle5 0.240301)(lle6 -0.0728581)",
//47
				"(he1 0)(he2 0)(rae1 -4.46222)(rae2 0)(rae3 0)(rae4 0.263755)(lae1 -4.4621)(lae2 0)(lae3 0)(lae4 -0.263755)(rle1 2.64989)(rle2 -0.0397677)(rle3 -0.350556)(rle4 0.263914)(rle5 0.236603)(rle6 0.109521)(lle1 2.04389)(lle2 -1.464)(lle3 -0.285179)(lle4 0.25777)(lle5 0.240866)(lle6 -0.0695855)",
//48
				"(he1 0)(he2 0)(rae1 -4.46256)(rae2 0)(rae3 0)(rae4 0.264008)(lae1 -4.46258)(lae2 0)(lae3 0)(lae4 -0.264008)(rle1 2.65079)(rle2 -0.0392761)(rle3 -0.350755)(rle4 0.262939)(rle5 0.236721)(rle6 0.109019)(lle1 2.04423)(lle2 -1.46371)(lle3 -0.283837)(lle4 0.256149)(lle5 0.240289)(lle6 -0.0675274)",
//49
				"(he1 0)(he2 0)(rae1 -4.46306)(rae2 0)(rae3 0)(rae4 0.264335)(lae1 -4.46306)(lae2 0)(lae3 0)(lae4 -0.262881)(rle1 2.6503)(rle2 -0.038632)(rle3 -0.34955)(rle4 0.263292)(rle5 0.236886)(rle6 0.109819)(lle1 2.04454)(lle2 -1.46483)(lle3 -0.281916)(lle4 0.255479)(lle5 0.241164)(lle6 -0.0660353)",
//50
				"(he1 0)(he2 0)(rae1 -4.46199)(rae2 0)(rae3 0)(rae4 0.263034)(lae1 -4.46199)(lae2 0)(lae3 0)(lae4 -0.263325)(rle1 2.64989)(rle2 -0.0395061)(rle3 -0.349889)(rle4 0.263521)(rle5 0.237108)(rle6 0.108934)(lle1 2.04325)(lle2 -1.46436)(lle3 -0.28109)(lle4 0.25435)(lle5 0.240354)(lle6 -0.0638331)",
//51
				"(he1 0)(he2 0)(rae1 -4.46513)(rae2 0)(rae3 0)(rae4 0.263669)(lae1 -4.46513)(lae2 0)(lae3 0)(lae4 -0.263596)(rle1 2.65144)(rle2 -0.0317111)(rle3 -0.350012)(rle4 0.263896)(rle5 0.237426)(rle6 0.108028)(lle1 2.04389)(lle2 -1.64295)(lle3 -0.279575)(lle4 0.254954)(lle5 0.241741)(lle6 -0.0628891)",
//52
				"(he1 0)(he2 0)(rae1 -4.46606)(rae2 0)(rae3 0)(rae4 0.264082)(lae1 -4.46606)(lae2 0)(lae3 0)(lae4 -0.264106)(rle1 2.65336)(rle2 -0.00706483)(rle3 -0.34738)(rle4 0.261563)(rle5 0.235015)(rle6 0.109434)(lle1 2.0414)(lle2 -1.79947)(lle3 -0.277281)(lle4 0.25538)(lle5 0.243322)(lle6 -0.0608962)",
//53
				"(he1 0)(he2 0)(rae1 -4.46902)(rae2 0)(rae3 0)(rae4 0.26502)(lae1 -4.46902)(lae2 0)(lae3 0)(lae4 -0.265008)(rle1 2.65702)(rle2 0.190882)(rle3 -0.347857)(rle4 0.262615)(rle5 0.235922)(rle6 0.111089)(lle1 2.04235)(lle2 -2.18027)(lle3 -0.277445)(lle4 0.256325)(lle5 0.24202)(lle6 -0.0574348)",
//54
				"(he1 0)(he2 0)(rae1 -2.23353)(rae2 0)(rae3 0)(rae4 0.133652)(lae1 -2.23353)(lae2 0)(lae3 0)(lae4 -0.133659)(rle1 1.68218)(rle2 0.100636)(rle3 -0.17745)(rle4 0.131189)(rle5 0.117658)(rle6 0.0535386)(lle1 1.02086)(lle2 -2.33022)(lle3 -0.142101)(lle4 0.124952)(lle5 0.1205)(lle6 -0.0329858)",
//55
				"(he1 0)(he2 0)(rae1 7.13172)(rae2 0)(rae3 0)(rae4 -13.5866)(lae1 8.84781)(lae2 0)(lae3 0)(lae4 13.7361)(rle1 -0.575228)(rle2 0.286072)(rle3 -0.938124)(rle4 -0.0997493)(rle5 0.273954)(rle6 -0.24383)(lle1 -0.798346)(lle2 -2.98146)(lle3 -0.0525591)(lle4 -2.10544)(lle5 1.30778)(lle6 0.475616)"
//56
		};

Angle CutDataShortDistanceShootingFromUT[]=
{
		{	//2650
			JointInfo(-2.44,0),
			JointInfo(-50.06,0),JointInfo(-29.97,0),JointInfo(0.22,0),JointInfo(49.93,0),
			JointInfo(-0,0),JointInfo(9.98,0),JointInfo(37,0),JointInfo(-70.04,0),JointInfo(38.03,0),JointInfo(-9.97,0),
			JointInfo(-45,0),
			JointInfo(-50.06,0),JointInfo(29.97,0),JointInfo(-0.22,0),JointInfo(-49.93,0),
			JointInfo(-0,0),JointInfo(9.98,0),JointInfo(36.99,0),JointInfo(-70.01,0),JointInfo(38.01,0),JointInfo(-9.98,0)
		},
		{	//2681
			JointInfo(-0.11,0),
			JointInfo(-50,0),JointInfo(-30,0),JointInfo(0,0),JointInfo(50,0),
			JointInfo(-0,0),JointInfo(10,0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38,0),JointInfo(-10,0),
			JointInfo(-45,0),
			JointInfo(-50,0),JointInfo(30,0),JointInfo(-0,0),JointInfo(-50,0),
			JointInfo(-0,0),JointInfo(10,0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38,0),JointInfo(-10,0)
		},
		{	//2704
			JointInfo(-0.01,0),
			JointInfo(-50,0),JointInfo(-30,0),JointInfo(0,0),JointInfo(50,0),
			JointInfo(-0,0),JointInfo(10,0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38,0),JointInfo(-10,0),
			JointInfo(-45,0),
			JointInfo(-50,0),JointInfo(30,0),JointInfo(-0,0),JointInfo(-50,0),
			JointInfo(-0,0),JointInfo(10,0),JointInfo(52.93,0),JointInfo(-91.91,0),JointInfo(38,0),JointInfo(-10,0)
		},
		{	//2708
			JointInfo(-0.01,0),
			JointInfo(-56.22,0),JointInfo(-24.45,0),JointInfo(-0.91,0),JointInfo(22.64,0),
			JointInfo(-11.87,0),JointInfo(5.32,0),JointInfo(8.42,0),JointInfo(-52.52,0),JointInfo(48.59,0),JointInfo(-8.74,0),
			JointInfo(-45,0),
			JointInfo(-43.56,0),JointInfo(25.67,0),JointInfo(4.59,0),JointInfo(-29.44,0),
			JointInfo(0.6,0),JointInfo(-0.93,0),JointInfo(36.45,0),JointInfo(-113.53,0),JointInfo(10.27,0),JointInfo(-10.79,0)
		},
		{	//2711
			JointInfo(-0.01,0),
			JointInfo(-65.52,0),JointInfo(-22.56,0),JointInfo(-1.23,0),JointInfo(10.46,0),
			JointInfo(-5.8,0),JointInfo(3.5,0),JointInfo(-2.5,0),JointInfo(-61.34,0),JointInfo(35.64,0),JointInfo(-8.26,0),
			JointInfo(-45,0),
			JointInfo(-55,0),JointInfo(24.19,0),JointInfo(6.16,0),JointInfo(-22.42,0),
			JointInfo(0.81,0),JointInfo(-6.97,0),JointInfo(15.35,0),JointInfo(-115.53,0),JointInfo(-10.74,0),JointInfo(-11.11,0)
		},
		{	//2717
			JointInfo(-0,0),
			JointInfo(-99.04,0),JointInfo(-21.21,0),JointInfo(-1.45,0),JointInfo(1.68,0),
			JointInfo(-0.6,0),JointInfo(-9.9,0),JointInfo(-16.6,0),JointInfo(-103.37,0),JointInfo(6.86,0),JointInfo(-20.86,0),
			JointInfo(-45,0),
			JointInfo(-96.4,0),JointInfo(23.13,0),JointInfo(7.28,0),JointInfo(-17.38,0),
			JointInfo(-41.2,0),JointInfo(-20.61,0),JointInfo(55.18,0),JointInfo(-74.74,0),JointInfo(-7.79,0),JointInfo(15.81,0)
		},
		{	//2723
			JointInfo(-0,0),
			JointInfo(-111.93,0),JointInfo(-20.88,0),JointInfo(-1.5,0),JointInfo(-0.38,0),
			JointInfo(0.62,0),JointInfo(-13.21,0),JointInfo(-23.03,0),JointInfo(-124.9,0),JointInfo(-29.88,0),JointInfo(-24.04,0),
			JointInfo(-45,0),
			JointInfo(-114.46,0),JointInfo(22.89,0),JointInfo(7.54,0),JointInfo(-16.2,0),
			JointInfo(-76.51,0),JointInfo(-23.98,0),JointInfo(88.07,0),JointInfo(-33.3,0),JointInfo(0.31,0),JointInfo(22.85,0)
		},
		{	//2727
			JointInfo(24.05,0),
			JointInfo(-92.88,0),JointInfo(-15.41,0),JointInfo(26.58,0),JointInfo(8.85,0),
			JointInfo(-0.24,0),JointInfo(-9.89,0),JointInfo(-19.3,0),JointInfo(-125.32,0),JointInfo(-3.21,0),JointInfo(-5.02,0),
			JointInfo(-45,0),
			JointInfo(-93.92,0),JointInfo(20.08,0),JointInfo(-20.46,0),JointInfo(-15.47,0),
			JointInfo(-48.42,0),JointInfo(-14.42,0),JointInfo(77.99,0),JointInfo(-56.86,0),JointInfo(27.08,0),JointInfo(14.02,0)
		},
		{	//2732
			JointInfo(47.37,0),
			JointInfo(-81.82,0),JointInfo(-13.15,0),JointInfo(55.64,0),JointInfo(13.16,0),
			JointInfo(-1.99,0),JointInfo(-5.52,0),JointInfo(15.58,0),JointInfo(-116.84,0),JointInfo(27.56,0),JointInfo(0.94,0),
			JointInfo(-45,0),
			JointInfo(-82.13,0),JointInfo(18.49,0),JointInfo(-52.33,0),JointInfo(-15.14,0),
			JointInfo(-18.15,0),JointInfo(-6.57,0),JointInfo(46.23,0),JointInfo(-70.84,0),JointInfo(38.34,0),JointInfo(6.18,0)
		},
};

Angle CutRightInfo[]=
{
		{	//506
			JointInfo(-1.87,-0),
			JointInfo(-80.09,0),JointInfo(-20,-0),JointInfo(90,-0),JointInfo(29.91,-0),
			JointInfo(-0,0),JointInfo(0,-0),JointInfo(25.78,0),JointInfo(-78.3,0),JointInfo(47.73,0),JointInfo(0,-0),
			JointInfo(-25,0),
			JointInfo(-79.91,0),JointInfo(20,-0),JointInfo(-90,-0),JointInfo(-30.09,-0),
			JointInfo(-0,0),JointInfo(-0,-0),JointInfo(26.26,0),JointInfo(-78.45,0),JointInfo(47.38,0),JointInfo(0,-0)
		},
		{	//511
			JointInfo(-0.98,-0),
			JointInfo(-63.44,0),JointInfo(-29.36,-0),JointInfo(54.86,-0),JointInfo(15.94,-0),
			JointInfo(-0,0),JointInfo(-4.8,-0),JointInfo(28.83,0),JointInfo(-73.77,0),JointInfo(44.02,0),JointInfo(4.8,-0),
			JointInfo(-25,0),
			JointInfo(-51,0),JointInfo(10.65,-0),JointInfo(-54.89,-0),JointInfo(-16.04,-0),
			JointInfo(-0,0),JointInfo(-5.74,-0),JointInfo(27.51,0),JointInfo(-63.81,0),JointInfo(39.54,0),JointInfo(5.74,-0)
		},
		{	//516
			JointInfo(-7.48,-0),
			JointInfo(-53.44,0),JointInfo(-34.98,-0),JointInfo(19.73,-0),JointInfo(7.53,-0),
			JointInfo(-0,0),JointInfo(-7.67,-0),JointInfo(30.66,0),JointInfo(-71.04,0),JointInfo(41.79,0),JointInfo(7.68,-0),
			JointInfo(-25,0),
			JointInfo(-33.3,0),JointInfo(5.03,-0),JointInfo(-19.76,-0),JointInfo(-7.58,-0),
			JointInfo(-0,0),JointInfo(-9.18,-0),JointInfo(28.26,0),JointInfo(-54.3,0),JointInfo(34.84,0),JointInfo(9.18,-0)
		},
		{	//521
			JointInfo(-13.6,-0),
			JointInfo(-47.84,0),JointInfo(-38.13,-0),JointInfo(-5.21,-0),JointInfo(2.8,-0),
			JointInfo(-0,0),JointInfo(-9.29,-0),JointInfo(31.69,0),JointInfo(-69.52,0),JointInfo(40.54,0),JointInfo(9.3,-0),
			JointInfo(-25,0),
			JointInfo(-23.37,0),JointInfo(1.88,-0),JointInfo(5.24,-0),JointInfo(-2.82,-0),
			JointInfo(-0,0),JointInfo(-11.11,-0),JointInfo(28.68,0),JointInfo(-48.96,0),JointInfo(32.2,0),JointInfo(11.12,-0)
		},
		{	//526
			JointInfo(-3.43,-0),
			JointInfo(-45.32,0),JointInfo(-39.55,-0),JointInfo(-16.39,-0),JointInfo(0.68,-0),
			JointInfo(-0,0),JointInfo(-10.02,-0),JointInfo(32.15,0),JointInfo(-68.83,0),JointInfo(39.98,0),JointInfo(10.03,-0),
			JointInfo(-25,0),
			JointInfo(-18.9,0),JointInfo(0.46,-0),JointInfo(16.39,-0),JointInfo(-0.68,-0),
			JointInfo(-0,0),JointInfo(-11.97,-0),JointInfo(28.87,0),JointInfo(-46.56,0),JointInfo(31.01,0),JointInfo(11.98,-0)
		},
		{	//531
			JointInfo(2.93,-0),
			JointInfo(-44.6,0),JointInfo(-39.9,-0),JointInfo(-19.62,-0),JointInfo(0.06,-0),
			JointInfo(-0,0),JointInfo(-10.2,-0),JointInfo(32.29,0),JointInfo(-68.63,0),JointInfo(39.85,0),JointInfo(10.21,-0),
			JointInfo(-25,0),
			JointInfo(-17.69,0),JointInfo(0.11,-0),JointInfo(19.65,-0),JointInfo(-0.08,-0),
			JointInfo(-0,0),JointInfo(-12.24,-0),JointInfo(28.91,0),JointInfo(-45.88,0),JointInfo(30.69,0),JointInfo(12.25,-0)
		},
		{	//532
			JointInfo(0.17,-0),
			JointInfo(-44.61,0),JointInfo(-39.93,-0),JointInfo(-19.6,-0),JointInfo(0.06,-0),
			JointInfo(-0,0),JointInfo(-10.21,-0),JointInfo(25.26,0),JointInfo(-75.6,0),JointInfo(43.1,0),JointInfo(10.22,-0),
			JointInfo(-25,0),
			JointInfo(-17.66,0),JointInfo(0.08,-0),JointInfo(19.62,-0),JointInfo(-0.08,-0),
			JointInfo(-0,0),JointInfo(-12.23,-0),JointInfo(28.86,0),JointInfo(-45.93,0),JointInfo(30.79,0),JointInfo(12.23,-0)
		},
		{	//534
			JointInfo(-7.37,-0),
			JointInfo(-44.5,0),JointInfo(-39.97,-0),JointInfo(-20.02,-0),JointInfo(-0.03,-0),
			JointInfo(-0,0),JointInfo(-10.24,-0),JointInfo(32.87,0),JointInfo(-89.66,0),JointInfo(42.02,0),JointInfo(10.25,-0),
			JointInfo(-25,0),
			JointInfo(-17.5,0),JointInfo(0.04,-0),JointInfo(20.03,-0),JointInfo(0.02,-0),
			JointInfo(-0,0),JointInfo(-12.27,-0),JointInfo(28.9,0),JointInfo(-45.83,0),JointInfo(30.71,0),JointInfo(12.28,-0)
		},
		{	//535
			JointInfo(-8.61,-0),
			JointInfo(-44.57,0),JointInfo(-39.91,-0),JointInfo(-19.89,-0),JointInfo(0.02,-0),
			JointInfo(-0,0),JointInfo(-10.19,-0),JointInfo(25.84,0),JointInfo(-96.64,0),JointInfo(44.5,0),JointInfo(10.21,-0),
			JointInfo(-25,0),
			JointInfo(-17.62,0),JointInfo(0.1,-0),JointInfo(19.95,-0),JointInfo(-0.04,-0),
			JointInfo(-0,0),JointInfo(-12.27,-0),JointInfo(28.81,0),JointInfo(-45.88,0),JointInfo(30.81,0),JointInfo(12.27,-0)
		},
		{	//536
			JointInfo(-8.69,-0),
			JointInfo(-44.61,0),JointInfo(-40.26,-0),JointInfo(-19.15,-0),JointInfo(0.26,-0),
			JointInfo(-0,0),JointInfo(-10.39,-0),JointInfo(18.82,0),JointInfo(-103.61,0),JointInfo(51.47,0),JointInfo(10.4,-0),
			JointInfo(-25,0),
			JointInfo(-17.3,0),JointInfo(-0.26,-0),JointInfo(18.93,-0),JointInfo(-0.12,-0),
			JointInfo(-0,0),JointInfo(-12.1,-0),JointInfo(28.83,0),JointInfo(-46.2,0),JointInfo(31.13,0),JointInfo(12.07,-0)
		},
		{	//541
			JointInfo(-1.61,-0),
			JointInfo(-60.77,0),JointInfo(-26.09,-0),JointInfo(-19.61,-0),JointInfo(0.12,-0),
			JointInfo(-0,0),JointInfo(-19.67,-0),JointInfo(-0.24,0),JointInfo(-113.6,0),JointInfo(16.66,0),JointInfo(10.32,-0),
			JointInfo(-25,0),
			JointInfo(-18.72,0),JointInfo(31.17,-0),JointInfo(19.51,-0),JointInfo(-0.06,-0),
			JointInfo(-13.05,0),JointInfo(-11.24,-0),JointInfo(20.46,0),JointInfo(-24.25,0),JointInfo(16.27,0),JointInfo(11.23,-0)
		},
		{	//546
			JointInfo(-9.73,-0),
			JointInfo(-70.5,0),JointInfo(-17.59,-0),JointInfo(-19.82,-0),JointInfo(0.05,-0),
			JointInfo(-0,0),JointInfo(-25.26,-0),JointInfo(-12.71,0),JointInfo(-120.9,0),JointInfo(-13.99,0),JointInfo(10.29,-0),
			JointInfo(-25,0),
			JointInfo(-19.55,0),JointInfo(51.67,-0),JointInfo(19.77,-0),JointInfo(-0.03,-0),
			JointInfo(-20.89,0),JointInfo(-10.72,-0),JointInfo(15.44,0),JointInfo(-11.11,0),JointInfo(7.38,0),JointInfo(10.71,-0)
		},
		{	//551
			JointInfo(9.29,-0),
			JointInfo(-75.95,0),JointInfo(-12.83,-0),JointInfo(-19.93,-0),JointInfo(0.02,-0),
			JointInfo(-0,0),JointInfo(-28.39,-0),JointInfo(-19.82,0),JointInfo(-125.01,0),JointInfo(-31.63,0),JointInfo(10.27,-0),
			JointInfo(-25,0),
			JointInfo(-20.01,0),JointInfo(63.17,-0),JointInfo(19.91,-0),JointInfo(-0.01,-0),
			JointInfo(-25.28,0),JointInfo(-10.42,-0),JointInfo(12.62,0),JointInfo(-3.74,0),JointInfo(2.39,0),JointInfo(10.42,-0)
		},
		{	//556
			JointInfo(8.77,-0),
			JointInfo(-78.4,0),JointInfo(-10.69,-0),JointInfo(-19.98,-0),JointInfo(0.01,-0),
			JointInfo(-0,0),JointInfo(-29.8,-0),JointInfo(-23.01,0),JointInfo(-126.86,0),JointInfo(-39.57,0),JointInfo(10.26,-0),
			JointInfo(-25,0),
			JointInfo(-20.22,0),JointInfo(68.34,-0),JointInfo(19.98,-0),JointInfo(-0,-0),
			JointInfo(-27.26,0),JointInfo(-10.29,-0),JointInfo(11.35,0),JointInfo(-0.43,0),JointInfo(0.15,0),JointInfo(10.29,-0)
		},
		{	//561
			JointInfo(22.43,-0),
			JointInfo(-79.1,0),JointInfo(-10.07,-0),JointInfo(-20.02,-0),JointInfo(-0.03,-0),
			JointInfo(-0,0),JointInfo(-30.2,-0),JointInfo(-23.94,0),JointInfo(-127.37,0),JointInfo(-41.82,0),JointInfo(10.26,-0),
			JointInfo(-25,0),
			JointInfo(-20.3,0),JointInfo(69.78,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-27.8,0),JointInfo(-10.27,-0),JointInfo(11.01,0),JointInfo(0.54,0),JointInfo(-0.47,0),JointInfo(10.27,-0)
		},
		{	//581
			JointInfo(11.59,-0),
			JointInfo(-79.22,0),JointInfo(-10.02,-0),JointInfo(-20,-0),JointInfo(-0,-0),
			JointInfo(-0,0),JointInfo(-30.25,-0),JointInfo(-24.08,0),JointInfo(-127.43,0),JointInfo(-42.15,0),JointInfo(10.26,-0),
			JointInfo(-25,0),
			JointInfo(-20.29,0),JointInfo(69.99,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-27.89,0),JointInfo(-10.25,-0),JointInfo(10.95,0),JointInfo(0.68,0),JointInfo(-0.6,0),JointInfo(10.25,-0)
		},
		{	//582
			JointInfo(7.58,-0),
			JointInfo(-76.62,0),JointInfo(-10.02,-0),JointInfo(-20,-0),JointInfo(-0,-0),
			JointInfo(2.83,0),JointInfo(-28.3,-0),JointInfo(-27.57,0),JointInfo(-124.71,0),JointInfo(-39.08,0),JointInfo(10.26,-0),
			JointInfo(-25,0),
			JointInfo(-18.73,0),JointInfo(69.99,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-30.07,0),JointInfo(-7.95,-0),JointInfo(10.92,0),JointInfo(0.75,0),JointInfo(-0.64,0),JointInfo(10.25,-0)
		},
		{	//583
			JointInfo(11.59,-0),
			JointInfo(-74.54,0),JointInfo(-10.02,-0),JointInfo(-20,-0),JointInfo(-0,-0),
			JointInfo(0.03,0),JointInfo(-24.47,-0),JointInfo(-24.08,0),JointInfo(-121.8,0),JointInfo(-46.1,0),JointInfo(10.26,-0),
			JointInfo(-25,0),
			JointInfo(-17.47,0),JointInfo(69.99,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-31.57,0),JointInfo(-3.96,-0),JointInfo(10.9,0),JointInfo(0.82,0),JointInfo(-0.67,0),JointInfo(10.25,-0)
		},
		{	//584
			JointInfo(13.26,-0),
			JointInfo(-76.82,0),JointInfo(-10.02,-0),JointInfo(-20,-0),JointInfo(-0,-0),
			JointInfo(-2.81,0),JointInfo(-22.77,-0),JointInfo(-17.84,0),JointInfo(-114.84,0),JointInfo(-39.28,0),JointInfo(10.26,-0),
			JointInfo(-25,0),
			JointInfo(-24.5,0),JointInfo(69.99,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-30.87,0),JointInfo(-5.24,-0),JointInfo(12.3,0),JointInfo(-3.03,0),JointInfo(-3.53,0),JointInfo(10.25,-0)
		},
		{	//586
			JointInfo(11.06,-0),
			JointInfo(-81.15,0),JointInfo(-10.01,-0),JointInfo(-20.01,-0),JointInfo(-0,-0),
			JointInfo(4.59,0),JointInfo(-17.01,-0),JointInfo(-3.9,0),JointInfo(-109.35,0),JointInfo(-40.07,0),JointInfo(10.26,-0),
			JointInfo(-25,0),
			JointInfo(-38.56,0),JointInfo(69.98,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-29.44,0),JointInfo(-7.78,-0),JointInfo(13.14,0),JointInfo(-16.67,0),JointInfo(-9.1,0),JointInfo(10.25,-0)
		},
		{	//590
			JointInfo(9.53,-0),
			JointInfo(-109.14,0),JointInfo(-10.01,-0),JointInfo(-20.01,-0),JointInfo(-0,-0),
			JointInfo(-20.86,0),JointInfo(5.95,-0),JointInfo(23.75,0),JointInfo(-82.34,0),JointInfo(-44.48,0),JointInfo(-10.67,-0),
			JointInfo(-25,0),
			JointInfo(-65.95,0),JointInfo(69.98,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-11.43,0),JointInfo(-11.16,-0),JointInfo(5.21,0),JointInfo(-44.76,0),JointInfo(-31.96,0),JointInfo(19.07,-0)
		},
		{	//593
			JointInfo(13.51,-0),
			JointInfo(-116.17,0),JointInfo(-10.01,-0),JointInfo(-20.01,-0),JointInfo(-0,-0),
			JointInfo(-41.77,0),JointInfo(21.29,-0),JointInfo(44.29,0),JointInfo(-62.29,0),JointInfo(-27.35,0),JointInfo(-17.83,-0),
			JointInfo(-25,0),
			JointInfo(-77.08,0),JointInfo(69.98,-0),JointInfo(20,-0),JointInfo(-0,-0),
			JointInfo(-3.25,0),JointInfo(-9.53,-0),JointInfo(-10.7,0),JointInfo(-65.82,0),JointInfo(-39.82,0),JointInfo(22.11,-0)
		},
		{	//594
			JointInfo(17.5,-0),
			JointInfo(-120.71,0),JointInfo(-10.01,-0),JointInfo(-20.01,-0),JointInfo(-0,-0),
			JointInfo(-47.01,0),JointInfo(26.81,-0),JointInfo(51.19,0),JointInfo(-55.54,0),JointInfo(-20.81,0),JointInfo(-19.38,-0),
			JointInfo(-25,0),
			JointInfo(-78.45,0),JointInfo(69.98,-0),JointInfo(20,-0),JointInfo(-0,-0),
			JointInfo(3.32,0),JointInfo(-14.52,-0),JointInfo(-14.29,0),JointInfo(-72.84,0),JointInfo(-41.4,0),JointInfo(22.73,-0)
		},
		{	//596
			JointInfo(17.47,-0),
			JointInfo(-116.22,0),JointInfo(-10.01,-0),JointInfo(-20.01,-0),JointInfo(-0,-0),
			JointInfo(-47.04,0),JointInfo(21.21,-0),JointInfo(51.19,0),JointInfo(-55.49,0),JointInfo(-20.76,0),JointInfo(-19.25,-0),
			JointInfo(-25,0),
			JointInfo(-78.46,0),JointInfo(69.98,-0),JointInfo(20,-0),JointInfo(-0,-0),
			JointInfo(9.77,0),JointInfo(-14.52,-0),JointInfo(-14.25,0),JointInfo(-86.83,0),JointInfo(-41.4,0),JointInfo(22.73,-0)
		},
};

Angle CutInfo[]=
{
		{	//506
			JointInfo(1.87,0),
			JointInfo(-79.91,0),JointInfo(-20,0),JointInfo(90,0),JointInfo(30.09,0),
			JointInfo(-0,0),JointInfo(0,0),JointInfo(26.26,0),JointInfo(-78.45,0),JointInfo(47.38,0),JointInfo(-0,0),
			JointInfo(-25,0),
			JointInfo(-80.09,0),JointInfo(20,0),JointInfo(-90,0),JointInfo(-29.91,0),
			JointInfo(-0,0),JointInfo(-0,0),JointInfo(25.78,0),JointInfo(-78.3,0),JointInfo(47.73,0),JointInfo(-0,0)
		},
		{	//511
			JointInfo(0.98,0),
			JointInfo(-51,0),JointInfo(-10.65,0),JointInfo(54.89,0),JointInfo(16.04,0),
			JointInfo(-0,0),JointInfo(5.74,0),JointInfo(27.51,0),JointInfo(-63.81,0),JointInfo(39.54,0),JointInfo(-5.74,0),
			JointInfo(-25,0),
			JointInfo(-63.44,0),JointInfo(29.36,0),JointInfo(-54.86,0),JointInfo(-15.94,0),
			JointInfo(-0,0),JointInfo(4.8,0),JointInfo(28.83,0),JointInfo(-73.77,0),JointInfo(44.02,0),JointInfo(-4.8,0)
		},
		{	//516
			JointInfo(7.48,0),
			JointInfo(-33.3,0),JointInfo(-5.03,0),JointInfo(19.76,0),JointInfo(7.58,0),
			JointInfo(-0,0),JointInfo(9.18,0),JointInfo(28.26,0),JointInfo(-54.3,0),JointInfo(34.84,0),JointInfo(-9.18,0),
			JointInfo(-25,0),
			JointInfo(-53.44,0),JointInfo(34.98,0),JointInfo(-19.73,0),JointInfo(-7.53,0),
			JointInfo(-0,0),JointInfo(7.67,0),JointInfo(30.66,0),JointInfo(-71.04,0),JointInfo(41.79,0),JointInfo(-7.68,0)
		},
		{	//521
			JointInfo(13.6,0),
			JointInfo(-23.37,0),JointInfo(-1.88,0),JointInfo(-5.24,0),JointInfo(2.82,0),
			JointInfo(-0,0),JointInfo(11.11,0),JointInfo(28.68,0),JointInfo(-48.96,0),JointInfo(32.2,0),JointInfo(-11.12,0),
			JointInfo(-25,0),
			JointInfo(-47.84,0),JointInfo(38.13,0),JointInfo(5.21,0),JointInfo(-2.8,0),
			JointInfo(-0,0),JointInfo(9.29,0),JointInfo(31.69,0),JointInfo(-69.52,0),JointInfo(40.54,0),JointInfo(-9.3,0)
		},
		{	//526
			JointInfo(3.43,0),
			JointInfo(-18.9,0),JointInfo(-0.46,0),JointInfo(-16.39,0),JointInfo(0.68,0),
			JointInfo(-0,0),JointInfo(11.97,0),JointInfo(28.87,0),JointInfo(-46.56,0),JointInfo(31.01,0),JointInfo(-11.98,0),
			JointInfo(-25,0),
			JointInfo(-45.32,0),JointInfo(39.55,0),JointInfo(16.39,0),JointInfo(-0.68,0),
			JointInfo(-0,0),JointInfo(10.02,0),JointInfo(32.15,0),JointInfo(-68.83,0),JointInfo(39.98,0),JointInfo(-10.03,0)
		},
		{	//531
			JointInfo(-2.93,0),
			JointInfo(-17.69,0),JointInfo(-0.11,0),JointInfo(-19.65,0),JointInfo(0.08,0),
			JointInfo(-0,0),JointInfo(12.24,0),JointInfo(28.91,0),JointInfo(-45.88,0),JointInfo(30.69,0),JointInfo(-12.25,0),
			JointInfo(-25,0),
			JointInfo(-44.6,0),JointInfo(39.9,0),JointInfo(19.62,0),JointInfo(-0.06,0),
			JointInfo(-0,0),JointInfo(10.2,0),JointInfo(32.29,0),JointInfo(-68.63,0),JointInfo(39.85,0),JointInfo(-10.21,0)
		},
		{	//532
			JointInfo(-0.17,0),
			JointInfo(-17.66,0),JointInfo(-0.08,0),JointInfo(-19.62,0),JointInfo(0.08,0),
			JointInfo(-0,0),JointInfo(12.23,0),JointInfo(28.86,0),JointInfo(-45.93,0),JointInfo(30.79,0),JointInfo(-12.23,0),
			JointInfo(-25,0),
			JointInfo(-44.61,0),JointInfo(39.93,0),JointInfo(19.6,0),JointInfo(-0.06,0),
			JointInfo(-0,0),JointInfo(10.21,0),JointInfo(25.26,0),JointInfo(-75.6,0),JointInfo(43.1,0),JointInfo(-10.22,0)
		},
		{	//534
			JointInfo(7.37,0),
			JointInfo(-17.5,0),JointInfo(-0.04,0),JointInfo(-20.03,0),JointInfo(-0.02,0),
			JointInfo(-0,0),JointInfo(12.27,0),JointInfo(28.9,0),JointInfo(-45.83,0),JointInfo(30.71,0),JointInfo(-12.28,0),
			JointInfo(-25,0),
			JointInfo(-44.5,0),JointInfo(39.97,0),JointInfo(20.02,0),JointInfo(0.03,0),
			JointInfo(-0,0),JointInfo(10.24,0),JointInfo(32.87,0),JointInfo(-89.66,0),JointInfo(42.02,0),JointInfo(-10.25,0)
		},
		{	//535
			JointInfo(8.61,0),
			JointInfo(-17.62,0),JointInfo(-0.1,0),JointInfo(-19.95,0),JointInfo(0.04,0),
			JointInfo(-0,0),JointInfo(12.27,0),JointInfo(28.81,0),JointInfo(-45.88,0),JointInfo(30.81,0),JointInfo(-12.27,0),
			JointInfo(-25,0),
			JointInfo(-44.57,0),JointInfo(39.91,0),JointInfo(19.89,0),JointInfo(-0.02,0),
			JointInfo(-0,0),JointInfo(10.19,0),JointInfo(25.84,0),JointInfo(-96.64,0),JointInfo(44.5,0),JointInfo(-10.21,0)
		},
		{	//536
			JointInfo(8.69,0),
			JointInfo(-17.3,0),JointInfo(0.26,0),JointInfo(-18.93,0),JointInfo(0.12,0),
			JointInfo(-0,0),JointInfo(12.1,0),JointInfo(28.83,0),JointInfo(-46.2,0),JointInfo(31.13,0),JointInfo(-12.07,0),
			JointInfo(-25,0),
			JointInfo(-44.61,0),JointInfo(40.26,0),JointInfo(19.15,0),JointInfo(-0.26,0),
			JointInfo(-0,0),JointInfo(10.39,0),JointInfo(18.82,0),JointInfo(-103.61,0),JointInfo(51.47,0),JointInfo(-10.4,0)
		},
		{	//541
			JointInfo(1.61,0),
			JointInfo(-18.72,0),JointInfo(-31.17,0),JointInfo(-19.51,0),JointInfo(0.06,0),
			JointInfo(-13.05,0),JointInfo(11.24,0),JointInfo(20.46,0),JointInfo(-24.25,0),JointInfo(16.27,0),JointInfo(-11.23,0),
			JointInfo(-25,0),
			JointInfo(-60.77,0),JointInfo(26.09,0),JointInfo(19.61,0),JointInfo(-0.12,0),
			JointInfo(-0,0),JointInfo(19.67,0),JointInfo(-0.24,0),JointInfo(-113.6,0),JointInfo(16.66,0),JointInfo(-10.32,0)
		},
		{	//546
			JointInfo(9.73,0),
			JointInfo(-19.55,0),JointInfo(-51.67,0),JointInfo(-19.77,0),JointInfo(0.03,0),
			JointInfo(-20.89,0),JointInfo(10.72,0),JointInfo(15.44,0),JointInfo(-11.11,0),JointInfo(7.38,0),JointInfo(-10.71,0),
			JointInfo(-25,0),
			JointInfo(-70.5,0),JointInfo(17.59,0),JointInfo(19.82,0),JointInfo(-0.05,0),
			JointInfo(-0,0),JointInfo(25.26,0),JointInfo(-12.71,0),JointInfo(-120.9,0),JointInfo(-13.99,0),JointInfo(-10.29,0)
		},
		{	//551
			JointInfo(-9.29,0),
			JointInfo(-20.01,0),JointInfo(-63.17,0),JointInfo(-19.91,0),JointInfo(0.01,0),
			JointInfo(-25.28,0),JointInfo(10.42,0),JointInfo(12.62,0),JointInfo(-3.74,0),JointInfo(2.39,0),JointInfo(-10.42,0),
			JointInfo(-25,0),
			JointInfo(-75.95,0),JointInfo(12.83,0),JointInfo(19.93,0),JointInfo(-0.02,0),
			JointInfo(-0,0),JointInfo(28.39,0),JointInfo(-19.82,0),JointInfo(-125.01,0),JointInfo(-31.63,0),JointInfo(-10.27,0)
		},
		{	//556
			JointInfo(-8.77,0),
			JointInfo(-20.22,0),JointInfo(-68.34,0),JointInfo(-19.98,0),JointInfo(0,0),
			JointInfo(-27.26,0),JointInfo(10.29,0),JointInfo(11.35,0),JointInfo(-0.43,0),JointInfo(0.15,0),JointInfo(-10.29,0),
			JointInfo(-25,0),
			JointInfo(-78.4,0),JointInfo(10.69,0),JointInfo(19.98,0),JointInfo(-0.01,0),
			JointInfo(-0,0),JointInfo(29.8,0),JointInfo(-23.01,0),JointInfo(-126.86,0),JointInfo(-39.57,0),JointInfo(-10.26,0)
		},
		{	//561
			JointInfo(-22.43,0),
			JointInfo(-20.3,0),JointInfo(-69.78,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-27.8,0),JointInfo(10.27,0),JointInfo(11.01,0),JointInfo(0.54,0),JointInfo(-0.47,0),JointInfo(-10.27,0),
			JointInfo(-25,0),
			JointInfo(-79.1,0),JointInfo(10.07,0),JointInfo(20.02,0),JointInfo(0.03,0),
			JointInfo(-0,0),JointInfo(30.2,0),JointInfo(-23.94,0),JointInfo(-127.37,0),JointInfo(-41.82,0),JointInfo(-10.26,0)
		},
		{	//581
			JointInfo(-11.59,0),
			JointInfo(-20.29,0),JointInfo(-69.99,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-27.89,0),JointInfo(10.25,0),JointInfo(10.95,0),JointInfo(0.68,0),JointInfo(-0.6,0),JointInfo(-10.25,0),
			JointInfo(-25,0),
			JointInfo(-79.22,0),JointInfo(10.02,0),JointInfo(20,0),JointInfo(0,0),
			JointInfo(-0,0),JointInfo(30.25,0),JointInfo(-24.08,0),JointInfo(-127.43,0),JointInfo(-42.15,0),JointInfo(-10.26,0)
		},
		{	//582
			JointInfo(-7.58,0),
			JointInfo(-18.73,0),JointInfo(-69.99,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-30.07,0),JointInfo(7.95,0),JointInfo(10.92,0),JointInfo(0.75,0),JointInfo(-0.64,0),JointInfo(-10.25,0),
			JointInfo(-25,0),
			JointInfo(-76.62,0),JointInfo(10.02,0),JointInfo(20,0),JointInfo(0,0),
			JointInfo(2.83,0),JointInfo(28.3,0),JointInfo(-27.57,0),JointInfo(-124.71,0),JointInfo(-39.08,0),JointInfo(-10.26,0)
		},
		{	//583
			JointInfo(-11.59,0),
			JointInfo(-17.47,0),JointInfo(-69.99,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-31.57,0),JointInfo(3.96,0),JointInfo(10.9,0),JointInfo(0.82,0),JointInfo(-0.67,0),JointInfo(-10.25,0),
			JointInfo(-25,0),
			JointInfo(-74.54,0),JointInfo(10.02,0),JointInfo(20,0),JointInfo(0,0),
			JointInfo(0.03,0),JointInfo(24.47,0),JointInfo(-24.08,0),JointInfo(-121.8,0),JointInfo(-46.1,0),JointInfo(-10.26,0)
		},
		{	//584
			JointInfo(-13.26,0),
			JointInfo(-24.5,0),JointInfo(-69.99,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-30.87,0),JointInfo(5.24,0),JointInfo(12.3,0),JointInfo(-3.03,0),JointInfo(-3.53,0),JointInfo(-10.25,0),
			JointInfo(-25,0),
			JointInfo(-76.82,0),JointInfo(10.02,0),JointInfo(20,0),JointInfo(0,0),
			JointInfo(-2.81,0),JointInfo(22.77,0),JointInfo(-17.84,0),JointInfo(-114.84,0),JointInfo(-39.28,0),JointInfo(-10.26,0)
		},
		{	//586
			JointInfo(-11.06,0),
			JointInfo(-38.56,0),JointInfo(-69.98,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-29.44,0),JointInfo(7.78,0),JointInfo(13.14,0),JointInfo(-16.67,0),JointInfo(-9.1,0),JointInfo(-10.25,0),
			JointInfo(-25,0),
			JointInfo(-81.15,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0,0),
			JointInfo(4.59,0),JointInfo(17.01,0),JointInfo(-3.9,0),JointInfo(-109.35,0),JointInfo(-40.07,0),JointInfo(-10.26,0)
		},
		{	//590
			JointInfo(-9.53,0),
			JointInfo(-65.95,0),JointInfo(-69.98,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-11.43,0),JointInfo(11.16,0),JointInfo(5.21,0),JointInfo(-44.76,0),JointInfo(-31.96,0),JointInfo(-19.07,0),
			JointInfo(-25,0),
			JointInfo(-109.14,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0,0),
			JointInfo(-20.86,0),JointInfo(-5.95,0),JointInfo(23.75,0),JointInfo(-82.34,0),JointInfo(-44.48,0),JointInfo(10.67,0)
		},
		{	//593
			JointInfo(-13.51,0),
			JointInfo(-77.08,0),JointInfo(-69.98,0),JointInfo(-20,0),JointInfo(0,0),
			JointInfo(-3.25,0),JointInfo(9.53,0),JointInfo(-10.7,0),JointInfo(-65.82,0),JointInfo(-39.82,0),JointInfo(-22.11,0),
			JointInfo(-25,0),
			JointInfo(-116.17,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0,0),
			JointInfo(-41.77,0),JointInfo(-21.29,0),JointInfo(44.29,0),JointInfo(-62.29,0),JointInfo(-27.35,0),JointInfo(17.83,0)
		},
		{	//594
			JointInfo(-17.5,0),
			JointInfo(-78.45,0),JointInfo(-69.98,0),JointInfo(-20,0),JointInfo(0,0),
			JointInfo(3.32,0),JointInfo(14.52,0),JointInfo(-14.29,0),JointInfo(-72.84,0),JointInfo(-41.4,0),JointInfo(-22.73,0),
			JointInfo(-25,0),
			JointInfo(-120.71,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0,0),
			JointInfo(-47.01,0),JointInfo(-26.81,0),JointInfo(51.19,0),JointInfo(-55.54,0),JointInfo(-20.81,0),JointInfo(19.38,0)
		},
		{	//596
			JointInfo(-17.47,0),
			JointInfo(-78.46,0),JointInfo(-69.98,0),JointInfo(-20,0),JointInfo(0,0),
			JointInfo(9.77,0),JointInfo(14.52,0),JointInfo(-14.25,0),JointInfo(-86.83,0),JointInfo(-41.4,0),JointInfo(-22.73,0),
			JointInfo(-25,0),
			JointInfo(-116.22,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0,0),
			JointInfo(-47.04,0),JointInfo(-21.21,0),JointInfo(51.19,0),JointInfo(-55.49,0),JointInfo(-20.76,0),JointInfo(19.25,0)
		},
};

Angle CutDataInfo[] =
{
		{	//395
			JointInfo(11.55,0),
			JointInfo(-80.05,0),JointInfo(-20,0),JointInfo(90,0),JointInfo(29.95,0),
			JointInfo(-0.01,0),JointInfo(0.16,0),JointInfo(26.04,0),JointInfo(-78.26,0),JointInfo(47.33,0),JointInfo(-0.16,0),
			JointInfo(-25,0),
			JointInfo(-79.96,0),JointInfo(20,0),JointInfo(-90,0),JointInfo(-30.05,0),
			JointInfo(-0,0),JointInfo(-0.16,0),JointInfo(26.27,0),JointInfo(-78.29,0),JointInfo(47.13,0),JointInfo(0.16,0)
		},
		{	//400
			JointInfo(15.52,0),
			JointInfo(-63.41,0),JointInfo(-29.36,0),JointInfo(54.86,0),JointInfo(15.96,0),
			JointInfo(-0.01,0),JointInfo(-4.71,0),JointInfo(28.97,0),JointInfo(-73.74,0),JointInfo(43.8,0),JointInfo(4.72,0),
			JointInfo(-25,0),
			JointInfo(-51.03,0),JointInfo(10.65,0),JointInfo(-54.89,0),JointInfo(-16.02,0),
			JointInfo(-0,0),JointInfo(-5.82,0),JointInfo(27.52,0),JointInfo(-63.72,0),JointInfo(39.41,0),JointInfo(5.82,0)
		},
		{	//405
			JointInfo(18.38,0),
			JointInfo(-53.43,0),JointInfo(-34.98,0),JointInfo(19.73,0),JointInfo(7.54,0),
			JointInfo(-0,0),JointInfo(-7.64,0),JointInfo(30.73,0),JointInfo(-71.03,0),JointInfo(41.69,0),JointInfo(7.64,0),
			JointInfo(-25,0),
			JointInfo(-33.31,0),JointInfo(5.03,0),JointInfo(-19.76,0),JointInfo(-7.57,0),
			JointInfo(-0,0),JointInfo(-9.21,0),JointInfo(28.26,0),JointInfo(-54.25,0),JointInfo(34.77,0),JointInfo(9.22,0)
		},
		{	//410
			JointInfo(13.86,0),
			JointInfo(-47.83,0),JointInfo(-38.13,0),JointInfo(-5.21,0),JointInfo(2.8,0),
			JointInfo(-0,0),JointInfo(-9.28,0),JointInfo(31.72,0),JointInfo(-69.51,0),JointInfo(40.5,0),JointInfo(9.29,0),
			JointInfo(-25,0),
			JointInfo(-23.37,0),JointInfo(1.88,0),JointInfo(5.24,0),JointInfo(-2.81,0),
			JointInfo(-0,0),JointInfo(-11.12,0),JointInfo(28.68,0),JointInfo(-48.94,0),JointInfo(32.17,0),JointInfo(11.13,0)
		},
		{	//415
			JointInfo(11.17,0),
			JointInfo(-45.32,0),JointInfo(-39.54,0),JointInfo(-16.39,0),JointInfo(0.68,0),
			JointInfo(-0,0),JointInfo(-10.01,0),JointInfo(32.16,0),JointInfo(-68.83,0),JointInfo(39.97,0),JointInfo(10.02,0),
			JointInfo(-25,0),
			JointInfo(-18.91,0),JointInfo(0.46,0),JointInfo(16.39,0),JointInfo(-0.68,0),
			JointInfo(-0,0),JointInfo(-11.97,0),JointInfo(28.87,0),JointInfo(-46.56,0),JointInfo(31.01,0),JointInfo(11.98,0)
		},
		{	//420
			JointInfo(17,0),
			JointInfo(-44.59,0),JointInfo(-39.98,0),JointInfo(-19.62,0),JointInfo(0.1,0),
			JointInfo(-0,0),JointInfo(-10.25,0),JointInfo(32.26,0),JointInfo(-68.62,0),JointInfo(39.83,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-17.6,0),JointInfo(0.11,0),JointInfo(19.65,0),JointInfo(-0.08,0),
			JointInfo(-0,0),JointInfo(-12.25,0),JointInfo(28.92,0),JointInfo(-45.85,0),JointInfo(30.62,0),JointInfo(12.24,0)
		},
		{	//421
			JointInfo(12.99,0),
			JointInfo(-44.6,0),JointInfo(-39.97,0),JointInfo(-19.61,0),JointInfo(0.09,0),
			JointInfo(-0,0),JointInfo(-10.23,0),JointInfo(25.24,0),JointInfo(-75.6,0),JointInfo(43.09,0),JointInfo(10.24,0),
			JointInfo(-25,0),
			JointInfo(-17.62,0),JointInfo(0.08,0),JointInfo(19.62,0),JointInfo(-0.08,0),
			JointInfo(-0,0),JointInfo(-12.23,0),JointInfo(28.87,0),JointInfo(-45.93,0),JointInfo(30.76,0),JointInfo(12.24,0)
		},
		{	//422
			JointInfo(17,0),
			JointInfo(-44.58,0),JointInfo(-39.93,0),JointInfo(-19.67,0),JointInfo(0.04,0),
			JointInfo(-0,0),JointInfo(-10.21,0),JointInfo(26.99,0),JointInfo(-82.63,0),JointInfo(44.73,0),JointInfo(10.22,0),
			JointInfo(-25,0),
			JointInfo(-17.62,0),JointInfo(0.01,0),JointInfo(19.64,0),JointInfo(-0.05,0),
			JointInfo(-0,0),JointInfo(-12.21,0),JointInfo(28.86,0),JointInfo(-45.95,0),JointInfo(30.87,0),JointInfo(12.23,0)
		},
		{	//423
			JointInfo(12.99,0),
			JointInfo(-44.5,0),JointInfo(-40.01,0),JointInfo(-20.01,0),JointInfo(0.02,0),
			JointInfo(-0,0),JointInfo(-10.27,0),JointInfo(32.82,0),JointInfo(-89.66,0),JointInfo(42.01,0),JointInfo(10.28,0),
			JointInfo(-25,0),
			JointInfo(-17.45,0),JointInfo(0.04,0),JointInfo(20.03,0),JointInfo(0.02,0),
			JointInfo(-0,0),JointInfo(-12.28,0),JointInfo(28.9,0),JointInfo(-45.8,0),JointInfo(30.67,0),JointInfo(12.26,0)
		},
		{	//425
			JointInfo(12.99,0),
			JointInfo(-44.69,0),JointInfo(-39.66,0),JointInfo(-19.15,0),JointInfo(-0.1,0),
			JointInfo(-0,0),JointInfo(-10.04,0),JointInfo(18.77,0),JointInfo(-103.61,0),JointInfo(51.44,0),JointInfo(10.05,0),
			JointInfo(-25,0),
			JointInfo(-17.97,0),JointInfo(-0.26,0),JointInfo(18.94,0),JointInfo(-0.11,0),
			JointInfo(-0,0),JointInfo(-12.01,0),JointInfo(28.73,0),JointInfo(-46.33,0),JointInfo(31.61,0),JointInfo(12.12,0)
		},
		{	//430
			JointInfo(2.83,0),
			JointInfo(-63.16,0),JointInfo(-23.79,0),JointInfo(-19.66,0),JointInfo(-0.04,0),
			JointInfo(-0,0),JointInfo(-20.89,0),JointInfo(-3.15,0),JointInfo(-115.34,0),JointInfo(9.65,0),JointInfo(10.18,0),
			JointInfo(-25,0),
			JointInfo(-19.18,0),JointInfo(36.13,0),JointInfo(19.57,0),JointInfo(-0.04,0),
			JointInfo(-14.96,0),JointInfo(-11.08,0),JointInfo(19.21,0),JointInfo(-21.12,0),JointInfo(14.3,0),JointInfo(11.13,0)
		},
		{	//435
			JointInfo(12.23,0),
			JointInfo(-71.9,0),JointInfo(-16.27,0),JointInfo(-19.85,0),JointInfo(-0.02,0),
			JointInfo(-0,0),JointInfo(-25.99,0),JointInfo(-14.53,0),JointInfo(-121.95,0),JointInfo(-18.49,0),JointInfo(10.22,0),
			JointInfo(-25,0),
			JointInfo(-19.79,0),JointInfo(54.6,0),JointInfo(19.81,0),JointInfo(-0.02,0),
			JointInfo(-22.01,0),JointInfo(-10.63,0),JointInfo(14.7,0),JointInfo(-9.25,0),JointInfo(6.19,0),JointInfo(10.65,0)
		},
		{	//440
			JointInfo(1.95,0),
			JointInfo(-76.65,0),JointInfo(-12.19,0),JointInfo(-19.95,0),JointInfo(-0.01,0),
			JointInfo(-0,0),JointInfo(-28.77,0),JointInfo(-20.72,0),JointInfo(-125.53,0),JointInfo(-33.87,0),JointInfo(10.25,0),
			JointInfo(-25,0),
			JointInfo(-20.11,0),JointInfo(64.63,0),JointInfo(19.93,0),JointInfo(-0.01,0),
			JointInfo(-25.84,0),JointInfo(-10.38,0),JointInfo(12.26,0),JointInfo(-2.81,0),JointInfo(1.79,0),JointInfo(10.39,0)
		},
		{	//445
			JointInfo(22,0),
			JointInfo(-78.64,0),JointInfo(-10.47,0),JointInfo(-19.99,0),JointInfo(-0,0),
			JointInfo(-0,0),JointInfo(-29.93,0),JointInfo(-23.33,0),JointInfo(-127.04,0),JointInfo(-40.35,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-20.25,0),JointInfo(68.84,0),JointInfo(19.99,0),JointInfo(-0,0),
			JointInfo(-27.45,0),JointInfo(-10.28,0),JointInfo(11.24,0),JointInfo(-0.1,0),JointInfo(-0.06,0),JointInfo(10.28,0)
		},
		{	//450
			JointInfo(9.4,0),
			JointInfo(-79.11,0),JointInfo(-10.04,0),JointInfo(-20.01,0),JointInfo(-0.01,0),
			JointInfo(-0,0),JointInfo(-30.18,0),JointInfo(-23.94,0),JointInfo(-127.37,0),JointInfo(-41.86,0),JointInfo(10.25,0),
			JointInfo(-25,0),
			JointInfo(-20.26,0),JointInfo(69.79,0),JointInfo(20,0),JointInfo(-0.01,0),
			JointInfo(-27.8,0),JointInfo(-10.27,0),JointInfo(10.98,0),JointInfo(0.53,0),JointInfo(-0.48,0),JointInfo(10.27,0)
		},
		{	//455
			JointInfo(7.17,0),
			JointInfo(-79.15,0),JointInfo(-10.02,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-0,0),JointInfo(-30.22,0),JointInfo(-23.99,0),JointInfo(-127.41,0),JointInfo(-42,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-20.28,0),JointInfo(69.9,0),JointInfo(20,0),JointInfo(-0,0),
			JointInfo(-27.85,0),JointInfo(-10.26,0),JointInfo(10.97,0),JointInfo(0.59,0),JointInfo(-0.53,0),JointInfo(10.26,0)
		},
		{	//469
			JointInfo(31.23,0),
			JointInfo(-79.22,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-0,0),JointInfo(-30.25,0),JointInfo(-23.99,0),JointInfo(-127.46,0),JointInfo(-42.13,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-20.29,0),JointInfo(69.99,0),JointInfo(20,0),JointInfo(-0,0),
			JointInfo(-27.9,0),JointInfo(-10.25,0),JointInfo(10.95,0),JointInfo(0.68,0),JointInfo(-0.6,0),JointInfo(10.25,0)
		},
		{	//471
			JointInfo(23.22,0),
			JointInfo(-74.54,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(0.03,0),JointInfo(-24.47,0),JointInfo(-23.99,0),JointInfo(-121.83,0),JointInfo(-46.08,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-17.46,0),JointInfo(69.99,0),JointInfo(20,0),JointInfo(-0,0),
			JointInfo(-31.58,0),JointInfo(-3.96,0),JointInfo(10.91,0),JointInfo(0.81,0),JointInfo(-0.68,0),JointInfo(10.25,0)
		},
		{	//474
			JointInfo(27.22,0),
			JointInfo(-81.15,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(4.59,0),JointInfo(-17.01,0),JointInfo(-3.81,0),JointInfo(-109.39,0),JointInfo(-40.05,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-38.55,0),JointInfo(69.99,0),JointInfo(19.99,0),JointInfo(-0,0),
			JointInfo(-29.44,0),JointInfo(-7.78,0),JointInfo(13.17,0),JointInfo(-16.68,0),JointInfo(-9.1,0),JointInfo(10.25,0)
		},
		{	//480
			JointInfo(19.26,0),
			JointInfo(-123.06,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-34.76,0),JointInfo(18.69,0),JointInfo(37.45,0),JointInfo(-69.11,0),JointInfo(-31.65,0),JointInfo(-15.92,0),
			JointInfo(-25,0),
			JointInfo(-75.09,0),JointInfo(69.99,0),JointInfo(19.99,0),JointInfo(-0.01,0),
			JointInfo(-1.55,0),JointInfo(-8.96,0),JointInfo(-6.2,0),JointInfo(-58.82,0),JointInfo(-37.81,0),JointInfo(21.33,0)
		},
		{	//482
			JointInfo(11.29,0),
			JointInfo(-120.71,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-47.01,0),JointInfo(26.81,0),JointInfo(51.28,0),JointInfo(-55.58,0),JointInfo(-20.79,0),JointInfo(-19.38,0),
			JointInfo(-25,0),
			JointInfo(-78.45,0),JointInfo(69.99,0),JointInfo(19.99,0),JointInfo(-0,0),
			JointInfo(3.29,0),JointInfo(-14.48,0),JointInfo(-14.31,0),JointInfo(-72.86,0),JointInfo(-41.41,0),JointInfo(22.73,0)
		},
		{	//485
			JointInfo(7.28,0),
			JointInfo(-116.22,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-47.03,0),JointInfo(21.2,0),JointInfo(51.28,0),JointInfo(-55.51,0),JointInfo(-20.73,0),JointInfo(-19.21,0),
			JointInfo(-25,0),
			JointInfo(-78.46,0),JointInfo(69.99,0),JointInfo(19.99,0),JointInfo(-0,0),
			JointInfo(-3.08,0),JointInfo(-14.48,0),JointInfo(-16.91,0),JointInfo(-93.88,0),JointInfo(-41.41,0),JointInfo(22.73,0)
		},
};
Angle CutDataShootingFromNexus3D[]=
{
		{	//2099
			JointInfo(4.16,0),
			JointInfo(-80.05,0),JointInfo(-20,0),JointInfo(90,0),JointInfo(29.95,0),
			JointInfo(-0,0),JointInfo(0.05,0),JointInfo(25.8,0),JointInfo(-78.27,0),JointInfo(47.61,0),JointInfo(-0.05,0),
			JointInfo(-25,0),
			JointInfo(-79.95,0),JointInfo(20,0),JointInfo(-90,0),JointInfo(-30.05,0),
			JointInfo(0,0),JointInfo(-0.05,0),JointInfo(26.09,0),JointInfo(-78.42,0),JointInfo(47.45,0),JointInfo(0.05,0)
		},
		{	//2115
			JointInfo(5.27,0),
			JointInfo(-47.12,0),JointInfo(-38.53,0),JointInfo(-8.35,0),JointInfo(2.2,0),
			JointInfo(-0,0),JointInfo(-9.49,0),JointInfo(31.82,0),JointInfo(-69.32,0),JointInfo(40.38,0),JointInfo(9.5,0),
			JointInfo(-25,0),
			JointInfo(-22.11,0),JointInfo(1.48,0),JointInfo(8.35,0),JointInfo(-2.21,0),
			JointInfo(0,0),JointInfo(-11.35,0),JointInfo(28.72,0),JointInfo(-48.28,0),JointInfo(31.87,0),JointInfo(11.36,0)
		},
		{	//2120
			JointInfo(-0.79,0),
			JointInfo(-45.32,0),JointInfo(-39.54,0),JointInfo(-16.39,0),JointInfo(0.68,0),
			JointInfo(-0,0),JointInfo(-10.01,0),JointInfo(32.15,0),JointInfo(-68.83,0),JointInfo(39.98,0),JointInfo(10.02,0),
			JointInfo(-25,0),
			JointInfo(-18.91,0),JointInfo(0.46,0),JointInfo(16.39,0),JointInfo(-0.68,0),
			JointInfo(0,0),JointInfo(-11.97,0),JointInfo(28.86,0),JointInfo(-46.56,0),JointInfo(31.01,0),JointInfo(11.98,0)
		},
		{	//2125
			JointInfo(3.54,0),
			JointInfo(-44.59,0),JointInfo(-39.98,0),JointInfo(-19.62,0),JointInfo(0.05,0),
			JointInfo(-0,0),JointInfo(-10.26,0),JointInfo(32.29,0),JointInfo(-68.62,0),JointInfo(39.8,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-17.6,0),JointInfo(0.11,0),JointInfo(19.65,0),JointInfo(-0.07,0),
			JointInfo(0,0),JointInfo(-12.23,0),JointInfo(28.96,0),JointInfo(-45.88,0),JointInfo(30.69,0),JointInfo(12.24,0)
		},
		{	//2130
			JointInfo(1.25,0),
			JointInfo(-44.69,0),JointInfo(-39.66,0),JointInfo(-19.15,0),JointInfo(0.32,0),
			JointInfo(-0,0),JointInfo(-10,0),JointInfo(18.73,0),JointInfo(-103.61,0),JointInfo(51.43,0),JointInfo(10.02,0),
			JointInfo(-25,0),
			JointInfo(-17.97,0),JointInfo(-0.26,0),JointInfo(18.94,0),JointInfo(-0.19,0),
			JointInfo(0,0),JointInfo(-12.17,0),JointInfo(28.46,0),JointInfo(-46.13,0),JointInfo(31.05,0),JointInfo(12.16,0)
		},
		{	//2135
			JointInfo(-2.75,0),
			JointInfo(-60.81,0),JointInfo(-25.82,0),JointInfo(-19.61,0),JointInfo(0.15,0),
			JointInfo(-0,0),JointInfo(-19.49,0),JointInfo(-0.26,0),JointInfo(-113.6,0),JointInfo(16.62,0),JointInfo(10.15,0),
			JointInfo(-25,0),
			JointInfo(-19.02,0),JointInfo(31.17,0),JointInfo(19.51,0),JointInfo(-0.09,0),
			JointInfo(-13.05,0),JointInfo(-11.28,0),JointInfo(20.3,0),JointInfo(-24.22,0),JointInfo(16.23,0),JointInfo(11.27,0)
		},
		{	//2140
			JointInfo(-0.03,0),
			JointInfo(-70.51,0),JointInfo(-17.46,0),JointInfo(-19.82,0),JointInfo(0.07,0),
			JointInfo(-0,0),JointInfo(-25.17,0),JointInfo(-12.73,0),JointInfo(-120.9,0),JointInfo(-14.02,0),JointInfo(10.21,0),
			JointInfo(-25,0),
			JointInfo(-19.69,0),JointInfo(51.67,0),JointInfo(19.77,0),JointInfo(-0.04,0),
			JointInfo(-20.89,0),JointInfo(-10.73,0),JointInfo(15.36,0),JointInfo(-11.09,0),JointInfo(7.36,0),JointInfo(10.73,0)
		},
		{	//2145
			JointInfo(12.01,0),
			JointInfo(-75.96,0),JointInfo(-12.78,0),JointInfo(-19.93,0),JointInfo(0.02,0),
			JointInfo(-0,0),JointInfo(-28.36,0),JointInfo(-19.83,0),JointInfo(-125.01,0),JointInfo(-31.64,0),JointInfo(10.24,0),
			JointInfo(-25,0),
			JointInfo(-20.07,0),JointInfo(63.17,0),JointInfo(19.91,0),JointInfo(-0.01,0),
			JointInfo(-25.28,0),JointInfo(-10.43,0),JointInfo(12.59,0),JointInfo(-3.73,0),JointInfo(2.39,0),JointInfo(10.43,0)
		},
		{	//2150
			JointInfo(7.99,0),
			JointInfo(-78.4,0),JointInfo(-10.68,0),JointInfo(-19.98,0),JointInfo(0.01,0),
			JointInfo(-0,0),JointInfo(-29.79,0),JointInfo(-23.02,0),JointInfo(-126.86,0),JointInfo(-39.57,0),JointInfo(10.25,0),
			JointInfo(-25,0),
			JointInfo(-20.23,0),JointInfo(68.34,0),JointInfo(19.98,0),JointInfo(-0,0),
			JointInfo(-27.26,0),JointInfo(-10.29,0),JointInfo(11.35,0),JointInfo(-0.42,0),JointInfo(0.15,0),JointInfo(10.3,0)
		},
		{	//2155
			JointInfo(18.31,0),
			JointInfo(-79.1,0),JointInfo(-10.03,0),JointInfo(-20.02,0),JointInfo(-0.04,0),
			JointInfo(-0,0),JointInfo(-30.19,0),JointInfo(-23.87,0),JointInfo(-127.37,0),JointInfo(-41.86,0),JointInfo(10.29,0),
			JointInfo(-25,0),
			JointInfo(-20.34,0),JointInfo(69.78,0),JointInfo(20,0),JointInfo(-0.05,0),
			JointInfo(-27.8,0),JointInfo(-10.27,0),JointInfo(11.01,0),JointInfo(0.5,0),JointInfo(-0.49,0),JointInfo(10.22,0)
		},
		{	//2160
			JointInfo(29.59,0),
			JointInfo(-79.14,0),JointInfo(-10.03,0),JointInfo(-20,0),JointInfo(-0.01,0),
			JointInfo(-0,0),JointInfo(-30.22,0),JointInfo(-23.96,0),JointInfo(-127.41,0),JointInfo(-41.98,0),JointInfo(10.27,0),
			JointInfo(-25,0),
			JointInfo(-20.31,0),JointInfo(69.88,0),JointInfo(20,0),JointInfo(-0.02,0),
			JointInfo(-27.84,0),JointInfo(-10.26,0),JointInfo(10.98,0),JointInfo(0.56,0),JointInfo(-0.52,0),JointInfo(10.24,0)
		},
		{	//2170
			JointInfo(7.08,0),
			JointInfo(-79.18,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-0,0),JointInfo(-30.25,0),JointInfo(-24.03,0),JointInfo(-127.45,0),JointInfo(-42.12,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-20.29,0),JointInfo(69.99,0),JointInfo(20,0),JointInfo(-0,0),
			JointInfo(-27.89,0),JointInfo(-10.25,0),JointInfo(10.95,0),JointInfo(0.64,0),JointInfo(-0.57,0),JointInfo(10.25,0)
		},
		{	//2175
			JointInfo(19.11,0),
			JointInfo(-79.22,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-0,0),JointInfo(-30.25,0),JointInfo(-24.05,0),JointInfo(-127.46,0),JointInfo(-42.1,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-20.29,0),JointInfo(69.99,0),JointInfo(20,0),JointInfo(-0.01,0),
			JointInfo(-27.9,0),JointInfo(-10.25,0),JointInfo(10.95,0),JointInfo(0.6,0),JointInfo(-0.55,0),JointInfo(10.25,0)
		},
		{	//2179
			JointInfo(12.69,0),
			JointInfo(-81.15,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(4.59,0),JointInfo(-17.01,0),JointInfo(-3.87,0),JointInfo(-109.39,0),JointInfo(-40.02,0),JointInfo(10.26,0),
			JointInfo(-25,0),
			JointInfo(-38.56,0),JointInfo(69.99,0),JointInfo(19.99,0),JointInfo(-0.01,0),
			JointInfo(-29.44,0),JointInfo(-7.78,0),JointInfo(13.14,0),JointInfo(-16.76,0),JointInfo(-9.05,0),JointInfo(10.25,0)
		},
		{	//2183
			JointInfo(18.16,0),
			JointInfo(-109.14,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-20.86,0),JointInfo(5.95,0),JointInfo(23.78,0),JointInfo(-82.37,0),JointInfo(-44.43,0),JointInfo(-10.67,0),
			JointInfo(-25,0),
			JointInfo(-65.95,0),JointInfo(69.99,0),JointInfo(20,0),JointInfo(-0.01,0),
			JointInfo(-11.44,0),JointInfo(-11.13,0),JointInfo(5.2,0),JointInfo(-44.85,0),JointInfo(-31.92,0),JointInfo(19.07,0)
		},
		{	//2187
			JointInfo(8.26,0),
			JointInfo(-120.71,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-47.01,0),JointInfo(26.81,0),JointInfo(51.22,0),JointInfo(-55.58,0),JointInfo(-20.76,0),JointInfo(-19.38,0),
			JointInfo(-25,0),
			JointInfo(-78.46,0),JointInfo(69.99,0),JointInfo(19.99,0),JointInfo(-0,0),
			JointInfo(3.23,0),JointInfo(-14.5,0),JointInfo(-14.4,0),JointInfo(-72.94,0),JointInfo(-41.36,0),JointInfo(22.73,0)
		},
		{	//2191
			JointInfo(-3.99,0),
			JointInfo(-116.22,0),JointInfo(-10,0),JointInfo(-20,0),JointInfo(-0,0),
			JointInfo(-47.03,0),JointInfo(21.19,0),JointInfo(51.22,0),JointInfo(-55.5,0),JointInfo(-20.69,0),JointInfo(-19.18,0),
			JointInfo(-25,0),
			JointInfo(-78.46,0),JointInfo(69.99,0),JointInfo(19.99,0),JointInfo(-0,0),
			JointInfo(-3.13,0),JointInfo(-14.49,0),JointInfo(-17.16,0),JointInfo(-95.69,0),JointInfo(-41.36,0),JointInfo(22.73,0)
		},
};

Angle CutDataLeftFromNexus3D[]=
{
		{	//2099
			JointInfo(-4.16,-0),
			JointInfo(-79.95,0),JointInfo(-20,-0),JointInfo(90,-0),JointInfo(30.05,-0),
			JointInfo(0,0),JointInfo(0.05,-0),JointInfo(26.09,0),JointInfo(-78.42,0),JointInfo(47.45,0),JointInfo(-0.05,-0),
			JointInfo(-25,0),
			JointInfo(-80.05,0),JointInfo(20,-0),JointInfo(-90,-0),JointInfo(-29.95,-0),
			JointInfo(-0,0),JointInfo(-0.05,-0),JointInfo(25.8,0),JointInfo(-78.27,0),JointInfo(47.61,0),JointInfo(0.05,-0)
		},
		{	//2115
			JointInfo(-5.27,-0),
			JointInfo(-22.11,0),JointInfo(-1.48,-0),JointInfo(-8.35,-0),JointInfo(2.21,-0),
			JointInfo(0,0),JointInfo(11.35,-0),JointInfo(28.72,0),JointInfo(-48.28,0),JointInfo(31.87,0),JointInfo(-11.36,-0),
			JointInfo(-25,0),
			JointInfo(-47.12,0),JointInfo(38.53,-0),JointInfo(8.35,-0),JointInfo(-2.2,-0),
			JointInfo(-0,0),JointInfo(9.49,-0),JointInfo(31.82,0),JointInfo(-69.32,0),JointInfo(40.38,0),JointInfo(-9.5,-0)
		},
		{	//2120
			JointInfo(0.79,-0),
			JointInfo(-18.91,0),JointInfo(-0.46,-0),JointInfo(-16.39,-0),JointInfo(0.68,-0),
			JointInfo(0,0),JointInfo(11.97,-0),JointInfo(28.86,0),JointInfo(-46.56,0),JointInfo(31.01,0),JointInfo(-11.98,-0),
			JointInfo(-25,0),
			JointInfo(-45.32,0),JointInfo(39.54,-0),JointInfo(16.39,-0),JointInfo(-0.68,-0),
			JointInfo(-0,0),JointInfo(10.01,-0),JointInfo(32.15,0),JointInfo(-68.83,0),JointInfo(39.98,0),JointInfo(-10.02,-0)
		},
		{	//2125
			JointInfo(-3.54,-0),
			JointInfo(-17.6,0),JointInfo(-0.11,-0),JointInfo(-19.65,-0),JointInfo(0.07,-0),
			JointInfo(0,0),JointInfo(12.23,-0),JointInfo(28.96,0),JointInfo(-45.88,0),JointInfo(30.69,0),JointInfo(-12.24,-0),
			JointInfo(-25,0),
			JointInfo(-44.59,0),JointInfo(39.98,-0),JointInfo(19.62,-0),JointInfo(-0.05,-0),
			JointInfo(-0,0),JointInfo(10.26,-0),JointInfo(32.29,0),JointInfo(-68.62,0),JointInfo(39.8,0),JointInfo(-10.26,-0)
		},
		{	//2130
			JointInfo(-1.25,-0),
			JointInfo(-17.97,0),JointInfo(0.26,-0),JointInfo(-18.94,-0),JointInfo(0.19,-0),
			JointInfo(0,0),JointInfo(12.17,-0),JointInfo(28.46,0),JointInfo(-46.13,0),JointInfo(31.05,0),JointInfo(-12.16,-0),
			JointInfo(-25,0),
			JointInfo(-44.69,0),JointInfo(39.66,-0),JointInfo(19.15,-0),JointInfo(-0.32,-0),
			JointInfo(-0,0),JointInfo(10,-0),JointInfo(18.73,0),JointInfo(-103.61,0),JointInfo(51.43,0),JointInfo(-10.02,-0)
		},
		{	//2135
			JointInfo(2.75,-0),
			JointInfo(-19.02,0),JointInfo(-31.17,-0),JointInfo(-19.51,-0),JointInfo(0.09,-0),
			JointInfo(-13.05,0),JointInfo(11.28,-0),JointInfo(20.3,0),JointInfo(-24.22,0),JointInfo(16.23,0),JointInfo(-11.27,-0),
			JointInfo(-25,0),
			JointInfo(-60.81,0),JointInfo(25.82,-0),JointInfo(19.61,-0),JointInfo(-0.15,-0),
			JointInfo(-0,0),JointInfo(19.49,-0),JointInfo(-0.26,0),JointInfo(-113.6,0),JointInfo(16.62,0),JointInfo(-10.15,-0)
		},
		{	//2140
			JointInfo(0.03,-0),
			JointInfo(-19.69,0),JointInfo(-51.67,-0),JointInfo(-19.77,-0),JointInfo(0.04,-0),
			JointInfo(-20.89,0),JointInfo(10.73,-0),JointInfo(15.36,0),JointInfo(-11.09,0),JointInfo(7.36,0),JointInfo(-10.73,-0),
			JointInfo(-25,0),
			JointInfo(-70.51,0),JointInfo(17.46,-0),JointInfo(19.82,-0),JointInfo(-0.07,-0),
			JointInfo(-0,0),JointInfo(25.17,-0),JointInfo(-12.73,0),JointInfo(-120.9,0),JointInfo(-14.02,0),JointInfo(-10.21,-0)
		},
		{	//2145
			JointInfo(-12.01,-0),
			JointInfo(-20.07,0),JointInfo(-63.17,-0),JointInfo(-19.91,-0),JointInfo(0.01,-0),
			JointInfo(-25.28,0),JointInfo(10.43,-0),JointInfo(12.59,0),JointInfo(-3.73,0),JointInfo(2.39,0),JointInfo(-10.43,-0),
			JointInfo(-25,0),
			JointInfo(-75.96,0),JointInfo(12.78,-0),JointInfo(19.93,-0),JointInfo(-0.02,-0),
			JointInfo(-0,0),JointInfo(28.36,-0),JointInfo(-19.83,0),JointInfo(-125.01,0),JointInfo(-31.64,0),JointInfo(-10.24,-0)
		},
		{	//2150
			JointInfo(-7.99,-0),
			JointInfo(-20.23,0),JointInfo(-68.34,-0),JointInfo(-19.98,-0),JointInfo(0,-0),
			JointInfo(-27.26,0),JointInfo(10.29,-0),JointInfo(11.35,0),JointInfo(-0.42,0),JointInfo(0.15,0),JointInfo(-10.3,-0),
			JointInfo(-25,0),
			JointInfo(-78.4,0),JointInfo(10.68,-0),JointInfo(19.98,-0),JointInfo(-0.01,-0),
			JointInfo(-0,0),JointInfo(29.79,-0),JointInfo(-23.02,0),JointInfo(-126.86,0),JointInfo(-39.57,0),JointInfo(-10.25,-0)
		},
		{	//2155
			JointInfo(-18.31,-0),
			JointInfo(-20.34,0),JointInfo(-69.78,-0),JointInfo(-20,-0),JointInfo(0.05,-0),
			JointInfo(-27.8,0),JointInfo(10.27,-0),JointInfo(11.01,0),JointInfo(0.5,0),JointInfo(-0.49,0),JointInfo(-10.22,-0),
			JointInfo(-25,0),
			JointInfo(-79.1,0),JointInfo(10.03,-0),JointInfo(20.02,-0),JointInfo(0.04,-0),
			JointInfo(-0,0),JointInfo(30.19,-0),JointInfo(-23.87,0),JointInfo(-127.37,0),JointInfo(-41.86,0),JointInfo(-10.29,-0)
		},
		{	//2160
			JointInfo(-29.59,-0),
			JointInfo(-20.31,0),JointInfo(-69.88,-0),JointInfo(-20,-0),JointInfo(0.02,-0),
			JointInfo(-27.84,0),JointInfo(10.26,-0),JointInfo(10.98,0),JointInfo(0.56,0),JointInfo(-0.52,0),JointInfo(-10.24,-0),
			JointInfo(-25,0),
			JointInfo(-79.14,0),JointInfo(10.03,-0),JointInfo(20,-0),JointInfo(0.01,-0),
			JointInfo(-0,0),JointInfo(30.22,-0),JointInfo(-23.96,0),JointInfo(-127.41,0),JointInfo(-41.98,0),JointInfo(-10.27,-0)
		},
		{	//2170
			JointInfo(-7.08,-0),
			JointInfo(-20.29,0),JointInfo(-69.99,-0),JointInfo(-20,-0),JointInfo(0,-0),
			JointInfo(-27.89,0),JointInfo(10.25,-0),JointInfo(10.95,0),JointInfo(0.64,0),JointInfo(-0.57,0),JointInfo(-10.25,-0),
			JointInfo(-25,0),
			JointInfo(-79.18,0),JointInfo(10,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-0,0),JointInfo(30.25,-0),JointInfo(-24.03,0),JointInfo(-127.45,0),JointInfo(-42.12,0),JointInfo(-10.26,-0)
		},
		{	//2175
			JointInfo(-19.11,-0),
			JointInfo(-20.29,0),JointInfo(-69.99,-0),JointInfo(-20,-0),JointInfo(0.01,-0),
			JointInfo(-27.9,0),JointInfo(10.25,-0),JointInfo(10.95,0),JointInfo(0.6,0),JointInfo(-0.55,0),JointInfo(-10.25,-0),
			JointInfo(-25,0),
			JointInfo(-79.22,0),JointInfo(10,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-0,0),JointInfo(30.25,-0),JointInfo(-24.05,0),JointInfo(-127.46,0),JointInfo(-42.1,0),JointInfo(-10.26,-0)
		},
		{	//2179
			JointInfo(-12.69,-0),
			JointInfo(-38.56,0),JointInfo(-69.99,-0),JointInfo(-19.99,-0),JointInfo(0.01,-0),
			JointInfo(-29.44,0),JointInfo(7.78,-0),JointInfo(13.14,0),JointInfo(-16.76,0),JointInfo(-9.05,0),JointInfo(-10.25,-0),
			JointInfo(-25,0),
			JointInfo(-81.15,0),JointInfo(10,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(4.59,0),JointInfo(17.01,-0),JointInfo(-3.87,0),JointInfo(-109.39,0),JointInfo(-40.02,0),JointInfo(-10.26,-0)
		},
		{	//2183
			JointInfo(-18.16,-0),
			JointInfo(-65.95,0),JointInfo(-69.99,-0),JointInfo(-20,-0),JointInfo(0.01,-0),
			JointInfo(-11.44,0),JointInfo(11.13,-0),JointInfo(5.2,0),JointInfo(-44.85,0),JointInfo(-31.92,0),JointInfo(-19.07,-0),
			JointInfo(-25,0),
			JointInfo(-109.14,0),JointInfo(10,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-20.86,0),JointInfo(-5.95,-0),JointInfo(23.78,0),JointInfo(-82.37,0),JointInfo(-44.43,0),JointInfo(10.67,-0)
		},
		{	//2187
			JointInfo(-8.26,-0),
			JointInfo(-78.46,0),JointInfo(-69.99,-0),JointInfo(-19.99,-0),JointInfo(0,-0),
			JointInfo(3.23,0),JointInfo(14.5,-0),JointInfo(-14.4,0),JointInfo(-72.94,0),JointInfo(-41.36,0),JointInfo(-22.73,-0),
			JointInfo(-25,0),
			JointInfo(-120.71,0),JointInfo(10,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-47.01,0),JointInfo(-26.81,-0),JointInfo(51.22,0),JointInfo(-55.58,0),JointInfo(-20.76,0),JointInfo(19.38,-0)
		},
		{	//2191
			JointInfo(3.99,-0),
			JointInfo(-78.46,0),JointInfo(-69.99,-0),JointInfo(-19.99,-0),JointInfo(0,-0),
			JointInfo(-3.13,0),JointInfo(14.49,-0),JointInfo(-17.16,0),JointInfo(-95.69,0),JointInfo(-41.36,0),JointInfo(-22.73,-0),
			JointInfo(-25,0),
			JointInfo(-116.22,0),JointInfo(10,-0),JointInfo(20,-0),JointInfo(0,-0),
			JointInfo(-47.03,0),JointInfo(-21.19,-0),JointInfo(51.22,0),JointInfo(-55.5,0),JointInfo(-20.69,0),JointInfo(19.18,-0)
		},
};

Angle CutDataShootingFromUT[]=
{
		{	//853
			JointInfo(-4.93,0),
			JointInfo(-80.66,0),JointInfo(-16.71,0),JointInfo(70,0),JointInfo(15,0),
			JointInfo(-0.52,0),JointInfo(-0.43,0),JointInfo(32.32,0),JointInfo(-76.18,0),JointInfo(47.61,0),JointInfo(0.45,0),
			JointInfo(-45,0),
			JointInfo(-80.66,0),JointInfo(13.28,0),JointInfo(-70,0),JointInfo(-15,0),
			JointInfo(-0.52,0),JointInfo(-2.06,0),JointInfo(38.16,0),JointInfo(-88.04,0),JointInfo(52.57,0),JointInfo(2.06,0)
		},
		{	//860
			JointInfo(-2.48,0),
			JointInfo(-55.9,0),JointInfo(-27.45,0),JointInfo(21.95,0),JointInfo(43.23,0),
			JointInfo(-0.1,0),JointInfo(-4.98,0),JointInfo(36.06,0),JointInfo(-71.08,0),JointInfo(39.88,0),JointInfo(4.99,0),
			JointInfo(-45,0),
			JointInfo(-55.9,0),JointInfo(26.78,0),JointInfo(-21.95,0),JointInfo(-43.22,0),
			JointInfo(-0.1,0),JointInfo(4.37,0),JointInfo(37.33,0),JointInfo(-73.69,0),JointInfo(40.93,0),JointInfo(-4.37,0)
		},
		{	//871
			JointInfo(-0.83,0),
			JointInfo(-50.41,0),JointInfo(-29.82,0),JointInfo(1.53,0),JointInfo(49.53,0),
			JointInfo(-0.01,0),JointInfo(-5.93,0),JointInfo(36.94,0),JointInfo(-70.07,0),JointInfo(38.13,0),JointInfo(5.93,0),
			JointInfo(-45,0),
			JointInfo(-50.41,0),JointInfo(29.78,0),JointInfo(-1.53,0),JointInfo(-49.53,0),
			JointInfo(-0.01,0),JointInfo(5.89,0),JointInfo(37.02,0),JointInfo(-70.26,0),JointInfo(38.2,0),JointInfo(-5.89,0)
		},
		{	//880
			JointInfo(-0.34,0),
			JointInfo(-50.05,0),JointInfo(-29.98,0),JointInfo(0.17,0),JointInfo(49.95,0),
			JointInfo(-0,0),JointInfo(-9.91,0),JointInfo(36.99,0),JointInfo(-70.01,0),JointInfo(38.02,0),JointInfo(9.52,0),
			JointInfo(-45,0),
			JointInfo(-50.05,0),JointInfo(29.97,0),JointInfo(-0.17,0),JointInfo(-49.95,0),
			JointInfo(-0,0),JointInfo(-7.9,0),JointInfo(37,0),JointInfo(-70.03,0),JointInfo(38.02,0),JointInfo(8.12,0)
		},
		{	//884
			JointInfo(-0.23,0),
			JointInfo(-50.02,0),JointInfo(-29.99,0),JointInfo(0.06,0),JointInfo(49.98,0),
			JointInfo(-0,0),JointInfo(-9.97,0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38.01,0),JointInfo(9.82,0),
			JointInfo(-45,0),
			JointInfo(-50.02,0),JointInfo(29.99,0),JointInfo(-0.06,0),JointInfo(-49.98,0),
			JointInfo(-0,0),JointInfo(-9.2,0),JointInfo(37,0),JointInfo(-70.01,0),JointInfo(38.01,0),JointInfo(9.28,0)
		},
		{	//892
			JointInfo(-0.1,0),
			JointInfo(-50,0),JointInfo(-30,0),JointInfo(0.01,0),JointInfo(50,0),
			JointInfo(-0,0),JointInfo(-10,0),JointInfo(50.58,0),JointInfo(-88.68,0),JointInfo(38,0),JointInfo(9.97,0),
			JointInfo(-45,0),
			JointInfo(-50,0),JointInfo(30,0),JointInfo(-0.01,0),JointInfo(-50,0),
			JointInfo(-0,0),JointInfo(-9.89,0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38,0),JointInfo(9.9,0)
		},
		{	//897
			JointInfo(-0.06,0),
			JointInfo(-52.6,0),JointInfo(-9.66,0),JointInfo(2.33,0),JointInfo(18.34,0),
			JointInfo(-0.29,0),JointInfo(-11.62,0),JointInfo(47.35,0),JointInfo(-104.14,0),JointInfo(5.29,0),JointInfo(7.69,0),
			JointInfo(-45,0),
			JointInfo(-50.51,0),JointInfo(8.68,0),JointInfo(0.12,0),JointInfo(-17.58,0),
			JointInfo(-5.42,0),JointInfo(-9.93,0),JointInfo(22.61,0),JointInfo(-42.66,0),JointInfo(23.17,0),JointInfo(11.81,0)
		},
		{	//905
			JointInfo(-0.03,0),
			JointInfo(-53.61,0),JointInfo(-1.75,0),JointInfo(3.23,0),JointInfo(3.68,0),
			JointInfo(-0.4,0),JointInfo(-12.96,0),JointInfo(8.08,0),JointInfo(-116.78,0),JointInfo(-23.37,0),JointInfo(5.78,0),
			JointInfo(-45,0),
			JointInfo(-50.7,0),JointInfo(0.4,0),JointInfo(0.17,0),JointInfo(-1.68,0),
			JointInfo(-22.47,0),JointInfo(-9.96,0),JointInfo(15.33,0),JointInfo(-17.61,0),JointInfo(10.98,0),JointInfo(13.37,0)
		},
		{	//910
			JointInfo(-0.02,0),
			JointInfo(-53.73,0),JointInfo(-0.81,0),JointInfo(3.34,0),JointInfo(1.94,0),
			JointInfo(-0.42,0),JointInfo(-13.37,0),JointInfo(-4.36,0),JointInfo(-120.7,0),JointInfo(-32.29,0),JointInfo(5.2,0),
			JointInfo(-45,0),
			JointInfo(-50.73,0),JointInfo(-0.59,0),JointInfo(0.18,0),JointInfo(0.22,0),
			JointInfo(-25.02,0),JointInfo(-9.97,0),JointInfo(13.35,0),JointInfo(-9.92,0),JointInfo(7.24,0),JointInfo(13.86,0)
		},
		{	//920
			JointInfo(-0.01,0),
			JointInfo(-53.77,0),JointInfo(-0.45,0),JointInfo(3.38,0),JointInfo(1.27,0),
			JointInfo(-0.42,0),JointInfo(-13.76,0),JointInfo(-15.97,0),JointInfo(-124.35,0),JointInfo(-40.62,0),JointInfo(4.66,0),
			JointInfo(-45,0),
			JointInfo(-50.74,0),JointInfo(-0.96,0),JointInfo(0.18,0),JointInfo(0.93,0),
			JointInfo(-26,0),JointInfo(-9.98,0),JointInfo(11.51,0),JointInfo(-2.76,0),JointInfo(3.75,0),JointInfo(14.3,0)
		},
		{	//923
			JointInfo(-0,0),
			JointInfo(-46.32,0),JointInfo(-0.43,0),JointInfo(3.38,0),JointInfo(1.24,0),
			JointInfo(-0.42,0),JointInfo(-13.86,0),JointInfo(-18.97,0),JointInfo(-127.14,0),JointInfo(-42.8,0),JointInfo(4.51,0),
			JointInfo(-45,0),
			JointInfo(-46.24,0),JointInfo(-0.98,0),JointInfo(0.18,0),JointInfo(0.97,0),
			JointInfo(-31.71,0),JointInfo(-9.99,0),JointInfo(11.02,0),JointInfo(-0.89,0),JointInfo(2.84,0),JointInfo(14.42,0)
		},
		{	//929
				JointInfo(-0,0),
				JointInfo(-73.91,0),JointInfo(-0.42,0),JointInfo(3.38,0),JointInfo(1.22,0),
				JointInfo(-21.21,0),JointInfo(5.22,0),JointInfo(20.26,0),JointInfo(-93.57,0),JointInfo(-44.46,0),JointInfo(-9.73,0),
				JointInfo(-45,0),
				JointInfo(-88.38,0),JointInfo(-1,0),JointInfo(0.18,0),JointInfo(0.99,0),
				JointInfo(-17.22,0),JointInfo(-17.26,0),JointInfo(13.82,0),JointInfo(-40.45,0),JointInfo(-21.54,0),JointInfo(19.64,0)
		},
		{	//931
			JointInfo(-0,0),
			JointInfo(-87.92,0),JointInfo(-0.42,0),JointInfo(3.39,0),JointInfo(1.21,0),
			JointInfo(-30.19,0),JointInfo(12.81,0),JointInfo(34.01,0),JointInfo(-80.14,0),JointInfo(-31.43,0),JointInfo(-15.33,0),
			JointInfo(-45,0),
			JointInfo(-100.24,0),JointInfo(-1,0),JointInfo(0.18,0),JointInfo(0.99,0),
			JointInfo(-10.28,0),JointInfo(-20.12,0),JointInfo(7.25,0),JointInfo(-54.52,0),JointInfo(-30.49,0),JointInfo(21.69,0)
		},
		{	//938
			JointInfo(-0,0),
			JointInfo(-114.02,0),JointInfo(-0.42,0),JointInfo(3.39,0),JointInfo(1.21,0),
			JointInfo(-67.51,0),JointInfo(22.69,0),JointInfo(79.32,0),JointInfo(-32.17,0),JointInfo(-25,0),JointInfo(-5,0),
			JointInfo(-45,0),
			JointInfo(-111.38,0),JointInfo(-1,0),JointInfo(0.18,0),JointInfo(1,0),
			JointInfo(-1.11,0),JointInfo(-23.89,0),JointInfo(-18.86,0),JointInfo(-102.77,0),JointInfo(-42.32,0),JointInfo(24.39,0)
		},
		{	//941
			JointInfo(18.59,0),
			JointInfo(-97.23,0),JointInfo(-6.82,0),JointInfo(24.38,0),JointInfo(7.98,0),
			JointInfo(-46.42,0),JointInfo(12.79,0),JointInfo(70.59,0),JointInfo(-47.64,0),JointInfo(17.21,0),JointInfo(-12.94,0),
			JointInfo(-45,0),
			JointInfo(-95.8,0),JointInfo(7.67,0),JointInfo(-20.88,0),JointInfo(-6.88,0),
			JointInfo(-0.69,0),JointInfo(-11.41,0),JointInfo(-2.26,0),JointInfo(-134.09,0),JointInfo(-21.24,0),JointInfo(11.78,0)
		},
};

Angle showBasicMotion[]=
{
//		和机器人同一方向
//		头1,   //控制不了
//		右臂向前,右臂向左,右臂逆时针,右肘向前,
//		右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向左转
//		头2 向上,
//		左臂向前,左臂向左,左臂逆时针,左肘向后,
//		左腿顺时针,左腿向左,左腿向前,左小腿向前,左脚尖向上,左踝向左转
		{
				JointInfo(0,0),
				JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),
				JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),
				JointInfo(0,0),
				JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),
				JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),
		},
		{
				JointInfo(0,0),
				JointInfo(0,0),JointInfo(-90,0),JointInfo(0,0),JointInfo(0,0),
				JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),
				JointInfo(0,0),
				JointInfo(0,0),JointInfo(90,0),JointInfo(0,0),JointInfo(0,0),
				JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),JointInfo(0,0),
		},
};

Angle leftFootShootingFromUT[]=
{
		{	//853
			JointInfo(4.93,-0),
			JointInfo(-80.66,0),JointInfo(-13.28,-0),JointInfo(70,-0),JointInfo(15,-0),
			JointInfo(-0.52,0),JointInfo(2.06,-0),JointInfo(38.16,0),JointInfo(-88.04,0),JointInfo(52.57,0),JointInfo(-2.06,-0),
			JointInfo(-45,0),
			JointInfo(-80.66,0),JointInfo(16.71,-0),JointInfo(-70,-0),JointInfo(-15,-0),
			JointInfo(-0.52,0),JointInfo(0.43,-0),JointInfo(32.32,0),JointInfo(-76.18,0),JointInfo(47.61,0),JointInfo(-0.45,-0)
		},
		{	//860
			JointInfo(2.48,-0),
			JointInfo(-55.9,0),JointInfo(-26.78,-0),JointInfo(21.95,-0),JointInfo(43.22,-0),
			JointInfo(-0.1,0),JointInfo(-4.37,-0),JointInfo(37.33,0),JointInfo(-73.69,0),JointInfo(40.93,0),JointInfo(4.37,-0),
			JointInfo(-45,0),
			JointInfo(-55.9,0),JointInfo(27.45,-0),JointInfo(-21.95,-0),JointInfo(-43.23,-0),
			JointInfo(-0.1,0),JointInfo(4.98,-0),JointInfo(36.06,0),JointInfo(-71.08,0),JointInfo(39.88,0),JointInfo(-4.99,-0)
		},
		{	//871
			JointInfo(0.83,-0),
			JointInfo(-50.41,0),JointInfo(-29.78,-0),JointInfo(1.53,-0),JointInfo(49.53,-0),
			JointInfo(-0.01,0),JointInfo(-5.89,-0),JointInfo(37.02,0),JointInfo(-70.26,0),JointInfo(38.2,0),JointInfo(5.89,-0),
			JointInfo(-45,0),
			JointInfo(-50.41,0),JointInfo(29.82,-0),JointInfo(-1.53,-0),JointInfo(-49.53,-0),
			JointInfo(-0.01,0),JointInfo(5.93,-0),JointInfo(36.94,0),JointInfo(-70.07,0),JointInfo(38.13,0),JointInfo(-5.93,-0)
		},
		{	//880
			JointInfo(0.34,-0),
			JointInfo(-50.05,0),JointInfo(-29.97,-0),JointInfo(0.17,-0),JointInfo(49.95,-0),
			JointInfo(-0,0),JointInfo(7.9,-0),JointInfo(37,0),JointInfo(-70.03,0),JointInfo(38.02,0),JointInfo(-8.12,-0),
			JointInfo(-45,0),
			JointInfo(-50.05,0),JointInfo(29.98,-0),JointInfo(-0.17,-0),JointInfo(-49.95,-0),
			JointInfo(-0,0),JointInfo(9.91,-0),JointInfo(36.99,0),JointInfo(-70.01,0),JointInfo(38.02,0),JointInfo(-9.52,-0)
		},
		{	//884
			JointInfo(0.23,-0),
			JointInfo(-50.02,0),JointInfo(-29.99,-0),JointInfo(0.06,-0),JointInfo(49.98,-0),
			JointInfo(-0,0),JointInfo(9.2,-0),JointInfo(37,0),JointInfo(-70.01,0),JointInfo(38.01,0),JointInfo(-9.28,-0),
			JointInfo(-45,0),
			JointInfo(-50.02,0),JointInfo(29.99,-0),JointInfo(-0.06,-0),JointInfo(-49.98,-0),
			JointInfo(-0,0),JointInfo(9.97,-0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38.01,0),JointInfo(-9.82,-0)
		},
		{	//892
			JointInfo(0.1,-0),
			JointInfo(-50,0),JointInfo(-30,-0),JointInfo(0.01,-0),JointInfo(50,-0),
			JointInfo(-0,0),JointInfo(9.89,-0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38,0),JointInfo(-9.9,-0),
			JointInfo(-45,0),
			JointInfo(-50,0),JointInfo(30,-0),JointInfo(-0.01,-0),JointInfo(-50,-0),
			JointInfo(-0,0),JointInfo(10,-0),JointInfo(50.58,0),JointInfo(-88.68,0),JointInfo(38,0),JointInfo(-9.97,-0)
		},
		{	//897
			JointInfo(0.06,-0),
			JointInfo(-50.51,0),JointInfo(-8.68,-0),JointInfo(-0.12,-0),JointInfo(17.58,-0),
			JointInfo(-5.42,0),JointInfo(9.93,-0),JointInfo(22.61,0),JointInfo(-42.66,0),JointInfo(23.17,0),JointInfo(-11.81,-0),
			JointInfo(-45,0),
			JointInfo(-52.6,0),JointInfo(9.66,-0),JointInfo(-2.33,-0),JointInfo(-18.34,-0),
			JointInfo(-0.29,0),JointInfo(11.62,-0),JointInfo(47.35,0),JointInfo(-104.14,0),JointInfo(5.29,0),JointInfo(-7.69,-0)
		},
		{	//905
			JointInfo(0.03,-0),
			JointInfo(-50.7,0),JointInfo(-0.4,-0),JointInfo(-0.17,-0),JointInfo(1.68,-0),
			JointInfo(-22.47,0),JointInfo(9.96,-0),JointInfo(15.33,0),JointInfo(-17.61,0),JointInfo(10.98,0),JointInfo(-13.37,-0),
			JointInfo(-45,0),
			JointInfo(-53.61,0),JointInfo(1.75,-0),JointInfo(-3.23,-0),JointInfo(-3.68,-0),
			JointInfo(-0.4,0),JointInfo(12.96,-0),JointInfo(8.08,0),JointInfo(-116.78,0),JointInfo(-23.37,0),JointInfo(-5.78,-0)
		},
		{	//910
			JointInfo(0.02,-0),
			JointInfo(-50.73,0),JointInfo(0.59,-0),JointInfo(-0.18,-0),JointInfo(-0.22,-0),
			JointInfo(-25.02,0),JointInfo(9.97,-0),JointInfo(13.35,0),JointInfo(-9.92,0),JointInfo(7.24,0),JointInfo(-13.86,-0),
			JointInfo(-45,0),
			JointInfo(-53.73,0),JointInfo(0.81,-0),JointInfo(-3.34,-0),JointInfo(-1.94,-0),
			JointInfo(-0.42,0),JointInfo(13.37,-0),JointInfo(-4.36,0),JointInfo(-120.7,0),JointInfo(-32.29,0),JointInfo(-5.2,-0)
		},
		{	//920
			JointInfo(0.01,-0),
			JointInfo(-50.74,0),JointInfo(0.96,-0),JointInfo(-0.18,-0),JointInfo(-0.93,-0),
			JointInfo(-26,0),JointInfo(9.98,-0),JointInfo(11.51,0),JointInfo(-2.76,0),JointInfo(3.75,0),JointInfo(-14.3,-0),
			JointInfo(-45,0),
			JointInfo(-53.77,0),JointInfo(0.45,-0),JointInfo(-3.38,-0),JointInfo(-1.27,-0),
			JointInfo(-0.42,0),JointInfo(13.76,-0),JointInfo(-15.97,0),JointInfo(-124.35,0),JointInfo(-40.62,0),JointInfo(-4.66,-0)
		},
		{	//923
			JointInfo(0,-0),
			JointInfo(-46.24,0),JointInfo(0.98,-0),JointInfo(-0.18,-0),JointInfo(-0.97,-0),
			JointInfo(-31.71,0),JointInfo(9.99,-0),JointInfo(11.02,0),JointInfo(-0.89,0),JointInfo(2.84,0),JointInfo(-14.42,-0),
			JointInfo(-45,0),
			JointInfo(-46.32,0),JointInfo(0.43,-0),JointInfo(-3.38,-0),JointInfo(-1.24,-0),
			JointInfo(-0.42,0),JointInfo(13.86,-0),JointInfo(-18.97,0),JointInfo(-127.14,0),JointInfo(-42.8,0),JointInfo(-4.51,-0)
		},
		{	//929
			JointInfo(0,-0),
			JointInfo(-88.38,0),JointInfo(1,-0),JointInfo(-0.18,-0),JointInfo(-0.99,-0),
			JointInfo(-17.22,0),JointInfo(17.26,-0),JointInfo(13.82,0),JointInfo(-40.45,0),JointInfo(-21.54,0),JointInfo(-19.64,-0),
			JointInfo(-45,0),
			JointInfo(-73.91,0),JointInfo(0.42,-0),JointInfo(-3.38,-0),JointInfo(-1.22,-0),
			JointInfo(-21.21,0),JointInfo(-5.22,-0),JointInfo(20.26,0),JointInfo(-93.57,0),JointInfo(-44.46,0),JointInfo(9.73,-0)
		},
		{	//931
			JointInfo(0,-0),
			JointInfo(-100.24,0),JointInfo(1,-0),JointInfo(-0.18,-0),JointInfo(-0.99,-0),
			JointInfo(-10.28,0),JointInfo(20.12,-0),JointInfo(7.25,0),JointInfo(-54.52,0),JointInfo(-30.49,0),JointInfo(-21.69,-0),
			JointInfo(-45,0),
			JointInfo(-87.92,0),JointInfo(0.42,-0),JointInfo(-3.39,-0),JointInfo(-1.21,-0),
			JointInfo(-30.19,0),JointInfo(-12.81,-0),JointInfo(34.01,0),JointInfo(-80.14,0),JointInfo(-31.43,0),JointInfo(15.33,-0)
		},
		{	//938
			JointInfo(0,-0),
			JointInfo(-111.38,0),JointInfo(1,-0),JointInfo(-0.18,-0),JointInfo(-1,-0),
			JointInfo(-1.11,0),JointInfo(23.89,-0),JointInfo(-18.86,0),JointInfo(-102.77,0),JointInfo(-42.32,0),JointInfo(-24.39,-0),
			JointInfo(-45,0),
			JointInfo(-114.02,0),JointInfo(0.42,-0),JointInfo(-3.39,-0),JointInfo(-1.21,-0),
			JointInfo(-67.51,0),JointInfo(-22.69,-0),JointInfo(79.32,0),JointInfo(-32.17,0),JointInfo(-25,0),JointInfo(20,-0)
		},
		{	//941
			JointInfo(-18.59,-0),
			JointInfo(-95.8,0),JointInfo(-7.67,-0),JointInfo(20.88,-0),JointInfo(6.88,-0),
			JointInfo(-0.69,0),JointInfo(11.41,-0),JointInfo(-2.26,0),JointInfo(-134.09,0),JointInfo(-21.24,0),JointInfo(-11.78,-0),
			JointInfo(-45,0),
			JointInfo(-97.23,0),JointInfo(6.82,-0),JointInfo(-24.38,-0),JointInfo(-7.98,-0),
			JointInfo(-46.42,0),JointInfo(-12.79,-0),JointInfo(70.59,0),JointInfo(-47.64,0),JointInfo(17.21,0),JointInfo(12.94,-0)
		},
};
//Angle leftFootShootingFromUT2[]=
//{
//		{	//985
//			JointInfo(-3.63,0),
//			JointInfo(-50.42,0),JointInfo(-29.79,0),JointInfo(1.53,0),JointInfo(49.53,0),
//			JointInfo(-0.01,0),JointInfo(-5.94,0),JointInfo(36.91,0),JointInfo(-70.05,0),JointInfo(38.08,0),JointInfo(5.94,0),
//			JointInfo(-45,0),
//			JointInfo(-50.42,0),JointInfo(29.8,0),JointInfo(-1.53,0),JointInfo(-49.53,0),
//			JointInfo(-0.01,0),JointInfo(5.89,0),JointInfo(36.98,0),JointInfo(-70.18,0),JointInfo(38.15,0),JointInfo(-5.89,0)
//		},
//		{	//992
//			JointInfo(-1.82,0),
//			JointInfo(-50.08,0),JointInfo(-29.96,0),JointInfo(0.28,0),JointInfo(49.91,0),
//			JointInfo(-0,0),JointInfo(6.8,0),JointInfo(36.98,0),JointInfo(-70.01,0),JointInfo(38.02,0),JointInfo(-6.93,0),
//			JointInfo(-45,0),
//			JointInfo(-50.08,0),JointInfo(29.96,0),JointInfo(-0.28,0),JointInfo(-49.91,0),
//			JointInfo(-0,0),JointInfo(9.47,0),JointInfo(37,0),JointInfo(-70.03,0),JointInfo(38.03,0),JointInfo(-9.21,0)
//		},
//		{	//998
//			JointInfo(-1,0),
//			JointInfo(-50.02,0),JointInfo(-29.99,0),JointInfo(0.07,0),JointInfo(49.98,0),
//			JointInfo(-0,0),JointInfo(9.25,0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38,0),JointInfo(-9.28,0),
//			JointInfo(-45,0),
//			JointInfo(-50.02,0),JointInfo(29.99,0),JointInfo(-0.06,0),JointInfo(-49.98,0),
//			JointInfo(-0,0),JointInfo(9.88,0),JointInfo(37,0),JointInfo(-70.01,0),JointInfo(38.01,0),JointInfo(-9.81,0)
//		},
//		{	//1006
//			JointInfo(-0.45,0),
//			JointInfo(-50,0),JointInfo(-30,0),JointInfo(0.01,0),JointInfo(50,0),
//			JointInfo(-0,0),JointInfo(9.89,0),JointInfo(37,0),JointInfo(-70,0),JointInfo(38,0),JointInfo(-9.89,0),
//			JointInfo(-45,0),
//			JointInfo(-50,0),JointInfo(30,0),JointInfo(-0.01,0),JointInfo(-50,0),
//			JointInfo(-0,0),JointInfo(9.98,0),JointInfo(50.58,0),JointInfo(-88.68,0),JointInfo(38,0),JointInfo(-9.97,0)
//		},
//		{	//1011
//			JointInfo(-0.28,0),
//			JointInfo(-50.51,0),JointInfo(-8.68,0),JointInfo(-0.12,0),JointInfo(17.58,0),
//			JointInfo(-4.46,0),JointInfo(9.95,0),JointInfo(22.85,0),JointInfo(-42.51,0),JointInfo(23.17,0),JointInfo(-11.8,0),
//			JointInfo(-45,0),
//			JointInfo(-52.6,0),JointInfo(9.66,0),JointInfo(-2.33,0),JointInfo(-18.34,0),
//			JointInfo(-0.29,0),JointInfo(11.62,0),JointInfo(46.9,0),JointInfo(-104.14,0),JointInfo(5.29,0),JointInfo(-7.68,0)
//		},
//		{	//1022
//			JointInfo(-0.09,0),
//			JointInfo(-50.72,0),JointInfo(0.33,0),JointInfo(-0.18,0),JointInfo(0.3,0),
//			JointInfo(-24.24,0),JointInfo(9.98,0),JointInfo(14.16,0),JointInfo(-12.47,0),JointInfo(8.5,0),JointInfo(-13.69,0),
//			JointInfo(-45,0),
//			JointInfo(-53.69,0),JointInfo(1.06,0),JointInfo(-3.31,0),JointInfo(-2.4,0),
//			JointInfo(-0.41,0),JointInfo(13.23,0),JointInfo(-0.33,0),JointInfo(-119.37,0),JointInfo(-29.27,0),JointInfo(-5.39,0)
//		},
//		{	//1034
//			JointInfo(-0.03,0),
//			JointInfo(-50.74,0),JointInfo(0.97,0),JointInfo(-0.18,0),JointInfo(-0.93,0),
//			JointInfo(-26,0),JointInfo(9.99,0),JointInfo(11.55,0),JointInfo(-2.75,0),JointInfo(3.75,0),JointInfo(-14.3,0),
//			JointInfo(-45,0),
//			JointInfo(-53.77,0),JointInfo(0.45,0),JointInfo(-3.38,0),JointInfo(-1.27,0),
//			JointInfo(-0.42,0),JointInfo(13.76,0),JointInfo(-16.01,0),JointInfo(-124.35,0),JointInfo(-40.62,0),JointInfo(-4.66,0)
//		},
//		{	//1037
//			JointInfo(-0.02,0),
//			JointInfo(-46.24,0),JointInfo(0.98,0),JointInfo(-0.18,0),JointInfo(-0.97,0),
//			JointInfo(-31.7,0),JointInfo(9.99,0),JointInfo(11.04,0),JointInfo(-0.88,0),JointInfo(2.84,0),JointInfo(-14.42,0),
//			JointInfo(-45,0),
//			JointInfo(-46.32,0),JointInfo(0.43,0),JointInfo(-3.38,0),JointInfo(-1.24,0),
//			JointInfo(-0.42,0),JointInfo(13.86,0),JointInfo(-18.99,0),JointInfo(-127.14,0),JointInfo(-42.79,0),JointInfo(-4.51,0)
//		},
//		{	//1040
//			JointInfo(-0.02,0),
//			JointInfo(-67.33,0),JointInfo(0.99,0),JointInfo(-0.18,0),JointInfo(-0.98,0),
//			JointInfo(-34.76,0),JointInfo(9.98,0),JointInfo(10.78,0),JointInfo(-19.37,0),JointInfo(-1.43,0),JointInfo(-14.48,0),
//			JointInfo(-45,0),
//			JointInfo(-52.93,0),JointInfo(0.42,0),JointInfo(-3.38,0),JointInfo(-1.22,0),
//			JointInfo(-0.42,0),JointInfo(13.91,0),JointInfo(-0.53,0),JointInfo(-113.92,0),JointInfo(-43.92,0),JointInfo(-4.44,0)
//		},
//		{	//1045
//			JointInfo(-0.01,0),
//			JointInfo(-100.24,0),JointInfo(1,0),JointInfo(-0.18,0),JointInfo(-0.99,0),
//			JointInfo(-10.28,0),JointInfo(20.12,0),JointInfo(7.21,0),JointInfo(-54.51,0),JointInfo(-30.53,0),JointInfo(-21.69,0),
//			JointInfo(-45,0),
//			JointInfo(-87.92,0),JointInfo(0.42,0),JointInfo(-3.38,0),JointInfo(-1.21,0),
//			JointInfo(-35.19,0),JointInfo(-12.81,0),JointInfo(34,0),JointInfo(-80.14,0),JointInfo(-31.43,0),JointInfo(15.33,0)
//		},
//		{	//1052
//			JointInfo(-0,0),
//			JointInfo(-111.38,0),JointInfo(1,0),JointInfo(-0.18,0),JointInfo(-1,0),
//			JointInfo(-1.11,0),JointInfo(23.9,0),JointInfo(-18.83,0),JointInfo(-102.76,0),JointInfo(-42.33,0),JointInfo(-24.4,0),
//			JointInfo(-45,0),
//			JointInfo(-114.02,0),JointInfo(0.42,0),JointInfo(-3.38,0),JointInfo(-1.21,0),
//			JointInfo(-67.51,0),JointInfo(-22.69,0),JointInfo(78.5,0),JointInfo(-32.15,0),JointInfo(-2.49,0),JointInfo(23.25,0)
//		},
//		{	//1061
//			JointInfo(-0,0),
//			JointInfo(-78.85,0),JointInfo(-11.06,0),JointInfo(56.32,0),JointInfo(13.09,0),
//			JointInfo(-3.26,0),JointInfo(0.21,0),JointInfo(13.38,0),JointInfo(-109.32,0),JointInfo(9.79,0),JointInfo(-0.43,0),
//			JointInfo(-45,0),
//			JointInfo(-79.19,0),JointInfo(15.27,0),JointInfo(-57.78,0),JointInfo(-13.34,0),
//			JointInfo(-15.07,0),JointInfo(-4.34,0),JointInfo(36.29,0),JointInfo(-67.96,0),JointInfo(40.27,0),JointInfo(4.53,0)
//		},
//};

Angle standUpFromUT[]=
{
		{	//206
			JointInfo(0,0),
			JointInfo(-50,0),JointInfo(-89.99,0),JointInfo(0,0),JointInfo(0,0),
			JointInfo(-0,0),JointInfo(-6,0),JointInfo(18,0),JointInfo(-30,0),JointInfo(18,0),JointInfo(6,0),
			JointInfo(-45,0),
			JointInfo(-50,0),JointInfo(89.99,0),JointInfo(-0,0),JointInfo(-0,0),
			JointInfo(-0,0),JointInfo(6,0),JointInfo(18,0),JointInfo(-30.01,0),JointInfo(18,0),JointInfo(-6,0)
		},
		{	//211
			JointInfo(0,0),
			JointInfo(-85.13,0),JointInfo(-58.07,0),JointInfo(0,0),JointInfo(-0.68,0),
			JointInfo(-0,0),JointInfo(-6,0),JointInfo(18.9,0),JointInfo(-30,0),JointInfo(18,0),JointInfo(6,0),
			JointInfo(-45,0),
			JointInfo(-85.13,0),JointInfo(58.07,0),JointInfo(-0,0),JointInfo(0.68,0),
			JointInfo(-0,0),JointInfo(6,0),JointInfo(18.9,0),JointInfo(-30,0),JointInfo(18,0),JointInfo(-6,0)
		},
		{	//220
			JointInfo(0,0),
			JointInfo(-114.98,0),JointInfo(-42.41,0),JointInfo(0,0),JointInfo(-0.96,0),
			JointInfo(-0,0),JointInfo(-6,0),JointInfo(80.13,0),JointInfo(-30,0),JointInfo(18,0),JointInfo(6,0),
			JointInfo(-45,0),
			JointInfo(-114.98,0),JointInfo(42.41,0),JointInfo(-0,0),JointInfo(0.96,0),
			JointInfo(-0,0),JointInfo(6,0),JointInfo(80.13,0),JointInfo(-30,0),JointInfo(18,0),JointInfo(-6,0)
		},
		{	//225
			JointInfo(0,0),
			JointInfo(-88.01,0),JointInfo(-25.12,0),JointInfo(0,0),JointInfo(-0.99,0),
			JointInfo(-35.13,0),JointInfo(-6,0),JointInfo(94.06,0),JointInfo(-51.07,0),JointInfo(-3.04,0),JointInfo(9.51,0),
			JointInfo(-45,0),
			JointInfo(-88.01,0),JointInfo(25.12,0),JointInfo(-0,0),JointInfo(0.99,0),
			JointInfo(-35.13,0),JointInfo(6,0),JointInfo(94.06,0),JointInfo(-51.07,0),JointInfo(-3.04,0),JointInfo(-9.51,0)
		},
		{	//236
			JointInfo(0,0),
			JointInfo(-10.65,0),JointInfo(-1.86,0),JointInfo(0,0),JointInfo(-1,0),
			JointInfo(-85.05,0),JointInfo(-6,0),JointInfo(99.59,0),JointInfo(-104.33,0),JointInfo(-41.79,0),JointInfo(12.92,0),
			JointInfo(-45,0),
			JointInfo(-10.65,0),JointInfo(1.86,0),JointInfo(-0,0),JointInfo(1,0),
			JointInfo(-85.06,0),JointInfo(6,0),JointInfo(99.59,0),JointInfo(-104.34,0),JointInfo(-41.78,0),JointInfo(-12.93,0)
		},
		{	//238
			JointInfo(0,0),
			JointInfo(3.42,0),JointInfo(-1.14,0),JointInfo(0,0),JointInfo(-1,0),
			JointInfo(-83.75,0),JointInfo(-6,0),JointInfo(85.92,0),JointInfo(-98.51,0),JointInfo(-28.02,0),JointInfo(13.02,0),
			JointInfo(-45,0),
			JointInfo(3.42,0),JointInfo(1.14,0),JointInfo(-0,0),JointInfo(1,0),
			JointInfo(-83.75,0),JointInfo(6,0),JointInfo(85.92,0),JointInfo(-98.51,0),JointInfo(-28.02,0),JointInfo(-13.02,0)
		},
		{	//245
			JointInfo(8.42,0),
			JointInfo(-37.52,0),JointInfo(-24.39,0),JointInfo(0,0),JointInfo(38.47,0),
			JointInfo(-42.39,0),JointInfo(-13.03,0),JointInfo(45.76,0),JointInfo(-65.66,0),JointInfo(15.44,0),JointInfo(7.36,0),
			JointInfo(-45,0),
			JointInfo(-37.52,0),JointInfo(24.39,0),JointInfo(-0,0),JointInfo(-38.47,0),
			JointInfo(-42.53,0),JointInfo(13.15,0),JointInfo(45.63,0),JointInfo(-65.66,0),JointInfo(15.44,0),JointInfo(-7.36,0)
		},
		{	//250
			JointInfo(10.37,0),
			JointInfo(-52.57,0),JointInfo(-17.07,0),JointInfo(35.09,0),JointInfo(22.53,0),
			JointInfo(-34.88,0),JointInfo(-17.81,0),JointInfo(21.61,0),JointInfo(-79.32,0),JointInfo(39.92,0),JointInfo(9.51,0),
			JointInfo(-45,0),
			JointInfo(-52.57,0),JointInfo(18.95,0),JointInfo(-35.13,0),JointInfo(-22.51,0),
			JointInfo(-34.93,0),JointInfo(14.59,0),JointInfo(16.62,0),JointInfo(-61.55,0),JointInfo(33.1,0),JointInfo(-6.72,0)
		},
};



Angle nexLTest[]=
{
		{ //1
				JointInfo(0.98,0),
				JointInfo(-51.00,0),JointInfo(-10.65,0),JointInfo(54.89,0),JointInfo(16.04,0),
				JointInfo(-0.00,0),JointInfo(5.74,0),JointInfo(27.51,0),JointInfo(-63.81,0),JointInfo(39.54,0),JointInfo(-5.74,0),
				JointInfo(-25.00,0),
				JointInfo(-63.44,0),JointInfo(29.36,0),JointInfo(-54.86,0),JointInfo(-15.94,0),
				JointInfo(-0.00,0),JointInfo(4.80,0),JointInfo(28.83,0),JointInfo(-73.77,0),JointInfo(44.02,0),JointInfo(-4.80,0),
			},
			{ //6
				JointInfo(7.48,0),
				JointInfo(-33.30,0),JointInfo(-5.03,0),JointInfo(19.76,0),JointInfo(7.58,0),
				JointInfo(-0.00,0),JointInfo(9.18,0),JointInfo(28.26,0),JointInfo(-54.30,0),JointInfo(34.84,0),JointInfo(-9.18,0),
				JointInfo(-25.00,0),
				JointInfo(-53.44,0),JointInfo(34.98,0),JointInfo(-19.73,0),JointInfo(-7.53,0),
				JointInfo(-0.00,0),JointInfo(7.67,0),JointInfo(30.66,0),JointInfo(-71.04,0),JointInfo(41.79,0),JointInfo(-7.68,0),
			},
			{ //11
				JointInfo(13.60,0),
				JointInfo(-23.37,0),JointInfo(-1.88,0),JointInfo(-5.24,0),JointInfo(2.82,0),
				JointInfo(-0.00,0),JointInfo(11.11,0),JointInfo(28.68,0),JointInfo(-48.96,0),JointInfo(32.20,0),JointInfo(-11.12,0),
				JointInfo(-25.00,0),
				JointInfo(-47.84,0),JointInfo(38.13,0),JointInfo(5.21,0),JointInfo(-2.80,0),
				JointInfo(-0.00,0),JointInfo(9.29,0),JointInfo(31.69,0),JointInfo(-69.52,0),JointInfo(40.54,0),JointInfo(-9.30,0),
			},
			{ //16
				JointInfo(3.43,0),
				JointInfo(-18.90,0),JointInfo(-0.46,0),JointInfo(-16.39,0),JointInfo(0.68,0),
				JointInfo(-0.00,0),JointInfo(11.97,0),JointInfo(28.87,0),JointInfo(-46.56,0),JointInfo(31.01,0),JointInfo(-11.98,0),
				JointInfo(-25.00,0),
				JointInfo(-45.32,0),JointInfo(39.55,0),JointInfo(16.39,0),JointInfo(-0.68,0),
				JointInfo(-0.00,0),JointInfo(10.02,0),JointInfo(32.15,0),JointInfo(-68.83,0),JointInfo(39.98,0),JointInfo(-10.03,0),
			},
			{ //21
				JointInfo(-2.93,0),
				JointInfo(-17.69,0),JointInfo(-0.11,0),JointInfo(-19.65,0),JointInfo(0.08,0),
				JointInfo(-0.00,0),JointInfo(12.24,0),JointInfo(28.91,0),JointInfo(-45.88,0),JointInfo(30.69,0),JointInfo(-12.25,0),
				JointInfo(-25.00,0),
				JointInfo(-44.60,0),JointInfo(39.90,0),JointInfo(19.62,0),JointInfo(-0.06,0),
				JointInfo(-0.00,0),JointInfo(10.20,0),JointInfo(32.29,0),JointInfo(-68.63,0),JointInfo(39.85,0),JointInfo(-10.21,0),
			},
			{ //24
				JointInfo(7.37,0),
				JointInfo(-17.50,0),JointInfo(-0.04,0),JointInfo(-20.03,0),JointInfo(-0.02,0),
				JointInfo(-0.00,0),JointInfo(12.27,0),JointInfo(28.90,0),JointInfo(-45.83,0),JointInfo(30.71,0),JointInfo(-12.28,0),
				JointInfo(-25.00,0),
				JointInfo(-44.50,0),JointInfo(39.97,0),JointInfo(20.02,0),JointInfo(0.03,0),
				JointInfo(-0.00,0),JointInfo(10.24,0),JointInfo(32.87,0),JointInfo(-89.66,0),JointInfo(42.02,0),JointInfo(-10.25,0),
			},
			{ //26
				JointInfo(8.69,0),
				JointInfo(-17.30,0),JointInfo(0.26,0),JointInfo(-18.93,0),JointInfo(0.12,0),
				JointInfo(-0.00,0),JointInfo(12.10,0),JointInfo(28.83,0),JointInfo(-46.20,0),JointInfo(31.13,0),JointInfo(-12.07,0),
				JointInfo(-25.00,0),
				JointInfo(-44.61,0),JointInfo(40.26,0),JointInfo(19.15,0),JointInfo(-0.26,0),
				JointInfo(-0.00,0),JointInfo(10.39,0),JointInfo(18.82,0),JointInfo(-103.61,0),JointInfo(40.00,0),JointInfo(-10.40,0),
			},
			{ //31
				JointInfo(1.61,0),
				JointInfo(-18.72,0),JointInfo(-31.17,0),JointInfo(-19.51,0),JointInfo(0.06,0),
				JointInfo(-13.05,0),JointInfo(11.24,0),JointInfo(20.46,0),JointInfo(-24.25,0),JointInfo(16.27,0),JointInfo(-11.23,0),
				JointInfo(-25.00,0),
				JointInfo(-60.77,0),JointInfo(26.09,0),JointInfo(19.61,0),JointInfo(-0.12,0),
				JointInfo(-0.00,0),JointInfo(19.67,0),JointInfo(-0.24,0),JointInfo(-113.60,0),JointInfo(16.66,0),JointInfo(-10.32,0),
			},
			{ //36
				JointInfo(9.73,0),
				JointInfo(-19.55,0),JointInfo(-51.67,0),JointInfo(-19.77,0),JointInfo(0.03,0),
				JointInfo(-20.89,0),JointInfo(10.72,0),JointInfo(15.44,0),JointInfo(-11.11,0),JointInfo(7.38,0),JointInfo(-10.71,0),
				JointInfo(-25.00,0),
				JointInfo(-70.50,0),JointInfo(17.59,0),JointInfo(19.82,0),JointInfo(-0.05,0),
				JointInfo(-0.00,0),JointInfo(25.26,0),JointInfo(-12.71,0),JointInfo(-120.90,0),JointInfo(-13.99,0),JointInfo(-10.29,0),
			},
			{ //41
				JointInfo(-9.29,0),
				JointInfo(-20.01,0),JointInfo(-63.17,0),JointInfo(-19.91,0),JointInfo(0.01,0),
				JointInfo(-25.28,0),JointInfo(10.42,0),JointInfo(12.62,0),JointInfo(-3.74,0),JointInfo(2.39,0),JointInfo(-10.42,0),
				JointInfo(-25.00,0),
				JointInfo(-75.95,0),JointInfo(12.83,0),JointInfo(19.93,0),JointInfo(-0.02,0),
				JointInfo(-0.00,0),JointInfo(28.39,0),JointInfo(-19.82,0),JointInfo(-125.01,0),JointInfo(-31.63,0),JointInfo(-10.27,0),
			},
			{ //46
				JointInfo(-8.77,0),
				JointInfo(-20.22,0),JointInfo(-68.34,0),JointInfo(-19.98,0),JointInfo(0.00,0),
				JointInfo(-27.26,0),JointInfo(10.29,0),JointInfo(11.35,0),JointInfo(-0.43,0),JointInfo(0.15,0),JointInfo(-10.29,0),
				JointInfo(-25.00,0),
				JointInfo(-78.40,0),JointInfo(10.69,0),JointInfo(19.98,0),JointInfo(-0.01,0),
				JointInfo(-0.00,0),JointInfo(29.80,0),JointInfo(-23.01,0),JointInfo(-126.86,0),JointInfo(-39.57,0),JointInfo(-10.26,0),
			},
			{ //51
				JointInfo(-22.43,0),
				JointInfo(-20.30,0),JointInfo(-69.78,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-27.80,0),JointInfo(10.27,0),JointInfo(11.01,0),JointInfo(0.54,0),JointInfo(-0.47,0),JointInfo(-10.27,0),
				JointInfo(-25.00,0),
				JointInfo(-79.10,0),JointInfo(10.07,0),JointInfo(20.02,0),JointInfo(0.03,0),
				JointInfo(-0.00,0),JointInfo(30.20,0),JointInfo(-23.94,0),JointInfo(-127.37,0),JointInfo(-41.82,0),JointInfo(-10.26,0),
			},
			{ //71
				JointInfo(-11.59,0),
				JointInfo(-20.29,0),JointInfo(-69.99,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-27.89,0),JointInfo(10.25,0),JointInfo(10.95,0),JointInfo(0.68,0),JointInfo(-0.60,0),JointInfo(-10.25,0),
				JointInfo(-25.00,0),
				JointInfo(-79.22,0),JointInfo(10.02,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-0.00,0),JointInfo(30.25,0),JointInfo(-24.08,0),JointInfo(-127.43,0),JointInfo(-42.15,0),JointInfo(-10.26,0),
			},
			{ //72
				JointInfo(-7.58,0),
				JointInfo(-18.73,0),JointInfo(-69.99,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-30.07,0),JointInfo(7.95,0),JointInfo(10.92,0),JointInfo(0.75,0),JointInfo(-0.64,0),JointInfo(-10.25,0),
				JointInfo(-25.00,0),
				JointInfo(-76.62,0),JointInfo(10.02,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(2.83,0),JointInfo(28.30,0),JointInfo(-27.57,0),JointInfo(-124.71,0),JointInfo(-39.08,0),JointInfo(-10.26,0),
			},
			{ //73
				JointInfo(-11.59,0),
				JointInfo(-17.47,0),JointInfo(-69.99,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-31.57,0),JointInfo(3.96,0),JointInfo(10.90,0),JointInfo(0.82,0),JointInfo(-0.67,0),JointInfo(-10.25,0),
				JointInfo(-25.00,0),
				JointInfo(-74.54,0),JointInfo(10.02,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(0.03,0),JointInfo(24.47,0),JointInfo(-24.08,0),JointInfo(-121.80,0),JointInfo(-46.10,0),JointInfo(-10.26,0),
			},
			{ //74
				JointInfo(-13.26,0),
				JointInfo(-24.50,0),JointInfo(-69.99,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-30.87,0),JointInfo(5.24,0),JointInfo(12.30,0),JointInfo(-3.03,0),JointInfo(-3.53,0),JointInfo(-10.25,0),
				JointInfo(-25.00,0),
				JointInfo(-76.82,0),JointInfo(10.02,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-2.81,0),JointInfo(22.77,0),JointInfo(-17.84,0),JointInfo(-114.84,0),JointInfo(-39.28,0),JointInfo(-10.26,0),
			},
			{ //76
				JointInfo(-11.06,0),
				JointInfo(-38.56,0),JointInfo(-69.98,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-29.44,0),JointInfo(7.78,0),JointInfo(13.14,0),JointInfo(-16.67,0),JointInfo(-9.10,0),JointInfo(-10.25,0),
				JointInfo(-25.00,0),
				JointInfo(-81.15,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0.00,0),
				JointInfo(4.59,0),JointInfo(17.01,0),JointInfo(-3.90,0),JointInfo(-109.35,0),JointInfo(-40.07,0),JointInfo(-10.26,0),
			},
			{ //80
				JointInfo(-9.53,0),
				JointInfo(-65.95,0),JointInfo(-69.98,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-11.43,0),JointInfo(11.16,0),JointInfo(5.21,0),JointInfo(-44.76,0),JointInfo(-31.96,0),JointInfo(-19.07,0),
				JointInfo(-25.00,0),
				JointInfo(-109.14,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0.00,0),
				JointInfo(-17.86,0),JointInfo(-5.95,0),JointInfo(23.75,0),JointInfo(-82.34,0),JointInfo(-33.5,0),JointInfo(10.67,0),
			},
			{ //83
				JointInfo(-13.51,0),
				JointInfo(-77.08,0),JointInfo(-69.98,0),JointInfo(-20.00,0),JointInfo(0.00,0),
				JointInfo(-3.25,0),JointInfo(9.53,0),JointInfo(-10.70,0),JointInfo(-65.82,0),JointInfo(-39.82,0),JointInfo(-22.11,0),
				JointInfo(-25.00,0),
				JointInfo(-116.17,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0.00,0),
				JointInfo(-41.77,0),JointInfo(-21.29,0),JointInfo(44.29,0),JointInfo(-62.29,0),JointInfo(-27.35,0),JointInfo(17.83,0),
			},
			{ //84
				JointInfo(-17.50,0),
				JointInfo(-78.45,0),JointInfo(-69.98,0),JointInfo(-20.00,0),JointInfo(0.00,0),
				JointInfo(3.32,0),JointInfo(14.52,0),JointInfo(-14.29,0),JointInfo(-72.84,0),JointInfo(-41.40,0),JointInfo(-22.73,0),
				JointInfo(-25.00,0),
				JointInfo(-120.71,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0.00,0),
				JointInfo(-47.01,0),JointInfo(-26.81,0),JointInfo(51.19,0),JointInfo(-55.54,0),JointInfo(-20.81,0),JointInfo(19.38,0),
			},
			{ //86
				JointInfo(-17.47,0),
				JointInfo(-78.46,0),JointInfo(-69.98,0),JointInfo(-20.00,0),JointInfo(0.00,0),
				JointInfo(9.77,0),JointInfo(14.52,0),JointInfo(-14.25,0),JointInfo(-86.83,0),JointInfo(-41.40,0),JointInfo(-22.73,0),
				JointInfo(-25.00,0),
				JointInfo(-116.22,0),JointInfo(10.01,0),JointInfo(20.01,0),JointInfo(0.00,0),
				JointInfo(-47.04,0),JointInfo(-21.21,0),JointInfo(51.19,0),JointInfo(-55.49,0),JointInfo(-20.76,0),JointInfo(19.25,0),
			},
};
Angle nexRTest[]=
{
		{ //1
				JointInfo(-0.98,0),
				JointInfo(-63.44,0),JointInfo(-29.36,0),JointInfo(54.86,0),JointInfo(15.94,0),
				JointInfo(-0.00,0),JointInfo(-4.80,0),JointInfo(28.83,0),JointInfo(-73.77,0),JointInfo(44.02,0),JointInfo(4.80,0),
				JointInfo(-25.00,0),
				JointInfo(-51.00,0),JointInfo(10.65,0),JointInfo(-54.89,0),JointInfo(-16.04,0),
				JointInfo(-0.00,0),JointInfo(-5.74,0),JointInfo(27.51,0),JointInfo(-63.81,0),JointInfo(39.54,0),JointInfo(5.74,0),
			},
			{ //6
				JointInfo(-7.48,0),
				JointInfo(-53.44,0),JointInfo(-34.98,0),JointInfo(19.73,0),JointInfo(7.53,0),
				JointInfo(-0.00,0),JointInfo(-7.67,0),JointInfo(30.66,0),JointInfo(-71.04,0),JointInfo(41.79,0),JointInfo(7.68,0),
				JointInfo(-25.00,0),
				JointInfo(-33.30,0),JointInfo(5.03,0),JointInfo(-19.76,0),JointInfo(-7.58,0),
				JointInfo(-0.00,0),JointInfo(-9.18,0),JointInfo(28.26,0),JointInfo(-54.30,0),JointInfo(34.84,0),JointInfo(9.18,0),
			},
			{ //11
				JointInfo(-13.60,0),
				JointInfo(-47.84,0),JointInfo(-38.13,0),JointInfo(-5.21,0),JointInfo(2.80,0),
				JointInfo(-0.00,0),JointInfo(-9.29,0),JointInfo(31.69,0),JointInfo(-69.52,0),JointInfo(40.54,0),JointInfo(9.30,0),
				JointInfo(-25.00,0),
				JointInfo(-23.37,0),JointInfo(1.88,0),JointInfo(5.24,0),JointInfo(-2.82,0),
				JointInfo(-0.00,0),JointInfo(-11.11,0),JointInfo(28.68,0),JointInfo(-48.96,0),JointInfo(32.20,0),JointInfo(11.12,0),
			},
			{ //16
				JointInfo(-3.43,0),
				JointInfo(-45.32,0),JointInfo(-39.55,0),JointInfo(-16.39,0),JointInfo(0.68,0),
				JointInfo(-0.00,0),JointInfo(-10.02,0),JointInfo(32.15,0),JointInfo(-68.83,0),JointInfo(39.98,0),JointInfo(10.03,0),
				JointInfo(-25.00,0),
				JointInfo(-18.90,0),JointInfo(0.46,0),JointInfo(16.39,0),JointInfo(-0.68,0),
				JointInfo(-0.00,0),JointInfo(-11.97,0),JointInfo(28.87,0),JointInfo(-46.56,0),JointInfo(31.01,0),JointInfo(11.98,0),
			},
			{ //21
				JointInfo(2.93,0),
				JointInfo(-44.60,0),JointInfo(-39.90,0),JointInfo(-19.62,0),JointInfo(0.06,0),
				JointInfo(-0.00,0),JointInfo(-10.20,0),JointInfo(32.29,0),JointInfo(-68.63,0),JointInfo(39.85,0),JointInfo(10.21,0),
				JointInfo(-25.00,0),
				JointInfo(-17.69,0),JointInfo(0.11,0),JointInfo(19.65,0),JointInfo(-0.08,0),
				JointInfo(-0.00,0),JointInfo(-12.24,0),JointInfo(28.91,0),JointInfo(-45.88,0),JointInfo(30.69,0),JointInfo(12.25,0),
			},
			{ //24
				JointInfo(-7.37,0),
				JointInfo(-44.50,0),JointInfo(-39.97,0),JointInfo(-20.02,0),JointInfo(-0.03,0),
				JointInfo(-0.00,0),JointInfo(-10.24,0),JointInfo(32.87,0),JointInfo(-89.66,0),JointInfo(42.02,0),JointInfo(10.25,0),
				JointInfo(-25.00,0),
				JointInfo(-17.50,0),JointInfo(0.04,0),JointInfo(20.03,0),JointInfo(0.02,0),
				JointInfo(-0.00,0),JointInfo(-12.27,0),JointInfo(28.90,0),JointInfo(-45.83,0),JointInfo(30.71,0),JointInfo(12.28,0),
			},
			{ //26
				JointInfo(-8.69,0),
				JointInfo(-44.61,0),JointInfo(-40.26,0),JointInfo(-19.15,0),JointInfo(0.26,0),
				JointInfo(-0.00,0),JointInfo(-10.39,0),JointInfo(18.82,0),JointInfo(-103.61,0),JointInfo(40.00,0),JointInfo(10.40,0),
				JointInfo(-25.00,0),
				JointInfo(-17.30,0),JointInfo(-0.26,0),JointInfo(18.93,0),JointInfo(-0.12,0),
				JointInfo(-0.00,0),JointInfo(-12.10,0),JointInfo(28.83,0),JointInfo(-46.20,0),JointInfo(31.13,0),JointInfo(12.07,0),
			},
			{ //31
				JointInfo(-1.61,0),
				JointInfo(-60.77,0),JointInfo(-26.09,0),JointInfo(-19.61,0),JointInfo(0.12,0),
				JointInfo(-0.00,0),JointInfo(-19.67,0),JointInfo(-0.24,0),JointInfo(-113.60,0),JointInfo(16.66,0),JointInfo(10.32,0),
				JointInfo(-25.00,0),
				JointInfo(-18.72,0),JointInfo(31.17,0),JointInfo(19.51,0),JointInfo(-0.06,0),
				JointInfo(-13.05,0),JointInfo(-11.24,0),JointInfo(20.46,0),JointInfo(-24.25,0),JointInfo(16.27,0),JointInfo(11.23,0),
			},
			{ //36
				JointInfo(-9.73,0),
				JointInfo(-70.50,0),JointInfo(-17.59,0),JointInfo(-19.82,0),JointInfo(0.05,0),
				JointInfo(-0.00,0),JointInfo(-25.26,0),JointInfo(-12.71,0),JointInfo(-120.90,0),JointInfo(-13.99,0),JointInfo(10.29,0),
				JointInfo(-25.00,0),
				JointInfo(-19.55,0),JointInfo(51.67,0),JointInfo(19.77,0),JointInfo(-0.03,0),
				JointInfo(-20.89,0),JointInfo(-10.72,0),JointInfo(15.44,0),JointInfo(-11.11,0),JointInfo(7.38,0),JointInfo(10.71,0),
			},
			{ //41
				JointInfo(9.29,0),
				JointInfo(-75.95,0),JointInfo(-12.83,0),JointInfo(-19.93,0),JointInfo(0.02,0),
				JointInfo(-0.00,0),JointInfo(-28.39,0),JointInfo(-19.82,0),JointInfo(-125.01,0),JointInfo(-31.63,0),JointInfo(10.27,0),
				JointInfo(-25.00,0),
				JointInfo(-20.01,0),JointInfo(63.17,0),JointInfo(19.91,0),JointInfo(-0.01,0),
				JointInfo(-25.28,0),JointInfo(-10.42,0),JointInfo(12.62,0),JointInfo(-3.74,0),JointInfo(2.39,0),JointInfo(10.42,0),
			},
			{ //46
				JointInfo(8.77,0),
				JointInfo(-78.40,0),JointInfo(-10.69,0),JointInfo(-19.98,0),JointInfo(0.01,0),
				JointInfo(-0.00,0),JointInfo(-29.80,0),JointInfo(-23.01,0),JointInfo(-126.86,0),JointInfo(-39.57,0),JointInfo(10.26,0),
				JointInfo(-25.00,0),
				JointInfo(-20.22,0),JointInfo(68.34,0),JointInfo(19.98,0),JointInfo(-0.00,0),
				JointInfo(-27.26,0),JointInfo(-10.29,0),JointInfo(11.35,0),JointInfo(-0.43,0),JointInfo(0.15,0),JointInfo(10.29,0),
			},
			{ //51
				JointInfo(22.43,0),
				JointInfo(-79.10,0),JointInfo(-10.07,0),JointInfo(-20.02,0),JointInfo(-0.03,0),
				JointInfo(-0.00,0),JointInfo(-30.20,0),JointInfo(-23.94,0),JointInfo(-127.37,0),JointInfo(-41.82,0),JointInfo(10.26,0),
				JointInfo(-25.00,0),
				JointInfo(-20.30,0),JointInfo(69.78,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-27.80,0),JointInfo(-10.27,0),JointInfo(11.01,0),JointInfo(0.54,0),JointInfo(-0.47,0),JointInfo(10.27,0),
			},
			{ //71
				JointInfo(11.59,0),
				JointInfo(-79.22,0),JointInfo(-10.02,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-0.00,0),JointInfo(-30.25,0),JointInfo(-24.08,0),JointInfo(-127.43,0),JointInfo(-42.15,0),JointInfo(10.26,0),
				JointInfo(-25.00,0),
				JointInfo(-20.29,0),JointInfo(69.99,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-27.89,0),JointInfo(-10.25,0),JointInfo(10.95,0),JointInfo(0.68,0),JointInfo(-0.60,0),JointInfo(10.25,0),
			},
			{ //72
				JointInfo(7.58,0),
				JointInfo(-76.62,0),JointInfo(-10.02,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(2.83,0),JointInfo(-28.30,0),JointInfo(-27.57,0),JointInfo(-124.71,0),JointInfo(-39.08,0),JointInfo(10.26,0),
				JointInfo(-25.00,0),
				JointInfo(-18.73,0),JointInfo(69.99,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-30.07,0),JointInfo(-7.95,0),JointInfo(10.92,0),JointInfo(0.75,0),JointInfo(-0.64,0),JointInfo(10.25,0),
			},
			{ //73
				JointInfo(11.59,0),
				JointInfo(-74.54,0),JointInfo(-10.02,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(0.03,0),JointInfo(-24.47,0),JointInfo(-24.08,0),JointInfo(-121.80,0),JointInfo(-46.10,0),JointInfo(10.26,0),
				JointInfo(-25.00,0),
				JointInfo(-17.47,0),JointInfo(69.99,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-31.57,0),JointInfo(-3.96,0),JointInfo(10.90,0),JointInfo(0.82,0),JointInfo(-0.67,0),JointInfo(10.25,0),
			},
			{ //74
				JointInfo(13.26,0),
				JointInfo(-76.82,0),JointInfo(-10.02,0),JointInfo(-20.00,0),JointInfo(-0.00,0),
				JointInfo(-2.81,0),JointInfo(-22.77,0),JointInfo(-17.84,0),JointInfo(-114.84,0),JointInfo(-39.28,0),JointInfo(10.26,0),
				JointInfo(-25.00,0),
				JointInfo(-24.50,0),JointInfo(69.99,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-30.87,0),JointInfo(-5.24,0),JointInfo(12.30,0),JointInfo(-3.03,0),JointInfo(-3.53,0),JointInfo(10.25,0),
			},
			{ //76
				JointInfo(11.06,0),
				JointInfo(-81.15,0),JointInfo(-10.01,0),JointInfo(-20.01,0),JointInfo(-0.00,0),
				JointInfo(4.59,0),JointInfo(-17.01,0),JointInfo(-3.90,0),JointInfo(-109.35,0),JointInfo(-40.07,0),JointInfo(10.26,0),
				JointInfo(-25.00,0),
				JointInfo(-38.56,0),JointInfo(69.98,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-29.44,0),JointInfo(-7.78,0),JointInfo(13.14,0),JointInfo(-16.67,0),JointInfo(-9.10,0),JointInfo(10.25,0),
			},
			{ //80
				JointInfo(9.53,0),
				JointInfo(-109.14,0),JointInfo(-10.01,0),JointInfo(-20.01,0),JointInfo(-0.00,0),
				JointInfo(-17.86,0),JointInfo(5.95,0),JointInfo(23.75,0),JointInfo(-82.34,0),JointInfo(-33.5,0),JointInfo(-10.67,0),
				JointInfo(-25.00,0),
				JointInfo(-65.95,0),JointInfo(69.98,0),JointInfo(20.00,0),JointInfo(0.00,0),
				JointInfo(-11.43,0),JointInfo(-11.16,0),JointInfo(5.21,0),JointInfo(-44.76,0),JointInfo(-31.96,0),JointInfo(19.07,0),
			},
			{ //83
				JointInfo(13.51,0),
				JointInfo(-116.17,0),JointInfo(-10.01,0),JointInfo(-20.01,0),JointInfo(-0.00,0),
				JointInfo(-41.77,0),JointInfo(21.29,0),JointInfo(44.29,0),JointInfo(-62.29,0),JointInfo(-27.35,0),JointInfo(-17.83,0),
				JointInfo(-25.00,0),
				JointInfo(-77.08,0),JointInfo(69.98,0),JointInfo(20.00,0),JointInfo(-0.00,0),
				JointInfo(-3.25,0),JointInfo(-9.53,0),JointInfo(-10.70,0),JointInfo(-65.82,0),JointInfo(-39.82,0),JointInfo(22.11,0),
			},
			{ //84
				JointInfo(17.50,0),
				JointInfo(-120.71,0),JointInfo(-10.01,0),JointInfo(-20.01,0),JointInfo(-0.00,0),
				JointInfo(-47.01,0),JointInfo(26.81,0),JointInfo(51.19,0),JointInfo(-55.54,0),JointInfo(-20.81,0),JointInfo(-19.38,0),
				JointInfo(-25.00,0),
				JointInfo(-78.45,0),JointInfo(69.98,0),JointInfo(20.00,0),JointInfo(-0.00,0),
				JointInfo(3.32,0),JointInfo(-14.52,0),JointInfo(-14.29,0),JointInfo(-72.84,0),JointInfo(-41.40,0),JointInfo(22.73,0),
			},
			{ //86
				JointInfo(17.47,0),
				JointInfo(-116.22,0),JointInfo(-10.01,0),JointInfo(-20.01,0),JointInfo(-0.00,0),
				JointInfo(-47.04,0),JointInfo(21.21,0),JointInfo(51.19,0),JointInfo(-55.49,0),JointInfo(-20.76,0),JointInfo(-19.25,0),
				JointInfo(-25.00,0),
				JointInfo(-78.46,0),JointInfo(69.98,0),JointInfo(20.00,0),JointInfo(-0.00,0),
				JointInfo(9.77,0),JointInfo(-14.52,0),JointInfo(-14.25,0),JointInfo(-86.83,0),JointInfo(-41.40,0),JointInfo(22.73,0),
			},
};



Angle RoboCansRight[]=
 {
		 {	//2639 0
		 	{-32.51,-0},
		 	{-90.27,0},{0.36,-0},{63.21,-0},{-2.96,-0},
		 	{1.29,0},{-0.91,-0},{31.92,0},{-43.2,0},{43.07,0},{13.97,-0},
		 	{-22.83,0},
		 	{-107.86,0},{31.08,-0},{-63.19,-0},{1,-0},
		 	{-1.99,0},{-5.59,-0},{25.16,0},{-24.07,0},{18.89,0},{9,-0}
		 },
		 {	//2654 1
		 	{-14.48,-0},
		 	{-75.38,0},{-5.41,-0},{83.41,-0},{9.17,-0},
		 	{1.32,0},{-21.87,-0},{29.47,0},{-84.35,0},{14.02,0},{36.75,-0},
		 	{-27.1,0},
		 	{-112.89,0},{9.09,-0},{-114.28,-0},{7.99,-0},
		 	{-10.57,0},{-8.69,-0},{15.44,0},{-2.61,0},{13.19,0},{16.15,-0}
		 },
		 {	//2655 2
		 	{-13.24,-0},
		 	{-82.4,0},{-12.4,-0},{88.08,-0},{12.46,-0},
		 	{-5.69,0},{-15.17,-0},{30.66,0},{-77.4,0},{7.07,0},{29.76,-0},
		 	{-27.44,0},
		 	{-105.88,0},{14.2,-0},{-107.3,-0},{1.16,-0},
		 	{-8.95,0},{-1.83,-0},{15.2,0},{-3.46,0},{12.3,0},{16.15,-0}
		 },
		 {	//2656
		 	{-12.34,-0},
		 	{-89.43,0},{-17.04,-0},{91.51,-0},{13.58,-0},
		 	{0.27,0},{-8.41,-0},{34.89,0},{-70.45,0},{0.71,0},{22.79,-0},
		 	{-27.69,0},
		 	{-98.89,0},{17.05,-0},{-100.8,-0},{1.03,-0},
		 	{-6.39,0},{3.49,-0},{11.96,0},{-6.32,0},{12.12,0},{15.24,-0}
		 },
		 {	//2657 3
		 	{-11.93,-0},
		 	{-96.46,0},{-18.69,-0},{93.17,-0},{12.48,-0},
		 	{4.24,0},{-2.4,-0},{41.84,0},{-63.55,0},{-4.23,0},{15.92,-0},
		 	{-27.17,0},
		 	{-91.92,0},{17.16,-0},{-96.82,-0},{1,-0},
		 	{-3.16,0},{6.48,-0},{6.37,0},{-10.91,0},{13.95,0},{13.5,-0}
		 },
		 {	//2658  4//carefull pengqiu kaishi
		 	{-11.92,-0},
		 	{-103.48,0},{-18.16,-0},{93.45,-0},{9.91,-0},
		 	{0.23,0},{3.1,-0},{48.74,0},{-56.78,0},{-7.45,0},{9.38,-0},
		 	{-26.61,0},
		 	{-84.96,0},{15.33,-0},{-95.19,-0},{1,-0},
		 	{0.58,0},{7.66,-0},{-0.72,0},{-16.47,0},{17.48,0},{11.26,-0}
		 },
		 {	//2659 5//pengqiu jieshu
		 	{-12.04,-0},
		 	{-109.77,0},{-16.31,-0},{92.92,-0},{6.48,-0},
		 	{-6.78,0},{7.93,-0},{55.51,0},{-50.08,0},{-9.69,0},{4.27,-0},
		 	{-26.26,0},
		 	{-78,0},{12.3,-0},{-95.14,-0},{3.22,-0},
		 	{4.25,0},{7.77,-0},{-7.45,0},{-22.64,0},{22.22,0},{8.71,-0}
		 },
		 {	//2660 6
		 	{-19.05,-0},
		 	{-115.05,0},{-13.93,-0},{92.02,-0},{2.77,-0},
		 	{-13.78,0},{12.43,-0},{62.43,0},{-43.29,0},{-11.49,0},{-6.39,-0},
		 	{-23.33,0},
		 	{-71.01,0},{8.79,-0},{-95.92,-0},{1,-0},
		 	{0.56,0},{7.39,-0},{-14.45,0},{-28.92,0},{27.47,0},{6.08,-0}
		 },
		 {	//2661 7
		 	{-25.71,-0},
		 	{-119.32,0},{-11.54,-0},{91.08,-0},{-0.87,-0},
		 	{-20.78,0},{16.56,-0},{69.32,0},{-36.54,0},{-13.01,0},{-12.22,-0},
		 	{-20.49,0},
		 	{-64.03,0},{5.4,-0},{-96.96,-0},{0.26,-0},
		 	{3.99,0},{6.89,-0},{-21.48,0},{-34.81,0},{32.59,0},{3.61,-0}
		 },
		 {	//2662 8
		 	{-30.24,-0},
		 	{-122.85,0},{-13.29,-0},{96.1,-0},{4.48,-0},
		 	{-16.35,0},{9.55,-0},{75.36,0},{-29.57,0},{-19.98,0},{-11.33,-0},
		 	{-18.56,0},
		 	{-57.06,0},{4.45,-0},{-99.07,-0},{-0.75,-0},
		 	{0.53,0},{2.1,-0},{-34.97,0},{-27.8,0},{31.38,0},{-3.4,-0}
		 },
		 {	//2663 9
		 	{-25.93,-0},
		 	{-119.33,0},{-15.11,-0},{99.21,-0},{9.04,-0},
		 	{-13.05,0},{2.91,-0},{76.66,0},{-23.41,0},{-22.03,0},{-7.31,-0},
		 	{-23.46,0},
		 	{-56.04,0},{2.63,-0},{-101.81,-0},{-0.6,-0},
		 	{11.69,0},{-2.13,-0},{-21.54,0},{-26.13,0},{28.8,0},{-8.59,-0}
		 },
		 {	//2664 10 shoujiao
		 	{-20.48,-0},
		 	{-112.31,0},{-15.86,-0},{99.03,-0},{10.46,-0},
		 	{-13.71,0},{1.43,-0},{69.66,0},{-22.93,0},{-17.77,0},{-3.24,-0},
		 	{-29.03,0},
		 	{-62.51,0},{-0.45,-0},{-104.56,-0},{0.58,-0},
		 	{0.63,0},{-4.46,-0},{-20.14,0},{-25.38,0},{26.83,0},{-9.09,-0}
		 },
		 {	//2669 11
		 	{-25.37,-0},
		 	{-89.92,0},{-11.6,-0},{69.94,-0},{-3.8,-0},
		 	{-0.71,0},{-3.66,-0},{35.34,0},{-52.06,0},{14.83,0},{3.97,-0},
		 	{-46.16,0},
		 	{-89.27,0},{10.27,-0},{-78.43,-0},{7.58,-0},
		 	{-0.55,0},{0.14,-0},{14.41,0},{-51.72,0},{36.14,0},{-0.54,-0}
		 },
 };



Angle RoboCansLeft[]=
 {
//		 {	//2639 0
//		 	{32.51,0},
//		 	{-107.86,0},{-31.08,0},{63.19,0},{-1,0},
//		 	{-1.99,0},{5.59,0},{25.16,0},{-24.07,0},{18.89,0},{-9,0},
//		 	{-22.83,0},
//		 	{-90.27,0},{-0.36,0},{-63.21,0},{2.96,0},
//		 	{1.29,0},{0.91,0},{31.92,0},{-43.2,0},{43.07,0},{-13.97,0}
//		 },
//		 {	//2653 1
//		 	{15.88,0},
//		 	{-119.9,0},{-5.71,0},{121.7,0},{-1,0},
//		 	{-11.59,0},{13.17,0},{16.69,0},{-2.37,0},{12.69,0},{-16.02,0},
//		 	{-26.7,0},
//		 	{-68.35,0},{-0.34,0},{-80.33,0},{-6.18,0},
//		 	{-5.72,0},{26.48,0},{28.62,0},{-91.35,0},{20.88,0},{-43.75,0}
//		 },
//		 {	//2654 2
//		 	{14.48,0},
//		 	{-112.89,0},{-9.09,0},{114.28,0},{-7.99,0},
//		 	{-10.57,0},{8.69,0},{15.44,0},{-2.61,0},{13.19,0},{-16.15,0},
//		 	{-27.1,0},
//		 	{-75.38,0},{5.41,0},{-83.41,0},{-9.17,0},
//		 	{1.32,0},{21.87,0},{29.47,0},{-84.35,0},{14.02,0},{-36.75,0}
//		 },
//		 {	//2655 3
//		 	{13.24,0},
//		 	{-105.88,0},{-14.2,0},{107.3,0},{-1.16,0},
//		 	{-8.95,0},{1.83,0},{15.2,0},{-3.46,0},{12.3,0},{-16.15,0},
//		 	{-27.44,0},
//		 	{-82.4,0},{12.4,0},{-88.08,0},{-12.46,0},
//		 	{-5.69,0},{15.17,0},{30.66,0},{-77.4,0},{7.07,0},{-29.76,0}
//		 },
//		 {	//2657 4
//		 	{11.93,0},
//		 	{-91.92,0},{-17.16,0},{96.82,0},{-1,0},
//		 	{-3.16,0},{-6.48,0},{6.37,0},{-10.91,0},{13.95,0},{-13.5,0},
//		 	{-27.17,0},
//		 	{-96.46,0},{18.69,0},{-93.17,0},{-12.48,0},
//		 	{4.24,0},{2.4,0},{41.84,0},{-63.55,0},{-4.23,0},{-15.92,0}
//		 },
//		 {	//2658 5
//		 	{11.92,0},
//		 	{-84.96,0},{-15.33,0},{95.19,0},{-1,0},
//		 	{0.58,0},{-7.66,0},{-0.72,0},{-16.47,0},{17.48,0},{-11.26,0},
//		 	{-26.61,0},
//		 	{-103.48,0},{18.16,0},{-93.45,0},{-9.91,0},
//		 	{0.23,0},{-3.1,0},{48.74,0},{-56.78,0},{-7.45,0},{-9.38,0}
//		 },
//
//		 {	//2659 6
//		 	{12.04,0},
//		 	{-78,0},{-12.3,0},{95.14,0},{-3.22,0},
//		 	{4.25,0},{-7.77,0},{-7.45,0},{-22.64,0},{22.22,0},{-8.71,0},
//		 	{-26.26,0},
//		 	{-109.77,0},{16.31,0},{-92.92,0},{-6.48,0},
//		 	{-6.78,0},{-7.93,0},{55.51,0},{-50.08,0},{-9.69,0},{-4.27,0}
//		 },
//
//		 {	//2660 7
//		 	{19.05,0},
//		 	{-71.01,0},{-8.79,0},{95.92,0},{-1,0},
//		 	{0.56,0},{-7.39,0},{-14.45,0},{-28.92,0},{27.47,0},{-6.08,0},
//		 	{-23.33,0},
//		 	{-115.05,0},{13.93,0},{-92.02,0},{-2.77,0},
//		 	{-13.78,0},{-12.43,0},{62.43,0},{-43.29,0},{-11.49,0},{6.39,0}
//		 },
//		 {	//2663 8
//		 	{25.93,0},
//		 	{-56.04,0},{-2.63,0},{101.81,0},{0.6,0},
//		 	{11.69,0},{2.13,0},{-21.54,0},{-26.13,0},{28.8,0},{8.59,0},
//		 	{-23.46,0},
//		 	{-119.33,0},{15.11,0},{-99.21,0},{-9.04,0},
//		 	{-13.05,0},{-2.91,0},{76.66,0},{-23.41,0},{-22.03,0},{7.31,0}
//		 },
//		 {	//2664 9
//		 	{20.48,0},
//		 	{-62.51,0},{0.45,0},{104.56,0},{-0.58,0},
//		 	{0.63,0},{4.46,0},{-20.14,0},{-25.38,0},{26.83,0},{9.09,0},
//		 	{-29.03,0},
//		 	{-112.31,0},{15.86,0},{-99.03,0},{-10.46,0},
//		 	{-13.71,0},{-1.43,0},{69.66,0},{-22.93,0},{-17.77,0},{3.24,0}
//		 },
//
//		 {	//2665 10
//		 	{17.96,0},
//		 	{-69.28,0},{2.8,0},{106.43,0},{-1.71,0},
//		 	{-3.39,0},{5.45,0},{-13.14,0},{-25.14,0},{25.66,0},{7.94,0},
//		 	{-33.13,0},
//		 	{-105.33,0},{16.02,0},{-97.86,0},{-10.43,0},
//		 	{-15.43,0},{-1.29,0},{62.67,0},{-24.41,0},{-12.88,0},{-3.22,0}
//		 },
//		 {	//2670 11
//		 	{30.41,0},
//		 	{-88.27,0},{-11.4,0},{71.4,0},{-0.58,0},
//		 	{-0.13,0},{-0.88,0},{18.43,0},{-54.95,0},{39.47,0},{0.64,0},
//		 	{-40.16,0},
//		 	{-91.55,0},{11.39,0},{-62.95,0},{-3.06,0},
//		 	{-1.74,0},{4.17,0},{35.39,0},{-59.09,0},{21.83,0},{-4.11,0}
//		 },
		 {	//2639
		 	{32.51,0},
		 	{-107.86,0},{-31.08,0},{63.19,0},{-1,0},
		 	{-1.99,0},{5.59,0},{25.16,0},{-24.07,0},{18.89,0},{-9,0},
		 	{-22.83,0},
		 	{-90.27,0},{-0.36,0},{-63.21,0},{2.96,0},
		 	{1.29,0},{0.91,0},{31.92,0},{-43.2,0},{43.07,0},{-13.97,0}
		 },
		 {	//2654
		 	{14.48,0},
		 	{-112.89,0},{-9.09,0},{114.28,0},{-7.99,0},
		 	{-10.57,0},{8.69,0},{15.44,0},{-2.61,0},{13.19,0},{-16.15,0},
		 	{-27.1,0},
		 	{-75.38,0},{5.41,0},{-83.41,0},{-9.17,0},
		 	{1.32,0},{21.87,0},{29.47,0},{-84.35,0},{14.02,0},{-36.75,0}
		 },

		 {	//2655
		 	{13.24,0},
		 	{-105.88,0},{-14.2,0},{107.3,0},{-1.16,0},
		 	{-8.95,0},{1.83,0},{15.2,0},{-3.46,0},{12.3,0},{-16.15,0},
		 	{-27.44,0},
		 	{-82.4,0},{12.4,0},{-88.08,0},{-12.46,0},
		 	{-5.69,0},{15.17,0},{30.66,0},{-77.4,0},{7.07,0},{-29.76,0}
		 },

		 {	//2656
		 	{12.34,0},
		 	{-98.89,0},{-17.05,0},{100.8,0},{-1.03,0},
		 	{-6.39,0},{-3.49,0},{11.96,0},{-6.32,0},{12.12,0},{-15.24,0},
		 	{-27.69,0},
		 	{-89.43,0},{17.04,0},{-91.51,0},{-13.58,0},
		 	{0.27,0},{8.41,0},{34.89,0},{-70.45,0},{0.71,0},{-22.79,0}
		 },

		 {	//2657
		 	{11.93,0},
		 	{-91.92,0},{-17.16,0},{96.82,0},{-1,0},
		 	{-3.16,0},{-6.48,0},{6.37,0},{-10.91,0},{13.95,0},{-13.5,0},
		 	{-27.17,0},
		 	{-96.46,0},{18.69,0},{-93.17,0},{-12.48,0},
		 	{4.24,0},{2.4,0},{41.84,0},{-63.55,0},{-4.23,0},{-15.92,0}
		 },

		 {	//2658
		 	{11.92,0},
		 	{-84.96,0},{-15.33,0},{95.19,0},{-1,0},
		 	{0.58,0},{-7.66,0},{-0.72,0},{-16.47,0},{17.48,0},{-11.26,0},
		 	{-26.61,0},
		 	{-103.48,0},{18.16,0},{-93.45,0},{-9.91,0},
		 	{0.23,0},{-3.1,0},{48.74,0},{-56.78,0},{-7.45,0},{-9.38,0}
		 },

		 {	//2659
		 	{12.04,0},
		 	{-78,0},{-12.3,0},{95.14,0},{-3.22,0},
		 	{4.25,0},{-7.77,0},{-7.45,0},{-22.64,0},{22.22,0},{-8.71,0},
		 	{-26.26,0},
		 	{-109.77,0},{16.31,0},{-92.92,0},{-6.48,0},
		 	{-6.78,0},{-7.93,0},{55.51,0},{-50.08,0},{-9.69,0},{-4.27,0}
		 },

		 {	//2660
		 	{19.05,0},
		 	{-71.01,0},{-8.79,0},{95.92,0},{-1,0},
		 	{0.56,0},{-7.39,0},{-14.45,0},{-28.92,0},{27.47,0},{-6.08,0},
		 	{-23.33,0},
		 	{-115.05,0},{13.93,0},{-92.02,0},{-2.77,0},
		 	{-13.78,0},{-12.43,0},{62.43,0},{-43.29,0},{-11.49,0},{6.39,0}
		 },

		 {	//2661
		 	{25.71,0},
		 	{-64.03,0},{-5.4,0},{96.96,0},{-0.26,0},
		 	{3.99,0},{-6.89,0},{-21.48,0},{-34.81,0},{32.59,0},{-3.61,0},
		 	{-20.49,0},
		 	{-119.32,0},{11.54,0},{-91.08,0},{0.87,0},
		 	{-20.78,0},{-16.56,0},{69.32,0},{-36.54,0},{-13.01,0},{12.22,0}
		 },

		 {	//2662
		 	{30.24,0},
		 	{-57.06,0},{-4.45,0},{99.07,0},{0.75,0},
		 	{0.53,0},{-2.1,0},{-34.97,0},{-27.8,0},{31.38,0},{3.4,0},
		 	{-18.56,0},
		 	{-122.85,0},{13.29,0},{-96.1,0},{-4.48,0},
		 	{-16.35,0},{-9.55,0},{75.36,0},{-29.57,0},{-19.98,0},{11.33,0}
		 },

		 {	//2663
		 	{25.93,0},
		 	{-56.04,0},{-2.63,0},{101.81,0},{0.6,0},
		 	{11.69,0},{2.13,0},{-21.54,0},{-26.13,0},{28.8,0},{8.59,0},
		 	{-23.46,0},
		 	{-119.33,0},{15.11,0},{-99.21,0},{-9.04,0},
		 	{-13.05,0},{-2.91,0},{76.66,0},{-23.41,0},{-22.03,0},{7.31,0}
		 },

		 {	//2664
		 	{20.48,0},
		 	{-62.51,0},{0.45,0},{104.56,0},{-0.58,0},
		 	{0.63,0},{4.46,0},{-20.14,0},{-25.38,0},{26.83,0},{9.09,0},
		 	{-29.03,0},
		 	{-112.31,0},{15.86,0},{-99.03,0},{-10.46,0},
		 	{-13.71,0},{-1.43,0},{69.66,0},{-22.93,0},{-17.77,0},{3.24,0}
		 },
		 {	//2669
		 	{25.37,0},
		 	{-89.27,0},{-10.27,0},{78.43,0},{-7.58,0},
		 	{-0.55,0},{-0.14,0},{14.41,0},{-51.72,0},{36.14,0},{0.54,0},
		 	{-46.16,0},
		 	{-89.92,0},{11.6,0},{-69.94,0},{3.8,0},
		 	{-0.71,0},{3.66,0},{35.34,0},{-52.06,0},{14.83,0},{-3.97,0}
		 },
 };



Angle RoboCansRightfour[]=
 {
		 {	//13352 0
		 	{-6.43,0},
		 	{-97.06,0},{-9.29,0},{14.05,0},{-0.85,0},
		 	{-0.8,0},{-0.24,0},{22.17,0},{-61.33,0},{50.42,0},{9.56,0},
		 	{-15.69,0},
		 	{-83.58,0},{9.73,0},{-14.04,0},{-1.02,0},
		 	{0.01,0},{3.28,0},{27.32,0},{-64.09,0},{40.16,0},{0.73,0}
		 },
		 {	//13356 1
		 	{-9.78,0},
		 	{-99.99,0},{-6.7,0},{42.13,0},{4.75,0},
		 	{-2.65,0},{2.75,0},{21.87,0},{-45.99,0},{40.85,0},{14.99,0},
		 	{-22.43,0},
		 	{-89.82,0},{12.58,0},{-42.12,0},{2.76,0},
		 	{-6.95,0},{6.32,0},{26.33,0},{-53.02,0},{33.29,0},{2.73,0}
		 },
		 {	//13361 2
		 	{-1.03,0},
		 	{-95.18,0},{-5.27,0},{77.21,0},{16.71,0},
		 	{-4.42,0},{5.49,0},{24.79,0},{-38.82,0},{27.28,0},{15.21,0},
		 	{-22.88,0},
		 	{-105.85,0},{17.48,0},{-77.26,0},{-0.7,0},
		 	{-20.48,0},{6.01,0},{19.89,0},{-30.03,0},{19.9,0},{6.11,0}
		 },
		 {	//13372 3
		 	{-3.3,0},
		 	{-47.75,0},{-13.4,0},{82.53,0},{-0.09,0},
		 	{-0.86,0},{-14.2,0},{-9.55,0},{-68.89,0},{43.88,0},{29.7,0},
		 	{-29.65,0},
		 	{-120.38,0},{-0.78,0},{-121.69,0},{6.47,0},
		 	{-7.35,0},{-18.6,0},{10.2,0},{-10.4,0},{17.2,0},{16.9,0}
		 },
		 {	//13373 4
		 	{-4.45,0},
		 	{-54.78,0},{-18.32,0},{81.21,0},{2.15,0},
		 	{5.34,0},{-9.96,0},{-2.56,0},{-61.91,0},{39.12,0},{24.13,0},
		 	{-30.2,0},
		 	{-119.01,0},{0.98,0},{-113.56,0},{-1.05,0},
		 	{-9.09,0},{-17.99,0},{8.3,0},{-11.18,0},{14.88,0},{20.31,0}
		 },

		 {	//13374 5
		 	{-5.39,0},
		 	{-61.8,0},{-24.32,0},{79.74,0},{4.64,0},
		 	{-0.86,0},{-3.74,0},{4.46,0},{-55.01,0},{32.39,0},{17.2,0},
		 	{-30.65,0},
		 	{-111.99,0},{3.96,0},{-106.57,0},{-7.57,0},
		 	{-11.89,0},{-14.11,0},{6.67,0},{-12.92,0},{12.6,0},{24.26,0}
		 },

		 {	//13375 6
		 	{1.66,0},
		 	{-68.83,0},{-26.27,0},{77.78,0},{4.16,0},
		 	{-0.61,0},{2.07,0},{11.45,0},{-48.1,0},{25.49,0},{10.56,0},
		 	{-29.08,0},
		 	{-105,0},{5,0},{-99.61,0},{-12.03,0},
		 	{-12.04,0},{-9.1,0},{3.61,0},{-17.51,0},{12.41,0},{25.72,0}
		 },

		 {	//13376 7
		 	{8.67,0},
		 	{-75.86,0},{-23.54,0},{75.28,0},{0.41,0},
		 	{-4.47,0},{6.76,0},{18.39,0},{-41.29,0},{18.68,0},{5.5,0},
		 	{-27.42,0},
		 	{-98.02,0},{3.57,0},{-97.32,0},{-11.85,0},
		 	{-8.99,0},{-3.88,0},{1.37,0},{-24.53,0},{15.13,0},{23.82,0}
		 },

		 {	//13377 8
		 	{13.08,0},
		 	{-82.88,0},{-17.72,0},{72.5,0},{-5.54,0},
		 	{-11.43,0},{10.44,0},{25.25,0},{-34.58,0},{11.98,0},{2.63,0},
		 	{-26.29,0},
		 	{-91.05,0},{0.57,0},{-100.63,0},{-7.92,0},
		 	{-3.85,0},{1.25,0},{-2.44,0},{-31.53,0},{19.86,0},{20.63,0}
		 },

		 {	//13378 9
		 	{14.35,0},
		 	{-89.91,0},{-12.51,0},{70.43,0},{0.35,0},
		 	{-18.41,0},{12.74,0},{31.38,0},{-27.84,0},{5.28,0},{-2.7,0},
		 	{-25.71,0},
		 	{-84.08,0},{-2.43,0},{-105.03,0},{-3.85,0},
		 	{0.84,0},{3.5,0},{-6.81,0},{-38.55,0},{23.93,0},{17.89,0}
		 },

		 {	//13379 10
		 	{13.27,0},
		 	{-96.93,0},{-8.67,0},{72.15,0},{-0.84,0},
		 	{-23.59,0},{11.2,0},{38.35,0},{-20.96,0},{-1.84,0},{-2.39,0},
		 	{-25.51,0},
		 	{-77.08,0},{0.48,0},{-107.06,0},{-0.86,0},
		 	{3.97,0},{2.98,0},{-7.62,0},{-40.54,0},{26.5,0},{14.37,0}
		 },

		 {	//13380 11
		 	{10.93,0},
		 	{-103.95,0},{-6.06,0},{77.13,0},{-2.25,0},
		 	{-25.25,0},{6.54,0},{45.37,0},{-13.99,0},{-8.66,0},{2.01,0},
		 	{-25.52,0},
		 	{-70.07,0},{0.24,0},{-106.46,0},{2.96,0},
		 	{0.74,0},{-0.6,0},{-12.21,0},{-37.65,0},{27.76,0},{10.11,0}
		 },
		 {	//13387 12
		 	{-9.62,0},
		 	{-94.91,0},{-13.55,0},{72.12,0},{0.8,0},
		 	{-0.47,0},{2.57,0},{29.94,0},{-35.76,0},{14.34,0},{-1.91,0},
		 	{-25.69,0},
		 	{-86.35,0},{10.12,0},{-66.21,0},{-0.16,0},
		 	{-2.33,0},{3.65,0},{20.71,0},{-52.84,0},{42.95,0},{-3.17,0}
		 },
 };



Angle RoboCansLeftfour[]=
 {
		 {	//13352
		 	{-6.43,0},
		 	{-97.06,0},{-9.29,0},{14.05,0},{-0.85,0},
		 	{-0.8,0},{-0.24,0},{22.17,0},{-61.33,0},{50.42,0},{9.56,0},
		 	{-15.69,0},
		 	{-83.58,0},{9.73,0},{-14.04,0},{-1.02,0},
		 	{0.01,0},{3.28,0},{27.32,0},{-64.09,0},{40.16,0},{0.73,0}
		 },
		 {	//13356
		 	{9.78,-0},
		 	{-89.82,0},{-12.58,-0},{42.12,-0},{-2.76,-0},
		 	{-6.95,0},{-6.32,-0},{26.33,0},{-53.02,0},{33.29,0},{-2.73,-0},
		 	{-22.43,0},
		 	{-99.99,0},{6.7,-0},{-42.13,-0},{-4.75,-0},
		 	{-2.65,0},{-2.75,-0},{21.87,0},{-45.99,0},{40.85,0},{-14.99,-0}
		 },
		 {	//13361
		 	{1.03,-0},
		 	{-105.85,0},{-17.48,-0},{77.26,-0},{0.7,-0},
		 	{-20.48,0},{-6.01,-0},{19.89,0},{-30.03,0},{19.9,0},{-6.11,-0},
		 	{-22.88,0},
		 	{-95.18,0},{5.27,-0},{-77.21,-0},{-16.71,-0},
		 	{-4.42,0},{-5.49,-0},{24.79,0},{-38.82,0},{27.28,0},{-15.21,-0}
		 },
		 {	//13372
		 	{3.3,-0},
		 	{-120.38,0},{0.78,-0},{121.69,-0},{-6.47,-0},
		 	{-7.35,0},{18.6,-0},{10.2,0},{-10.4,0},{17.2,0},{-16.9,-0},
		 	{-29.65,0},
		 	{-47.75,0},{13.4,-0},{-82.53,-0},{0.09,-0},
		 	{-0.86,0},{14.2,-0},{-9.55,0},{-68.89,0},{43.88,0},{-29.7,-0}
		 },
		 {	//13373
		 	{4.45,-0},
		 	{-119.01,0},{-0.98,-0},{113.56,-0},{1.05,-0},
		 	{-9.09,0},{17.99,-0},{8.3,0},{-11.18,0},{14.88,0},{-20.31,-0},
		 	{-30.2,0},
		 	{-54.78,0},{18.32,-0},{-81.21,-0},{-2.15,-0},
		 	{5.34,0},{9.96,-0},{-2.56,0},{-61.91,0},{39.12,0},{-24.13,-0}
		 },
		 {	//13374
		 	{5.39,-0},
		 	{-111.99,0},{-3.96,-0},{106.57,-0},{7.57,-0},
		 	{-11.89,0},{14.11,-0},{6.67,0},{-12.92,0},{12.6,0},{-24.26,-0},
		 	{-30.65,0},
		 	{-61.8,0},{24.32,-0},{-79.74,-0},{-4.64,-0},
		 	{-0.86,0},{3.74,-0},{4.46,0},{-55.01,0},{32.39,0},{-17.2,-0}
		 },
		 {	//13375
		 	{-1.66,-0},
		 	{-105,0},{-5,-0},{99.61,-0},{12.03,-0},
		 	{-12.04,0},{9.1,-0},{3.61,0},{-17.51,0},{12.41,0},{-25.72,-0},
		 	{-29.08,0},
		 	{-68.83,0},{26.27,-0},{-77.78,-0},{-4.16,-0},
		 	{-0.61,0},{-2.07,-0},{11.45,0},{-48.1,0},{25.49,0},{-10.56,-0}
		 },
		 {	//13376
		 	{-8.67,-0},
		 	{-98.02,0},{-3.57,-0},{97.32,-0},{11.85,-0},
		 	{-8.99,0},{3.88,-0},{1.37,0},{-24.53,0},{15.13,0},{-23.82,-0},
		 	{-27.42,0},
		 	{-75.86,0},{23.54,-0},{-75.28,-0},{-0.41,-0},
		 	{-4.47,0},{-6.76,-0},{18.39,0},{-41.29,0},{18.68,0},{-5.5,-0}
		 },
		 {	//13377
		 	{-13.08,-0},
		 	{-91.05,0},{-0.57,-0},{100.63,-0},{7.92,-0},
		 	{-3.85,0},{-1.25,-0},{-2.44,0},{-31.53,0},{19.86,0},{-20.63,-0},
		 	{-26.29,0},
		 	{-82.88,0},{17.72,-0},{-72.5,-0},{5.54,-0},
		 	{-11.43,0},{-10.44,-0},{25.25,0},{-34.58,0},{11.98,0},{-2.63,-0}
		 },
		 {	//13378
		 	{-14.35,-0},
		 	{-84.08,0},{2.43,-0},{105.03,-0},{3.85,-0},
		 	{0.84,0},{-3.5,-0},{-6.81,0},{-38.55,0},{23.93,0},{-17.89,-0},
		 	{-25.71,0},
		 	{-89.91,0},{12.51,-0},{-70.43,-0},{-0.35,-0},
		 	{-18.41,0},{-12.74,-0},{31.38,0},{-27.84,0},{5.28,0},{2.7,-0}
		 },
		 {	//13379
		 	{-13.27,-0},
		 	{-77.08,0},{-0.48,-0},{107.06,-0},{0.86,-0},
		 	{3.97,0},{-2.98,-0},{-7.62,0},{-40.54,0},{26.5,0},{-14.37,-0},
		 	{-25.51,0},
		 	{-96.93,0},{8.67,-0},{-72.15,-0},{0.84,-0},
		 	{-23.59,0},{-11.2,-0},{38.35,0},{-20.96,0},{-1.84,0},{2.39,-0}
		 },
		 {	//13380
		 	{-10.93,-0},
		 	{-70.07,0},{-0.24,-0},{106.46,-0},{-2.96,-0},
		 	{0.74,0},{0.6,-0},{-12.21,0},{-37.65,0},{27.76,0},{-10.11,-0},
		 	{-25.52,0},
		 	{-103.95,0},{6.06,-0},{-77.13,-0},{2.25,-0},
		 	{-25.25,0},{-6.54,-0},{45.37,0},{-13.99,0},{-8.66,0},{-2.01,-0}
		 },
		 {	//13387
		 	{9.62,-0},
		 	{-86.35,0},{-10.12,-0},{66.21,-0},{0.16,-0},
		 	{-2.33,0},{-3.65,-0},{20.71,0},{-52.84,0},{42.95,0},{3.17,-0},
		 	{-25.69,0},
		 	{-94.91,0},{13.55,-0},{-72.12,-0},{-0.8,-0},
		 	{-0.47,0},{-2.57,-0},{29.94,0},{-35.76,0},{14.34,0},{1.91,-0}
		 },
 };
Angle RightShootapollo2[]=
{
		//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
						{ //1
							JointInfo(-7.46,-0),
							JointInfo(-69.75,0),JointInfo(-5,-0),JointInfo(100,-0),JointInfo(-0,-0),
							JointInfo(0.04,0),JointInfo(0.16,-0),JointInfo(39.55,0),JointInfo(-67.32,0),JointInfo(38.07,0),JointInfo(-0.15,-0),
							JointInfo(-24,0),
							JointInfo(-70.25,0),JointInfo(5,-0),JointInfo(-100,-0),JointInfo(-0,-0),
							JointInfo(0.06,0),JointInfo(-0.28,-0),JointInfo(38.85,0),JointInfo(-70.06,0),JointInfo(41.29,0),JointInfo(0.25,-0)
						},
							{ //6
							JointInfo(-7.46,-0),
							JointInfo(-85.31,0),JointInfo(-5,-0),JointInfo(92.33,-0),JointInfo(35.16,-0),
							JointInfo(0.01,0),JointInfo(0.04,-0),JointInfo(39.58,0),JointInfo(-65.73,0),JointInfo(36.21,0),JointInfo(-0.04,-0),
							JointInfo(-24,0),
							JointInfo(-85.4,0),JointInfo(5,-0),JointInfo(-92.32,-0),JointInfo(-35.16,-0),
							JointInfo(0.02,0),JointInfo(-0.07,-0),JointInfo(39.42,0),JointInfo(-66.36,0),JointInfo(36.96,0),JointInfo(0.06,-0)
						},
							{ //13
							JointInfo(-7.46,-0),
							JointInfo(-89.61,0),JointInfo(-5,-0),JointInfo(90.2,-0),JointInfo(57.84,-0),
							JointInfo(0,0),JointInfo(0,-0),JointInfo(39.6,0),JointInfo(-65.29,0),JointInfo(35.7,0),JointInfo(-0.01,-0),
							JointInfo(-24,0),
							JointInfo(-89.62,0),JointInfo(5,-0),JointInfo(-90.2,-0),JointInfo(-57.84,-0),
							JointInfo(0,0),JointInfo(-0.01,-0),JointInfo(39.58,0),JointInfo(-65.34,0),JointInfo(35.76,0),JointInfo(0.01,-0)
						},
							{ //20
							JointInfo(-7.46,-0),
							JointInfo(-89.96,0),JointInfo(-5,-0),JointInfo(90.02,-0),JointInfo(59.78,-0),
							JointInfo(0,0),JointInfo(-10.81,-0),JointInfo(39.6,0),JointInfo(-65.25,0),JointInfo(35.66,0),JointInfo(10.81,-0),
							JointInfo(-24,0),
							JointInfo(-89.96,0),JointInfo(5,-0),JointInfo(-90.02,-0),JointInfo(-59.78,-0),
							JointInfo(0,0),JointInfo(-10.82,-0),JointInfo(39.6,0),JointInfo(-65.26,0),JointInfo(35.66,0),JointInfo(10.82,-0)
						},
							{ //22
							JointInfo(-7.46,-0),
							JointInfo(-89.98,0),JointInfo(-11.99,-0),JointInfo(90.01,-0),JointInfo(52.84,-0),
							JointInfo(0,0),JointInfo(-11.88,-0),JointInfo(45.67,0),JointInfo(-72.28,0),JointInfo(28.63,0),JointInfo(11.85,-0),
							JointInfo(-24,0),
							JointInfo(-89.98,0),JointInfo(11.99,-0),JointInfo(-90.01,-0),JointInfo(-52.84,-0),
							JointInfo(0,0),JointInfo(-11.85,-0),JointInfo(35.26,0),JointInfo(-58.22,0),JointInfo(34.06,0),JointInfo(11.85,-0)
						},
							{ //25
							JointInfo(-7.46,-0),
							JointInfo(-89.99,0),JointInfo(-28.78,-0),JointInfo(90.01,-0),JointInfo(31.8,-0),
							JointInfo(0,0),JointInfo(-12.58,-0),JointInfo(60.25,0),JointInfo(-92.47,0),JointInfo(7.56,0),JointInfo(12.56,-0),
							JointInfo(-24,0),
							JointInfo(-89.99,0),JointInfo(28.78,-0),JointInfo(-90.01,-0),JointInfo(-31.8,-0),
							JointInfo(0,0),JointInfo(-12.56,-0),JointInfo(18.53,0),JointInfo(-41.01,0),JointInfo(30.21,0),JointInfo(12.56,-0)
						},
							{ //28
							JointInfo(-7.46,-0),
							JointInfo(-89.99,0),JointInfo(-35.73,-0),JointInfo(90,-0),JointInfo(13.47,-0),
							JointInfo(0,0),JointInfo(-12.84,-0),JointInfo(66.29,0),JointInfo(-103.27,0),JointInfo(-13.5,0),JointInfo(12.83,-0),
							JointInfo(-24,0),
							JointInfo(-89.99,0),JointInfo(35.73,-0),JointInfo(-90,-0),JointInfo(-13.48,-0),
							JointInfo(0,0),JointInfo(-12.83,-0),JointInfo(11.14,0),JointInfo(-33.72,0),JointInfo(28.62,0),JointInfo(12.83,-0)
						},
							{ //30
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-37.76,-0),JointInfo(90,-0),JointInfo(7.09,-0),
							JointInfo(0,0),JointInfo(-12.92,-0),JointInfo(68.05,0),JointInfo(-106.47,0),JointInfo(-27.54,0),JointInfo(12.91,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(37.76,-0),JointInfo(-90,-0),JointInfo(-7.1,-0),
							JointInfo(0,0),JointInfo(-12.91,-0),JointInfo(8.98,0),JointInfo(-31.59,0),JointInfo(28.16,0),JointInfo(12.91,-0)
						},
							{ //32
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-38.83,-0),JointInfo(90,-0),JointInfo(3.71,-0),
							JointInfo(0,0),JointInfo(-12.95,-0),JointInfo(68.98,0),JointInfo(-108.15,0),JointInfo(-41.05,0),JointInfo(12.95,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(38.83,-0),JointInfo(-90,-0),JointInfo(-3.72,-0),
							JointInfo(0,0),JointInfo(-12.95,-0),JointInfo(7.85,0),JointInfo(-30.48,0),JointInfo(27.92,0),JointInfo(12.95,-0)
						},
							{ //37
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-39.77,-0),JointInfo(90,-0),JointInfo(0.73,-0),
							JointInfo(0,0),JointInfo(-12.99,-0),JointInfo(69.8,0),JointInfo(-109.63,0),JointInfo(-43.82,0),JointInfo(12.99,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(39.77,-0),JointInfo(-90,-0),JointInfo(-0.73,-0),
							JointInfo(0,0),JointInfo(-12.99,-0),JointInfo(6.85,0),JointInfo(-29.49,0),JointInfo(27.7,0),JointInfo(12.99,-0)
						},
							{ //39
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-41.88,-0),JointInfo(90,-0),JointInfo(0.38,-0),
							JointInfo(0,0),JointInfo(-12.99,-0),JointInfo(76.87,0),JointInfo(-102.93,0),JointInfo(-43.87,0),JointInfo(10.46,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(41.87,-0),JointInfo(-90,-0),JointInfo(-0.38,-0),
							JointInfo(0,0),JointInfo(-12.99,-0),JointInfo(6.23,0),JointInfo(-30.57,0),JointInfo(26.88,0),JointInfo(12.99,-0)
						},
							{ //42
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-46.74,-0),JointInfo(90,-0),JointInfo(0.15,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(97.85,0),JointInfo(-82.68,0),JointInfo(-23.56,0),JointInfo(4.55,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(46.74,-0),JointInfo(-90,-0),JointInfo(-0.14,-0),
							JointInfo(0,0),JointInfo(-12.99,-0),JointInfo(-11.61,0),JointInfo(-34.01,0),JointInfo(24.94,0),JointInfo(12.99,-0)
						},
							{ //43
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-47.64,-0),JointInfo(90,-0),JointInfo(0.11,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(104.84,0),JointInfo(-75.94,0),JointInfo(-16.79,0),JointInfo(3.42,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(47.64,-0),JointInfo(-90,-0),JointInfo(-0.1,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(-17.77,0),JointInfo(-35.15,0),JointInfo(24.59,0),JointInfo(13,-0)
						},
							{ //46
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-34.25,-0),JointInfo(90,-0),JointInfo(14.05,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(83.75,0),JointInfo(-81.54,0),JointInfo(4.23,0),JointInfo(6.31,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(34.26,-0),JointInfo(-90,-0),JointInfo(-14.09,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(-8.52,0),JointInfo(-48.05,0),JointInfo(28.79,0),JointInfo(13,-0)
						},
							{ //48
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-21.39,-0),JointInfo(90,-0),JointInfo(28.05,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(71.26,0),JointInfo(-91.81,0),JointInfo(18.26,0),JointInfo(9.36,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(21.4,-0),JointInfo(-90,-0),JointInfo(-28.11,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(5.53,0),JointInfo(-56.04,0),JointInfo(31.97,0),JointInfo(13,-0)
						},
							{ //49
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-16.95,-0),JointInfo(90,-0),JointInfo(35.06,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(67.11,0),JointInfo(-95.1,0),JointInfo(25.29,0),JointInfo(10.34,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(16.96,-0),JointInfo(-90,-0),JointInfo(-35.13,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(12.54,0),JointInfo(-58.55,0),JointInfo(32.98,0),JointInfo(13,-0)
						},
							{ //50
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-13.68,-0),JointInfo(90,-0),JointInfo(41.43,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(64.06,0),JointInfo(-97.5,0),JointInfo(32.32,0),JointInfo(11.06,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(13.68,-0),JointInfo(-90,-0),JointInfo(-41.49,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(19.34,0),JointInfo(-66.88,0),JointInfo(33.71,0),JointInfo(13,-0)
						},
							{ //52
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-9.55,-0),JointInfo(90,-0),JointInfo(50.13,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(60.24,0),JointInfo(-100.51,0),JointInfo(43.91,0),JointInfo(11.98,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(9.55,-0),JointInfo(-90,-0),JointInfo(-50.16,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(28.79,0),JointInfo(-68.53,0),JointInfo(34.63,0),JointInfo(13,-0)
						},
							{ //54
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-7.38,-0),JointInfo(90,-0),JointInfo(54.82,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(58.24,0),JointInfo(-102.09,0),JointInfo(50.48,0),JointInfo(12.46,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(7.38,-0),JointInfo(-90,-0),JointInfo(-54.83,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(33.92,0),JointInfo(-67.15,0),JointInfo(35.11,0),JointInfo(13,-0)
						},
							{ //56
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-6.24,-0),JointInfo(90,-0),JointInfo(57.28,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(57.18,0),JointInfo(-102.92,0),JointInfo(53.96,0),JointInfo(12.72,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(6.24,-0),JointInfo(-90,-0),JointInfo(-57.29,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(36.62,0),JointInfo(-66.26,0),JointInfo(35.37,0),JointInfo(13,-0)
						},
							{ //59
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-5.47,-0),JointInfo(90,-0),JointInfo(58.97,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(56.47,0),JointInfo(-103.48,0),JointInfo(56.35,0),JointInfo(12.89,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(5.47,-0),JointInfo(-90,-0),JointInfo(-58.97,-0),
							JointInfo(0,0),JointInfo(-13,-0),JointInfo(38.47,0),JointInfo(-65.63,0),JointInfo(35.54,0),JointInfo(13,-0)
						},
							{ //61
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-5.25,-0),JointInfo(90,-0),JointInfo(59.45,-0),
							JointInfo(0,0),JointInfo(-11,-0),JointInfo(52.98,0),JointInfo(-96.54,0),JointInfo(52.61,0),JointInfo(10.92,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(5.25,-0),JointInfo(-90,-0),JointInfo(-59.46,-0),
							JointInfo(0,0),JointInfo(-11,-0),JointInfo(39,0),JointInfo(-65.45,0),JointInfo(35.59,0),JointInfo(11,-0)
						},
							{ //64
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-5.09,-0),JointInfo(90,-0),JointInfo(59.79,-0),
							JointInfo(0,0),JointInfo(-5.21,-0),JointInfo(44.95,0),JointInfo(-78.42,0),JointInfo(42.47,0),JointInfo(5.14,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(5.09,-0),JointInfo(-90,-0),JointInfo(-59.79,-0),
							JointInfo(0,0),JointInfo(-5.21,-0),JointInfo(39.37,0),JointInfo(-65.32,0),JointInfo(35.62,0),JointInfo(5.21,-0)
						},
							{ //66
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-5.05,-0),JointInfo(90,-0),JointInfo(59.89,-0),
							JointInfo(0,0),JointInfo(-2.77,-0),JointInfo(42.41,0),JointInfo(-72.19,0),JointInfo(39.23,0),JointInfo(2.74,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(5.05,-0),JointInfo(-90,-0),JointInfo(-59.89,-0),
							JointInfo(0,0),JointInfo(-2.77,-0),JointInfo(39.48,0),JointInfo(-65.29,0),JointInfo(35.63,0),JointInfo(2.77,-0)
						},
							{ //68
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-5.03,-0),JointInfo(90,-0),JointInfo(59.94,-0),
							JointInfo(0,0),JointInfo(-1.46,-0),JointInfo(41.07,0),JointInfo(-68.89,0),JointInfo(37.53,0),JointInfo(1.44,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(5.03,-0),JointInfo(-90,-0),JointInfo(-59.94,-0),
							JointInfo(0,0),JointInfo(-1.46,-0),JointInfo(39.53,0),JointInfo(-65.27,0),JointInfo(35.64,0),JointInfo(1.46,-0)
						},
							{ //72
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-5.01,-0),JointInfo(90,-0),JointInfo(59.98,-0),
							JointInfo(0,0),JointInfo(-0.4,-0),JointInfo(40.01,0),JointInfo(-66.25,0),JointInfo(36.17,0),JointInfo(0.4,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(5.01,-0),JointInfo(-90,-0),JointInfo(-59.98,-0),
							JointInfo(0,0),JointInfo(-0.4,-0),JointInfo(39.58,0),JointInfo(-65.25,0),JointInfo(35.65,0),JointInfo(0.4,-0)
						},
							{ //74
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-5.01,-0),JointInfo(90,-0),JointInfo(59.99,-0),
							JointInfo(0,0),JointInfo(-0.21,-0),JointInfo(39.81,0),JointInfo(-65.77,0),JointInfo(35.92,0),JointInfo(0.21,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(5.01,-0),JointInfo(-90,-0),JointInfo(-59.99,-0),
							JointInfo(0,0),JointInfo(-0.21,-0),JointInfo(39.59,0),JointInfo(-65.25,0),JointInfo(35.65,0),JointInfo(0.21,-0)
						},
							{ //81
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-0.85,-0),JointInfo(47.85,-0),JointInfo(18.62,-0),
							JointInfo(0,0),JointInfo(-0.02,-0),JointInfo(7.39,0),JointInfo(-23.44,0),JointInfo(6.13,0),JointInfo(0.02,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(0.85,-0),JointInfo(-47.85,-0),JointInfo(-18.61,-0),
							JointInfo(0,0),JointInfo(-0.02,-0),JointInfo(7.33,0),JointInfo(-23.06,0),JointInfo(6.07,0),JointInfo(0.02,-0)
						},
							{ //85
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-0.23,-0),JointInfo(20.02,-0),JointInfo(5.24,-0),
							JointInfo(0,0),JointInfo(-0.01,-0),JointInfo(2.03,0),JointInfo(-6.66,0),JointInfo(1.69,0),JointInfo(0.01,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(0.23,-0),JointInfo(-20.02,-0),JointInfo(-5.24,-0),
							JointInfo(0,0),JointInfo(-0.01,-0),JointInfo(2.02,0),JointInfo(-6.54,0),JointInfo(1.67,0),JointInfo(0.01,-0)
						},
							{ //88
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-0.09,-0),JointInfo(7.73,-0),JointInfo(1.96,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.77,0),JointInfo(-2.53,0),JointInfo(0.64,0),JointInfo(0,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(0.09,-0),JointInfo(-7.73,-0),JointInfo(-1.97,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.77,0),JointInfo(-2.48,0),JointInfo(0.63,0),JointInfo(0,-0)
						},
							{ //90
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-0.05,-0),JointInfo(4.05,-0),JointInfo(1.01,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.41,0),JointInfo(-1.32,0),JointInfo(0.34,0),JointInfo(0,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(0.05,-0),JointInfo(-4.05,-0),JointInfo(-1.01,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.4,0),JointInfo(-1.3,0),JointInfo(0.33,0),JointInfo(0,-0)
						},
							{ //93
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-0.02,-0),JointInfo(1.54,-0),JointInfo(0.36,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.16,0),JointInfo(-0.5,0),JointInfo(0.13,0),JointInfo(0,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(0.02,-0),JointInfo(-1.54,-0),JointInfo(-0.36,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.15,0),JointInfo(-0.49,0),JointInfo(0.13,0),JointInfo(0,-0)
						},
							{ //96
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-0.01,-0),JointInfo(0.59,-0),JointInfo(0.13,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.06,0),JointInfo(-0.19,0),JointInfo(0.05,0),JointInfo(0,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(0.01,-0),JointInfo(-0.59,-0),JointInfo(-0.13,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.06,0),JointInfo(-0.19,0),JointInfo(0.05,0),JointInfo(0,-0)
						},
							{ //101
							JointInfo(-7.46,-0),
							JointInfo(-90,0),JointInfo(-0,-0),JointInfo(0.12,-0),JointInfo(-0.04,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.01,0),JointInfo(-0.04,0),JointInfo(0.01,0),JointInfo(0,-0),
							JointInfo(-24,0),
							JointInfo(-90,0),JointInfo(0,-0),JointInfo(-0.12,-0),JointInfo(0.04,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(0.01,0),JointInfo(-0.04,0),JointInfo(0.01,0),JointInfo(0,-0)
						},
							{ //116
							JointInfo(-7.46,-0),
							JointInfo(-5.58,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(84.42,0),JointInfo(-0.03,0),JointInfo(0.01,0),JointInfo(0,-0),
							JointInfo(-24,0),
							JointInfo(-5.58,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(84.42,0),JointInfo(-0.03,0),JointInfo(0.01,0),JointInfo(0,-0)
						},
							{ //118
							JointInfo(-7.46,-0),
							JointInfo(-2.92,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(87.07,0),JointInfo(-0.03,0),JointInfo(0.01,0),JointInfo(0,-0),
							JointInfo(-24,0),
							JointInfo(-2.92,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(0,0),JointInfo(-0,-0),JointInfo(87.08,0),JointInfo(-0.03,0),JointInfo(0.01,0),JointInfo(0,-0)
						},
							{ //123
							JointInfo(-7.46,-0),
							JointInfo(-2.12,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-28.12,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-28.14,0),JointInfo(-10.17,0),JointInfo(-4.74,-0),
							JointInfo(-24,0),
							JointInfo(-2.12,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-28.12,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-28.14,0),JointInfo(-10.17,0),JointInfo(4.74,-0)
						},
							{ //127
							JointInfo(-7.46,-0),
							JointInfo(-2.12,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-56.24,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-56.25,0),JointInfo(-13.66,0),JointInfo(-6.38,-0),
							JointInfo(-24,0),
							JointInfo(-2.12,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-56.24,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-56.25,0),JointInfo(-13.66,0),JointInfo(6.38,-0)
						},
							{ //130
							JointInfo(-7.46,-0),
							JointInfo(-2.12,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-73.37,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-77.33,0),JointInfo(-14.49,0),JointInfo(-6.76,-0),
							JointInfo(-24,0),
							JointInfo(-2.12,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-73.37,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-77.34,0),JointInfo(-14.49,0),JointInfo(6.76,-0)
						},
							{ //132
							JointInfo(-7.46,-0),
							JointInfo(-2.12,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-78.89,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-85.28,0),JointInfo(-14.73,0),JointInfo(-6.88,-0),
							JointInfo(-24,0),
							JointInfo(-2.12,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-78.89,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-85.28,0),JointInfo(-14.73,0),JointInfo(6.88,-0)
						},
							{ //134
							JointInfo(-7.46,-0),
							JointInfo(-2.12,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-81.8,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-93.77,0),JointInfo(-14.86,0),JointInfo(-6.93,-0),
							JointInfo(-24,0),
							JointInfo(-2.12,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-81.8,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-93.77,0),JointInfo(-14.86,0),JointInfo(6.93,-0)
						},
							{ //136
							JointInfo(-7.46,-0),
							JointInfo(-2.12,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-83.32,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-101.61,0),JointInfo(-14.93,0),JointInfo(-6.97,-0),
							JointInfo(-24,0),
							JointInfo(-2.12,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-83.32,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-101.62,0),JointInfo(-14.92,0),JointInfo(6.97,-0)
						},
							{ //138
							JointInfo(-7.46,-0),
							JointInfo(-2.12,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-84.12,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-109.19,0),JointInfo(-14.96,0),JointInfo(-6.98,-0),
							JointInfo(-24,0),
							JointInfo(-2.12,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-84.12,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-109.2,0),JointInfo(-14.96,0),JointInfo(6.98,-0)
						},
							{ //140
							JointInfo(-7.46,-0),
							JointInfo(-2.12,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-84.54,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-114.24,0),JointInfo(-14.98,0),JointInfo(-6.99,-0),
							JointInfo(-24,0),
							JointInfo(-2.12,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-84.54,0),JointInfo(-0,-0),JointInfo(87.88,0),JointInfo(-114.25,0),JointInfo(-14.98,0),JointInfo(6.99,-0)
						},
							{ //144
							JointInfo(-7.46,-0),
							JointInfo(-23.1,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-67.35,0),JointInfo(-0,-0),JointInfo(67.04,0),JointInfo(-95.09,0),JointInfo(6.11,0),JointInfo(-3.09,-0),
							JointInfo(-24,0),
							JointInfo(-23.1,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-67.35,0),JointInfo(-0,-0),JointInfo(67.04,0),JointInfo(-95.1,0),JointInfo(6.11,0),JointInfo(3.09,-0)
						},
							{ //147
							JointInfo(-7.46,-0),
							JointInfo(-44.18,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-46.27,0),JointInfo(-2.07,-0),JointInfo(50.67,0),JointInfo(-77.61,0),JointInfo(23.48,0),JointInfo(-1.19,-0),
							JointInfo(-24,0),
							JointInfo(-44.18,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-46.27,0),JointInfo(2.07,-0),JointInfo(50.67,0),JointInfo(-77.61,0),JointInfo(23.48,0),JointInfo(1.19,-0)
						},
							{ //149
							JointInfo(-7.46,-0),
							JointInfo(-55.91,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-32.21,0),JointInfo(-4.68,-0),JointInfo(45.42,0),JointInfo(-71.75,0),JointInfo(29.24,0),JointInfo(-0.63,-0),
							JointInfo(-24,0),
							JointInfo(-55.91,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-32.21,0),JointInfo(4.68,-0),JointInfo(45.42,0),JointInfo(-71.75,0),JointInfo(29.24,0),JointInfo(0.63,-0)
						},
							{ //151
							JointInfo(-7.46,-0),
							JointInfo(-62.58,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-18.74,0),JointInfo(-5.74,-0),JointInfo(42.64,0),JointInfo(-68.65,0),JointInfo(32.29,0),JointInfo(-0.33,-0),
							JointInfo(-24,0),
							JointInfo(-62.57,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-18.74,0),JointInfo(5.74,-0),JointInfo(42.64,0),JointInfo(-68.65,0),JointInfo(32.29,0),JointInfo(0.33,-0)
						},
							{ //153
							JointInfo(-7.46,-0),
							JointInfo(-66.11,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-11.27,0),JointInfo(-7.73,-0),JointInfo(41.18,0),JointInfo(-67.02,0),JointInfo(33.89,0),JointInfo(-0.17,-0),
							JointInfo(-24,0),
							JointInfo(-66.11,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-11.27,0),JointInfo(7.73,-0),JointInfo(41.18,0),JointInfo(-67.02,0),JointInfo(33.89,0),JointInfo(0.17,-0)
						},
							{ //154
							JointInfo(-7.46,-0),
							JointInfo(-67.18,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-8.27,0),JointInfo(-8.33,-0),JointInfo(40.74,0),JointInfo(-66.53,0),JointInfo(34.38,0),JointInfo(-0.13,-0),
							JointInfo(-24,0),
							JointInfo(-67.18,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-8.27,0),JointInfo(8.33,-0),JointInfo(40.74,0),JointInfo(-66.53,0),JointInfo(34.38,0),JointInfo(0.13,-0)
						},
							{ //156
							JointInfo(-7.46,-0),
							JointInfo(-68.52,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-4.36,0),JointInfo(-8.09,-0),JointInfo(40.19,0),JointInfo(-65.91,0),JointInfo(34.98,0),JointInfo(-0.07,-0),
							JointInfo(-24,0),
							JointInfo(-68.52,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-4.36,0),JointInfo(8.08,-0),JointInfo(40.19,0),JointInfo(-65.91,0),JointInfo(34.98,0),JointInfo(0.07,-0)
						},
							{ //158
							JointInfo(-7.46,-0),
							JointInfo(-69.23,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-2.29,0),JointInfo(-6.67,-0),JointInfo(39.91,0),JointInfo(-65.6,0),JointInfo(35.3,0),JointInfo(-0.03,-0),
							JointInfo(-24,0),
							JointInfo(-69.23,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-2.29,0),JointInfo(6.66,-0),JointInfo(39.91,0),JointInfo(-65.59,0),JointInfo(35.3,0),JointInfo(0.03,-0)
						},
							{ //160
							JointInfo(-7.46,-0),
							JointInfo(-69.59,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-1.2,0),JointInfo(-4.63,-0),JointInfo(39.76,0),JointInfo(-65.43,0),JointInfo(35.46,0),JointInfo(-0.02,-0),
							JointInfo(-24,0),
							JointInfo(-69.59,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-1.2,0),JointInfo(4.63,-0),JointInfo(39.76,0),JointInfo(-65.43,0),JointInfo(35.46,0),JointInfo(0.02,-0)
						},
							{ //163
							JointInfo(-7.46,-0),
							JointInfo(-69.84,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-0.46,0),JointInfo(-1.87,-0),JointInfo(39.66,0),JointInfo(-65.31,0),JointInfo(35.58,0),JointInfo(-0.01,-0),
							JointInfo(-24,0),
							JointInfo(-69.85,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-0.45,0),JointInfo(1.86,-0),JointInfo(39.66,0),JointInfo(-65.32,0),JointInfo(35.58,0),JointInfo(0.01,-0)
						},
							{ //165
							JointInfo(-7.46,-0),
							JointInfo(-69.92,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-0.24,0),JointInfo(-0.98,-0),JointInfo(39.63,0),JointInfo(-65.28,0),JointInfo(35.61,0),JointInfo(-0.01,-0),
							JointInfo(-24,0),
							JointInfo(-69.92,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-0.24,0),JointInfo(0.98,-0),JointInfo(39.63,0),JointInfo(-65.28,0),JointInfo(35.61,0),JointInfo(0.01,-0)
						},
							{ //169
							JointInfo(-7.46,-0),
							JointInfo(-69.97,0),JointInfo(-0,-0),JointInfo(0.09,-0),JointInfo(0,-0),
							JointInfo(-0.07,0),JointInfo(-0.27,-0),JointInfo(39.61,0),JointInfo(-65.26,0),JointInfo(35.63,0),JointInfo(-0,-0),
							JointInfo(-24,0),
							JointInfo(-69.97,0),JointInfo(0,-0),JointInfo(-0.09,-0),JointInfo(-0,-0),
							JointInfo(-0.07,0),JointInfo(0.27,-0),JointInfo(39.61,0),JointInfo(-65.26,0),JointInfo(35.63,0),JointInfo(0,-0)
						},
							{ //170
							JointInfo(-7.9,-0),
							JointInfo(-69.98,0),JointInfo(-1.16,-0),JointInfo(7.11,-0),JointInfo(0,-0),
							JointInfo(-0.05,0),JointInfo(-0.19,-0),JointInfo(39.25,0),JointInfo(-65.27,0),JointInfo(36.01,0),JointInfo(-0,-0),
							JointInfo(-24,0),
							JointInfo(-69.98,0),JointInfo(1.16,-0),JointInfo(-7.11,-0),JointInfo(-0,-0),
							JointInfo(-0.05,0),JointInfo(0.19,-0),JointInfo(39.25,0),JointInfo(-65.27,0),JointInfo(36.01,0),JointInfo(0,-0)
						},
							{ //173
							JointInfo(-8.78,-0),
							JointInfo(-70,0),JointInfo(-3.82,-0),JointInfo(28.19,-0),JointInfo(0,-0),
							JointInfo(-0.01,0),JointInfo(-0.03,-0),JointInfo(43.38,0),JointInfo(-77.09,0),JointInfo(43.71,0),JointInfo(-0.03,-0),
							JointInfo(-24,0),
							JointInfo(-70,0),JointInfo(3.82,-0),JointInfo(-28.19,-0),JointInfo(-0,-0),
							JointInfo(-0.11,0),JointInfo(0.46,-0),JointInfo(37.42,0),JointInfo(-65.23,0),JointInfo(37.78,0),JointInfo(-0.38,-0)
						},
							{ //177
							JointInfo(-8.78,-0),
							JointInfo(-77.03,0),JointInfo(-4.8,-0),JointInfo(56.28,-0),JointInfo(0,-0),
							JointInfo(-0.25,0),JointInfo(-0.02,-0),JointInfo(43.35,0),JointInfo(-77.47,0),JointInfo(43.95,0),JointInfo(0.04,-0),
							JointInfo(-24,0),
							JointInfo(-62.98,0),JointInfo(4.8,-0),JointInfo(-56.25,-0),JointInfo(-0,-0),
							JointInfo(-0.51,0),JointInfo(1.15,-0),JointInfo(35.08,0),JointInfo(-65.35,0),JointInfo(39.95,0),JointInfo(-1.15,-0)
						},                                        //                                    BY Allen.yan






};

Angle LeftShootapollo1[] =
{
				//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
				{ //1
						JointInfo(7.46,0),
						JointInfo(-70.25,0),JointInfo(-5.00,0),JointInfo(100.00,0),JointInfo(0.00,0),
						JointInfo(0.06,0),JointInfo(0.28,0),JointInfo(38.85,0),JointInfo(-70.06,0),JointInfo(41.29,0),JointInfo(-0.25,0),
						JointInfo(-24.00,0),
						JointInfo(-69.75,0),JointInfo(5.00,0),JointInfo(-100.00,0),JointInfo(0.00,0),
						JointInfo(0.04,0),JointInfo(-0.16,0),JointInfo(39.55,0),JointInfo(-67.32,0),JointInfo(38.07,0),JointInfo(0.15,0),
					},
					{ //6
						JointInfo(7.46,0),
						JointInfo(-85.40,0),JointInfo(-5.00,0),JointInfo(92.32,0),JointInfo(35.16,0),
						JointInfo(0.02,0),JointInfo(0.07,0),JointInfo(39.42,0),JointInfo(-66.36,0),JointInfo(36.96,0),JointInfo(-0.06,0),
						JointInfo(-24.00,0),
						JointInfo(-85.31,0),JointInfo(5.00,0),JointInfo(-92.33,0),JointInfo(-35.16,0),
						JointInfo(0.01,0),JointInfo(-0.04,0),JointInfo(39.58,0),JointInfo(-65.73,0),JointInfo(36.21,0),JointInfo(0.04,0),
					},
					{ //13
						JointInfo(7.46,0),
						JointInfo(-89.62,0),JointInfo(-5.00,0),JointInfo(90.20,0),JointInfo(57.84,0),
						JointInfo(0.00,0),JointInfo(0.01,0),JointInfo(39.58,0),JointInfo(-65.34,0),JointInfo(35.76,0),JointInfo(-0.01,0),
						JointInfo(-24.00,0),
						JointInfo(-89.61,0),JointInfo(5.00,0),JointInfo(-90.20,0),JointInfo(-57.84,0),
						JointInfo(0.00,0),JointInfo(-0.00,0),JointInfo(39.60,0),JointInfo(-65.29,0),JointInfo(35.70,0),JointInfo(0.01,0),
					},
					{ //20
						JointInfo(7.46,0),
						JointInfo(-89.96,0),JointInfo(-5.00,0),JointInfo(90.02,0),JointInfo(59.78,0),
						JointInfo(0.00,0),JointInfo(10.82,0),JointInfo(39.60,0),JointInfo(-65.26,0),JointInfo(35.66,0),JointInfo(-10.82,0),
						JointInfo(-24.00,0),
						JointInfo(-89.96,0),JointInfo(5.00,0),JointInfo(-90.02,0),JointInfo(-59.78,0),
						JointInfo(0.00,0),JointInfo(10.81,0),JointInfo(39.60,0),JointInfo(-65.25,0),JointInfo(35.66,0),JointInfo(-10.81,0),
					},
					{ //22
						JointInfo(7.46,0),
						JointInfo(-89.98,0),JointInfo(-11.99,0),JointInfo(90.01,0),JointInfo(52.84,0),
						JointInfo(0.00,0),JointInfo(11.85,0),JointInfo(35.26,0),JointInfo(-58.22,0),JointInfo(34.06,0),JointInfo(-11.85,0),
						JointInfo(-24.00,0),
						JointInfo(-89.98,0),JointInfo(11.99,0),JointInfo(-90.01,0),JointInfo(-52.84,0),
						JointInfo(0.00,0),JointInfo(11.88,0),JointInfo(45.67,0),JointInfo(-72.28,0),JointInfo(28.63,0),JointInfo(-11.85,0),
					},
					{ //25
						JointInfo(7.46,0),
						JointInfo(-89.99,0),JointInfo(-28.78,0),JointInfo(90.01,0),JointInfo(31.80,0),
						JointInfo(0.00,0),JointInfo(12.56,0),JointInfo(18.53,0),JointInfo(-41.01,0),JointInfo(30.21,0),JointInfo(-12.56,0),
						JointInfo(-24.00,0),
						JointInfo(-89.99,0),JointInfo(28.78,0),JointInfo(-90.01,0),JointInfo(-31.80,0),
						JointInfo(0.00,0),JointInfo(12.58,0),JointInfo(60.25,0),JointInfo(-92.47,0),JointInfo(7.56,0),JointInfo(-12.56,0),
					},
					{ //28
						JointInfo(7.46,0),
						JointInfo(-89.99,0),JointInfo(-35.73,0),JointInfo(90.00,0),JointInfo(13.48,0),
						JointInfo(0.00,0),JointInfo(12.83,0),JointInfo(11.14,0),JointInfo(-33.72,0),JointInfo(28.62,0),JointInfo(-12.83,0),
						JointInfo(-24.00,0),
						JointInfo(-89.99,0),JointInfo(35.73,0),JointInfo(-90.00,0),JointInfo(-13.47,0),
						JointInfo(0.00,0),JointInfo(12.84,0),JointInfo(66.29,0),JointInfo(-103.27,0),JointInfo(-13.50,0),JointInfo(-12.83,0),
					},
					{ //30
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-37.76,0),JointInfo(90.00,0),JointInfo(7.10,0),
						JointInfo(0.00,0),JointInfo(12.91,0),JointInfo(8.98,0),JointInfo(-31.59,0),JointInfo(28.16,0),JointInfo(-12.91,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(37.76,0),JointInfo(-90.00,0),JointInfo(-7.09,0),
						JointInfo(0.00,0),JointInfo(12.92,0),JointInfo(68.05,0),JointInfo(-106.47,0),JointInfo(-27.54,0),JointInfo(-12.91,0),
					},
					{ //32
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-38.83,0),JointInfo(90.00,0),JointInfo(3.72,0),
						JointInfo(0.00,0),JointInfo(12.95,0),JointInfo(7.85,0),JointInfo(-30.48,0),JointInfo(27.92,0),JointInfo(-12.95,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(38.83,0),JointInfo(-90.00,0),JointInfo(-3.71,0),
						JointInfo(0.00,0),JointInfo(12.95,0),JointInfo(68.98,0),JointInfo(-108.15,0),JointInfo(-41.05,0),JointInfo(-12.95,0),
					},
					{ //37
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-39.77,0),JointInfo(90.00,0),JointInfo(0.73,0),
						JointInfo(0.00,0),JointInfo(12.99,0),JointInfo(6.85,0),JointInfo(-29.49,0),JointInfo(27.70,0),JointInfo(-12.99,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(39.77,0),JointInfo(-90.00,0),JointInfo(-0.73,0),
						JointInfo(0.00,0),JointInfo(12.99,0),JointInfo(69.80,0),JointInfo(-109.63,0),JointInfo(-43.82,0),JointInfo(-12.99,0),
					},
					{ //39
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-41.87,0),JointInfo(90.00,0),JointInfo(0.38,0),
						JointInfo(0.00,0),JointInfo(12.99,0),JointInfo(6.23,0),JointInfo(-30.57,0),JointInfo(26.88,0),JointInfo(-12.99,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(41.88,0),JointInfo(-90.00,0),JointInfo(-0.38,0),
						JointInfo(0.00,0),JointInfo(12.99,0),JointInfo(76.87,0),JointInfo(-102.93,0),JointInfo(-43.87,0),JointInfo(-10.46,0),
					},
					{ //42
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-46.74,0),JointInfo(90.00,0),JointInfo(0.14,0),
						JointInfo(0.00,0),JointInfo(12.99,0),JointInfo(-11.61,0),JointInfo(-34.01,0),JointInfo(24.94,0),JointInfo(-12.99,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(46.74,0),JointInfo(-90.00,0),JointInfo(-0.15,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(97.85,0),JointInfo(-82.68,0),JointInfo(-23.56,0),JointInfo(-4.55,0),
					},
					{ //43
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-47.64,0),JointInfo(90.00,0),JointInfo(0.10,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(-17.77,0),JointInfo(-35.15,0),JointInfo(24.59,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(47.64,0),JointInfo(-90.00,0),JointInfo(-0.11,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(104.84,0),JointInfo(-75.94,0),JointInfo(-16.79,0),JointInfo(-3.42,0),
					},
					{ //46
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-34.26,0),JointInfo(90.00,0),JointInfo(14.09,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(-8.52,0),JointInfo(-48.05,0),JointInfo(28.79,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(34.25,0),JointInfo(-90.00,0),JointInfo(-14.05,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(83.75,0),JointInfo(-81.54,0),JointInfo(4.23,0),JointInfo(-6.31,0),
					},
					{ //48
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-21.40,0),JointInfo(90.00,0),JointInfo(28.11,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(5.53,0),JointInfo(-56.04,0),JointInfo(31.97,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(21.39,0),JointInfo(-90.00,0),JointInfo(-28.05,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(71.26,0),JointInfo(-91.81,0),JointInfo(18.26,0),JointInfo(-9.36,0),
					},
					{ //49
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-16.96,0),JointInfo(90.00,0),JointInfo(35.13,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(12.54,0),JointInfo(-58.55,0),JointInfo(32.98,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(16.95,0),JointInfo(-90.00,0),JointInfo(-35.06,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(67.11,0),JointInfo(-95.10,0),JointInfo(25.29,0),JointInfo(-10.34,0),
					},
					{ //50
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-13.68,0),JointInfo(90.00,0),JointInfo(41.49,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(19.34,0),JointInfo(-66.88,0),JointInfo(33.71,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(13.68,0),JointInfo(-90.00,0),JointInfo(-41.43,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(64.06,0),JointInfo(-97.50,0),JointInfo(32.32,0),JointInfo(-11.06,0),
					},
					{ //52
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-9.55,0),JointInfo(90.00,0),JointInfo(50.16,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(28.79,0),JointInfo(-68.53,0),JointInfo(34.63,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(9.55,0),JointInfo(-90.00,0),JointInfo(-50.13,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(60.24,0),JointInfo(-100.51,0),JointInfo(43.91,0),JointInfo(-11.98,0),
					},
					{ //54
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-7.38,0),JointInfo(90.00,0),JointInfo(54.83,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(33.92,0),JointInfo(-67.15,0),JointInfo(35.11,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(7.38,0),JointInfo(-90.00,0),JointInfo(-54.82,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(58.24,0),JointInfo(-102.09,0),JointInfo(50.48,0),JointInfo(-12.46,0),
					},
					{ //56
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-6.24,0),JointInfo(90.00,0),JointInfo(57.29,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(36.62,0),JointInfo(-66.26,0),JointInfo(35.37,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(6.24,0),JointInfo(-90.00,0),JointInfo(-57.28,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(57.18,0),JointInfo(-102.92,0),JointInfo(53.96,0),JointInfo(-12.72,0),
					},
					{ //59
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-5.47,0),JointInfo(90.00,0),JointInfo(58.97,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(38.47,0),JointInfo(-65.63,0),JointInfo(35.54,0),JointInfo(-13.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(5.47,0),JointInfo(-90.00,0),JointInfo(-58.97,0),
						JointInfo(0.00,0),JointInfo(13.00,0),JointInfo(56.47,0),JointInfo(-103.48,0),JointInfo(56.35,0),JointInfo(-12.89,0),
					},
					{ //61
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-5.25,0),JointInfo(90.00,0),JointInfo(59.46,0),
						JointInfo(0.00,0),JointInfo(11.00,0),JointInfo(39.00,0),JointInfo(-65.45,0),JointInfo(35.59,0),JointInfo(-11.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(5.25,0),JointInfo(-90.00,0),JointInfo(-59.45,0),
						JointInfo(0.00,0),JointInfo(11.00,0),JointInfo(52.98,0),JointInfo(-96.54,0),JointInfo(52.61,0),JointInfo(-10.92,0),
					},
					{ //64
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-5.09,0),JointInfo(90.00,0),JointInfo(59.79,0),
						JointInfo(0.00,0),JointInfo(5.21,0),JointInfo(39.37,0),JointInfo(-65.32,0),JointInfo(35.62,0),JointInfo(-5.21,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(5.09,0),JointInfo(-90.00,0),JointInfo(-59.79,0),
						JointInfo(0.00,0),JointInfo(5.21,0),JointInfo(44.95,0),JointInfo(-78.42,0),JointInfo(42.47,0),JointInfo(-5.14,0),
					},
					{ //66
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-5.05,0),JointInfo(90.00,0),JointInfo(59.89,0),
						JointInfo(0.00,0),JointInfo(2.77,0),JointInfo(39.48,0),JointInfo(-65.29,0),JointInfo(35.63,0),JointInfo(-2.77,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(5.05,0),JointInfo(-90.00,0),JointInfo(-59.89,0),
						JointInfo(0.00,0),JointInfo(2.77,0),JointInfo(42.41,0),JointInfo(-72.19,0),JointInfo(39.23,0),JointInfo(-2.74,0),
					},
					{ //68
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-5.03,0),JointInfo(90.00,0),JointInfo(59.94,0),
						JointInfo(0.00,0),JointInfo(1.46,0),JointInfo(39.53,0),JointInfo(-65.27,0),JointInfo(35.64,0),JointInfo(-1.46,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(5.03,0),JointInfo(-90.00,0),JointInfo(-59.94,0),
						JointInfo(0.00,0),JointInfo(1.46,0),JointInfo(41.07,0),JointInfo(-68.89,0),JointInfo(37.53,0),JointInfo(-1.44,0),
					},
					{ //72
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-5.01,0),JointInfo(90.00,0),JointInfo(59.98,0),
						JointInfo(0.00,0),JointInfo(0.40,0),JointInfo(39.58,0),JointInfo(-65.25,0),JointInfo(35.65,0),JointInfo(-0.40,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(5.01,0),JointInfo(-90.00,0),JointInfo(-59.98,0),
						JointInfo(0.00,0),JointInfo(0.40,0),JointInfo(40.01,0),JointInfo(-66.25,0),JointInfo(36.17,0),JointInfo(-0.40,0),
					},
					{ //74
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-5.01,0),JointInfo(90.00,0),JointInfo(59.99,0),
						JointInfo(0.00,0),JointInfo(0.21,0),JointInfo(39.59,0),JointInfo(-65.25,0),JointInfo(35.65,0),JointInfo(-0.21,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(5.01,0),JointInfo(-90.00,0),JointInfo(-59.99,0),
						JointInfo(0.00,0),JointInfo(0.21,0),JointInfo(39.81,0),JointInfo(-65.77,0),JointInfo(35.92,0),JointInfo(-0.21,0),
					},
					{ //81
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-0.85,0),JointInfo(47.85,0),JointInfo(18.61,0),
						JointInfo(0.00,0),JointInfo(0.02,0),JointInfo(7.33,0),JointInfo(-23.06,0),JointInfo(6.07,0),JointInfo(-0.02,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(0.85,0),JointInfo(-47.85,0),JointInfo(-18.62,0),
						JointInfo(0.00,0),JointInfo(0.02,0),JointInfo(7.39,0),JointInfo(-23.44,0),JointInfo(6.13,0),JointInfo(-0.02,0),
					},
					{ //85
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-0.23,0),JointInfo(20.02,0),JointInfo(5.24,0),
						JointInfo(0.00,0),JointInfo(0.01,0),JointInfo(2.02,0),JointInfo(-6.54,0),JointInfo(1.67,0),JointInfo(-0.01,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(0.23,0),JointInfo(-20.02,0),JointInfo(-5.24,0),
						JointInfo(0.00,0),JointInfo(0.01,0),JointInfo(2.03,0),JointInfo(-6.66,0),JointInfo(1.69,0),JointInfo(-0.01,0),
					},
					{ //88
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-0.09,0),JointInfo(7.73,0),JointInfo(1.97,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.77,0),JointInfo(-2.48,0),JointInfo(0.63,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(0.09,0),JointInfo(-7.73,0),JointInfo(-1.96,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.77,0),JointInfo(-2.53,0),JointInfo(0.64,0),JointInfo(-0.00,0),
					},
					{ //90
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-0.05,0),JointInfo(4.05,0),JointInfo(1.01,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.40,0),JointInfo(-1.30,0),JointInfo(0.33,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(0.05,0),JointInfo(-4.05,0),JointInfo(-1.01,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.41,0),JointInfo(-1.32,0),JointInfo(0.34,0),JointInfo(-0.00,0),
					},
					{ //93
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-0.02,0),JointInfo(1.54,0),JointInfo(0.36,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.15,0),JointInfo(-0.49,0),JointInfo(0.13,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(0.02,0),JointInfo(-1.54,0),JointInfo(-0.36,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.16,0),JointInfo(-0.50,0),JointInfo(0.13,0),JointInfo(-0.00,0),
					},
					{ //96
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-0.01,0),JointInfo(0.59,0),JointInfo(0.13,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.06,0),JointInfo(-0.19,0),JointInfo(0.05,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(0.01,0),JointInfo(-0.59,0),JointInfo(-0.13,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.06,0),JointInfo(-0.19,0),JointInfo(0.05,0),JointInfo(-0.00,0),
					},
					{ //101
						JointInfo(7.46,0),
						JointInfo(-90.00,0),JointInfo(-0.00,0),JointInfo(0.12,0),JointInfo(-0.04,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.01,0),JointInfo(-0.04,0),JointInfo(0.01,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-90.00,0),JointInfo(0.00,0),JointInfo(-0.12,0),JointInfo(0.04,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(0.01,0),JointInfo(-0.04,0),JointInfo(0.01,0),JointInfo(-0.00,0),
					},
					{ //116
						JointInfo(7.46,0),
						JointInfo(-5.58,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(84.42,0),JointInfo(-0.03,0),JointInfo(0.01,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-5.58,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(84.42,0),JointInfo(-0.03,0),JointInfo(0.01,0),JointInfo(-0.00,0),
					},
					{ //118
						JointInfo(7.46,0),
						JointInfo(-2.92,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(87.08,0),JointInfo(-0.03,0),JointInfo(0.01,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-2.92,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(0.00,0),JointInfo(0.00,0),JointInfo(87.07,0),JointInfo(-0.03,0),JointInfo(0.01,0),JointInfo(-0.00,0),
					},
					{ //123
						JointInfo(7.46,0),
						JointInfo(-2.12,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-28.12,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-28.14,0),JointInfo(-10.17,0),JointInfo(-4.74,0),
						JointInfo(-24.00,0),
						JointInfo(-2.12,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-28.12,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-28.14,0),JointInfo(-10.17,0),JointInfo(4.74,0),
					},
					{ //127
						JointInfo(7.46,0),
						JointInfo(-2.12,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-56.24,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-56.25,0),JointInfo(-13.66,0),JointInfo(-6.38,0),
						JointInfo(-24.00,0),
						JointInfo(-2.12,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-56.24,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-56.25,0),JointInfo(-13.66,0),JointInfo(6.38,0),
					},
					{ //130
						JointInfo(7.46,0),
						JointInfo(-2.12,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-73.37,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-77.34,0),JointInfo(-14.49,0),JointInfo(-6.76,0),
						JointInfo(-24.00,0),
						JointInfo(-2.12,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-73.37,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-77.33,0),JointInfo(-14.49,0),JointInfo(6.76,0),
					},
					{ //132
						JointInfo(7.46,0),
						JointInfo(-2.12,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-78.89,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-85.28,0),JointInfo(-14.73,0),JointInfo(-6.88,0),
						JointInfo(-24.00,0),
						JointInfo(-2.12,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-78.89,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-85.28,0),JointInfo(-14.73,0),JointInfo(6.88,0),
					},
					{ //134
						JointInfo(7.46,0),
						JointInfo(-2.12,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-81.80,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-93.77,0),JointInfo(-14.86,0),JointInfo(-6.93,0),
						JointInfo(-24.00,0),
						JointInfo(-2.12,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-81.80,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-93.77,0),JointInfo(-14.86,0),JointInfo(6.93,0),
					},
					{ //136
						JointInfo(7.46,0),
						JointInfo(-2.12,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-83.32,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-101.62,0),JointInfo(-14.92,0),JointInfo(-6.97,0),
						JointInfo(-24.00,0),
						JointInfo(-2.12,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-83.32,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-101.61,0),JointInfo(-14.93,0),JointInfo(6.97,0),
					},
					{ //138
						JointInfo(7.46,0),
						JointInfo(-2.12,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-84.12,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-109.20,0),JointInfo(-14.96,0),JointInfo(-6.98,0),
						JointInfo(-24.00,0),
						JointInfo(-2.12,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-84.12,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-109.19,0),JointInfo(-14.96,0),JointInfo(6.98,0),
					},
					{ //140
						JointInfo(7.46,0),
						JointInfo(-2.12,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-84.54,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-114.25,0),JointInfo(-14.98,0),JointInfo(-6.99,0),
						JointInfo(-24.00,0),
						JointInfo(-2.12,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-84.54,0),JointInfo(0.00,0),JointInfo(87.88,0),JointInfo(-114.24,0),JointInfo(-14.98,0),JointInfo(6.99,0),
					},
					{ //144
						JointInfo(7.46,0),
						JointInfo(-23.10,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-67.35,0),JointInfo(0.00,0),JointInfo(67.04,0),JointInfo(-95.10,0),JointInfo(6.11,0),JointInfo(-3.09,0),
						JointInfo(-24.00,0),
						JointInfo(-23.10,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-67.35,0),JointInfo(0.00,0),JointInfo(67.04,0),JointInfo(-95.09,0),JointInfo(6.11,0),JointInfo(3.09,0),
					},
					{ //147
						JointInfo(7.46,0),
						JointInfo(-44.18,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-46.27,0),JointInfo(-2.07,0),JointInfo(50.67,0),JointInfo(-77.61,0),JointInfo(23.48,0),JointInfo(-1.19,0),
						JointInfo(-24.00,0),
						JointInfo(-44.18,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-46.27,0),JointInfo(2.07,0),JointInfo(50.67,0),JointInfo(-77.61,0),JointInfo(23.48,0),JointInfo(1.19,0),
					},
					{ //149
						JointInfo(7.46,0),
						JointInfo(-55.91,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-32.21,0),JointInfo(-4.68,0),JointInfo(45.42,0),JointInfo(-71.75,0),JointInfo(29.24,0),JointInfo(-0.63,0),
						JointInfo(-24.00,0),
						JointInfo(-55.91,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-32.21,0),JointInfo(4.68,0),JointInfo(45.42,0),JointInfo(-71.75,0),JointInfo(29.24,0),JointInfo(0.63,0),
					},
					{ //151
						JointInfo(7.46,0),
						JointInfo(-62.57,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-18.74,0),JointInfo(-5.74,0),JointInfo(42.64,0),JointInfo(-68.65,0),JointInfo(32.29,0),JointInfo(-0.33,0),
						JointInfo(-24.00,0),
						JointInfo(-62.58,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-18.74,0),JointInfo(5.74,0),JointInfo(42.64,0),JointInfo(-68.65,0),JointInfo(32.29,0),JointInfo(0.33,0),
					},
					{ //153
						JointInfo(7.46,0),
						JointInfo(-66.11,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-11.27,0),JointInfo(-7.73,0),JointInfo(41.18,0),JointInfo(-67.02,0),JointInfo(33.89,0),JointInfo(-0.17,0),
						JointInfo(-24.00,0),
						JointInfo(-66.11,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-11.27,0),JointInfo(7.73,0),JointInfo(41.18,0),JointInfo(-67.02,0),JointInfo(33.89,0),JointInfo(0.17,0),
					},
					{ //154
						JointInfo(7.46,0),
						JointInfo(-67.18,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-8.27,0),JointInfo(-8.33,0),JointInfo(40.74,0),JointInfo(-66.53,0),JointInfo(34.38,0),JointInfo(-0.13,0),
						JointInfo(-24.00,0),
						JointInfo(-67.18,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-8.27,0),JointInfo(8.33,0),JointInfo(40.74,0),JointInfo(-66.53,0),JointInfo(34.38,0),JointInfo(0.13,0),
					},
					{ //156
						JointInfo(7.46,0),
						JointInfo(-68.52,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-4.36,0),JointInfo(-8.08,0),JointInfo(40.19,0),JointInfo(-65.91,0),JointInfo(34.98,0),JointInfo(-0.07,0),
						JointInfo(-24.00,0),
						JointInfo(-68.52,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-4.36,0),JointInfo(8.09,0),JointInfo(40.19,0),JointInfo(-65.91,0),JointInfo(34.98,0),JointInfo(0.07,0),
					},
					{ //158
						JointInfo(7.46,0),
						JointInfo(-69.23,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-2.29,0),JointInfo(-6.66,0),JointInfo(39.91,0),JointInfo(-65.59,0),JointInfo(35.30,0),JointInfo(-0.03,0),
						JointInfo(-24.00,0),
						JointInfo(-69.23,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-2.29,0),JointInfo(6.67,0),JointInfo(39.91,0),JointInfo(-65.60,0),JointInfo(35.30,0),JointInfo(0.03,0),
					},
					{ //160
						JointInfo(7.46,0),
						JointInfo(-69.59,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-1.20,0),JointInfo(-4.63,0),JointInfo(39.76,0),JointInfo(-65.43,0),JointInfo(35.46,0),JointInfo(-0.02,0),
						JointInfo(-24.00,0),
						JointInfo(-69.59,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-1.20,0),JointInfo(4.63,0),JointInfo(39.76,0),JointInfo(-65.43,0),JointInfo(35.46,0),JointInfo(0.02,0),
					},
					{ //163
						JointInfo(7.46,0),
						JointInfo(-69.85,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-0.45,0),JointInfo(-1.86,0),JointInfo(39.66,0),JointInfo(-65.32,0),JointInfo(35.58,0),JointInfo(-0.01,0),
						JointInfo(-24.00,0),
						JointInfo(-69.84,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-0.46,0),JointInfo(1.87,0),JointInfo(39.66,0),JointInfo(-65.31,0),JointInfo(35.58,0),JointInfo(0.01,0),
					},
					{ //165
						JointInfo(7.46,0),
						JointInfo(-69.92,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-0.24,0),JointInfo(-0.98,0),JointInfo(39.63,0),JointInfo(-65.28,0),JointInfo(35.61,0),JointInfo(-0.01,0),
						JointInfo(-24.00,0),
						JointInfo(-69.92,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-0.24,0),JointInfo(0.98,0),JointInfo(39.63,0),JointInfo(-65.28,0),JointInfo(35.61,0),JointInfo(0.01,0),
					},
					{ //169
						JointInfo(7.46,0),
						JointInfo(-69.97,0),JointInfo(-0.00,0),JointInfo(0.09,0),JointInfo(0.00,0),
						JointInfo(-0.07,0),JointInfo(-0.27,0),JointInfo(39.61,0),JointInfo(-65.26,0),JointInfo(35.63,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-69.97,0),JointInfo(0.00,0),JointInfo(-0.09,0),JointInfo(-0.00,0),
						JointInfo(-0.07,0),JointInfo(0.27,0),JointInfo(39.61,0),JointInfo(-65.26,0),JointInfo(35.63,0),JointInfo(0.00,0),
					},
					{ //170
						JointInfo(7.90,0),
						JointInfo(-69.98,0),JointInfo(-1.16,0),JointInfo(7.11,0),JointInfo(0.00,0),
						JointInfo(-0.05,0),JointInfo(-0.19,0),JointInfo(39.25,0),JointInfo(-65.27,0),JointInfo(36.01,0),JointInfo(-0.00,0),
						JointInfo(-24.00,0),
						JointInfo(-69.98,0),JointInfo(1.16,0),JointInfo(-7.11,0),JointInfo(-0.00,0),
						JointInfo(-0.05,0),JointInfo(0.19,0),JointInfo(39.25,0),JointInfo(-65.27,0),JointInfo(36.01,0),JointInfo(0.00,0),
					},
					{ //173
						JointInfo(8.78,0),
						JointInfo(-70.00,0),JointInfo(-3.82,0),JointInfo(28.19,0),JointInfo(0.00,0),
						JointInfo(-0.11,0),JointInfo(-0.46,0),JointInfo(37.42,0),JointInfo(-65.23,0),JointInfo(37.78,0),JointInfo(0.38,0),
						JointInfo(-24.00,0),
						JointInfo(-70.00,0),JointInfo(3.82,0),JointInfo(-28.19,0),JointInfo(-0.00,0),
						JointInfo(-0.01,0),JointInfo(0.03,0),JointInfo(43.38,0),JointInfo(-77.09,0),JointInfo(43.71,0),JointInfo(0.03,0),
					},
					{ //177
						JointInfo(8.78,0),
						JointInfo(-62.98,0),JointInfo(-4.80,0),JointInfo(56.25,0),JointInfo(0.00,0),
						JointInfo(-0.51,0),JointInfo(-1.15,0),JointInfo(35.08,0),JointInfo(-65.35,0),JointInfo(39.95,0),JointInfo(1.15,0),
						JointInfo(-24.00,0),
						JointInfo(-77.03,0),JointInfo(4.80,0),JointInfo(-56.28,0),JointInfo(-0.00,0),
						JointInfo(-0.25,0),JointInfo(0.02,0),JointInfo(43.35,0),JointInfo(-77.47,0),JointInfo(43.95,0),JointInfo(-0.04,0),
					},                                                                                  //      BY Allen.yan

};


Angle rightFootShootBall[] =
{
{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(23, 0),
		JointInfo(-45, 0), JointInfo(25, 0), JointInfo(0, 0), JointInfo(-42, 0),
		JointInfo(-90, 0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-30,
				0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(23, 0),
		JointInfo(-45, 0), JointInfo(25, 0), JointInfo(0, 0) },
{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(-13, 0), JointInfo(5, 0),
		JointInfo(-7.93, 0), JointInfo(7.75, 0), JointInfo(13, 0), JointInfo(
				-42, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(-90, 0),
		JointInfo(-30, 0), JointInfo(0, 0), JointInfo(-13, 0), JointInfo(5, 0),
		JointInfo(-7.93, 0), JointInfo(7.75, 0), JointInfo(13, 0) },
{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(-13, 0), JointInfo(2, 0),
		JointInfo(-54, 0), JointInfo(43, 0), JointInfo(13, 0), JointInfo(-42,
				0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(-90, 0),
		JointInfo(-30, 0), JointInfo(0, 0), JointInfo(-13, 0), JointInfo(5, 0),
		JointInfo(-7.93, 0), JointInfo(7.75, 0), JointInfo(13, 0) },
{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(-13, 0), JointInfo(18, 0),
		JointInfo(-60, 0), JointInfo(25.5, 0), JointInfo(13, 0), JointInfo(-42,
				0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(-90, 0),
		JointInfo(-30, 0), JointInfo(0, 0), JointInfo(-13, 0), JointInfo(5, 0),
		JointInfo(-7.93, 0), JointInfo(7.75, 0), JointInfo(13, 0) },

{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(50, 0), JointInfo(0,
		0), JointInfo(-3, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) },

{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(50, 0), JointInfo(
		100, 0), JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(-4, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) },

{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-3, 0), JointInfo(
		-3.5, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(1, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0) },
};
Angle leftFootShootBall[] =
{
{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(23, 0),
		JointInfo(-45, 0), JointInfo(25, 0), JointInfo(0, 0), JointInfo(-42, 0),
		JointInfo(-90, 0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-30,
				0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(23, 0),
		JointInfo(-45, 0), JointInfo(25, 0), JointInfo(0, 0) },
{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(13, 0), JointInfo(5, 0),
		JointInfo(-7.93, 0), JointInfo(7.75, 0), JointInfo(-13, 0), JointInfo(
				-42, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(-90, 0),
		JointInfo(-30, 0), JointInfo(0, 0), JointInfo(13, 0), JointInfo(5, 0),
		JointInfo(-7.93, 0), JointInfo(7.75, 0), JointInfo(-13, 0) },
{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(-90, 0),
		JointInfo(-30, 0), JointInfo(0, 0), JointInfo(13, 0), JointInfo(5, 0),
		JointInfo(-7.93, 0), JointInfo(7.75, 0), JointInfo(-13, 0), JointInfo(
				-42, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(13, 0), JointInfo(2, 0),
		JointInfo(-54, 0), JointInfo(43, 0), JointInfo(-13, 0) },
{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(-90, 0),
		JointInfo(-30, 0), JointInfo(0, 0), JointInfo(13, 0), JointInfo(5, 0),
		JointInfo(-7.93, 0), JointInfo(7.75, 0), JointInfo(-13, 0), JointInfo(
				-42, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(90, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(13, 0), JointInfo(18, 0),
		JointInfo(-60, 0), JointInfo(25.5, 0), JointInfo(-13, 0) },

{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(50, 0), JointInfo(0, 0), JointInfo(-3, 0),
		JointInfo(0, 0) },

{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-4, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(50, 0), JointInfo(100, 0), JointInfo(30, 0),
		JointInfo(0, 0) },

{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(1, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(-3, 0), JointInfo(-3.5, 0), JointInfo(-30,
				0), JointInfo(0, 0) },
};
Angle frontPass1[] =
{
///		/////////////////////////  left foot ,Strength 1 ///////////////////////////  
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(30, 0), JointInfo(-30,
						0), JointInfo(0, 0) },
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(30, 0), JointInfo(30,
						0), JointInfo(0, 0) },
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(30, 0), JointInfo(30,
						0), JointInfo(0, 0) },

		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) },

		///			/////////////////////////  right foot  Strength 1  ///////////////////////////  
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) },
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(30, 0), JointInfo(30, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						0, 0) },
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(30, 0), JointInfo(30, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						0, 0) },
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						0, 0) } };
Angle horizPass[] =
{
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0.3, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(-0.3, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
		0.1, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(30, 0), JointInfo(0, 0), JointInfo(0.1, 0), JointInfo(0, 0),
		JointInfo(0, 0) } };
Angle leftFrontPass[] =
{
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) ///0
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) ///1
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(0, 0), JointInfo(-30,
						0), JointInfo(0, 0) ///2
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(30, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0, 0) ///3
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0.3, 0) ///4
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(30, 0) ///5
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-0.2, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(30, 0) ///6
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) ///7
		} };
Angle rightFrontPass[] =
{
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) ///0
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(
						30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) ///1
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						30, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) ///2
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						30, 0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(-30, 0), JointInfo(-30, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0) ///3
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(-0.2,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0) ///4
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(-30,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0) ///5
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(-30,
						0), ///6
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0),
				JointInfo(-0.2, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						0, 0) },
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), ///7
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) } };

Angle backPass[] =
{
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) } };

Angle leftFrontPass_LessStrength[] =
{
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) ///0
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(30, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) ///1
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(0, 0), JointInfo(-30,
						0), JointInfo(0, 0) ///2
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(30, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0, 0) ///3
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0.3, 0) ///4
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(30, 0) ///5
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-0.2, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						-30, 0), JointInfo(30, 0) ///6
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) ///7
		} };
Angle rightFrontPass_LessStrength[] =
{
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
		0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0) ///0
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(
						30, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) ///1
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						30, 0), JointInfo(0, 0), JointInfo(-30, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(30,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0) ///2
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(
						30, 0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0) ///3
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(-0.2,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0) ///4
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(-30,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						-30, 0), JointInfo(-30, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0) ///5
		},
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(0,
						0), JointInfo(30, 0), JointInfo(-30, 0), JointInfo(-30,
						0), ///6
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(-30, 0),
				JointInfo(-0.2, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						0, 0) },
		{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(30, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), ///7
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0) } };

Angle aStandUpBackward_old[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-20, 0), JointInfo(0,
				0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,
						0), JointInfo(0, 0) },
		{ ///1
		JointInfo(0, 0), JointInfo(-120, 0), JointInfo(-0, 0), JointInfo(-90,
				0), JointInfo(45, 0), JointInfo(-90, 0), JointInfo(0, 0),
				JointInfo(10, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-120, 0), JointInfo(0,
						0), JointInfo(90, 0), JointInfo(-45, 0), JointInfo(-90,
						0), JointInfo(0, 0), JointInfo(10, 0), JointInfo(-0, 0),
				JointInfo(-0, 0), JointInfo(0, 0) },
		{ ///2
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-90, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(-30, 0),
				JointInfo(-10, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(90, 0), JointInfo(-0, 0), JointInfo(
						-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(
						-130, 0), JointInfo(-30, 0), JointInfo(10, 0) },
		{ ///3
		JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0,
						0), JointInfo(0, 0) },
		{ ///4
		JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0,
						0), JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-90, 0), JointInfo(
						-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0,
						0), JointInfo(0, 0) },
		{ ///5
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-45, 0), JointInfo(50, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(100, 0), JointInfo(-45, 0),
				JointInfo(50, 0), JointInfo(0, 0) },
		{ ///6
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-90, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(0, 0), JointInfo(
						0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(20,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-90,
						0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130,
						0), JointInfo(0, 0), JointInfo(0, 0) },
		{ ///7
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(55, 0),
				JointInfo(25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(
						-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ ///8
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						100, 0), JointInfo(-130, 0), JointInfo(55, 0),
				JointInfo(25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(
						0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(
						-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(
						-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ ///9
		JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(-60, 0), JointInfo(0, 0), JointInfo(
						80, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(
						25, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(0,
						0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(-60,
						0), JointInfo(0, 0), JointInfo(80, 0), JointInfo(-130,
						0), JointInfo(55, 0), JointInfo(-25, 0) } };
Angle aStandUpBackward_old1[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ JointInfo(0, 0),
		  JointInfo(-90, 0), JointInfo(-40, 0), JointInfo(0,0), JointInfo(0, 0),
		  JointInfo(0, 0), JointInfo(0, 0),JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,0),
		  JointInfo(0, 0),
		  JointInfo(-90, 0), JointInfo(40,0), JointInfo(-0, 0),  JointInfo(-0, 0),
		  JointInfo(0, 0),JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,0), JointInfo(0, 0) },
		{ ///1
		JointInfo(0, 0),
		JointInfo(-120, 0), JointInfo(-40, 0), JointInfo(-90,0), JointInfo(45, 0),
		JointInfo(-90, 0), JointInfo(0, 0),JointInfo(10, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
		JointInfo(0, 0),
		JointInfo(-120, 0), JointInfo(40,0), JointInfo(90, 0), JointInfo(-45, 0),
		JointInfo(-90, 0), JointInfo(0, 0), JointInfo(10, 0), JointInfo(-0, 0),JointInfo(-0, 0), JointInfo(0, 0) },
		{ ///2
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(-40, 0), JointInfo(-90, 0),JointInfo(0, 0),
		JointInfo(-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(-30, 0),JointInfo(-10, 0),
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(40, 0), JointInfo(90, 0), JointInfo(-0, 0),
		JointInfo(-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(-30, 0), JointInfo(10, 0) },
		{ ///3
		JointInfo(0, 0),
		JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(-0, 0),JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0,0),
		JointInfo(0, 0),
		JointInfo(-90, 0), JointInfo(0, 0),JointInfo(0, 0), JointInfo(-0, 0),
		JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0,0), JointInfo(0, 0) },
		{ ///4
		JointInfo(0, 0),
		JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(-0, 0),JointInfo(0, 0),
		JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0,0),
		JointInfo(0, 0),
		JointInfo(-90, 0), JointInfo(0, 0),JointInfo(0, 0), JointInfo(-0, 0),
		JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0,0), JointInfo(0, 0) },
		{ ///5
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-45, 0), JointInfo(50, 0), JointInfo(0, 0),
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(20,0), JointInfo(-0, 0), JointInfo(-0, 0),
		JointInfo(0, 0),JointInfo(0, 0), JointInfo(100, 0), JointInfo(-45, 0),JointInfo(50, 0), JointInfo(0, 0) },
		{ ///6
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(-40, 0), JointInfo(0, 0),JointInfo(0, 0),
		JointInfo(-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(40,0), JointInfo(-0, 0), JointInfo(-0, 0),
		JointInfo(-90,0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130,0), JointInfo(0, 0), JointInfo(0, 0) },
		{ ///7
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),JointInfo(0, 0),
		JointInfo(-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(55, 0),JointInfo(25, 0),
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0),
		JointInfo(-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ ///8
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),JointInfo(0, 0),
		JointInfo(-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(55, 0),JointInfo(25, 0),
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0),
		JointInfo(-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
		{ ///9
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),JointInfo(0, 0),
		JointInfo(-60, 0), JointInfo(0, 0), JointInfo(80, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(25, 0),
		JointInfo(0, 0),
		JointInfo(-0, 0), JointInfo(0,0), JointInfo(-0, 0), JointInfo(-0, 0),
		JointInfo(-60,0), JointInfo(0, 0), JointInfo(80, 0), JointInfo(-130,0), JointInfo(55, 0), JointInfo(-25, 0) } };
Angle aStandUpBackward_old3[] =
{
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
//头1,右臂向前,右臂向右,右臂逆时针,右肘向前,右腿逆时针,右腿向左,右腿向前,右小腿向前,右脚尖向上,右踝向右转
		{ JointInfo(0, 0),
				  JointInfo(-90, 0), JointInfo(-35, 0), JointInfo(0,0), JointInfo(0, 0),
				  JointInfo(0, 0), JointInfo(0, 0),JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,0),
				  JointInfo(0, 0),
				  JointInfo(-90, 0), JointInfo(35,0), JointInfo(-0, 0),  JointInfo(-0, 0),
				  JointInfo(0, 0),JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0,0), JointInfo(0, 0) },
				{ ///1
				JointInfo(0, 0),
				JointInfo(-120, 0), JointInfo(-35, 0), JointInfo(-90,0), JointInfo(50, 0),
				JointInfo(-90, 0), JointInfo(0, 0),JointInfo(10, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),
				JointInfo(0, 0),
				JointInfo(-120, 0), JointInfo(35,0), JointInfo(90, 0), JointInfo(-50, 0),
				JointInfo(-90, 0), JointInfo(0, 0), JointInfo(10, 0), JointInfo(-0, 0),JointInfo(-0, 0), JointInfo(0, 0) },
				{ ///2
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(-35, 0), JointInfo(-90, 0),JointInfo(0, 0),
				JointInfo(-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(-30, 0),JointInfo(-10, 0),
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(35, 0), JointInfo(90, 0), JointInfo(-0, 0),
				JointInfo(-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(-30, 0), JointInfo(10, 0) },
				{ ///3
				JointInfo(0, 0),
				JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(-0, 0),JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0,0),
				JointInfo(0, 0),
				JointInfo(-90, 0), JointInfo(0, 0),JointInfo(0, 0), JointInfo(-0, 0),
				JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0,0), JointInfo(0, 0) },
				{ ///4
				JointInfo(0, 0),
				JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(-0, 0),JointInfo(0, 0),
				JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0,0),
				JointInfo(0, 0),
				JointInfo(-90, 0), JointInfo(0, 0),JointInfo(0, 0), JointInfo(-0, 0),
				JointInfo(-90, 0), JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0,0), JointInfo(0, 0) },
				{ ///5
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(-20, 0), JointInfo(0, 0),JointInfo(0, 0),
				JointInfo(0, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-45, 0), JointInfo(50, 0), JointInfo(0, 0),
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(20,0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(0, 0),JointInfo(0, 0), JointInfo(100, 0), JointInfo(-45, 0),JointInfo(50, 0), JointInfo(0, 0) },
				{ ///6
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(-35, 0), JointInfo(0, 0),JointInfo(0, 0),
				JointInfo(-90, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(0, 0), JointInfo(0, 0),
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(35,0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(-90,0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130,0), JointInfo(0, 0), JointInfo(0, 0) },
				{ ///7
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),JointInfo(0, 0),
				JointInfo(-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(55, 0),JointInfo(25, 0),
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
				{ ///8
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),JointInfo(0, 0),
				JointInfo(-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(55, 0),JointInfo(25, 0),
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(0, 0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(-60, 0), JointInfo(0, 0), JointInfo(100, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(-25, 0) },
				{ ///9
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(-0, 0), JointInfo(0, 0),JointInfo(0, 0),
				JointInfo(-60, 0), JointInfo(0, 0), JointInfo(80, 0), JointInfo(-130, 0), JointInfo(55, 0), JointInfo(25, 0),
				JointInfo(0, 0),
				JointInfo(-0, 0), JointInfo(0,0), JointInfo(-0, 0), JointInfo(-0, 0),
				JointInfo(-60,0), JointInfo(0, 0), JointInfo(80, 0), JointInfo(-130,0), JointInfo(55, 0), JointInfo(-25, 0) } };
//  (HJ (n hj1) (ax 0.32))
// (HJ (n hj2) (ax -45.00))
// (HJ (n raj1) (ax -90.00))(HJ (n raj2) (ax -0.00))(HJ (n raj3) (ax 90.00))(HJ (n raj4) (ax 30.00))
// (HJ (n laj1) (ax -90.00))(HJ (n laj2) (ax 0.00))(HJ (n laj3) (ax -90.00))(HJ (n laj4) (ax -30.00))
// (HJ (n rlj1) (ax -0.00))(HJ (n rlj2) (ax 0.00))(HJ (n rlj3) (ax 49.32))(HJ (n rlj4) (ax -124.17))(HJ (n rlj5) (ax 74.85))(HJ (n rlj6) (ax 0.00))
// (HJ (n llj1) (ax -0.00))(HJ (n llj2) (ax -0.00))(HJ (n llj3) (ax 49.32))(HJ (n llj4) (ax -124.17))(HJ (n llj5) (ax 74.85))(HJ (n llj6) (ax -0.00))

//  (HJ (n hj1) (ax 0.32))
// (HJ (n hj2) (ax -45.00))
// (HJ (n raj1) (ax -90.00))(HJ (n raj2) (ax -0.00))(HJ (n raj3) (ax 90.00))(HJ (n raj4) (ax 30.00))
// (HJ (n laj1) (ax -90.00))(HJ (n laj2) (ax 0.00))(HJ (n laj3) (ax -90.00))(HJ (n laj4) (ax -30.00))
// (HJ (n rlj1) (ax -0.00))(HJ (n rlj2) (ax 0.00))(HJ (n rlj3) (ax 49.32))(HJ (n rlj4) (ax -124.17))(HJ (n rlj5) (ax 74.85))(HJ (n rlj6) (ax 0.00))
// (HJ (n llj1) (ax -0.00))(HJ (n llj2) (ax -0.00))(HJ (n llj3) (ax 49.32))(HJ (n llj4) (ax -124.17))(HJ (n llj5) (ax 74.85))(HJ (n llj6) (ax -0.00))

Angle slideTackleData[] =
{
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(-70, 0), JointInfo(-90, 0), JointInfo(45, 0),
		JointInfo(-70, 0), JointInfo(40, 0), JointInfo(0, 0), JointInfo(70, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(-100, 0), JointInfo(90, 0), JointInfo(45, 0), JointInfo(0, 0),
		JointInfo(-40, 0), JointInfo(0, 0), },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(-100, 0), JointInfo(-90, 0), JointInfo(45, 0),
		JointInfo(0, 0), JointInfo(-40, 0), JointInfo(0, 0), JointInfo(70, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(-70, 0), JointInfo(90, 0), JointInfo(45, 0), JointInfo(-70,
				0), JointInfo(40, 0), JointInfo(0, 0), },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(-70, 0), JointInfo(-90, 0), JointInfo(45, 0),
		JointInfo(-70, 0), JointInfo(40, 0), JointInfo(0, 0), JointInfo(70, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(-100, 0), JointInfo(90, 0), JointInfo(45, 0), JointInfo(0, 0),
		JointInfo(0, 0), JointInfo(0, 0), },
{ JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(
		0, 0), JointInfo(-100, 0), JointInfo(-90, 0), JointInfo(45, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(70, 0),
		JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0), JointInfo(0, 0),
		JointInfo(-70, 0), JointInfo(90, 0), JointInfo(45, 0), JointInfo(-70,
				0), JointInfo(40, 0), JointInfo(0, 0), } };
#endif
