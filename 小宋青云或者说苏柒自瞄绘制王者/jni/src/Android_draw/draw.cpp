#include "draw.h"
#include "2400.h"
#include "DrawPlayer.hpp"
#include "Font.h"
#include "Layout.hpp"
#include "触摸自瞄.h"
#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/input.h>
#include <string.h>
#include "SXlogo.h"
#include "BJlogo.h"
#include <vector>
#include <cstdint>
std::string loadTextFromFile(const std::string& filename) {
    std::string content;
    std::ifstream file(filename);
    if (file.is_open()) {
        content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
    }
    return content;
}

//不用看了 狗屎源码 还带后门的

//该删除的后门 泪心基本已经删除  
//删不了的后门 那也尽力了
//UI还好看 有能力自己抄抄
//绘图就没必要了   直接不看  狗屎一样的源码
//UI比较好抄   抄两个图片绘制  炒个Ui菜单源码

// 技术分析 TG@TearGame

//泪心王者荣耀源码分享




static bool 触摸驱动 = false;
static bool IsBall = true;
static bool 悬浮窗 = true;
int currentTab = 0;
timer FPS限制;
int GetEventCount() {
    DIR *dir = opendir("/dev/input/");
    dirent *ptr = NULL;
    int count = 0;
    while ((ptr = readdir(dir)) != NULL) {
        if (strstr(ptr->d_name, "event"))
            count++;
    }
    return count ? count : -1;
}
void 一加() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = 31;
    SmallMapY = 9;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 1527;
    zhsY = 977;
    屏幕x = 1;
    屏幕y = -88;
    读取();
}
void 王者() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = 90;
    SmallMapY = 16;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 2000;
    zhsY = 1288;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void 荣耀() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = 62;
    SmallMapY = 12;
    SmallHPX = 8;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 2000;
    zhsY = 1288;
    屏幕x = 24;
    屏幕y = -192;
    读取();
}
void 神明() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = 31;
    SmallMapY = 9;
    SmallHPX = 28;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 1527;
    zhsY = 977;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void 无敌() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = 90;
    SmallMapY = 16;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 2000;
    zhsY = 1288;
    屏幕x = 0;
    屏幕y = 0;
    jiange = -5;
    读取();
}
void 咳咳() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = 159;
    SmallMapY = 19;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 2145;
    zhsY = 1228;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void 欧凯() {
    touxiangdaxiao = -2;
    xiaodituxue = -2;
    jiange = 0;
    SmallMapX = 12;
    SmallMapY = 10;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 1493;
    zhsY = 850;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void 欧派() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = 159;
    SmallMapY = 19;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 2145;
    zhsY = 1228;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void 一般() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = 73;
    SmallMapY = 9;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 1649;
    zhsY = 977;
    屏幕x = 1;
    屏幕y = -88;
    读取();
}
void 胡萝卜() {
    touxiangdaxiao = 0;
    xiaodituxue = -2;
    jiange = 0;
    SmallMapX = 45;
    SmallMapY = 10;
    SmallHPX = -15;
    SmallHPY = 25;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 1500;
    zhsY = 850;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void 死了() {
    touxiangdaxiao = 0;
    xiaodituxue = 7;
    jiange = 0;
    SmallMapX = 73;
    SmallMapY = 16;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 0;
    zhsY = 0;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void 噢() {
    touxiangdaxiao = -67;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = -140;
    SmallMapY = 19;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 2341;
    zhsY = 1450;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void MI8() {
    touxiangdaxiao = 0;
    xiaodituxue = 0;
    jiange = 0;
    SmallMapX = -77;
    SmallMapY = 8;
    SmallHPX = 0;
    SmallHPY = 0;
    jinenglanzX = 0;
    jinenglanzY = 0;
    zhsX = 541;
    zhsY = 977;
    屏幕x = 0;
    屏幕y = 0;
    读取();
}
void SetResolution(int ScreenX, int ScreenY) {
    // 创建分辨率字符串
    char resolution[20];
    snprintf(resolution, sizeof(resolution), "%dx%d", ScreenX, ScreenY);

    if (strcmp(resolution, "2367x1080") == 0) {
        currentChoice = 0;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = 31;
        SmallMapY = 9;
        SmallHPX = 0;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 1527;
        zhsY = 977;
        屏幕x = 1;
        屏幕y = -88;
        读取();
    }
    else if (strcmp(resolution, "3200x1440") == 0) {
        currentChoice = 1;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = 90;
        SmallMapY = 16;
        SmallHPX = 0;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 2000;
        zhsY = 1288;
        屏幕x = 0;
        屏幕y = 0;
        读取();
    }
    else if (strcmp(resolution, "2712x1220") == 0) {
        currentChoice = 2;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = 62;
        SmallMapY = 12;
        SmallHPX = 8;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 2000;
        zhsY = 1288;
        屏幕x = 24;
        屏幕y = -192;
        读取();
    }
    else if (strcmp(resolution, "2400x1080") == 0) {
        currentChoice = 3;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = 31;
        SmallMapY = 9;
        SmallHPX = 28;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 1527;
        zhsY = 977;
        屏幕x = 0;
        屏幕y = 0;
        读取();
    }
    else if (strcmp(resolution, "2560x1600") == 0) {
        currentChoice = 4;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = 90;
        SmallMapY = 16;
        SmallHPX = 0;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 2000;
        zhsY = 1288;
        屏幕x = 0;
        屏幕y = 0;
        jiange = -5;
        读取();
    }
    else if (strcmp(resolution, "3192x1368") == 0) {
        currentChoice = 5;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = 159;
        SmallMapY = 19;
        SmallHPX = 0;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 2145;
        zhsY = 1228;
        屏幕x = 0;
        屏幕y = 0;
        读取();
    }
    else if (strcmp(resolution, "2340x1080") == 0) {
        currentChoice = 6;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = -2;
        xiaodituxue = -2;
        jiange = 0;
        SmallMapX = 12;
        SmallMapY = 10;
        SmallHPX = 0;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 1493;
        zhsY = 850;
        屏幕x = 0;
        屏幕y = 0;
        读取();
    }
    else if (strcmp(resolution, "2800x1800") == 0) {
        currentChoice = 7;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = 73;
        SmallMapY = 9;
        SmallHPX = 0;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 1649;
        zhsY = 977;
        屏幕x = 1;
        屏幕y = -88;
        读取();
    }
    else if (strcmp(resolution, "2460x1080") == 0) {
        currentChoice = 8;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = 159;
        SmallMapY = 19;
        SmallHPX = 0;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 2145;
        zhsY = 1228;
        屏幕x = 0;
        屏幕y = 0;
        读取();
    }
    else if (strcmp(resolution, "2160x1080") == 0) {
        currentChoice = 12;
        printf("[-] 屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
        touxiangdaxiao = 0;
        xiaodituxue = 0;
        jiange = 0;
        SmallMapX = -77;
        SmallMapY = 8;
        SmallHPX = 0;
        SmallHPY = 0;
        jinenglanzX = 0;
        jinenglanzY = 0;
        zhsX = 541;
        zhsY = 977;
        屏幕x = 0;
        屏幕y = 0;
        读取();
    }
    else {
        printf("[!] 不支持的屏幕分辨率: %dx%d\n", ScreenX, ScreenY);
    }
}
 

void 实体1() {
    顶上技能 = true;
    方框 = true;
    方框技能 = true;
    
    // 当选择实体1时，确保实体2不显示
    顶上技能2 = false;
    方框2 = false;
    方框技能2 = false;
    技能3 = false;
}

void 实体2() {
    顶上技能2 = true;
    方框2 = true;
    方框技能2 = true;
    
    // 当选择实体2时，确保实体1不显示
    顶上技能 = false;
    方框 = false;
    方框技能 = false;
    技能3 = false;
}
void 实体3(){ 
顶上技能 = true;
方框= true;
技能3 = true;
顶上技能2 = false;
方框2 = false;
方框技能2 = false;  
方框技能 = false;
}



bool permeate_record = false;
bool g_Initialized = false;
EGLDisplay display = EGL_NO_DISPLAY;
EGLConfig config;
EGLSurface surface = EGL_NO_SURFACE;
EGLContext context = EGL_NO_CONTEXT;
ANativeWindow *native_window;
int screen_x = 0, screen_y = 0;
int abs_ScreenX = 0, abs_ScreenY = 0;
int native_window_screen_x = 0, native_window_screen_y = 0;
android::ANativeWindowCreator::DisplayInfo displayInfo{0};
bool status = false;

int init_egl(int _screen_x, int _screen_y, bool log) {
  FILE* file = fopen("/data/小宋青云/防录屏", "r");
    if (file != NULL) {
        fclose(file);
        status = true;
    } else {
    	status = false;
	}
    native_window = android::ANativeWindowCreator::Create("Ssage7k7k", _screen_x, _screen_y, status);
     
    ANativeWindow_acquire(native_window);

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        printf("eglGetDisplay error=%u\n", glGetError());
        return -1;
    }
    if(log){
        printf("eglGetDisplay ok\n");
    }
    if (eglInitialize(display, 0, 0) != EGL_TRUE) {
        printf("eglInitialize error=%u\n", glGetError());
        return -1;
    }
    if(log){
        printf("eglInitialize ok\n");
    }
    EGLint num_config = 0;
    const EGLint attribList[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 5,   //-->delete
            EGL_GREEN_SIZE, 6,  //-->delete
            EGL_RED_SIZE, 5,    //-->delete
            EGL_BUFFER_SIZE, 32,  //-->new field
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, 8,
            EGL_NONE
    };
    if (eglChooseConfig(display, attribList, nullptr, 0, &num_config) != EGL_TRUE) {
        printf("eglChooseConfig  error=%u\n", glGetError());
        return -1;
    }
    if(log){
        printf("num_config=%d\n", num_config);
    }
    if (!eglChooseConfig(display, attribList, &config, 1, &num_config)) {
        printf("eglChooseConfig  error=%u\n", glGetError());
        return -1;
    }
    if(log){
        printf("eglChooseConfig ok\n");
    }
    EGLint egl_format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &egl_format);
    ANativeWindow_setBuffersGeometry(native_window, 0, 0, egl_format);
    const EGLint attrib_list[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, attrib_list);
    if (context == EGL_NO_CONTEXT) {
        printf("eglCreateContext  error = %u\n", glGetError());
        return -1;
    }
    if(log){
        printf("eglCreateContext ok\n");
    }
    surface = eglCreateWindowSurface(display, config, native_window, nullptr);
    if (surface == EGL_NO_SURFACE) {
        printf("eglCreateWindowSurface  error = %u\n", glGetError());
        return -1;
    }
    if(log){
        printf("eglCreateWindowSurface ok\n");
    }
    if (!eglMakeCurrent(display, surface, surface, context)) {
        printf("eglMakeCurrent  error = %u\n", glGetError());
        return -1;
    }
    if(log){
        printf("eglMakeCurrent ok\n");
    }
    
    
    
    return 1;
}




char *读取文件(char *path) {
    FILE *fp;
    if ((fp = fopen(path, "r")) == NULL) {
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    int filesize = ftell(fp);
    char *str;
    str = (char *) malloc(filesize);
    rewind(fp);
    fread(str, 1, filesize, fp);
    str[filesize] = '\0';
    fclose(fp);
    return str;
}

int 读取() {
    char *ndhdh = 读取文件("/data/小宋青云/配置.ini头像X");
    if (ndhdh) {
        SmallMapX = atof(ndhdh);
    }

    char *ndhdh2 = 读取文件("/data/小宋青云/配置.ini头像Y");
    if (ndhdh2) {
        SmallMapY = atof(ndhdh2);
    }

    char *ndhdh3 = 读取文件("/data/小宋青云/配置.ini实体X");
    if (ndhdh3) {
        SmallHPX = atof(ndhdh3);
    }

    char *ndhdh5 = 读取文件("/data/小宋青云/配置.ini实体Y");
    if (ndhdh5) {
        SmallHPY = atof(ndhdh5);
    }

    char *ndhdh6 = 读取文件("/data/小宋青云/配置.ini头像大小");
    if (ndhdh6) {
        touxiangdaxiao = atof(ndhdh6);
    }

    char *ndhdh7 = 读取文件("/data/小宋青云/配置.ini血量大小");
    if (ndhdh7) {
        xiaodituxue = atof(ndhdh7);
    }

    char *ndhdh8 = 读取文件("/data/小宋青云/配置.ini地图比例");
    if (ndhdh8) {
        jiange = atof(ndhdh8);
    }

    char *ndhdh9 = 读取文件("/data/小宋青云/配置.ini技能栏X");
    if (ndhdh9) {
        jinenglanzX = atof(ndhdh9);
    }

    char *ndhdh10 = 读取文件("/data/小宋青云/配置.ini技能栏Y");
    if (ndhdh10) {
        jinenglanzY = atof(ndhdh10);
    }

    char *ndhdh11 = 读取文件("/data/小宋青云/配置.ini上帝");
    if (ndhdh11) {
        shangdi = atof(ndhdh11);
    }

    char *ndhdh12 = 读取文件("/data/小宋青云/配置.ini视野X");
    if (ndhdh12) {
        屏幕x = atof(ndhdh12);
    }

    char *ndhdh13 = 读取文件("/data/小宋青云/配置.ini视野Y");
    if (ndhdh13) {
        屏幕y = atof(ndhdh13);
    }

    char *ndhdh14 = 读取文件("/data/小宋青云/配置.ini斩杀值");
    if (ndhdh14) {
        zhansha = atof(ndhdh14);
    }

    char *ndhdh16 = 读取文件("/data/小宋青云/配置.ini召唤师技能X");
    if (ndhdh16) {
        zhsX = atof(ndhdh16);
    }

    char *ndhdh17 = 读取文件("/data/小宋青云/配置.ini召唤师技能Y");
    if (ndhdh17) {
        zhsY = atof(ndhdh17);
    }

    char *ndhdh18 = 读取文件("/data/小宋青云/配置.iniFPS");
    if (ndhdh18) {
        FPS = atof(ndhdh18);
    }
    
    
    char *ndhdh24=读取文件("/data/颜色/傀儡x");
			if(ndhdh24){傀儡x= atof(ndhdh24);}
			
			char *ndhdh25=读取文件("/data/颜色/傀儡y");
			if(ndhdh25){傀儡y= atof(ndhdh25);}
   
char *ndhdh19 = 读取文件("/data/小宋青云/配置.ini自瞄位置");
if (ndhdh19)
{
    // 假设NumIo是一个全局数组，用于存储数值
    float x, y;
    sscanf(ndhdh19, "%f,%f", &x, &y); // 从字符串解析出坐标值
    NumIo[46] = x; // 更新自瞄位置的x坐标
    NumIo[45] = y; // 更新自瞄位置的y坐标

    free(ndhdh19); // 释放读取文件时分配的内存
}
 
    string LoadFile = "/data/小宋青云/配置.ini颜色配置";
    pdys = ReadDrawSet((总颜色 *) &颜色配置, LoadFile.c_str());

    return pdys;
}



#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

static int 录屏时长 = 9999; // 默认时间为900秒
static std::atomic<bool> isRecording(false); // 全局变量
static std::atomic<int> recordingTimeElapsed(0); // 录制经过的时间
static std::chrono::high_resolution_clock::time_point startTime; // 开始时间点

// 开始录制的函数
void startRecording(int duration) {
    isRecording.store(true);
    recordingTimeElapsed.store(0); // 开始时重置时间
    startTime = std::chrono::high_resolution_clock::now(); // 设置开始时间点

    // 非阻塞式开始录制
    std::string command = "screenrecord --time-limit " + std::to_string(duration) + " /sdcard/EA7录制.mp4";
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "录制失败，请检查screenrecord命令是否可用。" << std::endl;
        isRecording.store(false);
    }
}
// 停止录制的函数
void stopRecording() {
    // 停止screenrecord进程
    system("pkill -l SIGINT screenrecord");
    isRecording.store(false);
}

#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

static std::atomic<int> screenshotCount(0); // 截屏次数计数器
static std::atomic<bool> isScreenshotting(false); // 全局变量，表示是否正在截屏

// 开始截屏的函数
void takeScreenshot() {
    isScreenshotting.store(true);
    // 生成文件名，使用计数器确保文件名唯一
    std::string filename = "/sdcard/EA7截屏_" + std::to_string(++screenshotCount) + ".png";

    // 执行screencap命令
    std::string command = "screencap -p " + filename;
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "截屏失败，请检查screencap命令是否可用。" << std::endl;
        --screenshotCount; // 如果截屏失败，则计数器不增加
    } else {
        std::cout << "截屏成功，图片保存在: " << filename << std::endl;
    }
    isScreenshotting.store(false);
}

#include <arpa/inet.h>
#include <cstdlib>
#include <ctime>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <iostream>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;
// 用于存储当前选择的选项







// 在你的主循环中调用 ShowComboAndCallFunction
void 写出文件(char *aaa, char *bbb) {

    std::ofstream ofs;

    ofs.open(aaa, std::ios::out);

    ofs << bbb;

    ofs.close();
}
 
//std::thread 基址(DrawInit);
//std::thread 算法(解密算法);


 // 异步启动游戏
void async_start_game() {
    system("am start -n com.tencent.tmgp.sgame/.SGameActivity >/dev/null 2>&1");
}
int hotkey_monitor() {
    printf("\033[33;1m"); // 黄色
    printf("-------------------------\n");
    printf("\033[36;1m"); // 蓝色
    printf("[-] 音量+键开关悬浮窗\n");
    int EventCount = GetEventCount();
    if (EventCount < 0) {
        printf("\033[31;1m"); // 红色
        printf("[!] No found EventCount\n");
        exit(1);
    }
    int* fdArray = (int*)malloc(EventCount * sizeof(int));
    for (int i = 0; i < EventCount; i++) {
        char temp[128];
        sprintf(temp, "/dev/input/event%d", i);
        fdArray[i] = open(temp, O_RDWR | O_NONBLOCK);
    }
    input_event ev;

    while (!stopFlag) {
        for (int i = 0; i < EventCount; i++) {
            memset(&ev, 0, sizeof(ev));
            read(fdArray[i], &ev, sizeof(ev));
            if (ev.type == EV_KEY && ev.code == KEY_VOLUMEUP && ev.value == 1) {
                // count++;
                printf("\033[36;1m"); // 蓝色
                if (悬浮窗) {
                    悬浮窗 = false;
                    printf("[-] 悬浮窗已关闭\n\033[1A");
                }
                else if (!悬浮窗) {
                    悬浮窗 = true;
                    printf("[-] 悬浮窗已开启\n\033[1A");
                }
            }
        }
        usleep(1000 * 200);
    }
    return 0;
}

void ImGui_init() {
    if (g_Initialized) {
        return;
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.IniFilename = NULL;
    /*switch (Color[0])
    {
        case 0:
           // ImGui::StyleColorsRed();
                   ImGui::StyleColorsDark;
        break;
        case 1:
            ImGui::StyleColorsBlue();
        break;
        case 2:
            ImGui::StyleColorsOrange();
        break;
        }
  */
    new std::thread(hotkey_monitor);
    获取头像2();
    获取图标();
    获取其他图标();
    Icon = ImAgeHeadFile1(SXlogo, sizeof(SXlogo));
    BJ = ImAgeHeadFile1(BJlogo, sizeof(BJlogo));
    int pdys = 读取();
    //获取进程ID
    pid = getPID("com.tencent.tmgp.sgame");
    //获取坐标
    yxpx = abs_ScreenX;
    yxpy = abs_ScreenY;
    SetResolution(yxpx,yxpy);

    // gotpid();
    ImGui_ImplAndroid_Init(native_window);
    ImGui_ImplOpenGL3_Init("#version 300 es");

    ImFontConfig font_cfg;
    font_cfg.SizePixels = 20.0f;
    io.Fonts->AddFontFromMemoryTTF((void *) font_v, font_v_size, 28.0f, NULL,io.Fonts->GetGlyphRangesChineseFull());
    io.Fonts->AddFontDefault(&font_cfg);

    ImGui::GetStyle().ScaleAllSizes(3.0f);
    g_Initialized = true;
}

int huitu = 0;

void tick() {

FPS限制.AotuFPS_init();
float 帧率 = 1000.0f / FPS限制.AotuFPS();

    ImGuiStyle& style = ImGui::GetStyle();

    // 主要配色：白色背景 + 紫色元素
    style.Colors[ImGuiCol_Text] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.25f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.60f, 0.20f, 0.90f, 1.00f); // 紫色边框

    // 标题栏配色
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);

    // 按钮配色 - 紫色主题
    style.Colors[ImGuiCol_Button] = ImVec4(0.70f, 0.40f, 0.90f, 0.80f); // 浅紫色按钮
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.75f, 0.45f, 0.95f, 1.00f); // 悬停时更亮的紫色
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.65f, 0.35f, 0.85f, 1.00f); // 按下时更深的紫色

    // 框架和滑块配色 - 紫色主题
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.75f, 0.50f, 0.95f, 0.30f); // 浅紫色框架背景
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.75f, 0.50f, 0.95f, 0.40f); // 悬停时更明显
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.75f, 0.50f, 0.95f, 0.50f); // 激活时更明显
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.20f, 0.90f, 1.00f); // 紫色滑块抓取点
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.65f, 0.25f, 0.95f, 1.00f); // 激活的滑块抓取点

    // 勾选框和选择状态 - 紫色主题
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.20f, 0.90f, 1.00f); // 紫色勾选标记
    style.Colors[ImGuiCol_Header] = ImVec4(0.75f, 0.50f, 0.95f, 0.40f); // 紫色标题背景
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.50f, 0.95f, 0.60f); // 悬停时更明显
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.75f, 0.50f, 0.95f, 0.80f); // 激活时更明显

    // 分隔线和滚动条 - 紫色主题
    style.Colors[ImGuiCol_Separator] = ImVec4(0.60f, 0.20f, 0.90f, 0.50f); // 紫色分隔线
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.20f, 0.90f, 0.70f); // 悬停的分隔线
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.60f, 0.20f, 0.90f, 0.90f); // 激活的分隔线
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f); // 滚动条背景保持白色
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.70f, 0.40f, 0.90f, 0.80f); // 紫色滚动条抓取点
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.75f, 0.45f, 0.95f, 1.00f); // 悬停的滚动条
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.65f, 0.35f, 0.85f, 1.00f); // 激活的滚动条

    // 标签页配色 - 紫色主题
    style.Colors[ImGuiCol_Tab] = ImVec4(0.70f, 0.40f, 0.90f, 0.80f); // 紫色标签
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.75f, 0.45f, 0.95f, 1.00f); // 悬停的标签
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.65f, 0.35f, 0.85f, 1.00f); // 激活的标签
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.70f, 0.40f, 0.90f, 0.60f); // 未聚焦的标签
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.70f, 0.40f, 0.90f, 0.70f); // 未聚焦但激活的标签

    // 圆角设置
    style.FrameRounding = 4.0f;
    style.WindowRounding = 12.0f; // 窗口圆角
    style.ChildRounding = 6.0f;
    style.ScrollbarRounding = 4.0f;
    style.TabRounding = 6.0f;

    // 间距和尺寸
    style.ItemSpacing = ImVec2(10, 6);
    style.ItemInnerSpacing = ImVec2(8, 4);
    style.WindowPadding = ImVec2(12, 12);
    style.ScrollbarSize = 14.0f;
    style.GrabMinSize = 12.0f;
