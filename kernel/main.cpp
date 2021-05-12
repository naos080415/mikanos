#include <cstdint>
#include <cstddef>

#include "graphics.hpp"
#include "font.hpp"

void* operator new(size_t size, void* buf)
{
    return buf;
}

void operator delete(void *obj) noexcept { }

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter* pixel_writer;

// extern "C" : Cの言語仕様で関数を定義する。
extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config)
{
    switch(frame_buffer_config.pixel_format) {
        case kPixelRGBResv8BitPerColor:
            pixel_writer = new(pixel_writer_buf)
                RGBResv8BitPerColorPixelWriter{frame_buffer_config};
            break;

        case kPixelBGRResv8BitPerColor:
            pixel_writer = new(pixel_writer_buf)
                BGRResv8BitPerColorPixelWriter{frame_buffer_config};
            break;
    }

    for(int x = 0;x < frame_buffer_config.horizontal_resolution; ++x){
        for(int y = 0;y < frame_buffer_config.vertical_resolution; ++y){
            pixel_writer->Write(x, y, {255, 255, 255});
        }
    }

    for(int x = 0;x < 200; ++x){
        for(int y = 0;y < 500; ++y){
            pixel_writer->Write(x, y, {0, 255, 0});
        }
    }

    // WriteAscii(*pixel_writer, 50, 50, 'A', {0, 0, 0});
    // WriteAscii(*pixel_writer, 58, 50, 'C', {0, 0, 0});

    WriteString(*pixel_writer, 0, 66, "Hello World! MikanOS", {0, 0, 0});
    WriteString(*pixel_writer, 0, 66, "Helo Vim" , {0, 0, 0});     
    while(1) __asm__("hlt");
}
