int aimMode = 1;
Vector2 jn2pos = {NumIo[46], NumIo[45]};
float jnsize = 88;
Vector2 downPos;
int lastSlot;
Vector2 upLoadPos;
Vector2 upLoadPosN;
int 预判;
Vector2 Angle;
int yupanYanchi = 0;
float yupan = 0;//预判幅度
//触摸位置拖动

//不用看了 狗屎源码 还带后门的

//该删除的后门 泪心基本已经删除  
//删不了的后门 那也尽力了
//UI还好看 有能力自己抄抄
//绘图就没必要了   直接不看  狗屎一样的源码
//UI比较好抄   抄两个图片绘制  炒个Ui菜单源码

// 技术分析 TG@TearGame

//泪心王者荣耀源码分享




void Getxfctouch2() {
    for (;;) {
        usleep(2000);
        ImGuiIO &ioooi = ImGui::GetIO();

        if (DrawIo[17] && ioooi.MouseDown[0] && point.x <= NumIo[46] + NumIo[47] &&
            point.y <= NumIo[45] + NumIo[47] && point.x >= NumIo[46] - NumIo[47] &&
            point.y >= NumIo[45] - NumIo[47]) {
            usleep(55000);

            while (ioooi.MouseDown[0]) {

                NumIo[46] = point.x;
                NumIo[45] = point.y;
                jn2pos.x = NumIo[46];
                jn2pos.y = NumIo[45];

                usleep(500);
            }

        }

    }
}

bool IsMovIng(long classthis) {
    int mov = driver->read<int>(
            ReadValue(ReadValue(ReadValue(ReadValue(classthis + 0x118) + 0x10) + 0x118) + 0x140) +
            0x70);

    //int mov = driver->read<int>(Address);
    if (mov == 0)
        return false;
    else
        return true;
}

Vector3 GetPlayerPos(long classthis) {

    long Address = ReadValue(
            ReadValue(ReadValue(ReadValue(classthis + 0x248) + 0x10) + 0x00) + 0x10);


    Vector3 Pos;
    Pos.x = (float) driver->read<int>(Address);
    Pos.z = (float) driver->read<int>(Address + 0x4);
    Pos.y = (float) driver->read<int>(Address + 0x8);

    return Pos;

}


Vector2 getXyPos(long classthis) {
    long Address = ReadValue((classthis + 0x118));
    Address = Address + 0X80;
    Vector2 ret;
    ret.x = (float) driver->read<int>(Address);
    ret.y = (float) driver->read<int>(Address + 8);
    return ret;
}

static void TouchAim(std::vector <Touch::Device> *devices) {

    for (auto &device: *devices) {
        for (auto &obj: device.Finger) {
            if (Aim) {

                if (AimTarget) {

                    if (obj.isDown) {

                        if (!isAimDown) {
                            auto pos = Touch::Touch2Screen(obj.pos);

                            //printf("(%f %f)\n",jn2pos.x,jn2pos.y);
                            float rad = q2djl(jn2pos, pos);
                            //printf("(%f)\n",rad);
                            if (rad < jnsize) {
                                //std::cout<< " isAimDown " <<"\n";
                                lastTouchObj = &obj;
                                isAimDown = true;

                                downPos = obj.pos / Touch::GetScale();

                                lastSlot = obj.id;
                            }

                        } else if (obj.id == lastSlot) {
                            auto pos = Touch::Touch2Screen(obj.pos);

                            if (pos.y < (float) abs_ScreenY / 4 &&
                                pos.x < (float) abs_ScreenX / 2) {
                                lastSlot = -1;
                                downPos.zero();
                                isAimDown = false;

                                //printf("1\n");
                            } else {


                                //printf("1\n");
                                obj.pos = upLoadPos * Touch::GetScale();


                            }
                        }
                    } else if (isAimDown && obj.id == lastSlot) {
                        lastSlot = -1;
                        downPos.zero();
                        isAimDown = false;


                    }
                }
            }
        }
    }
    Touch::Upload();
}