if (悬浮窗) {
// 悬浮窗
    ImGui::SetNextWindowSize(ImVec2(740, 540), ImGuiCond_FirstUseEver);
    ImGui::Begin("王者荣耀CR内部（free）- 7.5", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImVec2 windowPos = ImGui::GetWindowPos(); // 获取窗口位置
    DrawBJ(ImVec2(windowPos.x + 370, windowPos.y + 270), 734.0f, 534.0f); // 窗口背景图绘制

    // ================ 侧边栏菜单 (方形按钮布局) ================
    ImGui::BeginChild("Sidebar", ImVec2(160, 0), true);
    // 统一参数
    const float buttonSizeX = 140.0f;        // 按钮宽
    const float buttonSizeY = 70.0f;        // 按钮高
    const float horizontalMargin = (150 - buttonSizeX) / 2; // 水平居中
    const float verticalSpacing = 10.0f;   // 按钮间距

    // 设置按钮大小样式
    ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0)); // 移除内边距


    DrawICON(ImVec2(windowPos.x + 90, windowPos.y + 100), 120.0f); // 在左上角绘制30x30图标
    ImGui::Dummy(ImVec2(0, 145)); // 更多留白
    // 辅助信息按钮
    ImGui::SetCursorPosX(horizontalMargin);
    if (ImGui::Selectable("主页区域", currentTab == 0, 0, ImVec2(buttonSizeX, buttonSizeY)))
        currentTab = 0;

    // 绘制功能按钮
    ImGui::SetCursorPosX(horizontalMargin);
    if (ImGui::Selectable("绘制区域", currentTab == 1, 0, ImVec2(buttonSizeX, buttonSizeY)))
        currentTab = 1;

    // 绘制设置按钮
    ImGui::SetCursorPosX(horizontalMargin);
    if (ImGui::Selectable("设置区域", currentTab == 2, 0, ImVec2(buttonSizeX, buttonSizeY)))
        currentTab = 2;

    // 退出辅助按钮
    ImGui::SetCursorPosX(horizontalMargin);
    if (ImGui::Selectable("缩小辅助", currentTab == 3, 0, ImVec2(buttonSizeX, buttonSizeY)))
        悬浮窗 = false;

    ImGui::PopStyleVar(2); // 恢复样式
    ImGui::EndChild();

    // ================ 内容区域 ================
    ImGui::SameLine();
    ImGui::BeginChild("Content", ImVec2(0, 0), true);

    // ====================== 分组1：信息 ======================
    if (currentTab == 0) {

        ImGui::TextColored(ImVec4(0.60f, 0.20f, 0.90f, 1.00f), " · 主页");
        ImGui::Separator();
        // 主控制按钮
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
        if (huitu == 0) {
            if (ImGui::Button("开启绘制", ImVec2(ImGui::GetContentRegionAvail().x, 60))) {
                huitu = 1;
                血量 = 1;
                read_config();
            }
        }
        else {
            if (pid == 0 || pid == -1) {
                血量 = 0;
                read_config();
                if (ImGui::Button("启动游戏", ImVec2(ImGui::GetContentRegionAvail().x, 60))) {
                    std::thread game_thread(async_start_game);
                    game_thread.detach();
                    huitu = 0;
                }
            }
            else {
                if (ImGui::Button("退出辅助", ImVec2(ImGui::GetContentRegionAvail().x, 60))) {
                    stopFlag = true;
                    write_config();
                    exit(0);
                }
            }
        }
        // 状态信息
        ImGui::Text("当前状态:");
        if (pid == 0 || pid == -1) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "游戏未运行");
        }
        else {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.3f, 1.0f, 0.3f, 1.0f), "游戏运行中...");
            ImGui::Text("游戏进程: %d", pid);
            ImGui::Text("设备分辨率: %dx%d", yxpx, yxpy);
            ImGui::Text("设备帧率 %.1f FPS", ImGui::GetIO().Framerate);
        }
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), " · 小宋青云内核 - 顶峰论道");
        ImGui::Separator();
        ImGui::SetNextWindowSize(ImVec2(100.0f, 0.0f)); // 设置组合框的宽度为100像素，高度自动计算
        if (ImGui::BeginCombo("分辨率", "当前选择: ")) {
            if (ImGui::Selectable("2367x1080")) currentChoice = 0;
            if (ImGui::Selectable("3200x1440")) currentChoice = 1;
            if (ImGui::Selectable("2712x1220")) currentChoice = 2;
            if (ImGui::Selectable("2400x1080")) currentChoice = 3;
            if (ImGui::Selectable("2560x1600")) currentChoice = 4;
            if (ImGui::Selectable("3192x1368")) currentChoice = 5;
            if (ImGui::Selectable("2340x1080")) currentChoice = 6;
            if (ImGui::Selectable("2800x1800")) currentChoice = 7;
            if (ImGui::Selectable("2460x1080")) currentChoice = 8;
            if (ImGui::Selectable("小米14专属")) currentChoice = 9;
            if (ImGui::Selectable("3168x1440")) currentChoice = 10;
            if (ImGui::Selectable("2800x1968")) currentChoice = 11;
            if (ImGui::Selectable("2160x1080")) currentChoice = 12;
            ImGui::EndCombo();
        }
        if (currentChoice != -1) {
            switch (currentChoice) {
            case 0:
                一加();
                break;
            case 1:
                王者();
                break;
            case 2:
                荣耀();
                break;
            case 3:
                神明();
                break;
            case 4:
                无敌();
                break;
            case 5:
                咳咳();
                break;
            case 6:
                欧凯();
                break;
            case 7:
                一般();
                break;
            case 8:
                欧派();
                break;
            case 9:
                胡萝卜();
                break;
            case 10:
                死了();
                break;
            case 11:
                噢();
                break;
            case 12:
                MI8();
                break;
            }
            currentChoice = -1; // 重置选择，使其不保持状态
        }
        // 功能按钮
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 10));
        if (ImGui::Button("强制截图", ImVec2(ImGui::GetContentRegionAvail().x, 60))) {
            system("su -c screencap -p /sdcard/截屏.jpg");
        }
        if (ImGui::Button("保存配置", ImVec2(ImGui::GetContentRegionAvail().x, 60))) {
            string SaveFile;
            SaveFile = "/data/小宋青云/配置.ini";
            pdys = SaveDrawSet((总颜色*)&颜色配置, SaveFile.c_str());
        }
        ImGui::Separator();
        ImGui::PopStyleVar();
    }

    // ====================== 分组2：绘制 ======================
    else if (currentTab == 1) {
        // 功能开关标题
        ImGui::TextColored(ImVec4(0.60f, 0.20f, 0.90f, 1.00f), " • 绘制");
        ImGui::Separator();

        // 功能开关布局
        ImGui::Columns(3, "##func_cols", true);
        ImGui::Checkbox("头像常显", &头像常显);
        ImGui::NextColumn();
        ImGui::Checkbox("技能计时", &小技能计时);
        ImGui::NextColumn();
        ImGui::Checkbox("屏幕暗化", &暗化);
        ImGui::NextColumn();

        ImGui::Checkbox("地图头像", &地图);
        ImGui::NextColumn();
        ImGui::Checkbox("绘制方框", &方框);
        ImGui::NextColumn();
        ImGui::Checkbox("方框技能", &方框技能);
        ImGui::NextColumn();

        ImGui::Checkbox("顶上技能", &顶上技能);
        ImGui::NextColumn();
        ImGui::Checkbox("绘制兵线", &兵线);
        ImGui::NextColumn();
        ImGui::Checkbox("野怪计时", &野怪);
        ImGui::NextColumn();

        ImGui::Checkbox("绘制射线", &射线);
        ImGui::NextColumn();
        ImGui::Checkbox("敌人可视", &视野方框);
        ImGui::NextColumn();
        ImGui::Checkbox("自身可视", &自身);
        ImGui::Columns(1);
    }

    // ====================== 分组3：设置 ======================
    else if (currentTab == 2) {
        // 位置调整
        ImGui::TextColored(ImVec4(0.60f, 0.20f, 0.90f, 1.00f), " · 设置");
        ImGui::Separator();
        if (ImGui::SliderInt("头像X", &SmallMapX, -200, 200, "X: %d")) {
            char urlls[2560];
            sprintf(urlls, "%d", SmallMapX);
            写出文件("/data/小宋青云/配置.ini头像X", urlls);
        }
        if (ImGui::SliderInt("头像Y", &SmallMapY, -200, 200, "Y: %d")) {
            char urlls[2560];
            sprintf(urlls, "%d", SmallMapY);
            写出文件("/data/小宋青云/配置.ini头像Y", urlls);
        }
        if (ImGui::SliderInt("头像大小", &touxiangdaxiao, -300, 300, "大小: %d")) {
            char urlls[2560];
            sprintf(urlls, "%d", touxiangdaxiao);
            写出文件("/data/小宋青云/配置.ini头像大小", urlls);
        }
        if (ImGui::SliderInt("血量大小", &xiaodituxue, -80, 80, "大小: %d")) {
            char urlls[2560];
            sprintf(urlls, "%d", xiaodituxue);
            写出文件("/data/小宋青云/配置.ini血量大小", urlls);
        }
        if (ImGui::SliderInt("地图比例", &jiange, -100, 100, "比例: %d")) {
            char urlls[2560];
            sprintf(urlls, "%d", jiange);
            写出文件("/data/小宋青云/配置.ini地图比例", urlls);
        }
        // 傀儡设置
        if (ImGui::SliderInt("傀儡实体x", &傀儡x, -100, 100, "X: %d")) {
            char urlls[2560];
            sprintf(urlls, "%d", 傀儡x);
            写出文件("/data/颜色/傀儡x", urlls);
        }
        if (ImGui::SliderInt("傀儡实体y", &傀儡y, -100, 100, "Y: %d")) {
            char urlls[2560];
            sprintf(urlls, "%d", 傀儡y);
            写出文件("/data/颜色/傀儡y", urlls);
        }
    }
    ImGui::EndChild();
}

    if (IsWin) {
        IsWin = false;
        IsLoGin = false;
        BallSwitch = false;
        ImGui::SetWindowSize("Ball", {100.0f, 100.0f});
    }
    /*****绘制帧率*****/
    // char fkhs[1000];
    // sprintf(fkhs,"%.1f FPS",ImGui::GetIO().Framerate);
    //  ImGui::GetForegroundDrawList()->AddText(ImVec2(300,
    //  1000),ImColor(225,255,255),fkhs);
    // ImGui::GetForegroundDrawList()->AddText(ImVec2(90,
    // 1000),ImColor(225,255,255),"TS内部解密 状态稳定");
    /*****结束*****/
    if (huitu == 1) {
        DrawPlayer(); // 调用绘图  直接写在这边的话有点影响观看了
        
    }
}

