#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <fstream>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include<iostream>
#include<ctime>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <draw.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sstream>
#include <iomanip>
#include <limits.h>
#include <comm.h>
#include "obfuscate.h"

//不用看了 狗屎源码 还带后门的

//该删除的后门 泪心基本已经删除  
//删不了的后门 那也尽力了
//UI还好看 有能力自己抄抄
//绘图就没必要了   直接不看  狗屎一样的源码
//UI比较好抄   抄两个图片绘制  炒个Ui菜单源码

// 技术分析 TG@TearGame

//泪心王者荣耀源码分享














void complexCondition(int pz) {
    int a = pz ^ 0x1234; 
    int b = (pz & 0x0F) + (pz >> 4); 
    int c = (a * 2) - b; 

    if (c != 0 && (pz != 12 || (pz % 5 == 0 && pz > 25))) {
        exit(0);
    }
}
using namespace std;
static bool 触摸驱动;  
int main(int argc, char *argv[]) 
{
   
      char YN[32] = {0};
    scanf("%s", YN);  // 从标准输入流中读取字符串    

    if (strstr(YN, "1") != NULL) {
     fopen(AY_OBFUSCATE("/data/CR配置/防录屏"), "w");
    } else {
     system(AY_OBFUSCATE("rm /data/CR配置/防录屏 2>/dev/null"));
    }
int Option;
    std::cout << AY_OBFUSCATE("\033[0m开启无后台模式:[1]开启 [2]关闭: \033[0m");  // 黄色提示
cin >> Option;
if (Option == 2) {
} else {
    pid_t pids = fork();
    if (pids > 0) {
        std::cout << AY_OBFUSCATE("\033[0m\n为你启动无后台模式,请稍等片刻...\033[0m\n");  // 黄色提示 + 前后换行
        exit(0);
    }
}
std::thread 基址(DrawInit);


    screen_config();
    ::abs_ScreenX = (::displayInfo.height > ::displayInfo.width ? ::displayInfo.height
                                                                : ::displayInfo.width);
    ::abs_ScreenY = (::displayInfo.height < ::displayInfo.width ? ::displayInfo.height
                                                                : ::displayInfo.width);

    ::native_window_screen_x = (displayInfo.height > displayInfo.width ? displayInfo.height
                                                                       : displayInfo.width);
    ::native_window_screen_y = (displayInfo.height > displayInfo.width ? displayInfo.height
                                                                       : displayInfo.width);
    if (init_egl(::native_window_screen_x, ::native_window_screen_y)) {
        ImGui_init();
    } else {
printf("\033[0m");
        printf("[!] EGL err\n");
        exit(1);    
    }
	
	Touch::Init({(float)::abs_ScreenX, (float)::abs_ScreenY}, false); //要想模拟触摸最后一个参数改成 false
    new std::thread(Getxfctouch2);
	Touch::setOrientation(displayInfo.orientation);
    while (true) {     
        drawBegin();
        
   	    tick();  
   	    
   	    drawEnd();
        usleep(1);
    }
   
    shutdown();
    return 0;
    
}
