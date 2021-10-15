/******************************************************************************

        版权所有 (C),2018-2025  开放智能机器（上海）有限公司
                        OPEN AI LAB
                        
******************************************************************************
  文 件 名   : mosse_tracker.hpp
  作     者:  杨荣钊
  生成日期   :  2019年6月23日
  功能描述   :  MOSSE跟踪器头文件
******************************************************************************/
#ifndef __MOSSE_TRACKER_HPP__
#define __MOSSE_TRACKER_HPP__

/*----------------------------------------------*
 *                    头文件                       *
 *----------------------------------------------*/
#include "tracking.hpp"


namespace cv
{

/*----------------------------------------------*
 *                    MOSSETracker              *
 *----------------------------------------------*/
class MOSSETracker
{
public:
    /********************************
    * 函数名称：MOSSETracker
    * 功能描述：构造函数
    * 输入参数   : 
    * 输出参数   : 
    * 返回参数   : 
    ********************************/
    MOSSETracker();

    /********************************
    * 函数名称：~MOSSETracker
    * 功能描述：析构函数
    * 输入参数   : 
    * 输出参数   : 
    * 返回参数   : 
    ********************************/
    ~MOSSETracker();

    /**************************************
    * 函数名称：init
    * 功能描述：初始化
    * 输入参数   : 
    *           img     输入图像，全图
    *           bbox    检测框
    * 输出参数   : 
    * 返回参数   : true代表成功,false代表失败
    **************************************/
    bool init(const cv::Mat& image, const cv::Rect& boundingBox);

    /**************************************
    * 函数名称：update
    * 功能描述：更新跟踪框
    * 输入参数   : 
    *           img     输入图像，全图   
    * 输出参数   : bbox     新的跟踪框
    * 返回参数   : true代表成功,false代表失败
    **************************************/
    bool update(const cv::Mat& image, cv::Rect& boundingBox);

    /**************************************
    * 函数名称：is_track_success
    * 功能描述：返回跟踪成功标志
    * 输入参数   :  
    * 输出参数   : 
    * 返回参数   : true代表成功,false代表失败
    **************************************/
    bool is_track_success() const;

    /**************************************
    * 函数名称：is_init
    * 功能描述：返回初始化成功标志
    * 输入参数   :  
    * 输出参数   : 
    * 返回参数   : true代表成功,false代表失败
    **************************************/
    bool is_init() const;

    /**************************************
    * 函数名称：set_thresh
    * 功能描述：改变阈值
    * 输入参数   :  
    *           thresh      响应值阈值
    * 输出参数   : 
    * 返回参数   : 
    **************************************/
    void set_thresh(double thresh);

private:
    /**************************************
    * 函数名称：divDFTs
    * 功能描述：复数矩阵的逐元素相除
    * 输入参数   : 
    *           src1     复数矩阵
    *           src2     复数矩阵
    * 输出参数   : 
    * 返回参数   : 商矩阵
    **************************************/
    Mat divDFTs(const Mat& src1, const Mat& src2) const;

    /**************************************
    * 函数名称：preProcess
    * 功能描述：预处理
    * 输入参数   : 
    *           window      窗口图像
    * 输出参数   : 
    * 返回参数   : 商矩阵
    **************************************/
    void preProcess(Mat &window) const;

    /**************************************
    * 函数名称：correlate
    * 功能描述：互相关
    * 输入参数   : 
    *           image_sub      
    *           delta_xy
    * 输出参数   : 
    * 返回参数   : 互相关系数
    **************************************/
    double correlate(const Mat& image_sub, Point& delta_xy) const;

    /**************************************
    * 函数名称：randWarp
    * 功能描述：随机仿射变换
    * 输入参数   : 
    *           a       输入图像      
    * 输出参数   : 
    * 返回参数   : 变换后的图像
    **************************************/
    Mat randWarp(const Mat& a) const;
    
private:
    Point center;                  // 框框中心点
    Size size;                     // 框框大小
    Mat hanWin;                    // 汉宁窗口
    Mat G;                         // 目标矩阵
    Mat H, A, B;                   // 状态矩阵
    const double eps=0.00001;      // 归一化系数
    const double rate=0.2;         // 学习率
    double psrThreshold=5.7; // 响应阈值
    bool track_success;            // 跟踪成功标志
    bool is_init_;                  // 初始化成功标志
}; // MOSSETracker

}
#endif // __MOSSE_TRACKER_HPP__