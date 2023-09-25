#include <sys/types.h>
#ifdef __cplusplus // 使用c的链接方式
extern "C" {
#endif

double face_recognition(const unsigned char *pic, size_t len);
    

#ifdef __cplusplus
}
#endif