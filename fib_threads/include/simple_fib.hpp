/**
 * @file fib_threads.hpp
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
#pragma once

#include <iostream>

#include <bits/stdc++.h>

#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"

namespace os_cpp
{

/**
 * @brief
 */
class simple_fib {
protected:
	/**
	 * @brief
	 * @param n
	 * @return
	 */
	long long unsigned int _fib_r(long long unsigned int n);

	/**
	 * @brief
	 * @param n
	 */
	void _print_fib_r(long long unsigned int n);

	std::vector<long long unsigned int> _memo{};

public:
	simple_fib(){ /*do nothing*/ };
	simple_fib(long long unsigned int n);
};

/**
 * @brief
 */
class simple_fib_multi_thread : protected simple_fib {
private:
	typedef struct _fib_thread_cfg_s {
		long long unsigned int start;
		long long unsigned int end;
		simple_fib_multi_thread *_this;
	} fib_thread_cfg_s;

	std::vector<pthread_t *> _threads{};

	static void *_thread_handler(void *args);
	sem_t _sem;

	long long unsigned int _num_threads{};
	long long unsigned int _thread_range_sz{};

public:
	simple_fib_multi_thread() = delete;
	~simple_fib_multi_thread();

	simple_fib_multi_thread(long long unsigned int n, uint16_t num_threads);
};

} // namespace os_cpp