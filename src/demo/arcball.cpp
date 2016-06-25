#include <cmath>
#include <GL/glut.h>

#include "arcball.h"

ArcBall::ArcBall(GLfloat NewWidth, GLfloat NewHeight)
{
    this->StVec.s.X = 0.0f;
    this->StVec.s.Y = 0.0f;
    this->StVec.s.Z = 0.0f;

    this->EnVec.s.X = 0.0f;
    this->EnVec.s.Y = 0.0f;
    this->EnVec.s.Z = 0.0f;

    Matrix4fSetIdentity(&Transform);
    Matrix3fSetIdentity(&LastRot);
    Matrix3fSetIdentity(&ThisRot);

    this->isDragging = false;
    this->isClicked = false;
    this->zoomRate = 1;
    this->setBounds(NewWidth, NewHeight);
}

void ArcBall::_mapToSphere(const Point2fT* NewPt, Vector3fT* NewVec) const
{
    Point2fT TempPt;
    GLfloat length;

    // 复制到临时变量
    TempPt = *NewPt;

    // 把长宽调整到[-1 ... 1]区间
    TempPt.s.X = (TempPt.s.X * this->AdjustWidth)  - 1.0f;
    TempPt.s.Y = 1.0f - (TempPt.s.Y * this->AdjustHeight);

    // 计算长度的平方
    length      = (TempPt.s.X * TempPt.s.X) + (TempPt.s.Y * TempPt.s.Y);

    // 如果点映射到球的外面
    if (length > 1.0f)
    {
        GLfloat norm;

        // 缩放到球上
        norm = 1.0f / FuncSqrt(length);

        // 设置y坐标为0
        NewVec->s.X = TempPt.s.X * norm;
        NewVec->s.Z = TempPt.s.Y * norm;
        NewVec->s.Y = 0.0f;
    }
    // 如果在球内
    else
    {
        // 利用半径的平方为1,求出z坐标
        NewVec->s.X = TempPt.s.X;
        NewVec->s.Z = TempPt.s.Y;
        NewVec->s.Y = -FuncSqrt(1.0f - length);
    }
}

void ArcBall::upstate()
{
    if (!this->isDragging && this->isClicked)                                   // 如果没有拖动
    {
        this->isDragging = true;                                                // 设置拖动为变量为true
        this->LastRot = this->ThisRot;
        this->click(&this->MousePt);
    }
    else if(this->isDragging)
    {
        if (this->isClicked)                                                    //如果按住拖动
        {
            Quat4fT ThisQuat;

            this->drag(&this->MousePt, &ThisQuat);                              // 更新轨迹球的变量
            Matrix3fSetRotationFromQuat4f(&this->ThisRot, &ThisQuat);           // 计算旋转量
            Matrix3fMulMatrix3f(&this->ThisRot, &this->LastRot);
            Matrix4fSetRotationFromMatrix3f(&this->Transform, &this->ThisRot);
        }
        else                                                                    // 如果放开鼠标，设置拖动为false
            this->isDragging = false;
    }
}

/// 按下鼠标,记录当前对应的轨迹球的位置
void ArcBall::click(const Point2fT* NewPt)
{
    this->_mapToSphere(NewPt, &this->StVec);
}

/// 鼠标拖动,计算旋转四元数
void    ArcBall::drag(const Point2fT* NewPt, Quat4fT* NewRot)
{
    // 新的位置
    this->_mapToSphere(NewPt, &this->EnVec);

    // 计算旋转
    if (NewRot)
    {
        Vector3fT Perp;

        // 计算旋转轴
        Vector3fCross(&Perp, &this->StVec, &this->EnVec);

        // 如果不为0
        if (Vector3fLength(&Perp) > Epsilon)
        {
            // 记录旋转轴
            NewRot->s.X = Perp.s.X;
            NewRot->s.Y = Perp.s.Y;
            NewRot->s.Z = Perp.s.Z;
            // 在四元数中,w=cos(a/2)，a为旋转的角度
            NewRot->s.W = Vector3fDot(&this->StVec, &this->EnVec);
        }
        // 是0，说明没有旋转
        else
        {
            NewRot->s.X =
            NewRot->s.Y =
            NewRot->s.Z =
            NewRot->s.W = 0.0f;
        }
    }
}