static void TraceAim(std::vector <Touch::Device> *devices) {
    for (auto &device: *devices) {
        for (auto &obj: device.Finger) {
            if (Aim) {
                if (AimTarget) {

                    if (obj.isDown) {
                        if (!isAimDown) {
                            auto pos = Touch::Touch2Screen(obj.pos);
                            float rad = q2djl(jn2pos, pos);
                            if (rad < jnsize) {
                                //std::cout<< " isAimDown " <<"\n";
                                isAimDown = true;
                                downPos = obj.pos / Touch::GetScale();
                                lastSlot = obj.id;
                            }
                        } else if (obj.id == lastSlot) {
                            auto pos = Touch::Touch2Screen(obj.pos);
                            //std::cout<< "Y --- "<<pos.y<<" Y / ->"<<(float)screen_y / 4<<"\n";
                            if (pos.y < (float) abs_ScreenY / 4 &&
                                pos.x < (float) abs_ScreenX / 2) {
                                //std::cout<< " isAimUp " <<"\n";
                                lastSlot = -1;
                                downPos.zero();
                                isAimDown = false;
                            }
                        }
                    } else if (isAimDown && obj.id == lastSlot) {
                        //std::cout<<"执行\n";
                        obj.isDown = true;
                        obj.pos = upLoadPos * Touch::GetScale();
                        Touch::Upload();
                        usleep(11000);

                        obj.isDown = false;
                        Touch::Upload();
                        lastSlot = -1;
                        downPos.zero();
                        isAimDown = false;
                        return;
                    }
                }
            }
        }
    }
    Touch::Upload();
}

static void TouchCallBack(std::vector <Touch::Device> *devices) {

    if (aimMode == 0) {
        TouchAim(devices);
    } else {
        TraceAim(devices);
    }


}

#include <chrono>

Vector2 lastAimTargetPos;
std::chrono::steady_clock::time_point lastRecordTime;

float dx, dy;
std::chrono::steady_clock::time_point currentTime;
int64_t timeSinceLastRecord;

#include <math.h>

float calculateDistance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

long getcoor(long addr) {
    return driver->read<uint64_t>(driver->read<uint64_t>(
            driver->read<uint64_t>(driver->read<uint64_t>(addr + 0x240) + 0x10) + 0x0) + 0x10);
}

void *QuYangAim(void *arg) {
    Vector3 lastPos;
    Vector3 velocity;
    Vector2 initPos = {-1, -1};
    Vector2 beforePos = initPos;
    Vector2 lastUpLoadPos;
    lastRecordTime = std::chrono::steady_clock::now();
    lastAimTargetPos = initPos;
    isMove = false;
    while (Aim) {
        if (AimTarget && isAimDown) {

            Vector3 myPos = GetPlayerPos(localplayer);
            TargetPos = Vector2{(float) driver->read<int>(getcoor(AimTarget) + 0x0),
                                (float) driver->read<int>(getcoor(AimTarget) + 0x8)};
            currentTime = std::chrono::steady_clock::now();
            timeSinceLastRecord = std::chrono::duration_cast<std::chrono::milliseconds>(
                    currentTime - lastRecordTime).count();
            if (TargetPos.x != 0 && TargetPos.y != 0) {
                if (timeSinceLastRecord >= 200) {
                    isMove = lastAimTargetPos != TargetPos;
                    lastAimTargetPos = TargetPos;
                    lastRecordTime = currentTime;
                    float ts = calculateDistance(myPos.x, myPos.y, TargetPos.x, TargetPos.y) /
                               60000;// 根据距离来调整预判幅度
                    dx = (TargetPos.x - beforePos.x) * 预判 * ts;
                    dy = (TargetPos.y - beforePos.y) * 预判 * ts;
                    beforePos = TargetPos;
                }
                Vector2 tempPos = TargetPos;
                if (isMove) {
                    tempPos.x = TargetPos.x + dx;
                    tempPos.y = TargetPos.y + dy;
                    TargetPos2 = tempPos;
                }
                float x = tempPos.x - myPos.x;
                float y = tempPos.y - myPos.y;
                float c = sqrt(x * x + y * y);
                Angle.x = x / c * localplayerCamp;
                Angle.y = y / c * localplayerCamp;
                upLoadPos = downPos + Vector2(Angle.y, Angle.x) * 250;
                upLoadPosN = upLoadPos * Touch::GetScale();
                upLoadPosN = Touch::Touch2Screen(upLoadPosN);
            }
           if (aimMode == 0 && lastTouchObj && select_mode == 1 && select_mode == 2) {
                lastUpLoadPos = upLoadPos;
                Touch::Move(lastTouchObj, upLoadPos.x, upLoadPos.y);
            }
        } else {
            lastPos.Zero();

        }
        usleep(6000);
    }

    return nullptr;
}
