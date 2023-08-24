/**
 * @file threads_tb.cpp
 *
 * @brief POSIX Threads testbench
 *
 * <long_description>
 */

/**
 * This file is part of OS_Concepts.
 *
 * OS_Concepts is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * OS_Concepts is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OS_Concepts. If not, see <https://www.gnu.org/licenses/>.
 */

#include <cstdbool>
#include <cstdio>

#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"

#include "simple_fib.hpp"

int main(int argc, char **argv)
{
	os_cpp::simple_fib_multi_thread fib1(100000u, 24u);

	return 0;
}