#include <iostream>
#include <algorithm>
#include <cstdlib>

#include <thread>
#include <chrono>

#include <cstdint>

#include <logging.h>
LOG_TAG(MATRIX);

namespace math_lib {

template<typename T, size_t ROWS, size_t COLS>
class matrix {
  private:
    T* _data;
    bool mxm_matrix{ false };

    /**
     * @brief get idx
     * @param i
     * @param j
     * @return
     */
    inline size_t get_idx(size_t i, size_t j) {
        if (i > ROWS || j > COLS) {
            throw std::out_of_range("Out of range");
        }
        return ((i * COLS) + j);
    }

    /**
     * @brief transpose m x m matrix
     * @param
     */
    void inline transpose_mxm_matrix(void) {
        for (size_t i = 0u; i < ROWS; i++) {
            for (size_t j = i + 1u; j < COLS; j++) { std::swap(_data[get_idx(i, j)], _data[get_idx(j, i)]); }
        }
    }

  public:
    /**
     * @brief
     */
    matrix() {
        LOG_INFO("Matrix M = %lu N = %lu", ROWS, COLS);
        mxm_matrix = (ROWS == COLS);
        _data = (T*) calloc(sizeof(T), ROWS * COLS);
        for (size_t i = 0u; i < ROWS; i++) {
            for (size_t j = 0u; j < COLS; j++) { _data[get_idx(i, j)] = ((rand()) % 10u) + '0'; }
        }
    }

    ~matrix() {
        free(_data);
    }

    /**
     * @brief Overload ostream operator
     * @param os
     * @param obj
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, matrix<T, ROWS, COLS>& obj) {
        for (size_t i = 0u; i < ROWS; i++) {
            os << "[ ";
            for (size_t j = 0u; j < COLS; j++) { os << obj._data[obj.get_idx(i, j)] << " "; }
            os << "]" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50u));
        }
        return os;
    }

    /**
     * @brief Pretty print matrix
     * @param
     */
    void print(void) {
        std::cout << *this;
    }

    /**
     * @brief rotate 90 degree clockwise
     * @param
     */
    void rotate_90_clockwise_mxm(void) {
        if (mxm_matrix) {
            this->transpose();

            /* reverse all rows */
            for (size_t i = 0u; i < ROWS; i++) {
                for (size_t j = 0u; j < COLS / 2u; j++) {
                    std::swap(_data[get_idx(i, j)], _data[get_idx(i, COLS - j - 1u)]);
                }
            }
        }
    }

    /**
     * @brief rotate a matrix, cycles style
     * @param
     */
    void rotate_90_clockwise(void) {
        if (!mxm_matrix) {
            return;
        }

        for (size_t i = 0u; i < ROWS / 2u; i++) {
            for (size_t j = 0u; j < COLS - i - 1u; j++) {
                T& top_left = _data[get_idx(i, j)];
                T& top_right = _data[get_idx(i, COLS - j - 1u)];
                T& bottom_left = _data[get_idx(ROWS - i - 1u, j)];
                T& bottom_right = _data[get_idx(ROWS - i - 1u, COLS - j - 1u)];

                T temp = top_left;

                top_left = top_right;
                top_right = bottom_right;
                bottom_right = bottom_left;
                bottom_left = temp;
            }
        }
    }

    /**
     * @brief transpose the matrix
     * @param
     */
    void transpose(void) {
        if (mxm_matrix) {
            transpose_mxm_matrix();
        } else {
            LOG_ERR("M x N not implemented");
        }
    }
};

} // namespace math_lib

int main(int argc, char** argv) {
    math_lib::matrix<uint8_t, 2u, 2u> _matrix;
    std::cout << _matrix << std::endl;

    _matrix.rotate_90_clockwise();
    std::cout << _matrix << std::endl;

    _matrix.transpose();
    std::cout << _matrix << std::endl;

    return 0;
}
