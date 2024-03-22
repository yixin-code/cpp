#include <iostream>
#include <string.h>
#include <fstream>
#include <assert.h>

void file_cp(char *argv[]);
void file_cp2(char *argv[]);

int main(int argc, char *argv[]) {
    // file_cp(argv);
    file_cp2(argv);

    return 0;
}

void file_cp(char *argv[]) {
    std::ifstream fin(argv[1]);
    assert(fin.is_open());
    std::ofstream fout(argv[2]);
    assert(fout.is_open());

    char buf[1024] = {0};
    while (fin.readsome(buf, sizeof(buf))) {
        std::cout << buf;
        fout.write(buf, strlen(buf));
    }

    fin.close();
    fout.close();
}

void file_cp2(char *argv[]) {
    std::ofstream fout(argv[1], std::ios::binary);
    assert(fout.is_open());

    char buf[] = R"(孤单听雨的猫
往时间裂缝里看到了我
雷电交加之外的另一些我
乌云静止以后 跳进平行时空
那些我 旅行中的你我
回忆胡乱穿梭 坠落
交换余生 是我 非我 苦与乐
阴天之后总有续命的晴空
如果我们几经转折 结局一样不动
也才算无愧这分合
定位心海的锚
让时间停顿的像慢动作
你说命运很坏吧幸好有我
如果没有以后 如果平行失控
那些我 不同人生的我
会以什么方式 哭过
交换余生 是我 非我 苦与乐
阴天之后总有续命的晴空
如果我们几经转折 结局一样不动
也才算无愧这分合
云等风 人等梦 爱辗过时光等什么
记不住 认不出 泪眼中谁一样脸红
等你说 等我说 一等就是一个宇宙
日升换月落 真爱换寂寞
交换余生 也许 忘了 第几梦
那时我们身处第几号时空
因为我们手心紧握 记忆也能紧扣
可不怕前方的虫洞
爱是时间的古董)";
    fout.write(buf, strlen(buf));
    fout.close();

    std::ifstream fin(argv[1], std::ios::binary);
    assert(fin.is_open());
    
    char buf2[1024] = {0};
    fin.read(buf2, sizeof(buf));

    std::cout << buf2;
    fin.close();
}