#pragma once
/*
*此文件由GUI工具生成
*文件功能：用于处理用户的逻辑相应代码
*功能说明：
*========================onButtonClick_XXXX
当页面中的按键按下后系统会调用对应的函数，XXX代表GUI工具里面的[ID值]名称，
如Button1,当返回值为false的时候系统将不再处理这个按键，返回true的时候系统将会继续处理此按键。比如SYS_BACK.
*========================onSlideWindowItemClick_XXXX(int index) 
当页面中存在滑动窗口并且用户点击了滑动窗口的图标后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如slideWindow1;index 代表按下图标的偏移值
*========================onSeekBarChange_XXXX(int progress) 
当页面中存在滑动条并且用户改变了进度后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如SeekBar1;progress 代表当前的进度值
*========================ogetListItemCount_XXXX() 
当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表的总数目,XXX代表GUI工具里面的[ID值]名称，
如List1;返回值为当前列表的总条数
*========================oobtainListItemData_XXXX(ZKListView::ZKListItem *pListItem, int index)
 当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表当前条目下的内容信息,XXX代表GUI工具里面的[ID值]名称，
如List1;pListItem 是贴图中的单条目对象，index是列表总目的偏移量。具体见函数说明
*========================常用接口===============
*LOGD(...)  打印调试信息的接口
*mTextXXX->setText("****") 在控件TextXXX上显示文字****
*mButton1->setSelected(true); 将控件mButton1设置为选中模式，图片会切换成选中图片，按钮文字会切换为选中后的颜色
*mSeekBar->setProgress(12) 在控件mSeekBar上将进度调整到12
*mListView1->refreshListView() 让mListView1 重新刷新，当列表数据变化后调用
*mDashbroadView1->setTargetAngle(120) 在控件mDashbroadView1上指针显示角度调整到120度
*
* 在Eclipse编辑器中  使用 “alt + /”  快捷键可以打开智能提示
*/

// 波形数据存储区
#define DIAGRAM_SIZE 100
static MPPOINT sPoints[DIAGRAM_SIZE];
static MPPOINT sPoints1[DIAGRAM_SIZE];
// 波形图测试用的数据
/*
static int testPoint1[]={50,50,50,60,50,80,95,80,50,50,
						50,50,50,50,50,60,50,50,50,40,
						50,50,50,50,50,50,50,50,50,50,50,05};

*/
//取波形数据里面的偏移值
static int mpointindex = 0;

static void movePoints(MPPOINT* p,int size){
	for(int i =0;i < size-1;i++){
		p[i].y = p[i+1].y;
	}
	p[size-1].y = 0;
}

/**
 * 注册定时器
 * 在此数组中添加即可
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{0,  200}, //定时器id=0,80ms刷新一个波形数据
	//{1,  1000},
};

static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1->setText("123");
	// 初始化一下要使用的数据
	for(int i =0;i < DIAGRAM_SIZE;i++){
		sPoints[i].x = (100*i)/DIAGRAM_SIZE;
		sPoints[i].y = 50;
	}
	for(int i =0;i < DIAGRAM_SIZE;i++){
		sPoints1[i].x = (100*i)/DIAGRAM_SIZE;
		sPoints1[i].y = 50;
	}
	// 初始化波形显示内容
	mDiagram1Ptr->setData(0,sPoints,DIAGRAM_SIZE);
	mDiagram1Ptr->setData(1,sPoints1,DIAGRAM_SIZE);
	mDiagram2Ptr->setData(0,sPoints,DIAGRAM_SIZE);
	mDiagram3Ptr->setData(0,sPoints1,DIAGRAM_SIZE);
}

static void onUI_quit() {

}


static void onProtocolDataUpdate(const SProtocolData &data) {
    // 串口数据回调接口
}
bool bRefresh = true;
static bool onUI_Timer(int id){
    //Tips:添加定时器响应的代码到这里,但是需要在本文件的 REGISTER_ACTIVITY_TIMER_TAB 数组中 注册
    //id 是定时器设置时候的标签,这里不要写耗时的操作，否则影响UI刷新,ruturn:[true] 继续运行定时器;[false] 停止运行当前定时器
	if(id == 0){
		if(!bRefresh){
			return true;
		}
		/** 模拟一个数据
		 *
		 */
		mpointindex++;
		if(mpointindex >= 30){
			mpointindex = 0;
		}
		movePoints(sPoints,DIAGRAM_SIZE);
		movePoints(sPoints1,DIAGRAM_SIZE);
		if(mpointindex%16 == 0){
			sPoints[DIAGRAM_SIZE-1].y = 95;
		}else if(mpointindex%8 == 0){
			sPoints[DIAGRAM_SIZE-1].y = 5;
		}else if(mpointindex%7 == 0){
			sPoints[DIAGRAM_SIZE-1].y = 40;
		}else{
			sPoints[DIAGRAM_SIZE-1].y = 50;
		}
		// 为了方便看到演示效果，我们把波形2的数据和波形1的数据做个相反的数据
		sPoints1[DIAGRAM_SIZE-1].y =100-sPoints[DIAGRAM_SIZE-1].y;

		// 数据和波形图绑定
		mDiagram1Ptr->setData(0,sPoints,DIAGRAM_SIZE);
		mDiagram1Ptr->setData(1,sPoints1,DIAGRAM_SIZE);
		mDiagram2Ptr->setData(0,sPoints,DIAGRAM_SIZE);
		mDiagram3Ptr->setData(0,sPoints1,DIAGRAM_SIZE);
	}
	return true;
}


static bool onwaveViewActivityTouchEvent(const MotionEvent &ev) {
    // 返回false触摸事件将继续传递到控件上，返回true表示该触摸事件在此被拦截了，不再传递到控件上
    return false;
}
static bool onButtonClick_ButtonOnOff(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonOnOff !!!\n");
	bRefresh = !bRefresh;
	mButtonOnOffPtr->setSelected(!bRefresh);
    return true;
}

static bool onButtonClick_sys_back(ZKButton *pButton) {
    //LOGD(" ButtonClick sys_back !!!\n");
    return true;
}

