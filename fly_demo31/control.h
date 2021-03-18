/*********************************************************************************
JJ_fly by TIVA
�ļ�����control.h
���������Ƴ���
���ߣ�¬���
ʱ�䣺2015.11
**********************************************************************************/
#ifndef CONTROL_H_
#define CONTROL_H_
/*
//����
#define CH_1_MAX 1960
#define CH_1_MID 1476
#define CH_1_MIN 1000
//ƫ��
#define CH_2_MAX 1956
#define CH_2_MID 1476
#define CH_2_MIN 996
//����
#define CH_3_MAX 1956
#define CH_3_MID 1476
#define CH_3_MIN 996
//����
#define CH_4_MAX 1000
#define CH_4_MID 1000
#define CH_4_MIN 1000
//����
#define CH_5_MAX 1962
#define CH_5_MID 1482
#define CH_5_MIN 1002
//����
#define CH_6_MAX 1978
#define CH_6_MID 1478
#define CH_6_MIN 1018
*/
//����
#define CH_1_MAX 200
#define CH_1_MID 149
#define CH_1_MIN 101
//ƫ��
#define CH_2_MAX 200
#define CH_2_MID 149
#define CH_2_MIN 101
//����
/*
#define CH_3_STOP 90
#define CH_3_TEST 117
#define CH_3_HAND 151
#define CH_3_HEIGHT 184
*/

#define CH_3_STOP 133
#define CH_3_TEST 172
#define CH_3_HAND 199
#define CH_3_HEIGHT 187

//����
#define CH_4_MAX 200
#define CH_4_MID 150
#define CH_4_MIN 101
//����
#define CH_5_MAX 200
#define CH_5_MID 149
#define CH_5_MIN 101
//����
#define CH_6_MAX 200
#define CH_6_MID 149
#define CH_6_MIN 101
extern float T;//����
extern int thr;//����
extern int motor_1,motor_2,motor_3,motor_4;//��·���pwm���
extern float error_angle_x,error_angle_y,error_angle_z;//�Ƕ����
extern float except_angle_x,except_angle_y,except_angle_z;//�����Ƕ�
extern float offset_angle_x,offset_angle_y,offset_angle_z;//�ǶȲ���
extern float i_error_angle_x,i_error_angle_y,i_error_angle_z;//�Ƕ�������ֵ
extern float i_error_angle_x_max,i_error_angle_y_max,i_error_angle_z_max;//�����޷����ֵ
extern float i_error_angle_x_min,i_error_angle_y_min,i_error_angle_z_min;//�����޷���Сֵ
extern float d_error_angle_x,d_error_angle_y,d_error_angle_z;//�Ƕ����΢��ֵ
extern float control_1_x,control_1_y,control_1_z;//�⻷pid���
extern float old_error_angle_x,old_error_angle_y,old_error_angle_z;//��ʷ����
extern float kp_angle_x,ki_angle_x,kd_angle_x,kp_angle_y,ki_angle_y,kd_angle_y,kp_angle_z,ki_angle_z,kd_angle_z;//�⻷pid����

extern float error_aspeed_x,error_aspeed_y,error_aspeed_z;//���ٶ����
extern float except_aspeed_x,except_aspeed_y,except_aspeed_z;//�������ٶ�
extern float offset_aspeed_x,offset_aspeed_y,offset_aspeed_z;//���ٶȲ���
extern float i_error_aspeed_x,i_error_aspeed_y,i_error_aspeed_z;//���ٶ�������ֵ
extern float i_error_aspeed_x_max,i_error_aspeed_y_max,i_error_aspeed_z_max;//�����޷����ֵ
extern float i_error_aspeed_x_min,i_error_aspeed_y_min,i_error_aspeed_z_min;//�����޷���Сֵ
extern float d_error_aspeed_x,d_error_aspeed_y,d_error_aspeed_z;//���ٶ����΢��ֵ
extern float control_2_x,control_2_y,control_2_z;//�ڻ�pid���
extern float old_error_aspeed_x,old_error_aspeed_y,old_error_aspeed_z;//��ʷ����
extern float kp_aspeed_x,ki_aspeed_x,kd_aspeed_x,kp_aspeed_y,ki_aspeed_y,kd_aspeed_y,kp_aspeed_z,ki_aspeed_z,kd_aspeed_z;//�ڻ�pid����
extern unsigned char ctrl_height;
extern unsigned char fly_low;
extern float except_height;
extern float kp_height,ki_height,kd_height,ki_height_ready;
extern float kp_point,kd_point,ki_point;
extern int buchang;
extern int shache;
extern int game_speed;
void control();
void control_init();
void control_height();
void control_point();//�������
void land();//һ������
void control_point_1();//�������1
#endif /* CONTROL_H_ */
