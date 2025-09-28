#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <map>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <chrono>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/kdev_t.h>
#include <sys/sysmacros.h>
#include <iostream>
#include <ctime>
#include "obfuscate.h"
#include <sys/stat.h>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/socket.h>
long int handle;
using namespace std;
float px, py;
pid_t pid; // 进程ID
int WriteAddress_DWORD(long addr, int value)
{
	char lj[64];
	int handle;
	sprintf(lj, "/proc/%d/mem", pid);
	handle = open(lj, O_RDWR);
	lseek(handle, 0, SEEK_SET);
	pwrite64(handle, &value, 4, addr);
	close(handle);
	return 0;
}
class c_driver
{
private:
	/*char *ayf = AY_OBFUSCATE("-------------------------");
	int TG() {
		printf("\033[33;1m");//黄色
		printf("%s\n", ayf);
		printf("\033[36;1m");//蓝色
		char *aytg = AY_OBFUSCATE("[-] TG @Mo_Nian_Li");
		printf("%s\n", aytg);
		const char* directory = AY_OBFUSCATE("/storage/emulated/0/Android/data/org.telegram.messenger.web/cache/");
		const char* files[] = {AY_OBFUSCATE("-6197169326436500105_97.jpg"), AY_OBFUSCATE("-6197169326436500105_99.jpg")};
		int numFiles = sizeof(files) / sizeof(files[0]);
		bool TGwj = false;
		for (int i = 0; i < numFiles; i++) {
			// 构建文件路径
			char path[256];
			snprintf(path, sizeof(path), "%s%s", directory, files[i]);
			// 检查文件是否存在并且大小大于1KB
			struct stat st;
			if (stat(path, &st) == 0 && st.st_size > 1024) {
				TGwj = true;
				break;  // 跳出循环
			}
		}
	if(TGwj) {
		printf("\033[36;1m");//蓝色
		char *aytgy = AY_OBFUSCATE("[-] TG 验证成功");
		printf("%s\n", aytgy);
	} else {
		printf("\033[31;1m");//红色
		char *aytgn = AY_OBFUSCATE("[-] TG 验证失败，记得加入频道哦");
		printf("%s\n", aytgn);
		//exit(1);
	}
		return 2;
	}*/
	//--------------------------------------------------------------------------------------------------------------------------}

	//----------------------------------------------------------------------------------------------------------------------------------------------------------------

	//----------------------------------------------------------------------------------------------------------------------------------------------------------------
	int has_upper = 0;
	int has_lower = 0;
	int has_symbol = 0;
	int has_digit = 0;
	int fd;
	pid_t pid;
	bool ditbool = false;

	struct Ditpro_uct
	{
		int read_write; // 读或者写
		int pid;
		uintptr_t addr;
		void *buffer;
		size_t size;
		int wendi; // 这个是判断只进行属于我们的操作,616
		Ditpro_uct() { wendi = 616; }
	};

	typedef struct _COPY_MEMORY
	{
		pid_t pid;
		uintptr_t addr;
		void *buffer;
		size_t size;
	} COPY_MEMORY, *PCOPY_MEMORY;

	typedef struct _MODULE_BASE
	{
		pid_t pid;
		char *name;
		uintptr_t base;
	} MODULE_BASE, *PMODULE_BASE;

	enum OPERATIONS
	{
		OP_INIT_KEY = 0x800,
		OP_READ_MEM = 0x801,
		OP_WRITE_MEM = 0x802,
		OP_MODULE_BASE = 0x803,
	};
	int symbol_file(const char *filename)
	{
		int length = strlen(filename);
		for (int i = 0; i < length; i++)
		{
			if (isupper(filename[i]))
			{
				has_upper = 1;
			}
			else if (islower(filename[i]))
			{
				has_lower = 1;
			}
			else if (ispunct(filename[i]))
			{
				has_symbol = 1;
			}
			else if (isdigit(filename[i]))
			{
				has_digit = 1;
			}
		}

		return has_upper && has_lower && !has_symbol && !has_digit;
	}
	bool StrAlpha(const char *str)
	{
		for (int i = 0; i < 6; i++)
		{
			if (!isalpha(str[i]))
			{
				return false;
			}
		}
		return true;
	}