void screen_config() {
    ::displayInfo = android::ANativeWindowCreator::GetDisplayInfo();
    ::screen_x = displayInfo.width;
    ::screen_y = displayInfo.height;
}

void drawBegin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(native_window_screen_x, native_window_screen_y);
    ImGui::NewFrame();

    screen_config();

    static uint32_t orientation = -1;
    if (orientation != displayInfo.orientation) {
        orientation = displayInfo.orientation;
        Touch::setOrientation(displayInfo.orientation);
        屏幕方向 = displayInfo.orientation;
        // cout << " width:" << displayInfo.width << " height:" <<
        // displayInfo.height << " orientation:" << displayInfo.orientation << endl;
    }
}

void drawEnd() {
    ImGuiIO &io = ImGui::GetIO();
    glViewport(0.0f, 0.0f, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT); // GL_DEPTH_BUFFER_BIT
    glFlush();
    if (display == EGL_NO_DISPLAY) {
        return;
    }
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    eglSwapBuffers(display, surface);
}

void shutdown() {
    if (!g_Initialized) {
        return;
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplAndroid_Shutdown();
    ImGui::DestroyContext();
    if (display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context != EGL_NO_CONTEXT) {
            eglDestroyContext(display, context);
        }
        if (surface != EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }
        eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;
    ANativeWindow_release(native_window);
}
