// extern "C" : Cの言語仕様で関数を定義する。
extern "C" void KernelMain()
{
    while(1) __asm__("hlt");
}