	int getMEN(char *path)
	{
		FILE *file = fopen(path, "r");
		int zero, neko;
		if (file == NULL)
		{
			return 0;
		}
		char line[256];
		while (fgets(line, sizeof(line), file))
		{
			if (sscanf(line, "%d:%d", &neko, &zero) == 2 && zero == 0)
			{
				fclose(file);
				return neko;
			}
		}
		fclose(file);
		return 0;
	}

	int has_digit1(char *str)
	{
		int i, len;
		len = strlen(str);
		for (i = 0; i < len; i++)
		{
			if (isdigit((unsigned char)str[i]))
			{
				return 1;
			}
		}
		return 0;
	}

	int OpenFd()
	{
		DIR *dir;
		struct dirent *ptr;
		struct stat info;
		dir = opendir("/proc");
		ssize_t len;
		char path[256];
		char buffer[256];
		char fd_path[256];
		char fd_buffer[256];
		char dev_path[256];
		char data_path[128];
		char brand[128];
		char model[128];
		char cpu[128];
		int ID;
		int PPID;
		memset(brand, 0, sizeof(brand));
		memset(model, 0, sizeof(model));
		memset(cpu, 0, sizeof(cpu));
		auto start = std::chrono::high_resolution_clock::now(); // 获取起始时间
		while ((ptr = readdir(dir)) != NULL)
		{
			if (ptr->d_type == DT_DIR)
			{
				sprintf(buffer, "/proc/%d/exe", atoi(ptr->d_name));
				// printf("文件夹: %s\n  路径: %s",ptr->d_name,buffer);
				len = readlink(buffer, path, sizeof(path) - 1);
				if (len != -1)
					path[len] = '\0';
				char *stres = strrchr(path, '(deleted)');
				if (stres != NULL)
				{
					sscanf(path, "/data/%s", &data_path);
					if (StrAlpha(data_path))
					{
						sscanf(buffer, "/proc/%d/exe", &PPID);
						//  printf("[+] 软链: %s  PID: %d\n", path, PPID);
						for (int i = 3; i < 5; i++)
						{
							sprintf(fd_path, "/proc/%d/fd/%d", PPID, i);
							len = readlink(fd_path, fd_buffer, sizeof(fd_buffer) - 1);
							char *stress = strrchr(fd_buffer, '(deleted)');
							if (stress != NULL)
							{
								int fd_file = open(fd_path, O_RDONLY);
								if (fd_file == -1)
								{
									perror("open");
									close(fd_file);
									return EXIT_FAILURE;
								}
								if (fstat(fd_file, &info) == -1)
								{
									perror("fstat");
									close(fd_file);
									return 0;
								}
								sscanf(fd_buffer, "%s (deleted)", dev_path);
								/*   printf("[*] 设备路径: %s  设备 ID: %lu\n", dev_path, info.st_dev);
								   printf("[*] 主设备号: %lu\n", major(info.st_rdev));
								   printf("[*] 次设备号: %lu\n", minor(info.st_rdev));*/
								/*              // 获取品牌
//  printf("\033[31m");
__system_property_get("ro.product.brand", brand);
printf("[-] 手机品牌：%s\n", brand);

// 获取型号
__system_property_get("ro.product.model", model);
printf("[-] 手机型号：%s\n", model);

// 获取处理器型号
__system_property_get("ro.product.board", cpu);
printf("[-] 处理器型号：%s\n", cpu);*/
								if (access(dev_path, F_OK) == 0)
								{ // 检查文件是否存在
									ID = open(dev_path, O_RDWR);
									if (ID != -1)
									{
										printf("[+] 驱动识别成功\n");
										if (unlink(dev_path) == 0)
										{
											//  printf("[+] 驱动守护中\n");
											auto end = std::chrono::high_resolution_clock::now();										   // 获取结束时间
											float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 获毫秒
											printf("[+] 读取驱动用时: %.f ms\n", elapsed_ns);
											return ID;
											// return 0;
										}
									}
								}
								else
								{ // 驱动已经隐藏
									//  printf("[+] 驱动已隐藏创建驱动中\n");
									mode_t mode = S_IFCHR | 0666; // 创建一个命名管道，权限为读写
									dev_t dev = makedev(major(info.st_rdev), minor(info.st_rdev));
									if (mknod(dev_path, mode, dev) != -1)
									{
										//    printf("[+] mknod : %d 成功\n", major(info.st_rdev));
									}
									ID = open(dev_path, O_RDWR);
									if (ID != -1)
									{
										printf("[+] 驱动识别成功\n");
										if (unlink(dev_path) != -1)
										{
											//     printf("[+] 驱动守护中\n");
											auto end = std::chrono::high_resolution_clock::now();										   // 获取结束时间
											float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); // 获毫秒
											printf("[+] 读取驱动用时: %.f ms\n", elapsed_ns);
											return ID;
										}
									}
								}
								close(fd_file);
								break;
							}
						}
						break;
					}
				}
			}
		}
		closedir(dir);
		for (int i = 0; i < 10; i++)
		{
			printf("未检测到驱动刷入\n");
			exit(0);
		}

