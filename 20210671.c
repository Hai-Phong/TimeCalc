#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct {
    char TimeString[10];
    int hour;
    int min;
    int sec;
    int err; //0 for error and 1 for correct format
} Time;

char TimeStringFinal[10] = {'+','0','0',':','0','0',':','0','0'}; //để in kết quả
char TimeStringFinalDefault[10] = {'+','0','0',':','0','0',':','0','0'};

void TimeCalc(Time s1, Time s2){
    //Tính abs chênh lệch t1 t2 theo đơn vị giây
    int Time1 = s1.hour * 3600 + s1.min * 60 + s1.sec;
    int Time2 = s2.hour * 3600 + s2.min * 60 + s2.sec;
    int Diff = abs(Time2 - Time1);

    //Quy đổi sang hệ (giờ:phút:giây)
    int FinalHour = Diff / 3600;
    int FinalMin = (Diff - FinalHour * 3600) / 60;
    int FinalSec = Diff - FinalHour * 3600 - FinalMin * 60;

    //In kết quả
    TimeStringFinal[1] = FinalHour/10+'0';
    TimeStringFinal[2] = FinalHour%10+'0';

    TimeStringFinal[4] = FinalMin/10+'0';
    TimeStringFinal[5] = FinalMin%10+'0';

    TimeStringFinal[7] = FinalSec/10+'0';
    TimeStringFinal[8] = FinalSec%10+'0';
    if ((Time2 - Time1) > 0) {
        TimeStringFinal[0] = '+';
    }
    else TimeStringFinal[0] = '-';
}

Time SaveData(){
    Time s1;
    if ((fgets(s1.TimeString, sizeof(s1.TimeString),stdin))!=NULL){
        if (s1.TimeString[2]!=':'||s1.TimeString[5]!=':'){
            s1.err = 0;
            s1.hour = s1.min = s1.sec = 0;
        }
        else {
            // convert and save time as integer as well
            s1.hour = (s1.TimeString[0] -48)*10 + (s1.TimeString[1] -48);
            s1.min = (s1.TimeString[3] -48)*10 + (s1.TimeString[4]-48);
            s1.sec = (s1.TimeString[6]-48)*10 + (s1.TimeString[7]-48);
            if (s1.hour >=24||s1.min>=60||s1.sec>=60){
                s1.err = 0;
            }
            else s1.err = 1;
        }
    }
    if (strlen(s1.TimeString)!=9) s1.err = 0;
    return s1;
}


int main(){
    Time s1, s2;
    s1 = SaveData();
    s2 = SaveData();

    TimeCalc(s1,s2);

    if(s1.err ==0||s2.err ==0){
        printf("%d %d %s",s1.err,s2.err,TimeStringFinalDefault);
    }
    else printf("%d %d %s",s1.err,s2.err,TimeStringFinal);
    return 0;
}