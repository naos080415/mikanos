#include <cstdint>
#include "frame_buffer_config.hpp"

struct PixelColor {
    uint8_t r, g, b;
};

// WritePixel は1つの点を描画する
// retaval : 0 → 成功   not 0(ex. -1)　→  失敗
int WritePixel(const FrameBufferConfig& config,
            int x, int y, const PixelColor& c)
{
    const int pixel_position = config.pixels_per_scan_line * y + x;
    if(config.pixel_format == kPixelRGBResv8BitPerColor) {
        uint8_t* p = &config.frame_buffer[4 * pixel_position];
        p[0] = c.r;
        p[1] = c.g;
        p[2] = c.b;
    }else if(config.pixel_format == kPixelBGRResv8BitPerColor) {
        uint8_t* p = &config.frame_buffer[4 * pixel_position];
        p[0] = c.b;
        p[1] = c.g;
        p[2] = c.r;
    }else {
        return -1;
    }
    return 0;
}


// extern "C" : Cの言語仕様で関数を定義する。
extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config)
{
    for(int x = 0;x < frame_buffer_config.horizontal_resolution; ++x){
        for(int y = 0;y < frame_buffer_config.vertical_resolution; ++y){
            WritePixel(frame_buffer_config, 100 + x, 100 + y, {0,255,0});
        }
    }
    while(1) __asm__("hlt");
}

// extern "C" : Cの言語仕様で関数を定義する。
// extern "C" void KernelMain(uint64_t frame_buffer_base,
//                            uint64_t frame_buffer_size)
// {
//     uint8_t* frame_buffer = reinterpret_cast<uint8_t*>(frame_buffer_base);
//     for(uint64_t i = 0;i < frame_buffer_size; ++i){
//         frame_buffer[i] = i % 256;
//     }
//     while(1) __asm__("hlt");
// }