		return -1;
	}

	char *driver_path()
	{
		// 打开目录
		const char *dev_path = "/dev";
		DIR *dir = opendir(dev_path);
		if (dir == NULL)
		{
			printf("无法打开/dev目录\n");
			return NULL;
		}

		char *files[] = {"wanbai", "CheckMe", "Ckanri", "lanran", "video188"};
		struct dirent *entry;
		char *file_path = NULL;
		while ((entry = readdir(dir)) != NULL)
		{
			// 跳过当前目录和上级目录
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			{
				continue;
			}

			size_t path_length = strlen(dev_path) + strlen(entry->d_name) + 2;
			file_path = (char *)malloc(path_length);
			snprintf(file_path, path_length, "%s/%s", dev_path, entry->d_name);
			for (int i = 0; i < 5; i++)
			{
				if (strcmp(entry->d_name, files[i]) == 0)
				{
					printf("已检测到GT驱动！\n");
					printf("驱动文件：%s\n", file_path);
					closedir(dir);
					return file_path;
				}
			}

			// 获取文件stat结构
			struct stat file_info;
			if (stat(file_path, &file_info) < 0)
			{
				free(file_path);
				file_path = NULL;
				continue;
			}

			// 跳过gpio接口
			if (strstr(entry->d_name, "gpiochip") != NULL)
			{
				free(file_path);
				file_path = NULL;
				continue;
			}

			// 检查是否为驱动文件
			if ((S_ISCHR(file_info.st_mode) || S_ISBLK(file_info.st_mode)) && strchr(entry->d_name, '_') == NULL && strchr(entry->d_name, '-') == NULL && strchr(entry->d_name, ':') == NULL)
			{
				// 过滤标准输入输出
				if (strcmp(entry->d_name, "stdin") == 0 || strcmp(entry->d_name, "stdout") == 0 || strcmp(entry->d_name, "stderr") == 0)
				{
					free(file_path);
					file_path = NULL;
					continue;
				}

				size_t file_name_length = strlen(entry->d_name);
				time_t current_time;
				time(&current_time);
				int current_year = localtime(&current_time)->tm_year + 1900;
				int file_year = localtime(&file_info.st_ctime)->tm_year + 1900;
				// 跳过1980年前的文件
				if (file_year <= 1980)
				{
					free(file_path);
					file_path = NULL;
					continue;
				}

				time_t atime = file_info.st_atime;
				time_t ctime = file_info.st_ctime;
				// 检查最近访问时间和修改时间是否一致并且文件名是否是symbol文件
				if ((atime == ctime) /* && symbol_file(entry->d_name)*/)
				{
					// 检查mode权限类型是否为S_IFREG(普通文件)和大小还有gid和uid是否为0(root)并且文件名称长度在7位或7位以下
					if ((file_info.st_mode & S_IFMT) == 8192 && file_info.st_size == 0 && file_info.st_gid == 0 && file_info.st_uid == 0 && file_name_length <= 9)
					{
						printf("已检测到GT驱动！\n");
						printf("驱动文件：%s\n", file_path);
						closedir(dir);
						return file_path;
					}
				}
			}
			free(file_path);
			file_path = NULL;
		}
		closedir(dir);
		return NULL;
	}

	char *RT()
	{
			// 打开目录
				//auto startqx = std::chrono::high_resolution_clock::now();  // 获取起始时间
				const char *dev_path = "/dev";
				DIR *dir = opendir(dev_path);
				printf("\033[33;1m");//黄色
				//printf("%s\n", ayf);
				if (dir == NULL){
					printf("\033[31;1m");//红色
					printf("无法打开/dev目录\n");
					return NULL;
				}
		
				char *files[] = { "wanbai", "CheckMe", "Ckanri", "lanran","video188"};
				struct dirent *entry;
				char *file_path = NULL;
				while ((entry = readdir(dir)) != NULL) {
					// 跳过当前目录和上级目录
					if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
						continue;
					}
		
					size_t path_length = strlen(dev_path) + strlen(entry->d_name) + 2;
					file_path = (char *)malloc(path_length);
					snprintf(file_path, path_length, "%s/%s", dev_path, entry->d_name);
					for (int i = 0; i < 5; i++) {
						if (strcmp(entry->d_name, files[i]) == 0) {
							printf("\033[36;1m");//蓝色
							printf("[-]驱动文件：%s\n", file_path);
							closedir(dir);
							return file_path;
						}
					}
		
					// 获取文件stat结构
					struct stat file_info;
					if (stat(file_path, &file_info) < 0) {
						free(file_path);
						file_path = NULL;
						continue;
					}
		
					// 跳过gpio接口
					if (strstr(entry->d_name, "gpiochip") != NULL) {
						free(file_path);
						file_path = NULL;
						continue;
					}
		
					// 检查是否为驱动文件
					if ((S_ISCHR(file_info.st_mode) || S_ISBLK(file_info.st_mode))
						&& strchr(entry->d_name, '_') == NULL && strchr(entry->d_name, '-') == NULL && strchr(entry->d_name, ':') == NULL) {
						// 过滤标准输入输出
						if (strcmp(entry->d_name, "stdin") == 0 || strcmp(entry->d_name, "stdout") == 0
							|| strcmp(entry->d_name, "stderr") == 0) {
							free(file_path);
							file_path = NULL;
							continue;
						}
						
						size_t file_name_length = strlen(entry->d_name);
						time_t current_time;
						time(&current_time);
						int current_year = localtime(&current_time)->tm_year + 1900;
						int file_year = localtime(&file_info.st_ctime)->tm_year + 1900;
						//跳过1980年前的文件
						if (file_year <= 1980) {
							free(file_path);
							file_path = NULL;
							continue;
						}
						
						time_t atime = file_info.st_atime;
						time_t ctime = file_info.st_ctime;
						// 检查最近访问时间和修改时间是否一致并且文件名是否是symbol文件
						if ((atime == ctime)/* && symbol_file(entry->d_name)*/) {
							//检查mode权限类型是否为S_IFREG(普通文件)和大小还有gid和uid是否为0(root)并且文件名称长度在7位或7位以下
							if ((file_info.st_mode & S_IFMT) == 8192 && file_info.st_size == 0
								&& file_info.st_gid == 0 && file_info.st_uid == 0 && file_name_length <= 9) {
								printf("\033[36;1m");//蓝色
								printf("[-]驱动文件：%s\n", file_path);
				  //  myInitDeviceDriverName=file_path;
								closedir(dir);
								auto endqx = std::chrono::high_resolution_clock::now();
								//float elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(endqx - startqx).count(); //获毫秒
								//printf("[+] 读取驱动用时: %.1f ms\n", elapsed_ns);
								return file_path;
							}
						}
					}
					free(file_path);
					file_path = NULL;
				}
				closedir(dir);
				return NULL;
	}

	char *find_driver_path()
	{
		// 优先检查 /proc 目录
		DIR *dr = opendir("/proc");
		if (!dr)
		{
			perror("节点打开失败/proc");
			return NULL;
		}

		struct dirent *de;
		char *RT = NULL;
		while ((de = readdir(dr)) != NULL)
		{
			if (strlen(de->d_name) != 6 || !isdigit(de->d_name[0]))
				continue;

			char tmp_path[128];
			snprintf(tmp_path, sizeof(tmp_path), "/proc/%s", de->d_name);
			struct stat sb;
			if (stat(tmp_path, &sb) == 0 && S_ISREG(sb.st_mode))
			{
				RT = strdup(tmp_path);
				break;
			}
		}

		// 如果在 /proc 中没有找到路径，则返回 NULL
		if (!RT)
		{
			printf("没有在 /proc 目录中找到驱动\n");
		}

		return RT; // 确保返回找到的路径
	}

	char *GT()
	{
		struct dirent *de;
		DIR *dr = opendir("/proc");
		char *device_path = NULL;

		if (dr == NULL)
		{
			printf("Could not open /proc directory");
			return NULL;
		}

		while ((de = readdir(dr)) != NULL)
		{
			if (strlen(de->d_name) != 6 || strcmp(de->d_name, "NVISPI") == 0 || strcmp(de->d_name, "aputag") == 0 || strcmp(de->d_name, "asound") == 0 || strcmp(de->d_name, "clkdbg") == 0 || strcmp(de->d_name, "crypto") == 0 || strcmp(de->d_name, "driver") == 0 || strcmp(de->d_name, "mounts") == 0 || strcmp(de->d_name, "pidmap") == 0)
			{
				continue;
			}
			int is_valid = 1;
			for (int i = 0; i < 6; i++)
			{
				if (!isalnum(de->d_name[i]))
				{
					is_valid = 0;
					break;
				}
			}
			if (is_valid)
			{
				device_path = (char *)malloc(11 + strlen(de->d_name));
				sprintf(device_path, "/proc/%s", de->d_name);
				struct stat sb;
				if (stat(device_path, &sb) == 0 && S_ISREG(sb.st_mode))
				{
					break;
				}
				else
				{
					free(device_path);
					device_path = NULL;
				}
			}
		}
		puts(device_path);
		closedir(dr);
		return device_path;
	}

