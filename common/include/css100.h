#ifndef CSS100_H
#define CSS100_H
#include <iostream>
/*!
������������
*/
struct TCraneBaseInfo{
    std::string Serial;     //�����������õ��豸���к�
    double   Height;        //�����߶�
    double   X;             //����x����
    double   Y;             //����y����
    double   LongArmLength; //��۳���
    double   ShortArmLenght; //�̱۳���
    double   Rs;             //��С����
    bool     Dyna;           //�Ƿ��Ƕ���ʽ
    double   DLong;          //����ͶӰ
    double   DHeight;        //���۸߶�+�����߶�
    double   HeatHeight;     //��ñ�߶�
    double   L1;             //���۵����Ƕ�85������
    double   L2;             //���۵���С�Ƕ�15��
    double   a0;             //��۸����µ㵽������ת���ĵľ��룬�����򸺻�0
    double   C2;             //���㳤��
    double   CAng;           //�̶��н�
    double   DLine;          //��������
};
/*!
����������Ϣ
*/
struct TProtectedArea{

};
#endif
