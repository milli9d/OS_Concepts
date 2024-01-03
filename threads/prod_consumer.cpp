#include <iostream>
#include <thread>
#include <cstdio>
#include <cstdint>

class producer {
  private:
    void _run(void* args) {}

  public:
    producer() {
        std::thread(_run);
    }
};

class consumer {};

int main() {
    return 0;
}