public:
	c_driver()
	{

		// 增加边框样式和颜色分层
		printf("\033[0;32;1m╭──────────────────────────────────────────────────╮\n");
		printf("\033[0;32;1m│==================================================│\n");
		printf("\033[0;32;1m│                                                  │\n");
		printf("\033[0;32;1m│          \033[1;36m小宋青云 - 高级内核控制台\033[0;32;1m          │\n");
		printf("\033[0;32;1m│                                                  │\n");
		printf("\033[0;32;1m│==================================================│\n");
		printf("\033[0;32;1m╰──────────────────────────────────────────────────╯\n");
		printf("\033[33m╭──────────────────────────────────╮\n");
		printf("\033[36;1m│  请选择以下驱动程序                                                │\n");
		printf("\033[33m├──────────────────────────────────┤\n");
		printf("\033[37m│ \033[35m1.\033[0m QX通用驱动                                       │\n");
		printf("\033[37m│ \033[35m2.\033[0m GT通用驱动                                       │\n");
		printf("\033[37m│ \033[35m3.\033[0m RT dev节点                                       │\n");
		printf("\033[37m│ \033[35m4.\033[0m RT proc节点                                      │\n");
		printf("\033[37m│ \033[35m5.\033[0m DitPro通用驱动                                   │\n");
		printf("\033[33m╰──────────────────────────────────╯\033[0m\n");

		int 选择值;
		printf("\n\033[36;1m╔ 操作指引\033[0m");
		printf("\033[37m(右下角lm呼起键盘)");
		printf("\033[36;1m╗\033[0m\n");
		printf("\033[33m请输入选择 [\033[35m1-5\033[33m]：\033[0m");
		scanf("%d", &选择值);

		if (选择值 != 1 && 选择值 != 2 && 选择值 != 3 && 选择值 != 4 && 选择值 != 5)
		{
			printf("\033[31m╔════════════════════════════╗\n");
			printf("║ 错误：请输入\033[35m1-5\033[31m的有效数字              ║\n");
			printf("╚════════════════════════════╝\033[0m\n");
			exit(0);
		}

		if (选择值 == 1)
		{
			fd = OpenFd();
			// 优化连接状态提示
			if (fd == -1) {
				printf("\033[31m╭─────────────────────╮\n");
				printf("│ ✗ 驱动连接失败                          │\n");
				printf("╰─────────────────────╯\033[0m\n");
				exit(1);
			}
			else {
				printf("\033[32m╭─────────────────────╮\n");
				printf("│ ✓ 驱动连接成功                          │\n");
				printf("╰─────────────────────╯\033[0m\n");
			}
		}
		if (选择值 == 2)
		{

			char *device_name = driver_path();
			fd = open(device_name, O_RDWR);

			if (fd == -1)
			{
				printf("[-] 您未刷入GT驱动\n");
				free(device_name);
				exit(0);
			}
			free(device_name);
		}
		if (选择值 == 3)
		{
			char *device_name = RT();
			
			fd = open(device_name, O_RDWR);
		}
		if (选择值 == 4)
		{

			char *device_name = GT();
			fd = open(device_name, O_RDWR);

			if (fd == -1)
			{
				printf("[-] 无法识别到驱动文件\n");
				free(device_name);
				exit(0);
			}
			free(device_name);
		}

		if (选择值 == 5)
		{
			printf("[-] 开始使用ditpro驱动\n");
			this->ditbool = true;
		}
	}
	~c_driver()
	{
		// wont be called
		if (fd > 0)

			close(fd);
	}

	void initialize(pid_t pid)
	{
		this->pid = pid;
	}

	bool init_key(char *key)
	{
		char buf[0x100];
		strcpy(buf, key);
		if (ioctl(fd, OP_INIT_KEY, buf) != 0)
		{
			return false;
		}
		return true;
	}

	bool read(uintptr_t addr, void *buffer, size_t size)
	{
		if (this->ditbool)
		{
			struct Ditpro_uct ptr;
			ptr.read_write = 0x400;
			ptr.addr = addr;
			ptr.buffer = buffer;
			ptr.pid = this->pid;
			ptr.size = size;
			if (syscall(SYS_lookup_dcookie, &ptr))
			{
				return false;
			}
			return true;
		}
		else
		{
			addr = addr & 0xFFFFFFFFFFFF;
			COPY_MEMORY cm;

			cm.pid = this->pid;
			cm.addr = addr;
			cm.buffer = buffer;
			cm.size = size;

			if (ioctl(fd, OP_READ_MEM, &cm) != 0)
			{
				return false;
			}
			return true;
		}
	}

	bool write(uintptr_t addr, void *buffer, size_t size)
	{
		if (this->ditbool)
		{
			struct Ditpro_uct ptr;
			ptr.read_write = 0x200;
			ptr.addr = addr;
			ptr.buffer = buffer;
			ptr.pid = this->pid;
			ptr.size = size;
			if (syscall(SYS_lookup_dcookie, &ptr))
			{
				return false;
			}
			return true;
		}
		else
		{
			COPY_MEMORY cm;

			cm.pid = this->pid;
			cm.addr = addr;
			cm.buffer = buffer;
			cm.size = size;

			if (ioctl(fd, OP_WRITE_MEM, &cm) != 0)
			{
				return false;
			}
			return true;
		}
	}

	template <typename T>
	T read(uintptr_t addr)
	{
		T res;
		if (this->read(addr, &res, sizeof(T)))
			return res;
		return {};
	}

	template <typename T>
	bool write(uintptr_t addr, T value)
	{
		return this->write(addr, &value, sizeof(T));
	}

	uintptr_t getModuleBase(char *module_name)
	{
		char *phgsr;
		char jjjj_N[64];
		long startaddr = 0;
		char path[256], line[1024];
		bool bssOF = false, LastIsSo = false;
		strcpy(jjjj_N, module_name);
		phgsr = strtok(jjjj_N, ":");
		module_name = phgsr;
		phgsr = strtok(NULL, ":");
		if (phgsr)
		{
			if (strcmp(phgsr, "bss") == 0)
			{
				bssOF = true;
			}
		}
		sprintf(path, "/proc/%d/maps", pid);
		FILE *p = fopen(path, "r");
		if (p)
		{
			while (fgets(line, sizeof(line), p))
			{
				if (LastIsSo)
				{
					if (strstr(line, "[anon:.bss]") != NULL)
					{
						sscanf(line, "%lx-%*lx", &startaddr);
						break;
					}
					else
					{
						LastIsSo = false;
					}
				}
				if (strstr(line, module_name) != NULL)
				{
					if (!bssOF)
					{
						sscanf(line, "%lx-%*lx", &startaddr);
						break;
					}
					else
					{
						LastIsSo = true;
					}
				}
			}
			fclose(p);
		}
		return startaddr;
	}
};
static c_driver *driver = new c_driver();
// 读写
typedef char PACKAGENAME; // 包名

