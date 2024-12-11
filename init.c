#include<libBareMetal.c>
#include"pf/pf.h"
ssize_t write (int __fd, const void *__buf, size_t __n) __wur{b_output(__buf,__n);return __n;}
typedef struct BMFSInfo {
 char pad[1024];
 char tag[3072];
} BMFSInfo;
typedef struct BMFSEntry { 
 char FileName[32];
 u64 StartingBlock;
 u64 ReservedBlock;
 u64 FileSize;
 u64 Unused;
}*BMFSEntry;
typedef struct BMFSEntry BMFSDirectory[64];
struct BMFS {
 BMFSInfo info;
 BMFSDirectory dir;
};
static struct BMFS bmfs;
static int base=32768; //BMFS starts 32768*4096=128MiB in from disk
int main(int,char**);int init();int ls();
__attribute__((__section__(".text.startup"))) 
int _start(){
 if(init())return pf("couldn't find BMFS\n");
 return ls();
}
int memcmp(char*x,char*y,u64 n){
 u64 i=0;for(;i<n;i++){
  char d=y[i]-x[i];
  if(d)return d;
 }
 return 0;
}
int init(void){
 return !(2==b_storage_read(&bmfs,base,2,0) && !memcmp("BMFS",bmfs.info.tag,4));  //BMFS signature
}
int ls(void){
 int i=0;
 for(;i<64&&*bmfs.dir[i].FileName;i++)
  pf("%s ",bmfs.dir[i].FileName);
 pf("\n");
 return 0;
}
