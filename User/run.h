#ifndef _RUN_H
#define _RUN_H


//Ð¡³µÐý×ª
void Clockwise90Handle(void);
void Clockwise90Handle2(void);
void Clockwise90Handle3(void);
void Clockwise180Handle(void);
void CounterClockwise90Handle(void);
void CounterClockwise90Handle2(void);

void InitCarPosition(void);
void InitCarPosition2(void);
void InitCarPosition3(void);
void ResetCarPosition(void);

void MoveToRawPosition(void);
void MoveToRawPosition2(void);
void MoveToRawPosition3(void);
void MoveToProcessPosition(void);

void CarFineTuning(void);

void CarBrake(void);

void MoveOne_Forward_X_N(void);
void MoveOne_Forward_X_P(void);
void MoveOne_Forward_Y_N(void);
void MoveOne_Forward_Y_P(void);

void MoveOne_Backward_X_N(void);
void MoveOne_Backward_X_P(void);
void MoveOne_Backward_Y_N(void);
void MoveOne_Backward_Y_P(void);


void MoveOne_Left_Y_P(void);
void MoveOne_Left_X_N(void);

void MoveOne_Right_Y_N(void);


#endif