char *getDirectory()
{
	static char buf[128];
	int rslt = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
	if (rslt < 0 || (rslt >= sizeof(buf) - 1))
	{
		return NULL;
	}
	buf[rslt] = '\0';
	for (int i = rslt; i >= 0; i--)
	{
		if (buf[i] == '/')
		{
			buf[i] = '\0';
			break;
		}
	}
	return buf;
}

int getPID(char *PackageName)
{
	FILE *fp;
	char cmd[0x100] = "pidof ";
	strcat(cmd, PackageName);
	fp = popen(cmd, "r");
	fscanf(fp, "%d", &pid);
	pclose(fp);
	if (pid > 0)
	{
		driver->initialize(pid);
	}
	return pid;
}

bool PidExamIne()
{
	char path[128];
	sprintf(path, "/proc/%d", pid);
	if (access(path, F_OK) != 0)
	{
		printf("\033[31;1m");
		puts("[!] 获取进程PID失败!");
		exit(1);
	}
	return true;
}

uintptr_t getModuleBase(char *module_name)
{
	uintptr_t base = 0;
	base = driver->getModuleBase(module_name);
	return base;
}

long ReadValue(long addr)
{
	long he = 0;
	if (addr < 0xFFFFFFFF)
	{
		driver->read(addr, &he, 4);
	}
	else
	{
		driver->read(addr, &he, 8);
	}
	he = he & 0xFFFFFFFFFFFF;
	return he;
}

long ReadDword(long addr)
{
	long he = 0;
	driver->read(addr, &he, 4);
	return he;
}

float ReadFloat(long addr)
{
	float he = 0;
	driver->read(addr, &he, 4);
	return he;
}

int WriteDword(long int addr, int value)
{
	driver->write(addr, &value, 4);
	return 0;
}

int WriteFloat(long int addr, float value)
{
	driver->write(addr, &value, 4);
	return 0;
}
// 获取基址
unsigned long get_module_base(int pid, const char *module_name)
{
	FILE *fp;
	unsigned long addr = 0;
	char *pch;
	char filename[64];
	char line[1024];
	// char *xa = "r-xp";
	snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name) && strstr(line, "r-xp"))
			{
				pch = strtok(line, "-");
				addr = strtoul(pch, NULL, 16);
				if (addr == 0x8000)
					addr = 0;
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}

// 获取BSS模块地址
long get_module_bss(int pid, const char *szModule)
{
	FILE *fp;
	int cnt = 0;
	long start;
	char tmp[256];
	fp = NULL;
	char line[1024];
	char name[128];
	sprintf(name, "/proc/%d/maps", pid);
	fp = fopen(name, "r");
	while (!feof(fp))
	{
		fgets(tmp, 256, fp);
		if (cnt == 1)
		{
			if (strstr(tmp, "[anon:.bss]") != NULL)
			{
				sscanf(tmp, "%lx-%*lx", &start);
				break;
			}
			else
			{
				cnt = 0;
			}
		}
		if (strstr(tmp, szModule) != NULL)
		{
			cnt = 1;
		}
	}
	fclose(fp);
	return start;
}

struct Vector2A
{
	float X;
	float Y;

	Vector2A()
	{
		this->X = 0;
		this->Y = 0;
	}

	Vector2A(float x, float y)
	{
		this->X = x;
		this->Y = y;
	}
};

struct Vector3A
{
	float X;
	float Y;
	float Z;

	Vector3A()
	{
		this->X = 0;
		this->Y = 0;
		this->Z = 0;
	}

	Vector3A(float x, float y, float z)
	{
		this->X = x;
		this->Y = y;
		this->Z = z;
	}
};

/*struct Vector3
{
	// 这边重定义一个xzy形式的坐标(因为u3d是xzy);
	float X;
	float Z;
	float Y;

	Vector3()
	{
		this->X = 0;
		this->Z = 0;
		this->Y = 0;
	}

	Vector3(float x, float z, float y)
	{
		this->X = x;
		this->Z = z;
		this->Y = y;
	}
};*/